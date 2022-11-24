#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    char Codigo[40];
    char Nome[120];
    char CPF[20];
    char Telefone[20];
    char Endereco[150];
    char DataNascimento[15];
    char Email[120];
    char DataDoDiagnostico[15];
    char ComorbidadeDoPaciente[20];
} DadosPacientes;

bool usuarioValido = false;
const int QUANTIDADE_CARACTERES = 30;
char DadosLogin[30] = "";
char DadosSenha[30] = "";
DadosPacientes dadosPacientes[30];
const char COMORBIDADE_DIABETES[20] = "DIABETES";
const char COMORBIDADE_OBESIDADE[20] = "OBESIDADE";
const char COMORBIDADE_HIPERTENSAO[20] = "HIPERTENSAO";
const char COMORBIDADE_TUBERCULOSE[20] = "TUBERCULOSE";
const char COMORBIDADE_OUTROS[20] = "OUTROS";
char GUID_PRIMARY_KEY[40];
const char ARQUIVO_PACIENTES[30] = "RCWC-BASE-DADOS-PACIENTES.txt";
const char ARQUIVO_COMORBIDADE[50] = "RCWC-BASE-DADOS-PACIENTES-COM-COMORBIDADES.txt";
char ValorChaveExtraido[160];
int indiceVetor = 0;
int dayAge;
int monthAge;
int yearAge;
int dayCurrent;
int monthCurrent;
int yearCurrent;

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

void ResgataPacientes()
{
    FILE* funcaoComArquivo;
    char conteudoDoArquivo;
    funcaoComArquivo = fopen("RCWC-BASE-DADOS-PACIENTES.txt", "r");

    if (NULL == funcaoComArquivo) {
        printf("N�O FOI POSS�VEL ENCONTRAR OS DADOS RELACIONADOS AS CREDENCIAIS DE ACESSO AO APLICATIVO. TENTE CONFIGURAR O APLICATIVO ANTES DE UTILIZA-LO.\n");
    }

    char conteudoLinha[500];

    while (fgets(conteudoLinha, sizeof(conteudoLinha), funcaoComArquivo)){

    }

    // Closing the file
    fclose(funcaoComArquivo);

}

void EscreverPacientes()
{
    FILE* funcaoComArquivo;
    char conteudoDoArquivo;
    funcaoComArquivo = fopen(ARQUIVO_PACIENTES, "w");

    if (NULL == funcaoComArquivo) {
        printf("N�O FOI POSS�VEL ENCONTRAR OS DADOS RELACIONADOS AOS PACIENTES.\n");
    }

    char conteudoLinha[500];
    int i = 0;
    int totalPacientesNaLista = sizeof(dadosPacientes) / sizeof(dadosPacientes[0]);

    for(i=0; i<=totalPacientesNaLista; i++)
    {
        fprintf(funcaoComArquivo, "CODIGO=%s|\n", dadosPacientes[i].Codigo);
        fprintf(funcaoComArquivo, "NOME=%s|\n", dadosPacientes[i].Nome);
        fprintf(funcaoComArquivo, "CPF=%s|\n", dadosPacientes[i].CPF);
        fprintf(funcaoComArquivo, "TELEFONE=%s|\n", dadosPacientes[i].Telefone);
        fprintf(funcaoComArquivo, "ENDERECO=%s|\n", dadosPacientes[i].Endereco);
        fprintf(funcaoComArquivo, "DATANASCIMENTO=%s|\n", dadosPacientes[i].DataNascimento);
        fprintf(funcaoComArquivo, "EMAIL=%s|\n", dadosPacientes[i].Email);
        fprintf(funcaoComArquivo, "DATADODIAGNOSTICO=%s|\n", dadosPacientes[i].DataDoDiagnostico);
        fprintf(funcaoComArquivo, "COMORBIDADEDOPACIENTE=%s|\n", dadosPacientes[i].ComorbidadeDoPaciente);
    }

    fclose(funcaoComArquivo);

}

