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
  make_option(c("-t","--threads"),type="integer",default=4,help="number of threads to use",metavar = "number")
) 
opt_parser = OptionParser(option_list=option_list);
opt = parse_args(opt_parser)


## for now, I manually change the values in the opt list. They should come from the command line arguments in the future.
opt$phenotype = "~/SURFdrive/trichome_team/11.analysis/metabolite_feature_selection/20170208_RF_with_sacha/01.whitefly_terpenoids/whiteflies.txt"
opt$features = "~/SURFdrive/trichome_team/11.analysis/metabolite_feature_selection/20170208_RF_with_sacha/01.whitefly_terpenoids/terpenoids.txt"
opt$ntrees = 500
opt$threads = 4

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
fit.test = randomForest(formula = class ~ ., data = df,ntree=500) 

# Determine optimal number of trees and optimal number of features
plot(fit.test$err.rate[,1],type="l",col="red",xlab = "Number of trees",ylab = "OOB error")

# Determine number of variables to be used at each split
model = train(class ~ .,data=df,method="rf")
number_of_variables_to_use = model$bestTune$mtry

####################################################
# run Random Forest analysis with optimal parameters
####################################################
fit.optimized = randomForest(
  formula = class ~ .,
  data=df,
  ntree=opt$ntrees,
  mtry=number_of_variables_to_use,
  importance=T)
  
#################################
### Plot most important variables
#################################
varImpPlot(fit.optimized)

#################################################################
# Comparison of OOB errors between original and permuted datasets 
#################################################################
# Features p-values 
# Post-analysis quality check (permutation)


