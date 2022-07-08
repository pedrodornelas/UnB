from cmath import log

f = [2.4,5]
d = [0.5,1,1.5,2,3,4,5,10]
for j in d:
    for i in f:
        l = 92.44778322 + 20*log(i,10) + 20*log(j,10)
        print(str(i) + "GHz "+ str(j) + "km " + "L_dB = " + str(l))

