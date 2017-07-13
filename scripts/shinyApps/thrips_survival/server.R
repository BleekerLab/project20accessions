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
  ############# load data ###############################
    #This function is responsible for loading in the selected file
    filedata <- reactive({
      if(input$source==1){
        df <- read.delim("data/example1_dose.txt",header = T,stringsAsFactors = F)
      }
      else if(input$source==2){
        infile <- input$upload
        if (is.null(infile)) {
        # User has not uploaded a file yet
        return(NULL)
        }
      read.csv(infile$datapath,header=input$header,sep=input$sep)
      }
    })

    #This previews the data file
    output$contents <- renderTable({
      filedata()
    })
    
    

    ######### make a survival object #################
    
    # example with dose assay
    observe({
      if(input$source==1){
        fit <- with(filedata(),survfit(formula = Surv(time,status) ~ dose,se.fit=T))
        output$plot <- renderPlot({
          gg <- ggsurvplot(fit,conf.int=TRUE,data = filedata())
          gg <- gg$plot + theme_bw() + facet_wrap(~strata)
          print(gg)
        })
        }
      })
    # if(input$source==1){
    #   fit <- with(filedata,survfit(formula = Surv(time,status) ~ dose,se.fit=T))
    #   output$plot <- renderPlot({
    #     gg <- ggsurvplot(fit,conf.int=TRUE,data = dataM)
    #     gg <- gg$plot + theme_bw() + facet_wrap(~strata)
    #     print(gg)
    #     })
    #   }

    
    ######### plots ############
    # output$plot <- renderPlot({
    #   gg <- ggsurvplot(fit,conf.int=TRUE,data = dataM)
    #   gg <- gg$plot + theme_bw() + facet_wrap(~strata)
    #   print(gg)
    # })
    
  
  #colnames(data) = c("factor","time","status")
  
  ######## Kaplan-Meier survival curves ###########
  # import helper function
  #source("helpers.R")

})


