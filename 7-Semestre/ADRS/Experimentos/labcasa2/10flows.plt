set terminal png
set output '10flows.png'

set title "10 Flows"
set xlabel "Tempo(s)"
set ylabel "RTT"

set autoscale

plot "../PfifoFast_10Flow/PfifoFast-v4PingRtt.txt" using 1:2 with lines title "PfifoFast", \
     "../ARED_10Flow/ARED-v4PingRtt.txt" using 1:2 with lines title "ARED", \
     "../CoDel_10Flow/CoDel-v4PingRtt.txt" using 1:2 with lines title " CoDel", \
     "../FqCoDel_10Flow/FqCoDel-v4PingRtt.txt" using 1:2 with lines title "FqCoDel", \
     "../PIE_10Flow/PIE-v4PingRtt.txt" using 1:2 with lines title "PIE"



