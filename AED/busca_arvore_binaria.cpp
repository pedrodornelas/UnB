/*Programa Uri - Árvore
  Pedro Henrique Dornelas Almeida
  Matrícula: 18/0108140 
  Uri: 1195 - Árvore Binária de Busca*/

#include<iostream>
using namespace std;

class BSTNode {
  public:
    int el;               //Elemento inteiro do nó da árvore.
    BSTNode *left;        //Ponteiros para indicar os nós que estão a sua esquerda e a sua direita
    BSTNode *right;
    BSTNode(){
      left = right = 0;
    }
    BSTNode(int e, BSTNode *l=0, BSTNode *r=0){
      el=e;
      left=l;
      right=r;
    }
};

class BST {
  public:
    BSTNode *root;         //Raiz da árvore
    //Construtor
    BST(){
      root=0;
    }
    //Destrutor
    ~BST(){
      clear();
    }

    //Métodos     -    É necessário a criação dessas funções que chamam outra, para que comece da raiz e sejam recursivas depois,
    // pois se fizermos somente uma função, teríamos que passar a raiz como parâmetro, para isso fizemos uma função que realiza esta ação.

    void clear() {        //Limpa árvore a partir da raiz.
        clear(root);
        root = 0;
    }
    void inorder(){       //Função que percorre a árvore em ordem.
      inorder(root);
    }
    void preorder(){      //FUnção que percorre a árvore pré-ordem.
      preorder(root);
    }
    void postorder(){     //Função que percorre a árvore pós-ordem.
      postorder(root);
    }
    void visit(BSTNode *p){
      cout <<' '<< p->el;
    }

    void clear(BSTNode*p) {      //Função para limpar a árvore implementada recursivamente a partir de um ponteiro de alguma posição.
        if (p != 0) {
             clear(p->left);      //Chamadas recursivas para todos os nós.
             clear(p->right);
             delete p;
         }
    }

    void insert(int el){          //Função para inserir elementos na árvore.
      BSTNode *p =root;
      BSTNode *prev = 0;
      while (p!=0){         //Encontra o nó em que é para ser adicinado o elemento.
        prev = p;
        if( el < p->el )
          p = p->left;
        else
          p = p->right;
      }
      if(root == 0)           //Quando não tem nenhum elemento na árvore, o elemento a ser adiconado é a própria raiz.
        root = new BSTNode(el);
      else if(el < prev->el)              //Quando o elemento é menor que o nó, ele será adiconado no lado esquerdo.
        prev->left = new BSTNode(el);
      else           //Nos outros casos será adicionado a esquerda.
        prev->right = new BSTNode(el);
    }

    void inorder(BSTNode *p) {      //Primeiro visita a sub-árvore a esquerda, depois o nó atual, e por fim a sub-árvore a direita.
      if(p!=0){
        inorder(p->left);
        visit(p);
        inorder(p->right);
      }
    }

    void preorder(BSTNode *p) {     //Primeiro visita o nó atual, depois a sub-árvore a esquerda, e por fim a sub-árvore a direita.
      if(p!=0){
        visit(p);
        preorder(p->left);
        preorder(p->right);
      }
    }

    void postorder(BSTNode *p) {      //Primeiro visita a sub-árvore a esquerda, depois visita a sub-árvore a direita, e por fim o nó atual.
      if(p!=0){
        postorder(p->left);
        postorder(p->right);
        visit(p);
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
      cout<<"Pre.:";arvore.preorder();
      cout<<"\nIn..:";arvore.inorder();
      cout<<"\nPost:";arvore.postorder();
      cout<<endl<<endl;
    }
    return 0;
}
