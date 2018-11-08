#ifndef PLANOS_H
#define PLANOS_H
#endif // PLANOS_H



/* em construcao
    tratamento de camera e cenario*/

int CriaParedeInv(int larg,int alt){
    PreparaOffScreenRenderer(alt,larg);
    PintaFundoOffScreen(BRANCO);

    return CriaObjetoOffScreen(0);
}

typedef struct plano {
    vetor ancora,dimensao;
    char *textura;
    PIG_Cor cor;
    plano *proximo;
}plano;

plano newPlano(vetor a, vetor dim){
    plano p;
    p.ancora = a;
    p.dimensao = dim;
    p.textura = NULL;
    p.cor = PRETO;
    p.proximo = NULL;
    return p;
}








