set terminal png
set output '20flows.png'

set title "20 Flows"
set xlabel "Tempo(s)"
set ylabel "RTT"

set autoscale

plot "../PfifoFast_20Flow/PfifoFast-v4PingRtt.txt" using 1:2 with lines title "PfifoFast", \
     "../ARED_20Flow/ARED-v4PingRtt.txt" using 1:2 with lines title "ARED", \
     "../CoDel_20Flow/CoDel-v4PingRtt.txt" using 1:2 with lines title " CoDel", \
     "../FqCoDel_20Flow/FqCoDel-v4PingRtt.txt" using 1:2 with lines title "FqCoDel", \
     "../PIE_20Flow/PIE-v4PingRtt.txt" using 1:2 with lines title "PIE"



