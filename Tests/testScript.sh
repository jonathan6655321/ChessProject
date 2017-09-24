#!/bin/bash
for i in `seq 1 5`
do	
	res=$(./../cmake-build-debug/ChessProject.exe < test_"$i".in > test_"$i".res)
	
	#res=$(./vault my_repository.vlt add folder1/folder2/data_filter"$i".c)
	desc=$(< test_"$i".desc)
	res=$(diff test_"$i".res test_"$i".out)	
	#echo result for test $i is: $res
	if [ "$res" != "" ]; then
		echo FAIL:  test number $i "		" $desc
		echo ___________"	"TEST $i DIFF START "	" ____________
		echo $res
		echo ___________"	"TEST $i DIFF END "	" ____________
	else 
		echo OK:    test number $i	"		" $desc
	fi	

done
