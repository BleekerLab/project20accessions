#
# This is a Shiny web application. You can run the application by clicking
# the 'Run App' button above.
#
# Find out more about building applications with Shiny here:
#
#    http://shiny.rstudio.com/

library(shiny)
library(dplyr)
library(ggplot2)


######### UI: user interface #######
shinyUI(fluidPage(
  
  # Application title
  titlePanel(title = "mRNA-Seq analysis"),
  
  # title
  h4("Allows basic representation of mRNA-Seq data from different tomato datasets"),
  
  # Side panel
  sidebarLayout(
    sidebarPanel(
      p("Several datasets are available"),
      checkboxGroupInput("dataset",
                         label = h4("Select relevant mRNA-Seq dataset"),
                         choices = list("7 accessions" = 1,"20 accessions" = 2),
                         selected = 2)))
