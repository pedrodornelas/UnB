# -*- coding: utf-8 -*-
"""
Created on Wed Sep 29 18:19:35 2021

@author: Gabriel
"""

import pyaudio
import wave

def gravarAudio(seconds, filename):
    chunk = 1024  #Chunks de 1024 samples
    sample_format = pyaudio.paInt16  #16 bits por sample
    channels = 1
    fs = 44100  #Gravar 44100 samples por segundo
    
    p = pyaudio.PyAudio()  #Interface PortAudio
    
    print('Gravando clipe de audio')
    
    stream = p.open(format=sample_format,
                    channels=channels,
                    rate=fs,
                    frames_per_buffer=chunk,
                    input=True)
    
    frames = []  # Initialize array to store frames
    
    #Guardar o audio em chunks de "seconds" segundos
    for i in range(0, int(fs / chunk * seconds)):
        data = stream.read(chunk)
        frames.append(data)
    
    #Encerrar e fechar a stream de audio
    stream.stop_stream()
    stream.close()
    #Encerrar a interface PortAudio
    p.terminate()
    
    print('Finished recording')
    
    #Salva os dados como .wav
    wf = wave.open(filename, 'wb')
    wf.setnchannels(channels)
    wf.setsampwidth(p.get_sample_size(sample_format))
    wf.setframerate(fs)
    wf.writeframes(b''.join(frames))
    wf.close()

# n = 0 #Gravar n sets de 10 segundos, para gravar por periodos longos, talvez converter para while true
# while(n != 10):
#     gravarAudio(10, "gravacao" + str(n) + ".wav")
#     n = n + 1