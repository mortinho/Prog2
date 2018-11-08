#ifndef PLANOS_H
#define PLANOS_H
#endif // PLANOS_H


typedef struct mapa{
    int colunas,linhas;
    bloco **blocos;
    vetor dimBloco;
    tipoBloco *tipos;
    int nTipos;

}mapa;

typedef struct plano {
    vetor ancora,dimensao;
    float inclinacao;
    char *textura;
    PIG_Cor cor;
    plano *proximo;
}plano;

plano newPlano(vetor a, vetor dim, float inc=0){
    plano p;
    plano.ancora = a;
    plano.dimensao = dim;
    plano.inclinacao = inc;
    plano.textura = NULL;
    plano.cor = PRETO;
    plano.proximo = NULL;
    return plano;
}








