#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>

/*
https://www.w3schools.blog/c-printf-and-scanf
funcionamento do printf
*/

bool usuarioValido = false;

void Apresentacao_Aplicativo()
{
    char mensagemInicial[100] = "BEM VINDO AO RCWC19 (Register Customer With COVID19) PROGRAMA CRIADO PARA PIMIV 2022.";

    //Apresentação do aplicativo.
    printf("*******************************************************************************************\n");
    printf("   %s   \n", mensagemInicial);
    printf("*******************************************************************************************\n");
}

void AutenticacaoDeOperador()
{
    char questionamentoLogin[100] = "DIGITE O SEU LOGIN DE ACESSO";
    char questionamentoSenha[100] = "DIGITE A SENHA PARA ACESSO";
    const int QUANTIDADE_CARACTERES = 30;
    char entradaLogin[QUANTIDADE_CARACTERES];
    char entradaSenha[QUANTIDADE_CARACTERES];
    char loginSistema[QUANTIDADE_CARACTERES];
    char senhaSistema[QUANTIDADE_CARACTERES];

    strcpy(loginSistema, "OPERADOR");
    strcpy(senhaSistema, "OPERADOR2022");

    Apresentacao_Aplicativo();

    do{
        //Resgata Login
        printf("%s\n", questionamentoLogin);
        scanf("%s", entradaLogin);

        //Resgata Senha
        printf("%s\n", questionamentoSenha);
        scanf("%s", entradaSenha);

        printf("%s, VALIDANDO SEU ACESSO AO APLICATIVO RCWC19.\n", entradaLogin);

        if( (strcmp(entradaLogin, loginSistema) == 0) && (strcmp(entradaSenha, senhaSistema) == 0))
        {
            usuarioValido = true;
        }
        else
        {
            system("cls");
            Apresentacao_Aplicativo();
            printf("SUAS CREDENCIAIS NÃO FORAM ACEITAS NO PROCESSO DE AUTENTICAÇÃO. TENTE NOVAMENTE!\n");

        }

    }while(!usuarioValido);
    system("cls");
    printf("CREDENCIAL RECONHECIDA. SEU ACESSO ESTÁ LIBERADO.\n");

}

int main() {
    setlocale (LC_ALL, "portuguese-brazilian");

    AutenticacaoDeOperador();

    return 0;
}
