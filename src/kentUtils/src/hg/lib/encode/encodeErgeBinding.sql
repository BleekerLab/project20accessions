# encodeErgeBinding.sql was originally generated by the autoSql program, which also 
# generated encodeErgeBinding.c and encodeErgeBinding.h.  This creates the database representation of
# an object which can be loaded and saved from RAM in a fairly 
# automatic way.

#ENCODE experimental data from dbERGEII
CREATE TABLE encodeErgeBinding (
    bin int,
    chrom varchar(255) not null,	# Human chromosome
    chromStart int unsigned not null,	# Start position in chromosome
    chromEnd int unsigned not null,	# End position in chromosome
    name varchar(255) not null,	# Name of read - up to 255 characters
    score int unsigned not null,	# Score from 0-1000.  1000 is best
    strand char(1) not null,	# Value should be + or -
    thickStart int unsigned not null,	# Start of where display should be thick (start codon)
    thickEnd int unsigned not null,	# End of where display should be thick (stop codon)
    reserved int unsigned not null,	# Always zero for now
    blockCount int unsigned not null,	# Number of separate blocks (regions without gaps)
    blockSizes longblob not null,	# Comma separated list of block sizes
    chromStarts longblob not null,	# Start position of each block in relative to chromStart
    Id varchar(255) not null,	# dbERGEII Id
    color varchar(255) not null,	# RGB color values
              #Indices
    INDEX(chrom(8),bin),
    UNIQUE(id(10))
#    PRIMARY KEY(chrom)
);
