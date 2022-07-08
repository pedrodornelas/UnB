import React from 'react'

import { NavigationContainer } from '@react-navigation/native'
import { createStackNavigator } from '@react-navigation/stack'
import { createBottomTabNavigator } from '@react-navigation/bottom-tabs'

import { Ionicons } from '@expo/vector-icons';

import Home from './Pages/Home'
import Login from './Pages/Login'
import Matricula from './Pages/Matricula'
import ListaOferta from './Pages/ListaOferta'
import Historico from './Pages/Historico'
import MatriculaDetalhe from './Pages/MatriculaDetalhe'
import Turmas from './Pages/Turmas'

const Tab = createBottomTabNavigator()
const AppStack = createStackNavigator()

export default function Routes() {
    return (
        <NavigationContainer>

            <AppStack.Navigator screenOptions={{ headerShown: false }}>
                <AppStack.Screen name="Home" component={Home}/>
                <AppStack.Screen name="Login" component={Login}/>
                <AppStack.Screen name="Logado" component={TabNavigator}/>
                <AppStack.Screen name="MatriculaDetalhe" component={MatriculaDetalhe}/>
                <AppStack.Screen name="Turmas" component={Turmas}/>
            </AppStack.Navigator>

            

        </NavigationContainer>
    )

    
}

const TabNavigator = () => {
    return(
        <Tab.Navigator
        screenOptions={({ route }) => ({
            tabBarIcon: ({ focused, color, size }) => {
                let iconName

                if (route.name === 'Matrícula') {
                    iconName = 'list-outline'
                }
                else if (route.name === 'Lista de Oferta') {
                    iconName = 'search-outline'
                }
                else if (route.name === 'Histórico') {
                    iconName = 'calendar-outline'
                }
                
  
                return <Ionicons name={iconName} size={28} color={color} />;
            },
          })}
            tabBarOptions={{
                activeTintColor: 'blue',
                inactiveTintColor: 'gray',
                style:{
                    height:'7%',
                    paddingBottom: '1%'
                },
                keyboardHidesTabBar: true,
            }}
        
        >
            <Tab.Screen name="Matrícula" component={Matricula} />
            <Tab.Screen name="Lista de Oferta" component={ListaOferta} />
            <Tab.Screen name="Histórico" component={Historico} />
        </Tab.Navigator>
    )
}