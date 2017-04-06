# For random forest

This repository contains resources to perform a so-called __Random Forest__ analysis to find features (genes, metabolites) related to phenotypic classes (resistant, sensitive). 

Data can come from averages of biological replicates but it is also possible to link phenotype to features for each individual plant for instance. 

# Usage

1.  To perform the analysis, use the `<randomforest.R>` script. 
2.  Open a new shell window and type `<Rscript --vanilla  randomforest.R --phenotype myphenotypedata.txt --features myfeaturesdata.txt>`

 takes several arguments:

## randomforest.R script arguments 

### Input files

*  `<--phenotype>` a tabulated file containing two columns: sample identifiers (id) and phenotypic classes for the samples. 
*  `<--features>`  a tabulated file containing 

Important: both files should have a column with the same ids. 


__Phenotypic data__ should have the following format (name of the columns do not matter, order does!)

id | class  
--------- | ------
C32       | Sensitive     
LA2172    | Sensitive     
LA2133    | Sensitive       
LA4024    | Sensitive   
PI127826  | Resistant  
LA0716    | Resistant     

__Features data__ should have the following format (name of the columns do not matter, order does!)
In this table, you will find 

id | feature1 | feature2 | feature3 
--------- | ------ | ------| -----
C32       | 10 | 20 | 0    
LA2172    | 0   | 15 | 
LA2133    | 125  | 16 | 47     
LA4024    | 407 | 15 | 16
PI127826  | 525  | 3 | 0
LA0716    | 402   | 15 | 1

### Parameters (to be implemented)
*  <`--ntrees>` number of trees to be built
*  <`--pvals`>  p-value threshold (0.05 for instance)
*  <`--perm`>   number of permutations (to calculate p-values)
