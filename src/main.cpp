#include "PIG.h"
#include "grid.h"
#include "vetores.h"
#include "fisicas.h"
#include "planos.h"

//defines
#define TICK 0.05
#define JUMPPOWER 30
#define IMPULSE 0.2

mapa mapa1;
PIG_Evento evento;
PIG_Teclado meuTeclado;
int tick;

int main( int argc, char* args[] )
{

    CriaJogo("Meu Jogo");
    tick = CriaTimer();
    meuTeclado = GetTeclado();
    while(JogoRodando()){
        evento = GetEvento();
        switch(evento.tipoEvento){
            case  EVENTO_MOUSE:{
                switch(evento.mouse.acao){
                    case MOUSE_PRESSIONADO:{
                    }break;
                    case MOUSE_LIBERADO:{
                    }break;
            }}break;

            case EVENTO_TECLADO:{
                switch(evento.teclado.acao){
                    case TECLA_PRESSIONADA:{
                        switch(evento.teclado.tecla){
                            case TECLA_d: break;
                            case TECLA_a:  break;
                            case TECLA_BARRAESPACO: break;
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
            ReiniciaTimer(tick);
        }
        IniciaDesenho();

        EncerraDesenho();

    }

    FinalizaJogo();
    return 0;
        //print
}
