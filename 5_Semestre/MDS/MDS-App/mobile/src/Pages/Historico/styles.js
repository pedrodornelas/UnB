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
    }
})