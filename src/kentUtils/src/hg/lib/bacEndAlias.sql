# bacEndAlias.sql was originally generated by the autoSql program, which also 
# generated bacEndAlias.c and bacEndAlias.h.  This creates the database representation of
# an object which can be loaded and saved from RAM in a fairly 
# automatic way.

#BAC ends aliases and associated identification numbers
CREATE TABLE bacEndAlias (
    alias varchar(255) not null,	# BAC end read name
    identNo int unsigned not null,	# Identification number of BAC End
    acc varchar(255) not null,	# GenBank accession for the BAC End
              #Indices
    PRIMARY KEY(alias),
    INDEX(identNo)
);
