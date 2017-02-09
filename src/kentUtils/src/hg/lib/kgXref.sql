# kgXref.sql was originally generated by the autoSql program, which also 
# generated kgXref.c and kgXref.h.  This creates the database representation of
# an object which can be loaded and saved from RAM in a fairly 
# automatic way.

#Link together a Known Gene ID and a gene alias
CREATE TABLE kgXref (
    kgID varchar(255) not null,	# Known Gene ID
    mRNA varchar(255) not null,	# mRNA ID
    spID varchar(255) not null,	# UniProt protein Accession number
    spDisplayID varchar(255) not null,	# UniProt display ID
    geneSymbol varchar(255) not null,	# Gene Symbol
    refseq varchar(255) not null,	# RefSeq ID
    protAcc varchar(255) not null,	# NCBI protein Accession number
    description longblob not null,	# Description
    rfamAcc varchar(255) not null,	# Rfam accession number
    tRnaName varchar(255) not null,	# Name from the tRNA track
              #Indices
    KEY(kgID),
    KEY(mRNA),
    KEY(spID),
    KEY(spDisplayID),
    KEY(geneSymbol),
    KEY(refseq),
    KEY(protAcc),
    KEY(rfamAcc),
    KEY(tRnaName)
);
