
#ifndef FIS_H
#define FIS_H
#endif // FIS_H

#include "vetores.h"
#include "planos.h"
#define ATRITO 0.8
#define GRAVIDADE 10


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

//movel checkPos(movel m){
//    if (m.posicao.y<=0&&m.estado==AR){
//        m.estado = CHAO;
//        m.posicao = vetorRet(m.posicao.x,0);
//        m.velocidade = vetorRet(m.velocidade.x,0); //sem colisao
//        m.accel = vetorRet(m.accel.x,0);
//    }
//    return m;
//}
//
//vetor checkAccel(vetor a){
//    if (a.x>-2&&a.x<2) a.x = 0;
//    if (a.x>=10) a.x=10;
//    if (a.x<=-10) a.x=-10;
//    return vetorRet(a.x,a.y);
//}
//
//vetor checkVel(vetor a){
//    if (a.x>-2&&a.x<2) a.x = 0;
//    if (a.x>=20) a.x=20;
//    if (a.x<=-20) a.x=-20;
//    return vetorRet(a.x,a.y);
//}


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
    int girth = 10;
    int lateral = CriaParedeInv(girth,ALT_TELA);
    int horizontal = CriaParedeInv(LARG_TELA,girth);



    MoveObjeto(lateral,-girth,0);
    MoveObjeto(horizontal,0,-girth);
    DesenhaObjeto(lateral);
    DesenhaObjeto(horizontal);
    if (TestaColisaoObjetos(lateral,m->obj))
        resultado = resultado + vetorRet(-1,0);
    if (TestaColisaoObjetos(horizontal,m->obj))
        resultado = resultado + vetorRet(0,-1);

    MoveObjeto(lateral,LARG_TELA,0);
    MoveObjeto(horizontal,0,ALT_TELA);

    if (TestaColisaoObjetos(lateral,m->obj))
        resultado = resultado + vetorRet(1,0);
    if (TestaColisaoObjetos(horizontal,m->obj))
        resultado = resultado + vetorRet(0,1);



    DestroiObjeto(lateral);
    DestroiObjeto(horizontal);
    return resultado;

}
void autoColisao(movel *m){
    if (m== NULL) return;
    movel *aux = m->n;
    while(aux){
        if (TestaColisaoObjetos(m->obj,aux->obj)) {
            undoTick(m);
            undoTick(aux);
            vetor axis = m->posicao - aux->posicao;
            m->velocidade = getReflexo(m->velocidade,axis);
            aux->velocidade = getReflexo(aux->velocidade,axis);
        }
        aux = aux->n;
    }
}

void doInteracao(movel *m){
    vetor colB = colisaoBorda(m);

    if (colB != nulo){
        undoTick(m);
        m->velocidade = getReflexo(m->velocidade,colB);
    }

    autoColisao(m);
    if (m->n==NULL) return;
    doInteracao(m->n);
}



