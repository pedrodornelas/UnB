import math
from cmath import exp, log10, sqrt

def factorial(x):
    return math.factorial(x)

def pow(x,y):
    return math.pow(x,y)

def somatorio(a,c):
    soma = 0
    for k in range(c):
        soma = soma + (pow(a,k)/factorial(k))
    return soma

a = 40.37
c = 50
h = 120
t = 10

# a = float(input("A(Erlangs) = "))
# c = int(input("C(canais) = "))
# h = float(input("H(hold time) = "))
# t = float(input("t(time) = "))

pr0 = pow(a,c) / (pow(a,c) + (factorial(c)*(1 - a/c)*somatorio(a,c)))

prt = pr0*exp(( (-(c-a)) * t) / h)

print("Pr[atraso > 0] = " + str(pr0))
print("Pr[atraso > " + str(t) + "] = " + str(prt))

n=9

# n = int(input("N = "))

q=sqrt(3*n)

si = 1 / (2*((q-1)**(-4)) + 2*((q+1)**(-4)) + 2*(q**(-4)))
sidb = 10*log10(si)

print("S/I = " + str(si))
print("S/I_dB = " + str(sidb))