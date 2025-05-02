// Aqui nessas 3 linhas estou introduzindo as bibliotecas necessarias para fazer o jogo de batalha naval
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// Estou definindo as constates para que sejam apenas um caractere, sera necessario para criar o tabuleiro, mascara e imprimir  a cada acerto!
#define MAX 30 // Sera importante para saber se ha um espaço livre no tabuleiro ou que os elementos nao se sobreponham ou que estejam fora do tabuleiro
#define AGUA '0'
#define MINA 'M'
#define NAVIO 'N'
#define SUBMARINO 'S'
#define REVELADO 'X'

// Função para criar o tabuleiro inicial visível ao jogador (todo 'X')
void criarTabuleiroVisivel(int tamanho_tabuleiro, char tabuleiro_visivel[tamanho_tabuleiro][tamanho_tabuleiro]) {
    for (int i = 0; i < tamanho_tabuleiro; i++) { // Utilizando o For para criar um vetor linha
        for (int j = 0; j < tamanho_tabuleiro; j++) { // Utilizando o for para criar um vetor coluna, um laço dentro de outro igual bidimensional
            tabuleiro_visivel[i][j] = 'X'; // Aqui minha matriz é minha matriz que sera 'X' cada posição
        }
    }
}

// Outra função para criar o tabuleiro, porem, aqui estou imprimindo o tabuleiro e utiliza a mesma tecnica de criação da função anterior
void imprimirTabuleiro(int tamanho_tabuleiro, char tabuleiro[tamanho_tabuleiro][tamanho_tabuleiro]) {
    printf("\nTabuleiro:\n");
    for (int i = 0; i < tamanho_tabuleiro; i++) {
        for (int j = 0; j < tamanho_tabuleiro; j++) {
            printf(" %c ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Nessa função estou criando uma mascara, no caso outro tabuleiro para que os elementos sejam posicionados (não é visivel para o jogador)
void criarMascaraTabuleiro(int tamanho_tabuleiro, char mascara[tamanho_tabuleiro][tamanho_tabuleiro]) {
    for (int i = 0; i < tamanho_tabuleiro; i++) {
        for (int j = 0; j < tamanho_tabuleiro; j++) {
            mascara[i][j] = AGUA; // Inicializa com água
        }
    }
}

// Nessa função é para verificar se o local está livre
int verificarPosicaoLivre(int x, int y, int tamanho, char mascara[MAX][MAX], int direcao) {
    if (direcao == 0) { // Horizontal
        if (y + tamanho > MAX) return 0; // Se ultrapassar a borda
        for (int i = 0; i < tamanho; i++) {
            if (mascara[x][y + i] != AGUA) return 0; // Verifica se já tem algo na posição
        }
    } else { // Vertical
        if (x + tamanho > MAX) return 0; // Se ultrapassar a borda
        for (int i = 0; i < tamanho; i++) {
            if (mascara[x + i][y] != AGUA) return 0; // Verifica se já tem algo na posição
        }
    }
    return 1; // Posição livre
}

// Funçao para posicionar os elementos de acordo com a dificuldade
void posicionarElementos(int tamanho_tabuleiro, char mascara[tamanho_tabuleiro][tamanho_tabuleiro], int num_minas, int num_navios, int num_submarinos, int num_ng){
    // O sufixo num_''algumacoisa'' é o limite superior que sera recebido pela quantidade de elementos dependendo da dificuldade, declarada na main
    srand(time(NULL));  // Semente para gerar aleatoriamente os elementos

    int m = 0; // contador para as minas
     int n2 = 0; // contador para o navio (2x1)
     int ng4 = 0; // contador para o navio (4x1)
     int  s = 0; // contador para o submarino

     // No proximo é o loop (While), so lembrando que Eixo x = Horizontal, y = Eixo Vertical
     int direcao_horizontal = 0; // Define a direção horizontal

    // Posicionando as Minas
    while (m < num_minas) {
        int x = rand() % tamanho_tabuleiro;
        int y = rand() % tamanho_tabuleiro;
        if (mascara[x][y] == AGUA) {
            mascara[x][y] = MINA;
            m++;
        }
    }

    // Posicionando os Navios (2x1) - SEMPRE HORIZONTAL
    while (n2 < num_navios) {
        int x = rand() % tamanho_tabuleiro;
        int y = rand() % tamanho_tabuleiro;
        if (verificarPosicaoLivre(x, y, 2, mascara, direcao_horizontal)) { // Verifica se a posição está livre na horizontal
            for (int i = 0; i < 2; i++) {
                mascara[x][y + i] = NAVIO; 
            }
            n2++;
        }
    }

    // Posicionando os Navios Grandes (4x1) - SEMPRE HORIZONTAL
    while (ng4 < num_ng) {
        int x = rand() % tamanho_tabuleiro;
        int y = rand() % tamanho_tabuleiro;
        if (verificarPosicaoLivre(x, y, 4, mascara, direcao_horizontal)) { // Verifica se a posição está livre na horizontal
            for (int i = 0; i < 4; i++) {
                mascara[x][y + i] = NAVIO;
            }
            ng4++;
        }
    }

    // Posicionando os Submarinos (3x1 vertical) - SEMPRE VERTICAL
    while (s < num_submarinos) {
        int x = rand() % tamanho_tabuleiro;
        int y = rand() % tamanho_tabuleiro;
        if (verificarPosicaoLivre(x, y, 3, mascara, 1)) { // Sempre vertical para o submarino
            for (int i = 0; i < 3; i++) {
                mascara[x + i][y] = SUBMARINO;
            }
            s++;
        }
    }
}

// Essa função é para impirmir a mascara(gabarito) que sera definida no inicio da partida, eu fiz para ter certeza que os elementos estavam sendo posicionados certos
void imprimirMascara(int tamanho_tabuleiro, char mascara[tamanho_tabuleiro][tamanho_tabuleiro], int gabarito) {
    if (gabarito == 1) {
        printf("\nGabarito do Tabuleiro:\n");
        for (int i = 0; i < tamanho_tabuleiro; i++) {
            for (int j = 0; j < tamanho_tabuleiro; j++) {
                printf("%c ", mascara[i][j]);
            }
            printf("\n");
        }
    }
}

//função para fazer o jogo rodar
void jogar(int tamanho_tabuleiro, char mascara[tamanho_tabuleiro][tamanho_tabuleiro], char tabuleiro_visivel[tamanho_tabuleiro][tamanho_tabuleiro]) {
    int x, y;
    char virgula; // Para ler a vírgula

    printf("\nDigite a coordenada no formato x,y: ");
    if (scanf("%d%c%d", &x, &virgula, &y) == 3 && virgula == ',') { // Aqui é o laço para as jogadas, preferi que seja no estilo x,y 
        if (x >= 0 && x < tamanho_tabuleiro && y >= 0 && y < tamanho_tabuleiro) {
            if(mascara[x][y] == MINA) {
                printf("Você acertou uma Mina!\n");
                tabuleiro_visivel[x][y] = MINA; // Revela a mina
                mascara[x][y] = REVELADO;      // Marca na máscara como revelado
            }
            else if(mascara[x][y] == NAVIO) {
                printf("Você acertou um navio! \n");
                tabuleiro_visivel[x][y] = NAVIO; // Revela o navio
                mascara[x][y] = REVELADO;       // Marca na máscara como revelado
            }
            else if(mascara[x][y] == SUBMARINO) {
                printf("Você acertou um Submarino!\n");
                tabuleiro_visivel[x][y] = SUBMARINO; // Revela o submarino
                mascara[x][y] = REVELADO;         // Marca na máscara como revelado
            }
            else if(mascara[x][y] == AGUA) {
                printf("Você acertou a ÁGUA!\n");
                tabuleiro_visivel[x][y] = AGUA; // Revela a água
                mascara[x][y] = REVELADO;      // Marca na máscara como revelado
            }
        } else{
            printf("Coordenada inválida! Certifique-se de que x e y estão dentro dos limites do tabuleiro (0-%d).\n", tamanho_tabuleiro - 1);
            while (getchar() != '\n');
        }
    }
    else{
        printf("Formato de coordenada inválido. Use o formato x,y.\n");
        while(getchar() != '\n'); // digitar apenas um caractere
    }
    while(getchar() != '\n');
}

int continuarJogo() {
    int opcao;
    printf("\nDeseja continuar jogando?\n1 - Sim\n2 - Não\n");
    scanf("%d", &opcao);
    getchar(); // Limpa o buffer do teclado
    return opcao;
}

int main() {
    int tamanho_tabuleiro;
    int num_minas;
    int num_navios;
    int num_submarinos;
    int num_ng;
    int gabarito;
    int continuar_jogando = 1;

    printf("Deseja imprimir o gabarito com a partida?\n1 - SIM\n2 - NÃO\n"); //Imprimir o gabarito como eu defini na funcao criada imprimirMascara
    scanf("%d", &gabarito);
    getchar(); // Limpa o buffer do teclado

    printf("Escolha a Dificuldade:\n1 - Facil\n2 - Medio\n3 - Dificil\n");
    scanf("%d", &tamanho_tabuleiro);
    getchar(); // Limpa o buffer do teclado


    // Aqui são os laços para definir a dificuldade
    if (tamanho_tabuleiro == 1) {
        tamanho_tabuleiro = 10;
        num_minas = 1;
        num_navios = 1;
        num_submarinos = 1;
        num_ng = 0;
    } else if (tamanho_tabuleiro == 2) {
        tamanho_tabuleiro = 20;
        num_minas = 2;
        num_navios = 2;
        num_submarinos = 1;
        num_ng = 0;
    } else if (tamanho_tabuleiro == 3) {
        tamanho_tabuleiro = 30;
        num_minas = 3;
        num_navios = 2;
        num_submarinos = 3;
        num_ng = 1;
    } else {
        printf("Opção inválida. Definindo tamanho padrão 10 (Fácil).\n"); //Aqui se o usuario digitar um valor invalido, retorna para a dificuldade facil
        tamanho_tabuleiro = 10;
        num_minas = 1;
        num_navios = 1;
        num_submarinos = 1;
        num_ng = 0;
    }

    printf("\nTamanho do tabuleiro: %d x %d\n", tamanho_tabuleiro, tamanho_tabuleiro);
    printf("Minas: %d, Navios (2x1): %d, Submarinos (3x1): %d, Navios Grandes (4x1): %d\n\n", num_minas, num_navios, num_submarinos, num_ng);

    char mascara[tamanho_tabuleiro][tamanho_tabuleiro];
    criarMascaraTabuleiro(tamanho_tabuleiro, mascara);
    posicionarElementos(tamanho_tabuleiro, mascara, num_minas, num_navios, num_submarinos, num_ng);
    imprimirMascara(tamanho_tabuleiro, mascara, gabarito);

    char tabuleiro_visivel[tamanho_tabuleiro][tamanho_tabuleiro];
    criarTabuleiroVisivel(tamanho_tabuleiro, tabuleiro_visivel);
    imprimirTabuleiro(tamanho_tabuleiro, tabuleiro_visivel); // Imprime o tabuleiro inicial

    do{ //Aqui nesse loop bati muita cabeça, precisava fazer com que sempre voltasse para opção jogar, passei 1 hora tentando resolver, não consegui entao usei o chatGPT para ajudar. 
        // queria ter feito um loop dentro da propria função jogar, porem, estava sempre imprimindo infinitamente o printf entao tive que criar uma função auxiliar
        jogar(tamanho_tabuleiro, mascara, tabuleiro_visivel);
        imprimirTabuleiro(tamanho_tabuleiro, tabuleiro_visivel); // Imprime o tabuleiro atualizado
        int opcao_continuar = continuarJogo();
        if (opcao_continuar == 2) {
            continuar_jogando = 0;
        }
        int elementos_restantes = 0;
        for(int i = 0; i < tamanho_tabuleiro; i++) {
            for(int j = 0; j < tamanho_tabuleiro; j++) {
                if (mascara[i][j] == MINA || mascara[i][j] == NAVIO || mascara[i][j] == SUBMARINO) {
                    elementos_restantes++;
                }
            }
        }
        if(elementos_restantes == 0) {
            printf("\nParabéns! Você encontrou todos os elementos! 🎉\n");
            continuar_jogando = 0;
        }

    }
    while(continuar_jogando == 1);

    printf("\nFim de Jogo!\n");
    return 0;
}