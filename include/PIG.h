/********************************
Vers�o 0.6.1 da Biblioteca Pig.h
********************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <string.h>
#include <time.h>
#include <map>
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "Tipos_PIG.h"
#include "CPoolNumeros.h"
#include "SDL_mixer.h"
#include "CGerenciadorJanelas.h"
#include "CAssetLoader.h"
#include "CMapaCaracteres.h"
#include "CGerenciadorObjetos.h"
#include "CGerenciadorTimers.h"
#include "CGerenciadorAudios.h"
#include "CGerenciadorParticulas.h"
#include "CGerenciadorAnimacoes.h"
#include "CMouse.h"
#include "CGerenciadorControles.h"
#include "CJogo.h"


/********************************
/ Vari�veis Globais
/********************************/
Jogo jogo=NULL;

/********************************
A fun��o CriaJogo() � respons�vel pela cria��o da janela do jogo e pelos componentes audio-visuais.
Ela deve ser chamada antes de qualquer outra fun��o da biblioetac PIG.h. N�o � poss�vel criar dois
jogos no mesmo progama. Logo, somente a primeira chamada ter� efeito. A janela padr�o da aplica��o ter� o tamanho definido pelas constantes ALT_TELA e LARG_TELA
definidas no arquivo Tipos.PIG.h, exceto se forem passados outros valores.
Par�metros:
nomeJanela (entrada, passagem por refer�ncia*): indica o nome que a janela do jogo mostrar� no seu t�tulo.
� utilizado o operador * apenas por se tratar de um par�metro string. O valor do par�metro n�o � alterado dentro da fun��o.
cursorProprio (entrada, passagem por valor): indica se o jogo utilizar� cursores (ponteiros) pr�prios para o mouse ou utilizar� o cursor padr�o.
altura (entrada, passagem por valor n�o-obrigat�rio): indica a altura em pixels da janela principal do jogo.
largura (entrada, passagem por valor n�o-obrigat�rio): indica a largura em pixels da janela principal do jogo.
********************************/
void CriaJogo(char *nomeJanela,int cursorProprio=0,int altura=ALT_TELA,int largura=LARG_TELA){
    if (jogo==NULL){
        jogo = new CJogo(nomeJanela,cursorProprio,altura,largura);
        CAssetLoader::Inicia();
        if (cursorProprio)
            CMouse::Inicia();
        CGerenciadorTimers::Inicia();
        CGerenciadorAudios::Inicia();
        CGerenciadorObjetos::Inicia();
        CGerenciadorParticulas::Inicia();
        CGerenciadorAnimacoes::Inicia();
        CGerenciadorControles::Inicia();
    }
}

/********************************
A fun��o GetEstadoJogo() indica o estado do jogo. Este estado � apenas um valor inteiro
que pode ser usado para indicar uma fase do jogo, ou a vez de algum jogador por exemplo.
Retorno:
inteiro indicando o valor do estado do jogo.
********************************/
int GetEstadoJogo(){
    return jogo->GetEstado();
}

/********************************
A fun��o SetEstadoJogo() atribui um novo valor ao estado do jogo. Este estado � apenas um valor inteiro
que pode ser usado para indicar uma fase do jogo, ou a vez de algum jogador por exemplo.
Par�metro:
estado (entrada, passagem por valor): indica o novo estado do jogo;
********************************/
void SetEstadoJogo(int estado){
    jogo->SetEstado(estado);
}

/********************************
A fun��o DefineFundoJanela() permite escolher um arquivo de imagem como fundo (background) de uma janela que ser� automaticamente desenhado a cada nova etapa de desenho na tela.
Par�metros:
nomeArquivoImagem (entrada, passagem por refer�ncia*): indica o caminho relativo ou absoluto do arquivo de imagem que ser� utilizado como fundo do jogo.
� utilizado o operador * apenas por se tratar de um par�metro string. O valor do par�metro n�o � alterado dentro da fun��o.
idJanela (entrada, passagem por valor n�o-obrigatorio): indica de qual janela � a imagem.
********************************/
void DefineFundo(char *nomeArquivoImagem,int idJanela=0){
    CGerenciadorJanelas::DefineFundo(nomeArquivoImagem,idJanela);
}

/********************************
A fun��o GetTeclado() faz um mapeamento entre o teclado f�sico a uma vari�vel do tipo PIG_Teclado que funciona como um vetor de vari�veis l�gicas,
sendo cada posi��o do vetor relativo a uma tecla f�sica.
Uma lista das poss�veis teclas e seus c�digo pode ser vista no arquivo Tipos_PIG.h.
Retorno:
O valor de retorno da fun��o � um vetor de n�meros inteiros que indicam se uma determinada tecla (�ndice do vetor) foi
pressionada (valor diferente de 0,zero) ou n�o (valor igual a zero).
********************************/
PIG_Teclado GetTeclado(){
    return jogo->PegaTeclado();
}

/********************************
A fun��o GetEvento() indica se houve algum tipo de evento desde a �ltima vez que a fun��o foi chamada.
Um evento pode ser uma tecla pressionada, um clique do mouse ou outra coisa relacionada � tela do jogo.
Maiores informa��e podem ser vistas no arquivo Tipo_PIG.h
Retorno:
O valor de retorno � um struct contendo o tipo de evento ocorrido e v�rios outros structs com informa��es espec�ficas.
********************************/
PIG_Evento GetEvento(){
    return jogo->PegaEvento();
}

/********************************
A fun��o IniciaDesenho() � respons�vel por preparar a janela do jogo para que os objetos gr�ficos
possam ser mostrados, al�m de desenhar a imagem de fundo do jogo, caso tenha sido definida.
Deve ser chamada repetidamente a cada novo quadro (frame) a ser desenhado.
Par�metros:
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica qual janela deve preparar a renderiza��o. O valor (-1) indica que todas as janelas devem ser preparadas.
********************************/
void IniciaDesenho(int idJanela=-1){
    jogo->IniciaDesenho(idJanela);
}

/********************************
A fun��o EncerraDesenho() � respons�vel por encerrar o desenho que foi criado, mostrando na janela do jogo.
Deve ser chamado sempre ao final do loop principal do jogo.
Par�metros:
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica qual janela deve preparar a renderiza��o. O valor (-1) indica que todas as janelas devem ser exibidas.
********************************/
void EncerraDesenho(int idJanela=-1){
    if (jogo->cursorPadrao!=0)
        CMouse::Desenha();
    jogo->EncerraDesenho(idJanela);
}

/********************************
A fun��o SalvaTela() � respons�vel por criar um arquivo Bitmap, contendo uma c�pia de uma janela do jogo naquele momento.
Par�metros:
nomeArquivoBMP (entrada, passagem por refer�ncia*): indica o nome do arquivo Bitmap que ser� salvo. O valor do par�metro deve conter a extens�o ".bmp".
� utilizado o operador * apenas por se tratar de um par�metro string. O valor do par�metro n�o � alterado dentro da fun��o.
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica qual janela deve ter a imagem salva.
********************************/
void SalvaTela(char *nomeArquivoBMP,int idJanela=0){
    CGerenciadorJanelas::SaveScreenshotBMP(nomeArquivoBMP,idJanela);
}

/********************************
A fun��o JogoRodando() � repons�vel por retornar se o jogo ainda est� ativo ou n�o.
O jogo ser� encerrado se a janela do jogo for fechada, por exemplo.
Retorno:
inteiro que indica se o jogo ainda est� sendo executado (valor diferente de zero) ou n�o (valor igual a 0, zero).
********************************/
int JogoRodando(){
    return jogo->GetRodando();
}

/********************************
A fun��o Espera() "congela" a tela do jogo por alguns milisegundos, impedindo que qualquer outro comando seja executado enquanto isso.
Par�metros:
tempo (entrada, passagem por valor): indica a quantidade de milisegundos durante a qual o jogo ser� pausado.
********************************/
void Espera(int tempo){
    SDL_Delay(tempo);
}

/********************************
A fun��o FinalizaJogo() � respons�vel por encerrar com a PIG. Ap�s tudo o jogo ser executado
a fun��o deve ser chamada e ela ir� realizar a libera��o de mem�ria dos elementos criados pela PIG.
********************************/
void FinalizaJogo(){
    CGerenciadorControles::Encerra();
    CGerenciadorAnimacoes::Encerra();
    CGerenciadorParticulas::Encerra();
    CGerenciadorObjetos::Encerra();
    CGerenciadorTimers::Encerra();
    if (jogo->cursorPadrao==0)
        CMouse::Encerra();
    CAssetLoader::Encerra();
    delete jogo;
}

/********************************
A fun��o GetFPS() � respons�vel por calcular o valor do Frames Per Seconds (FPS), que representa a quantidade de
frames (quadros) desenhados por segundo pela PIG.
Retorno:
float que indica a m�dia de quadros desenhados por segundo.
********************************/
float GetFPS(){
    return jogo->GetFPS();
}

/********************************
A fun��o CarregaCursor() � respons�vel por armazenar um novo cursor para o mouse, dado pelo arquivo de imagem indicado.
O arquivo deve ser uma imagem com 32 pixels de altura orbigatoriamente.
Par�metro:
indice (entrada, passagem por valor): informa um �ndice para este novo cursor. Se o �ndice j� estiver sendo utilizado,
o cursor antigo � removido. O valor deve estar entre 0..MAX_CURSORES-1.
nomeArquivoCursor (entrada, passagem por refer�ncia*): indica o nome do arquivo de imagem que ser� utilziado como cursor do mouse.
� utilizado o operador * apenas por se tratar de um par�metro string. O valor do par�metro n�o � alterado dentro da fun��o.
********************************/
void CarregaCursor(int indice,char *nomeArquivoCursor){
    CMouse::CarregaCursor(indice,nomeArquivoCursor);
}

/********************************
A fun��o MudaCursor() � respons�vel por alterar o cursor atual do mouse por outro j� carregado.
Par�metro:
indice (entrada, passagem por valor): informa um �ndice para este novo cursor que j� deve ter sido
carregado anteriormente e deve estar no intervalo 0..MAX_CURSORES-1.
********************************/
void MudaCursor(int indice){
    CMouse::MudaCursor(indice);
}

/********************************
Se��o de tratamento de janelas
********************************/

/********************************
A fun��o GetQtdJanela() � respons�vel por calcular quantas janelas est�o criadas pelo jogo, incluindo as que est�o minimizadas ou escondidas.
Retono:
inteiro que representa a quantidade de janelas ainda abertas pelo jogo, incluindo as que est�o minimizadas ou escondidas.
********************************/
int GetQtdJanelas(){
    return CGerenciadorJanelas::GetQtdJanelas();
}

/********************************
A fun��o CriaJanela() � respons�vel por criar e exibir uma nova janela para a aplica��o. O identificador num�rico da nova janela � retornado como par�metro.
Se n�o foi poss�vel criar a janela, o valor de retorno ser� -1. Existe um limite m�ximo de janela que podem ser criadas. Esse limite � dado pelo par�metro MAX_JANELAS configurado na Tipos_PIG.h.
O valor da janela original (padr�o) � sempre igual a 0 (zero). Para se desenhar qualquer coisa nas janelas adicionais, � preciso criar objetos, anima��es, geradores de part�culas e fontes
especificando-se a janela na qual estes elementos ser�o renderizados. Ao utilizar-se janelas adicionais, tamb�m � poss�vel estipular individualmente quais janelas ser�o preparadas e mostradas, utilizando o
n�mero da janela nas chamadas das fun��es IniciaDesenho e EncerraDesenho. Caso n�o seja especificado o n�mero, todas as janelas s�o preparadas e mostradas, respectivamente.
Par�metros:
nomeJanela (entrada, passagem por refer�ncia*): indica o nome que a nova janela mostrar� no seu t�tulo.
� utilizado o operador * apenas por se tratar de um par�metro string. O valor do par�metro n�o � alterado dentro da fun��o.
altura (entrada, passagem por valor n�o-obrigat�rio): indica a altura em pixels da janela a ser criada.
largura (entrada, passagem por valor n�o-obrigat�rio): indica a largura em pixels da janela a ser criada.
Retorno
inteiro que representa o n�mero de identifica��o dessa janela. esse n�mero deve ser utilizado sempre que um comando deva ser executado para uma janela espec�fica.
A janela padr�o da aplica��o possui sempre o n�mero 0 (zero).
********************************/
int CriaJanela(char *nomeJanela,int altura=ALT_TELA,int largura=LARG_TELA){
    return CGerenciadorJanelas::CriaJanela(nomeJanela,altura,largura);
}

/********************************
A fun��o FechaJanela() � respons�vel por fechar uma janela. As renderiza��es nessa janela que ocorrerem posteriormente n�o ter�o qualquer efeito.
A janela fechada vai deixar de gerar eventos, mas n�o poderpa ser reaberta. O efeito de reabrir um janela pode ser obtido com os comandos EscondeJanela() e ExibeJanela().
Par�metros:
idJanela (entrada, passagem por valor): indica o n�mero da janela a ser fechada.
********************************/
void FechaJanela(int idJanela){
    CGerenciadorJanelas::FechaJanela(idJanela);
}

/********************************
A fun��o EscondeJanela() � respons�vel por fazer a janela deixar de ser vis�vel, mas n�o a fecha de forma definitiva.
A janela poder� ser reaberta com a fun��o ExibeJanela().
Par�metros:
idJanela (entrada, passagem por valor): indica o n�mero da janela a ser oculta.
********************************/
void EscondeJanela(int idJanela){
    CGerenciadorJanelas::EscondeJanela(idJanela);
}

/********************************
A fun��o ExibeJanela() � respons�vel por fazer a janela voltar a ser vis�vel, mas n�o faz automaticamente a janela ter o foco para gerar eventos.
A janela poder� ser reaberta com foca por meio da fun��o GanhaFocoJanela().
Par�metros:
idJanela (entrada, passagem por valor): indica o n�mero da janela a ser reexibida sem foco.
********************************/
void ExibeJanela(int idJanela){
    CGerenciadorJanelas::ExibeJanela(idJanela);
}

