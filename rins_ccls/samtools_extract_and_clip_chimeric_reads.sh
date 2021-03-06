#!/usr/bin/env bash

function usage(){
	echo
	echo "Usage:"
	echo
	echo "`basename $0` [-q] <samfile(s) or bamfile(s)>"
	echo
	echo "Example:"
	echo "  `basename $0` /my/path/*bam"
	echo
	echo "Assuming ..."
	echo "      ... input was aligned with bowtie2 and a form of --local"
	echo "          to a database with just 2 reads longer than the input reads."
	echo "          1 db entry is the 'beginning' of the start of the ltr."
	echo "          1 db entry is the 'ending' of the end of the ltr."
	echo
	echo "Default output is currently 2 fasta files containing the "
	echo "	pre- and post-ltr chimeric reads."
	echo
	echo "	-q ... yields fastq files instead."
	echo
	exit 1
}
#	Basically, this is TRUE AND DO ...
[ $# -eq 0 ] && usage

out='fasta'

while [ $# -ne 0 ] ; do
	case $1 in
		-q)
			shift; out="fastq";;
		-*)
			echo ; echo "Unexpected args from: ${*}"; usage ;;
		*) 
			break;;
	esac
done









while [ $# -ne 0 ] ; do
	echo $1
	base=${1%.*}		#	drop the extension
	ext=${1##*.}		#	grab the extension
	name=${base##*/}	#	just in case given path, drop the path

	#	requires bash >= 4.0
	#	${VARIABLE^^} converts to uppercase
	#	${VARIABLE,,} converts to lowercase
	#if [[ ${ext,,} =~ sam ]] ; then
	#	flag='-S'
	#	samheader="-h $1"
	#else
	#	echo "Input file is not a sam file so not including header in output."
	#	flag=''
	#	samheader=''
	#fi
	[[ ${ext,,} =~ sam ]] && flag='-S' || flag=''

	#	
	#	Find alignments that align past the appropriate end of the ends of the ltr.
	#

	#    f4 = unmapped
	#    F4 = NOT unmapped = mapped
	#    F8 = mate NOT unmapped = mate mapped

	# For some reason, this doesn't work on very big files.
	# It just runs, without any errors?
	# And doesn't create the fasta files.
	# If I run the samtools command and dump a sam/bam file, then run this on that it works?

	#	Has nothing to do with file size.  Old version of awk.
	#	Older versions of awk do not directly support "interval expressions", 
	#		ie ({4}, {4,}, {4,6])
	#	Need a newer version or add the --posix option

	cmd="samtools view $flag -h -F 4 $1"
	echo $cmd

	dir=`dirname $0`
	#	--posix NEEDS to be AFTER any -v settings!
	$cmd | awk -v base=$base -v out=$out --posix -f "$dir/samtools_extract_and_clip_chimeric_reads.awk"
#	$cmd | awk -v base=$base -v out=$out --posix '
#		BEGIN {
#			pre_out=sprintf("%s.pre_ltr.%s",base,out)
#			post_out=sprintf("%s.post_ltr.%s",base,out)
#		}
#		( ( NR % 10000 ) == 0 ){ print "Read "NR" records" }
#
#		( /^@SQ/ ){ ref[substr($2,4)] = substr($3,4) }
#
#		( ( $6 ~ /^[0-9]{2,}S[0-9IDM]*$/ ) && ( $4 <= 5 ) && ( $3 ~ /beginning/ ) ){
#			split($6,a,"S")
#			clip=a[1]-$4+1
#			if( out == "fastq" ){
#				print "@"$1"_pre_ltr" >> pre_out
#				print substr($10,1,clip) >> pre_out
#				print "+" >> pre_out
#				print substr($11,1,clip) >> pre_out
#			} else {
#				print ">"$1"_pre_ltr" >> pre_out
#				print substr($10,1,clip) >> pre_out
#			}
#		}
#
#		( ( $6 ~ /^[0-9IDM]*[0-9]{2,}S$/ ) && ( $4 >= ( ref[$3] - (length($10)*0.9) ) ) && ( $3 ~ /ending/ ) ){
#			clip=ref[$3]-$4+2
#			if( out == "fastq" ){
#				print "@"$1"_post_ltr" >> post_out
#				print substr($10,clip) >> post_out
#				print "+" >> post_out
#				print substr($11,clip) >> post_out
#			} else {
#				print ">"$1"_post_ltr" >> post_out
#				print substr($10,clip) >> post_out
#			}
#		}'

	#	The 2-digit requirment allows reads as short as 10 to be clipped and pass.
	#	However, the post_ltr requirement $4 >= ( ref[$3] - (length($10)*0.8)
	#	effectively forces them to be at least 20. This makes the post files shorter.
	#	Changing the 0.8 to 0.9.
#
#	Sam file columns
#	1 QNAME String Query template NAME
#	2 FLAG Int bitwise FLAG
#	3 RNAME String Reference sequence NAME
#	4 POS Int 1-based leftmost mapping POSition
#	5 MAPQ Int MAPping Quality
#	6 CIGAR String CIGAR string
#	7 RNEXT String Ref.  name of the mate/next read
#	8 PNEXT Int Position of the mate/next read
#	9 TLEN Int observed Template LENgth
#	10 SEQ String segment SEQuence
#	11 QUAL String
#
#	20151102
#	I used [0-9]{2,}S to select those that were solf clipped
#	by at least 2 digits (10bp). I would have needed more
#	complex logic to be more specific.
#	When choosing pre, I used ( $4 <= 5 ) to select those that aligned 
#	within 5bp of the beginning.
#	I used ( $4 >= (ref[$3] - (length($10)*0.9)) for post to match at the end.
#	Effective, but I don't like it.  I should've used a fixed number like pre.
#	Perhaps, ( $4 >= ( ref[$3] - length($10) + 5 ))?
#	I don't think that this would have changed anything
#	in the outcome, but would be more clear.
#
#	Actually, with 100bp reads, this condition could double the post output,
#	but the additional condition would effectively undo this as it requires
#	a 10bp soft clip.  I could run some tests, but I don't expect any difference.
#

	#	bowtie2 -x hg19 -U $base.pre_ltr.fasta  -S $base.pre_ltr.bowtie2.hg19.sam
	#	bowtie2 -x hg19 -U $base.post_ltr.fasta -S $base.post_ltr.bowtie2.hg19.sam

#    $4+$6 correctly does integer math and ignores the trailing M from $6
#samtools view -q 2 TCGA-FG-7636-10A.bowtie2.herv_k113_ltr_ends.__very_sensitive_local.beginning.soft_clipped.bowtie2.hg19..bam | awk '{print $3,$4,$6,$4+$6}'

#	NO! NO! NO!  Not like this for the ending. Just the beginning.
#samtools view -q 2 TCGA-FG-7636-10A.bowtie2.herv_k113_ltr_ends.__very_sensitive_local.ending.soft_clipped.bowtie2.hg19..bam | awk '{print $3,$4,$6,$4+$6}' > TCGA-FG-7636-10A.bowtie2.herv_k113_ltr_ends.__very_sensitive_local.ending.soft_clipped.bowtie2.hg19..insertion_points


	shift
done
