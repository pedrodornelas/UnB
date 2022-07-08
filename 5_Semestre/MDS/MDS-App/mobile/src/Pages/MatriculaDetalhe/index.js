import React, {useEffect, useState} from 'react'
import { View, Text, TouchableOpacity } from 'react-native'
import { useNavigation, useRoute } from '@react-navigation/native'
import AsyncStorage from '@react-native-async-storage/async-storage'
import { Ionicons } from '@expo/vector-icons'

import styles from './styles'

export default function MatriculaDetalhe(){

    const navigation = useNavigation()
    const route = useRoute()

    const [codigo, setCodigo] = useState('')
    const [nome, setNome] = useState('')
    const [turma, setTurma] = useState({})
    const [horarioAula, setHorarioAula] = useState([])
    const [status, setStatus] = useState('')
    const [professor, setProfessor] = useState([])


    const storeData = async (value) => {
        try {
            const jsonValue = JSON.stringify(value)
            await AsyncStorage.setItem('@storage_Key', jsonValue)
        } catch(e) {
            // saving error
        }
    }

    useEffect(() => {
        const { codigo, nome, turma, status } = route.params
        codigo ? setCodigo(codigo) : setCodigo('')
        nome ? setNome(nome) : setNome('')
        turma ? setTurma(turma) : setTurma('')
        horarioAula ? setHorarioAula(turma.horarioAula) : setHorarioAula([])
        status ? setStatus(status) : setStatus('')
        professor ? setProfessor(turma.professor) : setProfessor([])
    }, [])

    async function navigateToMatricula(s){
        await storeData({
            codigo: codigo,
            codigoTurma: turma.codigo,
            status: s,
            pag: 'detalhe',
        })
        navigation.navigate('Logado',{
            screen:'Matrícula',
        })
    }

    function navigateToBack(){
        navigation.goBack()
    }

    function BotoesConfirmacao(){
        if(status=='Confirmar' || status=='Solicitar'){
            return(
                <View style={styles.botoes} key='a'>
                    <TouchableOpacity onPress={() => {navigateToMatricula('retirar')}} style={styles.retirar}><Text style={styles.botaoText}>Retirar</Text></TouchableOpacity>
                </View>
            )
        }
        else if(status=='Pré-Matricula'){
            return(
                <View style={styles.botoes} key='b'>
                    <TouchableOpacity onPress={() => {navigateToMatricula('confirmar')}} style={styles.confirmar}><Text style={styles.botaoText}>Confirmar</Text></TouchableOpacity>
                    <TouchableOpacity onPress={() => {navigateToMatricula('retirar')}} style={styles.retirar}><Text style={styles.botaoText}>Retirar</Text></TouchableOpacity>
                </View>
            )
        }
        else if(status == 'Retirar'){
            return(
                <View style={styles.botoes} key='a'>
                    <TouchableOpacity onPress={() => {navigateToMatricula('confirmar')}} style={styles.confirmar}><Text style={styles.botaoText}>Matricular</Text></TouchableOpacity>
                </View>
            )
        }
        else{
            return(<></>)
        }
    }

    return(
        <View style={styles.container}>
            <View style={styles.nomeBox}>
                <Ionicons name='arrow-back-outline' size={30} onPress={navigateToBack}/>
                <Text style={styles.nomeText}>{codigo} - {nome} - {turma.codigo}</Text>
            </View>

                    <View style={styles.objeto}>
                        <Text style={styles.textStatus}> Professores: </Text>
                        {professor.map(element =>
                            <Text key={element.nome} style={styles.textStatus}>      - {element.nome}</Text>
                        )}
                        <Text style={styles.textStatus}> Vagas ofertadas: {turma.numeroVagas}</Text>
                        <Text style={styles.textMatriculadas}> Vagas matriculadas: {turma.numeroMatriculas}</Text>
                    </View>
                    <Text>{"\n"}</Text>
            {horarioAula.map((h) => {
                return(
                    <Text style={styles.horarioText} key={h.dia}>{h.dia} {h.hora}</Text>
                )
            })}
            <Text style={styles.statusText}>Status: {status}</Text>
            <BotoesConfirmacao/>

        </View>
    )
}