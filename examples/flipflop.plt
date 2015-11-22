set terminal postscript eps  size 15, 20
set output 'result/flipflop/flipflop.eps'


set tmargin 2
set bmargin 0
set lmargin 10
set rmargin 4


set multiplot layout 8,1 title "flipflop"

set xrange [0 :500]
set yrange [0 :2]

unset xtics 
set ytics 0,1,1

unset xlabel

plot "result/flipflop/GNU_flipflop.dat"  index 0 using 2:1 lt rgb "violet" lw 3 with steps  title columnheader(1) 
set tmargin 0
plot "result/flipflop/GNU_flipflop.dat" index 1 using 2:1 lt rgb "green" lw 3  with steps  title columnheader(1)

plot "result/flipflop/GNU_flipflop.dat" index 2 using 2:1  lt rgb "blue" lw 3 with steps  title columnheader(1)


plot "result/flipflop/GNU_flipflop.dat" index 3 using 2:1  lt rgb "red" lw 3  with steps  title columnheader(1)
plot "result/flipflop/GNU_flipflop.dat" index 4 using 2:1  lt rgb "green" lw 3  with steps  title columnheader(1)
plot "result/flipflop/GNU_flipflop.dat" index 5 using 2:1  lt rgb "violet" lw 3  with steps  title columnheader(1)
plot "result/flipflop/GNU_flipflop.dat" index 6 using 2:1  lt rgb "violet" lw 3  with steps  title columnheader(1)

set bmargin 4
set xtics 10
set ylabel 'Value' offset -1
set xlabel 'Time' offset -1
plot "result/flipflop/GNU_flipflop.dat" index 7 using 2:1  lt rgb "black" lw 5 with steps  title columnheader(1)





unset multiplot; set output
