/* Pedro Henrique Dornelas Almeida
   Data: 11/07/2019
   Matrícula: 18/0108140
   Uri: 1148 - Países em Guerra*/

#include <iostream>
#include <map>
#include <set>
#include <cfloat>

using namespace std;

class Edge;

class Node{
public:
  Node(int label){
    this->label = label;
    this->adjacency = set<Edge *>();
  }

private:
  int label; //rotulo (identificador) do vertice
  set<Edge *> adjacency; //lista de vertices adjacentes
  friend class Graph;
};

class Edge{
public:
  Edge(Node *s, Node* f, double w){
    this->start = s;
    this->finish = f;
    this->weight = w;
  }

private:
  Node* start; //vertice de inicio da aresta
  Node *finish; //vertice de fim da aresta
  double weight; //peso da aresta do grafo
  friend class Graph;
};

class Graph{
public:
  Graph(bool directed){
    this->directed = directed;
    this->nodeMap = map<int, Node *>();
    this->nodes = set<Node *>();
    this->edges = set<Edge *>();
  }

  //adiciona um vertice a G
  void addNode(int name){
    Node *tmp = new Node(name);
    this->nodes.insert(tmp);
    this->nodeMap[name] = tmp;
  }
  //adiciona aresta entre vertices de rotulo label1 e label2
  void addEdge(int label1, int label2, double weight){

    Node *n1 = this->nodeMap[label1];//busca os dois vertices no mapa pelos seus labels
    Node *n2 = this->nodeMap[label2];


    for(Edge *arc : n2->adjacency){          //Verificar se está sendo criada uma aresta que liga 2 cidades no mesmo país.
      if( arc->finish == n1){                //Quando isso ocorrer, o peso entre elas deverá ser 0.
        weight=0;
        arc->weight = 0;
      }
    }

    this->createEdge(n1, n2, weight);//cria aresta entre os vertices

  }

  //procura caminho minimo entre dois vertices
  double findShortestPath(int initLabel, int finalLabel){
    Node *start = this->nodeMap[initLabel];
    Node *fim = this->nodeMap[finalLabel];
    return this->dijkstra(start,fim);
  }

private:
  //cria objeto aresta ligando vertices s e f
  void createEdge(Node* s, Node* f, double weight){
    Edge *e = new Edge(s, f, weight);
    this->edges.insert(e);//insere nova aresta no conjunto de arestas do grafo
    s->adjacency.insert(e);//seta vertice f como adjacente ao vertice s
  }

  double dijkstra(Node* start , Node* fim){    //Nós em que o usuário deseja saber o custo mínimo entre eles são passados como parâmetro para checagem.
     map<int, double> currDist;
     set<Node *> toBeChecked; //todos os nos de G sao copiados para toBeChecked

     for(Node * v : this->nodes){
       currDist[v->label] = DBL_MAX; //inicializa com distancia "infinita"
       toBeChecked.insert(v);
     }

     Node* first = start;
     currDist[first->label] = 0; //no inicial tem distancia 0

     while (!toBeChecked.empty() && currDist[fim->label] == DBL_MAX) {
       Node *v = *toBeChecked.begin();
       for(Node *next : toBeChecked) //busca vertice v de menor custo/distancia
         if(currDist[next->label] < currDist[v->label])
           v = next;
       toBeChecked.erase(v); //tira v do conj. a checar
       for(Edge *arc : v->adjacency) //para toda aresta adjacente de v
         if(toBeChecked.find(arc->finish) != toBeChecked.end()) //se vertice destino esta em toBeChecked
           if(currDist[arc->finish->label] > (currDist[v->label] + arc->weight)){
             currDist[arc->finish->label] = currDist[v->label] + arc->weight; //atualiza (relaxamento) do custo
           }
     }
     return currDist[fim->label];          //retorna o caminho mínimo de um vértice até outro,tais são definidos pelo usuário.
 }

  bool directed; //variável booleana que marca se G é direcionado
  map<int, Node *> nodeMap;//mapa de labels para os vertices
  set<Node *> nodes;  //conjunto de vertices
  set<Edge *> edges; //conjunto de arestas
};


int main() {

  int N;   //Número de cidades
  int E;   //Número de acordos para envio de cartas

  while( (cin>>N) && (cin>>E) && (N!=0) && (E!=0) ){

    Graph g(true);//grafo ponderado direcionado

    for(int i=1 ; i<=N ; i++){
      g.addNode(i);}

    for(int i=1 ; i<=E ; i++){
      int X,Y;
      double H;
      cin>>X>>Y>>H;            //Cidade X para a cidade Y com peso da aresta H.
      g.addEdge(X,Y,H);
    }

    int K;
    cin>>K;   //Número de casos teste.

    for(int i=1 ; i<=K ; i++){
      int O,D;
      cin>>O>>D;       //Cidades a serem consultadas.

      double aux = g.findShortestPath(O,D);         //Caminho mínimo entre as 2 cidades a ser consultadas.

      if(aux == DBL_MAX)      //Quando o vértice não foi visitado e estiver com o valor DBL_MAX quer dizer que não há acordos entre as cidades.
        cout << "Nao e possivel entregar a carta" << endl;
      else
        cout << aux << endl ;
    }
    cout<<endl;
  }

  return 0;
}
