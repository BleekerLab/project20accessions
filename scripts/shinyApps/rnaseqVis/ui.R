# load library
library(shiny)

# Define UI for application that draws a histogram
shinyUI(fluidPage(
  
  # Application title
  titlePanel("RNA-Seq application!"),
  
  # Sidebar with a slider input for the number of bins
  sidebarLayout(
    sidebarPanel(
      textInput("gene",label= h4("Enter your favorite gene here"),value = "Solyc01g008670")
    ),
    
    # Show a plot of the generated distribution
    mainPanel(
      plotOutput("genePlot")
    )
  )
))