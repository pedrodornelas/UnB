import numpy as np
from math import *

r1 = float(input('R1: '))
r2 = float(input('R2: '))
r3 = float(input('R3: '))
r4 = float(input('R4: '))
r5 = float(input('R5: '))
c = float(input('c: '))
vs= float(input('vs: '))


print("PArte 2 ")

soma1= r1+ r2+ r3
soma2 = r3+r4

A = np.array([[soma1, -r3  ], [-r3, soma2]])
B = np.array([ 0 , vs])
X = np.linalg.inv(A).dot(B)

vr4 = X[1]*r4

print("A tensão em R4 quando o capacitor volta a estar plenamente carregado é", vr4)
print("O t=0 é o maior valor")