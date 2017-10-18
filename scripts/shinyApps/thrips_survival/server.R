#
# This is the server logic of a Shiny web application. You can run the 
# application by clicking 'Run App' above.
#
# Find out more about building applications with Shiny here:
# 
#    http://shiny.rstudio.com/
#

##############
# Load library
##############
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
      
      # load an example file
      if(input$source==1){
        df <- read.delim("data/example1_dose.txt",header = T,stringsAsFactors = F)
      }
      
      # load a user defined file
      else if (input$source==2){
        req(input$upload)
        infile <- input$upload
        df <- read.csv(infile$datapath,header=input$header,sep=input$sep,col.names = c("dose","time","status"),stringsAsFactors = F,check.names = F)
        }
    })

    #This previews the data file
    output$contents <- renderDataTable({
      filedata()
    })
    
    ####################################
    ## Make a survival object and plot
    ####################################
    observe({
      # Example file
      if (input$source==1){
        df <- filedata()
        df$dose = factor(x = df$dose,levels = c("water","mock","1ug","10ug","100ug"))
        fit <- with(df,survfit(formula = Surv(time,status) ~ dose,se.fit=T))
        output$plot <- renderPlot({
          gg <- ggsurvplot(fit,conf.int=TRUE,data = df)
          gg <- gg$plot + theme_bw() + facet_wrap(~strata)
          print(gg) 
      })
      }
      # User file
      if (input$source==2){
        req(filedata())
        observe({
          df <- filedata()
          df$dose = factor(x = df$dose,levels = unique(df$dose))
          # this is how the levels were at the beggining
          levs = levels(df$dose)
          output$levels <- renderPrint({levs})
          # re-order the levels so that the selected control condition is at the beggining 
          control.cond <- renderText(input$control)
          reordered.levs = c(input$control,setdiff(levs,input$control))
          output$newlevs = renderPrint({reordered.levs})
          df = droplevels(df)
          levels(df$dose)=reordered.levs
          # creates a survival object
          fit <- with(df,survfit(formula = Surv(time,status) ~ dose,se.fit=T))
          # plot it
          output$plot <- renderPlot({
            gg <- ggsurvplot(fit,conf.int=TRUE,data = df)
            gg <- gg$plot + theme_bw() + facet_wrap(~strata)
            print(gg)
            })
          # download it
          output$downloadPlots <- downloadHandler(
            filename = function() {paste("plots.pdf")},
            content <- function(file){
              pdf(file,width=7,height=5)
              gg <- ggsurvplot(fit,conf.int=TRUE,data = df)
              gg <- gg$plot + theme_bw() + facet_wrap(~strata)
              print(gg)
              dev.off()
            },
            contentType = "application/pdf"
          )
        })
        }
      })

})