/********************************
A fun��o GanhaFocoJanela() � respons�vel por fazer a janela voltar a ser vis�vel e automaticamente voltar a ter o foco para gerar eventos.
Par�metros:
idJanela (entrada, passagem por valor): indica o n�mero da janela a ser reexibida com foco.
********************************/
void GanhaFocoJanela(int idJanela){
    CGerenciadorJanelas::GanhaFocoJanela(idJanela);
}

/********************************
A fun��o GetAlturaJanela() � respons�vel por recuperar a altura da janela em pixels.
Par�metros:
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica o n�mero da janela a ser consultada.
Retorno:
inteiro que representa a altura da janela em pixels.
********************************/
int GetAlturaJanela(int idJanela=0){
    return CGerenciadorJanelas::GetAltura(idJanela);
}

/********************************
A fun��o GetLarguraJanela() � respons�vel por recuperar a largura da janela em pixels.
Par�metros:
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica o n�mero da janela a ser consultada.
Retorno:
inteiro que representa a largura da janela em pixels.
********************************/
int GetLarguraJanela(int idJanela=0){
    return CGerenciadorJanelas::GetLargura(idJanela);
}

/********************************
A fun��o GetTituloJanela() � respons�vel por recuperar o t�tulo (caption) atual da janela.
Par�metros:
tituloJanela (sa�da, passagem por refer�ncia): armazena o t�tulo da janela que foi recuperado.
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica o n�mero da janela a ser consultada.
********************************/
void GetTituloJanela(char *tituloJanela,int idJanela=0){
    CGerenciadorJanelas::GetTitulo(tituloJanela,idJanela);
}

/********************************
A fun��o SetTituloJanela() � respons�vel por definir um novo t�tulo (caption) para a janela.
Par�metros:
novoTitulo (entrada, passagem por refer�ncia*): indica o novo t�tulo para a janela.
� utilizado o operador * apenas por se tratar de um par�metro string. O valor do par�metro n�o � alterada dentro da fun��o.
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica o n�mero da janela a ser alterada.
********************************/
void SetTituloJanela(char *novoTitulo,int idJanela=0){
    CGerenciadorJanelas::SetTitulo(novoTitulo,idJanela);
}

/********************************
A fun��o GetCorFundoJanela() � respons�vel por recuperar uma cor de fundo para a janela indicada. A cor de fundo ser� utilizada como background autom�tico quando a janela for preparada para renderiza��es.
Par�metros:
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica o n�mero da janela a ser alterada.
Retorno
cor contendo os componentes RGBA da cor utilizada para pintar automaticamente o fundo da janela.
********************************/
PIG_Cor GetCorFundoJanela(int idJanela=0){
    return CGerenciadorJanelas::GetCorFundo(idJanela);
}

/********************************
A fun��o SetCorFundoJanela() � respons�vel por definir uma cor de fundo para a janela indicada. A cor de fundo ser� utilizada como background autom�tico quando a janela for preparada para renderiza��es.
Par�metros:
cor (entrada, passagem por valor): indica a cor para o fundo da janela.
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica o n�mero da janela a ser alterada.
********************************/
void SetCorFundoJanela(PIG_Cor cor,int idJanela=0){
    CGerenciadorJanelas::SetCorFundo(cor,idJanela);
}

/********************************
A fun��o GetOpacidadeJanela() � respons�vel por recuperar o n�vel de opacidade de uma janela. A opacidade pode variar entre 1.0 (totalmente opaca) e 0 (totalmente transparente).
Par�metros:
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica o n�mero da janela a ser alterada.
Retorno:
n�mero real que indica o n�vel de opacidade da janela, variando entre 1.0 e 0.
********************************/
float GetOpacidadeJanela(int idJanela=0){
    return CGerenciadorJanelas::GetOpacidade(idJanela);
}

/********************************
A fun��o SetOpacidadeJanela() � respons�vel por definir o n�vel de opacidade de uma janela. A opacidade pode variar entre 1.0 (totalmente opaca) e 0 (totalmente transparente).
Par�metros:
nivelOpacidade (entrada, passagem por valor): indica o n�vel de opacidade da janela, variando entre 1.0 e 0.
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica o n�mero da janela a ser alterada.
********************************/
void SetOpacidadeJanela(float nivelOpacidade,int idJanela=0){
    CGerenciadorJanelas::SetOpacidade(nivelOpacidade,idJanela);
}

/********************************
A fun��o SetPosicaoJanela() � respons�vel por definir a posi��o de um janela na tela correspondente. A tela normalmente utiliza um sistema de coordenadas, cujo ponto (0,0) � o canto superior esquerdo.
Par�metros:
posicaoX (entrada, passagem por valor): indica o valor no eixo X (horizontal) da esquerda para direita.
posicaoY (entrada, passagem por valor): indica o valor no eixo Y (vertical), normalmente de cima para baixo.
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica o n�mero da janela a ser reposicionada.
********************************/
void SetPosicaoJanela(int posicaoX,int posicaoY,int idJanela=0){
    CGerenciadorJanelas::SetPosicao(posicaoX,posicaoY,idJanela);
}

/********************************
A fun��o SetPosicaoJanela() � respons�vel por recuperar a posi��o de um janela na tela correspondente. A tela normalmente utiliza um sistema de coordenadas, cujo ponto (0,0) � o canto superior esquerdo.
Par�metros:
posicaoX (sa�da, passagem por refer�ncia): indica o valor no eixo X (horizontal) da esquerda para direita.
posicaoY (saida, passagem por refer�ncia): indica o valor no eixo Y (vertical), normalmente de cima para baixo.
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica o n�mero da janela a ser reposicionada.
********************************/
void GetPosicaoJanela(int *posicaoX,int *posicaoY,int idJanela=0){
    CGerenciadorJanelas::GetPosicao(posicaoX,posicaoY,idJanela);
}

/********************************
A fun��o SetBordaJanela() � respons�vel por definir se uma janela possuir� ou n�o bordas vis�veis. O valor de 0 (zero) indica aus�ncia de borda, enquanto valores diferentes de zero indicam presen�a de borda.
Par�metros:
valor (entrada, passagem por valor): indica se a janela possui borda (valor diferente de zero) ou n�o (valor igual a zero).
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica o n�mero da janela a ser reposicionada.
********************************/
void SetBordaJanela(int valor,int idJanela=0){
    CGerenciadorJanelas::SetBorda(valor,idJanela);
}

/********************************
A fun��o SetModoJanela() � respons�vel por definir o modo de exibi��o de uma janela. A janela pode ser exibida em tr�s diferentes modos: JANELA_NORMAL, que � o modo padr�o onde a janela ocupa o espa�o da tela definido por sua altura e largura atual;
JANELA_TELACHEIA_DISPLAY, que � o modo no qual a janela fica em tela cheia com a resolu��o id�ntica � da tela; JANELA_TELACHEIA, que � o modo onde a janela fica em tela cheia, mas com a resolu��o atual mantida.
A tela cheia n�o � acionada automaticamente com a combin��o ALT+ENTER, � preciso executar o comando espec�fico.
Par�metros:
modo (entrada, passagem por valor): indica qual dos tr�s modos (JANELA_NORMAL, JANELA_TELACHEIA, JANELA_TELACHEIA_DISPLAY) deve ser usado para exibir a janela.
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica o n�mero da janela a ser reposicionada.
********************************/
void SetModoJanela(int modo,int idJanela=0){
    CGerenciadorJanelas::SetModo(modo,idJanela);
}

/********************************
A fun��o GetModoJanela() � respons�vel por recuperar o modo de exibi��o de uma janela. A janela pode ser exibida em tr�s diferentes modos: JANELA_NORMAL, que � o modo padr�o onde a janela ocupa o espa�o da tela definido por sua altura e largura atual;
JANELA_TELACHEIA_DISPLAY, que � o modo no qual a janela fica em tela cheia com a resolu��o id�ntica � da tela; JANELA_TELACHEIA, que � o modo onde a janela fica em tela cheia, mas com a resolu��o atual mantida.
A tela cheia n�o � acionada automaticamente com a combin��o ALT+ENTER, � preciso executar o comando espec�fico.
Par�metros:
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica o n�mero da janela a ser reposicionada.
Retorno:
inteiro que indica qual dos tr�s modos (JANELA_NORMAL, JANELA_TELACHEIA, JANELA_TELACHEIA_DISPLAY) est� sendo usado para exibir a janela.
********************************/
int GetModoJanela(int idJanela=0){
    return CGerenciadorJanelas::GetModo(idJanela);
}


/********************************
Se��o de controle de jogo
********************************/

/********************************
A fun��o BotaoPressionadoControle() � respons�vel por verificar se um determinado bot�o do controle est� ou n�o pressionado.
Par�metros:
idControle (entrada, passagem por valor): indica qual controle est� sendo verificado.
botao (entrada, passagem por valor): indica qual botao est� sendo verificado.
retono:
inteiro que representa se o bot�o est� pressionado (valor diferente de zero) ou est� livre (valor igual a zero).
********************************/
int BotaoPressionadoControle(int idControle,int botao){
    return CGerenciadorControles::BotaoPressionado(idControle,botao);
}

/********************************
A fun��o EixoAcionadoControle() � respons�vel por verificar o n�vel de acionamento de um eixo do controle. Essa fun��o pode ser utilizada
tanto para eixos anal�gicos, cujos valores s�o de -32768 a 32767, ou gatilhos, cujos valores s�o de 0 a 32767.
Par�metros:
idControle (entrada, passagem por valor): indica qual controle est� sendo verificado.
eixo (entrada, passagem por valor): indica qual eixo est� sendo verificado.
retono:
inteiro que representa o n�vel de acionamento do eixo. Pode ser um valor negativo (eixos anal�gicos) ou valores positivos (eixos anal�gicos e gatilhos).
********************************/
int EixoAcionadoControle(int idControle,int eixo){
    return CGerenciadorControles::EixoAcionado(idControle,eixo);
}

/********************************
A fun��o EixoAcionadoPercentualControle() � respons�vel por verificar o n�vel percentual de acionamento de um eixo do controle. Essa fun��o pode ser utilizada
tanto para eixos anal�gicos, cujos valores s�o de -1.0 a 1.0, ou gatilhos, cujos valores s�o de 0 a 1.0.
Par�metros:
idControle (entrada, passagem por valor): indica qual controle est� sendo verificado.
eixo (entrada, passagem por valor): indica qual eixo est� sendo verificado.
retono:
n�mero real que representa o n�vel percentual de acionamento do eixo. Pode ser um valor negativo (eixos anal�gicos) ou valores positivos (eixos anal�gicos e gatilhos).
********************************/
float EixoAcionadoPercentualControle(int idControle,int eixo){
    return CGerenciadorControles::EixoAcionadoPercentual(idControle,eixo);
}

/********************************
A fun��o GetQtdEixosControle() � respons�vel por calcular quantos eixos e gatilhos est�o dispon�veis no controle.
Par�metros:
idControle (entrada, passagem por valor): indica qual controle est� sendo verificado.
retono:
inteiro que representa a quantidade de eixos e gatilhos.
********************************/
int GetQtdEixosControle(int idControle){
    return CGerenciadorControles::GetQtdEixos(idControle);
}

/********************************
A fun��o GetQtdBotoesControle() � respons�vel por calcular quantos bot�es digitais (incluindo os direcionais) est�o dispon�veis no controle.
Par�metros:
idControle (entrada, passagem por valor): indica qual controle est� sendo verificado.
retono:
inteiro que representa a quantidade de bot�es digitais (incluindo os direcionais).
********************************/
int GetQtdBotoesControle(int idControle){
    return CGerenciadorControles::GetQtdBotoes(idControle);
}

/********************************
A fun��o GetNomeControle() � respons�vel recuperar o nome com o qual o controle foi registrado no sistema.
Par�metros:
idControle (entrada, passagem por valor): indica qual controle est� sendo verificado.
nomeControle (sa�da, passagem por refer�ncia): armazena a string contendo o nome que foi recuperada para o controle.
********************************/
void GetNomeControle(int idControle,char *nomeControle){
    CGerenciadorControles::GetNome(idControle,nomeControle);
}


/********************************
Se��o de elementos geom�tricos
********************************/

/********************************
A fun��o DesenhaLinhasSimples() � respons�vel por desenhar uma �nica linha, cujo in�cio � o ponto (x1,y1) e o fim � o ponto (x2,y2).
Par�metros:
pontoX1 (entrada, passagem por valor): inteiro que indica o in�cio da linha no eixo X.
pontoY1 (entrada, passagem por valor): inteiro que indica o in�cio da linha no eixo Y.
pontoX2 (entrada, passagem por valor): inteiro que indica o fim da linha no eixo X.
pontoY2 (entrada, passagem por valor): inteiro que indica o fim da linha no eixo Y.
cor (entrada, passagem por valor): indica a cor no sistema RGB para o desenho da linha;
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica o n�mero da janela onde a linha ser� desenhada.
********************************/
void DesenhaLinhaSimples(int pontoX1,int pontoY1,int pontoX2,int pontoY2, PIG_Cor cor, int idJanela=0){
    jogo->DesenhaLinhaSimples(pontoX1,pontoY1,pontoX2,pontoY2,cor,idJanela);
}

/********************************
A fun��o DesenhaLinhasDisjuntas() � respons�vel por desenhar linhas separadamente, ou seja, os ponto iniciais de cada linha est�o nas posi��es pares e
os pontos finais est�o nas posi��es �mpares. Assim, os vetores precisam ter tamanho qtd*2.
Par�metros:
pontosX (entrada, passagem por refer�ncia): vetor de inteiros, de tamanho qtd*2, contendo os valores X (inicias e finais) de cada linha.
pontosY (entrada, passagem por refer�ncia): vetor de inteiros, de tamanho qtd*2, contendo os valores Y (inicias e finais) de cada linha.
qtd (entrada, passagem por valor): quantidade de linhas a serem desenhadas.
cor (entrada, passagem por valor): indica a cor no sistema RGB para o desenho das linhas;
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica o n�mero da janela onde as linhas ser�o desenhadas.
********************************/
void DesenhaLinhasDisjuntas(int *pontosX,int *pontosY,int qtd, PIG_Cor cor, int idJanela=0){
    jogo->DesenhaLinhasDisjuntas(pontosX,pontosY,qtd,cor,idJanela);
}

