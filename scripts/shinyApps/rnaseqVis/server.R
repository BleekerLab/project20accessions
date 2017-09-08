# server

# load libraries
library(shiny)
library(ggplot2)
library(dplyr)
library(data.table)

# load data
df <- fread("data/kallisto_normalized_counts.txt",sep = "\t",header = T)

# what is your gene of interest? Filter that gene only

shinyServer(function(input,output){
  # One gene
  observe({
    if(input$source==1){
      filtered.df = dplyr::filter(df,gene == input$gene)
      }
    # Multiple genes
    if(input$source==2){
      if(is.null(input$mygenes)) {return(NULL)} # no data yet
      mygenes = input$mygenes
      filtered.df = dplyr::filter(df,df[,"gene"] %in% mygenes)
      }  
  #This previews the data file
    output$contents <- renderDataTable({
      filtered.df
      })
  
  # plot
  observe({
    #If only one gene to plot
    if(input$source==1){
      output$genePlot <- renderPlot({
        ggplot(data = filtered.df,aes(x = accession,y=value)) +
          geom_boxplot() +
          ggtitle(input$gene) +
          labs(x = "Accession",y = "Normalized expression (counts)") +
          theme(axis.text.x = element_text(angle=40,hjust=1))
      })
    }
  })
  #   if(input$source==2){
  #     
  #   }
    })
})

