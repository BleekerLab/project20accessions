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
        # creates a Survival class object
        fit <- with(df,survfit(formula = Surv(time,status) ~ dose,se.fit=T))
        # fit a Cox Proportional Hazards model
        fitCox = coxph(formula = Surv(time,status) ~ dose,data = df)
        
        # build a summary and print it
        fm <- as.character(fitCox$call)[2]
        # make a nice summary table
        summary.fit <- summary(fitCox)
        data = as.data.frame(summary.fit$coefficients)
        # get signif codes
        signif.codes = as.character(cut(data[,5],breaks = c( -Inf, 0.001, 0.01, 0.05, Inf),labels= c("<0.001", "<0.01", "<0.1", "n.s." )))
        # format data values
        data[,1] = formatC(data[, 1], digits=3, format = "f")
        data[,2] = formatC(data[, 2], digits=3, format = "f")
        data[,3] = formatC(data[, 3], digits=3, format = "f")
        data[,4] = ifelse(test = data[,4] < 0.001,yes = "< 0.001",no = formatC( data[,4], digits=5, format = "f"))
        # add signif codes to data
        data$Signif = signif.codes
        # remove "dose", add a "condition" column and reorder columns
        conditions = gsub("dose","",row.names(data))
        data$condition = conditions
        data = data[,c("condition","coef","exp(coef)","se(coef)","z","Pr(>|z|)","Signif")]
        
        # send it to output
        output$summary.table <- renderDataTable({data})
        
        # makes a plot
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
          # to order the plots
          df$dose = factor(x = df$dose,levels = unique(df$dose))
          # creates a survival object
          fit <- with(df,survfit(formula = Surv(time,status) ~ dose,se.fit=T))
          # fit a Cox Proportional Hazards model
          fitCox = coxph(formula = Surv(time,status) ~ dose,data = df)
          
          # build a summary and print it
          fm <- as.character(fitCox$call)[2]
          # make a nice summary table
          summary.fit <- summary(fitCox)
          data = as.data.frame(summary.fit$coefficients)
          # get signif codes
          signif.codes = as.character(cut(data[,5],breaks = c( -Inf, 0.001, 0.01, 0.05, Inf),labels= c("<0.001", "<0.01", "<0.1", "n.s." )))
          # format data values
          data[,1] = formatC(data[, 1], digits=3, format = "f")
          data[,2] = formatC(data[, 2], digits=3, format = "f")
          data[,3] = formatC(data[, 3], digits=3, format = "f")
          data[,4] = ifelse(test = data[,4] < 0.001,yes = "< 0.001",no = formatC( data[,4], digits=5, format = "f"))
          # add signif codes to data
          data$Signif = signif.codes
          # remove "dose", add a "condition" column and reorder columns
          conditions = gsub("dose","",row.names(data))
          data$condition = conditions
          data = data[,c("condition","coef","exp(coef)","se(coef)","z","Pr(>|z|)","Signif")]
          
          # send it to output
          output$summary.table <- renderDataTable({data})
          # rename strata for ploting (removes prefix)
          newNames = sub("dose=","",names(fit$strata))
          names(fit$strata) = newNames
          
          # download stat table
          output$statistics.table <- downloadHandler(
            filename = function() {"statistics"},
            content = function(file) {write.table(data, file, row.names = FALSE,quote = F,sep="\t")}
          )
          ################## plot it
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