/********************************
A fun��o DesenhaLinhasSequencia() � respons�vel por desenhar linhas em sequ�ncia, ou seja, o ponto final da primeira linha
corresponde ao ponto inicial da segunda linha.
Par�metros:
pontosX (entrada, passagem por refer�ncia): vetor de inteiros, de tamanho qtd+1, contendo os valores X de cada linha da sequ�ncia.
pontosY (entrada, passagem por refer�ncia): vetor de inteiros, de tamanho qtd+1, contendo os valores Y de cada linha da sequ�ncia.
qtd (entrada, passagem por valor): quantidade de linhas a serem desenhadas.
cor (entrada, passagem por valor): indica a cor no sistema RGB para o desenho das linhas;
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica o n�mero da janela onde as linhas ser�o desenhadas.
********************************/
void DesenhaLinhasSequencia(int *pontosX,int *pontosY,int qtd, PIG_Cor cor, int idJanela=0){
    jogo->DesenhaLinhasSequencia(pontosX,pontosY,qtd,cor,idJanela);
}

/********************************
A fun��o DesenhaRetangulo() � respons�vel por desenhar um ret�ngulo com preenchimento s�lido na tela em uma posi��o desejada pelo usu�rio.
O mesmo pode ser colocado em qualquer lugar do campo de vis�o da tela.
Par�metros:
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usu�rio deseja colocar o ret�ngulo.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usu�rio deseja colocar o ret�ngulo.
altura (entrada, passagem por valor): Valor onde o usu�rio ir� fornecer o n�mero correspondente em pixels � altura desse ret�ngulo.
largura (entrada, passagem por valor): Valor onde o usu�rio ir� fornecer o n�mero correspondente em pixels � largura desse ret�ngulo.
cor (entrada, passagem por valor): indica a cor no sistema RGB para o desenho do ret�ngulo;
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica o n�mero da janela onde o ret�ngulo ser� desenhado.
********************************/
void DesenhaRetangulo(int posicaoX, int posicaoY, int altura, int largura, PIG_Cor cor, int idJanela=0){
    jogo->DesenhaRetangulo(posicaoX,posicaoY,altura,largura,cor,idJanela);
}

/********************************
A fun��o DesenhaRetanguloVazado() � respons�vel por desenhar um ret�ngulo sem preenchimento na tela em uma posi��o desejada pelo usu�rio.
O mesmo pode ser colocado em qualquer lugar do campo de vis�o da tela.
Par�metros:
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usu�rio deseja colocar o ret�ngulo.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usu�rio deseja colocar o ret�ngulo.
altura (entrada, passagem por valor): Valor onde o usu�rio ir� fornecer o n�mero correspondente em pixels � altura desse ret�ngulo.
largura (entrada, passagem por valor): Valor onde o usu�rio ir� fornecer o n�mero correspondente em pixels � largura desse ret�ngulo.
cor (entrada, passagem por valor): indica a cor no sistema RGB para a borda do ret�ngulo;
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica o n�mero da janela onde o ret�ngulo ser� desenhado.
********************************/
void DesenhaRetanguloVazado(int posicaoX, int posicaoY, int altura, int largura, PIG_Cor cor, int idJanela=0){
    jogo->DesenhaRetanguloVazado(posicaoX,posicaoY,altura,largura,cor,idJanela);
}

/********************************
A fun��o DesenhaPoligono() � respons�vel por desenhar na janela um pol�gono de preenchimento s�lido com o n�mero de lados indicados. Os dois primeiros par�metros indicam as coordenadas
de cada um dos v�rtices do pol�gono.
AVISO: essa fun��o utiliza o renderizador offscreen para gerar o pol�gono e posterior o renderiza na janela em quest�o; isto pode fazer o FPS da aplica��o diminuir consideravelmente.
Par�metros:
pontosX (entrada, passagem por refer�ncia): vetor de inteiros, de tamanho qtd, contendo as coordenadas X de cada v�rtice do pol�gono.
pontosY (entrada, passagem por refer�ncia): vetor de inteiros, de tamanho qtd, contendo as coordenadas Y de cada v�rtice do pol�gono.
qtd (entrada, passagem por valor): quantidade de lados do pol�gono.
cor (entrada, passagem por valor): indica a cor no sistema RGB para o desenho do pol�gono;
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica o n�mero da janela onde o pol�gono ser� desenhado.
********************************/
void DesenhaPoligono(int *pontosX,int *pontosY,int qtd, PIG_Cor cor, int idJanela=0){
    jogo->PintarPoligono(pontosX,pontosY,qtd,cor,idJanela);
}


/********************************
Se��o de desenho Offscreen
********************************/

/********************************
A fun��o PreparaOffScreenRenderer() serve para criar um novo bitmap offscreen que servir� de �rea
de desenho para outras fun��es que utilizem este bitmap.
Par�metros:
altura (entrada, passagem por valor): indica a altura em pixels do novo bitmap.
largura (entrada, passagem por valor): indica a largura em pixels do novo bitmap.
********************************/
void PreparaOffScreenRenderer(int altura,int largura){
    jogo->PreparaOffScreenRenderer(altura,largura);
}

/********************************
A fun��o SalvaOffScreenBMP() serve para efetivamente salvar a imagem offscreen como um arquivo do sistema operacional.
A imagem offscreen continuar� existindo em mem�ria e a��es subsequentes ainda poder�o ser feitas. Para "limpar" a imagem
deve-se utilizar a fun��o PintaFundoOffScreen().
Par�metros:
nomeArquivoBMP (entrada, passagem por refer�ncia*): indica com que nome a imagem offscreen ser� salva. O valor do par�metro deve conter a extens�o ".bmp".
� utilizado o operador * apenas por se tratar de um par�metro string. O valor do par�metro n�o � alterado dentro da fun��o.
********************************/
void SalvaOffScreenBMP(char *nomeArquivoBMP){
    jogo->SalvaOffScreenBMP(nomeArquivoBMP);
}

/********************************
A fun��o SalvaOffScreenPNG() serve para efetivamente salvar a imagem offscreen como um arquivo do sistema operacional.
A imagem offscreen continuar� existindo em mem�ria e a��es subsequentes ainda poder�o ser feitas. Para "limpar" a imagem
deve-se utilizar a fun��o PintaFundoOffScreen().
Par�metros:
nomeArquivoPNG (entrada, passagem por refer�ncia*): indica com que nome a imagem offscreen ser� salva. O valor do par�metro deve conter a extens�o ".png".
� utilizado o operador * apenas por se tratar de um par�metro string. O valor do par�metro n�o � alterado dentro da fun��o.
********************************/
void SalvaOffScreenPNG(char *nomeArquivoPNG){
    jogo->SalvaOffScreenPNG(nomeArquivoPNG);
}

/********************************
A fun��o PintaAreaOffScreen() serve para mudar a cor de uma �rea cont�gua de pixels da mesma cor.
A funcionalidade � semelhante � ferramenta "balde" dos editores de imagem. A �rea ser� pintada a partir do
ponto (posicaoX,posicaoY) de acordo com o sistema de coordenadas da PIG. A fun��o de pintura padr�o pode ser
substitu�da por outra fun��o customizada qualquer com o comando DefineFuncaoPintarAreaOffscreen().
Par�metros:
posicaoX (entrada, passagem por valor): indica o ponto no eixo X para come�ar a pintar a �rea cont�gua de pixels.
posicaoY (entrada, passagem por valor): indica o ponto no eixo Y para come�ar a pintar a �rea cont�gua de pixels.
cor (entrada, passagem por valor): indica a cor que deve ser usada durante a pintura da �rea cont�gua de pixels.
ponteiro (entrada, passagem por refer�ncia): ponteiro para qualquer tipo de estrutura a ser usada na fun��o customizada de pintura da �rea.
********************************/
void PintaAreaOffScreen(int posicaoX,int posicaoY,PIG_Cor cor,void *ponteiro=NULL){
    jogo->PintaAreaOffScreen(posicaoX,posicaoY,cor,ponteiro);
}

/********************************
A fun��o DefineFuncaoPintarAreaOffScreen() permite substituir a fun��o padr�o de pintura por outra fun��o customizada que deve ser passada como par�metro.
A fun��o de pintura deve ser definida de forma que receba 4 par�metros inteiros (respectivamente, a posi��o x e y do pixel que deve ser pintado e as
dimens�es - altura e largura - da imagem offscreen) e 2 cores (a cor atual do pixel e a cor que deveria ser usada para pint�-lo). A fun��o deve tamb�m retornar
o valor de uma cor, que ser� a cor efetivamente utilizada para pintar o pixel em quest�o. A fun��o, portanto, deve definir para cada ponto solicitado qual a cor
final daquele ponto.
Par�metros:
funcao (entrada, passagem por refer�ncia): nome da fun��o customizada para pintar uma �rea no renderizador offscreen.
********************************/
void DefineFuncaoPintarAreaOffscreen(PIG_Cor (*funcao)(int,int,int,int,PIG_Cor,PIG_Cor)){
    jogo->DefineFuncaoPintarArea(funcao);
}

/********************************
A fun��o MoveCanetaOffScreen() reposiciona a caneta do renderizador offscreen em algum outro ponto da imagem.
Par�metros:
novoX (entrada, passagem por valor): nova posi��o no eixo X na qual a caneta ser� reposicionada. O tipo de par�metro � double mas ser� convertido para int, dentro da fun��o.
novoY (entrada, passagem por valor): nova posi��o no eixo Y na qual a caneta ser� reposicionada. O tipo de par�metro � dpuble mas ser� convertido para int, dentro da fun��o.
********************************/
void MoveCanetaOffscreen(double novoX,double novoY){
    jogo->MoveCanetaOffscreen(novoX,novoY);
}

/********************************
A fun��o AvancaCanetaOffScreen() cria uma linha no renderizador offscreen na dire��o e sentido nos quais a canete est� orientada.
Par�metros:
distancia (entrada, passagem por valor): dist�ncia a ser percorrida pela caneta. O tipo de par�metro � double para permitir que o c�lculo da dist�ncia seja feito livremente.
********************************/
void AvancaCanetaOffscreen(double distancia){
    jogo->AvancaCanetaOffscreen(distancia);
}

/********************************
A fun��o MudaCorCanetaOffScreen() modifica a cor a ser utilizada pela caneta do renderizador offscreen daqui por diante. Desenhos feitos anteriormente permancem com a cor com a qual foram feitos.
Par�metros:
novaCor (entrada, passagem por valor): valor da nova cor a ser utilizada pela caneta do renderizador offscreen.
********************************/
void MudaCorCanetaOffscreen(PIG_Cor novaCor){
    jogo->MudaCorCanetaOffscreen(novaCor);
}

/********************************
A fun��o GiraCanetaHorarioOffScreen() gira a caneta do renderizador offscreen. A caneta passa a ter uma nova dire��o e sentido. Se o comando AvancaCanetaOffscreen() for executado posteriormente,
esses novos valores de dire��o e sentido ser�o utilizados para que o ponto final do tra�o seja calculado.
Par�metros:
angulo (entrada, passagem por valor): valor do �ngulo (sentido hor�rio, em radianos) pelo qual a caneta ser� redirecionada.
********************************/
void GiraCanetaHorarioOffscreen(double angulo){
    jogo->GiraCanetaHorarioOffscreen(angulo);
}

/********************************
A fun��o GiraCanetaAntiHorarioOffScreen() gira a caneta do renderizador offscreen. A caneta passa a ter uma nova dire��o e sentido. Se o comando AvancaCanetaOffscreen() for executado posteriormente,
esses novos valores de dire��o e sentido ser�o utilizados para que o ponto final do tra�o seja calculado.
Par�metros:
angulo (entrada, passagem por valor): valor do �ngulo (sentido anti-hor�rio, em radianos) pelo qual a caneta ser� redirecionada.
********************************/
void GiraCanetaAntiHorarioOffscreen(double angulo){
    jogo->GiraCanetaAntiHorarioOffscreen(angulo);
}

/********************************
A fun��o GiraCanetaAnguloFixoOffScreen() gira a caneta do renderizador offscreen. A caneta passa a ter uma nova dire��o e sentido. Se o comando AvancaCanetaOffscreen() for executado posteriormente,
esses novos valores de dire��o e sentido ser�o utilizados para que o ponto final do tra�o seja calculado.
Par�metros:
angulo (entrada, passagem por valor): valor do �ngulo usando como refer�ncia o �ngulo 0 do c�rculo trigonom�trico.
********************************/
void GiraCanetaAnguloFixoOffscreen(double angulo){
    jogo->GiraCanetaAnguloFixoOffscreen(angulo);
}

/********************************
A fun��o GetAnguloAtualOffScreen() recupera o �ngulo atual que est� sendo usado pela caneta do renderizador offscreen.
Retorno:
n�mero real que representa o valor do �ngulo atual, tendo como refer�ncia o �ngulo 0 do c�rculo trigonom�trico.
********************************/
double GetAnguloAtualOffscreen(){
    return jogo->GetAngAtual();
}

/********************************
A fun��o GetXCanetaOffScreen() recupera a posi��o no eixo X na qual est� posicionada atualmente a caneta do renderizador offscreen.
Retorno:
inteiro que representa a posi��o atual da caneta no eixo X.
********************************/
int GetXCanetaOffscreen(){
    return jogo->GetXCaneta();
}

/********************************
A fun��o GetYCanetaOffScreen() recupera a posi��o no eixo Y na qual est� posicionada atualmente a caneta do renderizador offscreen.
Retorno:
inteiro que representa a posi��o atual da caneta no eixo Y.
********************************/
int GetYCanetaOffscreen(){
    return jogo->GetYCaneta();
}

/********************************
A fun��o PintaFundoOffScreen() serve para "limpar" o bitmap offscreen, mudando completamente para cor indicada.
Par�metros:
cor (entrada, passagem por valor): indica a cor que deve ser usada durante a pintura completa do bitmap offscreen.
********************************/
void PintaFundoOffScreen(PIG_Cor cor){
    jogo->PintaFundoOffScreen(cor);
}

