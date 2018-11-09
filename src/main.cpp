
int d=0;
#define TICK 0.05
#define JUMPPOWER 30
#define IMPULSE 0.2

#include "PIG.h"
#include "fisicas.h"

//defines


PIG_Evento evento;
PIG_Teclado meuTeclado;
int tick;

int main( int argc, char* args[] )
{
    CriaJogo("Meu Jogo");

    movel *balls;
    balls = (movel *) malloc(sizeof(movel));
    *balls = newMovel(CriaObjeto("../imagens/redball.png"),vetorRet(LARG_TELA/2,0),vetorRet(200,50),vetorRet(0,-1000));
    int fonte = CriaFonteNormal("../fontes/arial.ttf",32,BRANCO,0,PRETO);
    tick = CriaTimer();
    meuTeclado = GetTeclado();
    while(JogoRodando()){
        evento = GetEvento();
        switch(evento.tipoEvento){
            case  EVENTO_MOUSE:{
                switch(evento.mouse.acao){
                    case MOUSE_PRESSIONADO:{
                        movel *meh = (movel *) malloc(sizeof(movel));
                        *meh = newMovel(CriaObjeto("../imagens/redball.png"),vetorRet(LARG_TELA/2,ALT_TELA/2),getRandomCircular(350),vetorRet(0,-350));
                        addMovel(&balls, meh);
                    }break;
                    case MOUSE_LIBERADO:{
                    }break;
                }}break;

            case EVENTO_TECLADO:{
                switch(evento.teclado.acao){
                    case TECLA_PRESSIONADA:{
                        switch(evento.teclado.tecla){
                            case TECLA_d:{
                                movel *aux = balls;
                                while(aux){
                                    //aux->accel = aux->accel + vetorRet(0, -100);
                                    aux = aux->n;
                                }
                                }break;
                            case TECLA_a:  break;
                            case TECLA_BARRAESPACO: break;
                            case TECLA_ESC: FechaJanela(0); break;
                        }

                    }break;
                     case TECLA_LIBERADA:{
                        switch(evento.teclado.tecla){
                            case TECLA_d:break;
                            case TECLA_a:break;
                            case TECLA_BARRAESPACO:break;
                        }
                     }break;
                }
            }break;
        }

        if(TempoDecorrido(tick)>=TICK){
            doTick(balls);
            ReiniciaTimer(tick);
        }
        IniciaDesenho();
            EscreverCentralizada("Click Click Click",LARG_TELA/2,20,fonte);
            autoColisao(balls);
            checkOOB(balls);
            desenhaMovel(balls);
        EncerraDesenho();

    }

    FinalizaJogo();
    return 0;
        //print
}
