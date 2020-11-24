#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

typedef struct credenciais_usuario
{
     char nome[5];
     char senha[9];
}CredenciaisUsuario;

typedef struct endereco
{
    char logradouro[30];
    int numero;
    char bairro[20];
    char cidade[15];
    char estado[3];
    char cep[10];
}Endereco;

typedef struct dadosPaciente
{
    char nome[30];
    char dtNasc[11];
    char dtDiag[11];
    char cpf[12];
    Endereco ender;
    char email[30];
    double telefone;
    char comorbidades[128];
}Paciente;


void desenharSegmento(char carac)
{
    for (int i = 0; i < 80; i++)
    {
        printf("%c",carac);
    }
}

void desenharCabecalho()
{
    desenharSegmento('=');
    printf("\n\n\t\t\tCadastro de pacientes com covid-19\n\n\n");
    desenharSegmento('=');
    printf("\n");
}

void desenharNomeDaTela(char nomeDaTela[])
{
    printf("\t%s\n",nomeDaTela);
    desenharSegmento('_');

}

int desenharTelaDeAcessoEVerificarCredenciais(CredenciaisUsuario cred)
{
    char auxNomeUsuario[8];
    char auxSenhaUsuario[16];
    printf("\n\n\tNome de usuario: ");

    gets(auxNomeUsuario);

    printf("\n\tSenha: ");

    gets(auxSenhaUsuario);

    //Verifica a igualdade.
    if (strcmp(cred.nome, auxNomeUsuario) == 0 && strcmp(cred.senha, auxSenhaUsuario) == 0)
    {
        return 0;
    }

    return 1;
}

void desenharMsgDeAlerta(char msg[], char simbolo)
{

    desenharSegmento(simbolo);
    printf("\n%s\n\n", msg);
    desenharSegmento(simbolo);
}

int procurarNumeros(char palavra[])
{
    int comprimento = strlen(palavra);
    for (int i = 0; i < comprimento; i++)
    {
        if (palavra[i] < 48 || palavra[i] > 57)
        {
            //foi encontrado um caractere diferente de um numero

            return 0;
        }
    }
        //somente numeros
        return 1;
}

int procurarNomes(char palavra[],char caracPermitidos[])
{
    int comprimentoPlv = strlen(palavra), comprimentoCarac = strlen(caracPermitidos);

    for (int i = 0; i < comprimentoPlv; i++)
    {
        if (palavra[i] < 65 || (palavra[i] > 90 && palavra[i] < 97) || palavra[i] > 122 )
        {
            int possuiCaracPermit = 0;
            for (int j = 0; j < comprimentoCarac; j++)
            {
                if (palavra[i] == caracPermitidos[j])
                {
                    possuiCaracPermit = 1;
                    break;
                }
            }
            if (possuiCaracPermit == 0)
            {
                //nenhum caractere permitido foi encontrado
                return 0;
            }
        }
    }
    //somente letras ou caracteres permitidos
    return 1;
}

void pegarDiaMesAno(char data[],int* dia, int* mes, int* ano)
{
    char aux[5];

    aux[0] = data[0];
    aux[1] = data[1];
    aux[2] = '\0';
    //converter dia para o tipo int
    *dia = atoi(aux);

    aux[0] = data[3];
    aux[1] = data[4];
    aux[2] = '\0';
    //converter mês para o tipo int
    *mes = atoi(aux);

    aux[0] = data[6];
    aux[1] = data[7];
    aux[2] = data[8];
    aux[3] = data[9];
    aux[4] = '\0';
    //converter ano para o tipo int
    *ano = atoi(aux);
}

int serAnoBissexto(int ano)
{
    if (ano % 400 == 0 || (ano % 100 != 0 && ano % 4 == 0))
    {
        return 1;
    }

    return 0;
}

int validarData(char data[])
{
    int dia, mes, ano;
    pegarDiaMesAno(data, &dia, &mes, &ano);

    const time_t tempoBruto = time(NULL);
    struct tm* dataAtual = localtime(&tempoBruto);
    int anoAtual = dataAtual->tm_year + 1900;

    if (dia > 31 || dia < 1 || mes > 12 || mes < 1 || ano > anoAtual || ano < (anoAtual - 200) || (dia == 31 && (mes == 4 || mes == 6 || mes == 9 || mes == 11)) || serAnoBissexto(ano) == 0 && dia == 29 && mes == 2)
    {
        //não é válida
        return 0;
    }
    return 1;
}

