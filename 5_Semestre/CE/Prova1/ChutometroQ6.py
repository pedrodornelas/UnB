import numpy as np
from math import *

r1 = float(input('R1: '))
r2 = float(input('R2: '))
r3 = float(input('R3: '))
r4 = float(input('R4: '))
l = float(input('l: '))
vs= float(input('vs: '))

req= (r1*r2)/(r1+r2)

tempo = (r3+r4)/l

print("A constante de tempo é", tempo)

val1 = req + r3
val2 = r3 + r4

A = np.array([[val1 , -r3 ], [-r3, val2 ]])
B = np.array([ vs , 0])
X = np.linalg.inv(A).dot(B)

print("A corrente inicialmente armazenada no indutor é ", X[1])