
#ifndef GPD_H
#define GPD_H
#endif // GPD_H

/*
Contem a matematica de vetores utilizada

desaconselho a mudanca direta de variaveis do struct vetor (ex. "vetor1.x = 100;") por nao atualizar as coordenadas polares

uso "ideal": vetor1 = vetorRet(100,vetorRet.y);
            vetor1 = vetor1 + vetorRet(100,0);

o ideal é criar variaves pra cada vetor mesmo q estatico como gravidade, posicoes absolutas etc.
e utilizar os operadores + - *

*/
#include <time.h>
#include <math.h>

typedef struct vetor{
    double x,y;
    double r,ang;
}vetor;


/*<improvavelmente util>*/
        typedef struct linha{
            int xa,ya,xb,yb;
            double tamanho,ang;
        }linha;

        linha newLinha(vetor v,int x,int y){
            linha l;
            l.xa = x; l.ya = y;
            l.xb = v.x; l.yb = v.y;
            l.tamanho = v.r;
            l.ang = v.ang;
            return l;
        }

        void DesenhaLinhaSimples(linha l,SDL_Color c){
            DesenhaLinhaSimples(l.xa,l.ya,l.xb,l.yb,c);
        }
/*</improvavelmente util>*/




/* inicializa um vetor pelas coordenadas retangulares (x,y)
    calcula o modulo e o angulo desse vetor*/
//vetor vetorRet(int x,int y){
//    vetor v;
//    double tn;
//    v.x = x; v.y = y;
//    v.r = sqrt(pow(x,2)+pow(y,2));
//    if(v.r==0){
//        v.ang=0;
//        return v;
//    }
//    v.ang = acos(x*pow(v.r,-1));
//    if(y<0) v.ang *= -1;
//    return v;
//}

vetor vetorRet(double x,double y){
    vetor v;
    double tn;
    v.x = x; v.y = y;
    v.r = sqrt(pow(x,2)+pow(y,2));
    if(v.r==0){
        v.ang=0;
        return v;
    }
    v.ang = acos(x*pow(v.r,-1));
    if(y<0) v.ang *= -1;
    return v;
}

/* inicializa um vetor pelas coordenadas polares de tamanho e angulo
    e calcula (x,y) desse vetor*/
vetor vetorPol(double r, double ang){
    vetor v;
    v.r = r; v.ang = ang;
    v.x = r*cos(ang);
    v.y = r*sin(ang);
    return v;
}

/* operacoes com vetores, AKA. sobrecarga de operadores*/
vetor operator+(vetor a,vetor b){
    return vetorRet(a.x+b.x,a.y+b.y);
}

vetor operator-(vetor a,vetor b){
    return vetorRet(a.x-b.x,a.y-b.y);
}
vetor operator*(vetor a,double b){
    return vetorPol(a.r * b, a.ang);
}

int operator==(vetor a,vetor b){
    return (a.x==b.x&&a.y==b.y);
}

int operator!=(vetor a,vetor b){
    return !(a.x==b.x&&a.y==b.y);
}


/*retorna um vetor com angulo aleatorio de raio passado por parametro */
vetor getRandomCircular(int raio=100){
    vetor v;
    double ang;
    ang = (rand()%200)*0.01;
    ang *= M_PI;
    v = vetorPol(raio,ang);
    return v;
}


/* teoricamente retorna um vetor de angulo aleatorio e mesmo raio dentro de um cone centrado em v
com deltaMax sendo a distancia maxima*/
vetor getRandomCone(vetor v,double deltaMax){ /*conta feia do krl, refazer ou remover*/
    double deltaAng;
    vetor vr;
    deltaAng = ((rand()%1000)*0.001);
    deltaAng *= deltaMax;
    deltaAng *= 2;
    deltaAng -= deltaMax;
    vr = vetorPol(v.r, v.ang + deltaAng);


    return vr;
}

int getMiddleX(vetor a,vetor b,int y){
    vetor ab = a-b;
    if (ab.y==0) ab.y=1;
    float x = (a.y - y) * ab.x / ab.y;
    return a.x+x;
}

int getMiddleY(vetor a,vetor b,int x){
    vetor ab = a-b;
    if (ab.x==0) ab.x=1;
    float y = (a.x - x) * ab.y / ab.x;
    return a.y+y;
}


/*
retorna o vetor refletido numa superficie de normal dada
*/
vetor getProjecao(vetor v,vetor u){
    return vetorPol(v.r*(cos(v.ang-u.ang)),u.ang);

}

void roundVetor(vetor *v){
    if (v->r > -1 && v->r < 1 ){
        *v = vetorPol(0,0);
    } else if (v->x < 1 && v->x > -1){
        *v = vetorRet(0,v->y);
    } else if (v->y < 1 && v->y > -1) {
        *v = vetorRet(v->x,0);
    }
}

/*vetor getReflexo(vetor v,vetor normal){
    vetor xlinha,ylinha;
    xlinha = vetorRet(normal.y,-normal.x);
    xlinha = getProjecao(v,xlinha);
    ylinha = getProjecao(v,normal) * -1;

    float deltaTeta = v.ang - normal.ang;
    v = vetorPol(-v.r,v.ang - (2*deltaTeta));
    return v;
}*/







void printv(char *msg,vetor v){
    printf("%s (%i,%i): %f|%f\n",msg,v.x,v.y,v.r,v.ang*180/M_PI);
}
