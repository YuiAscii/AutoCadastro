// Codigo para trabalho da AV2 do 1 Semestre de 2026
// Feito por YuiAscii

#include <stdio.h>  // Fornece recursos de print
#include <stdlib.h> // Funcoes do sistema
#include <string.h> // Manipulação de Strings
#include <time.h>   // Funcoes de tempo, usado para gerar o ID aleatorio dos registros.
/*
Essa função é responsável por contar quantos registros existem no arquivo, ele cria a variavel
de linha e ela basicamente procura a quantidade de linhas tipo "=======" presentes no arquivo.
Cada um dos registros contém 2 dessas, uma no começo e uma no fim, então o programa divide por 2 e consegue a quantidade
de registro atual no programa.
*/
int contarRegistros(FILE *arquivo)
{
    char linha[200];
    if (fgets(linha, sizeof(linha), arquivo) == NULL)
        return 0;

    if (strstr(linha, "=========================="))
        return 1 + contarRegistros(arquivo);

    return contarRegistros(arquivo);
}
/*
Essa éa função de login para moderadores, é simples, são definidas variaveis que o usuario preencherá e também são
hard codadas qual é o usuario e senha correta, o programa vê se o valor da variavel scaneada e a hardcodada são iguais,
se ambas forem iguais para o usuario e a senha, é feito o login do moderador.
Após isso, se nao houver nenhum registro existente, não aparece no programa (ele tira o registro do arquivo txt registros.txt)
e houver nenhum, não aparece, se houver, ele lista e mostra a quantidade de registros.
Se o total ultrapassar 16 registros, é alertado.
*/

void LoginMod()
{
    char nmodUsuario[30], nmodSenha[40];
    char usuarioCorreto[] = "ModCarros";
    char senhaCorreta[] = "senhadaorapraumsistemadecarros";

    printf("Boas-vindas, insira seu usuario:\n");
    scanf(" %[^\n]", nmodUsuario);
    printf("Insira sua senha: \n");
    scanf(" %[^\n]", nmodSenha);

    if (strcmp(nmodUsuario, usuarioCorreto) == 0 && strcmp(nmodSenha, senhaCorreta) == 0)
    {
        system("cls");
        printf("==========================\n");
        printf("  Bem-vindo, Moderador.   \n");
        printf("==========================\n\n");

        FILE *arquivo = fopen("registros.txt", "r");
        if (arquivo == NULL)
        {
            printf("Nenhum registro encontrado.\n");
        }
        else
        {
            int total = contarRegistros(arquivo);
            printf("Total de registros cadastrados: %d\n\n", total / 2);
            rewind(arquivo);
            if (total > 16)
            {
                printf("Limite de carros atingido!!\n\n");
            }

            char linha[200];
            while (fgets(linha, sizeof(linha), arquivo))
            {
                printf("%s", linha);
            }
            fclose(arquivo);
        }
    }
    else
    {
        printf("Usuario ou senha incorretos!\n");
    }
}

/*
Essa é a função responsável pela geração aleatoria de numeros para o seu User ID.
O programa roda 16 vezes até que chege no último digito, cada vez que ele roda ele gera um numero aleatorio entre 0 e 9,
e o '0' é somado ao numero gerado, para que a memoria mostre o numero corretamente.
Basicamente, o rand() gera um numero de 0-9, porém o valor é gerado é ele bruto, se ele gerar 5 ele realmente gera 5 na memoria.
Porém o que queremos é um digito legivel, e não um "bruto", dai adicionamos o 0 para que ele entre nos legiveis.
*/
void gerarID(char *id)
{
    for (int j = 0; j < 16; j++)
    {
        id[j] = '0' + (rand() % 10);
    }
    id[16] = '\0';
}

