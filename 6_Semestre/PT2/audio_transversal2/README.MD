### Para Treinar a Rede
```
ludwig experiment   --dataset audio_dataset.csv   --config_file config_file.yaml
```


### Criação do ambiente virtual com miniconda
```
conda create -n ludwig-audio
conda activate ludwig-audio
```

### Instalação do ambiente
```
pip install ludwig
pip install ludwig[audio]
pip install petastorm
sudo apt-get install libjack-jackd2-dev portaudio19-dev
pip install PyAudio
pip install mysql-connector-python
```

### Colocar ID da coletora, latitude e longitude
```
echo "2  -15.873972 -47.821119" > info_coletora.txt
```

### Para rodar o script do projeto
```
python3 predict.py
```
