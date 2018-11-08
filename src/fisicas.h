
#ifndef FIS_H
#define FIS_H
#endif // FIS_H
#define ATRITO 0.8
#define GRAVIDADE 10

enum estadoMov{
CHAO,
AR,
PAREDE,
PAREDEAR};

vetor nulo = vetorPol(0,0);

typedef struct movel{
    int obj;
    vetor posicao;
    vetor velocidade;
    vetor accel;
    int estado;
    movel *n;
}movel;


movel newMovel(int obj, vetor p=nulo,vetor v= nulo,vetor a=nulo){
    movel m;
    m.obj = obj;
    m.posicao = p;
    m.velocidade = v;
    m.accel = a;
    m.n = NULL;
    return m;
}

movel checkPos(movel m){
    if (m.posicao.y<=0&&m.estado==AR){
        m.estado = CHAO;
        m.posicao = vetorRet(m.posicao.x,0);
        m.velocidade = vetorRet(m.velocidade.x,0); //sem colisao
        m.accel = vetorRet(m.accel.x,0);
    }
    return m;
}

vetor checkAccel(vetor a){
    if (a.x>-2&&a.x<2) a.x = 0;
    if (a.x>=10) a.x=10;
    if (a.x<=-10) a.x=-10;
    return vetorRet(a.x,a.y);
}

vetor checkVel(vetor a){
    if (a.x>-2&&a.x<2) a.x = 0;
    if (a.x>=20) a.x=20;
    if (a.x<=-20) a.x=-20;
    return vetorRet(a.x,a.y);
}

movel doTick(movel m){
    m.accel = checkAccel(m.accel);
    m.velocidade = checkVel(m.velocidade);
    vetor currentAccel = m.accel;
    currentAccel = m.accel + (m.velocidade* -ATRITO) + vetorRet(0,-GRAVIDADE);
    if (m.estado==CHAO) currentAccel = currentAccel + vetorRet(0,GRAVIDADE);

            printf("x>%i<x",m.estado);
    m.velocidade = m.velocidade + checkAccel(currentAccel);
    m.velocidade = checkVel(m.velocidade);
    m.posicao = m.posicao + m.velocidade;
    m = checkPos(m);
    MoveObjeto(m.obj,m.posicao.x,m.posicao.y);
    return m;
}


