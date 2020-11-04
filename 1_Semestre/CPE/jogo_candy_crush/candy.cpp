#include"candy.h"
#include<windows.h>
#include<iostream>
#include<conio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<fstream>
#include<sstream>

using namespace std;

struct Rank{
	string nome;
	int pontua;
};

char gerador(char jogo[6][6]){
		srand(time(NULL));
		int numaux;	
	for(int l=0;l<6;l++){
		for(int c=0;c<6;c++){
			numaux=rand() %5 + 1;
			if(jogo[l][c]==' '){
				if(numaux==1)
					jogo[l][c]=157;
				if(numaux==2)
					jogo[l][c]=169;
				if(numaux==3)
					jogo[l][c]=190;
				if(numaux==4)
					jogo[l][c]=38;
				if(numaux==5)
					jogo[l][c]=207;
			}
		}
	}
	return jogo[6][6];
}

void ponteiro(int marc,int &x,int &y){
	if(marc==77){
		if(y+1==6)
			y=0;
		else 
			y=y+1;
	}
	if(marc==75){
		if(y-1==-1)
			y=5;
		else
			y=y-1;
	}
	if(marc==72){
		if(x-1==-1)
			x=5;
		else
			x=x-1;
	}
	if(marc==80){
		if(x+1==6)
			x=0;
		else
			x=x+1;
	}
	return;
}

void setcolor(WORD color){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	return;
}

void mostrajogo(int select,char a[6][6],int pos_x,int pos_y,int pontuacao, int objetivo,int num_jogadas,int aux){
	system("cls");
	if(num_jogadas==-1)
		cout<<"\n\n => Voce tem 1 min para atingir a meta.\n";
	else
		cout<<"\n\n => Voce tem "<<num_jogadas<<" jogadas para atingir a meta.\n";
	cout<<"\t- Aperte ENTER para selecionar a peça que quer trocar. Em seguida onde quer trocar nas letras:\n";
	cout<<"\t- W-CIMA / A-ESQUERDA / S-BAIXO / D-DIREITA.\n";
	cout<<"\t- Caso queira sair e salvar seu progresso, tecle <Esc>.\n";
	cout<<"\t- Voce deve alcancar "<<objetivo<<" pontos.\n";
	for(int l=0;l<6;l++){
		cout<<"\n\t";
		for(int c=0;c<6;c++){
			if((l==pos_x)&&(c==pos_y)&&(select!=13)){
				setcolor(10);
				cout<<"|"<<a[l][c]<<"|";
				setcolor(15);
			}
			else if((l==pos_x)&&(c==pos_y)&&(select==13)){
				setcolor(6);
				cout<<"|"<<a[l][c]<<"|";
				setcolor(15);
			}
			else{
				setcolor(15);
				cout<<" "<<a[l][c]<<" ";
			}
		}
	}
	cout<<"\n\nPontuacao: "<<pontuacao<<endl;
	if(num_jogadas==-1);
	else
		cout<<"\nJogadas Restantes: "<<aux<<endl;
	return;
}

