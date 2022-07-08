import { Button, StyleSheet } from 'react-native'
import Constants from 'expo-constants'
import { withSafeAreaInsets } from 'react-native-safe-area-context'

export default StyleSheet.create({
    container: {
        flex: 1,
        //paddingHorizontal: 24,
        paddingTop: Constants.statusBarHeight,
        backgroundColor: '#D9E2EA',
    },
    image: {
        width: '100%',
        height: '100%',
        alignItems: 'center',
    },
    logo: {
        marginTop: '40%',
        width: 150,
        height: 150,
    },
    text: {
        fontSize: 24,
        fontWeight: 'bold',
        marginTop: '10%',
        textAlign: 'center',
        marginHorizontal: '10%'
    },
    text_button: {
        color: '#fff',
    },
    button: {
        marginTop: 20,
        width: '40%',
        paddingVertical: 8,
        paddingHorizontal: 20,
        backgroundColor: '#11283A',
        justifyContent: 'center',
        alignItems: 'center',
        borderRadius: 10,
    }
})