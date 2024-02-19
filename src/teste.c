#include <stdio.h>

int main(void)
{
    // Número binário inicial
    int numero = 0b101000;

    // Máscara para isolar o quarto bit (contando da direita para a esquerda)
    int mascara = 0b0100;


    // Aplicando a operação OR bitwise para definir o quarto bit como 1
    int resultado = numero | mascara;

    // Convertendo o resultado de volta para binário para verificar
    printf("Resultado: %d\n", resultado);
    printf("Numero: %d\n", numero);

    return 0;
}
