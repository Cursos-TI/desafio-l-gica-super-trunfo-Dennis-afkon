#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char estado;
    char codigo[4];
    char cidade[100];
    unsigned long int populacao;
    float area;
    float pib;
    int pontosTuristicos;
    float densidade_populacional;
    float pib_per_capita;
    float super_poder;
} Carta;

void limparEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

float calcularSuperPoder(Carta c) {
    float densidade = c.densidade_populacional > 0 ? (1.0f / c.densidade_populacional) : 0;
    return (float)c.populacao + c.area + c.pib + (float)c.pontosTuristicos + c.pib_per_capita + densidade;
}

void cadastrarCarta(Carta *carta) {
    printf("Estado (A-H): ");
    scanf(" %c", &carta->estado);
    limparEntrada();

    printf("Código (ex: A01): ");
    fgets(carta->codigo, sizeof(carta->codigo), stdin);
    carta->codigo[strcspn(carta->codigo, "\n")] = '\0';

    printf("Nome da Cidade: ");
    fgets(carta->cidade, sizeof(carta->cidade), stdin);
    carta->cidade[strcspn(carta->cidade, "\n")] = '\0';

    printf("População: ");
    scanf("%lu", &carta->populacao);

    printf("Área (em km²): ");
    scanf("%f", &carta->area);

    printf("PIB (em bilhões de reais): ");
    scanf("%f", &carta->pib);

    printf("Número de Pontos Turísticos: ");
    scanf("%d", &carta->pontosTuristicos);
    limparEntrada();

    carta->densidade_populacional = carta->area > 0 ? carta->populacao / carta->area : 0;
    carta->pib_per_capita = carta->populacao > 0 ? (carta->pib * 1000000000) / carta->populacao : 0;
    carta->super_poder = calcularSuperPoder(*carta);
}

int main() {
    Carta carta1, carta2;
    printf("Cadastro da Carta 1:\n");
    cadastrarCarta(&carta1);

    printf("\nCadastro da Carta 2:\n");
    cadastrarCarta(&carta2);

    int opcao, atributo1, atributo2;

    do {
        printf("\n🔍 MENU DE COMPARAÇÃO:\n");
        printf("1. Comparar um atributo\n");
        printf("2. Comparar dois atributos\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("\nAtributos disponíveis:\n");
                printf("1. População\n2. Área\n3. PIB\n4. Pontos Turísticos\n5. Densidade Populacional\n6. PIB per Capita\n7. Super Poder\n");
                printf("Escolha o atributo para comparar: ");
                scanf("%d", &atributo1);

                switch (atributo1) {
                    case 1:
                        printf("População: %s\n", carta1.populacao > carta2.populacao ? "Carta 1 venceu" :
                                                        carta2.populacao > carta1.populacao ? "Carta 2 venceu" : "Empate");
                        break;
                    case 2:
                        printf("Área: %s\n", carta1.area > carta2.area ? "Carta 1 venceu" :
                                                    carta2.area > carta1.area ? "Carta 2 venceu" : "Empate");
                        break;
                    case 3:
                        printf("PIB: %s\n", carta1.pib > carta2.pib ? "Carta 1 venceu" :
                                                  carta2.pib > carta1.pib ? "Carta 2 venceu" : "Empate");
                        break;
                    case 4:
                        printf("Pontos Turísticos: %s\n", carta1.pontosTuristicos > carta2.pontosTuristicos ? "Carta 1 venceu" :
                                                                  carta2.pontosTuristicos > carta1.pontosTuristicos ? "Carta 2 venceu" : "Empate");
                        break;
                    case 5:
                        printf("Densidade Populacional: %s\n", carta1.densidade_populacional < carta2.densidade_populacional ? "Carta 1 venceu" :
                                                                      carta2.densidade_populacional < carta1.densidade_populacional ? "Carta 2 venceu" : "Empate");
                        break;
                    case 6:
                        printf("PIB per Capita: %s\n", carta1.pib_per_capita > carta2.pib_per_capita ? "Carta 1 venceu" :
                                                              carta2.pib_per_capita > carta1.pib_per_capita ? "Carta 2 venceu" : "Empate");
                        break;
                    case 7:
                        printf("Super Poder: %s\n", carta1.super_poder > carta2.super_poder ? "Carta 1 venceu" :
                                                           carta2.super_poder > carta1.super_poder ? "Carta 2 venceu" : "Empate");
                        break;
                    default:
                        printf("Atributo inválido.\n");
                }
                break;

            case 2:
                printf("\nEscolha o primeiro atributo (1 a 7): ");
                scanf("%d", &atributo1);
                printf("Escolha o segundo atributo (1 a 7): ");
                scanf("%d", &atributo2);

                int pontos1 = 0, pontos2 = 0;

                for (int i = 0; i < 2; i++) {
                    int attr = (i == 0) ? atributo1 : atributo2;
                    switch (attr) {
                        case 1: pontos1 += carta1.populacao > carta2.populacao;
                                pontos2 += carta2.populacao > carta1.populacao;
                                break;
                        case 2: pontos1 += carta1.area > carta2.area;
                                pontos2 += carta2.area > carta1.area;
                                break;
                        case 3: pontos1 += carta1.pib > carta2.pib;
                                pontos2 += carta2.pib > carta1.pib;
                                break;
                        case 4: pontos1 += carta1.pontosTuristicos > carta2.pontosTuristicos;
                                pontos2 += carta2.pontosTuristicos > carta1.pontosTuristicos;
                                break;
                        case 5: pontos1 += carta1.densidade_populacional < carta2.densidade_populacional;
                                pontos2 += carta2.densidade_populacional < carta1.densidade_populacional;
                                break;
                        case 6: pontos1 += carta1.pib_per_capita > carta2.pib_per_capita;
                                pontos2 += carta2.pib_per_capita > carta1.pib_per_capita;
                                break;
                        case 7: pontos1 += carta1.super_poder > carta2.super_poder;
                                pontos2 += carta2.super_poder > carta1.super_poder;
                                break;
                        default: printf("Atributo inválido.\n");
                    }
                }

                if (pontos1 > pontos2)
                    printf("🏆 Carta 1 venceu na comparação de dois atributos!\n");
                else if (pontos2 > pontos1)
                    printf("🏆 Carta 2 venceu na comparação de dois atributos!\n");
                else
                    printf("🤝 Empate na comparação de dois atributos.\n");

                break;

            case 0:
                printf("Encerrando o programa...\n");
                break;

            default:
                printf("Opção inválida.\n");
        }

    } while (opcao != 0);

    return 0;
}