/********************************
A fun��o DesenhaRetanguloOffScreen() � respons�vel por desenhar um ret�ngulo cem preenchimento s�lido no bitmap offscreen em uma posi��o desejada pelo usu�rio.
O sistema de coordenadas � o mesmo da tela, com o eixo Y aumentando para cima.
Par�metros:
posicaoX (entrada, passagem por valor): Valor da coordenada X onde o usu�rio deseja colocar o ret�ngulo.
posicaoY (entrada, passagem por valor): Valor da coordenada Y onde o usu�rio deseja colocar o ret�ngulo.
altura (entrada, passagem por valor): Valor onde o usu�rio ir� fornecer o n�mero correspondente em pixels � altura desse ret�ngulo.
largura (entrada, passagem por valor): Valor onde o usu�rio ir� fornecer o n�mero correspondente em pixels � largura desse ret�ngulo.
cor (entrada, passagem por valor): indica a cor no sistema RGB para o preenchimento do ret�ngulo;
********************************/
void DesenhaRetanguloOffScreen(int x1,int y1,int altura,int largura,PIG_Cor cor){
    jogo->DesenhaRetanguloOffScreen(x1,y1,altura,largura,cor);
}

/********************************
A fun��o DesenhaRetanguloVazadoOffScreen() � respons�vel por desenhar um ret�ngulo sem preenchimento no bitmap offscreen em uma posi��o desejada pelo usu�rio.
O sistema de coordenadas � o mesmo da tela, com o eixo Y aumentando para cima.
Par�metros:
posicaoX (entrada, passagem por valor): Valor da coordenada X onde o usu�rio deseja colocar o ret�ngulo.
posicaoY (entrada, passagem por valor): Valor da coordenada Y onde o usu�rio deseja colocar o ret�ngulo.
altura (entrada, passagem por valor): Valor onde o usu�rio ir� fornecer o n�mero correspondente em pixels � altura desse ret�ngulo.
largura (entrada, passagem por valor): Valor onde o usu�rio ir� fornecer o n�mero correspondente em pixels � largura desse ret�ngulo.
cor (entrada, passagem por valor): indica a cor no sistema RGB para a borda do ret�ngulo;
********************************/
void DesenhaRetanguloVazadoOffScreen(int x1,int y1,int altura,int largura,PIG_Cor cor){
    jogo->DesenhaRetanguloVazadoOffScreen(x1,y1,altura,largura,cor);
}

/********************************
A fun��o DesenhaLinhasSimplesOffScreen() � respons�vel por desenhar no bitmap offscreen uma �nica linha, cuja in�cio � o ponto (x1,y1) e o fim � o ponto (x2,y2).
Par�metros:
pontoX1 (entrada, passagem por valor): inteiro que indica o in�cio da linha no eixo X.
pontoY1 (entrada, passagem por valor): inteiro que indica o in�cio da linha no eixo Y.
pontoX2 (entrada, passagem por valor): inteiro que indica o fim da linha no eixo X.
pontoY2 (entrada, passagem por valor): inteiro que indica o fim da linha no eixo Y.
cor (entrada, passagem por valor): indica a cor no sistema RGB para o desenho das linhas;
********************************/
void DesenhaLinhaSimplesOffScreen(int x1,int y1,int x2,int y2,PIG_Cor cor){
    jogo->DesenhaLinhaOffScreen(x1,y1,x2,y2,cor);
}


/********************************
Se��o de fontes
********************************/

/********************************
A fun��o CriaFonteNormal() � respons�vel por disponibilizar uma nova fonte com preenchimento s�lido.
Par�metros:
nome (entrada, passagem por refer�ncia): nome do arquivo que cont�m a fonte (normalmente com extens�o ttf).
tamanho (entrada, passagem por valor): tamanho da fonte, que normalmente representa a altura m�dia (em pixels) dos caracteres da fonte.
corLetra (entrada, passagem por valor): representa a cor de preenchimento da fonte.
contorno (entrada, passagem por valor): representa a espessura do contorno que fonte ter�. Caso n�o seja desejado um contorno, basta utilizar um valor 0.
corContorno (entrada, passagem por valor): representa a cor do contorno da fonte.
estilo (entrada, passagem por valor): representa o estilo da fonte. Pode ser uma combina��o bin�ria de: ESTILO_NEGRITO, para negrito; ESTILO_SUBLINHADO, para sublinhado; ESTILO_ITALICO, para it�lico;
ESTILO_CORTADO, para uma linha horizontal � meia-altura. Caso nenhum estilo seja desejado, pode ser omitido ou usado ESTILO_NORMAL.
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica qual janela vai receber a fonte. Uma fonte s� pode ser usada na janela na qual foi criada.
retono:
inteiro que representa a ideintifica��o �nica da fonte. Futuras refer�ncia a esta fonte devem idenitific�-las pelo n�mero.
********************************/
int CriaFonteNormal(char *nome,int tamanho,PIG_Cor corLetra,int contorno,PIG_Cor corContorno,PIG_Estilo estilo=ESTILO_NORMAL,int idJanela=0){
    return jogo->CriaFonteNormal(nome,tamanho,estilo,corLetra,contorno,corContorno,idJanela);
}

/********************************
A fun��o CriaFonteFundo() � respons�vel por disponibilizar uma nova fonte com preenchimento de um bitmap espec�fico.
Par�metros:
nome (entrada, passagem por refer�ncia): nome do arquivo que cont�m a fonte (normalmente com extens�o ttf).
tamanho (entrada, passagem por valor): tamanho da fonte, que normalmente representa a altura m�dia (em pixels) dos caracteres da fonte.
arquivoFundo (entrada, passagem por refer�ncia): indica o nome do arquivo de imagem que servir� de fundo para a fonte.
contorno (entrada, passagem por valor): representa a espessura do contorno que fonte ter�. Caso n�o seja desejado um contorno, basta utilizar um valor 0.
corContorno (entrada, passagem por valor): representa a cor do contorno da fonte.
estilo (entrada, passagem por valor): representa o estilo da fonte. Pode ser uma combina��o bin�ria de: ESTILO_NEGRITO, para negrito; ESTILO_SUBLINHADO, para sublinhado; ESTILO_ITALICO, para it�lico;
ESTILO_CORTADO, para uma linha horizontal � meia-altura. Caso nenhum estilo seja desejado, pode ser omitido ou usado ESTILO_NORMAL.
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica qual janela vai receber a fonte. Uma fonte s� pode ser usada na janela na qual foi criada.
retono:
inteiro que representa a ideintifica��o �nica da fonte. Futuras refer�ncia a esta fonte devem idenitific�-las pelo n�mero.
********************************/
int CriaFonteFundo(char *nome,int tamanho,char *arquivoFundo,int contorno,PIG_Cor corContorno,PIG_Estilo estilo=ESTILO_NORMAL,int idJanela=0){
    return jogo->CriaFonteFundo(nome,tamanho,estilo,arquivoFundo,contorno,corContorno,idJanela);
}

/********************************
A fun��o CalculaLarguraPixels() por realizar a soma das larguras de cada letra da string informada.
Par�metros:
str (entrada, passagem por refer�ncia): string a ser escrita na tela.
numFonte (entrada, passagem por valor): n�mero da fonte a ser utilizada. Caso o usu�rio n�o deseje uma fonte especial, ser� utilizada a fonte padr�o (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
retorno:
inteiro que representa o total de pixels (no eixo x) necess�rios para escrever a string.
********************************/
int CalculaLarguraPixels(char *str,int numFonte=0){
    return jogo->GetLarguraPixels(str);
}

/********************************
A fun��o EscreverDireita() � respons�vel por exibir uma string na tela de jogo, com alinhamento � direita do valor de X.
Par�metros:
str (entrada, passagem por refer�ncia): string a ser escrita na tela.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usu�rio deseja come�ar a escrever a string.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usu�rio deseja come�ar a escrever a string.
numFonte (entrada, passagem por valor): n�mero da fonte a ser utilizada. Caso o usu�rio n�o deseje uma fonte especial, ser� utilizada a fonte padr�o (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
********************************/
void EscreverDireita(char *str,int posicaoX,int posicaoY,int numFonte=0){
    jogo->EscreverDireita(str,posicaoX,posicaoY,numFonte);
}

/********************************
A fun��o EscreverEsquerda() � respons�vel por exibir uma string na tela de jogo, com alinhamento � esquerda do valor de X.
Par�metros:
str (entrada, passagem por refer�ncia): string a ser escrita na tela.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usu�rio deseja come�ar a escrever a string.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usu�rio deseja come�ar a escrever a string.
numFonte (entrada, passagem por valor): n�mero da fonte a ser utilizada. Caso o usu�rio n�o deseje uma fonte especial, ser� utilizada a fonte padr�o (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
********************************/
void EscreverEsquerda(char *str,int posicaoX,int posicaoY,int numFonte=0){
    jogo->EscreverEsquerda(str,posicaoX,posicaoY,numFonte);
}

/********************************
A fun��o EscreverCentralizada() � respons�vel por exibir uma string na tela de jogo, com alinhamento em rela��o ao valor de X.
Par�metros:
str (entrada, passagem por refer�ncia): string a ser escrita na tela.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usu�rio deseja come�ar a escrever a string.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usu�rio deseja come�ar a escrever a string.
numFonte (entrada, passagem por valor): n�mero da fonte a ser utilizada. Caso o usu�rio n�o deseje uma fonte especial, ser� utilizada a fonte padr�o (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
********************************/
void EscreverCentralizada(char *str,int posicaoX,int posicaoY,int numFonte=0){
    jogo->EscreverCentralizada(str,posicaoX,posicaoY,numFonte);
}

/********************************
Se��o de objetos
********************************/

/********************************
A fun��o CriaObjeto() � respons�vel por criar um objeto. Qualquer objeto que for necess�rio,
pode ser criado atrav�s dessa fun��o. O objeto ainda n�o ser� desenhado, apenas criado dentro do jogo.
Par�metros:
nomeArquivo (entrada, passagem por refer�ncia): string que informa o nome do arquivo da imagem do objeto a ser criado.
retiraFundo (entrada, passagem por valor): inteiro que indica se o fundo da imagem deve ser retirado ou n�o ao ler o arquivo em quest�o. O valor padr�o � 1, indicando que o fundo deve ser retirado.
opacidade (entrada,passagem por valor): n�vel de opacidade do objeto na faixa 0-255. O valor padr�o � 255, indicando n�vel m�ximo de opacidade.
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica qual janela vai receber o objeto.
Retorno:
inteiro que representa o identificador �nico do objeto. Todas as opera��es subsequentes com este objeto dever�o receber este identificador como par�metro.
********************************/
int CriaObjeto(char* nomeArquivo,int retiraFundo=1,int opacidade=255, int idJanela=0){
    return CGerenciadorObjetos::CriaObjeto(0,0,nomeArquivo,retiraFundo,opacidade,idJanela);
}

/********************************
A fun��o CriaObjetoOffScreen() � respons�vel por criar um objeto a partir da imagem que est� sendo montanda pelo
renderizador Offscreen. O renderizador precisa ter sido preparado anteriormente.
Par�metros:
retiraFundo (entrada, passagem por valor): inteiro que indica se o fundo da imagem deve ser retirado ou n�o ao ler o arquivo em quest�o. O valor padr�o � 1, indicando que o fundo deve ser retirado.
opacidade (entrada,passagem por valor): n�vel de opacidade do objeto na faixa 0-255. O valor padr�o � 255, indicando n�vel m�ximo de opacidade.
Retorno:
inteiro que representa o identificador �nico do objeto. Todas as opera��es subsequentes com este objeto dever�o receber este identificador como par�metro.
********************************/
int CriaObjetoOffScreen(int retiraFundo=1,int opacidade=255){
    return CGerenciadorObjetos::CriaObjetoOffScreen(0,0,jogo->offRenderer,retiraFundo,opacidade);
}

/********************************
A fun��o DestroiObjeto() � respons�vel por eliminar o objeto em quest�o do jogo.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto a ser exclu�do.
********************************/
void DestroiObjeto(int idObjeto){
    CGerenciadorObjetos::DestroiObjeto(idObjeto);
}

/********************************
A fun��o SetValorIntObjeto() � respons�vel incorporar a um objeto um atributo inteiro.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por valor): relaciona um n�mero inteiro ao atributo.
valor (entrada, passagem por valor): valor do atributo inteiro a ser associado ao objeto.
********************************/
void SetValorIntObjeto(int idObjeto,int indice,int valor){
    CGerenciadorObjetos::SetValorIntObjeto(idObjeto,indice,valor);
}

/********************************
A fun��o SetValorFloatObjeto() � respons�vel incorporar a um objeto um atributo float.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por valor): relaciona um n�mero inteiro ao atributo.
valor (entrada, passagem por valor): valor do atributo float a ser associado ao objeto.
********************************/
void SetValorFloatObjeto(int idObjeto,int indice,float valor){
    CGerenciadorObjetos::SetValorFloatObjeto(idObjeto,indice,valor);
}

/********************************
A fun��o SetValorIntObjeto() � respons�vel incorporar a um objeto um atributo inteiro.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por valor): relaciona um n�mero inteiro ao atributo.
valor (entrada, passagem por refer�ncia): valor do atributo string a ser associado ao objeto.
********************************/
void SetValorStringObjeto(int idObjeto,int indice,char *valor){
    CGerenciadorObjetos::SetValorStringObjeto(idObjeto,indice,valor);
}

/********************************
A fun��o SetValorIntObjeto() � respons�vel incorporar a um objeto um atributo inteiro.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por refer�ncia): relaciona uma string ao atributo.
valor (entrada, passagem por valor): valor do atributo inteiro a ser associado ao objeto.
********************************/
void SetValorIntObjeto(int idObjeto,char *indice,int valor){
    CGerenciadorObjetos::SetValorIntObjeto(idObjeto,indice,valor);
}

/********************************
A fun��o SetValorFloatObjeto() � respons�vel incorporar a um objeto um atributo float.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por refer�ncia): relaciona uma string ao atributo.
valor (entrada, passagem por valor): valor do atributo float a ser associado ao objeto.
********************************/
void SetValorFloatObjeto(int idObjeto,char *indice,float valor){
    CGerenciadorObjetos::SetValorFloatObjeto(idObjeto,indice,valor);
}

