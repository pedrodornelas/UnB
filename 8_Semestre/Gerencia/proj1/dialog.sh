#!/bin/bash
#
# As funcoes devem ser declaradas antes da chamada principal do Dialog

#declaracao da função config_VM1()
#
# config_VM1(){
#     dialog --title  'Configuracao Manual das Interface de Redes' \
#            --menu   'Escolhe uma Interface' \
#                     0 0 0 \
#                     enp0s3 'Interface n. 1' \
#                     enp0s8 'Interface n. 2' \
#                     SAIR '' 2> /tmp/opcao
#                     opt=$(cat /tmp/opcao)
#                         case $opt in
#                         "enp0s3")   sudo ip a flush $(opt /tmp/opcao)
#                                     dialog --backtitle "Configuracao enp0s3" \
#                                            --inputbox "Digitar o IP (x.x.x.x/y):" -1 -1 '' \
#                                     2> /tmp/enp0s8
#                                     sudo ip a add $(cat /tmp/enp0s8) dev $(cat /tmp/opcao)
#                                     sudo ip a show $(cat /tmp/opcao) > /tmp/opcao2
#                                     dialog --title 'Configuracao realizada' --textbox /tmp/opcao2 22 70
#                                     config_VM1
#                                     ;;
#                         "SAIR")
#                         break
#                         ;;
#                         *) echo Opcao Invalida
#                     esac
#            clear
# }

config_VM1() {
       variable=$1
       dialog --title 'Tela de Controle da VM1' \
              --menu 'Escolha uma opcao' \
              0 0 0 \
              AUTOIP 'Configuracao Automatica de TCP/IP - Script' \
              IP 'Configuracao Manual de TCP/IP' \
              PROC 'Listar e Matar Processos' \
              CONF 'Listar Configuracoes' \
              CRON 'Configurar Crontab' \
              VOLTAR '' 2>/tmp/opcao
       opt=$(cat /tmp/opcao)
       case $opt in
              "AUTOIP")
                     sudo ip a flush $(opt /tmp/opcao)
                     dialog --backtitle "Configuracao enp0s3" \
                            --inputbox "Digitar o IP (x.x.x.x/y):" -1 -1 '' \
                            2>/tmp/enp0s8
                     sudo ip a add $(cat /tmp/enp0s8) dev $(cat /tmp/opcao)
                     sudo ip a show $(cat /tmp/opcao) >/tmp/opcao2
                     dialog --title 'Configuracao realizada' --textbox /tmp/opcao2 22 70
                     config_VM1
                     ;;
              'IP') tcp_ip_manual_VM1 ;;
              "VOLTAR") main ;;
              *) echo Opcao Invalida ;;
       esac
       clear
       main
}

tcp_ip_manual_VM1() {
       dialog --title 'Configuracao Manual TCP/IP VM2' \
              --menu 'Escolha uma interface:' \
              0 0 0 \
              ETH0 'Interface ethernet 0' \
              ETH1 'Interface ethernet 1' \
              ETH2 'Interface ethernet 2' \
              ROUTE 'Default Gateway e Roteamento' \
              DNS 'Name Server' \
              VOLTAR '' 2>/tmp/tcp_ip_manual
       opt=$(cat /tmp/tcp_ip_manual)
       case $opt in
              'VOLTAR') config_VM1 ;;
              *) echo Opcao Invalida ;;
       esac
       clear
       main
}

snmpwalk() {
       name=$1
       ip=$2
       #echo "$name - $ip" > /tmp/snmpwalk
       sudo snmpwalk -v2c -c grs $ip 1.3.6.1.2.1.2.1.0 >/tmp/snmpwalk
       dialog --title "SNMPWALK $name - $ip" \
              --msgbox "$(cat /tmp/snmpwalk)" 20 70
       clear
       main
}

snmpget() {
       name=$1
       ip=$2
       sudo snmpwalk -v2c -c grs $ip 1.3.6.1.2.1.2.1.0 >/tmp/snmpget
       dialog --title "SNMPGET $name - $ip" \
              --msgbox "$(cat /tmp/snmpget)" 20 70
       clear
       main
}

config_Router() {
       name=$1
       ip=$2
       dialog --title "Informacoes Router $name - $ip" \
              --menu 'Selecione uma Opcao' \
              0 0 0 \
              SNMPWALK '' \
              SNMPGET '' \
              SNMPGETNEXT '' \
              SNMPSET '' \
              VOLTAR '' 2>/tmp/snmp
       opt=$(cat /tmp/snmp)
       case $opt in
              'SNMPWALK') snmpwalk $name $ip ;;
              'SNMPGET') snmpget $name $ip ;;
              'SNMPGETNEXT') snmpgetnext $name $ip ;;
              'SNMPSET') snmpset $name $ip ;;
              'VOLTAR') main ;;
              *) echo Opcao Invalida ;;
       esac
       clear
}

main() {
       dialog --title 'Selecao da VM a ser Configurada' \
              --menu 'Selecione uma opcao' \
              0 0 0 \
              VM1 'Maquina Virtual 1' \
              R1 'Router R1' \
              R2 'Router R2' \
              R3 'Router R3' \
              SAIR '' 2>/tmp/escolha_vm
       opt=$(cat /tmp/escolha_vm)
       case $opt in
              "VM1") config_VM1 ;;
              "R1") config_Router "R1" "192.168.15.33" ;;
              "R2") config_Router "R2" "192.168.15.1" ;;
              "R3") config_Router "R3" "192.168.15.46" ;;
              "SAIR") break ;;
              *) echo Opcao Invalida ;;
       esac
       clear
}

main
