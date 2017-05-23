#!/usr/bin/env Rscript
##############################################################################
### Random Forest analysis

#Usage
# Rscript --vanilla survival.R --data [data file] --outdir [outdir]
# Arguments: 
#     phenotype: a tabulated file containing ids and phenotypic classes
#     features:  a tabulated file containing ids and the level of each individual features
#     outdir:    a path to a folder that will contain all results
#####################################################################

#######################################
# Libraries and command-line arguments
######################################
# load libraries
library(optparse)
library(dplyr)
library(survminer)
library(survival)
library(svglite)
library(ggplot2)

# parse command line arguments
option_list = list(
  make_option(c("-i", "--data"), type="character", default=NULL,help="input file containing the survival data", metavar="character"),
  make_option(c("-o", "--outdir"), type="character", default="./",help="output directory location: by default current working directory", metavar="character")
) 
opt_parser = OptionParser(option_list=option_list);
args = parse_args(opt_parser)


args$data = "~/SURFdrive/trichome_team/06.results_from_xp/Bioassays/thrips/20161216_survival/survival_data.txt"
args$outdir = "~/Desktop/surv/"

##############
# import data
#############

# check file extension to load file
if (tools::file_ext(args$data) == "csv"){
  survData = read.csv(args$data,header = T,stringsAsFactors = F)
} else if (tools::file_ext(args$data) == "txt") {
  survData = read.delim(args$data,header=T,stringsAsFactors = F)
} else {
  print("The input data file needs to be comma-separated (.csv) or tabulated (.txt)")
}

# change column names
colnames(survData) = c("accession","time","status")

##########################
# creates result directory
##########################
resdir = "results"
unlink(resdir,recursive = TRUE) # empty in case older results are present
dir.create(resdir,showWarnings = F)

###################
# Survival analysis
###################

####### Medians ###########
fit <- with(survData,survfit(formula = Surv(time,status) ~ accession))

# extract and plot medians
res = as.data.frame(summary(fit)$table)

# order by biggest median survival time
res = res[order(res$median,decreasing = F),]

# change names and add column
row.names(res) = gsub("accession=","",row.names(res))
res$accession = row.names(res)

# plot medians
g <- ggplot(res,mapping = aes(x=accession,y=median)) +
  geom_bar(stat="identity",colour="black") + 
  scale_x_discrete(limits=res$accession) +
  theme(axis.text.x = element_text(angle=40,hjust = 1)) +
  labs(y = "Median survival time (days)")

ggsave(file.path(resdir,"medians.png"),plot = g,width = 7,height = 5,dpi=600)
ggsave(file.path(resdir,"medians.svg"),plot = g,width= 7,height = 5)

######## Kaplan-Meier survival curves ###########
# define helper function to plot survival curve
plotSurvival = function(df,confidence=0.95,xmin=0,xmax = 19){
  # calculate survival object
  survObject = with(df,Surv(time = time,event = status))
  # fit model
  fit <- survfit(formula = survObject ~ accession,data = df,conf.int=confidence)
  # plot model
  g <- ggsurvplot(
    fit,                      # survfit object with calculated statistics.
    risk.table = FALSE,        # show risk table.
    pval = TRUE,              # show p-value of log-rank test.
    conf.int = TRUE,          # show confidence intervals for 
    # point estimaes of survival curves.
    xlim = c(xmin,xmax),           # present narrower X axis, but not affect
    # survival estimates.
    break.time.by = 1,        # break X axis in time intervals by 500.
    ggtheme = theme_bw(),  # customize plot and risk table with a theme.
    risk.table.y.text.col = T,  # colour risk table text annotations.
    risk.table.y.text = FALSE, # show bars instead of names in text annotations in legend of risk table
    font.main = 18,              # title font size
    font.x = 16,                 # font x axis 
    font.y = 16                 # font y axis
  )
  return(g)
}

# empty list for plots
l = list()

# make plots
accessions = unique(survData$accession)
for (i in seq_along(accessions)){
  df = dplyr::filter(survData,accession == accessions[i])
  l[[i]] = plotSurvival(df)
  gg = l[[i]]$plot + ggtitle(accessions[i]) + theme(plot.title = element_text(hjust = 0.5))
  ggsave(filename = file.path(resdir,paste(accessions[i],".png",sep = "")),plot = gg,width = 7,height = 5,dpi = 400)
}


##########################
# Cox proportional hazards
##########################
# fit a Cox PH model
cox.fit = coxph(formula = Surv(time,status) ~ accession,data = survData)

# exp(β) is the ratio of the hazards between two individuals whose values of x1 differ by one unit when all other covariates are held constant. 
#This is equivalent to say that log(group hazard/baseline hazard)=log((h(t)/h0(t))=∑iβixi.
#Then, a unit increase in xi is associated with βi increase in the log hazard rate

# Here the coefficient can be translated as:
# with all other covariates held constant, this is the hazard ratio (increase chance to die) for a thrips if on the corresponding accession
# compared with the baseline (not being on that accession)
capture.output(summary(cox.fit), file = file.path("cox.results.txt"))
