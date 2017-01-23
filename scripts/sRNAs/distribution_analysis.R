####
# To display distributions of small RNAs in Solanum sp. samples
#####
library(ggplot2)
library(dplyr)
library(reshape2)


setwd("/Users/mgalland/SURFdrive/trichome_team/06.results_from_xp/sRNA-Seq/20170113_srnadesc")


distridir = "distri/"

# read all original files
originals = list.files(distridir)
# input files
original = read.table("original_distributions.txt",header = T,sep = "\t")
trimmed = read.table("trimmed_distributions.txt",header = T,sep = "\t")
accession2species = read.table("~/Documents/02.UvA_POSTDOC_backup/data//01.sequencing_runs//Ion_Proton_20_accessions//sample2species.parsed.txt",header = T,sep = "\t")

# filtering original 
colnames(original)[1] = c("range")
good_columns = colnames(original)[!grepl(pattern = "^S[0-9][0-9][0-9]*|*trimmed.clipped",x = colnames(original),ignore.case = F)] # to list unwanted columns
original_filtered = data.frame(original[,1],original[colnames(original) %in% good_columns])

############### compute and plot read percentages per length from original/trimmed counts #####################
# calculate percentages
original_percent = data.frame(
  original_filtered[,1],
  sweep(original_filtered[,-1],MARGIN = 2,colSums(na.omit(original_filtered[,-1])),FUN = "/")
  )
colnames(original_percent)[1] = c("range")

trimmed_percent = data.frame(trimmed[,1],
                             sweep(trimmed[,-1],MARGIN = 2,colSums(na.omit(trimmed[,-1])),FUN = "/")
)
colnames(trimmed_percent)[1] = c("range")

# reshape
m_original_percent = melt(original_percent, na.rm = TRUE,id.vars = c("range"),value.name = c("percentage"),variable.name = c("accession"))
m_trimmed_percent = melt(trimmed_percent, na.rm = TRUE,id.vars = c("range"),value.name = c("percentage"),variable.name = c("accession"))

# draw 1 plot per accession (before / after trimming)
accessions = as.character(unique(m_original_percent$accession))
formats = c(".png",".pdf")

  # original
for (j in 1:length(formats)){
  for (i in 1:length(accessions)){
    mypath = file.path(getwd(),paste(accessions[i],"_original_distribution",formats[j],sep = ""))
    p <- ggplot(data = m_original_percent[which(m_original_percent$accession == accessions[i]),],aes(x=range,y = percentage)) + geom_bar(stat="identity")
    p + ggtitle(paste("Raw read length distribution of ",accessions[i],sep = "")) + theme(plot.title=element_text(size=rel(1.5),family="Arial",face="bold",colour="black"))
    p + xlab("Read length (nts") + ylab("Percentage of reads")
    p + theme(axis.title.x = element_text(size=16,family="Arial"),axis.title.y = element_text(size=16,family="Arial"))
    p + scale_x_continuous(name="Read lengths (nts)",limits=c(0,200))
    ggsave(filename = mypath,width = 10,height = 8,units = "cm")
  }
}

  # trimmed
for (j in 1:length(formats)){
  for (i in 1:length(accessions)){
    mypath = file.path(getwd(),paste(accessions[i],"_trimmed_distribution",formats[j],sep = ""))
    p <- ggplot(data = m_trimmed_percent[which(m_trimmed_percent$accession == accessions[i]),],aes(x=range,y = percentage)) + geom_bar(stat="identity")
    p + ggtitle(paste("Trimmed read length distribution of ",accessions[i],sep = "")) + theme(plot.title=element_text(size=rel(1.5),family="Arial",face="bold",colour="black"))
    p + xlab("Read length (nts") + ylab("Percentage of reads")
    p + theme(axis.title.x=element_text(size=16,family="Arial"),axis.title.y =element_text(size=16,family="Arial"))
    p + scale_x_continuous(name="Read lengths (nts)",limits=c(18,40),breaks=c(seq(from = 18,to = 40,by = 2)))
    ggsave(filename = mypath,width = 10,height = 8,units = "cm")
  }
}
# draw plots for all accessions + combine with species information to display it
#ori = ggplot(data = m_original_percent,aes(x=range,y = percentage)) + geom_bar(stat="identity") + facet_wrap( ~ accession,nrow=5) 

#trim = ggplot(data = m_trimmed_percent,aes(x=range,y = percentage)) + geom_bar(stat="identity") + facet_wrap( ~ accession,nrow = 5) + scale_x_continuous(breaks=c(0,5,10,15,seq(from = 20,to = 25,by = 1),30,35,40))


# add species to each melted df
#m_original_percent = merge(m_original_percent,accession2species,by.x = "accession")
#m_trimmed_percent = merge(m_trimmed_percent,accession2species,by.x = "accession")
