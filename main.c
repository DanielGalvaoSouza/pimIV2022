#include <stdio.h>
#include <locale.h>
int main() {
    setlocale (LC_ALL, "portuguese-brazilian");

    char mensagemInicial[100] = "BEM VINDO AO RCWC19 (Register Customer With COVID19) PROGRAMA CRIADO PARA PIMIV 2022.";
    char questionamentoLogin[100] = "DIGITE O SEU LOGIN DE ACESSO";
    char pacientName[10];
    printf("%s\n", mensagemInicial);
    printf("%s\n", questionamentoLogin);
    scanf("%s", pacientName);



    /*if(strcmp(pacientName) <= 5)
    {
        printf("Voc� deve informar um nome v�lido para este paciente");
    }else{
        printf("O nome do paciente FOI RECONHECIDO COM V�LIDO. SEU VALOR � %s. %d\n", pacientName, sizeof(pacientName));
    }*/

    return 0;
}
