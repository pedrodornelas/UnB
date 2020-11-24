#include <string.h>
#include <time.h>
#include <unistd.h>
#include "fila.h"
#include "mem.h"

#define ENABLE_SLEEP_SIM 1

int preenche_fila(fila *f){
    for(int i=0;i<128;i++){
        insere_fila(i, f, 0);
    }
}

int altera_r(int num, int Rnum, fila *f){
    fila_node *fn = f->cabeca;

    if(fila_vazia(f)){
        //printf("Fila vazia");
        return -1;
    }
    else{
        while(fn->prox != NULL){
            if(fn->dado == num){
                fn->R=Rnum;
                return 1;
            }
            else
                fn = fn->prox;
        }

        if(fn->dado == num){
            fn->R=Rnum;
            return 1;
        }
    }

    //printf("Não está na fila");
    return -2;
}

//simulacao
int main(int argc, char **argv)
{

  FILE *fp;
  FILE *fp2;
  int vaddr;
  int offset;
  int pnum;
  int fnum;

  int tlb_hit = 0;
  int ptable_hit = 0;
  int backstore_hit = 0;
  int addr_count = 0;

  mem_phy phy[PHY_MEM_DEPTH];
  mem_tlb tlb[TLB_DEPTH];
  mem_page ptable[PAGE_TABLE_DEPTH];
  unsigned char tmp_frame[FRAME_SIZE];

  //estrutura de fila pronta
  fila f;
  init_fila(&f);
  int cont = 0;
  int cont_R_0 = 0;
  int cont_R_1 = 0;
  //preenche_fila(&f);

  //teste da fila
  if (FILA_DEBUG)
  {    
    insere_fila(3,&f,0);
    insere_fila(8,&f,0);
    insere_fila(21,&f,0);
    print_fila(&f);
    int dado = retira_fila(&f);
    print_fila(&f);
    printf("dado retirado = %d\n",dado);
    dado = retira_fila(&f);
    printf("dado retirado = %d\n",dado);
    insere_fila(38,&f,0);
    print_fila(&f);
    dado = retira_fila(&f);
    printf("dado retirado = %d\n",dado);
    print_fila(&f);
    exit(0);
  }

  srand(time(NULL));

  fp = fopen("enderecos.txt","r");
  if(fp == NULL)
  {
    printf("cannot open enderecos.txt\n");
    exit(EXIT_FAILURE);
  }

  fp2 = fopen("backstore.bin","r");
  if(fp2 == NULL)
  {
    printf("cannot open backstore.bin\n");
    exit(EXIT_FAILURE);
  }
  
  //init...
  for(int i = 0 ; i < PAGE_TABLE_DEPTH ; i++)
  {
    ptable[i].pnum = -1;
    ptable[i].fnum = -1;
    //ptable[i].R = 0;
    //ptable[i].M = 0;

    if(i < PHY_MEM_DEPTH)
    {
      phy[i].vazia = 1;
    }
    if(i < TLB_DEPTH)
    {
      tlb[i].pnum = -1;
      tlb[i].fnum = -1;
      //tlb[i].R = 0;
      //tlb[i].M = 0;
    }
  }
  
  time_t start,end;
  
  start = time(NULL);
  //leitura dos enderecos
  while(fscanf(fp,"%d\n",&vaddr) != EOF)
  {
    addr_count ++;
    //printf("%d\n",vaddr);
    pnum = (vaddr & 0x0000ff00) >> 8;
    offset = (vaddr & 0x000000ff);

    //printf("vaddr(%5d) = pnum(%3d) + offset(%3d) => ",vaddr,pnum,offset);

    int fnum = 0;
   
    fnum = consulta_tlb(tlb, pnum);
    if(fnum < 0) //ops, nao esta na tlb
    {
      if(ENABLE_SLEEP_SIM) usleep(10000); //simula penalidade de 1s
      fnum = consulta_ptable(ptable, pnum);
      if(fnum < 0) //ops, nao esta na ptable tambem (PAGE FAULT)
      {
        //procura posicao vazia na mem phy
        int pos = phy_cheia(phy);
        if (pos == CHEIA) //nao existem quadros livres na memoria fisica
        {
          if(ENABLE_SLEEP_SIM) usleep(30000); //simula penalidade de 3s (page fault + algoritmo substituicao)

          //------------------------------------------------------------
          //-------ESCREVA SEU ALGORITMO DE SUBSTITUICAO AQUI-----------
          //------------------------------------------------------------
          //fnum = rand()%PHY_MEM_DEPTH;  //apague essa linha quando for introduzir seu algoritmo

          //Para debugar fila
          /*print_fila(&f);
          int tmp;
          scanf("%d", &tmp);*/

          int Rnum;
          fila_node *fn;
   
          if(!fila_vazia(&f)){
              fnum = -1;
            
              while(fnum == -1){
                fn = f.cabeca;
                Rnum = fn->R;
                
                if(Rnum == 0){ //Bit R=0, fnum = dado desta posição
                  fnum = fn->dado;
                  insere_fila(fnum, &f, 0);
                  retira_fila(&f);
                  //cont_R_0++;
                }
                if(Rnum == 1){ //Bir R=1, insere na fila com o Bit R = 0, e retira a cabeça
                  insere_fila((fn->dado), &f, 0);
                  retira_fila(&f);
                  //cont_R_1++;
                }
              }
          }

          
          //------------------------------------------------------------
          //-------ESCREVA SEU ALGORITMO DE SUBSTITUICAO AQUI-----------
          //------------------------------------------------------------
        

          //SWAP -> backstore.bin
          memcpy(tmp_frame, phy[fnum].fdata, FRAME_SIZE);
        
          rewind(fp2);
          fseek (fp2, pnum*PAGE_SIZE , SEEK_SET );          
          fread(phy[fnum].fdata,1,FRAME_SIZE*sizeof(char),fp2); //swap-in

          int tmp_pnum = -1;
          //descobre a que pagina o quadro "fnum" corresponde
          for(int k = 0 ; k < PAGE_TABLE_DEPTH ; k++)
          {
            if (ptable[k].fnum == fnum)
              tmp_pnum = ptable[k].pnum;                
          }
          
          rewind(fp2);
          fseek (fp2, tmp_pnum*PAGE_SIZE , SEEK_SET );
          fwrite(tmp_frame,1,FRAME_SIZE*sizeof(char),fp2); //swap-out
        }
        else //ainda existem quadros vazios na memoria fisica
        {
          if(ENABLE_SLEEP_SIM) usleep(20000); //simula penalidade de 2s (page fault)
          
          fnum = pos; //pega proximo quadro livre
          
          //Se a memória física estiver vazia 
          insere_fila(fnum, &f, 0);

          rewind(fp2);
          fseek (fp2, pnum*PAGE_SIZE , SEEK_SET );
          fread(phy[fnum].fdata,1,FRAME_SIZE*sizeof(char),fp2);
          phy[fnum].vazia = 0; //indica quadro ocupado
        }
        
        printf(" fnum(%3d) + offset(%3d) => tlb(MISS) ptable(MISS), byte(%c)\n", fnum, offset, phy[fnum].fdata[offset]);

        //atualiza tlb e ptable
        atualiza_ptable(ptable,pnum,fnum);
        atualiza_tlb(tlb,pnum,fnum);
        backstore_hit++;
      }
      else //blz! ja esta na ptable!
      {

        int aux = altera_r(fnum, 1, &f);

        if(aux == -1){ //Se a fila estiver vazia 
          //printf("Inseriu %d\n", fnum);
          insere_fila(fnum, &f, 1);
        }
        else if(aux == -2){ //Se não estiver na fila
          //printf("Não está na fila!!\n");
          insere_fila(fnum, &f, 1);
        }
        else //Alterou R
          cont++;

        //atualiza tlb 
        atualiza_tlb(tlb,pnum,fnum);

        printf(" fnum(%3d) + offset(%3d) => tlb(MISS) ptable(HIT), byte(%c)\n", fnum, offset, phy[fnum].fdata[offset]);
        ptable_hit++;

      }
    }
    else //blz! ja esta na tlb! (sem penalidades)
    {

      int aux = altera_r(fnum, 1, &f);

      if(aux == -1){ //Fila estiver vazia
        //printf("FILA VAZIA | Inseriu %d\n", fnum);
        insere_fila(fnum, &f, 1);
      }
      else if(aux == -2){ //Não está na fila
        //printf("NÃO ESTÁ NA FILA | Inseriu %d\n", fnum);
        insere_fila(fnum, &f, 1);
      }
      else  //Está na fila
        cont++;

      //printf("fnum = %d\n",fnum);
      printf(" fnum(%3d) + offset(%3d) => tlb(HIT), byte(%c)\n", fnum, offset, phy[fnum].fdata[offset]);
      tlb_hit ++;
    }
    //print_tlb(tlb);
  }

  end = time(NULL);

  //Debugar bit R e leitura
  //printf("Cont ptable e tlb = %d\n", cont);
  //printf("Cont R=0 = %d\n", cont_R_0);
  //printf("Cont R=1 = %d\n", cont_R_1);

  printf("tlb hit = %4.4f \n",(((float) tlb_hit)/addr_count)*100);
  printf("ptable hit = %4.4f \n",(((float) ptable_hit)/addr_count)*100);
  printf("backstore hit = %4.4f \n",(((float) backstore_hit)/addr_count)*100);

  printf("tempo total = %lds\n", (end-start));

  //Debugar fila
  //printf("%d\n", f.tam);
  //print_fila(&f);

  fclose(fp);
}
