#####################################
## Useful functions for Random Forest
#####################################

# replace.negatives.by.zeros
# takes a vector of numeric values and return the same without negatives
replace.negative.by.zeros <- function(x) {
  sapply(x,function(y) {
      if (y < 0) {
        y = 0
      } else {
        y = y
      }
    })
}

# Load Rdata into a new environment to stop messing up the current environment!
LoadToEnvironment <- function(RData, env = new.env()){
  load(RData, env)
  return(env) 
}