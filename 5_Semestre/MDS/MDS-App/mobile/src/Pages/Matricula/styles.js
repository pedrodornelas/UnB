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
    },
    box: {
        flexDirection: 'row',
        alignItems: 'center',
        marginTop: 15
    },
    logo: {
        width: 70,
        height: 70,
        marginRight: 20,
        borderRadius: 35
    },
    inputBox: {
        marginTop: 20,
        borderWidth: 1,
        borderRadius: 10,
        width: '100%',
        paddingVertical: 8,
        paddingHorizontal: 8,
        alignItems: 'center',
        flexDirection: 'row',
    },
    input: {
        marginLeft: 8,
    },
    lista: {
        //justifyContent: 'center',
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
        fontSize: 14,
        marginBottom: 10
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
    titleBox:{
        flexDirection: 'row',
        alignItems: 'center',
        justifyContent: 'space-between'
    },

///////////// Modal ///////////////////
    modalContainer:{
        flex: 1,
        backgroundColor: '#D9E2EA',
        paddingHorizontal: 24,
        paddingTop: Constants.statusBarHeight + 20
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
    retirarModal:{
        backgroundColor: '#E43553',
        color: '#ffffff',
        paddingHorizontal: 20,
        borderRadius: 10,
        paddingVertical: 8,
        width:'40%',
        alignItems: 'center',
        marginLeft: 4
    },
    confirmarModal:{
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