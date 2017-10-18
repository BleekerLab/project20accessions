# server

# load libraries
library(shiny)
library(ggplot2)
library(dplyr)

# load data
df <- read.delim("data/kallisto_normalized_counts.txt",sep = "\t",header = T)

# what is your gene of interest? Filter data with that gene only. Alternatively n genes

shinyServer(function(input,output){
  # One gene
  dataFrame <- reactive({
    if(input$source==1){
      filtered.df = dplyr::filter(df,gene == input$gene)
      }
    # Multiple genes
    if(input$source==2){
      # no data yet
      if(is.null(input$mygenes)) {
        return(NULL)
        }
      mygenes = input$mygenes
      # convert input to a simple vector
      mygenes = unlist(strsplit(mygenes,","))
      filtered.df = dplyr::filter(df,df[,"gene"] %in% mygenes)
    }
    return(filtered.df)
  })
  
  #This previews the data file
  output$contents <- renderDataTable({
    dataFrame()
  })

  # plot
  observe({
    #If only one gene to plot
    if(input$source==1){
      output$genePlot <- renderPlot({
        ggplot(data = dataFrame(),aes(x = accession,y=value)) +
          geom_boxplot() +
          ggtitle(input$gene) +
          labs(x = "Accession",y = "Normalized expression (counts)") +
          theme(axis.text.x = element_text(angle=40,hjust=1))

      })
    }
    #If n genes
    if(input$source==2){
      # # scale choice for the faceting
      # if (input$scale==1){
      #   my_scale_choice == "free"
      # }
      # if (input$scale==2){
      #   my_scale_choice == "fixed"
      # }
      # make plot  
      output$genePlot <- renderPlot({
        # choice for scale
        my_scale_choice = switch(input$scale,'1'="free",'2'="fixed")
        # plot
        ggplot(data = dataFrame(),aes(x = accession,y=value)) +
          geom_boxplot() +
          facet_wrap( ~ gene,scales = my_scale_choice) +
          labs(x = "Accession",y = "Normalized expression (counts)") +
          theme(axis.text.x = element_text(angle=40,hjust=1))
      })
      }
    })
})

