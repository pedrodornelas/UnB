/*Tarefa 5 - Fila do recreio.
  Pedro Henrique Dornelas Almeida
  Data: 08/06/2019 
  Uri: 1548 - Fila do Recreio*/

#include<iostream>

using namespace std;

void Heapify(int* v, int p, int maxsize){       //Função para tranformar uma árvore em heap, porém, com alterações para
	int L= (2*p)+1;                               //transformar em uma heap em que o pai tem de ser menor que seus filhos.
	int R= (2*p)+2;                               //Posição dos seus filhos, esquerda dado por L, e direita dado  por R.
	int menor;

	if( L < maxsize && v[L] < v[p])             //Aqui commparamos o pai aos seus filhos,e pegamos a posição do menor deles.
		menor=L;
	else
		menor=p;

	if( R < maxsize && v[R] < v[menor])
		menor=R;

	if(menor!=p){                                 //Aqui fazemos a troca para transformar a árvore na heap em que desejamos, e após isso, chamamos a função novamente,
		int aux=v[p];                               //até que vire o heap que desejamos.
		v[p]=v[menor];
		v[menor]=aux;
		Heapify(v,menor,maxsize);
	}
}

void Build_Heap(int* v,int maxsize){          //Função para transformar em heap, a árvore "de baixo para cima", em que eu pego o último elemento que pode ter filhos
	for(int p = maxsize/2 ; p >= 0 ; p--)       //e vou os trasnformando em heaps.
		Heapify(v,p,maxsize);
}

void Heapsort(int* v,int maxsize){            //Função para ordenação em si de um array, baseado nos processos de heap em que fazemos, e trocas, até deixarmos nosso array
	Build_Heap(v,maxsize);                      //ordenado.
	for(int p=maxsize-1 ; p >=1 ;p--){
		int aux=v[p];
		v[p]=v[0];
		v[0]=aux;
		Heapify(v,0,p);
	}
}

int main(){
    int n , m , p ;   //n = números de casos teste , m = número de alunos na fila, p = notas dos alunos.
    cin >> n;
    for(int i=0 ; i < n ; i++){
      cin >> m;
      int fila[m];           //Fila de chegada dos alunos(notas).
      int ordenado[m];       //Array que será ordenado, de acordo com a proposta do exercício, em que o primeiro aluno tenha a melhor nota e o último a pior.
      for(int j=0 ; j < m ; j++){
        cin >> p;
        fila[j] = p;
        ordenado[j] = p;
      }
      Heapsort(ordenado,m);      //Chamamos a função para ordenar.
      int cont=0;
      for(int k=0; k < m ; k++){
        if(ordenado[k]==fila[k])     //Lógica para saber quantos alunos não tivemos de mexer na fila.
          cont++;
      }
      cout<<cont<<endl;
    }
    return 0;
}