void ResgataCredenciais()
{
    FILE* funcaoComArquivo;
    char conteudoDoArquivo;

    // Opening file in reading mode
    funcaoComArquivo = fopen("RCWC-BASE-DADOS-SEGURANCA.txt", "r");

    if (NULL == funcaoComArquivo) {
        printf("N�O FOI POSS�VEL ENCONTRAR OS DADOS RELACIONADOS AS CREDENCIAIS DE ACESSO AO APLICATIVO. TENTE CONFIGURAR O APLICATIVO ANTES DE UTILIZA-LO.\n");
    }

    char conteudoLinha[500];

    while (fgets(conteudoLinha, sizeof(conteudoLinha), funcaoComArquivo)){
        //printf("o conte�do da linha do arquivo �: %s", conteudoLinha);

        char *findLogin = strstr(conteudoLinha, "LOGIN:");

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
    char mensagemInicial[100] = "BEM VINDO AO RCWC19 (Register Customers With COVID19) PROGRAMA CRIADO PARA PIM IV 2022.";

    //Apresenta��o do aplicativo.
    printf("********************************************************************************************\n");
    printf("   %s   \n", mensagemInicial);
    printf("********************************************************************************************\n");
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
            printf("SUAS CREDENCIAIS N�O FORAM ACEITAS NO PROCESSO DE AUTENTICA��O. TENTE NOVAMENTE!\n\n");

        }

    }while(!usuarioValido);

    system("cls");
    //printf("CREDENCIAL RECONHECIDA. SEU ACESSO EST� LIBERADO.\n");

}

bool FoiArquivoGerado(char *nomearquivo)
{
    FILE* funcaoComArquivo;
    bool ExisteArquivo = true;

    funcaoComArquivo = fopen(nomearquivo, "r");

    if (NULL == funcaoComArquivo) {
        ExisteArquivo = false;
    }

    fclose(funcaoComArquivo);

    return ExisteArquivo;
}

void EscreverPacientesComComorbidade()
{
    FILE* funcaoComArquivo;

    char conteudoDoArquivo;
    funcaoComArquivo = fopen(ARQUIVO_COMORBIDADE, "w");

    if (NULL == funcaoComArquivo) {
        printf("N�O FOI POSS�VEL ENCONTRAR OS DADOS RELACIONADOS AOS PACIENTES.\n");
    }

    char conteudoLinha[500];
    int i = 0;
    int totalPacientesNaLista = sizeof(dadosPacientes) / sizeof(dadosPacientes[0]);

    for(i=0; i<=totalPacientesNaLista; i++)
    {
        if(strlen(dadosPacientes[i].ComorbidadeDoPaciente) > 0)
        {
            fprintf(funcaoComArquivo, "CODIGO=%s|\n", dadosPacientes[i].Codigo);
            fprintf(funcaoComArquivo, "NOME=%s|\n", dadosPacientes[i].Nome);
            fprintf(funcaoComArquivo, "CPF=%s|\n", dadosPacientes[i].CPF);
            fprintf(funcaoComArquivo, "TELEFONE=%s|\n", dadosPacientes[i].Telefone);
            fprintf(funcaoComArquivo, "ENDERECO=%s|\n", dadosPacientes[i].Endereco);
            fprintf(funcaoComArquivo, "DATANASCIMENTO=%s|\n", dadosPacientes[i].DataNascimento);
            fprintf(funcaoComArquivo, "EMAIL=%s|\n", dadosPacientes[i].Email);
            fprintf(funcaoComArquivo, "DATADODIAGNOSTICO=%s|\n", dadosPacientes[i].DataDoDiagnostico);
            fprintf(funcaoComArquivo, "COMORBIDADEDOPACIENTE=%s|\n\n\n", dadosPacientes[i].ComorbidadeDoPaciente);
        }
    }

    fclose(funcaoComArquivo);

}

//https://stackoverflow.com/questions/7399069/how-to-generate-a-guid-in-c
void GenerateGuidToPrimaryKey()
{
    srand (clock());
    int posicao = 0;
    char *uniqueIdentifier = "xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx";
    char *possiveisCaracteres = "0123456789ABCDEF-";
    int nLen = strlen (uniqueIdentifier);

    for (posicao=0; posicao<nLen+1; posicao++)
    {
        int r = rand () % 16;
        char c = ' ';

        if(uniqueIdentifier[posicao] == 'x'){
            c = possiveisCaracteres[r];
        }else if(uniqueIdentifier[posicao] == 'y'){
            c = possiveisCaracteres[r & 0x03 | 0x08];
        }else if(uniqueIdentifier[posicao] == '-'){
            c = '-';
        }else if(uniqueIdentifier[posicao] == '4'){
            c = '4';
        }

        GUID_PRIMARY_KEY[posicao] = ( posicao < nLen ) ? c : 0x00;
    }

    //
}

