import React, { useState, useEffect } from 'react'
import { View, Text, FlatList, Image} from 'react-native'
import { useNavigation } from '@react-navigation/native'

import styles from './styles'

import logoUnb from '../../assets/logoUnb.png'

export default function Matricula() {

    const navigation = useNavigation()
    const [materias, setMaterias] = useState([])

    function navigateToHome() {
        navigation.navigate('Home')
    }

    function navigateToDetalhe(materia) {
        navigation.navigate('MatriculaDetalhe', materia)
    }

    useEffect(() => {
        setMaterias(dados)
    }, [])

    const dados = [
        {
            codigo: 'MAT0025',
            nome: 'Cálculo 1',
            status: 'Pré-Matricula',
            data: '2020-03-01T12:00:03',
        },
        {
            codigo: 'MAT0026',
            nome: 'Cálculo 2',
            status: 'Pré-Matricula',
            data: '2020-03-01T12:00:03',
        },
        {
            codigo: 'MAT0027',
            nome: 'Cálculo 3',
            status: 'Pré-Matricula',
            data: '2020-03-01T12:00:03',
        },

    ]

    return (
        <View style={styles.container}>
            <Text style={styles.title}>Histórico de Matrícula</Text>
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
                keyExtractor={materia => materia.codigo}
                renderItem={({ item: materia }) => (
                    <View style={styles.objeto}>
                        <Text style={styles.text_objeto}>{materia.codigo} - {materia.nome}</Text>
                        <Text style={styles.textStatus}>{materia.status} em {materia.data}</Text>
                    </View>
                )}
            />

        </View>
    )
}