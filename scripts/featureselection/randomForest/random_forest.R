#!/usr/bin/env Rscript
##############################################################################
### Random Forest analysis

#Usage
# Rscript --vanilla randomforest.R --phenotype [phenotype] --features [features] [outdir]
# Arguments: 
#     phenotype: a tabulated file containing ids and phenotypic classes
#     features:  a tabulated file containing ids and the level of each individual features
#     outdir:    a path to a folder that will contain all results
#####################################################################

#############
# Parse arguments
############
# load libraries
library(optparse)
library(randomForest)
library(plyr)
library(dplyr)
library(caret)
library(e1071)
library(doMC)


# parse command line arguments
option_list = list(
  make_option(c("-p", "--phenotype"), type="character", default=NULL,help="phenotypic classes file", metavar="character"),
  make_option(c("-f", "--features"),type="character",default=NULL,help="features data file",metavar="character"),
  make_option(c("-n", "--ntrees"),type="integer",default=500,help="number of trees to build. By default 500. A sufficiently high number of tree is recommended",metavar = "number"),
  make_option(c("-o", "--outdir"), type="character", default="./RF.results/",help="output directory location (by default: ./RF.results", metavar="character"),
  make_option(c("-r", "--runs"), type="integer",default=100,help="number of runs for RF on original and permuted datasets",metavar="number"),
  make_option(c("-t","--threads"),type="integer",default=4,help="number of threads to use",metavar = "number")
) 
opt_parser = OptionParser(option_list=option_list);
opt = parse_args(opt_parser)


## for now, I manually change the values in the opt list. They should come from the command line arguments in the future.
opt$phenotype = "~/SURFdrive/trichome_team/11.analysis/metabolite_feature_selection/20170208_RF_with_sacha/01.whitefly_terpenoids/whiteflies.txt"
opt$features = "~/SURFdrive/trichome_team/11.analysis/metabolite_feature_selection/20170208_RF_with_sacha/01.whitefly_terpenoids/terpenoids.txt"
opt$ntrees = 500
opt$threads = 4
opt$runs = 4

#############################
# Read and format input files
#############################

# read phenotype data
# change column name
pheno.df = read.delim(opt$phenotype,header = T,stringsAsFactors = F)
colnames(pheno.df) = c("id","class")

# read feature data
# change only the first column name
features.df = read.delim(opt$features,header=T,stringsAsFactors = F)
colnames(features.df)[1]="id"

# merge the two dataframes
df = dplyr::inner_join(pheno.df,features.df,by="id")

# put sample ids as row names
row.names(df)=df$id
df$id <- NULL

# convert class column into factor (so that random forest knows should run a classification)
df$class = as.factor(df$class)

############################################
# Determine Random Forest optimal parameters
############################################
# Random forest analysis (using default number of trees and features)
# mtry = number of variables. Will be the square root of number of features
registerDoMC(cores = opt$threads)
fit.test = randomForest(formula = class ~ ., data = df,ntree=1000) 

# Determine optimal number of trees and optimal number of features
plot(fit.test$err.rate[,1],type="l",col="red",xlab = "Number of trees",ylab = "OOB error")

# Determine number of variables to be used at each split
model = train(class ~ .,data=df,method="rf")
number_of_variables_to_use = model$bestTune$mtry


###################################################################
# run Random Forest analysis with optimal parameters multiple times
###################################################################
fits.original = list()
for (i in 1:opt$runs){
  fits.original[[i]] = randomForest(
    formula = class ~ .,
    data=df,
    ntree=opt$ntrees,
    mtry=number_of_variables_to_use,
    importance=T)
}

####### MDA #########
# original Mean Decrease in Accuracy for each feature
original.mdas = list(length=nFeatures)
for (k in 1:nFeatures){
  feature.mdas = numeric(length=opt$runs)
  for (i in 1:opt$runs){
    # fit a Random Forest on the original dataframe
    fit = randomForest(formula = class ~ .,data = df,ntree=opt$ntrees,mtry=number_of_variables_to_use,importance=T)
    # extract Mean Decrease in Accuracy for feature k
    imp = fit$importance[k,3]
    feature.mdas[i] = imp                     
  }
  original.mdas[[k]]=feature.mdas
}


# add names of features
# transform into a dataframe and then a matrix
names(original.mdas) = colnames(df)[1:nFeatures+1]
original.mdas = ldply(original.mdas,.id = "feature")
colnames(original.mdas)=c("feature",paste("mda",seq(1:opt$runs),sep = ""))
row.names(original.mdas)=original.mdas$feature;original.mdas$feature = NULL;original.mdas=as.matrix(original.mdas)

######### original Out Of Bag error (based on confusion matrix) ##########
original.OOBs = numeric(length=opt$runs)
for (i in 1:opt$runs){
  original.OOBs[i] = mean(fits.original[[i]]$err.rate[,1])
}

#########################################################################################
# Permutations: comparison of OOB error and MDA values for original and permuted datasets 
#########################################################################################
nFeatures = ncol(df) - 1

# helper function to permute the dataframe on one column
permute.dataframe <- function(df,col2permute){
  permutedRows = shuffle(nrow(df))
  df[,col2permute] = df[permutedRows,col2permute]
  return(df)
}

# the i loop get MDA values for one feature for the number of requested runs
# the k loop iterates over the number of features
# the results are stored in a list
permuted.mdas = list(length=nFeatures)
for (k in 1:nFeatures){
  feature.mdas = numeric(length=opt$runs)
  for (i in 1:opt$runs){
    # permute original dataframe for feature k (add +1 to start after the class column)
    permuted.df = permute.dataframe(df,k+1)
    # fit a Random Forest on the permuted dataframe
    fit = randomForest(formula = class ~ .,data = permuted.df,ntree=opt$ntrees,mtry=number_of_variables_to_use,importance=T)
    # extract Mean Decrease in Accuracy for feature k
    imp = fit$importance[k,3]
    feature.mdas[i] = imp                     
  }
  permuted.mdas[[k]]=feature.mdas
}
# add names of features
# transform into a dataframe and then to a matrix
names(permuted.mdas) = colnames(df)[1:nFeatures+1]
permuted.mdas = ldply(permuted.mdas,.id = "feature")
colnames(permuted.mdas)=c("feature",paste("mda",seq(1:opt$runs),sep = ""))
row.names(permuted.mdas)=permuted.mdas$feature;permuted.mdas$feature = NULL;permuted.mdas=as.matrix(permuted.mdas)
hist(permuted.mdas)

#########################################################################################
# Computing feature p-values
#########################################################################################
pvals = numeric(length=nFeatures)
for (i in 1:nFeatures){
  pvals[i] = ks.test(original.mdas[i,],permuted.mdas[i,])$p.value
}
  
  
  
  
  
}