int CarregarDadosIniciais()
{
    char keyRow[10] = "1";

    GenerateGuidToPrimaryKey();
    strcpy(dadosPacientes[indiceVetor].Codigo, GUID_PRIMARY_KEY);
    strcpy(dadosPacientes[indiceVetor].Nome, "Eduardo Bryan Ramos");
    strcpy(dadosPacientes[indiceVetor].CPF, "862.262.603-27");
    strcpy(dadosPacientes[indiceVetor].Telefone, "(27) 2676-8460");
    strcpy(dadosPacientes[indiceVetor].Endereco, "Rua Cravo, 784 - Jabaet� - Vila Velha - ES");
    strcpy(dadosPacientes[indiceVetor].DataNascimento, "26/09/1963");
    strcpy(dadosPacientes[indiceVetor].Email, "eduardo.bryan.ramos@abareias.com.br");
    strcpy(dadosPacientes[indiceVetor].DataDoDiagnostico, "21/11/2022");
    strcpy(dadosPacientes[indiceVetor].ComorbidadeDoPaciente, COMORBIDADE_OBESIDADE);

    indiceVetor++;
    GenerateGuidToPrimaryKey();

    strcpy(dadosPacientes[indiceVetor].Codigo, GUID_PRIMARY_KEY);
    strcpy(dadosPacientes[indiceVetor].Nome, "Fabiana F�tima Yasmin Caldeira");
    strcpy(dadosPacientes[indiceVetor].CPF, "759.786.381-01");
    strcpy(dadosPacientes[indiceVetor].Telefone, "(81) 3729-4662");
    strcpy(dadosPacientes[indiceVetor].Endereco, "Rua Benedita Pereira das Neves, 593 - Parque Capibaribe - S�o Louren�o da Mata - PE");
    strcpy(dadosPacientes[indiceVetor].DataNascimento, "08/04/1989");
    strcpy(dadosPacientes[indiceVetor].Email, "fabiana-caldeira87@way2goidiomas.com.br");
    strcpy(dadosPacientes[indiceVetor].DataDoDiagnostico, "01/02/2022");
    strcpy(dadosPacientes[indiceVetor].ComorbidadeDoPaciente, COMORBIDADE_DIABETES);

    indiceVetor++;
    GenerateGuidToPrimaryKey();

    strcpy(dadosPacientes[indiceVetor].Codigo, GUID_PRIMARY_KEY);
    strcpy(dadosPacientes[indiceVetor].Nome, "Alana Kamilly Cl�udia Cardoso");
    strcpy(dadosPacientes[indiceVetor].CPF, "226.786.068-64");
    strcpy(dadosPacientes[indiceVetor].Telefone, "(69) 3739-2068");
    strcpy(dadosPacientes[indiceVetor].Endereco, "Rua Margarita, 678 - Industrial - Porto Velho - RO");
    strcpy(dadosPacientes[indiceVetor].DataNascimento, "17/01/2000");
    strcpy(dadosPacientes[indiceVetor].Email, "alana-cardoso90@academiagolf.com.br");
    strcpy(dadosPacientes[indiceVetor].DataDoDiagnostico, "03/03/2022");
    strcpy(dadosPacientes[indiceVetor].ComorbidadeDoPaciente, COMORBIDADE_HIPERTENSAO);

    indiceVetor++;
    GenerateGuidToPrimaryKey();

    strcpy(dadosPacientes[indiceVetor].Codigo, GUID_PRIMARY_KEY);
    strcpy(dadosPacientes[indiceVetor].Nome, "Renato Gustavo Vieira");
    strcpy(dadosPacientes[indiceVetor].CPF, "136.999.100-24");
    strcpy(dadosPacientes[indiceVetor].Telefone, "(44) 3951-6023");
    strcpy(dadosPacientes[indiceVetor].Endereco, "Rua Marginal, 196 - Jardim Morada do Sol - Paranava� - PR");
    strcpy(dadosPacientes[indiceVetor].DataNascimento, "20/07/1992");
    strcpy(dadosPacientes[indiceVetor].Email, "renatogustavovieira@yahoo.se");
    strcpy(dadosPacientes[indiceVetor].DataDoDiagnostico, "06/08/2022");
    strcpy(dadosPacientes[indiceVetor].ComorbidadeDoPaciente, COMORBIDADE_TUBERCULOSE);

    indiceVetor++;
    GenerateGuidToPrimaryKey();

    strcpy(dadosPacientes[indiceVetor].Codigo, GUID_PRIMARY_KEY);
    strcpy(dadosPacientes[indiceVetor].Nome, "Elias Marcos Samuel Jesus");
    strcpy(dadosPacientes[indiceVetor].CPF, "279.784.323-19");
    strcpy(dadosPacientes[indiceVetor].Telefone, "(69) 2548-9949");
    strcpy(dadosPacientes[indiceVetor].Endereco, "Rua Joinville, 516 - Setor 09 - Ariquemes - RO");
    strcpy(dadosPacientes[indiceVetor].DataNascimento, "20/09/1999");
    strcpy(dadosPacientes[indiceVetor].Email, "elias-jesus84@oi15.com.br");
    strcpy(dadosPacientes[indiceVetor].DataDoDiagnostico, "03/06/2020");
    strcpy(dadosPacientes[indiceVetor].ComorbidadeDoPaciente, COMORBIDADE_OUTROS);

    indiceVetor++;
    GenerateGuidToPrimaryKey();

    strcpy(dadosPacientes[indiceVetor].Codigo, GUID_PRIMARY_KEY);
    strcpy(dadosPacientes[indiceVetor].Nome, "Fernanda Giovana Foga�a");
    strcpy(dadosPacientes[indiceVetor].CPF, "127.051.358-39");
    strcpy(dadosPacientes[indiceVetor].Telefone, "(63) 2711-2269");
    strcpy(dadosPacientes[indiceVetor].Endereco, "Quadra 412 Sul Avenida NS 10, 924 - Plano Diretor Sul - Palmas - TO");
    strcpy(dadosPacientes[indiceVetor].DataNascimento, "07/09/1986");
    strcpy(dadosPacientes[indiceVetor].Email, "fernandagiovanafogaca@octagonbrasil.com.br");
    strcpy(dadosPacientes[indiceVetor].DataDoDiagnostico, "12/12/2021");
    strcpy(dadosPacientes[indiceVetor].ComorbidadeDoPaciente, COMORBIDADE_OBESIDADE);

    int i;
    for(i=0; i<=indiceVetor; i++)
    {
        printf("Codigo: %s \n", dadosPacientes[i].Codigo);
        printf("Nome: %s \n", dadosPacientes[i].Nome);
        printf("CPF: %s \n", dadosPacientes[i].CPF);
        printf("Telefone: %s \n", dadosPacientes[i].Telefone);
        printf("Endereco: %s \n", dadosPacientes[i].Endereco);
        printf("DataNascimento: %s \n", dadosPacientes[i].DataNascimento);
        printf("Email: %s \n", dadosPacientes[i].Email);
        printf("DataDoDiagnostico: %s \n", dadosPacientes[i].DataDoDiagnostico);
        printf("ComorbidadeDoPaciente: %s \n \n \n", dadosPacientes[i].ComorbidadeDoPaciente);
    }

}

