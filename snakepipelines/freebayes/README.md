# Variant calling pipeline based on freebayes

This Snakemake pipeline will generate a Variant Calling Format file (VCF) of SNPs and small InDels detected from Illumina paired-end DNA-Seq reads. 

# Step by step
1. QC and trim DNA-Seq paired-end Illumina sequencing reads (using fastqc and trimmomatic)
2. Align them to a reference genome (using bwa mem)
3. Calls variants (using freebayes)
