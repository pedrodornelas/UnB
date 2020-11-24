#include "mem.h"

//consulta se existe mapeamento de "pnum" na tlb
int consulta_tlb(mem_tlb *t, int pnum)
{
  for(int i = 0 ; i < TLB_DEPTH ; i ++)
  {
    if(t[i].pnum == pnum)
      return t[i].fnum; //HIT
  }
  return MISS;
}

//atualiza a tlb de forma "aleatoria"
int atualiza_tlb(mem_tlb *t, int pnum, int fnum)
{
  for (int i = 0 ; i < TLB_DEPTH ; i ++)
  {
    if(t[i].pnum == pnum || t[i].pnum < 0)
    {
      t[i].pnum = pnum;      
      t[i].fnum = fnum;
      return UPDATE;
    }
  }

  int pos = rand()%TLB_DEPTH; //ESCREVE UMA POSICAO ALEATORIA

  t[pos].pnum = pnum; 
  t[pos].fnum = fnum; 
  return OVERWRITE;
}

//imprime o conteudo da tlb
void print_tlb(mem_tlb *t)
{
  for(int i = 0 ; i < TLB_DEPTH ; i ++)
  {
    printf("tlb[%d] (%d => %d) \n",i,t[i].pnum, t[i].fnum);
  }
}

//consulta se existe mapeamento de "pnum" na tabela de pagina
int consulta_ptable(mem_page *pt, int pnum)
{
  for(int i = 0 ; i < PHY_MEM_DEPTH ; i++)
  {
    if(pt[i].pnum == pnum)
      return pt[i].fnum; //HIT
  }
  return MISS; //PAGE FAULT!
}

//atualiza a tabela de paginas com "pnum => fnum"
int atualiza_ptable(mem_page *pt, int pnum, int fnum)
{
  for(int i = 0 ; i < PHY_MEM_DEPTH ; i++)
  {
    if(pt[i].pnum == pnum || pt[i].pnum < 0)
    {
      pt[pnum].pnum = pnum;
      pt[pnum].fnum = fnum;      
      return UPDATE;
    }
  }

  int pos = rand()%PAGE_TABLE_DEPTH; //ESCREVE UMA POSICAO ALEATORIA

  pt[pos].pnum = pnum; //ATUALIZA PNUM
  pt[pos].fnum = fnum; //ATUALIZA FNUM
  return OVERWRITE;
}

//testa se ainda existem quadros livres na memoria fisica
int phy_cheia(mem_phy *phy)
{
  for(int i = 0 ; i < PHY_MEM_DEPTH ; i++)
  {
    if(phy[i].vazia)
      return i;
  }
  return CHEIA;
}