//https://overiq.com/c-examples/c-program-to-calculate-the-difference-of-two-dates-in-years-months-and-days/
int valid_date(int day, int mon, int year)
{
    int is_valid = 1, is_leap = 0;

    if (year >= 1800 && year <= 9999)
    {

        //  check whether year is a leap year
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        {
            is_leap = 1;
        }

        // check whether mon is between 1 and 12
        if(mon >= 1 && mon <= 12)
        {
            // check for days in feb
            if (mon == 2)
            {
                if (is_leap && day == 29)
                {
                    is_valid = 1;
                }
                else if(day > 28)
                {
                    is_valid = 0;
                }
            }

            // check for days in April, June, September and November
            else if (mon == 4 || mon == 6 || mon == 9 || mon == 11)
            {
                if (day > 30)
                {
                    is_valid = 0;
                }
            }

            // check for days in rest of the months
            // i.e Jan, Mar, May, July, Aug, Oct, Dec
            else if(day > 31)
            {
                is_valid = 0;
            }
        }

        else
        {
            is_valid = 0;
        }

    }
    else
    {
        is_valid = 0;
    }

    return is_valid;

}

int calculaIdade()
{
    int diaSubtracao, mesSubtracao, anoSubtracao;

    if(!valid_date(dayAge, monthAge, yearAge))
    {
        return 0;
    }

    if(!valid_date(dayCurrent, monthCurrent, yearCurrent))
    {
        return 0;
    }

    if(dayCurrent < dayAge)
    {
        // borrow days from february
        if (monthCurrent == 3)
        {
            //  check whether year is a leap year
            if ((yearCurrent % 4 == 0 && yearCurrent % 100 != 0) || (yearCurrent % 400 == 0))
            {
                dayCurrent += 29;
            }

            else
            {
                dayCurrent += 28;
            }
        }

        // borrow days from April or June or September or November
        else if (monthCurrent == 5 || monthCurrent == 7 || monthCurrent == 10 || monthCurrent == 12)
        {
           dayCurrent += 30;
        }

        // borrow days from Jan or Mar or May or July or Aug or Oct or Dec
        else
        {
           dayCurrent += 31;
        }

        monthCurrent = monthCurrent - 1;
    }

    if (monthCurrent < monthAge)
    {
        monthCurrent += 12;
        yearCurrent -= 1;
    }

    diaSubtracao = dayCurrent - dayAge;
    mesSubtracao = monthCurrent - monthAge;
    anoSubtracao = yearCurrent - yearAge;

    return anoSubtracao;

}

