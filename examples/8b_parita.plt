set terminal postscript eps  size 15, 40
set output 'result/8b_parita/8b_parita.eps'


set tmargin 2
set bmargin 0
set lmargin 10
set rmargin 4


set multiplot layout 44,1 title "8b_parita"

set xrange [0 :200]
set yrange [0 :2]

unset xtics 
set ytics 0,1,1

unset xlabel

plot "result/8b_parita/GNU_8b_parita.dat"  index 0 using 2:1 lt rgb "violet" lw 3 with steps  title columnheader(1) 
set tmargin 0
plot "result/8b_parita/GNU_8b_parita.dat" index 1 using 2:1 lt rgb "green" lw 3  with steps  title columnheader(1)

plot "result/8b_parita/GNU_8b_parita.dat" index 2 using 2:1  lt rgb "blue" lw 3 with steps  title columnheader(1)


plot "result/8b_parita/GNU_8b_parita.dat" index 3 using 2:1  lt rgb "red" lw 3  with steps  title columnheader(1)
plot "result/8b_parita/GNU_8b_parita.dat" index 4 using 2:1  lt rgb "green" lw 3  with steps  title columnheader(1)
plot "result/8b_parita/GNU_8b_parita.dat" index 5 using 2:1  lt rgb "violet" lw 3  with steps  title columnheader(1)
plot "result/8b_parita/GNU_8b_parita.dat" index 6 using 2:1  lt rgb "green" lw 3  with steps  title columnheader(1)
plot "result/8b_parita/GNU_8b_parita.dat" index 7 using 2:1  lt rgb "red" lw 3  with steps  title columnheader(1)
plot "result/8b_parita/GNU_8b_parita.dat" index 8 using 2:1  lt rgb "green" lw 3  with steps  title columnheader(1)
plot "result/8b_parita/GNU_8b_parita.dat" index 9 using 2:1  lt rgb "violet" lw 3  with steps  title columnheader(1)
plot "result/8b_parita/GNU_8b_parita.dat" index 10 using 2:1  lt rgb "green" lw 3  with steps  title columnheader(1)
plot "result/8b_parita/GNU_8b_parita.dat" index 11 using 2:1  lt rgb "red" lw 3  with steps  title columnheader(1)
plot "result/8b_parita/GNU_8b_parita.dat" index 12 using 2:1  lt rgb "green" lw 3  with steps  title columnheader(1)

plot "result/8b_parita/GNU_8b_parita.dat" index 13 using 2:1  lt rgb "red" lw 3  with steps  title columnheader(1)
plot "result/8b_parita/GNU_8b_parita.dat" index 14 using 2:1  lt rgb "green" lw 3  with steps  title columnheader(1)
plot "result/8b_parita/GNU_8b_parita.dat" index 15 using 2:1  lt rgb "violet" lw 3  with steps  title columnheader(1)
plot "result/8b_parita/GNU_8b_parita.dat" index 16 using 2:1  lt rgb "green" lw 3  with steps  title columnheader(1)
plot "result/8b_parita/GNU_8b_parita.dat" index 17 using 2:1  lt rgb "red" lw 3  with steps  title columnheader(1)
plot "result/8b_parita/GNU_8b_parita.dat" index 18 using 2:1  lt rgb "green" lw 3  with steps  title columnheader(1)
plot "result/8b_parita/GNU_8b_parita.dat" index 19 using 2:1  lt rgb "violet" lw 3  with steps  title columnheader(1)
plot "result/8b_parita/GNU_8b_parita.dat" index 20 using 2:1  lt rgb "green" lw 3  with steps  title columnheader(1)
plot "result/8b_parita/GNU_8b_parita.dat" index 21 using 2:1  lt rgb "red" lw 3  with steps  title columnheader(1)
plot "result/8b_parita/GNU_8b_parita.dat" index 22 using 2:1  lt rgb "green" lw 3  with steps  title columnheader(1)

plot "result/8b_parita/GNU_8b_parita.dat" index 23 using 2:1  lt rgb "violet" lw 3  with steps  title columnheader(1)
plot "result/8b_parita/GNU_8b_parita.dat" index 24 using 2:1  lt rgb "green" lw 3  with steps  title columnheader(1)
plot "result/8b_parita/GNU_8b_parita.dat" index 25 using 2:1  lt rgb "red" lw 3  with steps  title columnheader(1)
plot "result/8b_parita/GNU_8b_parita.dat" index 26 using 2:1  lt rgb "green" lw 3  with steps  title columnheader(1)
plot "result/8b_parita/GNU_8b_parita.dat" index 27 using 2:1  lt rgb "violet" lw 3  with steps  title columnheader(1)
plot "result/8b_parita/GNU_8b_parita.dat" index 28 using 2:1  lt rgb "green" lw 3  with steps  title columnheader(1)
plot "result/8b_parita/GNU_8b_parita.dat" index 29 using 2:1  lt rgb "red" lw 3  with steps  title columnheader(1)
plot "result/8b_parita/GNU_8b_parita.dat" index 30 using 2:1  lt rgb "green" lw 3  with steps  title columnheader(1)
plot "result/8b_parita/GNU_8b_parita.dat" index 31 using 2:1  lt rgb "violet" lw 3  with steps  title columnheader(1)
plot "result/8b_parita/GNU_8b_parita.dat" index 32 using 2:1  lt rgb "green" lw 3  with steps  title columnheader(1)

plot "result/8b_parita/GNU_8b_parita.dat" index 33 using 2:1  lt rgb "red" lw 3  with steps  title columnheader(1)
plot "result/8b_parita/GNU_8b_parita.dat" index 34 using 2:1  lt rgb "green" lw 3  with steps  title columnheader(1)
plot "result/8b_parita/GNU_8b_parita.dat" index 35 using 2:1  lt rgb "violet" lw 3  with steps  title columnheader(1)
plot "result/8b_parita/GNU_8b_parita.dat" index 36 using 2:1  lt rgb "green" lw 3  with steps  title columnheader(1)
plot "result/8b_parita/GNU_8b_parita.dat" index 37 using 2:1  lt rgb "red" lw 3  with steps  title columnheader(1)
plot "result/8b_parita/GNU_8b_parita.dat" index 38 using 2:1  lt rgb "green" lw 3  with steps  title columnheader(1)
plot "result/8b_parita/GNU_8b_parita.dat" index 39 using 2:1  lt rgb "violet" lw 3  with steps  title columnheader(1)
plot "result/8b_parita/GNU_8b_parita.dat" index 40 using 2:1  lt rgb "green" lw 3  with steps  title columnheader(1)
plot "result/8b_parita/GNU_8b_parita.dat" index 41 using 2:1  lt rgb "red" lw 3  with steps  title columnheader(1)
plot "result/8b_parita/GNU_8b_parita.dat" index 42 using 2:1  lt rgb "green" lw 3  with steps  title columnheader(1)

set bmargin 4
set xtics 10
set ylabel 'Value' offset -1
set xlabel 'Time' offset -1
plot "result/8b_parita/GNU_8b_parita.dat" index 43 using 2:1  lt rgb "black" lw 5 with steps  title columnheader(1)





unset multiplot; set output
