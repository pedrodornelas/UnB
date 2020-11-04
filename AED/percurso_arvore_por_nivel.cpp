/*Tarefa 2 - Árvores
  Pedro Henrique Dornelas Almeida
  Matrícula: 18/0108140
  Uri: 1466 - Percurso em Árvore por Nível*/


#include<iostream>
#include<queue>
using namespace std;

class BSTNode {
  public:
    int el;            //Elemento inteiro do nó da árvore.
    BSTNode *left;     //Ponteiros para indicar os nós que estão a sua erquerda e direita.
    BSTNode *right;
    //Construtor
    BSTNode(){
      el=0;
      left=0;
      right=0;
    }
    BSTNode(int e, BSTNode *l=0, BSTNode *r=0){
      el = e ; left = l ; right = r;
    }
};

class BST {
  public:
    BSTNode *root;         //Raiz da árvore.
    //Construtor
    BST(){
      root=0;
    }
    //Destrutor
    ~BST(){
      clear();
    }

    //Métodos

    void clear() {
        clear(root);
        root = 0;
    }

    void clear(BSTNode*p) {
        if (p != 0) {
             clear(p->left);
             clear(p->right);
             delete p;
         }
    }

    void insert(int el){     //Função que insere elementos na árvore binária.
      BSTNode *p=root;
      BSTNode *prev=0;
      while(p!=0){        //Aqui encontramos o local em que o elemnto deverá ser adicionado.
        prev=p;
        if(el < p->el)
          p=p->left;
        else
          p=p->right;
      }
      if(root==0)            //Fazemos a inserção com base na busca que fizemos anteriormente.
        root = new BSTNode(el);
      else if( el < prev->el)           //Será adicionado a esquerda caso for menor que o nó pai,e a direita se for maior ou igual.
         prev->left = new BSTNode(el);
      else
        prev->right = new BSTNode(el);
    }

    void breadthFirst(){              //Função em que percorremos a árvore em largura, ou em nível.
      queue<BSTNode*> fila;           //É necessário uma fila para que conseguimos pegar todos os nós que estão no mesmo nível, na mesma altura,e em seguida seus consequentes filhos.
      BSTNode *p = root;
      if(p!=0){
        fila.push(p);
        while(!fila.empty()) {         //Enquanto não percorrermos toda a árore e mostramos seus elementos
          p=fila.front();
          fila.pop();
          if(p == root)
            cout<<p->el;
          else
            cout<<' '<<p->el;
          if(p->left != 0)             //Aqui pegamos todos os filhos do nó pai, e colocaos na fila, para que após isso, conseguiremos pegar seus filhos,
            fila.push(p->left);        //assim fazendo um percurso em nível.
          if(p->right != 0)
            fila.push(p->right);
        }
      }
    }
};

int main(){
  int n , x , y;   //n é o número de casos teste , x é o número de elementos na árvore , y é o elemento a ser adicionado.
  cin>>n;
  for(int i=1; i <= n; i++){
    BST arvore;
    cin>>x;                  //Algorítimo que permite ao usuário digitar os casos testes.
    for(int j=1; j <= x; j++){
      cin >> y;
      arvore.insert(y);             //Insere elementos na árvore
    }
    cout<<"Case "<< i <<":\n";
    arvore.breadthFirst();
    cout<<endl;
    cout<<endl;
  }
  return 0;
}