void FormularioDeEntrada()
{
    char formularioCodigo[40];
    char formularioNome[120];
    char formularioCPF[20];
    char formularioTelefone[20];
    char formularioEndereco[150];
    char formularioDataNascimento[15];
    char formularioEmail[120];
    char formularioDataDoDiagnostico[15];
    char formularioComorbidadeDoPaciente[20];

    system("cls");
    Apresentacao_Aplicativo();


    //const char PROXIMO_CAMPO[50] = "Pressione a tecla ENTER para pr�ximo campo";

    printf("\nA SEGUIR VOC� DEVE INFORMAR OS DADOS DO PACIENTE QUE DESEJA CADASTRAR\n\n");
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
    printf("NOME: [Utilize no m�ximo %d caracteres]\n", sizeof(formularioNome));
    gets(formularioNome);


    printf("CPF: [Utilize no m�ximo %d caracteres]\n", sizeof(formularioCPF));
    gets(formularioCPF);

    printf("TELEFONE (DDD+NUMERO DE TELEFONE): [Utilize no m�ximo %d caracteres]\n", sizeof(formularioTelefone));
    gets(formularioTelefone);

    printf("ENDERE�O (RUA, N�MERO, BAIRRO, CIDADE, ESTADO E CEP): [Utilize no m�ximo %d caracteres]\n", sizeof(formularioEndereco));
    gets(formularioEndereco);

    printf("DATA DE NASCIMENTO: [Utilize no m�ximo %d caracteres] com a m�scara dd/mm/aaaa\n", sizeof(formularioDataNascimento));
    gets(formularioDataNascimento);

    printf("E-MAIL: [Utilize no m�ximo %d caracteres]\n", sizeof(formularioEmail));
    gets(formularioEmail);

    printf("DATA DO DIAGN�STICO: [Utilize no m�ximo %d caracteres com a m�scara dd/mm/aaaa]\n", sizeof(formularioDataDoDiagnostico));
    gets(formularioDataDoDiagnostico);

    //puts(PROXIMO_CAMPO);
    printf("COMORBIDADE DO PACIENTE (DIGITE D => DIABETES, O => OBESIDADE, H => HIPERTENS�O, T => TUBERCULOSE, R => OUTROS OU DEIXE O CAMPO VAZIO PARA NENHUMA CORMOBIDADE): [Utilize no m�ximo %d caracteres]\n", sizeof(formularioComorbidadeDoPaciente));
    gets(formularioComorbidadeDoPaciente);

    if(strstr(formularioComorbidadeDoPaciente, "D") != NULL && strcmp(formularioComorbidadeDoPaciente, "d") != NULL )
    {
        strcpy(formularioComorbidadeDoPaciente, COMORBIDADE_DIABETES);
    }
    else if(strstr(formularioComorbidadeDoPaciente, "O") != NULL && strcmp(formularioComorbidadeDoPaciente, "o") != NULL )
    {
        strcpy(formularioComorbidadeDoPaciente, COMORBIDADE_OBESIDADE);

    }
    else if(strstr(formularioComorbidadeDoPaciente, "H") != NULL && strcmp(formularioComorbidadeDoPaciente, "h") != NULL )
    {
        strcpy(formularioComorbidadeDoPaciente, COMORBIDADE_HIPERTENSAO);

    }
    else if(strstr(formularioComorbidadeDoPaciente, "T") != NULL && strcmp(formularioComorbidadeDoPaciente, "t") != NULL )
    {
        strcpy(formularioComorbidadeDoPaciente, COMORBIDADE_TUBERCULOSE);

    }
    else if(strstr(formularioComorbidadeDoPaciente, "R") != NULL && strcmp(formularioComorbidadeDoPaciente, "r") != NULL )
    {
        strcpy(formularioComorbidadeDoPaciente, COMORBIDADE_OUTROS);

    }
    else
    {
        strcpy(formularioComorbidadeDoPaciente, "");

    }

    indiceVetor++;
    GenerateGuidToPrimaryKey();

    strcpy(dadosPacientes[indiceVetor].Codigo, GUID_PRIMARY_KEY);
    strcpy(dadosPacientes[indiceVetor].Nome, formularioNome);
    strcpy(dadosPacientes[indiceVetor].CPF, formularioCPF);
    strcpy(dadosPacientes[indiceVetor].Telefone, formularioTelefone);
    strcpy(dadosPacientes[indiceVetor].Endereco, formularioEndereco);
    strcpy(dadosPacientes[indiceVetor].DataNascimento, formularioDataNascimento);
    strcpy(dadosPacientes[indiceVetor].Email, formularioEmail);
    strcpy(dadosPacientes[indiceVetor].DataDoDiagnostico, formularioDataDoDiagnostico);
    strcpy(dadosPacientes[indiceVetor].ComorbidadeDoPaciente, formularioComorbidadeDoPaciente);

    MostraStructsPacientes(indiceVetor);

    EscreverPacientes();

    bool arquivoComorbidadeGerado = FoiArquivoGerado(ARQUIVO_PACIENTES);

    printf("PACIENTE CADASTRADO COM SUCESSO. ");

    if(arquivoComorbidadeGerado)
    {
        printf("ARQUIVO COM TODOS OS PACIENTES FOI ATUALIZADO COM OS DADOS INSERIDOS.");
    }else{
        printf("HOUVE UMA FALHA AO GRAVAR OS PACIENTES EM UM ARQUIVO. PROCURE OS ALUNOS DO PIM IV OU VERIFIQUE O MANUAL PARA SOLU��O DE PROBLEMAS.");
    }

    RetornaAoMenuPrincipal();

}