/********************************
A fun��o SetValorIntObjeto() � respons�vel incorporar a um objeto um atributo inteiro.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por refer�ncia): relaciona uma string ao atributo.
valor (entrada, passagem por refer�ncia): valor do atributo string a ser associado ao objeto.
********************************/
void SetValorStringObjeto(int idObjeto,char *indice,char *valor){
    CGerenciadorObjetos::SetValorStringObjeto(idObjeto,indice,valor);
}

/********************************
A fun��o GetValorIntObjeto() � respons�vel recuperar o valor de um atributo inteiro relacionado a um objeto.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por valor): indica o n�mero do atributo que se deseja recuperar.
valor (sa�da, passagem por refer�ncia): indica o valor do atributo, se a fun��o retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo n�o existir, a fun��o retorna o valor 0 (zero).
********************************/
int GetValorIntObjeto(int idObjeto,int indice,int *valor){
    return CGerenciadorObjetos::GetValorIntObjeto(idObjeto,indice,valor);
}

/********************************
A fun��o GetValorFloatObjeto() � respons�vel recuperar o valor de um atributo float relacionado a um objeto.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por valor): indica o n�mero do atributo que se deseja recuperar.
valor (sa�da, passagem por refer�ncia): indica o valor do atributo, se a fun��o retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo n�o existir, a fun��o retorna o valor 0 (zero).
********************************/
int GetValorFloatObjeto(int idObjeto,int indice,float *valor){
    return CGerenciadorObjetos::GetValorFloatObjeto(idObjeto,indice,valor);
}

/********************************
A fun��o GetValorStringObjeto() � respons�vel recuperar o valor de um atributo string relacionado a um objeto.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por valor): indica o n�mero do atributo que se deseja recuperar.
valor (sa�da, passagem por refer�ncia): indica o valor do atributo, se a fun��o retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo n�o existir, a fun��o retorna o valor 0 (zero).
********************************/
int GetValorStringObjeto(int idObjeto,int indice,char *valor){
    return CGerenciadorObjetos::GetValorStringObjeto(idObjeto,indice,valor);
}

/********************************
A fun��o GetValorIntObjeto() � respons�vel recuperar o valor de um atributo inteiro relacionado a um objeto.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por refer�ncia): indica o nome do atributo que se deseja recuperar.
valor (sa�da, passagem por refer�ncia): indica o valor do atributo, se a fun��o retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo n�o existir, a fun��o retorna o valor 0 (zero).
********************************/
int GetValorIntObjeto(int idObjeto,char *indice,int *valor){
    return CGerenciadorObjetos::GetValorIntObjeto(idObjeto,indice,valor);
}

/********************************
A fun��o GetValorFloatObjeto() � respons�vel recuperar o valor de um atributo float relacionado a um objeto.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por valor): indica o nome do atributo que se deseja recuperar.
valor (sa�da, passagem por refer�ncia): indica o valor do atributo, se a fun��o retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo n�o existir, a fun��o retorna o valor 0 (zero).
********************************/
int GetValorFloatObjeto(int idObjeto,char *indice,float *valor){
    return CGerenciadorObjetos::GetValorFloatObjeto(idObjeto,indice,valor);
}

/********************************
A fun��o GetValorStringObjeto() � respons�vel recuperar o valor de um atributo string relacionado a um objeto.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por valor): indica o nome do atributo que se deseja recuperar.
valor (sa�da, passagem por refer�ncia): indica o valor do atributo, se a fun��o retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo n�o existir, a fun��o retorna o valor 0 (zero).
********************************/
int GetValorStringObjeto(int idObjeto,char *indice,char *valor){
    return CGerenciadorObjetos::GetValorStringObjeto(idObjeto,indice,valor);
}

/********************************
A fun��o GetXYObjeto() � respons�vel recuperar o valor da posi��o (X,Y) do objeto de acordo com o sistema de coordenadas do jogo.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
posicaoX (sa�da, passagem por referencia): indica a posicao no eixo X do objeto.
posicaoY (sa�da, passagem por referencia): indica a posicao no eixo Y do objeto.
********************************/
void GetXYObjeto(int idObjeto,int *posicaoX,int *posicaoY){
    CGerenciadorObjetos::GetPosicaoXY(idObjeto,posicaoX,posicaoY);
}

/********************************
A fun��o MoveObjeto() � respons�vel por movimentar um determinado obeto para uma nova posi��o informada.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto a ser movido.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usu�rio deseja reposicionar o objeto.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usu�rio deseja reposicionar o objeto.
********************************/
void MoveObjeto(int idObjeto,int posicaoX,int posicaoY){
    CGerenciadorObjetos::Move(idObjeto,posicaoX,posicaoY);
}

/********************************
A fun��o SetAnguloObjetoo() � respons�vel pela angula��o de determinado objeto. A angula��o � calculada em sentido
hor�rio a partir do eixo X (0 graus). O objeto ser� desenhado com a angula��o informada no pr�ximo comando
DesenhaObjeto(). A detec��o de colis�o n�o funciona com objetos fora da angula��o padr�o (0 graus).
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
angulo (entrada, passagem por valor): valor para indicar a angula��o do objeto em graus.
********************************/
void SetAnguloObjeto(int idObjeto, float angulo){
    CGerenciadorObjetos::SetAngulo(idObjeto,angulo);
}

/********************************
A fun��o GetAnguloObjeto() � respons�vel por recuperar o �ngulo de rota��o de determinado objeto. A angula��o � calculada em sentido
hor�rio a partir do eixo X (0 graus). O objeto ser� desenhado com a angula��o informada no pr�ximo comando
DesenhaObjeto(). A detec��o de colis�o n�o funciona com objetos fora da angula��o padr�o (0 graus).
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
Retorno:
Retorna o valor do �ngulo em graus.
********************************/
float GetAnguloObjeto(int idObjeto){
    return CGerenciadorObjetos::GetAngulo(idObjeto);
}

/********************************
A fun��o SetPivoObjeto() define um ponto (X,Y) em rela��o ao ponto (0,0) do objeto, sobre o qual o objeto ser�
rotacionado quando a fun��o SetAnguloObjeto() for executada.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
posicaoX (entrada, passagem por valor): Valor da coordenada X do piv� em rela��o ao ponto (0,0) do objeto.
posicaoY (entrada, passagem por valor): Valor da coordenada Y do piv� em rela��o ao ponto (0,0) do objeto.
********************************/
void SetPivoObjeto(int idObjeto,int posicaoX,int posicaoY){
    CGerenciadorObjetos::SetPivo(idObjeto,posicaoX,posicaoY);
}

/********************************
A fun��o SetPivoObjeto() define um ponto relativo (X,Y) em rela��o ao ponto (0,0) e ao tamanho do objeto, sobre o qual o objeto ser�
rotacionado quando a fun��o SetAnguloObjeto() for executada.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
relX (entrada, passagem por valor): porcentagem da largura do objeto onde ficar� o piv�.
relY (entrada, passagem por valor): porcentagem da altura do objeto onde ficar� o piv�.
********************************/
void SetPivoObjeto(int idObjeto,float relX,float relY){
    CGerenciadorObjetos::SetPivo(idObjeto,relX,relY);
}

/********************************
A fun��o GetPivoObjeto() define um ponto (X,Y) em rela��o ao ponto (0,0) do objeto, sobre o qual o objeto ser�
rotacionado quando a fun��o SetAnguloObjeto() for executada.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
posicaoX (sa�da, passagem por refer�ncia): Valor da coordenada X do piv� em rela��o ao ponto (0,0) do objeto.
posicaoY (sa�da, passagem por refer�ncia): Valor da coordenada Y do piv� em rela��o ao ponto (0,0) do objeto.
********************************/
void GetPivoObjeto(int idObjeto,int *posicaoX,int *posicaoY){
    CGerenciadorObjetos::GetPivo(idObjeto,posicaoX,posicaoY);
}

/********************************
A fun��o SetFlipObjeto() � respons�vel por virar o objeto, invertendo-o em alguma dire��o. O objeto somente ser�
desenhado na nova orienta��o no pr�ximo comando DesenhaObjeto().
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto a ser virado.
valor (entrada, passagem por valor): valor do tipo de Flip. Pode ser FLIP_NENHUM (nenhum tipo de invers�o),
FLIP_HORIZONTAL (inverte da esquerda para a direita), FLIP_VERTICAL (inverte de cima para baixo),
ou FLIP_HORIZ_VERT (inverte da esquerda para direita e de cima para baixo).
********************************/
void SetFlipObjeto(int idObjeto,PIG_Flip valor){
    CGerenciadorObjetos::SetFlip(idObjeto,valor);
}

/********************************
A fun��o GetFlipObjeto() � respons�vel por recuperar o valor da manipula��o causada pela fun��o SetFlipObjeto().
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto a ser virado.
Retorno:
inteiro que indica o tipo de Flip. Pode ser FLIP_NENHUM (nenhum tipo de invers�o),
FLIP_HORIZONTAL (inverte da esquerda para a direita), FLIP_VERTICAL (inverte de cima para baixo),
ou FLIP_HORIZ_VERT (inverte da esquerda para direita e de cima para baixo).
********************************/
PIG_Flip GetFlipObjeto(int idObjeto){
    return CGerenciadorObjetos::GetFlip(idObjeto);
}

/********************************
A fun��o SetDimensoesObjeto() � respons�vel por delimitar a altura e a largura do objeto que ser� desenhado na tela,
independentemente do tamanho original do arquivo de imagem.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
altura (entrada, passagem por valor): altura em pixels.
largura (entrada, passagem por valor): largura em pixels.
********************************/
void SetDimensoesObjeto(int idObjeto, int altura, int largura){
    CGerenciadorObjetos::SetDimensoes(idObjeto,altura,largura);
}

/********************************
A fun��o GetDimensoesObjeto() � respons�vel por recuperar a altura e a largura da �rea a ser usada
para desenhar o objeto na tela. Em outras palavras, representa o tamanho atual do objeto.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
altura (sa�da, passagem por refer�ncia): altura atual em pixels do objeto.
largura (sa�da, passagem por refer�ncia): largura atual em pixels do objeto.
********************************/
void GetDimensoesObjeto(int idObjeto, int *altura, int *largura){
    CGerenciadorObjetos::GetDimensoes(idObjeto,altura,largura);
}

/********************************
A fun��o GetDimensoesOriginaisObjeto() � respons�vel por recuperar a altura e a largura originais da imagem
que foi usada para criar o objeto. Qualquer utiliza��o da fun��o SetDimensoesObjeto � ignorada para
o c�lculo desta fun��o.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
altura (sa�da, passagem por refer�ncia): altura original em pixels do objeto.
largura (sa�da, passagem por refer�ncia): largura original em pixels do objeto.
********************************/
void GetDimensoesOriginaisObjeto(int idObjeto, int *altura, int *largura){
    CGerenciadorObjetos::GetDimensoesOriginais(idObjeto,altura,largura);
}

/********************************
A fun��o DefineFrameObjeto() � respons�vel por delimitar o posicionamento dos pixels do arquivo de imagem que ser�o
utilizados para representar o objeto na tela. Desta forma, nem toda a imagem ser� automaticamente utilizada para
representar o objeto. O sistema de coordenadas deve ser o padr�o dos arquivos de imagem, com o eixo Y aumentando para baixo.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto a ser desenhado.
xBitmap (entrada, passagem por valor): indica a posi��o de eixo X onde come�a o frame.
yBitmap (entrada, passagem por valor): indica a posi��o de eixo Y onde come�a o frame. Neste caso, o eixo Y aumenta para baixo.
altura (entrada, passagem por valor): altura em pixels do frame.
largura (entrada, passagem por valor): largura em pixels do frame.
********************************/
void DefineFrameObjeto(int idObjeto,int xBitmap, int yBitmap,int altura,int largura){
    CGerenciadorObjetos::CriaFrame(idObjeto,xBitmap,yBitmap,altura,largura);
}

/********************************
A fun��o SetColoracaoObjeto() � respons�vel por mesclar uma determinada cor com os pixels do arquivo de imagem.
Ap�s a modifica��o, todos os desenhos deste objeto ser�o mostrados j� com a mesclagem definida.
Para voltar ao padr�o original de pixels, deve-se chamar a fun��o, passando a cor branca (255,255,255).
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto a ser desenhado.
cor (entrada,passagem por valor): cor do sistema RGB utilizada para mesclagem com o arquivo de imagem
********************************/
void SetColoracaoObjeto(int idObjeto,PIG_Cor cor){
    CGerenciadorObjetos::SetColoracao(idObjeto,cor);
}

/********************************
A fun��o SetOpacidadeObjeto() � respons�vel por modificar o n�vel de opacidade do objeto.
O n�vel de opacidade varia de 0-255, sendo 0 totalmente transparente e 255 totalmente opaco.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
valor (entrada,passagem por valor): n�vel de opacidade do objeto na faixa 0-255.
********************************/
void SetOpacidadeObjeto(int idObjeto,int valor){
    CGerenciadorObjetos::SetOpacidade(idObjeto,valor);
}

/********************************
A fun��o DesenhaObjeto() � respons�vel por desenhar um objeto na tela ou no Renderizador Offscreen. O objeto ser� desenhado de acordo com todas as defini��es
de posi��o e �ngulo informado at� o momento. Al�m disso, se o objeto estiver virado (flipping), isso tamb�m ser� levado em considera��o.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto a ser desenhado.
offScreen (entrada, passagem por valor): indica se o objeto deve ser desenhado no Renderizador Offscreen.
********************************/
void DesenhaObjeto(int idObjeto,int offScreen=0){
    if (offScreen==0)
    CGerenciadorObjetos::Desenha(idObjeto,NULL);
    else CGerenciadorObjetos::Desenha(idObjeto,jogo->offRenderer);
}

/********************************
A fun��o TestaColisaoObjetos() � respons�vel por testar se dois objetos se colidiram ou n�o, ao passar
os identificadores dos objetos por par�metro.
Par�metros:
idObjeto1 (entrada, passagem por valor): identificador do primeiro objeto.
idObjeto2 (entrada, passagem por valor): identificador do segundo objeto.
Retorno:
Inteiro indicando se houve colis�o (valor diferente de zero) ou n�o (valor igual a 0, zero).
********************************/
int TestaColisaoObjetos(int idObjeto1,int idObjeto2){
    return CGerenciadorObjetos::TestaColisao(idObjeto1,idObjeto2);
}

