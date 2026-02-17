#!/usr/bin/env sh

# Usage:
# This script should be a sibling to the students' submission directories.
# e.g. if 
# $ ls submissions
# garciamallenjonathan_pa1
# bitdiddleben_pa1
# reasonerlouis_pa1
# hackerpalyssa_pa1
# rate_style.sh

# Then you may run the script.

for i in greedyScheduling.c editDistance.c balanced.c; do
    echo starting "$i"
    for j in ./*/*/"$i"; do
	# Loop over all the student's code for a single problem.
	# The file $j is a student's submitted C file.
	score=9999
	for k in LLVM GNU Google Chromium Microsoft Mozilla WebKit; do
	    # Define a score as the quantity of lines in the diff diff
	    # between the student's C file clang-format's correction.
	    # Keep the best score is the lowest score across the above formats.
	    new=$(clang-format --style=$k "$j" | diff -Z - "$j" | wc -l);
	    if [ "$new" -lt "$score" ] ; then
		score=$new
	    fi
	done
	# Print the score and the filename to stdout.
	# This permits sorting with POSIX sort later.
	echo "$score" "$j"
    done
    echo ending "$i"
done
