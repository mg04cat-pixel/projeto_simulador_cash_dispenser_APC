#include <stdio.h>
#include <stdlib.h> // Para função atoi - conversão de texto em nro inteiro 
#include <string.h> // Para função strcpy - copiar texto
#include <time.h> // Biblioteca para data e hora 

int main () {
    // DATA
    time_t agora = time(NULL); // pega o tempo atual
    struct tm *info = localtime(&agora); // converte para data e hora local

    // VARIAVEIS
    char data[11];
    int opcao_menu; // Qual opção será selecionada no menu
    int valores_notas[4] = {10,20,50,100}; // Valores disponíveis de notas
    int qtde_notas[4] = {0,0,0,0}; // Quantidade de notas
    int i; // Para loops
    int adicionar; // Manipulação de abastecimento de notas
    char linha[20]; // Leitura de stdin
    int valor_saque, resto, quantas; // Para Sacar dinheiro
    int saque_final[4] = {0,0,0,0}; // Notas entregues

    // HISTÓRICO
    char hist_tipo[100][10]; // "SAQUE" ou "ABASTECER"
    int hist_valor[100]; // Valor em dinheiro da operação
    char hist_data[100][20]; // Data e hora no formato dd/mm/aaaa hh:mm:ss
    int total_hist = 0; // Quantos registros já existem
    int total_abastecido; // Soma em dinheiro do abastecimento atual

    setvbuf(stdout, NULL, _IONBF, 0); // envia o printf na hora, necessário para o servidor

    strftime(data, sizeof(data), "%d/%m/%Y", info); // formata padrão dd/mm/aaaa

    printf("UNICSUL - Simulador de Cash Dispenser - versão 2026 - %s \n\n", data );
    // MENU INICIAL
    do { // Toda vez que o case quebrar, ele volta ao menu
        printf("\nMenu Inicial \n\n 0 - Exibir Notas Disponíveis\n 1 - Abastecer ATM\n 2 - Sacar Dinheiro\n 3 - Exibir Histórico\n 9 - Sair\n\n Escolha uma operação: "); // mais opção 3
        fgets(linha, sizeof(linha), stdin); // Lê o que usuário digita, não trava com letra e não deixa enter sobrando
        opcao_menu = atoi(linha); // Texto inválido vira 0

        // OPÇOES
        switch (opcao_menu) {
            case 0:
                // EXIBIR NOTAS
                for (i = 0; i < 4; i++) {   // Loop percorre valores e quantidades de notas
                    printf("\nNotas %d: %d\n", valores_notas[i], qtde_notas[i]); 
                }
                break;

            case 1:
                // ABASTECER ATM
                total_abastecido = 0; // zera o total antes de abastecer
                for (i = 0; i < 4; i++) { 
                    printf("\nNotas %d: ", valores_notas[i]);
                    fgets(linha, sizeof(linha), stdin); // Lê o que usuário digita e permite enter vazio
                    adicionar = atoi(linha);   // Enter vazio vira 0

                    if (adicionar < 0) { // Se valor for menor que zero é desconsiderado
                        printf("\nValor inválido!\n");
                        adicionar = 0; // Sem isso, o número negativo seria subtraído do estoque
                    }
                    qtde_notas[i] = qtde_notas[i] + adicionar;   // Soma a quantidades de notas
                    total_abastecido = total_abastecido + adicionar * valores_notas[i]; // valor em dinheiro abastecido
                }
                for (i = 0; i < 4; i++) {
                    printf("\nConfirmando o abastecimento %d: %d\n", valores_notas[i], qtde_notas[i]);
                }

                // registra no histórico (só se abasteceu alguma nota)
                if (total_abastecido > 0 && total_hist < 100) {
                    agora = time(NULL); // pega a hora de AGORA
                    info = localtime(&agora);
                    strcpy(hist_tipo[total_hist], "ABASTECER");
                    hist_valor[total_hist] = total_abastecido;
                    strftime(hist_data[total_hist], 20, "%d/%m/%Y %H:%M:%S", info);
                    total_hist++;
                }
                break;

            case 2:
                // SACAR DINHEIRO
                printf("\nDigite o valor do Saque: ");
                fgets(linha, sizeof(linha), stdin); // fgets para não sobrar enter no menu
                valor_saque = atoi(linha);

                if (valor_saque <= 0 || valor_saque % 10 != 0) {
                    printf("\nValor inválido. Digite um múltiplo de 10\n");
                } else {
                    resto = valor_saque;
                    for (i = 3; i >= 0; i--) { // Da nota de maior valor para a menor
                        quantas = resto / valores_notas[i];   // Quantas notas cabem no valor
                        if (quantas > qtde_notas[i]) {
                            quantas = qtde_notas[i];   // Garante que não passa da qtde_notas disponível
                        }
                        saque_final[i] = quantas;
                        resto = resto - quantas * valores_notas[i]; // Realiza o uso das notas
                    }
                    if (resto == 0) {
                        for (i = 0; i < 4; i++) {
                            qtde_notas[i] = qtde_notas[i] - saque_final[i]; // Notas supriram o valor do saque
                        }
                        printf("\nSaque realizada com sucesso\n");
                        printf("\nValor do Saque: %d\n", valor_saque);
                        for (i = 0; i < 4; i++) {
                            printf("\n Notas %d: %d\n", valores_notas[i], saque_final[i]); // Resultado final do saque
                        }

                        // registra no histórico
                        if (total_hist < 100) {
                            agora = time(NULL); // pega a hora de AGORA
                            info = localtime(&agora);
                            strcpy(hist_tipo[total_hist], "SAQUE");
                            hist_valor[total_hist] = valor_saque;
                            strftime(hist_data[total_hist], 20, "%d/%m/%Y %H:%M:%S", info);
                            total_hist++;
                        }
                    } else {
                        printf("\nSaque negado - ATM sem notas para esse valor\n");
                    }
                }
                break;

            case 3:
                // EXIBIR HISTÓRICO
                if (total_hist == 0) {
                    printf("\nNenhuma operação registrada.\n");
                }
                for (i = 0; i < total_hist; i++) {
                    printf("\n%s - Valor: %d - %s\n", hist_tipo[i], hist_valor[i], hist_data[i]);
                }
                break;

            case 9:
                printf("\nEncerrando...\n");
                break;

            default:
                printf("\nOpção inválida, tente novamente.\n");
        }

    } while (opcao_menu != 9); // Para de executar o menu
    return 0;
}