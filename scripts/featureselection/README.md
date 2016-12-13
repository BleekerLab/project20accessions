# feature_selection
A collection of R scripts (R Markdown) to select interesting features (e.g. transcripts, metabolites) related to a response (e.g. whitefly survival)

## For random forest

For now, phenotypic data from whitefly no-choice experiments (survival after X days) and thrips survival (life expectancy) can be
imported.

Phenotypic data for whitefly have to comply with the following format. 

accession | plant | cage | alive | total | percentage
--------- | ------| -----|-------|-------|-----------
C32       | 1     | A    | 11    | 4     | 73
C32       | 1     | B    | 14    | 2     | 88
C32       | 2     | A    | 14    | 1     | 93
C32       | 2     | B    | 13    | 1     | 93 
LA0716    | 1     | A    | 0     | 11    | 0



## For WGCNA (weighted gene correlation network analysis)