int main()
{
    /*
    O srand aqui é pra gerar os numeros aleatorios, se eu deixasse ele na funcao era capaz de ele gerar
    os mesmos IDs iguais sempre, enquanto dessa maneira ele sempre gera de certeza IDs aleatorios.

    Aqui no começo são declaradas as variaveis que usaremos, eu organizei elas com numeros em ordem por organização.
    a variavel de destino usa o conceito de pointer, nós usamos ela no sistema de registros para que quando o usuarios
    mande o input, a maquina saiba para qual variavel enviar o valor, através do pointer.
    */
    srand(time(NULL));
    int opcaoacesso, i, continuar = 1;

    char nUsuario[40], ncpf[12], nModeloCarro[40], nMarca[30], nAno[15];
    char nTipo[30], nCor[30], nEndereco[50], nPlaca[8], nNumero[14];

    char nPerguntas[][50] = {
        "Nome de Usuario",   // 0
        "CPF",               // 1
        "Modelo do Carro",   // 2
        "Marca do Veiculo",  // 3
        "Ano de Fabricacao", // 4
        "Tipo de Veiculo",   // 5
        "Cor do Veiculo",    // 6
        "Endereco",          // 7
        "Placa do Carro" ,   // 8
        "Número de Telefone do Usuario" // 9
    };

    char *destinos[] = {
        nUsuario,     // 0
        ncpf,         // 1
        nModeloCarro, // 2
        nMarca,       // 3
        nAno,         // 4
        nTipo,        // 5
        nCor,         // 6
        nEndereco,    // 7
        nPlaca,       // 8
        nNumero       // 9
    };

    do
    {
        printf("==========================\n");
        printf("Bem-vindo ao AutoCadastro!\n");
        printf("Seu sistema de registro de veiculos.\n");
        printf("==========================\n\n");

        printf("O que deseja acessar?\n\n");
        printf("1. Cadastro de veiculos\n");
        printf("2. Espaco Moderador\n");
        printf("3. Sair\n");
        scanf("%d", &opcaoacesso);
        system("cls");

        switch (opcaoacesso)
        {
        case 1:
            for (i = 0; i < 10; i++)
            {
                /*
                Esse codigo se repete 9 vezes, nas 9 vezes ele cicla por uma variavel com varias strings que vai dizer o que
                precisará ser inserido e ao mesmo tempo a variavel pointer destinos, que conforme você faz o input,
                já envia o valor para a posição correta na memória.
                Além disso ele faz a verificação se o CPF é maior que 11 digitos e se a placa tem ultrapassa o limite
                de 7 digitos.

                Se todos os requisitos forem cumpridos, ele avisa que o registro foi concluido
                e te da um exemplo de registro concluido.
                */

                printf("Insira o %s: \n", nPerguntas[i]);
                scanf(" %[^\n]", destinos[i]);

                if (i == 1 && strlen(ncpf) > 11)
                {
                    printf("Seu CPF e invalido.\n");
                    i--;
                }
                else if (i == 8 && strlen(nPlaca) != 7)
                {
                    printf("Sua placa e invalida.\n");
                    i--;
                }
                else if (i == 9)
                {
                    char nid[17];
                    gerarID(nid);

                    printf("Registro feito com sucesso.\n");
                    printf("ID do registro: %s\n", nid);

                    FILE *arquivo = fopen("registros.txt", "a");
                    if (arquivo == NULL)
                    {
                        printf("Erro ao salvar registro!\n");
                    }
                    else
                    {
                        fprintf(arquivo, "==========================\n");
                        fprintf(arquivo, "Usuario: %s\n", nUsuario);
                        fprintf(arquivo, "CPF: %s\n", ncpf);
                        fprintf(arquivo, "Modelo do Veiculo: %s\n", nModeloCarro);
                        fprintf(arquivo, "Marca do Veiculo: %s\n", nMarca);
                        fprintf(arquivo, "Ano de Fabricacao: %s\n", nAno);
                        fprintf(arquivo, "Tipo de Veiculo: %s\n", nTipo);
                        fprintf(arquivo, "Cor do Veiculo: %s\n", nCor);
                        fprintf(arquivo, "Endereco: %s\n", nEndereco);
                        fprintf(arquivo, "Placa: %s\n", nPlaca);
                        fprintf(arquivo, "Numero do Usuario: %s\n", nNumero);
                        fprintf(arquivo, "ID: %s\n", nid);
                        fprintf(arquivo, "==========================\n");
                        fclose(arquivo);
                    }
                }
            }

            printf("\n1. Voltar ao menu\n");
            printf("2. Fechar o programa\n");
            scanf("%d", &continuar);
            system("cls");
            break;

        case 2:
            LoginMod();

            printf("\n1. Voltar ao menu\n");
            printf("2. Fechar o programa\n");
            scanf("%d", &continuar);
            system("cls");
            break;

        default:
            continuar = 2;
            break;
        }

    } while (continuar == 1);

    printf("Encerrando o programa\n");
    return 0;
}