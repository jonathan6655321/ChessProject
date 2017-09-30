#!/bin/bash
for i in `seq 1 2`
do	
	res=$(./../../FuckingGui.exe < test"$i".in > test"$i".res)
	#res=$(diff "$i".res "$i".out)
	diff test"$i".res test"$i"a.out
done
