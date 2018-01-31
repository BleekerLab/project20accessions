import os
import gzip

def get_fastq_basename(myfastqfile):
    """
    get the basename of the fastq file without its full path and fastq extension		
    [Example] my_sample.fastq then it will extract "my_sample"
    """
    if myfastqfile.endswith(".fq"):
        basename = myfastqfile.split(".fq")[0]
    elif myfastqfile.endswith(".fastq"):
        myfastqfile.split(".fastq")[0] 
    elif myfastqfile.endswith(".fq.gz"):
        basename = myfastqfile.split(".fq.gz")[0]
    elif myfastqfile.endswith(".fastq.gz"):
        basename = myfastqfile.split(".fastq.gz")[0] 
    else:
        print("please specify a correct fastq file ending with .fq, .fastq or compressed such as .fq.gz or .fastq.gz")
    basename_wo_full_path = os.path.basename(basename)
    return basename_wo_full_path

def generate_read_group_id(myfastqfile):
    """
    generate a read group ID (instrument + run_id + flowcell_id) from a fastq file
    """  
    if myfastqfile.endswith((".fastq",".fq")):
        with open(myfastqfile,"r") as f:
            first_line = f.readline()
            read_group_id = first_line.split(":")[0] + ":" + first_line.split(":")[1] + ":" + first_line.split(":")[2]
    elif myfastqfile.endswith(".gz"):
        with gzip.open(myfastqfile,mode='rt') as f:
            first_line = f.readline()
            read_group_id = first_line.split(":")[0] + ":" + first_line.split(":")[1] + ":" + first_line.split(":")[2]
    return read_group_id

if __name__ == '__main__':
    main()
