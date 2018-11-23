
#ifndef MENU_H

#define MENU_H

#endif // MENU_H

typedef struct itemMenu{
    struct * itemMenu;
    char * texto;
    int valor;
    int estado;
    vetor posicao;
    vetor tamanho;

} iMenu;

typedef struct menu{
    struct * itemMenu primeiroItem;
    vetor cursor;
    vetor posicao;
    char * imgFundoBotao;
}
