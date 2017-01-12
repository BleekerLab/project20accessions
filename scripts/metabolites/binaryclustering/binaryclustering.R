#!/usr/bin/env Rscript
############################
### Binary clustering and dendrogram from a dataframe
# author: marc galland
# contact: m.galland@uva.nl
# First version: 2016/12/16
##########################

# load librairies
library("optparse")
library("gridExtra")
library("ade4")

#############
# option list
#############
option_list = list(
  make_option(c("-i","--input",default=FALSE,type="character",help="Path to input data file")),
  make_option(c("-o","--outdir",default=FALSE,type="character",help="Output directory")),
  make_option(c("-s","--species",default=FALSE,help="The tomato genotype to species correspondence file (two columns accession/species"))
)
opt = parse_args(OptionParser(option_list = option_list))

# check if arguments are correct
if (is.null(opt$input)){
  stop("I need input data to give you a proper cluster")
}
if (is.null(opt$outdir)){
  stop("Please specify an output directory to store results")
}
if (is.null(opt$species)){
  stop("Please specify a file with the genotype/species correspondence")
}

## result directory
print(opt$outdir)
dir.create(opt$outdir,showWarnings = F)

#########################################
## Load data and convert to binary matrix
########################################
# check file extension to load file
if (tools::file_ext(opt$input) == "csv"){
  df = read.csv(opt$input,header = T,stringsAsFactors = F)
} else if (tools::file_ext(opt$input) == "txt") {
  df = read.delim(opt$input,header=T,stringsAsFactors = F)
} else {
  print("input data needs to be comma-separated (.csv) or tabulated (.txt)")
}

# load species/accession
accession2species = read.delim(opt$species,header = T,sep="\t",stringsAsFactors = F)

# replace values > 0 by 1
# util functions
replacebyone <- function(x) {
  if (x > 0){
    x <- 1
  } else if (x == 0) {
    x <- 0
  } else {
    print("you have a problem in your input data (should be 0 or positive values")
  }
}

# make df binary (0 or 1) by applying it to the whole matrix
# replace NAs by zero
# convert to matrix
df[is.na(df)] <- 0
row.names(df) = df$compound
df$compound <- NULL
mat = apply(as.matrix(df[,2:ncol(df)]),MARGIN = 1:2,FUN = replacebyone)
mat = t(mat)

# print the table
#title <- textGrob("Title",gp=gpar(fontsize=50))
#footnote <- textGrob("footnote", x=0, hjust=0,
#                     gp=gpar( fontface="italic"))

# Dendrograms
# select method for distance calculation 
# 1 = Jaccard (size of intersection/size of union)
dist = dist.binary(mat,method=1)

# hierarchical clustering  
hclust.mat = hclust(dist,method = "average")

# plot using base graph
maxy = round(max(hclust.mat$height) + 0.1*max(hclust.mat$height),digits = 1)
plot(hclust.mat,ylab = "Jaccard distance",xlab = "Accessions")

#save
svg(filename = file.path("results/","dendogram.svg"))
plot(hclust.mat,ylab = "Jaccard distance",xlab = "Accessions",ylim=c(0,maxy))
dev.off()

######################
### Print a nice table
######################
table <- tableGrob(mat)

