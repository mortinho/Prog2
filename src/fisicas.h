
#ifndef FIS_H
#define FIS_H
#endif // FIS_H

#include "vetores.h"
#include "planos.h"
#define ATRITO 1
#define GRAVIDADE 10
#define DEADZONE 4


vetor nulo = vetorPol(0,0);

typedef struct movel{
    int obj;
    vetor posicao;
    vetor velocidade;
    vetor accel;
    int timer;
    movel *n;
}movel;


movel newMovel(int obj, vetor p=nulo,vetor v= nulo,vetor a=nulo){

    movel m;
    m.obj = obj;
    m.posicao = p;
    m.velocidade = v;
    m.accel = a;
    m.timer = -1;
    m.n = NULL;
    return m;
}

void addMovel(movel **m,movel *a){
    if (*m == NULL){ *m = a; return; }
    //if ((*m)->n==NULL){(*m)->n = a; return }
    addMovel(&((*m)->n),a);
}

void desenhaMovel(movel *m){
    if (m==NULL) return;
    MoveObjeto(m->obj,m->posicao.x,m->posicao.y);
    DesenhaObjeto(m->obj);
    desenhaMovel(m->n);
}


/* atualiza todos os objetos moveis(afetados por tempo) para seu proximo estado
    escalavel com adicoes a struct movel
*/
void doTick(movel *m){
    m->velocidade = m->velocidade + (m->accel*TICK);
    m->posicao = m->posicao + (m->velocidade*TICK);
    if (m->n == NULL) return;
    doTick(m->n);
}

void undoTick(movel *m){
    m->velocidade = m->velocidade - (m->accel*TICK);
    m->posicao = m->posicao - (m->velocidade*TICK);
}

/*
    testa colisao com as bordas da tela
    retorna um vetor indicando quais bordas foram colididas
        1
    -1  0   1
        -1
*/

vetor colisaoBorda(movel *m){
    vetor resultado = nulo;
    int girth = 80;
    int lateral = CriaParedeInv(girth,ALT_TELA);
    int horizontal = CriaParedeInv(LARG_TELA,girth);



    MoveObjeto(lateral,-girth,0);
    MoveObjeto(horizontal,0,-girth);
    DesenhaObjeto(lateral);
    DesenhaObjeto(horizontal);
    if (TestaColisaoObjetos(lateral,m->obj)||m->posicao.x<0)
        resultado = resultado + vetorRet(-1,0);
    if (TestaColisaoObjetos(horizontal,m->obj)||m->posicao.y<0)
        resultado = resultado + vetorRet(0,-1);

    MoveObjeto(lateral,LARG_TELA,0);
    MoveObjeto(horizontal,0,ALT_TELA);

    if (TestaColisaoObjetos(lateral,m->obj) || m->posicao.x > LARG_TELA)
        resultado = resultado + vetorRet(1,0);
    if (TestaColisaoObjetos(horizontal,m->obj) || m->posicao.y > ALT_TELA)
        resultado = resultado + vetorRet(0,1);



    DestroiObjeto(lateral);
    DestroiObjeto(horizontal);
    return resultado;

}
void autoColisao(movel *m){
    if (m == NULL||m->n == NULL) return;
    movel *aux = m->n;
    while(aux){
        if (TestaColisaoObjetos(m->obj,aux->obj)) {
            vetor axis = m->posicao - aux->posicao;
            float media = (abs(m->velocidade.r)+abs(aux->velocidade.r) )/2;
            d = abs(axis.r);
            if (d <= 40){
                undoTick(m);
                undoTick(aux);
                //m->velocidade = getReflexo(m->velocidade,axis);
                m->velocidade = vetorPol(-media,axis.ang);
                aux->velocidade = vetorPol(media,axis.ang);
                if (d < 40 - DEADZONE && d!=0) {
                    m->velocidade = m->velocidade * 2 * (20/d);
                    aux->velocidade = aux->velocidade * (20/d);
                }
            }
        }
        aux = aux->n;
    }
    autoColisao(m->n);
}

void doInteracao(movel *m){
    if (m->n==NULL) return;
    doInteracao(m->n);
}

void checkOOB(movel *m){
    if (!m) return;
    vetor borda = colisaoBorda(m);
    if (borda.x <0) {
        m->posicao = vetorRet(0,getMiddleY(m->posicao,m->posicao - m->velocidade,0));
        m->velocidade = getReflexo(m->velocidade, vetorRet(1,0));
    } else if (borda.x >0) {
        m->posicao = vetorRet(LARG_TELA-40,getMiddleY(m->posicao,m->posicao - m->velocidade,LARG_TELA-40));
        m->velocidade = getReflexo(m->velocidade, vetorRet(1,0));
    }
    if (borda.y <0){
        m->posicao = vetorRet(getMiddleX(m->posicao,m->posicao - m->velocidade,0),0);
        m->velocidade = getReflexo(m->velocidade, vetorRet(0,1));
        m->velocidade = m->velocidade * 0.5;
    } else if (borda.y >0){
        m->posicao = vetorRet(getMiddleX(m->posicao,m->posicao - m->velocidade,ALT_TELA-40),ALT_TELA-40);
        m->velocidade = getReflexo(m->velocidade, vetorRet(0,1));
    }

    checkOOB(m->n);
}



