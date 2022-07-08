set terminal png
set output '2flows.png'

set title "2 Flows"
set xlabel "Tempo(s)"
set ylabel "RTT"

set autoscale

plot "../PfifoFast_2Flow/PfifoFast-v4PingRtt.txt" using 1:2 with lines title "PfifoFast", \
     "../ARED_2Flow/ARED-v4PingRtt.txt" using 1:2 with lines title "ARED", \
     "../CoDel_2Flow/CoDel-v4PingRtt.txt" using 1:2 with lines title " CoDel", \
     "../FqCoDel_2Flow/FqCoDel-v4PingRtt.txt" using 1:2 with lines title "FqCoDel", \
     "../PIE_2Flow/PIE-v4PingRtt.txt" using 1:2 with lines title "PIE"



