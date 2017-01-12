# bioassays
A collection of R scripts (R Markdown) to output plots and statistics on bioassays (whitefly survival, thrips)


## Thrips
The Rmarkdown `survival.Rmd`script takes two input arguments:
1.  A table containing the survival data in the format

accession | time | status 
--------- | ------| -----
C32       | 5     | 0    
C32       | 6     | 1    
C32       | 8     | 1    
C32       | 7     | 1     
LA0716    | 1     | 1  
LA0716    | 2     | 0  
LA0716    | 1     | 1    

__accession__: name of the genotype
__time__: time to event (death of the thrips)
__status__: 
*  0 if censored (alive at end of experiment or missing)
*  1 if event occured (death of the thrips)

2. A directory name to store all results (e.g. "results").

The script can be executed with rmarkdown::render function
`rmarkdown::render("survival.Rmd",params=list(data="path/to/data"txt",resdir="results")`
