import os
import subprocess

# dir = './Chainsaw' #Mudar a classe aqui
dir = input('Digite o diretório onde estão os videos a serem cortados: ')
label = input('Digite o label desses videos: ')

for diretorio, subpastas, arquivos in os.walk(dir):
    for arquivo in arquivos:
        params = arquivo.split('_')
        id = params[0]
        time = params[2].split('.')[0]

        stereo_novo_arquivo = './audio_dataset_cortado/'+ 'stereo_' + label + '_' + id + '.wav'
        novo_arquivo = './audio_dataset_cortado/' + label + '_' + id + '.wav'

        subprocess.run(['ffmpeg', '-ss', time, '-i', dir+'/'+arquivo, '-t', '10', '-vcodec', 'copy', '-acodec', 'copy', stereo_novo_arquivo])

        subprocess.run(['ffmpeg', '-i', stereo_novo_arquivo, '-ac', '1', novo_arquivo])

        subprocess.run(['rm', stereo_novo_arquivo])

        