int verificarData(char data[])
{
    if ((strlen(data) == 10 && data[2] == '/' && data[5] == '/' ) && validarData(data))
    {
        return 1;
    }
    return 0;
}

int retornarIdade(char dtDiag[], char dtNasc[])
{
    int diaDiag, mesDiag, anoDiag, diaNasc, mesNasc, anoNasc, idade;
    pegarDiaMesAno(dtDiag, &diaDiag, &mesDiag, &anoDiag);
    pegarDiaMesAno(dtNasc, &diaNasc, &mesNasc, &anoNasc);

    if (anoDiag < anoNasc || (anoDiag == anoNasc && mesDiag < mesNasc) || (anoDiag == anoNasc && mesDiag == mesNasc && diaDiag < diaNasc))
    {
        //a data de diagnóstico não pode ser inferior a data de nascimento
        return -1;
    }

    idade = anoDiag - anoNasc;

    if ((anoDiag > anoNasc && mesDiag < mesNasc) || (anoDiag > anoNasc && mesDiag == mesNasc && diaDiag < diaNasc))
    {
        //Ainda não fez aniversário
        idade--;
    }

    return idade;
}

int naoSerVazio(char primeiraLetra)
{
    if ((int)primeiraLetra != 0 && (int)primeiraLetra != 32)
    {
        return 1;
    }
    return 0;
}


