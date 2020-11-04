/*Pedro Henrique Dornelas Almeida
  Data: 13/06/2019
  Matrícula: 18/0108140  
  Uri: 1766 - O Elfo das Trevas*/

#include<iostream>
#include<string.h>
#include<vector>

using namespace std;

class Rena {              //Classe para criar os objetos Rena.
  private:
    //Atributos da Rena
    string nome;
    int peso;
    int idade;
    float altura;

  public:
    //Construtores
    Rena(){
      nome="";
      peso=0;
      idade=0;
      altura=0;
    }
    Rena(string S,int P,int I,float A){
      nome=S;
      peso=P;
      idade=I;
      altura=A;
    }

    //Funções para retornar os atributos da Rena.
    string getNome(){
      return nome;
    }
    int getPeso(){
      return peso;
    }
    int getIdade(){
      return idade;
    }
    float getAltura(){
      return altura;
    }
};

void ordenaRenas(vector<Rena> &Renas){                 //Algorítmo para ordenação do vetor de Renas de acordo com o exercício.
  int T = Renas.size();
  for(int i=0 ; i < T ; i++){             //Primeiro verificamos quem será candidato a ser o primeiro da lista das renas, verificado por 'maior'.
    Rena maior = Renas[i];
    int pos = i;
    for(int j = i + 1 ; j < T ; j++){         //A partir do elemento seguinte ao que dizemos ser o 'maior' verificamos a existência de outros candidatos
                                                         //atualizando a variável maior em todo o vetor.
      if(maior.getPeso() < Renas[j].getPeso()){         //Quando a Rena com maior peso não está na primeira posição do vetor, nós guardamos a variavel maior e sua posição
        maior = Renas[j];                               //no vetor.
        pos = j;
      }
      else if(maior.getPeso() == Renas[j].getPeso()){    //Quando os pesos das Renas são iguais.
        if(maior.getIdade() > Renas[j].getIdade()){      //Verificamos qual delas tem a menor idade, e guardamos seu valor e sua posição caso ocorra.
          maior=Renas[j];
          pos = j;
        }
        else if(maior.getIdade() == Renas[j].getIdade()){    //Quando o peso e a idade das Renas são iguais, verificamos quem tem a menor altura, e este será salvo e sua
          if(maior.getAltura() > Renas[j].getAltura()){      //posição também.
            maior=Renas[j];
            pos = j;
          }
          else if(maior.getAltura() == Renas[j].getAltura()){    //Quando os pesos são iguais, as idades e as alturas, então utilizamos a ordem alfabética dos nomes para
            if(maior.getNome() > Renas[j].getNome()){            //definir quem irá primeiro, guardamos em uma variável e sua posição.
              maior=Renas[j];
              pos = j;
            }
          }
        }
      }
      //Troca entre as renas.
      }
      if(pos != i){            //caso a posição que achamos seja diferente do primeiro elemento, devemos realizar a troca das Renas de lugar, até que todo o vetor
        Rena aux = Renas[i];   //esteja ordenado.
        Renas[i]=Renas[pos];
        Renas[pos]=aux;
      }
  }
}

int main(){

  int T;       //Números casos teste;
  cin>>T;

  for(int i=1 ; i<=T ; i++){
    vector<Rena> Renas;      //Lista de todas as Renas existentes no caso teste
    int N,M;  //N=número de Renas existentes , M=número de Renas a serem utilizadas no trenó.
    cin >> N >> M;
    for(int j=1 ; j<=N ; j++){

      string nome;
      int peso;
      int idade;
      float altura;

      cin >> nome >> peso >> idade >> altura;

      Rena rena(nome,peso,idade,altura);   //inicializando objeto Rena com os parâmetros digitados pelo usuário.
      Renas.push_back(rena);    //Adicionando a Rena a lista de Renas existentes
    }

    ordenaRenas(Renas);     //Função que ordena o vetor de objetos Rena.

    cout<<"CENARIO {"<< i << "}" << endl;        //casos teste
    for(int j=1 ; j <= M ; j++){
      cout << j << " - " << Renas[j-1].getNome() << endl;
    }
  }
  return 0;
}
