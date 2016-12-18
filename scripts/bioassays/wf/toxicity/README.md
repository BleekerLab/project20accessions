# Toxicity assay

To run the `wf_toxicity_assay.Rmd`, you have two choices in RStudio:
*  __Using the Knit command__ 
First, you change the working directory using `setwd()` to the directory of the script `wf_toxicity_assay.Rmd`. 
Make sure the `dataFile` and the `resultDir` are properly set (pointing to the result datafile) and the desired output directory.
* __Using the ezknitr package__
The package is available on Github [here](https://github.com/ropenscilabs/ezknitr). Follow instructions to install.
In the RStudio console, type `ezknit("path/to/wf_toxicity_assay.Rmd",out_dir = "/desired/output/directory/")