/********************************
A fun��o GetPixelsObjeto() � respons�vel por extrair os pixels da imagem que originou o objeto, devolvendo-os como
uma matriz de pixels (PIG_Cor). Mudan�as nessa matriz s� ser�o validadas ap�s a chamada da fun��o AtualizaPixelsObjeto().
O linha 0 corresponde � primeira linha da imagem, ou seja, � linha superior, pois o sistema de coordenadas
das imagens tem o eixo Y aumentando para baixo.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
Retorno:
matriz de pixels (PIG_Cor) da imagem que gerou o objeto. O total de linhas da matriz � dado pela altura original do objeto e o
total de colunas � dado pela largura original do objeto. Ambos os valores podem ser obtidos pela fun��o GetDimensoesOriginaisObjeto().
********************************/
PIG_Cor **GetPixelsObjeto(int idObjeto){
    return CGerenciadorObjetos::GetPixels(idObjeto);
}

/********************************
A fun��o AtualizaPixelsObjeto() � respons�vel por efetivar quaisquer mudan�as nos pixels do objeto obtidos pela fun��o GetPixelsObjeto().
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
retiraFundo (entrada, passagem por valor): inteiro que indica se o fundo da imagem deve ser retirado ou n�o ao ler o arquivo em quest�o. O valor padr�o � 1, indicando que o fundo deve ser retirado.
opacidade (entrada,passagem por valor): n�vel de opacidade do objeto na faixa 0-255. O valor padr�o � 255, indicando n�vel m�ximo de opacidade.
********************************/
void AtualizaPixelsObjeto(int idObjeto,int retiraFundo=1,int opacidade=255){
    CGerenciadorObjetos::AtualizaPixels(idObjeto,retiraFundo,opacidade);
}

/********************************
Se��o de gerador de part�culas
********************************/

/********************************
A fun��o CriaGeradorParticulas() cria um novo gerador de part�culas (GDP). As part�culas em si precisam ser criadas
posteriormente atrav�s da fun��o CriaParticula(), passando o identificador do GDP como par�metro.
Par�metros:
maxParticulas (entrada, passagem por valor): informa o maior n�mero de part�culas que o gerador ter� simultaneamente. O maior valor aceito � 1000 part�culas.
nomeArquivo (entrada, passagem por refer�ncia): indica o caminho relativo ou absoluto do arquivo de imagem,
que ser� utilizado para cada part�cula do GDP.
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica qual janela vai receber o GDP.
********************************/
int CriaGeradorParticulas(int maxParticulas,char* nomeArquivo,int idJanela=0){
    return CGerenciadorParticulas::CriaGeradorParticulas(maxParticulas,nomeArquivo,idJanela);
}

/********************************
A fun��o DestroiGeradorParticulas() encerra um gerador de part�culas (GDP). Todas as part�culas relacionadas a ele tamb�m s�o finalizadas
neste momento.
Par�metros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da fun��o CriaGeradorParticulas().
********************************/
void DestroiGeradorParticulas(int idGerador){
    CGerenciadorParticulas::DestroiGeradorParticulas(idGerador);
}

/********************************
A fun��o MoveGeradorParticulas() reposiciona um gerador de part�culas (GDP). Na pr�tica, isto significa que as novas part�culas que
forem criadas posteriormente ter�o esse ponto de origem.
Par�metros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da fun��o CriaGeradorParticulas().
posicaoX (entrada, passagem por valor): informa a nova posi��o X do GDP, em rela��o ao sistema de coordenadas do jogo.
posicaoY (entrada, passagem por valor): informa a nova posi��o Y do GDP, em rela��o ao sistema de coordenadas do jogo.
********************************/
void MoveGeradorParticulas(int idGerador,int posicaoX,int posicaoY){
    CGerenciadorParticulas::Move(idGerador,posicaoX,posicaoY);
}

/********************************
A fun��o MudaDirecaoParticulas() modifica a dire��o na qual as part�culas se movimentar�o ap�s serem criadas.
Somente as part�culas criadas posteriormente seguir�o a dire��o especificada.
Par�metros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da fun��o CriaGeradorParticulas().
valorX (entrada, passagem por valor): informa a componente X da dire��o a ser definida para as part�culas.
valorY (entrada, passagem por valor): informa a componente Y da dire��o a ser definida para as part�culas.
********************************/
void MudaDirecaoParticulas(int idGerador,int valorX,int valorY){
    CGerenciadorParticulas::MudaDirecaoParticulas(idGerador,valorX,valorY);
}

/********************************
A fun��o MudaRotacaoParticulas() modifica a velocidade angular das part�culas ap�s serem criadas.
Somente as part�culas criadas posteriormente seguir�o a velocidade angular especificada.
Par�metros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da fun��o CriaGeradorParticulas().
angPerSec (entrada, passagem por valor): informa a velocidade em graus por segundo.
********************************/
void MudaRotacaoParticulas(int idGerador,float grausPerSec){
    CGerenciadorParticulas::MudaRotacaoParticulas(idGerador,grausPerSec);
}

/********************************
A fun��o MudaEscalaParticulas() modifica o tamanho das part�culas ap�s serem criadas, durante o seu tempo de vida.
Somente as part�culas criadas posteriormente seguir�o a velocidade angular especificada.
Par�metros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da fun��o CriaGeradorParticulas().
escalaInicial (entrada, passagem por valor): informa a escala da part�cula ao ser criada.
escalaFinal (entrada, passagem por valor): informa a escala da part�cula ao final do seu tempo de vida.
********************************/
void MudaEscalaParticulas(int idGerador,float escalaInicial,float escalaFinal){
    CGerenciadorParticulas::MudaEscalaParticulas(idGerador,escalaInicial,escalaFinal);
}

/********************************
A fun��o SetPivoParticulas() determina o ponto a ser considerado como pivo da part�cula.
Somente as part�culas criadas posteriormente seguir�o a velocidade angular especificada.
Par�metros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da fun��o CriaGeradorParticulas().
posicaoX (entrada, passagem por valor): Valor da coordenada X do piv� em rela��o ao ponto (0,0) da part�cula.
posicaoY (entrada, passagem por valor): Valor da coordenada Y do piv� em rela��o ao ponto (0,0) da part�cula.
********************************/
void SetPivoParticulas(int idGerador,int posicaoX,int posicaoY){
    CGerenciadorParticulas::MudaEscalaParticulas(idGerador,posicaoX,posicaoY);
}

/********************************
A fun��o CriaParticula() adiciona uma nova part�cula ao jogo relacionada com o GDP passado como par�metro.
Par�metros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da fun��o CriaGeradorParticulas().
fadingOut (entrada, passagem por valor): valor l�gico que indica se a part�cula deve esmaecer ao longo do tempo.
minX (entrada, passagem por valor): valor m�nimo de X para que a part�cula seja considerada ativa
minY (entrada, passagem por valor): valor m�nimo de Y para que a part�cula seja considerada ativa
maxX (entrada, passagem por valor): valor m�ximo de X para que a part�cula seja considerada ativa
maxY (entrada, passagem por valor): valor m�ximo de Y para que a part�cula seja considerada ativa
maxTempo (entrada, passagem por valor): tempo de vida da part�cula
Retorno:
inteiro indicando se a part�cula foi criada (valor maior ou igual a zero) ou n�o (valor menor do que zero).
A part�cula n�o ser� criada se j� houver o n�mero m�ximo de part�culas ativas.
********************************/
int CriaParticula(int idGerador,int fadingOut=0,int minX=-50,int minY=-50,int maxX=LARG_TELA+50,int maxY=ALT_TELA+50,float maxTempo=999999.9){
    return CGerenciadorParticulas::CriaParticula(idGerador,fadingOut,minX,minY,maxX,maxY,maxTempo);
}

/********************************
A fun��o MoveParticulas() faz com que todas as part�cula ativas do GDP em quest�o se movimentem de acordo com as componentes
X e Y passadas na fun��o MudaDirecaoParticulas(). As part�culas que sa�rem da tela de jogo ou aqueles que j� existerm a mais de 10000 segundos
ser�o consideradas inativas e deixar�o de existir.
Par�metros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da fun��o CriaGeradorParticulas().
********************************/
void MoveParticulas(int idGerador){
    CGerenciadorParticulas::MoveParticulas(idGerador);
}

/********************************
A fun��o QuantidadeParticulasAtivas() indica quantas part�culas do GDP em quest�o ainda est�o ativas. As part�culas deixam de
ser ativas quando saem da tela do jogo, quando colidem com algum objeto ou depois de 10000 segundos de vida.
Par�metros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da fun��o CriaGeradorParticulas().
Retorno:
inteiro que indica o n�mero de part�culas ativas.
********************************/
int QuantidadeParticulasAtivas(int idGerador){
    return CGerenciadorParticulas::GetQtdAtivas(idGerador);
}

/********************************
A fun��o DesenhaParticulas() desenha todas as part�culas ativas do GDP na posi��o que estiverem.
Par�metros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da fun��o CriaGeradorParticulas().
********************************/
void DesenhaParticulas(int idGerador){
    CGerenciadorParticulas::Desenha(idGerador);
}

/********************************
A fun��o ColisaoParticulasObjeto() indica se houve colis�o de alguma part�cula ativa do GDP com um outro objeto espec�fico, atrav�s do seu identificador.
Par�metros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da fun��o CriaGeradorParticulas().
idObjeto (entrada, passagem por valor): identificador do objeto que pode ter colidido com as part�culas do GDP.
Retorno:
inteiro que indica se houve colis�o de alguma part�cula ativa do GDP (valor diferente de zero) ou n�o (valor igual a 0, zero).
********************************/
int ColisaoParticulasObjeto(int idGerador,int idObjeto){
    Objeto obj = CGerenciadorObjetos::GetObjeto(idObjeto);
    return CGerenciadorParticulas::Colisao(idGerador,obj);
}

/********************************
A fun��o ColisaoParticulasAnimacao() indica se houve colis�o de alguma part�cula ativa do GDP com uma outra anim��o espec�fica, atrav�s do seu identificador.
Par�metros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da fun��o CriaGeradorParticulas().
idAnimacao (entrada, passagem por valor): identificador da anima��o que pode ter colidido com as part�culas do GDP.
Retorno:
inteiro que indica se houve colis�o de alguma part�cula ativa do GDP (valor diferente de zero) ou n�o (valor igual a 0, zero).
********************************/
int ColisaoParticulasAnimacao(int idGerador,int idAnimacao){
    Animacao anima = CGerenciadorAnimacoes::GetAnimacao(idAnimacao);
    return CGerenciadorParticulas::Colisao(idGerador,anima);
}

/********************************
Se��o dos temporizadores
********************************/

/********************************
A fun��o CriaTimer() � respons�vel por criar um timer (temporizador). Ap�s a cria��o o tempo decorrido
poder� ser obtido a partir da fun��o TempoDecorrido(), informando o identificador que � passado na resposta.
Par�metros:
congelado (entrada, passagem por valor): valor l�gico que indica se o timer deve ser criado sem iniciar de imediato a contagem de tempo ou n�o.
Retorno:
inteiro que identifica o timer criado.
********************************/
int CriaTimer(int congelado=false){
    return CGerenciadorTimers::CriaTimer(congelado);
}

/********************************
A fun��o TempoDecorrido() � respons�vel por informar o tempo decorrido desde a cria��o do timer
at� a hora em que a fun��o for chamada.
Par�metros:
idTimer (entrada, passagem por valor): identificador do timer.
Retorno:
n�mero real indicando o tempo (em segundos) desde a cria��o do timer.
********************************/
float TempoDecorrido(int idTimer){
    return CGerenciadorTimers::GetTempoDecorrido(idTimer);
}

/********************************
A fun��o PausaTimer() � respons�vel por realizar uma pausa na contagem do tempo de um timer. Ap�s a despausa,
o timer continuar� a contar o tempo normalmente.
Par�metros:
idTimer (entrada, passagem por valor): identificador do timer.
********************************/
void PausaTimer(int idTimer){
    CGerenciadorTimers::PausaTimer(idTimer);
}

/********************************
A fun��o PausaTudo() � respons�vel por realizar uma pausa na contagem do tempo de todos os timers
criados pela fun��o CriaTimer();
********************************/
void PausaTudo(){
    CGerenciadorTimers::PausaTodos();
}

/********************************
A fun��o DespausaTimer() � respons�vel por retomar a contagem do tempo de um timer ap�s uma pausa.
Par�metros:
idTimer (entrada, passagem por valor): identificador do timer.
********************************/
void DespausaTimer(int idTimer){
    CGerenciadorTimers::DespausaTimer(idTimer);
}

/********************************
A fun��o DespausaTudo() � respons�vel por retomar a contagem do tempo de todos os timers
criados pela fun��o CriaTimer();
********************************/
void DespausaTudo(){
    CGerenciadorTimers::DespausaTodos();
}

/********************************
A fun��o ReiniciaTimer() � respons�vel por zerar a contagem do tempo de um timer, idependente do tempo j� decorrido.
Na pr�tica, � equivalente a encerrer um temporizador e recri�-lo em seguida.
Par�metros:
idTimer (entrada, passagem por valor): identificador do timer.
congelado (entrada, passagem por valor): valor l�gico que indica se o timer deve ser reiniciado sem iniciar de imediato a contagem de tempo ou n�o.
********************************/
void ReiniciaTimer(int idTimer, int congelado=false){
    CGerenciadorTimers::ReiniciaTimer(idTimer,congelado);
}

/********************************
A fun��o DestroiTimer() � respons�vel por encerrar a utiliza��o de timer.
Seu identificador n�o poder� ser utilizado ap�s a fun��o ser executada.
Par�metros:
idTimer (entrada, passagem por valor): identificador do timer.
********************************/
void DestroiTimer(int idTimer){
    CGerenciadorTimers::DestroiTimer(idTimer);
}

/********************************
Se��o das anima��es
********************************/

