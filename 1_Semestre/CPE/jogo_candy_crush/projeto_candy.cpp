/*Autores: Fabricio de Oliveira Barcelos 18/0119770
  Pedro Henrique Dornelas Almeida 18/0108140
  Projeto Final de CPE */

#include"candy.h"
#include<iostream>
#include<string.h>        
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<windows.h>
#include<Windows.h>
#include<vector>

using namespace std;

struct Rank{
	string nome;
	int pontua;
};

int main(){
	//setlocale(LC_ALL,"Portuguese");
	inicio:
	system("cls");
	Rank ranq;
	vector<Rank> ranqs;
	char jogo[6][6];
	int x,y,numaux,marcador,objetivo=0, pontuacao=0,num_jogadas=0,aux;
	int pos_x=0,pos_y=0;
	int jogada;
	char resposta;
	string player;
	for(int l=0;l<6;l++){
		for(int c=0;c<6;c++){
			jogo[l][c]=' ';
		}
	}
	
	le_dados(ranqs);
	
	//ordena(ranqs);
	
	cout<<"\n\n\t\t**********************************\n";
	cout<<"\n\n\t\t\tBem vindo ao jogo!!\n";
	cout<<"\n\n\t\t**********************************\n";
	meio:
	int pont;
	system("pause");
	
	int comando1,comando;
	
	menu(objetivo,num_jogadas,comando,comando1,player,ranqs);
	
	if(comando1==51){
		objetivo=75;
		num_jogadas=-1;
	}
	if(comando==49)
		goto meio;
	
	time_t tempo = time(NULL);
	string tempo2 = asctime(localtime(&tempo));	
	Sleep(1000);
	aux=num_jogadas;
	
	while(1){
		if(comando1==51){
			time_t tempo = time(NULL);
			string tempo3 = asctime(localtime(&tempo));
			if((tempo2[17]==tempo3[17])&&(tempo2[18]==tempo3[18])){
				ranq.nome=player;
				ranq.pontua=pontuacao;
				ranqs.push_back(ranq);
				salvadados(ranqs);
				cout<<"\nO tempo esgotou!\n";
				if(pontuacao>=objetivo){
					cout<<"Voce conseguiu, parabéns!!\nContinue a jogar para bater seus recordes e de outras pessoas!!\n";
					cout<<"Deseja jogar novamente?(s/n)\n";
					cin>>resposta;
					if(resposta=='s'){
						ranq.nome=player;
						ranq.pontua=pontuacao;
						ranqs.push_back(ranq);
						salvadados(ranqs);
						goto inicio;
					}
					else;
				}
				else{
					cout<<"Tente novamente! Voce falhou!\n";
					cout<<"Deseja jogar novamente?(s/n)\n";
					cin>>resposta;
					if(resposta=='s')
						goto inicio;
					else;
				}
				return 0;
			}	
		}
		gerador(jogo);
		setcolor(15);
		pont=getch();
		
		ponteiro(pont,pos_x,pos_y);
		
		if(pont==27){
			for(int i=0;i<1;i++){
				cout<<"\n\nSua pontuacao sera " << pontuacao << " , deseja realmente sair?(s/n)\n";
				cin>>resposta;
				if(resposta=='s'){
					ranq.nome=player;
					ranq.pontua=pontuacao;
					ranqs.push_back(ranq);
					salvadados(ranqs);
					return 0;
				}
				else;
			}		

		}
		if(pont==13){
			mostrajogo(pont,jogo,pos_x,pos_y,pontuacao,objetivo,num_jogadas,aux);
			
			jogada=getch();

			seleciona(jogada,jogo,pos_x,pos_y,aux);
			
			fflush(stdin);
		}
		apaga(jogo,pontuacao);
		
		desce_elementos(jogo);
		
		mostrajogo(pont,jogo,pos_x,pos_y,pontuacao,objetivo,num_jogadas,aux);
		
		if(aux==0){
			if(pontuacao<objetivo)
				cout<<"\nVoce nao atingiu a meta!!\n";
			else
				cout<<"\nParabens!!Voce conseguiu!!\nTente a proxima fase.\n";
			cout<<"Voce deseja tentar novamente?(s/n)\n";
			cin>>resposta;
			if(resposta=='s'){
				ranq.nome=player;
				ranq.pontua=pontuacao;
				ranqs.push_back(ranq);
				salvadados(ranqs);
				goto inicio;
			}
			else{
				ranq.nome=player;
				ranq.pontua=pontuacao;
				ranqs.push_back(ranq);
				salvadados(ranqs);
				return 0;
			}
		}
	}
	return 0;
}
