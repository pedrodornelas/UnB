#include "fila.h"

int pesquisa_fila(int num, fila *f){
    fila_node *fn;

    if(fila_vazia(f)){
        return -1;
    }
    else{
        fn = f->cabeca;
        
        while(fn->prox != NULL){
            if(fn->dado == num)
                return num;
            else
                fn = fn->prox;
        }
        
        if(fn->dado == num)
            return num;
    }

    return -1;
}

int altera_r(int num, int Rnum, fila *f){
    fila_node *fn = f->cabeca;

    if(fila_vazia(f)){
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

    return -2;
}

int preenche_fila(fila *f){
    for(int i=0;i<128;i++){
        insere_fila(i, f, 0);
    }
}

int main(int argc, char **argv){
    //estrutura de fila pronta
    fila f;
    init_fila(&f);
  
    /*insere_fila(3,&f);
    insere_fila(8,&f);
    insere_fila(21,&f);
    print_fila(&f);
    int dado = retira_fila(&f);
    print_fila(&f);
    printf("dado retirado = %d\n",dado);
    dado = retira_fila(&f);
    printf("dado retirado = %d\n",dado);
    insere_fila(38,&f);
    print_fila(&f);
    dado = retira_fila(&f);
    printf("dado retirado = %d\n",dado);
    print_fila(&f);*/

    /*for(int i=0; i<10;i++){
        insere_fila(i,&f,0);
    }*/

    preenche_fila(&f);

    print_fila(&f);

    if(fila_cheia(&f)){
        printf("A fila está cheia\n");
    }
    else{
        printf("A fila não está cheia\n");
    }

    /*while(1){
        int i;
        printf("Digite um valor a ser pesquisado:");
        scanf("%i", &i);

        int num = pesquisa_fila(i, &f);
        if(num < 0)
            printf("\nNão está na fila\n");
        else{
            printf("\nEstá na fila\n");
        }
    }*/

    /*while(1){
        int i,j;
        printf("Digite um valor a ser pesquisado:");
        scanf("%d", &i);

        printf("Digite R:");
        scanf("%d", &j);

        int num = altera_r(i, j, &f);
        if(num < 0)
            printf("\nNão está na fila, valor não alterado\n");
        else{
            printf("\nEstá na fila, valor alterado\n");
        }

        print_fila(&f);
    }*/

    exit(0);
}