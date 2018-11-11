
#ifndef FIS_H
#define FIS_H
#endif // FIS_H

#define INFINITE 1e20

#include "vetores.h"
#include "planos.h"
#define ATRITO 1
#define GRAVIDADE 10


vetor nulo = vetorPol(0,0);

typedef struct movel{
    int obj;
    double massa;
    vetor posicao;
    vetor velocidade;
    vetor accel;
    int timer;
    movel *n;
}movel;


movel newMovel(int obj, vetor p=nulo,vetor v= nulo,vetor a=nulo){

    movel m;
    m.massa = 100;
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

void updateMovel(movel *m){
    roundVetor(&(m->accel));
    roundVetor(&(m->velocidade));
    roundVetor(&(m->posicao));
    MoveObjeto(m->obj,m->posicao.x,m->posicao.y);
}

void desenhaMovel(movel *m){
    if (m==NULL) return;
    updateMovel(m);
    DesenhaObjeto(m->obj);
    desenhaMovel(m->n);
}


/* atualiza todos os objetos moveis(afetados por tempo) para seu proximo estado
    escalavel com adicoes a struct movel
*/
void doTick(movel *m){
    m->velocidade = m->velocidade + (m->accel*TICK);
    m->posicao = m->posicao + (m->velocidade*TICK);
    updateMovel(m);
    if (m->n == NULL) return;
    doTick(m->n);
}

void undoTick(movel *m){
    m->velocidade = m->velocidade - (m->accel*TICK);

    m->posicao = m->posicao - (m->velocidade*TICK);
}

/*
    testa colisao com as bordas da tela
*/
void colidir(movel *a,movel *b){
    vetor axis = a->posicao - b->posicao;
    vetor xlinha = vetorRet(axis.y,-axis.x);
    vetor vfa,vfb;
    vfa = getProjecao(a->velocidade,axis);
    vfb = getProjecao(b->velocidade,axis);
    double temp = vfa.r;
    vfa.r = ( vfa.r*(a->massa - b->massa) + 2*vfb.r*b->massa ) / (a->massa + b->massa);
    vfb.r = ( vfb.r*(b->massa - a->massa) + 2*temp*a->massa ) / (a->massa + b->massa);

    a->velocidade = vetorPol(vfa.r,vfa.ang) + getProjecao(a->velocidade,xlinha);
    b->velocidade = vetorPol(vfb.r,vfb.ang) + getProjecao(b->velocidade,xlinha);
}


void colisaoBorda(movel *m){
    int girth = 80;
    double temp;
    movel bEsq = newMovel(CriaParedeInv(girth,ALT_TELA), vetorRet(-girth,0));
    movel bDireita = newMovel(CriaParedeInv(girth,ALT_TELA), vetorRet(LARG_TELA,0));
    movel bBaixo = newMovel(CriaParedeInv(LARG_TELA,girth), vetorRet(0,-girth));
    movel bCima = newMovel(CriaParedeInv(LARG_TELA,girth), vetorRet(0,ALT_TELA));
    bEsq.massa = INFINITE;
    bDireita.massa = INFINITE;
    bCima.massa = INFINITE;
    bBaixo.massa = INFINITE;
    while(m){
        updateMovel(&bEsq);
        if (TestaColisaoObjetos(bEsq.obj,m->obj)){
                temp = bEsq.posicao.y; bEsq.posicao.y = m->posicao.y;
                colidir(&bEsq,m);
                bEsq.posicao.y = temp;
                while(TestaColisaoObjetos(bEsq.obj,m->obj)){
                    m->posicao = m->posicao + vetorRet(1,0);
                    updateMovel(m);
                }
        }
        updateMovel(&bDireita);
        if (TestaColisaoObjetos(bDireita.obj,m->obj)){
                temp = bDireita.posicao.y; bDireita.posicao.y = m->posicao.y;
                colidir(&bDireita,m);
                bDireita.posicao.y = temp;
                while(TestaColisaoObjetos(bDireita.obj,m->obj)){
                    m->posicao = m->posicao + vetorRet(-1,0);
                    updateMovel(m);
                }
        }
        updateMovel(&bCima);
        if (TestaColisaoObjetos(bCima.obj,m->obj)){
                temp = bCima.posicao.x; bCima.posicao.x = m->posicao.x;
                colidir(&bCima,m);
                bCima.posicao.x = temp;
                updateMovel(&bCima);
                while(TestaColisaoObjetos(bCima.obj,m->obj)){
                    m->posicao = m->posicao + vetorRet(0,-1);
                    updateMovel(m);
                }
        }
        updateMovel(&bBaixo);
        if (TestaColisaoObjetos(bBaixo.obj,m->obj)){
                temp = bBaixo.posicao.x; bBaixo.posicao.x = m->posicao.x;
                colidir(&bBaixo,m);
                bBaixo.posicao.x = temp;
                updateMovel(&bBaixo);
                while(TestaColisaoObjetos(bBaixo.obj,m->obj)){
                    m->posicao = m->posicao + vetorRet(0,1);
                    updateMovel(m);
                }
        }
        m = m->n;
    }
    DestroiObjeto(bEsq.obj);
    DestroiObjeto(bDireita.obj);
    DestroiObjeto(bCima.obj);
    DestroiObjeto(bBaixo.obj);
}

void autoColisao(movel *m){
    if (!m) return;

    movel * temp = m->n;
    while(temp){
        if(TestaColisaoObjetos(m->obj,temp->obj)){
            colidir(temp,m);
            while(TestaColisaoObjetos(m->obj,temp->obj)){
                m->posicao = m->posicao + m->velocidade*TICK;
                temp->posicao = temp->posicao + temp->velocidade*TICK;
                updateMovel(m); updateMovel(temp);
            }
        }

        temp=temp->n;
    }

    autoColisao(m->n);
}





