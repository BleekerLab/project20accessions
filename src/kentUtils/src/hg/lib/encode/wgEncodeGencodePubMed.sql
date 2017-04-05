# wgEncodeGencodePubMed.sql was originally generated by the autoSql program, which also 
# generated wgEncodeGencodePubMed.c and wgEncodeGencodePubMed.h.  This creates the database representation of
# an object which can be loaded and saved from RAM in a fairly 
# automatic way.

#Gencode metadata table of PubMed identifier of published experimental data associated with Gencode Genes
CREATE TABLE wgEncodeGencodePubMed (
    transcriptId varchar(255) not null,	# GENCODE transcript identifier
    pubMedId int not null,	# PubMed identifier of supporting literature
              #Indices
    index(transcriptId)
);