/********************************
A fun��o CriaAnimacao() � respons�vel por criar uma animacao. A anima��o pode ser considerada um tipo especial
de objeto, capaz de mudar de figura (sprite) dentro de um tempo determinado. Uma sequ�ncia completa de
sprites � chamada de modo. Uma mesma anim��o pode apresentar v�rios modos diferentes.
Para que a anima��o funcione corretamente, ser� necess�rio: definir cada frame (peda�o do arquivo bitmap que cont�m o sprite desejado),
criar um ou mais modos, inserir os frames criados no modo correspondente e dizer qual modo dever� ser exibido inicialmente.
Tudo isso pode ser feito por outras fun��es que manipulam as anima��es.
Par�metros:
nomeArquivo (entrada, passagem por refer�ncia): string que informa o nome do arquivo da imagem (spritesheet) da anima��o.
retiraFundo (entrada, passagem por valor): inteiro que indica se o fundo da imagem deve ser retirado ou n�o ao ler o arquivo em quest�o. O valor padr�o � 1, indicando que o fundo deve ser retirado.
opacidade (entrada,passagem por valor): n�vel de opacidade do objeto na faixa 0-255. O valor padr�o � 255, indicando n�vel m�ximo de opacidade.
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica qual janela vai receber a anima��o.
Retorno:
inteiro que representa o identificador �nico da anima��o. Todas as opera��es subsequentes com esta anima��o dever�o receber este identificador como par�metro.
********************************/
int CriaAnimacao(char* nomeArquivo,int retiraFundo=1,int opacidade=255,int idJanela=0){
    return CGerenciadorAnimacoes::CriaAnimacao(nomeArquivo,retiraFundo,opacidade,idJanela);
}

/********************************
A fun��o CriaAnimacao() � respons�vel por criar uma animacao. A anima��o pode ser considerada um tipo especial
de objeto, capaz de mudar de figura (sprite) dentro de um tempo determinado. Uma sequ�ncia completa de
sprites � chamada de modo. Uma mesma anim��o pode apresentar v�rios modos diferentes.
Esta forma de criar uma anima��o, copia todos os frames e modos de outra anima��o j� existente, evitando assim
que toda esta prepara��o precise ser feita novamente. O usu�rio deve ter cuidado de n�o destruir a anima��o
original enquanto as c�pias estiverem ativas ou haver� erros de execu��o. Da mesma forma, n�o se deve alterar os
frames ou os modos da c�pia, pois pode provocar erros na anima��o original.
Par�metros:
idAnimacao (entrada, passagem por valor): indica o identificador da anima��o original que ser� copiada.
Retorno:
inteiro que representa o identificador �nico da anima��o. Todas as opera��es subsequentes com esta anima��o dever�o receber este identificador como par�metro.
********************************/
int CriaAnimacao(int idAnimacao){
    return CGerenciadorAnimacoes::CriaAnimacao(idAnimacao);
}

/********************************
A fun��o DestroiAnimacao() � respons�vel por eliminar a anima��o em quest�o do jogo.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o a ser exclu�da.
********************************/
void DestroiAnimacao(int idAnimacao){
    CGerenciadorAnimacoes::DestroiAnimacao(idAnimacao);
}

/********************************
A fun��o CriaFrameAnimacao() � respons�vel por estabelecar uma parte do sprisheet da anima��o que cont�m um sprite espec�fico.
O frame criado deve ser posteriormente inserido em um ou mais modos da anima��o. O posicionamento do frame
respeita o sistema de coordenadas dos arquivos de imagem, com o eixo Y aumentando para baixo.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o a ter um novo frame.
codigoFrame (entrada, passagem por valor): numero do frame a ser criado. Pode ser usado qualquer n�mero de 0..MAX_FRAMES-1.
xBitmap (entrada, passagem por valor): indica a posi��o de eixo X onde come�a o frame.
yBitmap (entrada, passagem por valor): indica a posi��o de eixo Y onde come�a o frame. Neste caso, o eixo Y aumenta para baixo.
altura (entrada, passagem por valor): altura em pixels do frame.
largura (entrada, passagem por valor): largura em pixels do frame.
********************************/
void CriaFrameAnimacao(int idAnimacao,int codigoFrame,int xBitmap,int yBitmap,int altura,int largura){
    CGerenciadorAnimacoes::CriaFrame(idAnimacao,codigoFrame,xBitmap,yBitmap,altura,largura);
}

/********************************
A fun��o CriaModoAnimacao() � respons�vel por criar um modo, ou seja, uma sequ�ncia de sprites.
Ap�s a cria��o do modo, os frames deve ser inseridos um a um. O modo pode ser criado antes dos frames
e vice-versa, mas os frames s� podem ser associados ao modo, ap�s as respectivas cria��es.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o a ter um novo modo.
codigoModo (entrada, passagem por valor): numero do modo a ser criado. Pode ser usado qualquer n�mero de 0..MAX_MODOS-1.
loop (entrada, passagem por valor): valor l�gico que indica se este modo deve recome�ar do primeiro frame ap�s a execu��o do �ltimo.
********************************/
void CriaModoAnimacao(int idAnimacao,int codigoModo,int loop){
    CGerenciadorAnimacoes::CriaModo(idAnimacao,codigoModo,loop);
}

/********************************
A fun��o InsereFrameAnimacao() � respons�vel por associar os frames aos modos correspondentes. Um mesmo
frame pode fazer parte de diversos modos, mas cada modo deve ter no m�ximo MAX_FRAMES_MODO-1 frames.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o em quest�o.
codigoModo (entrada, passagem por valor): numero do modo a ter um frame inserido.
codigoFrame (entrada, passagem por valor): numero do frame a ser inserido no modo.
tempo (entrada, passagem por valor): dura��o (em segundos) da exibi��o autom�tica do frame neste modo espec�fico.
********************************/
void InsereFrameAnimacao(int idAnimacao,int codigoModo, int codigoFrame, float tempo){
    CGerenciadorAnimacoes::InsereFrame(idAnimacao,codigoModo,codigoFrame,tempo);
}

/********************************
A fun��o MudaModoAnimacao() � respons�vel por alterar a anima��o para um outro modo.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o em quest�o.
codigoModo (entrada, passagem por valor): numero do novo modo.
inicia (entrada, passagem por valor): valor l�gico que indica se a novo modo deve come�ar do primeiro sprite (valor 1) ou do �ltimo sprite (valor 0).
********************************/
void MudaModoAnimacao(int idAnimacao,int codigoModo,int inicia){
    CGerenciadorAnimacoes::MudaModo(idAnimacao,codigoModo,inicia);
}

/********************************
A fun��o ColisaoAnimacoes() indica se houve colis�o entre duas anima��es, de forma semelhante aos objetos.
Par�metros:
idAnimacao1 (entrada, passagem por valor): identificador da primeira anima��o.
idAnimacao2 (entrada, passagem por valor): identificador da segunda anima��o.
Retorno:
inteiro que indica se houve colis�o entre as anima��es.
********************************/
int ColisaoAnimacoes(int idAnimacao1,int idAnimacao2){
    return CGerenciadorAnimacoes::ColisaoAnimacoes(idAnimacao1,idAnimacao2);
}

/********************************
A fun��o ColisaoAnimacaoObjeto() indica se houve colis�o de alguma animacao com algum outro objeto espec�fico, atrav�s do seu identificador.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o que pode ter colidido com o objeto.
idObjeto (entrada, passagem por valor): identificador do objeto que pode ter colidido com a anima��o.
Retorno:
inteiro que indica se houve colis�o da anima��o com o objeto.
********************************/
int ColisaoAnimacaoObjeto(int idAnimacao,int idObjeto){
    Objeto obj = CGerenciadorObjetos::GetObjeto(idObjeto);
    return CGerenciadorAnimacoes::ColisaoObjeto(idAnimacao,obj);
}

/********************************
A fun��o DesenhaAnima��o() � respons�vel por desenhar uma anima��o na tela. A anima��o ser� desenhada de acordo com o modo atual da anima��o,
fazendo com que os frames sejam automaticamente ajustados de acordo com o tempo estipulado. Caso o modo atual esteja em loop, o primeiro frame ser�
desenhado novamente logo ap�s o t�rmino do �ltimo frame.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o a ser desenhada.
Retorno:
inteiro que indica se a anima��o encerrou ou n�o. O valor s� ser� diferente de zero, se o modo atual tamb�m n�o estiver em loop.
********************************/
int DesenhaAnimacao(int idAnimacao){
    return CGerenciadorAnimacoes::Desenha(idAnimacao);
}

/********************************
A fun��o MoveAnimacao() � respons�vel por movimentar uma determinada anima��o para uma nova posi��o informada.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o a ser movida.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usu�rio deseja reposicionar a anima��o.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usu�rio deseja reposicionar a anima��o.
********************************/
void MoveAnimacao(int idAnimacao,int x,int y){
    CGerenciadorAnimacoes::Move(idAnimacao,x,y);
}

/********************************
A fun��o SetOpacidadeAnimacao() � respons�vel por modificar o n�vel de opacidade da anima��o.
O n�vel de opacidade varia de 0-255, sendo 0 totalmente transparente e 255 totalmente opaco.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o.
valor (entrada,passagem por valor): n�vel de opacidade da anima��o na faixa 0-255.
********************************/
void SetOpacidadeAnimacao(int idAnimacao,int valor){
    CGerenciadorAnimacoes::SetOpacidade(idAnimacao,valor);
}

/********************************
A fun��o SetColoracaoAnimacao() � respons�vel por mesclar uma determinada cor com os pixels do arquivo de imagem.
Ap�s a modifica��o, todos os desenhos desta anima��o ser�o mostrados j� com a mesclagem definida.
Para voltar ao padr�o original de pixels, deve-se chamar a fun��o, passando a cor branca (255,255,255).
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o a ser desenhado.
cor (entrada,passagem por valor): cor do sistema RGB utilizada para mesclagem com o arquivo de imagem
********************************/
void SetColoracaoAnimacao(int idAnimacao,PIG_Cor cor){
    CGerenciadorAnimacoes::SetColoracao(idAnimacao,cor);
}

/********************************
A fun��o SetAnguloAnimacao() � respons�vel pela angula��o de determinada animacao. A angula��o � calculada em sentido
hor�rio a partir do eixo X (0 graus). A anima��o ser� desenhada com a angula��o informada no pr�ximo comando
DesenhaAnimcao(). A detec��o de colis�o n�o funciona com anima��es fora da angula��o padr�o (0 graus).
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o.
angulo (entrada, passagem por valor): valor para indicar a angula��o da anima��o em graus.
********************************/
void SetAnguloAnimacao(int idAnimacao, float angulo){
    CGerenciadorAnimacoes::SetAngulo(idAnimacao,angulo);
}

/********************************
A fun��o GetAnguloAnimacao() � respons�vel por recuperar o �ngulo de rota��o de determinada anima��o. A angula��o � calculada em sentido
hor�rio a partir do eixo X (0 graus). A anima��o ser� desenhada com a angula��o informada no pr�ximo comando
DesenhaAnimacao(). A detec��o de colis�o n�o funciona com anima��es fora da angula��o padr�o (0 graus).
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o.
Retorno:
Retorna o valor do �ngulo em graus.
********************************/
float GetAnguloAnimacao(int idAnimacao){
    return CGerenciadorAnimacoes::GetAngulo(idAnimacao);
}

/********************************
A fun��o SetPivoAnimacao() define um ponto (X,Y) em rela��o ao ponto (0,0) da anima��o, sobre o qual a anima��o ser�
rotacionado quando a fun��o SetAnguloAnimacao() for executada.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o.
posicaoX (entrada, passagem por valor): Valor da coordenada X do piv� em rela��o ao ponto (0,0) da anima��o.
posicaoY (entrada, passagem por valor): Valor da coordenada Y do piv� em rela��o ao ponto (0,0) da anima��o.
********************************/
void SetPivoAnimacao(int idAnimacao,int posicaoX,int posicaoY){
    CGerenciadorAnimacoes::SetPivo(idAnimacao,posicaoX,posicaoY);
}

/********************************
A fun��o GetPivoAnimacao() define um ponto (X,Y) em rela��o ao ponto (0,0) da animacao, sobre o qual a anima��o ser�
rotacionado quando a fun��o SetAnguloAnimacao() for executada.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o.
posicaoX (sa�da, passagem por refer�ncia): Valor da coordenada X do piv� em rela��o ao ponto (0,0) da anima��o.
posicaoY (sa�da, passagem por refer�ncia): Valor da coordenada Y do piv� em rela��o ao ponto (0,0) da anima��o.
********************************/
void GetPivoAnimacao(int idAnimacao,int *posicaoX,int *posicaoY){
    CGerenciadorAnimacoes::GetPivo(idAnimacao,posicaoX,posicaoY);
}

/********************************
A fun��o SetDimensoesAnimacao() � respons�vel por delimitar a altura e a largura da anima��o que ser� desenhada na tela,
independentemente do tamanho original do arquivo de imagem.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o.
altura (entrada, passagem por valor): altura em pixels.
largura (entrada, passagem por valor): largura em pixels.
********************************/
void SetDimensoesAnimacao(int idAnimacao, int altura, int largura){
    CGerenciadorAnimacoes::SetDimensoes(idAnimacao,altura,largura);
}

/********************************
A fun��o GetDimensoesAnimacao() � respons�vel por recuperar a altura e a largura da �rea a ser usada
para desenhar a anima��o na tela. Em outras palavras, representa o tamanho atual da anima��o.
Par�metros:
idObjeto (entrada, passagem por valor): identificador da anima��o.
altura (sa�da, passagem por refer�ncia): altura atual em pixels da anima��o.
largura (sa�da, passagem por refer�ncia): largura atual em pixels da anima��o.
********************************/
void GetDimensoesAnimacao(int idAnimacao, int *altura, int *largura){
    CGerenciadorAnimacoes::GetDimensoes(idAnimacao,altura,largura);
}

/********************************
A fun��o SetValorIntAnimacao() � respons�vel incorporar a uma anima��o um atributo inteiro.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o.
indice (entrada, passagem por valor): relaciona um n�mero inteiro ao atributo.
valor (entrada, passagem por valor): valor do atributo inteiro a ser associado � anima��o.
********************************/
void SetValorIntAnimacao(int idAnimacao,int indice,int valor){
    CGerenciadorAnimacoes::SetValorIntAnimacao(idAnimacao,indice,valor);
}

