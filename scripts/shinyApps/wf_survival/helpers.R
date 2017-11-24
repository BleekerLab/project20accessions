# helper functions
calculate_wf_percentage = function(df,example=TRUE){
  # rename columns
  colnames(df) = c("condition","alive","dead")
  if (example == TRUE){
    df$condition = factor(x = df$condition,levels = c("water","mock","1ug","10ug","100ug"))
  } 
  else {
    df$condition = factor(x = df$condition,levels = unique(df$condition))
  }
  # remove NAs
  df = na.omit(df)
  # calculate total number of flies
  df$total = rowSums(df[,c("alive","dead")])
  # calculate percentage of surviving flies
  df$percentage = round(df$alive / df$total *100,digits = 0)
  # return the modified df
  return(df)
}

# plot function
plot_pct_res = function(df,fontsize.x=20,fontsize.y=20,legend=T,guide.choice=F,lab.x="Dose",lab.y="Whitefly survival (%)"){
  localenv <- environment()
  # plot
  p <- ggplot(data = df,aes(x = condition,y = percentage,fill=condition)) +
    geom_boxplot() +
    stat_summary(fun.y="mean",geom="point",shape=23,size=2,fill="white") +
    theme(
      axis.text.x = element_text(angle=0,hjust=1,vjust=1,size = 10),
      axis.text.y = element_text(size = fontsize.y),
      plot.title = element_text(size=18),
      legend.title=element_blank()) +
    guides(fill=guide.choice) +
    labs(x = lab.x,y = lab.y) 
  # return the plot
  return(p)
}

# logistic regression function
logistic_reg <- function(df){
  # computes fit
  fit = glm(cbind(dead,total-dead) ~ 1 + condition, data=df, family = binomial(link = logit)) 
  # makes a nice summary table
  summary.fit <- summary(fit)
  fit.table = as.data.frame(coef(summary(fit)))
  # get signif codes
  signif.codes = as.character(cut(fit.table[,4],breaks = c( -Inf, 0.001, 0.01, 0.05, Inf),labels= c("<0.001", "<0.01", "<0.1", "n.s." )))
  # format data values
  fit.table[,1] = formatC(fit.table[, 1], digits=3, format = "f")
  fit.table[,2] = formatC(fit.table[, 2], digits=3, format = "f")
  fit.table[,3] = formatC(fit.table[, 3], digits=3, format = "f")
  fit.table[,4] = ifelse(test = fit.table[,4] < 0.001,yes = "< 0.001",no = formatC(fit.table[,4], digits=5, format = "f"))
  # add signif codes to data
  fit.table$signif = signif.codes
  # remove "dose", add a "condition" column and reorder columns
  conditions = gsub("condition","",row.names(fit.table))
  row.names(fit.table) <- NULL
  fit.table$condition = conditions
  fit.table = fit.table[,c("condition","Estimate","Std. Error","z value","Pr(>|z|)","signif")]
  return(fit.table)
}

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

