set terminal postscript eps  size 15, 20
set output 'result/MUX/MUX.eps'


set tmargin 2
set bmargin 0
set lmargin 10
set rmargin 4


set multiplot layout 23,1 title "MUX"

set xrange [0 :500]
set yrange [0 :2]

unset xtics 
set ytics 0,1,1

unset xlabel

plot "result/MUX/GNU_MUX.dat"  index 0 using 2:1 lt rgb "violet" lw 3 with steps  title columnheader(1) 
set tmargin 0
plot "result/MUX/GNU_MUX.dat" index 1 using 2:1 lt rgb "green" lw 3  with steps  title columnheader(1)

plot "result/MUX/GNU_MUX.dat" index 2 using 2:1  lt rgb "blue" lw 3 with steps  title columnheader(1)


plot "result/MUX/GNU_MUX.dat" index 3 using 2:1  lt rgb "red" lw 3  with steps  title columnheader(1)
plot "result/MUX/GNU_MUX.dat" index 4 using 2:1  lt rgb "green" lw 3  with steps  title columnheader(1)
plot "result/MUX/GNU_MUX.dat" index 5 using 2:1  lt rgb "violet" lw 3  with steps  title columnheader(1)
plot "result/MUX/GNU_MUX.dat" index 6 using 2:1  lt rgb "green" lw 3  with steps  title columnheader(1)
plot "result/MUX/GNU_MUX.dat" index 7 using 2:1  lt rgb "red" lw 3  with steps  title columnheader(1)
plot "result/MUX/GNU_MUX.dat" index 8 using 2:1  lt rgb "green" lw 3  with steps  title columnheader(1)
plot "result/MUX/GNU_MUX.dat" index 9 using 2:1  lt rgb "violet" lw 3  with steps  title columnheader(1)
plot "result/MUX/GNU_MUX.dat" index 10 using 2:1  lt rgb "green" lw 3  with steps  title columnheader(1)
plot "result/MUX/GNU_MUX.dat" index 11 using 2:1  lt rgb "red" lw 3  with steps  title columnheader(1)
plot "result/MUX/GNU_MUX.dat" index 12 using 2:1  lt rgb "red" lw 3  with steps  title columnheader(1)
plot "result/MUX/GNU_MUX.dat" index 13 using 2:1  lt rgb "green" lw 3  with steps  title columnheader(1)
plot "result/MUX/GNU_MUX.dat" index 14 using 2:1  lt rgb "violet" lw 3  with steps  title columnheader(1)
plot "result/MUX/GNU_MUX.dat" index 15 using 2:1  lt rgb "green" lw 3  with steps  title columnheader(1)
plot "result/MUX/GNU_MUX.dat" index 16 using 2:1  lt rgb "red" lw 3  with steps  title columnheader(1)
plot "result/MUX/GNU_MUX.dat" index 17 using 2:1  lt rgb "green" lw 3  with steps  title columnheader(1)
plot "result/MUX/GNU_MUX.dat" index 18 using 2:1  lt rgb "violet" lw 3  with steps  title columnheader(1)

set bmargin 4
set xtics 10
set ylabel 'Value' offset -1
set xlabel 'Time' offset -1
plot "result/MUX/GNU_MUX.dat" index 19 using 2:1  lt rgb "black" lw 5 with steps  title columnheader(1)





unset multiplot; set output
