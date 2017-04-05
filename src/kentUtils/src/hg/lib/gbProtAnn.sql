# gbProtAnn.sql was originally generated by the autoSql program, which also 
# generated gbProtAnn.c and gbProtAnn.h.  This creates the database representation of
# an object which can be loaded and saved from RAM in a fairly 
# automatic way.

#Protein Annotations from GenPept mat_peptide fields
CREATE TABLE gbProtAnn (
    chrom varchar(255) not null,	# chromosome
    chromStart int unsigned not null,	# Start position in chromosome
    chromEnd int unsigned not null,	# End position in chromosome
    name varchar(255) not null,	# Name of item
    product varchar(255) not null,	# Protein product name
    note varchar(255) not null,	# Note (may be empty)
    proteinId varchar(255) not null,	# GenBank protein accession(.version)
    giId int unsigned not null,	# GenBank db_xref number
              #Indices
    PRIMARY KEY(name),
    INDEX(chrom,chromStart)
);
