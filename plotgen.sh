#!/bin/bash
EXAMPLES=examples/*.in
PLOT=examples/*.plt

#create result tree 
for file in $EXAMPLES;do
	file=${file##*/}
	dir=${file%.in}
	mkdir result/$dir
	./logicSim examples/$file
done

for plot  in $PLOT;do
	echo "Generating plot for: ${plot##*/}"
	gnuplot $plot
done
