#ifndef FILA_H
#define FILA_H

#include <stdio.h>
#include <stdlib.h>

#define FILA_DEBUG 0
#define FILA_DEPTH 100000 //Muitas posicoes na fila
#define TRUE (0==0)
#define FALSE (0==1)

typedef struct n{
  struct n *prox;
  int dado;
  int R;
}fila_node;

typedef struct f{
  fila_node *cabeca;
  fila_node *rabo;
  int tam;  
}fila;

int init_fila(fila *f);
int fila_cheia(fila *f);
int fila_vazia(fila *f);
int insere_fila(int num, fila *f, int Rnum);
int retira_fila(fila *f);
void print_fila(fila *f);

#endif