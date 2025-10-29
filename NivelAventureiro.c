#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Struct para representar um território
struct Territorio {
    char nome[30];
    char cor[10];
    int quantitropa;
};

// Função para limpar o buffer de entrada
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função que lista todos os territórios
void listarTerritorios(struct Territorio *mapa, int total) {
    if (mapa == NULL || total == 0) {
        printf("\nNenhum território cadastrado!\n");
        return;
    }

    printf("\n====================================\n");
    printf(" MAPA DO MUNDO - ESTADO ATUAL\n");
    printf("====================================\n");
    for (int i = 0; i < total; i++) {
        printf("%d. %s (Exército %s, Tropas: %d)\n",
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].quantitropa);
    }
}

// Função que simula um ataque entre dois territórios
void atacar(struct Territorio *atacante, struct Territorio *defensor) {
    printf("\n>>> Ataque iniciado entre %s (Exército %s) e %s (Exército %s)\n",
           atacante->nome, atacante->cor, defensor->nome, defensor->cor);

    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Não é possível atacar um território da mesma cor!\n");
        return;
    }

    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("Dado do atacante: %d \n", dadoAtacante);
    printf("Dado do defensor: %d \n", dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        defensor->quantitropa--;

        if (defensor->quantitropa >= 1) {
            printf("VITÓRIA DO ATAQUE! O defensor perdeu 1 tropa.\n");
        } else {
            strcpy(defensor->cor, atacante->cor);
            printf("CONQUISTA! O Território %s foi dominado pelo Exército %s.\n",
                   defensor->nome, defensor->cor);
        }
    } else {
        printf("VITÓRIA DA DEFESA! O atacante perdeu 1 tropa.\n");
        atacante->quantitropa--;
        if (atacante->quantitropa < 0) atacante->quantitropa = 0;
    }
}

// Função para liberar memória
void liberarMemoria(struct Territorio *mapa) {
    free(mapa);
    printf("\nMemória liberada com sucesso!\n");
}

// Função principal
int main() {
    srand(time(NULL));

    struct Territorio *territorios = NULL;
    int total = 0;
    int opcao;

    do {
        printf("\n====================\n");
        printf("   -> JOGO WAR <-\n");
        printf("====================\n");
        printf("1 - Inserir Territórios\n");
        printf("2 - Listar Territórios\n");
        printf("3 - Atacar\n");
        printf("0 - Sair do Jogo\n");
        printf("====================\n");
        printf("Escolha uma Opção: ");
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao) {
            case 1:
                if (territorios != NULL) {
                    printf("Os territórios já foram alocados!\n");
                } else {
                    printf("Quantos territórios deseja criar? ");
                    scanf("%d", &total);
                    limparBufferEntrada();

                    territorios = (struct Territorio*) malloc(total * sizeof(struct Territorio));
                    if (territorios == NULL) {
                        printf("Erro ao alocar memória!\n");
                        return 1;
                    }

                    printf("Memória alocada para %d territórios!\n", total);

                    for (int i = 0; i < total; i++) {
                        printf("\n--- Cadastro do Território %d ---\n", i + 1);

                        printf("Nome: ");
                        fgets(territorios[i].nome, 30, stdin);
                        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';

                        printf("Cor do Exército: ");
                        fgets(territorios[i].cor, 10, stdin);
                        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0';

                        printf("Tropas: ");
                        scanf("%d", &territorios[i].quantitropa);
                        limparBufferEntrada();
                    }
                }
                break;

            case 2:
                listarTerritorios(territorios, total);
                break;

            case 3:
                if (territorios == NULL || total < 2) {
                    printf("\nCadastre ao menos 2 territórios para atacar!\n");
                    break;
                }

                listarTerritorios(territorios, total);
                int iAtacante, iDefensor;

                printf("\n--- FASE DE ATAQUE ---\n");
                printf("\nEscolha o número do território atacante: " );
                scanf("%d", &iAtacante);

                printf("Escolha o número do território defensor: " );
                scanf("%d", &iDefensor);
                limparBufferEntrada();

                if (iAtacante < 1 || iAtacante > total || iDefensor < 1 || iDefensor > total) {
                    printf("\nEscolha inválida!\n");
                    break;
                }

                atacar(&territorios[iAtacante - 1], &territorios[iDefensor - 1]);
                listarTerritorios(territorios, total);
                break;

            case 0:
                printf("\nSaindo do jogo...\n");
                break;

            default:
                printf("\nOpção inválida, tente novamente!\n");
        }

    } while (opcao != 0);

    liberarMemoria(territorios);
    return 0;
}
