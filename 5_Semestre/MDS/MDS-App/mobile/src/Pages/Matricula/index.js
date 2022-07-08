import React, { useState, useEffect } from 'react'
import { View, Text, TouchableOpacity, FlatList, Image} from 'react-native'
import { useNavigation, useIsFocused } from '@react-navigation/native'
import AsyncStorage from '@react-native-async-storage/async-storage';
import { Ionicons } from '@expo/vector-icons'

import styles from './styles'

import logoUnb from '../../assets/logoUnb.png'

import dados from '../../data/materiasAluno.json'
import materiasAll from '../../data/materias.json'

export default function Matricula() {

    const navigation = useNavigation()

    const [materias, setMaterias] = useState([])
    const [change, setChange] = useState(false)

    const focus = useIsFocused()

    useEffect(() => {
        setMaterias(dados)
        storeData(null)
    }, [])

    useEffect(() => {
        if(focus){
            getData(materias)
        }
    }, [focus])


    function setNewMaterias(m, data){
        let newMaterias = m
        let newStatus

        //console.log(data.status);
        if(data.status == 'confirmar'){
            newStatus = 'Confirmar'
        }
        else if(data.status == 'retirar'){
            newStatus = 'Retirar'
        }
        else if(data.status == 'matricular'){
            newStatus = 'Solicitar'
        }

        let aux = 0

        for (let i = 0; i < newMaterias.length; i++) {
            if(newMaterias[i].codigo == data.codigo && newMaterias[i].turma.codigo == data.codigoTurma){
                newMaterias[i].status = newStatus
                aux = 1
            } 
        }
        
        if(aux == 0){
            let i=0, encontrou=false
            while(encontrou == false || i < materiasAll.length){
                if(materiasAll[i].codigo == data.codigo){
                    for(let j=0 ; j<materiasAll[i].turmas.length; j++){
                        if(materiasAll[i].turmas[j].codigo == data.codigoTurma){
                            let newMateria = {
                                codigo: materiasAll[i].codigo,
                                nome: materiasAll[i].nome,
                                status: newStatus,
                                turma: materiasAll[i].turmas[j],
                                prioridade: data.prioridade
                            }
                            newMaterias.push(newMateria)
                            encontrou = true
                        }
                    }
                }
                i+=1
            }
        }

        setMaterias([])
        setMaterias(newMaterias)
    }

    const getData = async (m) => {
        //console.log(materias);
        let data
        try {
            const jsonValue = await AsyncStorage.getItem('@storage_Key')
            data = jsonValue != null ? JSON.parse(jsonValue) : null;
            if(m.length > 0 && data !== null){
                storeData(null)
                setNewMaterias(m, data)
            }
        } catch(e) {
          console.log(e);
        }
    }

    const storeData = async (value) => {
        try {
            const jsonValue = JSON.stringify(value)
            await AsyncStorage.setItem('@storage_Key', jsonValue)
        } catch(e) {
            // saving error
        }
    }

    function navigateToHome() {
        navigation.navigate('Home')
    }

    function navigateToDetalhe(materia) {
         navigation.navigate('MatriculaDetalhe', materia)
    }

    function confirmar(){
        let confirmarMaterias = materias
        for (let i = 0; i < materias.length; i++) {
            //console.log(confirmarMaterias[i].status);
            if(confirmarMaterias[i].status == 'Retirar'){
                confirmarMaterias.splice(i,1)
                i -= 1
            }
            else if(confirmarMaterias[i].status == 'Confirmar'){
                confirmarMaterias[i].status = 'Confirmado'
            }
            else if(confirmarMaterias[i].status == 'Solicitar'){
                confirmarMaterias[i].status = 'Solicitado'
            }
        }

        setChange(!change)
        setMaterias(confirmarMaterias)
    }

    function verificaPrioridade(element){
        if(element.prioridade){
            return (" - Prioridade: "+element.prioridade)
        }
    }

    return (
        <View style={styles.container}>
            <View style={styles.titleBox}>
                <Text style={styles.title}>Matrícula - 2021/1</Text>
                <Ionicons name='log-out' size={30} onPress={navigateToHome}/>
            </View>
            <View style={styles.box}>
                <Image source={logoUnb} style={styles.logo} />
                <View>
                    <Text>180108042</Text>
                    <Text>Pedro Duarte Alvim</Text>
                </View>
            </View>

            <FlatList
                style={styles.lista}
                data={materias}
                keyExtractor={materia => materia.codigo+materia.turma.codigo}
                renderItem={({ item: materia }) => (
                    <TouchableOpacity onPress={() => {navigateToDetalhe(materia)}} style={styles.objeto}>
                        <Text style={styles.text_objeto}>{materia.codigo} - {materia.nome} - {materia.turma.codigo}</Text>
                        <Text style={styles.textStatus}>{materia.status}{verificaPrioridade(materia)}</Text>
                    </TouchableOpacity>
                )}
            />
            <View style={styles.botaoConfirmar}>
                <TouchableOpacity onPress={confirmar} style={styles.confirmar}><Text style={styles.botaoText}>Confirmar</Text></TouchableOpacity>
            </View>
        </View>
    )
}