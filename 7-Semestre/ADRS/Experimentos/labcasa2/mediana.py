import statistics

def mediana(x):
    return statistics.median(x)

def rtt(df):
    f = open(df,'r')
    lines = f.readlines()
    rtt = []
    for line in lines:
        line = line.split()
        rtt.append(int(line[1]))
    return rtt

pfifofast_2flow = mediana(rtt('PfifoFast_2Flow/PfifoFast-v4PingRtt.txt'))
ared_2flow = mediana(rtt('ARED_2Flow/ARED-v4PingRtt.txt'))
codel_2flow = mediana(rtt('CoDel_2Flow/CoDel-v4PingRtt.txt'))
fqcodel_2flow = mediana(rtt('FqCoDel_2Flow/FqCoDel-v4PingRtt.txt'))
pie_2flow = mediana(rtt('PIE_2Flow/PIE-v4PingRtt.txt'))


pfifofast_20flow = mediana(rtt('PfifoFast_20Flow/PfifoFast-v4PingRtt.txt'))
ared_20flow = mediana(rtt('ARED_20Flow/ARED-v4PingRtt.txt'))
codel_20flow = mediana(rtt('CoDel_20Flow/CoDel-v4PingRtt.txt'))
fqcodel_20flow = mediana(rtt('FqCoDel_20Flow/FqCoDel-v4PingRtt.txt'))
pie_20flow = mediana(rtt('PIE_20Flow/PIE-v4PingRtt.txt'))

# labelx = ['PfifoFast','ARED','CoDel', 'FqCodel', 'PIE']
# labely = ['2 Flows', '20 Flows']

print('PfifoFast_2Flow = ' + str(pfifofast_2flow))
print('ARED_2Flow = ' + str(ared_2flow))
print('CoDel_2Flow = ' + str(codel_2flow))
print('fqcodel_2Flow = ' + str(fqcodel_2flow))
print('pie_2Flow = ' + str(pie_2flow))
print('pfifofast_20Flow = ' + str(pfifofast_20flow))
print('ared_20Flow = ' + str(ared_20flow))
print('codel_20Flow = ' + str(codel_20flow))
print('fqcodel_20Flow = ' + str(fqcodel_20flow))
print('pie_20Flow = ' + str(pie_20flow))

