#
# This is the user-interface definition of a Shiny web application. You can
# run the application by clicking 'Run App' above.
#
# Find out more about building applications with Shiny here:
# 
#    http://shiny.rstudio.com/
#

library(shiny)

shinyUI(fluidPage(
  titlePanel("Thrips survival analysis"),
  
  sidebarLayout(
    sidebarPanel(
      # h3("Choose a data source"),
      # radioButtons("dataSource",label = "Data source",choices = c("Dose"=1,"Genotype"=2)),
      # br(),
      # div("Type the name of the experimental condition you want to compare your results to"),
      # textInput("control",label = "Control condition",value="Mock")
      h3("Load dataset"),
      radioButtons("source","",list("Load sample data"=1,"Upload file"=2)),
      br(),
      
      conditionalPanel(
        condition="input.source == '1'",
        h4("This loads a sample dataset for a dose toxicity assay")
       ),
      conditionalPanel(
        condition="input.source == '2'",
        h4("This allows you to load your own dataset"),
        fileInput("upload","",accept = c("text/csv")),
        h5("Header"),
        checkboxInput("header",label = "Header",value = TRUE),
        radioButtons('sep', 'Separator',
                     c(Tab="\t",
                       Comma=',',
                       Semicolon=';',
                       Space=" "),
                     "\t")
        )
),
    
    mainPanel(
      tabsetPanel(
        tabPanel("About",
                 h3("Welcome to the Shiny app for thrips survival biossays"),
                 tags$ul(
                   tags$li("You can visualise your input data by selecting the",strong("Data input"),"tab"),
                   tags$li("Plots will be generated in the",strong("Plot"),"tab"),
                   tags$li("Statistical tests are available in the",strong("Stats"),"tab")
                 )
          ),
        tabPanel("Data input",dataTableOutput("contents")),
        tabPanel("Plot",plotOutput("plot"),downloadButton("downloadPlots",label = "Download plots as a PDF")),
        tabPanel("Stats",
                 br(),
                 h4("Each condition is compared against the first condition found in the table (e.g. water in the given example)"),
                 downloadButton("statistics.table",label="Download statistical results"),
                 br(),
                 br(),
                 dataTableOutput("summary.table")
                 )
        )
    )
  )
))


