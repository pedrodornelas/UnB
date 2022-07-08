from ludwig.api import LudwigModel

import threading

import gravarAudio as gravar

import mysql.connector

from datetime import datetime

df = open('./info_coletora.txt','r')
linha = df.readline()
linha = linha.split()

id_coletora = linha[0]
latitude = linha[1]
longitude = linha[2]

df.close()

def mysql_data_send(sql, val):
    mydb = mysql.connector.connect(
        host='192.185.210.165',
        user='engne598',
        password='ges2019direx@)!(',
        database='engne598_coletora_alerta_db'
    )

    mycursor = mydb.cursor()

    mycursor.execute(sql, val)

    mydb.commit()




def thread_prediction(model):
    predictions, output_directory = model.predict(dataset='./audio_predict.csv')   

    # print(predictions.info())
    # for i in predictions.label_probabilities:
    #     print(i)
    # print(predictions.label_probabilities)
    # print(predictions.label_probability[0])
    # # print(predictions.label_probabilities_<UNK>)

    status_tiro = '0'
    status_serra = '0'

    if predictions.label_probabilities_0[0] > 0.7:
        status_serra = '1'
    
    elif predictions.label_probabilities_1[0] > 0.5 or predictions.label_probabilities_2[0] > 0.5 or predictions.label_probabilities_4[0] > 0.5:
        status_tiro = '1'


    print(predictions.label_probabilities_0[0])
    print(predictions.label_probabilities_1[0])
    print(predictions.label_probabilities_2[0])
    print(predictions.label_probabilities_4[0])
    #print(predictions.label_probabilities_5[0])

    data = str(datetime.now())

    sql = "INSERT INTO dados (id_coletora, status_tiro, status_serra, latitude, longitude, data) VALUES (%s, %s, %s, %s, %s, %s)"
    val = (id_coletora, status_tiro, status_serra, latitude, longitude, data)   

    mysql_data_send(sql, val)




def main():
    model = LudwigModel.load('./results/experiment_run_5/model/')

    while True:
        gravar.gravarAudio(10, './prediction/gravacao.wav')

        threading.Thread(target=thread_prediction(model)).start()

if __name__ == '__main__':
    main()
        
    

    