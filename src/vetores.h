
#ifndef GPD_H
#define GPD_H
#endif // GPD_H

/*

*/
#include <time.h>
#include <math.h>

typedef struct vetor{
    int x,y;
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
        linha newLinha(int xa, int ya,int xb,int yb){
            return newLinha(vetorRet(xa,ya),xb,yb);
        }
        void DesenhaLinhaSimples(linha l,SDL_Color c){
            DesenhaLinhaSimples(l.xa,l.ya,l.xb,l.yb,c);
        }
/*</improvavelmente util>*/


vetor vetorRet(int x,int y){
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

vetor vetorPol(double r, double ang){
    vetor v;
    v.r = r; v.ang = ang;
    v.x = r*cos(ang);
    v.y = r*sin(ang);
    return v;
}

vetor getRandomCircular(int vel=100){
    vetor v;
    double ang;
    ang = (rand()%200)*0.01;
    ang *= M_PI;
    v = vetorPol(vel,ang);
    return v;
}

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

vetor operator+(vetor a,vetor b){
    return vetorRet(a.x+b.x,a.y+b.y);
}
vetor operator-(vetor a,vetor b){
    return vetorRet(a.x-b.x,a.y-b.y);
}
vetor operator*(vetor a,double b){
    return vetorPol(a.r * b, a.ang);
}




