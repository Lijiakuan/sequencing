#!/bin/sh

#
#	pieces_check.sh  dna/output/fallon_SFPB001A_filtered_20130722/trinity_input_single.fasta.20130725154032.pieces
#
#	count the contents of the given path
#
#	parse the blastn output files to ensure that they are complete and not truncated
#	or written to by multiple processes at the same time or anything like that.
#
#	a blast files should start with
#
#	BLASTN 2.2.25+
#	
#	
#	Reference: Zheng Zhang, Scott Schwartz, Lukas Wagner, and Webb
#	Miller (2000), "A greedy algorithm for aligning DNA sequences", J
#	Comput Biol 2000; 7(1-2):203-14.
#	
#
#	... and end with ...
#
#
#  Database: Nucleotide collection (nt)
#    Posted date:  Mar 31, 2013  4:15 PM
#  Number of letters in database: 47,995,143,033
#  Number of sequences in database:  24,586,792
#
#
#
#	Matrix: blastn matrix 1 -2
#	Gap Penalties: Existence: 0, Extension: 2.5
#



if [ $# -eq 0 ]; then
	echo
	echo "checks the contents of the given 'pieces' directory(ies)"
	echo
	echo "Usage:"
	echo
	echo "`basename $0` directory(ies)"
	echo
	echo "Example:"
	echo "pieces_check.sh  dna/output/fallon_SFPB001A_filtered_20130722/trinity_input_single.fasta.20130725154032.pieces"
	echo
	exit
fi

tmp=`echo $1 | tr -cd '[:digit:]'`
# need the x's in case is blank
if [ "x${tmp}" == "x${1}" ] ; then
	skip=$1
	shift
else
	skip=0
fi


#
#	It is unlikely that more than one will actually be called,
#	however, the while loop provides a nice wrapper.
#
while [ $# -ne 0 ] ; do
	path=$1

#	re-adding .fasta extension to increase findability.
#	also may change the number of digits in pieces.
#	would prefer to be able to glob like a regex \d+ , but can't
#
#	fasta_count=`ls $path/*fasta_????????? | wc -l`
#	fake.fasta_000000006.fasta
	fasta_count=`ls $path/*.fasta | wc -l`
#	blast_count=`ls $path/*fasta_?????????.blastn.txt | wc -l`
#	fake.fasta_000000006.fasta.blastn.txt
	blast_count=`ls $path/*.fasta.blastn*.txt | wc -l`

	echo "Found $fasta_count fasta files"
	echo "Found $blast_count blast files"

#	for blast in `ls $path/*fasta_?????????.blastn.txt` ; do
	#
	#	If there aren't any, this loop will crash
	#	ls: fake.fasta.20130802170906.pieces/*fasta_*.blastn.txt: No such file or directory
	#
	i=0
	for blast in `ls $path/*fasta.blastn*.txt` ; do
		i=`expr $i + 1`
		if [ $i -le $skip ] ; then
			echo "skipping $blast"
			continue
		fi
		echo "Checking $blast"
#
#	I think that double square brackets are only needed for regexps [[ ]]
#
		if [[ ! `head -1 $blast` =~ ^BLASTN ]] ; then
			echo "  *  First line in $blast is not correct"
		else
			echo 'First line is good'
		fi
		if [[ ! `tail -1 $blast` =~ ^Gap\ Penalties ]] ; then
			echo "  *  Last line in $blast is not correct"
		else
			echo 'Last line is good'
		fi

#		echo 'Counting "Query= " lines'
#		grep 'Query= ' $blast | wc -l
#
#		echo 'Counting "Effective search space used:" lines'
#		grep 'Effective search space used:' $blast | wc -l
#
##	If crashes, output is incomplete.  May not have "Effective search" line.  And "BLASTN" won't start on left.
##	Trying without anchor.
#
#
#		echo "Checking for silent failures. Rerun if any found."
#		echo "Checking for 'no longer exists' caused by database files temporarily disappearing?"
#		grep -n "no longer exists in database" $blast
#
#		echo "Checking for non-printable control characters (won't show the chars though) ..."
#		grep -n '[[:cntrl:]]'  $blast
#
#		if [ `grep '^BLASTN' $blast | wc -l` -gt 1 ] ; then
#			echo "  *  Too many 'first lines' in $blast"
#		fi
#		if [ `grep '^Gap Penalties' $blast | wc -l` -gt 1 ] ; then
#			echo "  *  Too many 'last lines' in $blast"
#		fi

		blastn_check.gawk $blastn

#
#		#	using 1 awk call rather than 6 greps.  MUCH FASTER
#		#	use GAWK instead of AWK.  Gets control chars better
#		gawk '
#			(/BLASTN/){ blastn++ }
#			(/Gap Penalties/){ gap++ }
#			(/Query= /){ query++ }
#			(/Effective search space used:/){ effective++ }
#			(/no longer exists in database/){ nolonger++ }
#			(/[^[:print:]]/){ 	#	too many (includes \anything?)
#				print "Non-printable character(s) found on line number :",NR,":"
#				print $0
#				nonprint++ 
#			}
#			(/[[:cntrl:]]/){	#	REQUIRES double brackets as they are for different reasons
#				print "Control character(s) found on line number :",NR,":"
#				print $0
#				control++ 
#			}
#			END{
#				print "BLASTN line count"
#				print blastn
#				if( blastn > 1 ){ print " * TOO MANY" }
#				print "Gap Penalties line count"
#				print gap
#				if( gap > 1 ){ print " * TOO MANY" }
#				if( blastn != gap ){ print " * BLASTN and Gap Penalties lines are out of sync" }
#				print "Query=  line count"
#				print query
#				print "Effective search space used: line count"
#				print effective
#				if( query != effective ){ print " * Query= and Effective search lines are out of sync" }
#				print "no longer exists in database line count"
#				print nolonger
#				if( nolonger > 0 ){ print " * TOO MANY" }
#				print "nonprint character line count"
#				print nonprint
#				if( nonprint > 0 ){ print " * TOO MANY" }
#				print "control character line count"
#				print control
#				if( control > 0 ){ print " * TOO MANY" }
#				print "---"
#			}
#		' $blast
#
	done

	shift
done