int main()
{
    CredenciaisUsuario admin;
    admin.nome[0] = 'a';
    admin.nome[1] = 'd';
    admin.nome[2] = 'm';
    admin.nome[3] = 'h';
    admin.nome[4] = '\0';

    admin.senha[0] = 'm';
    admin.senha[1] = 'g';
    admin.senha[2] = '5';
    admin.senha[3] = '/';
    admin.senha[4] = '2';
    admin.senha[5] = 'e';
    admin.senha[6] = '#';
    admin.senha[7] = 'b';
    admin.senha[8] = '\0';

   /*//Usadas para testes
    CredenciaisUsuario faceis;
    faceis.nome[0] = 'a'; faceis.nome[1] = '\0';
    faceis.senha[0] = 's'; faceis.senha[1] = '\0';*/

    const int teclaNeutra = 15;

    char auxTextoGeral[128];

    int permaneceTelaDeAcesso, permaneceNoPrograma, cadastraOutroPaciente;

    do
    {
        //Tela de acesso
        do
        {
            desenharCabecalho();
            desenharNomeDaTela("Credenciais de acesso");

            //Desenha a tela de acesso e devolve um numero que indica a continuidade
            permaneceTelaDeAcesso = desenharTelaDeAcessoEVerificarCredenciais(admin);
            if (permaneceTelaDeAcesso == 1)
            {
                desenharMsgDeAlerta("  Credenciais invalidas. Pressione qualquer tecla para tentar novamente.", '*');
                getch();
            }

            //limpa a tela para qualquer um dos dois casos
            system("cls");
        } while (permaneceTelaDeAcesso == 1);

        //Tela de cadastro e criacao dos arquivos
        do
        {
            //declaracao e inicializacao dos primeiros caracteres com um valor fora dos valores possiveis do teclado
            Paciente p;
            p.cpf[0] = p.dtDiag[0] = p.dtNasc[0] = p.email[0] = p.ender.bairro[0]
                = p.ender.cep[0] = p.ender.cidade[0] = p.ender.estado[0] = p.comorbidades[0]
                = p.ender.logradouro[0] = p.nome[0] = teclaNeutra;
            p.ender.numero = -1;
            p.telefone = -1;

            do
            {
                desenharCabecalho();
                desenharNomeDaTela("Novo paciente");
                desenharMsgDeAlerta("  Obs.: Todos os campos marcados com \"*\" precisam ser preenchidos.", '.');

                //Preechimento e analise do nome
                if (p.nome[0] == teclaNeutra)
                {
                    printf("\n\t*Nome: ");
                    gets(auxTextoGeral);


                    if (procurarNomes(auxTextoGeral," ") && strlen(auxTextoGeral) < 30 && naoSerVazio(auxTextoGeral[0]))
                    {
                        strcpy(p.nome, auxTextoGeral);
                    }
                    else
                    {
                        desenharMsgDeAlerta("  Somente letras, espacos e no maximo 29 caracteres sao permitidos. Pressione qualquer tecla para tentar novamente.",'*');
                        getch();
                        system("cls");
                        continue;
                    }
                }
                else
                {
                    printf("\n\t*Nome: %s\n", p.nome);
                }

                //Preechimento e analise do CPF
                if (p.cpf[0] == teclaNeutra)
                {
                    printf("\n\t*CPF: ");
                    gets(auxTextoGeral);
                    if (procurarNumeros(auxTextoGeral) && strlen(auxTextoGeral) == 11)
                    {
                        strcpy(p.cpf, auxTextoGeral);
                    }
                    else
                    {
                        desenharMsgDeAlerta("  Digite apenas numeros e todos os 11 digitos do CPF. Pressione qualquer tecla para tentar novamente.", '*');
                        getch();
                        system("cls");
                        continue;
                    }
                }
                else
                {
                    printf("\n\t*CPF: %s\n", p.cpf);
                }

                //Preechimento e analise da data de nascimento
                if (p.dtNasc[0] == teclaNeutra)
                {
                    printf("\n\t*Data de nascimento: ");
                    gets(auxTextoGeral);
                    if (verificarData(auxTextoGeral))
                    {
                        strcpy(p.dtNasc, auxTextoGeral);
                    }
                    else
                    {
                        desenharMsgDeAlerta("  A data digitada nao e valida. Ela precisa estar no formato dd/mm/aaaa e ser anterior (ate 200 anos) ou igual ao ano atual. Pressione qualquer tecla para tentar novamente.", '*');
                        getch();
                        system("cls");
                        continue;
                    }
                }
                else
                {
                printf("\n\t*Data de nascimento: %s\n", p.dtNasc);
                }

                //Preechimento e analise da data do diagnostico
                if (p.dtDiag[0] == teclaNeutra)
                {
                    printf("\n\t*Data do diagnostico: ");
                    gets(auxTextoGeral);

                    if (verificarData(auxTextoGeral) && retornarIdade(auxTextoGeral, p.dtNasc) > -1)
                    {

                        strcpy(p.dtDiag, auxTextoGeral);
                    }
                    else
                    {
                        desenharMsgDeAlerta("  A data digitada nao e valida. Ela precisa estar no formato dd/mm/aaaa e ser anterior (ate 200 anos) ou igual ao ano atual. Não pode ser anterior em relacao a data de nascimento. Pressione qualquer tecla para tentar novamente.", '*');
                        getch();
                        system("cls");
                        continue;
                    }
                }
                else
                {
                    printf("\n\t*Data do diagnostico: %s\n", p.dtDiag);
                }

                //Preechimento e analise de comorbidades
                if (p.comorbidades[0] == teclaNeutra)
                {
                    printf("\n\tComorbidades: ");
                    gets(auxTextoGeral);
                    if (strlen(auxTextoGeral) < 128)
                    {
                        strcpy(p.comorbidades, auxTextoGeral);
                    }
                    else
                    {
                        desenharMsgDeAlerta("  No maximo 127 caracteres sao permitidos. Pressione qualquer tecla para tentar novamente.", '*');
                        getch();
                        system("cls");
                        continue;
                    }
                }
                else
                {
                    printf("\n\tComorbidades: %s\n", p.comorbidades);
                }

                //Preechimento e analise do logradouro
                if (p.ender.logradouro[0] == teclaNeutra)
                {
                    printf("\n\tLogradouro: ");
                    gets(auxTextoGeral);
                    if (procurarNomes(auxTextoGeral, " .") && strlen(auxTextoGeral) < 30)
                    {
                        strcpy(p.ender.logradouro, auxTextoGeral);
                    }
                    else
                    {
                        desenharMsgDeAlerta("  Somente letras, espacos, pontos finais e no maximo 29 caracteres sao permitidos. A formatacao completa sera feita automaticamente em seguida. Pressione qualquer tecla para tentar novamente.", '*');
                        getch();
                        system("cls");
                        continue;
                    }
                }
                else
                {
                    printf("\n\tLogradouro: %s\n", p.ender.logradouro);
                }

                //Preechimento e analise do numero do logradouro
                if (p.ender.numero < 0)
                {
                    printf("\n\t*Numero do logradouro: ");
                    gets(auxTextoGeral);
                    if (procurarNumeros(auxTextoGeral) && strlen(auxTextoGeral) < 6 && naoSerVazio(auxTextoGeral[0]))
                    {
                        //converter cadeia para int
                        p.ender.numero = atoi(auxTextoGeral);
                    }
                    else
                    {
                        desenharMsgDeAlerta("  Somente numeros com no maximo 5 digitos sao permitidos. A formatacao completa sera feita automaticamente em seguida. Pressione qualquer tecla para tentar novamente.", '*');
                        getch();
                        system("cls");
                        continue;
                    }
                }
                else
                {
                    printf("\n\t*Numero do logradouro: %d\n", p.ender.numero);
                }

                //Preechimento e analise do bairro
                if (p.ender.bairro[0] == teclaNeutra)
                {
                    printf("\n\tBairro: ");
                    gets(auxTextoGeral);
                    if (procurarNomes(auxTextoGeral, " .") && strlen(auxTextoGeral) < 20)
                    {
                        strcpy(p.ender.bairro, auxTextoGeral);
                    }
                    else
                    {
                        desenharMsgDeAlerta("  Somente letras, espacos, pontos finais e no maximo 19 caracteres sao permitidos. A formatacao completa sera feita automaticamente em seguida. Pressione qualquer tecla para tentar novamente.", '*');
                        getch();
                        system("cls");
                        continue;
                    }
                }
                else
                {
                    printf("\n\tBairro: %s\n", p.ender.bairro);
                }

                //Preechimento e analise da cidade
                if (p.ender.cidade[0] == teclaNeutra)
                {
                    printf("\n\tCidade: ");
                    gets(auxTextoGeral);
                    if (procurarNomes(auxTextoGeral, " .") && strlen(auxTextoGeral) < 15)
                    {
                        strcpy(p.ender.cidade, auxTextoGeral);
                    }
                    else
                    {
                        desenharMsgDeAlerta("  Somente letras, espacos, pontos finais e no maximo 14 caracteres sao permitidos. A formatacao completa sera feita automaticamente em seguida. Pressione qualquer tecla para tentar novamente.", '*');
                        getch();
                        system("cls");
                        continue;
                    }
                }
                else
                {
                    printf("\n\tCidade: %s\n", p.ender.cidade);
                }

                //Preechimento e analise do estado
                if (p.ender.estado[0] == teclaNeutra)
                {
                    printf("\n\tEstado: ");
                    gets(auxTextoGeral);
                    if (procurarNomes(auxTextoGeral, " ") && strlen(auxTextoGeral) < 3)
                    {
                        strcpy(p.ender.estado, auxTextoGeral);
                    }
                    else
                    {
                        desenharMsgDeAlerta("  Digite somente a sigla do estado. A formatacao completa sera feita automaticamente em seguida. Pressione qualquer tecla para tentar novamente.", '*');
                        getch();
                        system("cls");
                        continue;
                    }
                }
                else
                {
                    printf("\n\tEstado: %s\n", p.ender.estado);
                }

                //Preechimento e analise do CEP
                if (p.ender.cep[0] == teclaNeutra)
                {
                    printf("\n\t*CEP: ");
                    gets(auxTextoGeral);
                    if (procurarNumeros(auxTextoGeral) && strlen(auxTextoGeral) == 8)
                    {
                        strcpy(p.ender.cep, auxTextoGeral);
                    }
                    else
                    {
                        desenharMsgDeAlerta("  Digite apenas numeros e todos os 8 digitos do CEP. Pressione qualquer tecla para tentar novamente.", '*');
                        getch();
                        system("cls");
                        continue;
                    }
                }
                else
                {
                    printf("\n\t*CEP: %s\n", p.ender.cep);
                }

                //Preechimento e analise do telefone
                if (p.telefone < 0)
                {
                    printf("\n\t*Telefone: ");
                    gets(auxTextoGeral);
                    if (procurarNumeros(auxTextoGeral) && (strlen(auxTextoGeral) == 11 || strlen(auxTextoGeral) == 10))
                    {
                        //converter cadeia para double
                        p.telefone = atof(auxTextoGeral);
                    }
                    else
                    {
                        desenharMsgDeAlerta("  Digite apenas numeros e todos os 10 digitos do telefone fixo ou 11 digitos do celular (DDD e o numero). Pressione qualquer tecla para tentar novamente.", '*');
                        getch();
                        system("cls");
                        continue;
                    }
                }
                else
                {
                    printf("\n\t*Telefone: %0.0f\n", p.telefone);
                }

                //Preechimento e analise do email
                if (p.email[0] == teclaNeutra)
                {
                    printf("\n\tE-mail: ");
                    gets(auxTextoGeral);
                    if (strlen(auxTextoGeral) < 30)
                    {
                        strcpy(p.email, auxTextoGeral);
                    }
                    else
                    {
                        desenharMsgDeAlerta("  No maximo 29 caracteres sao permitidos. Pressione qualquer tecla para tentar novamente.", '*');
                        getch();
                        system("cls");
                        continue;
                    }
                }
                else
                {
                    printf("\n\tE-mail: %s\n", p.email);
                }

                break;

            } while (1);

            //Gerar arquivos
            FILE* arqDoPaciente;
            //compr do arquivo: nome, espaco, CPF, extensao e caractere nulo
            int comprimentoTotal = strlen(p.nome) + 17;
            int comprNome = comprimentoTotal - 17;

            char* nomeArqPaciente;
            nomeArqPaciente = (char*)malloc(comprimentoTotal * sizeof(char));

            int i;
            for ( i = 0; i < comprNome; i++)
            {
                nomeArqPaciente[i] = p.nome[i];
            }

            nomeArqPaciente[comprNome] = ' ';
            comprNome++;

            for ( i = 0; i < 11 ; i++)
            {
                nomeArqPaciente[comprNome + i] = p.cpf[i];
            }

            nomeArqPaciente[comprNome + 11] = '.';
            nomeArqPaciente[comprNome + 12] = 't';
            nomeArqPaciente[comprNome + 13] = 'x';
            nomeArqPaciente[comprNome + 14] = 't';
            nomeArqPaciente[comprNome + 15] = '\0';

            arqDoPaciente = fopen(nomeArqPaciente, "w");
            fprintf(arqDoPaciente, "Nome: %s\n\nCPF: %s\n\nData de nascimento:  %s\n\nData de diagnóstico: %s\n\nComorbidades: %s\n\nEndereço: %s, %d - %s, %s - %s, %s\n\nTelefone: %0.0f\n\nE-mail: %s", p.nome, p.cpf, p.dtNasc, p.dtDiag, p.comorbidades, p.ender.logradouro, p.ender.numero, p.ender.bairro, p.ender.cidade, p.ender.estado, p.ender.cep, p.telefone, p.email);
            fclose(arqDoPaciente);

            free(nomeArqPaciente);

            desenharMsgDeAlerta("  O arquivo do paciente foi gerado com sucesso.", '-');

            //Verifica se o paciente pertence ao grupo de risco e o inclui o CEP e a idade ao arquivo do grupo
            int idade = retornarIdade(p.dtDiag, p.dtNasc);
            if (idade > 64)
            {
                FILE* arq;
                arq = fopen("_Grupo de risco.txt", "a");
                fprintf(arq, "%s\t%d\n", p.ender.cep, idade);
                fclose(arq);
                desenharMsgDeAlerta("  Este paciente tambem foi adicionado ao arquivo do grupo de risco.", '-');
            }

            desenharMsgDeAlerta("  Aperte [Enter] para cadastrar outro paciente.\n\n  Aperte [A] ou [a] para voltar a tela de acesso.\n\n  Aperte [Esc] para encerrar o programa.", '.');

            char resposta;
            do
            {
                resposta = getch();

            } while (resposta != 13 && resposta != 65 && resposta != 97 && resposta != 27);

            switch (resposta)
            {
            case 13:
                cadastraOutroPaciente = 1;
                break;
            case 65:
            case 97:
                cadastraOutroPaciente = 0;
                permaneceNoPrograma = 1;
                break;
            case 27:
                cadastraOutroPaciente = 0;
                permaneceNoPrograma = 0;
            default:
                break;
            }
            system("cls");

        } while (cadastraOutroPaciente == 1);

    } while (permaneceNoPrograma == 1);
    return 0;
};

