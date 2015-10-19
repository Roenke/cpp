#!/bin/bash
exec_path="./bin/huffman"
ls "./test" | while read test_case
do
	basename=$(basename "$test_case")
	dirname=$(dirname "$test_case")
	input="./test/$basename"
	output="$input.huf"
	rev="$input.rev"
	echo "$input -> $output"
	time "$exec_path" -f "$input" -c -o "$output" > /dev/null
	echo "$output -> $rev"
	time "$exec_path" -f "$output" -u -o "$rev" > /dev/null
	diff -q "$input" "$rev"
	rm "$output" "$rev"
done