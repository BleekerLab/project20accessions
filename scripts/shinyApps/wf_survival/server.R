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
library(ggplot2,verbose = F,warn.conflicts = F)
library(lme4)
source("helpers.R") # to get helper functions for percentages, plots, etc.

# Define server logic required to draw a histogram
shinyServer(
  function(input, output) {
    ##############
    ### Load data
    ##############
    #This function is responsible for loading in the selected file
    filedata <- reactive({
      
      # load an example file
      if(input$source==1){
        df <- read.delim("data/dose_results.txt",header = T,stringsAsFactors = F,na.strings = "NA")
      }
      
      # load a user defined file
      else if (input$source==2){
        req(input$upload)
        infile <- input$upload
        df <- read.csv(infile$datapath,header=input$header,sep=input$sep,col.names = c("condition","alive","dead"),stringsAsFactors = F,check.names = F,na.strings = "NA")
        if (is.data.frame(df) == FALSE){
          print("please provide a valid dataframe")
        }
        }
    })

    #This previews the data file
    output$contents <- renderDataTable({
      filedata()
    })
    
    ####################################
    ## Make boxplots and computes stats
    ####################################
    observe({
      # Example file
      if (input$source == 1){
        ####### read data
        df <- filedata()
        ####### calculate percentage
        df = calculate_wf_percentage(df,example = T)
        ####### make a plot and sends it to the output
        g <- plot_pct_res(df = df)
        output$plot <- renderPlot({print(g)})
        ######## fit a logistic regression and send stats to output
        summary.fit <- logistic_reg(df)
        output$summary.fit <- renderDataTable({summary.fit})
        output$statistics <- downloadHandler(
          filename = function() {"statistics"},
          content = function(file) {write.table(summary.fit, file, row.names = FALSE,quote = F,sep="\t")}
          )
      }
    })
    
    # observe({
    #   # Example file
    #   if (input$source==1){
    #     df <- filedata()
    #     df$condition = factor(x = df$condition,levels = c("water","mock","1ug","10ug","100ug"))
    #     # remove NAs
    #     df = na.omit(df)
    #     # calculate total number of flies
    #     df$total = rowSums(df[,c("alive","dead")])
    #     # calculate percentage of surviving flies
    #     df$percentage = round(df$alive / df$total *100,digits = 0)
    # 
    #     ################# make the plot ##################
    #     p <- ggplot(data = df,aes(x = condition,y = percentage,fill=condition)) +
    #       geom_boxplot() +
    #       stat_summary(fun.y="mean",geom="point",shape=23,size=2,fill="white") +
    #       theme(
    #         axis.text.x = element_text(angle=0,hjust=1,vjust=1,size = 20),
    #         plot.title = element_text(size=18),
    #         legend.title=element_blank()
    #         ) +
    #       guides(fill=FALSE) +
    #       labs(x = "Dose",y = "Whitefly survival (%)") + 
    #       scale_x_discrete(limits=conditionOrder)
    #     output$plot <- renderPlot({print(p)})
    #     
    #     ################ Statistics ##################
    #     # fit a logistic regression
    #     fit = glm(cbind(dead,total-dead) ~ 1 + condition, data=df, family = binomial(link = logit)) 
    #     # make a nice summary table
    #     summary.fit <- summary(fit)
    #     data = as.data.frame(fit$coefficients)
    #     # get signif codes
    #     signif.codes = as.character(cut(data[,4],breaks = c( -Inf, 0.001, 0.01, 0.05, Inf),labels= c("<0.001", "<0.01", "<0.1", "n.s." )))
    #     # format data values
    #     data[,1] = formatC(data[, 1], digits=3, format = "f")
    #     data[,2] = formatC(data[, 2], digits=3, format = "f")
    #     data[,3] = formatC(data[, 3], digits=3, format = "f")
    #     data[,4] = ifelse(test = data[,4] < 0.001,yes = "< 0.001",no = formatC( data[,4], digits=5, format = "f"))
    #     # add signif codes to data
    #     data$Signif = signif.codes
    #     # remove "dose", add a "condition" column and reorder columns
    #     conditions = gsub("condition","",row.names(data))
    #     data$condition = conditions
    #     data = data[,c("condition","Estimate","Std. Error","z value","Pr(>|z|)","Signif")]
    #     # send it to output
    #     output$summary.table <- renderDataTable({data})
    #     # download stat table
    #     output$statistics.table <- downloadHandler(
    #       filename = function() {"statistics"},
    #       content = function(file) {write.table(data, file, row.names = FALSE,quote = F,sep="\t")}
    #     )
    #   }
    #   
    #   # User file
    #   if (input$source==2){
    #     req(filedata())
    #     observe({
    #       
    #       ############ data preparation ##########
    #       df$condition = factor(x = df$condition,levels = unique(df$condition))
    #       # remove NAs
    #       df = na.omit(df)
    #       # calculate total number of flies
    #       df$total = rowSums(df[,c("alive","dead")])
    #       # calculate percentage of surviving flies
    #       df$percentage = round(df$alive / df$total *100,digits = 0)
    # 
    #       ################## plot ##############
    #       # make the plot
    #       p <- ggplot(data = df,aes(x = condition,y = percentage,fill=condition)) +
    #         geom_boxplot() +
    #         stat_summary(fun.y="mean",geom="point",shape=23,size=2,fill="white") +
    #         theme(
    #           axis.text.y = element_text(size = 16),
    #           axis.text.x = element_text(angle=0,hjust=1,vjust=1,size = 16),
    #           plot.title = element_text(size=18),
    #           legend.title=element_blank()) +
    #         guides(fill=FALSE) +
    #         labs(x = "Condition",y = "Whitefly survival (%)") 
    #       output$plot <- renderPlot({print(p)})
    #     # download it
    #     output$downloadPlots <- downloadHandler(
    #       filename = function() {paste("plots.pdf")},
    #       content <- function(file){
    #         pdf(file,width=7,height=5)
    #         p <- ggsurvplot(fit,conf.int=TRUE,data = df)
    #         gg <- gg$plot + theme_bw() + facet_wrap(~strata)
    #         print(gg)
    #         dev.off()
    #         },
    #         contentType = "application/pdf"
    #       )
    #     
    #     ################ Statistics ##################
    #     # fit a logistic regression
    #     fit = glm(cbind(dead,total-dead) ~ 1 + condition, data=df, family = binomial(link = logit)) 
    #     # make a nice summary table
    #     summary.fit <- summary(fit)
    #     data = as.data.frame(fit$coefficients)
    #     # get signif codes
    #     signif.codes = as.character(cut(data[,4],breaks = c( -Inf, 0.001, 0.01, 0.05, Inf),labels= c("<0.001", "<0.01", "<0.1", "n.s." )))
    #     # format data values
    #     data[,1] = formatC(data[, 1], digits=3, format = "f")
    #     data[,2] = formatC(data[, 2], digits=3, format = "f")
    #     data[,3] = formatC(data[, 3], digits=3, format = "f")
    #     data[,4] = ifelse(test = data[,4] < 0.001,yes = "< 0.001",no = formatC( data[,4], digits=5, format = "f"))
    #     # add signif codes to data
    #     data$Signif = signif.codes
    #     # remove "dose", add a "condition" column and reorder columns
    #     conditions = gsub("condition","",row.names(data))
    #     data$condition = conditions
    #     data = data[,c("condition","Estimate","Std. Error","z value","Pr(>|z|)","Signif")]
    #     # send it to output
    #     output$summary.table <- renderDataTable({data})
    #     # download stat table
    #     output$statistics.table <- downloadHandler(
    #       filename = function() {"statistics"},
    #       content = function(file) {write.table(data, file, row.names = FALSE,quote = F,sep="\t")}
    #     )
    #     })
    #   }

  }
)


