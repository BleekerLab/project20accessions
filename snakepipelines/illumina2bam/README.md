# illumina2bam Snakemake pipeline 
This pipeline performs trimming, mapping of mRNA-Seq Illumina paired-end reads on the human genome. It outputs BAM alignment files that can be displayed on a genome browser.

# How to use it

## Install all softwares and packages needed with the [Conda package manager](https://conda.io/docs/using/envs.html)

### Create a virtual environment named "myrnaseqworkflow" from the `environment.yaml` file
conda env create --name illumina2bam --file environment.yaml

### Activate this virtual environment
source activate illumina2bam

### execute the workflow (here dry run with the -n option)
snakemake -np
 
# Main outputs:
*   Mapping statistics ("logs") for each sample
*   Indexed alignment files (.bam and .bai) 

# config.yaml
This file is used to customize the analysis. 

## Directories:
*  fastqdir: this is the directory that contains the mRNA-Seq fastq files
*  workdir: this is the directory that will contain all intermediate files (can be cleaned up after analysis)
*  resultdir: this is where you want to store all desired outputs.

## Genomic references, annotations and aligner indexes
refs:
* genome: [path/to/genomic fasta file]
* gff: [path/to/gff]
* chromsizes: [path/to/chromosome lengths]
* star: [path/to/STAR index]

## samples
Provide a list of samples
samples:
  LA1777:
    forward:  "LA1777_GCCAAT_L008_R1_001.fastq.gz"
    reverse:  "LA1777_GCCAAT_L008_R2_001.fastq.gz"
  PI127826:
    forward:  "PI127826_CGATGT_L008_R1_001.fastq.gz"
    reverse:  "PI127826_CGATGT_L008_R2_001.fastq.gz"
  F1:
    forward:  "F1cross_TGACCA_L008_R1_001.fastq.gz"
    reverse:  "F1cross_TGACCA_L008_R1_001.fastq.gz"
etc.   

## Parameters for softwares used
Trimmomatic (trimming and quality check)
STAR (mapping)

