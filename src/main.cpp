
#define FND2 "../imagens/fundo2.png"
#define CHAO 50
#define TICK 0.05
#define JUMPPOWER 30
#define IMPULSE 0.2
#define DEADZONE 4
#define GRAVIDADE 10
#define SPEED 30

#include "PIG.h"
#include "fisicas.h"

//defines

vetor camera = nulo;

plano fundo = newPlano(nulo,vetorRet(LARG_TELA,ALT_TELA));
plano fundo2 = newPlano(nulo,vetorRet(300,ALT_TELA));

PIG_Evento evento;
PIG_Teclado meuTeclado;
int tick;

int main( int argc, char* args[] )
{
    CriaJogo("Meu Jogo");
/*< setup, posteriormente incluir leituro de arquivo de configuracao */

    meuTeclado = GetTeclado();
    int fonte = CriaFonteNormal("../fontes/arial.ttf",32,BRANCO,0,PRETO);
    tick = CriaTimer();




/* end setup >*/



    while(JogoRodando()){
        evento = GetEvento();
/*< eventos prioritarios aqui; pause, quit etc */
        switch(evento.tipoEvento){
            case  EVENTO_MOUSE:{
                switch(evento.mouse.acao){
                    case MOUSE_PRESSIONADO:{
                    }break;
                    case MOUSE_LIBERADO:{
                    }break;
                }}break;

            case EVENTO_TECLADO:{
            }break;
        }
/*>*/
        if(TempoDecorrido(tick)>=TICK){
/*< area de atualizacao baseada no clock e tratamento de input relacionado */





 /* fim da area atualizacao >*/
            ReiniciaTimer(tick);
        }
        IniciaDesenho();
/*< area de desenho */
        desenhaPlano(&fundo,camera);


/* fim desenho >*/
        EncerraDesenho();

    }

    FinalizaJogo();
    return 0;
}
