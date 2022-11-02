#!/bin/bash

filename="data.txt"
patterns="patterns.txt"
flags=(e i v c n o l h)

rm s21_grep
make s21_grep

for flag in ${flags[*]};
do
	echo "--$flag"
	grep -$flag my $filename >> out1.txt
	./s21_grep -$flag my $filename >> out2.txt
	result=$(diff out1.txt out2.txt)
	if (($? == '0')); then
		echo "SUCCESS"
		rm out*
	else
		echo "FAIL"
		exit 0
	fi
done

echo "--f"
grep -f $patterns $filename >> out1.txt
./s21_grep -f $patterns $filename >> out2.txt
result=$(diff out1.txt out2.txt)
if (($? == '0')); then
	echo "SUCCESS"
	rm out*
else
	echo "FAIL"
	exit 0
fi

echo "--s"
grep -s my invalid.txt >> out1.txt
./s21_grep -s my invalid.txt >> out2.txt
result=$(diff out1.txt out2.txt)
if (($? == '0')); then
        echo "SUCCESS"
        rm out*
else
        echo "FAIL"
        exit 0
fi

