#!/bin/bash
for i in `seq 4 4`
do	
	res=$(./../../FuckingGui.exe < "$i"a.in > "$i"a.res)
	#res=$(diff "$i".res "$i".out)
	diff "$i".res "$i"a.out
done
