#!/usr/bin/env ruby

require 'optparse'

# This hash will hold all of the options
# parsed from the command-line by
# OptionParser.
options = {
	:db      => "/Volumes/cube/working/indexes/nt",
	:verbose => false
}

optparse = OptionParser.new do |opts|
	# Set a banner, displayed at the top of the help screen.
	opts.banner = "\nUsage: #{File.basename($0)} [options] in_file out_file\n\n" <<
		"This script was designed to add the sequence description\n" <<
		"to the results.txt file produced by the write_result.rb script.\n" <<
		"It does this by looping through the input file and using\n" <<
		"blastdbcmd on each entry and parsing the results.\n\n" <<
		"The in file is expected to be in blastn outfmt 6.\n\n"

	#	Define the options, and what they do

	opts.on( '-d', '--db BlastDB', "Blast database reference",
			"(default #{options[:db]})" ) do |db|
		options[:db] = db
	end

	opts.on( '-v', '--verbose', 'Output more information' ) do
		options[:verbose] = true
	end

	# This displays the help screen, all programs are assumed to have this option.
	#	Add extra "\n" to last option for aesthetics.
	opts.on( '-h', '--help', 'Display this help screen',"\n") do
		puts opts
		exit
	end
end
 
# Parse the command-line. Remember there are two forms
# of the parse method. The 'parse' method simply parses
# ARGV, while the 'parse!' method parses ARGV and removes
# any options found there, as well as any parameters for
# the options. What's left is the list of files to resize.
optparse.parse!

#	Infile and outfile required
unless ARGV.length == 2
	puts optparse	#	Basically display the command line help
	exit
end

unless File.exists?(ARGV[0])
	puts "File #{ARGV[0]} not found." 
	exit
end
 
File.open( ARGV[0], 'r' ) { |infile|
File.open( ARGV[1], 'w' ) { |outfile|

#	first line better be a header line
#	   contig_name^Inumber_of_raw_reads_fall_on_this_contig^Inon_human_species^IE-value^Ibit_scor     e^Icontig_sequence$

	line = infile.gets
	parts = line.split("\t")
	parts.insert( 3, 'description' )
	outfile.puts parts.join("\t")

	while( line = infile.gets )
#	  comp155_c0_seq1^I9^Igi|115286659|gb|CP000443.1|^I3e-149^I 536^IGCGGCGTGTTCTTCCTCGGCTTCGGTG     GTTCGCGTTGGACTTCCGACATGGCGATCAACTACTACAAGGTCGTCCTGGGCGTGGCCGCGCAGCTCTTCGCAATGGTGCTCCTGGTGG     GCATCGGCAAGACCTTCCTCGATGACTACTACGCGCGCATGAGCGCCGGCATCAGCCTCAAGGAAATGGGTGTGATGCTGATCGTCGTCA     TCATCCTTCTGGCGTTGACCAACAAGATTCCGCCGCTCATCGCCGGGATCATCACCGGCGCGAGCGTGGGCGGTGCCGGCATCGGTCAGT     TCGGTGCAGGCGCTGCGCT$

		puts "Initial line without description ...\n#{line}" if options[:verbose]
		parts = line.split("\t")
		command = "blastdbcmd -entry '#{parts[2]}' -db #{options[:db]} | head -1"
		puts "Executing ...\n#{command}" if options[:verbose]
		description = `#{command}`

		puts "Got ...\n#{description}" if options[:verbose]

		description.gsub!(">#{parts[2]}",'')
		description.gsub!(/^\s*/,'')
		description.chomp!
		puts "After parsing out seqid ...\n#{description}" if options[:verbose]

#> blastdbcmd -entry "gi|301795361|emb|FQ312042.1|" -db /Volumes/cube/working/indexes/nt | head -1
#>gi|301795361|emb|FQ312042.1| Streptococcus pneumoniae SPN033038 draft genome
		parts.insert( 3, description )

		newline = parts.join("\t")
		puts "New line with description ...\n#{newline}" if options[:verbose]
		outfile.puts newline
	end
} }	#	File.open
