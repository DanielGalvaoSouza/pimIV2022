#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>
#include <stdlib.h>

bool usuarioValido = false;
const int QUANTIDADE_CARACTERES = 30;
char DadosLogin[30] = "";
char DadosSenha[30] = "";

char ValorChaveExtraido[160];
void ResgataValorChave(char *chave)
{
    int i = 0;
    int j = 0;
    bool isAKeyValue = false;
    char charStart = ':';
    char charEnd = ';';

    for(i=0; i < strlen(chave); i++)
    {
        char valueKey = chave[i];
        if(valueKey == charStart)
        {
            isAKeyValue = true;
        }
        if(valueKey == charEnd)
        {
            isAKeyValue = false;
        }
        if(isAKeyValue && (valueKey != charStart && valueKey != charEnd))
        {
            ValorChaveExtraido[j] = chave[i];
            j++;
        }
    }
}

void LeituraDeArquivo()
{
    FILE* ptr;
    char ch;

    // Opening file in reading mode
    ptr = fopen("RCWC-BASE-DADOS.txt", "r");

    if (NULL == ptr) {
        printf("file can't be opened \n");
    }

    printf("content of this file are \n");

    // Printing what is written in file
    // character by character using loop.
    do {
        ch = fgetc(ptr);
        printf("%c", ch);

        // Checking if character is not EOF.
        // If it is EOF stop eading.
    } while (ch != EOF);

    // Closing the file
    fclose(ptr);
    return 0;
}

void ResgataCredenciais()
{
    FILE* funcaoComArquivo;
    char conteudoDoArquivo;

    // Opening file in reading mode
    funcaoComArquivo = fopen("RCWC-BASE-DADOS-SEGURANCA.txt", "r");

    if (NULL == funcaoComArquivo) {
        printf("NÃO FOI POSSÍVEL ENCONTRAR OS DADOS RELACIONADOS AS CREDENCIAIS DE ACESSO AO APLICATIVO. TENTE CONFIGURAR O APLICATIVO ANTES DE UTILIZA-LO.\n");
    }

    char conteudoLinha[500];

    while (fgets(conteudoLinha, sizeof(conteudoLinha), funcaoComArquivo)){
        //printf("o conteúdo da linha do arquivo é: %s", conteudoLinha);

        char *findLogin = strstr(conteudoLinha, "LOGIN:");

        //printf("findLogin: %s ", findLogin);
        if(findLogin != NULL)
        {
            ResgataValorChave(conteudoLinha);
            strcpy(DadosLogin, ValorChaveExtraido);
        }

        char *findSenha = strstr(conteudoLinha, "SENHA:");

        if(findSenha != NULL)
        {
            ResgataValorChave(conteudoLinha);
            strcpy(DadosSenha, ValorChaveExtraido);
        }
    }

    // Closing the file
    fclose(funcaoComArquivo);

}

void Apresentacao_Aplicativo()
{
    char mensagemInicial[100] = "BEM VINDO AO RCWC19 (Register Customers With COVID19) PROGRAMA CRIADO PARA PIMIV 2022.";

    //Apresentação do aplicativo.
    printf("*******************************************************************************************\n");
    printf("   %s   \n", mensagemInicial);
    printf("*******************************************************************************************\n");
}

void AutenticacaoDeOperador()
{
    char questionamentoLogin[100] = "DIGITE O SEU LOGIN DE ACESSO";
    char questionamentoSenha[100] = "DIGITE A SENHA PARA ACESSO";

    char entradaLogin[QUANTIDADE_CARACTERES];
    char entradaSenha[QUANTIDADE_CARACTERES];
    char loginSistema[QUANTIDADE_CARACTERES];
    char senhaSistema[QUANTIDADE_CARACTERES];

    ResgataCredenciais();

    strcpy(loginSistema, DadosLogin);
    strcpy(senhaSistema, DadosSenha);

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
