# server

# load libraries
library(shiny)
library(ggplot2)
library(dplyr)

# load data
df <- read.delim("data/kallisto_normalized_counts.txt")

# what is your gene of interest? Filter that gene only

shinyServer(function(input,output){
  
  # plot
  output$genePlot <- renderPlot({
    # filter df
    filtered.df = dplyr::filter(df,gene == input$gene)
    
    # plot
    ggplot(data = filtered.df,aes(x = accession,y=value)) +
      geom_boxplot() +
      ggtitle(input$gene) +
      labs(x = "Accession",y = "Normalized expression (counts)") +
      theme(axis.text.x = element_text(angle=40,hjust=1))
  })
})

