
#define FND2 "../imagens/fundo2.png"
#define CHAO 50
#define TICK 0.05
#define JUMPPOWER 30
#define IMPULSE 0.2
#define DEADZONE 4
#define GRAVIDADE 10
#define SPEED 30

#include "PIG.h"
#include "input.h"
#include "fisicas.h"

//defines
void tratarTeclado(InfoEventoTeclado e,input *i){
    switch(e.acao){
        case TECLA_PRESSIONADA:{
            switch(e.tecla){
                case RIGHT:{
                     if(!e.repeticao) i->direita = 1;
                } break;
                case LEFT:{
                     if(!e.repeticao) i->esquerda = 1;
                } break;
                case JUMP:{
                     if(!e.repeticao) i->pulando = 1;
                } break;
                case TECLA_ESC: FinalizaJogo(); break;
            }

        }break;
         case TECLA_LIBERADA:{
            switch(e.tecla){
                case RIGHT: i->direita = 0;break;
                case LEFT: i->esquerda = 0;break;
                case TECLA_BARRAESPACO: /*nada*/ break;
            }
         }break;
    }
}
vetor camera = nulo;

plano fundo = newPlano(nulo,vetorRet(LARG_TELA,ALT_TELA));
plano fundo2 = newPlano(nulo,vetorRet(300,ALT_TELA));

PIG_Evento evento;
PIG_Teclado meuTeclado;
int tick;

int main( int argc, char* args[] )
{
    CriaJogo("Meu Jogo");
//
//    movel *balls;
//    balls = (movel *) malloc(sizeof(movel));
//    *balls = newMovel(CriaObjeto("../imagens/redball.png"),vetorRet(LARG_TELA/2,0),vetorRet(200,50),vetorRet(0,-100));
    input teclado = newTeclado();
    int fonte = CriaFonteNormal("../fontes/arial.ttf",32,BRANCO,0,PRETO);
    setPlanoImg("../imagens/fundo1.png",&fundo);
    movel *bob = (movel *) malloc(sizeof(movel));
    *bob = newMovel(CriaObjeto("../imagens/redball.png"),vetorRet(50,CHAO));
    tick = CriaTimer();
    meuTeclado = GetTeclado();
    while(JogoRodando()){
        evento = GetEvento();
        switch(evento.tipoEvento){
            case  EVENTO_MOUSE:{
                switch(evento.mouse.acao){
                    case MOUSE_PRESSIONADO:{
//                        movel *meh = (movel *) malloc(sizeof(movel));
//                        *meh = newMovel(CriaObjeto("../imagens/redball.png"),vetorRet(LARG_TELA/2,ALT_TELA/2),getRandomCircular(350),vetorRet(0,-3050));
//                        addMovel(&balls, meh);
                    }break;
                    case MOUSE_LIBERADO:{
                    }break;
                }}break;

            case EVENTO_TECLADO:{
                tratarTeclado(evento.teclado,&teclado);
            }break;
        }

        if(TempoDecorrido(tick)>=TICK){
            doTickPersonagem(bob,&teclado);
//            doTick(balls);
//            autoColisao(balls);
//            colisaoBorda(balls);
            ReiniciaTimer(tick);
        }
        IniciaDesenho();
            desenhaPlano(&fundo,camera);
//            EscreverCentralizada("Click Click Click",400,125,fonte);
//            autoColisao(balls);
//            desenhaMovel(balls);
        EncerraDesenho();

    }

    FinalizaJogo();
    return 0;
        //print
}
