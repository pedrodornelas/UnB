#include "fila.h"

//operacoes de fila
int init_fila(fila *f)
{
  f->cabeca = NULL;
  f->rabo = NULL;
  f->tam = 0;
}

int fila_cheia(fila *f)
{
  return (f->tam == FILA_DEPTH) ? TRUE: FALSE;  
}

int fila_vazia(fila *f)
{  
  return (f->tam == 0) ? TRUE: FALSE;
}

int insere_fila(int num, fila *f, int Rnum)
{
  fila_node *fn;
  
  if(fila_vazia(f))
  {    
    fn = (fila_node*) malloc(1*sizeof(fila_node));
    fn->dado = num;
    fn->prox = NULL;
    fn->R = Rnum;
    f->cabeca = fn;
    f->rabo = fn;
    f->tam ++;      
    return TRUE;
  }
  else
  {
    if(!fila_cheia(f))
    {   
      fn = (fila_node*) malloc(1*sizeof(fila_node));
      fn->dado = num;
      fn->prox = NULL;
      fn->R = Rnum;
      f->rabo->prox = fn;
      f->rabo = fn;
      f->tam ++;
      return TRUE;
    }
  }
  return FALSE;
}

int retira_fila(fila *f)
{
  fila_node *fn;
  int dado = -1;

  if(fila_vazia(f))
    return dado;
  else
  {
    if(f->tam == 1)
    {
      fn = f->cabeca;
      dado = fn->dado;
      f->cabeca = NULL;
      f->rabo = NULL;
      f->tam = 0;
      free(fn);
      return dado;
    }
    else
    {
      dado = f->cabeca->dado;
      fn = f->cabeca;
      f->cabeca = f->cabeca->prox;
      free(fn);
      f->tam --;
      return dado;
    }    
  }
}

void print_fila(fila *f)
{
  if (fila_vazia(f))
  {
    printf("fila vazia\n");
  }
  else
  {    
    fila_node *fn = f->cabeca;

    while(fn != NULL)
    {
      printf("%d_%d ",fn->dado, fn->R);
      fn = fn->prox;
    }
    printf("\n");
  }
}