void MostraStructsPacientes(int indiceVetor)
{
    int i;
    if(indiceVetor == 0){

        int totalPacientesNaLista = sizeof(dadosPacientes) / sizeof(dadosPacientes[0]);

        printf("SEGUE LISTA COMPLETA DE PACIENTES CADASTRADOS NO APLICATIVO.\n\n\n");

        for(i=0;i<totalPacientesNaLista;i++)
        {
            printf("CODIGO=%s|\n", dadosPacientes[i].Codigo);
            printf("NOME=%s|\n", dadosPacientes[i].Nome);
            printf("CPF=%s|\n", dadosPacientes[i].CPF);
            printf("TELEFONE=%s|\n", dadosPacientes[i].Telefone);
            printf("ENDERECO=%s|\n", dadosPacientes[i].Endereco);
            printf("DATANASCIMENTO=%s|\n", dadosPacientes[i].DataNascimento);
            printf("EMAIL=%s|\n", dadosPacientes[i].Email);
            printf("DATADODIAGNOSTICO=%s|\n", dadosPacientes[i].DataDoDiagnostico);
            printf("COMORBIDADEDOPACIENTE=%s|\n\n\n", dadosPacientes[i].ComorbidadeDoPaciente);
        }
    }else{
        printf("CODIGO=%s|\n", dadosPacientes[indiceVetor].Codigo);
        printf("NOME=%s|\n", dadosPacientes[indiceVetor].Nome);
        printf("CPF=%s|\n", dadosPacientes[indiceVetor].CPF);
        printf("TELEFONE=%s|\n", dadosPacientes[indiceVetor].Telefone);
        printf("ENDERECO=%s|\n", dadosPacientes[indiceVetor].Endereco);
        printf("DATANASCIMENTO=%s|\n", dadosPacientes[indiceVetor].DataNascimento);
        printf("EMAIL=%s|\n", dadosPacientes[indiceVetor].Email);
        printf("DATADODIAGNOSTICO=%s|\n", dadosPacientes[indiceVetor].DataDoDiagnostico);
        printf("COMORBIDADEDOPACIENTE=%s|\n\n\n", dadosPacientes[indiceVetor].ComorbidadeDoPaciente);
    }
}

