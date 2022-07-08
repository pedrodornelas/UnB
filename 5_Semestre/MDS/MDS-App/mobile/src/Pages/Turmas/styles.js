import { StyleSheet } from 'react-native'
import Constants from 'expo-constants'

export default StyleSheet.create({
    container: {
        flex: 1,
        paddingHorizontal: 24,
        paddingTop: Constants.statusBarHeight + 20,
        backgroundColor: '#D9E2EA',
    },
    title: {
        fontSize: 30,
        fontWeight: 'bold',
        marginLeft: 8,
    },
    objeto: {
        //marginVertical: 25,
        borderBottomWidth: 1,
        alignItems: 'flex-start',
    },
    text_objeto: {
        marginTop: 25,
        marginBottom: 15,
        fontSize: 18,
        fontWeight: 'bold',
    },
    textStatus: {
        opacity: 0.8,
        fontSize: 14,
    },
    textMatriculadas: {
        opacity: 0.8,
        fontSize: 14,
        marginBottom: 8
    },
    modalContainer:{
        flex: 1,
        backgroundColor: '#D9E2EA',
        paddingHorizontal: 24,
        paddingTop: Constants.statusBarHeight + 20,
        alignItems: 'center',
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
    botaoConfirmar:{
        marginBottom: '10%',
        justifyContent: 'center',
        alignItems: 'center',
        marginTop: '6%'
    },
    confirmar:{
        backgroundColor: '#11283A',
        color: '#ffffff',
        paddingHorizontal: 20,
        borderRadius: 10,
        paddingVertical: 8,
        width:'40%',
        alignItems: 'center',
        marginRight: 4
    },
    botaoText:{
        color: '#fff'
    },
    horarioText:{
        marginBottom: 3
    },
    inputBox:{
        height: 50,
        width: '75%',
        paddingHorizontal: 20,
        borderWidth: 1,
        borderRadius: 10,
        marginBottom: 20
    },
    titleBox:{
        flexDirection: 'row',
        alignItems: 'center'
    }
})