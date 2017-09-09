#!/bin/bash
for i in `seq 1 1`
do	
	res=$(./../cmake-build-debug/ChessProject.exe < test_"$i".in > test_"$i".res)
	
	#res=$(./vault my_repository.vlt add folder1/folder2/data_filter"$i".c)
	res=$(diff test_"$i".res test_"$i".out)
	echo $res
	if [ "$res" != "" ]; then
		echo FAIL:  test number $i
	else 
		echo OK:    test number $i
	fi

done
