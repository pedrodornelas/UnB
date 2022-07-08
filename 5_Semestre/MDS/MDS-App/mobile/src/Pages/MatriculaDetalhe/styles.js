import { StyleSheet } from 'react-native'
import Constants from 'expo-constants'

export default StyleSheet.create({
    container: {
        flex: 1,
        paddingHorizontal: 24,
        paddingTop: Constants.statusBarHeight + 40,
        backgroundColor: '#D9E2EA',
    },
    nomeBox:{
        width: '100%',
        flexDirection: 'row',
        marginBottom: 25,
        paddingBottom: 20,
        borderBottomWidth: 1,
        alignItems: 'center'
    },  
    nomeText: {
        fontSize: 20,
        fontWeight: 'bold',
        marginLeft: 15
    },
    horarioText:{
        marginBottom: 3
    },
    statusText:{
        marginTop: 70,
        fontSize: 18
    },
    botoes:{
        justifyContent: 'center',
        flex: 1,
        flexDirection: 'row',
        alignItems: 'flex-end',
        paddingBottom: '15%'
    },
    retirar:{
        backgroundColor: '#E43553',
        color: '#ffffff',
        paddingHorizontal: 20,
        borderRadius: 10,
        paddingVertical: 8,
        width:'40%',
        alignItems: 'center',
        marginLeft: 4
    },
    confirmar:{
        backgroundColor: '#349634',
        color: '#ffffff',
        paddingHorizontal: 20,
        borderRadius: 10,
        paddingVertical: 8,
        width:'40%',
        alignItems: 'center',
        marginRight: 4
    },
    botaoText:{
        color:'#fff'
    }
})