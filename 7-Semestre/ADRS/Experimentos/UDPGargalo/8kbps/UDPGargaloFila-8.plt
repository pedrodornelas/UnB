set terminal png
set output "UDPGargaloFila.png"
set title "Tamanho da Fila x Tempo de Simulacao"
set xlabel "Tempo de Simulacao (s)"
set ylabel "Numero de pacotes na fila"

set xrange [0:100]
set yrange [0:100]
plot "-"  title "Pacotes na fila" with steps
0.08632 1
0.08632 0
0.27332 1
0.46032 2
0.64732 3
0.83432 4
1.02132 5
1.14032 4
1.20832 5
1.39532 6
1.58232 7
1.76932 8
1.95632 9
2.14332 10
2.19432 9
2.33032 10
2.51732 11
2.70432 12
2.89132 13
3.07832 14
3.24832 13
3.26532 14
3.45232 15
3.63932 16
3.82632 17
4.01332 18
4.20032 19
4.30232 18
4.38732 19
4.57432 20
4.76132 21
4.94832 22
5.13532 23
5.32232 24
5.35632 23
5.50932 24
5.69632 25
5.88332 26
6.07032 27
6.25732 28
6.41032 27
6.44432 28
6.63132 29
6.81832 30
7.00532 31
7.19232 32
7.37932 33
7.46432 32
7.56632 33
7.75332 34
7.94032 35
8.12732 36
8.31432 37
8.50132 38
8.51832 37
8.68832 38
8.87532 39
9.06232 40
9.24932 41
9.43632 42
9.57232 41
9.62332 42
9.81032 43
9.99732 44
10.1843 45
10.3713 46
10.5583 47
10.6263 46
10.7453 47
10.9323 48
11.1193 49
11.3063 50
11.4933 51
11.6803 50
11.6803 51
11.8673 52
12.0543 53
12.2413 54
12.4283 55
12.6153 56
12.7343 55
12.8023 56
12.9893 57
13.1763 58
13.3633 59
13.5503 60
13.7373 61
13.7883 60
13.9243 61
14.1113 62
14.2983 63
14.4853 64
14.6723 65
14.8423 64
14.8593 65
15.0463 66
15.2333 67
15.4203 68
15.6073 69
15.7943 70
15.8963 69
15.9813 70
16.1683 71
16.3553 72
16.5423 73
16.7293 74
16.9163 75
16.9503 74
17.1033 75
17.2903 76
17.4773 77
17.6643 78
17.8513 79
18.0043 78
18.0383 79
18.2253 80
18.4123 81
18.5993 82
18.7863 83
18.9733 84
19.0583 83
19.1603 84
19.3473 85
19.5343 86
19.7213 87
19.9083 88
20.0953 89
20.1123 88
20.2823 89
20.4693 90
20.6563 91
20.8433 92
21.0303 93
21.1663 92
21.2173 93
21.4043 94
21.5913 95
21.7783 96
21.9653 97
22.1523 98
22.2203 97
22.3393 98
22.5263 99
22.7133 100
23.2743 99
23.2743 100
24.3283 99
24.3283 100
25.3823 99
25.3823 100
26.4363 99
26.4363 100
27.4903 99
27.4903 100
28.5443 99
28.5443 100
29.5983 99
29.5983 100
30.6523 99
30.6523 100
31.7063 99
31.7063 100
32.7603 99
32.7603 100
33.8143 99
33.8143 100
34.8683 99
34.8683 100
35.9223 99
35.9223 100
36.9763 99
36.9763 100
38.0303 99
38.0303 100
39.0843 99
39.0843 100
40.1383 99
40.1383 100
41.1923 99
41.1923 100
42.2463 99
42.2463 100
43.3003 99
43.3003 100
44.3543 99
44.3543 100
45.4083 99
45.4083 100
46.4623 99
46.4623 100
47.5163 99
47.5163 100
48.5703 99
48.5703 100
49.6243 99
49.6243 100
50.6783 99
50.6783 100
51.7323 99
51.7323 100
52.7863 99
52.7863 100
53.8403 99
53.8403 100
54.8943 99
54.8943 100
55.9483 99
55.9483 100
57.0023 99
57.0023 100
58.0563 99
58.0563 100
59.1103 99
59.1103 100
60.1643 99
60.1643 100
61.2183 99
61.2183 100
62.2723 99
62.2723 100
63.3263 99
63.3263 100
64.3803 99
64.3803 100
65.4343 99
65.4343 100
66.4883 99
66.4883 100
67.5423 99
67.5423 100
68.5963 99
68.5963 100
69.6503 99
69.6503 100
70.7043 99
70.7043 100
71.7583 99
71.7583 100
72.8123 99
72.8123 100
73.8663 99
73.8663 100
74.9203 99
74.9203 100
75.9743 99
75.9743 100
77.0283 99
77.0283 100
78.0823 99
78.0823 100
79.1363 99
79.1363 100
80.1903 99
80.1903 100
81.2443 99
81.2443 100
82.2983 99
82.2983 100
83.3523 99
83.3523 100
84.4063 99
84.4063 100
85.4603 99
85.4603 100
86.5143 99
86.5143 100
87.5683 99
87.5683 100
88.6223 99
88.6223 100
89.6763 99
89.6763 100
90.7303 99
90.7303 100
91.7843 99
91.7843 100
92.8383 99
92.8383 100
93.8923 99
94.9463 98
96.0003 97
97.0543 96
98.1083 95
99.1623 94
e
