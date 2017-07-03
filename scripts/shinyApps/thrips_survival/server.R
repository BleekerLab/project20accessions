#
# This is the server logic of a Shiny web application. You can run the 
# application by clicking 'Run App' above.
#
# Find out more about building applications with Shiny here:
# 
#    http://shiny.rstudio.com/
#

library(shiny)
library(optparse)
library(dplyr,quietly = TRUE,warn.conflicts = F,verbose = F)
library(survminer)
library(survival)
library(ggplot2,verbose = F,warn.conflicts = F)


# Define server logic required to draw a histogram
shinyServer(
  function(input, output) {
    ########## load data ###############################
    dataM <- read.delim("data/example1_dose.txt",header=TRUE,stringsAsFactors = TRUE)
    dataM = na.omit(dataM)
    
    ######### make a survival object #################
    fit <- with(dataM,survfit(formula = Surv(time,status) ~ dose,se.fit=T))
    
    output$mydata <- renderDataTable({
      dataM
    })
    
    ######### plots ############
    output$plot <- renderPlot({
      gg <- ggsurvplot(fit,conf.int=TRUE,data = dataM)
      gg <- gg$plot + theme_bw() + facet_wrap(~strata)
      print(gg)
    })
    
  
  #colnames(data) = c("factor","time","status")
  
  ######## Kaplan-Meier survival curves ###########
  # import helper function
  source("helpers.R")


########### Load data ####################
# dataM <- reactive({
#   
#   # if choice == 1 then load sample datasets
#   if(input$dataInput==1){
#     if(input$sampleData==1){
#       data<-read.delim("data/example1_dose.txt",header=TRUE,stringsAsFactors = TRUE)			
#     } else {
#       data<-read.table("data/example2_genotype.txt",header=TRUE,stringsAsFactors = TRUE)		
#     }
#   
#   # if choice == 2 then upload the user file
#   } else if(input$dataInput==2){
#     inFile <- input$upload
#     # Avoid error message while file is not uploaded yet
#     if (is.null(input$upload))  {return(NULL)}
#     # Get the separator
#     mySep <- switch(input$fileSepDF, '1'=",",'2'="\t") #list("Comma"=1,"Tab"=2)
#     myNA <- input$na
#     data<-read.table(inFile$datapath, sep=mySep, header=TRUE,stringsAsFactors = T,na.strings = myNA)
#   }
#   return(data)
# })

})

