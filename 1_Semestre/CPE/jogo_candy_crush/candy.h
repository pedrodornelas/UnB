#include<windows.h>
#include<string.h>
#include<iostream>
#include<vector>
char gerador(char[6][6]);
void ponteiro(int, int&, int& );
void setcolor(WORD);
void mostrajogo(int, char [6][6], int, int, int, int, int, int);
char seleciona(int, char[6][6], int, int, int&);
char apaga(char[6][6],int&);
char desce_elementos(char[6][6]);
void menu(int &, int&,int&, int&, std::string&,std::vector<struct Rank>);
void salvadados(std::vector<struct Rank>);
void le_dados(std::vector<struct Rank>&);
void ordena(std::vector<struct Rank>&);
