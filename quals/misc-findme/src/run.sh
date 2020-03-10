#!/bin/bash

for i in {1..20}
do
   	mkdir file$i
	for j in {1..20}
	do
   		mkdir file$i/file$j
		for k in {1..20}
		do
			mkdir file$i/file$j/file$k
			echo CTF{thisIsNotTheFlag] > file$i/file$j/file$k/flag.txt
		done
	done
done

