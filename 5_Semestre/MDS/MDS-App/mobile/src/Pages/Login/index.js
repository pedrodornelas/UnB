import React, { useState } from 'react'
import { View, Text, TouchableOpacity, Alert} from 'react-native'
import { useNavigation } from '@react-navigation/native'

import styles from './styles'
import { TextInput } from 'react-native-gesture-handler'

export default function Login(){
    const [mat, setMat] = useState(null)
    const [senha, setSenha] = useState(null)

    const navigation = useNavigation()

    function navigateToLogado(){
        navigation.navigate('Logado');
    }

    function autorizar(){
        if((mat == '180108042' || mat == '180108140' || mat=='1') && (senha=='123' || senha=='1')){
            navigateToLogado()
        }
        else{
            Alert.alert('Login Inválido')
        }
    }

    return(
        <View style={styles.container}>
            <Text style={styles.titulo}>AUTENTICAÇÃO</Text>
            <TextInput 
                style={styles.inputBox}
                placeholder='Matrícula'
                onChangeText={setMat}
                keyboardType='numeric'
            />
            <TextInput 
                style={styles.inputBox}
                placeholder='Senha'
                onChangeText={setSenha}
                secureTextEntry={true}
            />
            <TouchableOpacity onPress={autorizar} style={styles.entrar}><Text style={styles.entrarText}>Entrar</Text></TouchableOpacity>
        </View>
    )
}