void GerarRelatorioComComorbidade()
{
    system("cls");
    Apresentacao_Aplicativo();

    printf("\n\nSER� GERADO A LISTA COM OS PACIENTES COM COMORBIDADE NO ARQUIVO %s.\n", ARQUIVO_COMORBIDADE);

    EscreverPacientesComComorbidade();

    bool arquivoComorbidadeGerado = FoiArquivoGerado(ARQUIVO_COMORBIDADE);

    if(arquivoComorbidadeGerado)
    {
        printf("\nREPOSTA DO PROCEDIMENTO: O arquivo %s foi gerado corretamente.", ARQUIVO_COMORBIDADE);
    }else{
        printf("\nREPOSTA DO PROCEDIMENTO: Houve uma falha durante a escrita. Procure os alunos do PIM IV ou consulte o manual entregue com o trabalho para saber o que fazer neste caso.");
    }

    RetornaAoMenuPrincipal();

}

void RetornaAoMenuPrincipal()
{
    char opcaoInformada[15];
    const char OPCAO_SAIR[15] = "SAIR";
    const char OPCAO_SAIR_MINUSCULO[15] = "sair";
    const char OPCAO_MENU_PRINCIPAL[15] = "MENU PRINCIPAL";
    const char OPCAO_MENU_PRINCIPAL_MINUSCULO[15] = "menu principal";

    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);

    printf("\n\n********************************************************************************************\n");
    printf("\nVOC� PODE ENCERRAR O APLICATIVO AGORA OU RETORNAR AO MENU PRINCIPAL\n\n");
    printf("PARA PARA FINALIZAR O PROGRAMA DIGITE \"SAIR\" E PARA RETORNAR AO MENU PRINCIPAL DIGITE \"MENU PRINCIPAL\"\n");
    gets(opcaoInformada);

    if(strcmp(opcaoInformada, OPCAO_SAIR) == 0 || strcmp(opcaoInformada, OPCAO_SAIR_MINUSCULO) == 0)
    {
        exit(EXIT_SUCCESS);
    }else if(strstr(opcaoInformada, OPCAO_MENU_PRINCIPAL) != NULL || strstr(opcaoInformada, OPCAO_MENU_PRINCIPAL_MINUSCULO) != NULL)
    {
        MenuInicial();
    }

    system("cls");
    Apresentacao_Aplicativo();
    RetornaAoMenuPrincipal();

}

void MenuInicial()
{
    char opcaoInformada[10];
    const char OPCAO_CADASTRO[10] = "CADASTRO";
    const char OPCAO_CADASTRO_MINUSCULO[10] = "cadastro";
    const char OPCAO_LISTA[10] = "LISTA";
    const char OPCAO_LISTA_MINUSCULO[10] = "lista";
    const char OPCAO_SAIR[15] = "SAIR";
    const char OPCAO_SAIR_MINUSCULO[15] = "sair";

    system("cls");
    Apresentacao_Aplicativo();

    printf("\nESTE � O MENU INICIAL VEJA ABAIXO AS OP��ES QUE S�O POSS�VEIS ACESSAR\n\n");
    printf("DIGITE \"CADASTRO\" PARA IR PARA O PROCEDIMENTO DE CADASTRO \nOU \"LISTA\" PARA GERAR A LISTA PARA A SECRETARIA DA SA�DE\n");
    printf("OU AINDA PARA SAIR DIGITE \"SAIR\" E O APLICATIVO SER� ENCERRADO.\n");
    scanf("%s", opcaoInformada);

    if(strcmp(opcaoInformada, OPCAO_CADASTRO) == 0 || strcmp(opcaoInformada, OPCAO_CADASTRO_MINUSCULO) == 0)
    {
        FormularioDeEntrada();

    }
    else if(strcmp(opcaoInformada, OPCAO_LISTA) == 0 || strcmp(opcaoInformada, OPCAO_LISTA_MINUSCULO) == 0)
    {
        GerarRelatorioComComorbidade();
    }
    else if(strcmp(opcaoInformada, OPCAO_SAIR) == 0 || strcmp(opcaoInformada, OPCAO_SAIR_MINUSCULO) == 0)
    {
        exit(EXIT_SUCCESS);
    }
}

