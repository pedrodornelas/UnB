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
        alignItems: 'center',
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
        alignItems: 'center',
    },
    text_objeto: {
        marginVertical: 25,
        fontSize: 20
    },
})