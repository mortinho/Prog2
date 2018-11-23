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
    int obj;
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

void setPlanoImg(char * img,plano * p){
    if(!p->textura) free(p->textura);
    p->textura = (char *) malloc((strlen(img)+1)*sizeof(char));
    strcpy(p->textura,img);
    p->obj = CriaObjeto(p->textura);
}

plano window(vetor pos,vetor dim){

}

void desenhaPlano(plano *p,vetor cam){
    if (!p) return;
    vetor posRel = p->ancora - cam;
    MoveObjeto(p->obj,posRel.x,posRel.y);
    DesenhaObjeto(p->obj);
    if (!p->proximo)
        if (((posRel.x + p->dimensao.x)<LARG_TELA ) && posRel.x + p->dimensao.x >=0 ){
            p->proximo = (plano *) malloc(sizeof(plano));
            *(p->proximo) = newPlano(vetorRet(posRel.x + p->dimensao.x,0)+cam, vetorRet(300,ALT_TELA));
            setPlanoImg(FND2,p->proximo);

        }
    desenhaPlano(p->proximo,cam);
}








