#!/usr/bin/env awk -f
#	
#	#!/bin/sh
#	#
#	# split fasta files into smaller fasta files with no more than 200 reads
#	#
#	#		fasta_read_split.sh my_file_1.fasta my_file_2.fasta
#	#
#	#	if first argument is a number, it will be used for the max_reads
#	#
#	
#	
#	if [ $# -eq 0 ]; then
#		echo 
#		echo "split fasta files into smaller fasta files with no more than 200 reads"
#		echo
#		echo "Usage:"
#		echo
#		echo "`basename $0` [optional max_read_size]"
#		echo
#		echo "Example:"
#		echo
#		exit
#	fi
#	
#	tmp=`echo $1 | tr -cd '[:digit:]'`
#	#	need the x's in case is blank
#	if [ "x${tmp}" == "x${1}" ] ; then
#		max_reads=$1
#		shift
#	else
#		max_reads=200
#	fi
#	
#	while [ $# -ne 0 ] ; do
#		awk '
	BEGIN{
		max_reads=200	#	explicitly overridable on the command line
		current_file_name=""
	}
	( FILENAME != current_file_name ){ 
		current_file_name=FILENAME
		read_count=0
		file_number=0
		f=sprintf("%s_%04d",FILENAME,++file_number)
	}	
	{
		if(/^>/){
			if( read_count >= max_reads ){
				close(f)
				f=sprintf("%s_%04d",FILENAME,++file_number)
				read_count=0
			}
			read_count++
		}
		print>>f
	}
#	' $1
#		shift
#	done
