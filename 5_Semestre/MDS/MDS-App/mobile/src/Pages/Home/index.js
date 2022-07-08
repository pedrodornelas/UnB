import React from 'react'
import { View, Text, TouchableOpacity, Image, ImageBackground } from 'react-native'
import { useNavigation } from '@react-navigation/native'
import logoUnb from '../../assets/logoUnb.png'
import background_img from '../../assets/background-unb.jpeg'

import styles from './styles'

export default function Home(){

    const navigation = useNavigation()

    function navigateToLogin(){
        navigation.navigate('Login');
    }

    return(
        <View style={styles.container}>
            <ImageBackground source={background_img} imageStyle={{opacity:0.4}} style={styles.image}>
                <Image source={logoUnb} style={styles.logo}/>
                <Text style={styles.text}>Bem vindo ao SIGAA! Identifique-se, por favor.</Text>
                <TouchableOpacity onPress={() => navigateToLogin()} style={styles.button}><Text style={styles.text_button}>Entrar</Text></TouchableOpacity>
            </ImageBackground>
        </View>
    )
}