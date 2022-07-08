
from cmath import sqrt


tempos = [3.8 , 4.5 , 2.5 , 3.9 , 3.2 , 4.2 , 3.3 , 3.7 , 5.5]
nAmostras = len(tempos)

soma = 0
for i in tempos:
    soma += i

# media = soma / nAmostras
media = soma / nAmostras

soma = 0
for i in tempos:
    termo = pow((i-media),2)
    soma += termo

variancia = soma / (nAmostras-1)
desvioPadrao = sqrt(variancia)


tTabelaA4 = 1.860
termoIntervalo = (tTabelaA4*desvioPadrao) / sqrt(nAmostras)
intervalo1 = media - termoIntervalo
intervalo2 = media + termoIntervalo

intervalo90 = str(media) + " +- " + str(termoIntervalo) + " = (" + str(intervalo1) + ";" + str(intervalo2)


tTabelaA4 = 5.041
termoIntervalo = (tTabelaA4*desvioPadrao) / sqrt(nAmostras)
intervalo1 = media - termoIntervalo
intervalo2 = media + termoIntervalo

intervalo99 = str(media) + " +- " + str(termoIntervalo) + " = (" + str(intervalo1) + ";" + str(intervalo2)


print("Tempo Médio(TM) = " + str(media))
print("Variância = " + str(variancia))
print("Desvio padrão = " + str(desvioPadrao))
print("Intervalo de confiança 90% = " + intervalo90)
print("Intervalo de confiança 99% = " + intervalo99)