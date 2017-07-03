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
      h3("Choose a data source"),
      radioButtons("dataInput",label = "Data source",choices = c("Example1 - dose" = 1,"Example2 - genotype"=2))
      
      
      ),
    
    mainPanel(
      tabsetPanel(
        tabPanel("Data input",dataTableOutput("mydata")),
        tabPanel("Plot",plotOutput("plot"))
      )
    )
  )
))



# # Define UI for application that draws a histogram
# shinyUI(fluidPage(
#   
#   # Application title
#   titlePanel("Survival data analysis"),
#   
#   # Sidebar with a slider input for number of bins 
#   sidebarLayout(
#     sidebarPanel(
#       h3("Enter survival dataset"),
#       br(),
#       radioButtons("data",label="Choose a data source",choices=c("Load example dataset" = 1,"Upload delimited text file" = 2)),
#       
#       conditionalPanel(condition="input.data=='1'",
#                        h5("Load example dataset:"),
#                        radioButtons("sampleData",label= NULL, choices=c("Example 1: toxicity assay (dose effect)"=1,"Example 2: genotype assay"=2))
#       ),
#       br(),
#       conditionalPanel(condition="input.data=='2'",
#                        h5("Upload delimited text file: "),
#                        fileInput("upload", "", multiple = FALSE),
#                        radioButtons("fileSepDF",label = "Delimiter:", list("Comma"=1,"Tab"=2)),
#                        textInput(inputId = "na",label = h5("indicate here your code for missing values. NA by default"),value="NA"),
#                        p("Delimited text files can be separated by comma or tab"),
#                        br(),
#                        p("For example, Excel data can be exported in .csv (comma separated) or .tab (tab separated) format.")
#                        )),
#     # Show a plot of the generated distribution
#     mainPanel(
#       h3("Help text"),
#       helpText("Note: help text isn't a true widget but it provides an easy way to add text to accompany other widgets"),
#       #dataTableOutput("filetable")
#       dataTableOutput("mydata")
#     )
#     )
# ))
