import os

dir = './audio_dataset_cortado'

f = open('audio_dataset.csv', 'w')
f.write('audio_path,label\n')
f.close()

f = open('audio_dataset.csv', 'a')

for diretorio, subpastas, arquivos in os.walk(dir):
    for arquivo in arquivos:
        path = os.path.join(diretorio, arquivo)
        label = arquivo.split('_')[0]

        if label != '3':
            line = path+','+label+'\n'

            f.write(line)
        
f.close()