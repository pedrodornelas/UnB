import React, {useState, useEffect} from 'react'
import { View, Text, TextInput, TouchableOpacity, FlatList } from 'react-native'
import { useNavigation } from '@react-navigation/native'
import { Ionicons } from '@expo/vector-icons'

import dadosMaterias from '../../data/materias.json'

import styles from './styles'

export default function ListaOferta(){
    
    const [dados, setDados] = useState([])

    const [text, setText] = useState('')

    const [turmas, setTurmas] = useState([])

    const navigation = useNavigation()

    let consulta = []

    let texto, codigo, nome

    useEffect(() => {
        setDados(dadosMaterias)
    }, [])

    useEffect(() => {
        if(text.length > 0){
            dados.forEach(element => {
                texto = (text.normalize('NFD').replace(/[\u0300-\u036f]/g, "")).toLowerCase()
                codigo = (element.codigo.normalize('NFD').replace(/[\u0300-\u036f]/g, "")).toLowerCase()
                nome = (element.nome.normalize('NFD').replace(/[\u0300-\u036f]/g, "")).toLowerCase()
                if((codigo.indexOf(texto)>=0) || (nome.indexOf(texto)>=0)){
                    consulta.push(element)
                }
            })
        }
        setTurmas(consulta)
    }, [text])

    function navigateToTurmas(c){
        navigation.navigate('Turmas',{disciplina: c})
    }

    return(
        <View style={styles.container}>
            <Text style={styles.title}>Lista de Oferta</Text>
            <View style={styles.box}>
                <View style={styles.inputBox}>
                    <Ionicons name='search' size={20}/>
                    <TextInput 
                        style={styles.input}
                        placeholder='ex: "CÁL" ou "CÁLCULO 2"' 
                        onChangeText={setText}/>
               </View>
            </View>

            <FlatList 
                style={styles.lista}
                data={turmas}
                keyExtractor={turma => turma.codigo}
                renderItem={({item: turma}) => (
                <TouchableOpacity onPress={() => {navigateToTurmas(turma)}} style={styles.objeto}>
                    <Text style={styles.text_objeto}>{turma.codigo} - {turma.nome}</Text>
                </TouchableOpacity>
                )}
            />

        </View>
    )
}