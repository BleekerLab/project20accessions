# load library
library(shiny)

# Define UI for application that draws a histogram
shinyUI(fluidPage(
  
  # Application title
  titlePanel("RNA-Seq application!"),
  
  # Sidebar with a slider input for the number of bins
  sidebarLayout(
    sidebarPanel(
      h3("What do you prefer? One gene or multiple genes?"),
      radioButtons("source","",list("One gene"=1,"Multiple genes"=2),selected = 1),
      br(),
      
      conditionalPanel(
        condition="input.source == '1'","This loads one plot for one gene",
        textInput("gene",label= h4("Enter your favorite gene here"),value = "Solyc01g008670")),
      
      conditionalPanel(
        condition="input.source=='2'",
        h3("Paste a list of Solyc numbers (Solyc01g008650) separated by commas"),
        textInput("mygenes",label = "My genes of interest",value = "Solyc01g008650,Solyc01g008670",width='400px'),
        actionButton('clearText_button','Clear data')
    )),
    
    # Show plots and data
    mainPanel(
      tabsetPanel(
        tabPanel("Plots",plotOutput("genePlot")),
        tabPanel("Data input",dataTableOutput("contents"))
    )
  )
)))