char seleciona(int marc, char jogo[6][6], int pos_x, int pos_y, int &aux){
	char adc;
	if(marc==100){//(Direita)
		if(pos_y+1==6);
		else{
			if( ((jogo[pos_x][pos_y]==jogo[pos_x][pos_y+2]) && (jogo[pos_x][pos_y]==jogo[pos_x][pos_y+3])) ||
			   ((jogo[pos_x][pos_y]==jogo[pos_x-1][pos_y+1]) && ((jogo[pos_x][pos_y]==jogo[pos_x-2][pos_y+1]) ||
			   (jogo[pos_x][pos_y]==jogo[pos_x+1][pos_y+1]))) || ((jogo[pos_x][pos_y]==jogo[pos_x+1][pos_y+1]) &&
			   (jogo[pos_x][pos_y]==jogo[pos_x+2][pos_y+1])) ){
				//troca
				adc=jogo[pos_x][pos_y];
				jogo[pos_x][pos_y]=jogo[pos_x][pos_y + 1];
				jogo[pos_x][pos_y + 1]=adc;
				aux--;
			}
			else{
				cout<<"\n\nJogada Invalida.Tente novamente.\n";
				system("pause");
			}
		}
	}
	if(marc==119){      //(Cima)
		if(pos_x-1==-1);
		else{
			if( ((jogo[pos_x][pos_y]==jogo[pos_x-2][pos_y]) && (jogo[pos_x][pos_y]==jogo[pos_x-3][pos_y])) ||
			   ((jogo[pos_x][pos_y]==jogo[pos_x-1][pos_y+1]) && ((jogo[pos_x][pos_y]==jogo[pos_x-1][pos_y+2]) ||
			   (jogo[pos_x][pos_y]==jogo[pos_x-1][pos_y-1] ))) || ((jogo[pos_x][pos_y]==jogo[pos_x-1][pos_y-1]) &&
			   (jogo[pos_x][pos_y]==jogo[pos_x-1][pos_y-2])) ){
				//troca
				adc=jogo[pos_x][pos_y];
				jogo[pos_x][pos_y]=jogo[pos_x - 1][pos_y];
				jogo[pos_x - 1][pos_y]=adc;
				aux--;
			}
			else{
				cout<<"\n\nJogada Invalida.Tente novamente.\n";
				system("pause");
			}
		}
	}
	if(marc==115){//(Baixo)
		if(pos_x+1==6);
		else{
			if(((jogo[pos_x][pos_y]==jogo[pos_x+2][pos_y]) && (jogo[pos_x][pos_y]==jogo[pos_x+3][pos_y])) || 
			((jogo[pos_x][pos_y]==jogo[pos_x+1][pos_y+1]) && ((jogo[pos_x][pos_y]==jogo[pos_x+1][pos_y+2]) || 
			(jogo[pos_x][pos_y]==jogo[pos_x+1][pos_y-1]))) || ((jogo[pos_x][pos_y]==jogo[pos_x+1][pos_y-1]) && 
			(jogo[pos_x][pos_y]==jogo[pos_x+1][pos_y-2]))){
				//troca
				adc=jogo[pos_x][pos_y];
				jogo[pos_x][pos_y]=jogo[pos_x + 1][pos_y];
				jogo[pos_x + 1][pos_y]=adc;
				aux--;
			}
			else{
				cout<<"\n\nJogada Invalida.Tente novamente.\n";
				system("pause");
			}
		}
	}
	if(marc==97){//(Esquerda)
		if(pos_y-1==-1);
		else{
			if(((jogo[pos_x][pos_y]==jogo[pos_x][pos_y-2]) && (jogo[pos_x][pos_y]==jogo[pos_x][pos_y-3])) || 
			((jogo[pos_x][pos_y]==jogo[pos_x+1][pos_y-1]) && ((jogo[pos_x][pos_y]==jogo[pos_x+2][pos_y-1]) || 
			(jogo[pos_x][pos_y]==jogo[pos_x-1][pos_y-1]))) || ((jogo[pos_x][pos_y]==jogo[pos_x-1][pos_y-1]) && 
			(jogo[pos_x][pos_y]==jogo[pos_x-2][pos_y-1])) ){
				//troca
				adc=jogo[pos_x][pos_y];
				jogo[pos_x][pos_y]=jogo[pos_x][pos_y - 1];
				jogo[pos_x][pos_y - 1]=adc;
				aux--;
			}
			else{
				cout<<"\n\nJogada Invalida.Tente novamente.\n";
				system("pause");
			}
		}
	}
	return jogo[6][6];
}

char apaga(char jogo[6][6],int &pontuacao){
	for(int l=0;l<6;l++){
		for(int c=0;c<6;c++){
			if((c<=3)&&(jogo[l][c]!=' ')&&(jogo[l][c]==jogo[l][c+1])&&(jogo[l][c]==jogo[l][c+2])){ //apaga trinca em linha.
				jogo[l][c]=' ';
				jogo[l][c+1]=' ';
				jogo[l][c+2]=' ';
				pontuacao=pontuacao+3;				
			}
			else if((l<=3)&&(jogo[l][c]!=' ')&&(jogo[l][c]==jogo[l+1][c])&&(jogo[l][c]==jogo[l+2][c])){ //apaga trinca em coluna.
				jogo[l][c]=' ';
				jogo[l+1][c]=' ';
				jogo[l+2][c]=' ';
				pontuacao=pontuacao+3;
			}
		}
	}
	return jogo[6][6];
}

