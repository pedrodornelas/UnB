import math

f = open('caso3.txt','r')
aux=0
print("Freq\tMag(dB)\tAngle(º)")
for linha in f:
    if aux!=0 :
        campos = linha.split('\t')
        #print("Testando",campos[0])
        num=float(campos[1].replace(',','.'))
        mag = 20*math.log(num,10)
        #print(campos[1], mag)

        num=float(campos[2].replace(',','.'))
        angle=180*num/math.pi
        
        print(campos[0],"\t",mag,"\t",angle)
    aux=1
f.close()