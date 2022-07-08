#!/bin/bash

choose() {

escolha=$( dialog --stdout --menu 'Configuracao de Rede:' 0 0 0 IP 'Defina o IP da maquina' GW 'Defina o gateway da rede' SHOW 'Mostrar as configuracoes de rede' QUIT 'Sair' )

case $escolha in
"IP")
config_ip
;;
"GW")
config_gw
;;
"SHOW")
show_ip
;;
"QUIT")
break
;;
*) echo Opcao Invalida
esac
clear

}

config_ip() {

ip=$( dialog --stdout --inputbox 'Digite o IP no seguinte formato (x.x.x.x/y):' 0 0 )
ifconfig $interface $ip

dialog                                            \
   --title 'Configuracao realizada com sucesso'                             \
   --msgbox 'Aperte Enter para voltar ao menu'  \
   6 40
choose

}

config_gw() {

gw=$( dialog --stdout --inputbox 'Digite o IP do gateway no seguinte formato (x.x.x.x):' 0 0 )
route add default gw $gw

dialog                                            \
   --title 'Configuracao realizada com sucesso'                             \
   --msgbox 'Aperte Enter para voltar ao menu'  \
   6 40
choose

}

show_ip() {

ip=$(ifconfig | grep "Bcast" | cut -d ":" -f2 | cut -d " " -f1)

mask=$(ifconfig | grep "Bcast" | cut -d ":" -f4)

bcast=$(ifconfig | grep "Bcast" | cut -d ":" -f3 | cut -d " " -f1)

gw=$(route -n | grep 0.0.0.0 | cut -d " " -f10)

dialog --title "Configuracao de rede" --msgbox "IP: $ip \nMask: $mask \nBroadcast: $bcast \nGateway: $gw" 10 40

choose
}

dialog                                            \
   --title 'Bem Vindo a configuracao de rede'                             \
   --msgbox 'Aperte Enter para comecar.'  \
   6 40
choose