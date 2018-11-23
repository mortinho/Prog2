
#ifndef INPUT_H
#define INPUT_H
#endif // INPUT_H

#define LEFT TECLA_a
#define RIGHT TECLA_d
#define JUMP TECLA_BARRAESPACO

typedef struct input {
    int direita, esquerda, pulando;
} input;

input newTeclado(){
    input i;
    i.direita = 0;
    i.esquerda = 0;
    i.pulando = 0;
    return i;
}


