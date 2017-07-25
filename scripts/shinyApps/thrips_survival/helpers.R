# define helper function to plot survival curve
plotSurvival = function(df,confidence=0.95,xmin=0,xmax = 19){
  # calculate survival object
  survObject = with(df,Surv(time = time,event = status))
  # fit model
  fit <- survfit(formula = survObject ~ factor,data = df,conf.int=confidence)
  # plot model
  g <- ggsurvplot(
    fit,
    color = "#2E9FDF",
    risk.table = FALSE,        # show risk table.
    pval = TRUE,              # show p-value of log-rank test.
    conf.int = TRUE,          # show confidence intervals for 
    # point estimaes of survival curves.
    xlim = c(xmin,xmax),           # present narrower X axis, but not affect
    # survival estimates.
    break.time.by = 1,        # break X axis in time intervals by 500.
    ggtheme = theme_bw(),  # customize plot and risk table with a theme.
    risk.table.y.text.col = T,  # colour risk table text annotations.
    risk.table.y.text = FALSE, # show bars instead of names in text annotations in legend of risk table
    font.main = 18,              # title font size
    font.x = 16,                 # font x axis 
    font.y = 16                 # font y axis
  )
  return(g)
}