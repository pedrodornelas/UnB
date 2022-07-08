import { StyleSheet } from 'react-native'
import Constants from 'expo-constants'

export default StyleSheet.create({
    container: {
        flex: 1,
        backgroundColor: '#D9E2EA',
        paddingHorizontal: 24,
        justifyContent: 'center',
        alignItems: 'center'
    },

    titulo:{
        fontWeight: 'bold',
        marginBottom: 28
    },

    inputBox:{
        height: 50,
        width: '75%',
        paddingHorizontal: 20,
        borderWidth: 1,
        borderRadius: 10,
        marginBottom: 20
    },

    entrar:{
        backgroundColor: '#11283A',
        color: '#ffffff',
        paddingHorizontal: 20,
        borderRadius: 10,
        paddingVertical: 8,
        width:'40%',
        alignItems: 'center'
    },

    entrarText:{
        color: '#fff'
    }

})