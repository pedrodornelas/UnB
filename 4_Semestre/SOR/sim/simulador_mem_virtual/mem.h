#ifndef MEM_H
#define MEM_H

#include <stdio.h>
#include <stdlib.h>

#define MISS -1
#define UPDATE 1
#define OVERWRITE 2
#define CHEIA -1

#define TLB_DEPTH 16 //16 posicoes

#define PHY_MEM_DEPTH 128 //64 frames de FRAME_SIZE
#define PAGE_TABLE_DEPTH 256 //256 páginas de PAGE_SIZE
#define PAGE_SIZE 256 //em bytes
#define FRAME_SIZE PAGE_SIZE //tamanhos iguaiss

typedef struct mp{
  int vazia;
  unsigned char fdata[FRAME_SIZE];
}mem_phy;

//entrada da tlb
typedef struct tl{
  //int R;
  //int M;
  int pnum;
  int fnum;
}mem_tlb;

//entrada da tabela de paginas
typedef struct tp{
  //int R;
  //int M;
  int pnum;
  int fnum;
}mem_page;

//consulta se existe mapeamento de "pnum" na tlb
int consulta_tlb(mem_tlb *t, int pnum);

//atualiza a tlb de forma "aleatoria"
int atualiza_tlb(mem_tlb *t, int pnum, int fnum);

//imprime o conteudo da tlb
void print_tlb(mem_tlb *t);

//consulta se existe mapeamento de "pnum" na tabela de pagina
int consulta_ptable(mem_page *pt, int pnum);

//atualiza a tabela de paginas com "pnum => fnum"
int atualiza_ptable(mem_page *pt, int pnum, int fnum);

//testa se ainda existem quadros livres na memoria fisica
int phy_cheia(mem_phy *phy);

#endif