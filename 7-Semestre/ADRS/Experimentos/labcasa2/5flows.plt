set terminal png
set output '5flows.png'

set title "5 Flows"
set xlabel "Tempo(s)"
set ylabel "RTT"

set autoscale

plot "../PfifoFast_5Flow/PfifoFast-v4PingRtt.txt" using 1:2 with lines title "PfifoFast", \
     "../ARED_5Flow/ARED-v4PingRtt.txt" using 1:2 with lines title "ARED", \
     "../CoDel_5Flow/CoDel-v4PingRtt.txt" using 1:2 with lines title " CoDel", \
     "../FqCoDel_5Flow/FqCoDel-v4PingRtt.txt" using 1:2 with lines title "FqCoDel", \
     "../PIE_5Flow/PIE-v4PingRtt.txt" using 1:2 with lines title "PIE"



