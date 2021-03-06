#!/bin/bash
output="./test/hardest_exp"
echo "" > "$output"
start_char="a"
if  ! [[ $1 =~ (^[1-9][0-9]{0,2}|1000)$ ]] ; then
	echo "Bad input. Need number in [1, 1000]"
	exit 1
fi

prev=1
d=$(printf '%d' "'$start_char")
i=1
while (( i < $1 )) ;
do
	next=$(echo "2 * $prev" | bc)
	prev=$(echo "$next" | bc)
	next_char=$(printf \\$(printf '%03o' $d))
	head -c "$next" /dev/zero | tr '\0' "$next_char" >> "$output"
	((++d))
	((++i))
done