char desce_elementos(char jogo[6][6]){
	for(int l=1;l<6;l++){
		for(int c=0;c<6;c++){

			if((jogo[l][c]==' ')&&(jogo[l-1][c]!=' ')){
				jogo[l][c]=jogo[l-1][c];
				jogo[l-1][c]=' ';
				l=1;
				c=-1;

			}
		}
	}
	return jogo[6][6];
}

void menu(int &objetivo, int &num_jogadas,int &comando,int &comando1, string &player, vector<Rank>ranqs){
	system("cls");
	vector<Rank>::iterator pessoas;
	cout<<"\n\n Menu do jogo: \n";
	cout<<"\t1- Ver Scores.\n";
	cout<<"\t2- Ir para o jogo\n";
	
	while(1){
		comando=getch();
		if(comando==49){
			for(pessoas=ranqs.begin();pessoas!=ranqs.end();pessoas++)
				cout<<pessoas->nome<<", "<<pessoas->pontua<<" pontos."<<endl;
			return;
		}
		if(comando==50){
			string nada;
			system("cls");
			cout<<"\n\n Por gentileza, digite o nome do Player: \n";
			fflush(stdin);
			getline(cin,player);
			system("cls");
			cout<<"\n\n Menu do jogo: \n";
			cout<<"\tEscolha o nivel: \n";
			cout<<"\t  1.Easy.\n";
			cout<<"\t  2.Medium\n";
			cout<<"\t  3.Hard\n";
			cout<<"\t Digite a opcao que desejar.";
			fflush(stdin);
			comando1=getch();
			if(comando1==49){
				objetivo=35;
				num_jogadas=10;
			}
			if(comando1==50){
				objetivo=45;
				num_jogadas=8;
			}
			return;
		}
	}
	return;
}
void salvadados(vector<Rank> ranqs){
	vector<Rank>::iterator pessoa;
	ofstream arquivo("Score.txt");
	if(arquivo.is_open()){
		for(pessoa=ranqs.begin();pessoa!=ranqs.end();pessoa++){
			arquivo<<pessoa->nome<<"*"<<pessoa->pontua<<endl;
		}
	arquivo.close();
	}
	return;
}
void le_dados(vector<Rank> &ranqs){
	Rank ranq;
	ifstream meu_arquivo("Score.txt");
	if(meu_arquivo.is_open()){
		
		size_t pos=0;
		string linha,parte,delimitador="*";		
		int aux;
		while(! meu_arquivo.eof()){
			
			getline(meu_arquivo,linha);
			
			while((pos = linha.find(delimitador)) != std::string::npos){
				parte = linha.substr(0,pos);
				ranq.nome=parte;
				linha.erase(0,pos+delimitador.length());
			}
			stringstream ss;
			ss<<linha;
			ss>>aux;
			ranq.pontua=aux;
			ranqs.push_back(ranq);
		}
	}
	meu_arquivo.close();
	ranqs.pop_back();
	return;
}

void ordena(vector<Rank> &ranqs){
	Rank ranq;
	int aux1,aux2;
	vector<Rank>::iterator it1;
	vector<Rank>::iterator it2;
	for(it1=ranqs.begin();it1!=ranqs.end()-1;it1++){
		if(ranqs.size()>2){
			it2=it1+1;
			it1->pontua=aux1;
			it2->pontua=aux2;
			cout<<aux1<<endl<<aux2<<endl;
			system("pause");
			if(aux2>aux1){
				ranq.nome=it2->nome;
				ranq.pontua=it2->pontua;
				ranqs.erase(it2);
				ranqs.insert(it1,ranq);
				it1=ranqs.begin();
			}
		}
	}
	return;
}