/********************************
A fun��o SetValorFloatAnimacao() � respons�vel incorporar a uma anima��o um atributo float.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o.
indice (entrada, passagem por valor): relaciona um n�mero inteiro ao atributo.
valor (entrada, passagem por valor): valor do atributo float a ser associado � anima��o.
********************************/
void SetValorFloatAnimacao(int idAnimacao,int indice,float valor){
    CGerenciadorAnimacoes::SetValorFloatAnimacao(idAnimacao,indice,valor);
}

/********************************
A fun��o SetValorIntAnimacao() � respons�vel incorporar a uma anima��o um atributo inteiro.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o.
indice (entrada, passagem por valor): relaciona um n�mero inteiro ao atributo.
valor (entrada, passagem por refer�ncia): valor do atributo string a ser associado � anima��o.
********************************/
void SetValorStringAnimacao(int idAnimacao,int indice,char *valor){
    CGerenciadorAnimacoes::SetValorStringAnimacao(idAnimacao,indice,valor);
}

/********************************
A fun��o SetValorIntAnimacao() � respons�vel incorporar a uma anima��o um atributo inteiro.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o.
indice (entrada, passagem por refer�ncia): relaciona uma string ao atributo.
valor (entrada, passagem por valor): valor do atributo inteiro a ser associado � anima��o.
********************************/
void SetValorIntAnimacao(int idAnimacao,char *indice,int valor){
    CGerenciadorAnimacoes::SetValorIntAnimacao(idAnimacao,indice,valor);
}

/********************************
A fun��o SetValorFloatAnimacao() � respons�vel incorporar a uma anima��o um atributo float.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o.
indice (entrada, passagem por refer�ncia): relaciona uma string ao atributo.
valor (entrada, passagem por valor): valor do atributo float a ser associado � anima��o.
********************************/
void SetValorFloatAnimacao(int idAnimacao,char *indice,float valor){
    CGerenciadorAnimacoes::SetValorFloatAnimacao(idAnimacao,indice,valor);
}

/********************************
A fun��o SetValorIntAnimacao() � respons�vel incorporar a uma anima��o um atributo inteiro.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o.
indice (entrada, passagem por refer�ncia): relaciona uma string ao atributo.
valor (entrada, passagem por refer�ncia): valor do atributo string a ser associado � anima��o.
********************************/
void SetValorStringAnimacao(int idAnimacao,char *indice,char *valor){
    CGerenciadorAnimacoes::SetValorStringAnimacao(idAnimacao,indice,valor);
}

/********************************
A fun��o GetValorIntAnimacao() � respons�vel recuperar o valor de um atributo inteiro relacionado a uma anima��o.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o.
indice (entrada, passagem por valor): indica o n�mero do atributo que se deseja recuperar.
valor (sa�da, passagem por refer�ncia): indica o valor do atributo, se a fun��o retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo n�o existir, a fun��o retorna o valor 0 (zero).
********************************/
int GetValorIntAnimacao(int idAnimacao,int indice,int *valor){
    return CGerenciadorAnimacoes::GetValorIntAnimacao(idAnimacao,indice,valor);
}

/********************************
A fun��o GetValorFloatAnimacao() � respons�vel recuperar o valor de um atributo float relacionado a uma anima��o.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o.
indice (entrada, passagem por valor): indica o n�mero do atributo que se deseja recuperar.
valor (sa�da, passagem por refer�ncia): indica o valor do atributo, se a fun��o retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo n�o existir, a fun��o retorna o valor 0 (zero).
********************************/
int GetValorFloatAnimacao(int idAnimacao,int indice,float *valor){
    return CGerenciadorAnimacoes::GetValorFloatAnimacao(idAnimacao,indice,valor);
}

/********************************
A fun��o GetValorStringAnimacao() � respons�vel recuperar o valor de um atributo string relacionado a uma anima��o.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o.
indice (entrada, passagem por valor): indica o n�mero do atributo que se deseja recuperar.
valor (sa�da, passagem por refer�ncia): indica o valor do atributo, se a fun��o retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo n�o existir, a fun��o retorna o valor 0 (zero).
********************************/
int GetValorStringAnimacao(int idAnimacao,int indice,char *valor){
    return CGerenciadorAnimacoes::GetValorStringAnimacao(idAnimacao,indice,valor);
}

/********************************
A fun��o GetValorIntAnimacao() � respons�vel recuperar o valor de um atributo inteiro relacionado a uma anima��o.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o.
indice (entrada, passagem por refer�ncia): indica o nome do atributo que se deseja recuperar.
valor (sa�da, passagem por refer�ncia): indica o valor do atributo, se a fun��o retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo n�o existir, a fun��o retorna o valor 0 (zero).
********************************/
int GetValorIntAnimacao(int idAnimacao,char *indice,int *valor){
    return CGerenciadorAnimacoes::GetValorIntAnimacao(idAnimacao,indice,valor);
}

/********************************
A fun��o GetValorFloatAnimacao() � respons�vel recuperar o valor de um atributo float relacionado a uma anima��o.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o.
indice (entrada, passagem por valor): indica o nome do atributo que se deseja recuperar.
valor (sa�da, passagem por refer�ncia): indica o valor do atributo, se a fun��o retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo n�o existir, a fun��o retorna o valor 0 (zero).
********************************/
int GetValorFloatAnimacao(int idAnimacao,char *indice,float *valor){
    return CGerenciadorAnimacoes::GetValorFloatAnimacao(idAnimacao,indice,valor);
}

/********************************
A fun��o GetValorStringAnimacao() � respons�vel recuperar o valor de um atributo string relacionado a uma anima��o.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o.
indice (entrada, passagem por valor): indica o nome do atributo que se deseja recuperar.
valor (sa�da, passagem por refer�ncia): indica o valor do atributo, se a fun��o retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo n�o existir, a fun��o retorna o valor 0 (zero).
********************************/
int GetValorStringAnimacao(int idAnimacao,char *indice,char *valor){
    return CGerenciadorAnimacoes::GetValorStringAnimacao(idAnimacao,indice,valor);
}

/********************************
A fun��o GetXYAnimacao() � respons�vel por recuperar o valor da posi��o (X,Y) da animacao de acordo com o sistema de coordenadas do jogo.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o.
posicaoX (sa�da, passagem por referencia): indica a posicao no eixo X da anima��o.
posicaoY (sa�da, passagem por referencia): indica a posicao no eixo Y da anima��o.
********************************/
void GetXYAnimacao(int idAnimacao,int *posicaoX,int *posicaoY){
    return CGerenciadorAnimacoes::GetPosicaoXY(idAnimacao,posicaoX,posicaoY);
}


/********************************
Se��o dos �udios
********************************/

/********************************
A fun��o CriaAudio() � respons�vel por ler e preparar um arquivo de audio.
Os formatos permitidos s�o WAVE, AIFF, RIFF, OGG, VOC.
Par�metros:
nomeArquivo (entrada, passagem por refer�ncia): string que informa o nome do arquivo de �udio.
nLoops (entrada, passagem por valor): indica o n�mero de repeti��es do �udio. O valor 0 indica que ser� tocado apenas uma vez. O valor -1 indica que o audio deve ser tocado indefinidamente.
tempoExecucao (entrada, passage por valor): indica uma quantidade de milissegundos do arquivo de audio que dem ser tocados. O valor de -1 indica que todo o arquivo deve ser tocado.
Retorno:
Retorna o identificador do audio para ser utilizado por outras fun��es.
********************************/
int CriaAudio(char *nomeArquivo,int nLoops,int tempoExecucao=-1){
    return CGerenciadorAudios::CriaAudio(nomeArquivo,nLoops,tempoExecucao);
}

/********************************
A fun��o DestroiAudio() � respons�vel por eliminar um �udio do jogo.
Par�metros:
idAudio (entrada, passagem por valor): identificador do �udio a ser exclu�do.
********************************/
void DestroiAudio(int idAudio){
    CGerenciadorAudios::DestroiAudio(idAudio);
}

/********************************
A fun��o CarregaBackground() � respons�vel por ler e preparar um arquivo de audio para ser tocado em background.
Apenas um �nico arquivo de �udio para background � permitido. Os formatos permitidos s�o WAVE, MOD, MIDI, OGG, MP3, FLAC.
Par�metros:
nomeArquivo (entrada, passagem por refer�ncia): string que informa o nome do arquivo de �udio.
********************************/
void CarregaBackground(char *nomeArquivo){
    CGerenciadorAudios::CarregaBackground(nomeArquivo);
}

/********************************
A fun��o PlayBackground() � respons�vel por tocar um �udio de background previamente carregado.
Par�metros:
nVezes (entrada, passagem por valor): indica o n�mero de vezes que o background deve ser executado.
O valor -1 indica que deve sertocado indefinidamente.
********************************/
void PlayBackground(int nVezes=-1){
    CGerenciadorAudios::PlayBackground(nVezes);
}

/********************************
A fun��o StopBackground() � respons�vel por parar um �udio de background previamente carregado.
********************************/
void StopBackground(){
    CGerenciadorAudios::StopBackground();
}

/********************************
A fun��o PauseBackground() � respons�vel por pausar um �udio de background previamente carregado.
********************************/
void PauseBackground(){
    CGerenciadorAudios::PauseBackground();
}

/********************************
A fun��o ResumeBackground() � respons�vel por continuar a tocar um �udio de background previamente carregado.
********************************/
void ResumeBackground(){
    CGerenciadorAudios::ResumeBackground();
}

/********************************
A fun��o GetStatusBackground() recupera o status do audio de background.
Retorno:
Retorna: o valor do status do �udio de background(AUDIO_TOCANDO, AUDIO_PARADO ou AUDIO_PAUSADO)
********************************/
PIG_StatusAudio GetStatusBackground(){
    return CGerenciadorAudios::GetStatusBackground();
}

/********************************
A fun��o SetVolumeBackground() define o valor do volume do �udio de background.
Par�metro:
valor (entrada, passagem por valor): valor do novo volume a ser utilizado. Os valores devem ser entre 0 (mudo) e 128 (volume m�ximo).
********************************/
void SetVolumeBackground(int valor){
    CGerenciadorAudios::SetVolumeBackground(valor);
}

/********************************
A fun��o GetVolumeBackground() recupera o valor do volume do �udio de background.
Retorno:
Retorna o valor do volume do audio de background. Os valores devem ser entre 0 (mudo) e 128 (volume m�ximo).
********************************/
int GetVolumeBackground(){
    return CGerenciadorAudios::GetVolumeBackground();
}

/********************************
A fun��o SetVolumeBackground() define o valor do volume do �udio em quest�o.
Par�metro:
idAudio (entrada, passagem por valor): identificador do �udio.
volume (entrada, passagem por valor): valor do novo volume a ser utilizado. Os valores devem ser entre 0 (mudo) e 128 (volume m�ximo).
********************************/
void SetVolume(int idAudio,int volume){
    CGerenciadorAudios::SetVolume(idAudio,volume);
}

/********************************
A fun��o SetVolumeBackground() recupera o valor do volume do �udio em quest�o.
Par�metro:
idAudio (entrada, passagem por valor): identificador do �udio.
Retorno:
Retorna o valor do volume do audio. Os valores devem ser entre 0 (mudo) e 128 (volume m�ximo).
********************************/
int GetVolume(int idAudio){
    return CGerenciadorAudios::GetVolume(idAudio);
}

/********************************
A fun��o SetVolumeBackground() define o valor do volume de todos os �udios.
Par�metro:
volume (entrada, passagem por valor): valor do novo volume a ser utilizado. Os valores devem ser entre 0 (mudo) e 128 (volume m�ximo).
********************************/
void SetVolumeTudo(int volume){
    CGerenciadorAudios::SetVolumeTudo(volume);
}

/********************************
A fun��o PlayAudio() � respons�vel por tocar um �udio previamente criado.
Par�metro:
idAudio (entrada, passagem por valor): indentificador do �udio.
********************************/
void PlayAudio(int idAudio){
    CGerenciadorAudios::Play(idAudio);
}

/********************************
A fun��o PauseAudio() � respons�vel por pausar um �udio que esteja tocandoo.
Par�metro:
idAudio (entrada, passagem por valor): indentificador do �udio.
********************************/
void PauseAudio(int idAudio){
    CGerenciadorAudios::Pause(idAudio);
}

/********************************
A fun��o ResumeAudio() � respons�vel por continuar a tocar um �udios pausado.
Par�metro:
idAudio (entrada, passagem por valor): indentificador do �udio.
********************************/
void ResumeAudio(int idAudio){
    CGerenciadorAudios::Resume(idAudio);
}

/********************************
A fun��o StopAudio() � respons�vel por parar um �udios pausado ou tocando.
Par�metro:
idAudio (entrada, passagem por valor): indentificador do �udio.
********************************/
void StopAudio(int idAudio){
    CGerenciadorAudios::Stop(idAudio);
}

/********************************
A fun��o GetStatusAudio() recupera o status do audio em quest�o.
Par�metro:
idAudio (entrada, passagem por valor): indentificador do �udio.
Retorno:
Retorna: o valor do status do �udio (AUDIO_TOCANDO, AUDIO_PARADO ou AUDIO_PAUSADO)
********************************/
PIG_StatusAudio GetStatusAudio(int idAudio){
    return CGerenciadorAudios::GetStatus(idAudio);
}

/********************************
A fun��o ResumeTudoAudio() � respons�vel por parar todos os �udios pausados ou tocando.
********************************/
void StopTudoAudio(){
    CGerenciadorAudios::StopTudo();
}

/********************************
A fun��o PauseTudoAudio() � respons�vel por pausar todos os �udios que estiverem tocando.
********************************/
void PauseTudoAudio(){
    CGerenciadorAudios::PauseTudo();
}

/********************************
A fun��o ResumeTudoAudio() � respons�vel por continuar a tocar todos os �udios pausados.
********************************/
void ResumeTudoAudio(){
    CGerenciadorAudios::ResumeTudo();
}
