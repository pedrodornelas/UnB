import React, { useEffect, useState } from 'react'
import { View, Text, FlatList, Alert, Modal, TouchableOpacity, TextInput } from 'react-native'
import { useNavigation, useRoute } from '@react-navigation/native'
import { Ionicons } from '@expo/vector-icons'
import AsyncStorage from '@react-native-async-storage/async-storage'

import styles from './styles'

export default function Turmas(){

    const route = useRoute()
    const navigation = useNavigation()

    const [disciplina, setDisciplina] = useState({})
    const [modalVisible, setModalVisible] = useState(false)
    const [codigoDisciplina, setCodigoDisciplina] = useState('')
    const [nomeDisciplina, setNomeDisciplina] = useState('')    
    const [materia, setMateria] = useState({})
    const [prioridade, setPrioridade] = useState('')

    useEffect(() => {
        const { disciplina } = route.params
        setDisciplina(disciplina)
    }, [])

    function usarModal(m, c, n){
        setMateria(m)
        setCodigoDisciplina(c)
        setNomeDisciplina(n)
        setModalVisible(true)
    }

    const storeData = async (value) => {
        try {
            const jsonValue = JSON.stringify(value)
            await AsyncStorage.setItem('@storage_Key', jsonValue)
        } catch(e) {
            // saving error
        }
    }

    async function matricular(){
        let prioridadeInt = parseInt(prioridade)
        //console.log(typeof(prioridadeInt));
        if(prioridade.length == 0 || typeof(prioridadeInt) != 'number' || prioridadeInt > 10 || prioridadeInt < 1){
            alert("Digite uma prioridade válida entre 1 e 10.")
        }
        else{
            await storeData({
                codigoTurma: materia.codigo,
                codigo: codigoDisciplina,
                status: 'matricular',
                pag: 'turmas',
                prioridade: prioridade,
            })
            navigation.navigate('Logado',{
                screen:'Matrícula',
            })
        }
    }

    function navigateToBack(){
        navigation.goBack()
    }

    return(
        <View style={styles.container}>
            <Modal
                animationType="slide"
                transparent={true}
                visible={modalVisible}
                onRequestClose={() => {
                    //Alert.alert("Modal has been closed.")
                    setModalVisible(!modalVisible)
                }}>
                <View style={styles.modalContainer}>
                    <View style={styles.nomeBox}>
                        <Ionicons name='arrow-back-outline' size={30} onPress={() => setModalVisible(false)}/>
                        <Text style={styles.nomeText}>{codigoDisciplina} - {nomeDisciplina} - {materia.codigo}</Text>
                    </View>

                    <TextInput 
                        style={styles.inputBox}
                        placeholder='Prioridade: 1 - 10'
                        onChangeText={setPrioridade}
                        keyboardType='numeric'
                    />

                    <View style={styles.botaoConfirmar}>
                        <TouchableOpacity 
                            onPress={() => matricular()}
                            style={styles.confirmar}>
                                <Text style={styles.botaoText}>Confirmar</Text>
                        </TouchableOpacity>
                    </View>
                </View>
            </Modal>
            
            <View style={styles.titleBox}>
                <Ionicons name='arrow-back-outline' size={30} onPress={navigateToBack}/>
                <Text style={styles.title}>Turmas</Text>
            </View>

            <FlatList
                style={styles.lista}
                data={disciplina.turmas}
                keyExtractor={turma => turma.codigo}
                renderItem={({ item: turma }) => (
                    <TouchableOpacity onPress={() => usarModal(turma, disciplina.codigo, disciplina.nome)} style={styles.objeto}>
                        <Text style={styles.text_objeto}>{disciplina.codigo} - {disciplina.nome} - {turma.codigo}</Text>
                        {turma.horarioAula.map(element =>
                            <Text key={element.dia+element.hora} style={styles.textStatus}> {element.dia}: {element.hora}</Text>
                        )}
                        <Text style={styles.textStatus}> Professores: </Text>
                        {turma.professor.map(element =>
                            <Text key={element.nome} style={styles.textStatus}>      - {element.nome}</Text>
                        )}
                        <Text style={styles.textStatus}> Vagas ofertadas: {turma.numeroVagas}</Text>
                        <Text style={styles.textMatriculadas}> Vagas matriculadas: {turma.numeroMatriculas}</Text>
                    </TouchableOpacity>
                )}
            />
        </View>
    )
}