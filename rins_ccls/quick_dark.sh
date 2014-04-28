#!/bin/sh -x
#
#	with the -x the commands are sent to STDERR before execution
#
#	bowtie output goes to stderr for some reason
#	probably because the SAM file usually goes to stdout
#	so, wrap everything in curly braces and direct both
#	to files.
#
#	Explicit redirection within the block will override this
#


if [ $# -eq 0 ]; then
	echo
	echo "Usage:"
	echo
	echo "`basename $0` raw.1.fastq raw.2.fastq"
	echo
	echo "Example:"
	echo
	exit
fi

{
echo "Starting at ..."
date

if [ $# -eq 2 ] ; then
	ln -s $1 raw.1.fastq
	ln -s $2 raw.2.fastq
fi
#	else ...
#	I expect the existance of raw.1.fastq and raw.2.fastq
#

#indexes=/Volumes/cube/working/indexes
#	leading with the ": " stops execution
#	just ${BOWTIE2_INDEXES:"/Volumes/cube/working/indexes"}
#	would try to execute the result.  I just want the OR/EQUALS feature
: ${BOWTIE2_INDEXES:="/Volumes/cube/working/indexes"}
: ${BLASTDB:="/Volumes/cube/working/indexes"}

#	they MUST be exported, apparently, to be picked up by bowtie2
export BOWTIE2_INDEXES
export BLASTDB

#bowtie2
#-x <bt2-idx> The basename of the index for the reference genome. The basename is the name of any of the index files up to but not including the final .1.bt2 / .rev.1.bt2 / etc. bowtie2 looks for the specified index first in the current directory, then in the directory specified in the BOWTIE2_INDEXES environment variable.

#	blastn
#$BLASTDB - This is the variable which points to the Blast Database. This directory should contain the databases that you would want to search. BLAST by default checks this location and the current working directory for the presence of the databases. This variable is set during login by system login scripts , and may be changed by the user to point to her preferred location in her startup scripts. 

bowtie2="bowtie2 -N 1 -q -S /dev/null --threads 4"

#
#	Try to super simplify the bowtie stuff like so ....
#
dbs="hg18 hg19 Blast1 Blast2,2 Homo_sapiens.GRCh37.69.cdna.all,Homo
	nt_human_1 nt_human_2,2 nt_human_3,3
	human_genomic_01
	human_genomic_02,02
	human_genomic_03,03
	human_genomic_04,04
	human_genomic_05,05
	human_genomic_06,06
	human_genomic_07,07
	human_genomic_08,08
	human_genomic_09,09
	human_genomic_10,10
	human_genomic_11,11
	human_genomic_12,12
	human_genomic_13,13"

ifile='raw.1.fastq,raw.2'	#	yes, this works
ofile='raw_not'
for db in $dbs; do
	#	If contains comma (nt_human_2,2), split it.  If not (hg18), db and suffix will be the same.
	suffix=${db##*,}	#	2
	db=${db%%,*}			#	nt_human_2
	ofile=${ofile}_$suffix
	$bowtie2 -x $db -U $ifile.fastq --un $ofile.fastq
	ifile=$ofile
	date
done


ln -s $ofile.fastq raw_non_human.fastq


#
#	On genepi/n0, had some failure
#
#CMD: /my/home/jwendt/dna/trinityrnaseq_r2013-02-25/trinity-plugins/parafly/bin/ParaFly -c /my/home/jwendt/dna/output/fallon_715723_filtered/trinity_output_single/chrysalis/butterfly_commands.adj -shuffle -CPU 2 -failed_cmds failed_butterfly_commands.20633.txt -v 
#Number of  Commands: 3057
#Error occurred during initialization of VM
#Could not reserve enough space for object heap
#Error: Could not create the Java Virtual Machine.
#Error: A fatal exception has occurred. Program will exit.
#
#	Adding --bflyHeapSpaceMax 5G to Trinity.pl call seems to fix
#
#	adding --min_contig_length 100 in attempt to get ALL input reads in the output
#

date
echo "de novo assembly of single 'unpaired' non-human using Trinity"
Trinity.pl --seqType fq --bflyHeapSpaceMax 5G --JM 2G \
	--min_contig_length 100 \
	--single raw_non_human.fastq \
	--output trinity_output_single
date

cp trinity_output_single/single.fa trinity_input_single.fasta

cp trinity_output_single/Trinity.fasta trinity_non_human_single.fasta

echo "Laning composite fasta file."
bioruby_lane_fasta.rb trinity_input_single.fasta
#	=> trinity_input_single_1.fasta, trinity_input_single_2.fasta

mv trinity_input_single_1.fasta trinity_input_paired_1.fasta
mv trinity_input_single_2.fasta trinity_input_paired_2.fasta

echo "de novo assembly of re-paired non-human using Trinity"
Trinity.pl --seqType fa --bflyHeapSpaceMax 5G --JM 2G \
	--min_contig_length 100 \
	--left  trinity_input_paired_1.fasta \
	--right trinity_input_paired_2.fasta \
	--output trinity_output_paired
date

#
#	We are no longer keeping trinity_input_paired related files
#
#	cp trinity_output_paired/both.fa trinity_input_paired.fasta

cp trinity_output_paired/Trinity.fasta trinity_non_human_paired.fasta


echo "Removing duplicate reads from fasta files to speed up blasting."

#bioruby_extract_uniq_sequences_from_fasta.rb trinity_input_single.fasta
#	=> trinity_input_single.uniq.fasta
#	using fastx_collapser instead.  Better on memory and faster.
#	Also adds read count
#	http://hannonlab.cshl.edu/fastx_toolkit/
#	This will completely rename the reads so will lose lane info etc.
fastx_collapser -i trinity_input_single.fasta -o trinity_input_single.uniq.fasta






#
#	We are no longer keeping trinity_input_paired related files
#
#bioruby_extract_uniq_sequences_from_fasta.rb trinity_input_paired.fasta
#	=> trinity_input_paired.uniq.fasta


#	even 10000 processes quite fast
echo "Spliting fasta files into 20000 read fasta files and queueing for blasting to viral genomic"
date
ec_fasta_split_and_blastn.sh -m 20000 --dbs viral_genomic --options "-task blastn" trinity_non_human_single.fasta
date
ec_fasta_split_and_blastn.sh -m 20000 --dbs viral_genomic --options "-task blastn" trinity_non_human_paired.fasta
date
ec_fasta_split_and_blastn.sh -m 20000 --dbs viral_genomic --options "-task blastn" trinity_input_single.uniq.fasta

#	Defaults are -m 1000 and --dbs nt
echo "Spliting fasta files into 2000 read fasta files and queueing for blasting to nt"
date
ec_fasta_split_and_blastn.sh -m 2000 trinity_non_human_single.fasta
date
ec_fasta_split_and_blastn.sh -m 2000 trinity_non_human_paired.fasta
date
ec_fasta_split_and_blastn.sh -m 2000 trinity_input_single.uniq.fasta



#
#	We are no longer keeping trinity_input_paired related files
#
#ec_fasta_split_and_blastn.sh trinity_input_paired.uniq.fasta


echo "Finished at ..."
date

#} 1>>quick_dark.out 2>>quick_dark.err
} 1>>quick_dark.out 2>&1