int main() {
    setlocale (LC_ALL, "portuguese-brazilian");

    AutenticacaoDeOperador();
    CarregarDadosIniciais();
    MenuInicial();

    /*dayAge = 5;
    monthAge = 7;
    yearAge = 1981;

    dayCurrent = 23;
    monthCurrent = 7;
    yearCurrent = 2022;

    char formularioDataDoDiagnostico[15];

    while ((ch = getchar()) != '\n' && ch != EOF);
    printf("DATA DO DIAGN�STICO: [Utilize no m�ximo %d caracteres com a mascara dd/mm/aaaa]\n", sizeof(formularioDataDoDiagnostico));
    fgets(formularioDataDoDiagnostico, sizeof(formularioDataDoDiagnostico), stdin);*/

    /*/printf("Data Digitada: %s", )
    /*char idade[20];

    idade[0] = "0";
    //, "6", "/", "0", "5", "/", "1", "9", "9", "1"}
    int posicao;
    for(posicao = 0; posicao < strlen(idade); posicao++)
    {
        printf("posicao %s \n", idade[posicao]);
    }*/

    /*printf("Idade\n");
    int char1;// = strtol(idade[0], NULL, 10);
    fgets(&char1, sizeof(&char1), stdin);

    char1 = char1 +1;
    printf("Soma +1 %i", char1);*/


    //char c = '1';
    //int a = c - '0';

    //printf("idade %i", char1);

    /*int num;
    char cNum[] = {0};
    printf("Digite um numero: ");
    scanf("%s%*c", cNum);
    num = strtol(cNum, NULL, 10);
    printf("%i", num);*/

    /*char a = 'b';
    int ia = (int)a;
    */

    //strcpy(idade, (char)dayCurrent);
    //printf("idade: %d", ia);
    //printf("Anos de idade: %d", calculaIdade());
    return 0;




    //cadastrar o paciente
    //calcular a idade do paciente
    //os pacientes que possuem alguma comorbidade deve ser relacionados para elabora��o de um arquivo.
    //CarregarDadosIniciais();

    //EscreverPacientes2();

    //printf("Nome do Paciente no Objeto: %s \n", objetoAutenticacao[0].Nome);
    //printf("CPF do Paciente no Objeto: %s \n", objetoAutenticacao[0].CPF);

    //AutenticacaoDeOperador();

    //char chave[160] = "LOGIN:12AGORAPOSSOCOLOCARUMVALORENORMENOVASENHA2022;\n";

    //ResgataValorChave(chave);

    //char *senha = ValorChaveExtraido;

    //printf("%s", senha);
/*


    //compara textos corretamente
    printf("\nSENHA �: %s", senha);
    if(strcmp(senha, "NOVASENHA2022") == 0)
    {
        printf(" - A SENHA INFORMADA � A CORRETA");
    }*/


    //remove quebra de linha
    /*int i=0;
    char retorno[30] = "";
    char chave[30] = "nussa:agora;\n";

    int j = 0;
    int lasCharInString = strlen(chave)-2;
    bool isAKeyValue = 0;
    char charStart = ":";
    char charEnd = ";";

    //printf("encontrado: %s; %d", chave, strlen(chave));

    for(i=0; i <= lasCharInString; i++)
    {
        char valueKey = chave[i];
        printf("%c", valueKey);
    }*/

    //RegataValorChave("SEQUENCIA DE CARACTERES");
    /*ResgataCredenciais();
    printf("Login: %s", DadosLogin);
    printf("Senha: %s\n", DadosSenha);

    printf("\nSENHA �: %s", DadosSenha);
    if(strcmp(DadosSenha, "OPERADOR2023") == 0)
    {
        printf(" - A SENHA INFORMADA � A CORRETA");
    }*/

    /*if(strcmp(DadosLogin, ";OPERADOR") == 0)
    {
        printf("Este � o operador %s.\n", DadosLogin);
    }else{
        printf("Compara��o n�o obteve exito %s %s", DadosLogin, ";OPERADOR");
    }

    if(strcmp(DadosSenha, ";OPERADOR2022") == 0)
    {
        printf("Esta � a senha correta.\n");
    }

    char entradaLogin[30] = "";
    strcat(entradaLogin, ";");
    printf("valor da fun��o strcat %s", entradaLogin);*/
    //exit(EXIT_SUCCESS);

    //char loginPadraoSistema[QUANTIDADE_CARACTERES];

    //char entradaLogin[30] = "";


    //strcpy(entradaLogin, );

    //printf("OPERADOR ENCONTRADO %s", entradaLogin);

    /*if(strcmp(DadosLogin, entradaLogin) == 0)
    {
        printf("LOGIN OPERADOR UTILIZADO.-");
    }else{
        printf("COMPARA��O DEU RUIM");
    }
    printf("FIM DO PROCESSO %s", entradaLogin);*/

    /*char string[50] = "LOGIN;OPERADOR";
    // Extract the first token
    char * token = strtok(string, ";");
    // loop through the string to extract all other tokens
    while( token != NULL ) {
      printf( " %s\n", token ); //printing each token
      token = strtok(NULL, " ");
    }
    return 0;*/

    return 0;
}
