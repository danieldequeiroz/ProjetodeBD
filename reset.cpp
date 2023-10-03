#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <limits>
using namespace std;

// Definição da struct Produto
struct Produto {
    int value;
    int index;
};

struct LinhaProducao {
    vector<Produto> ListaProdutos;
    int tempo_total = 0;
};

// Predicado para comparar dois Produto pelo valor
bool compareByValue(const Produto& e1, const Produto& e2) {
    return e1.value < e2.value;
}

// Função de reset
void reset(vector<Produto>& lista_produtos, vector<LinhaProducao>& lista_producao, LinhaProducao& melhor_linha, const int matriz_troca_tempo[][6]) {
    // Reinicialize a lista de produtos
    int arr[] = {5, 4, 3, 2, 3, 3};
    int size = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < size; i++) {
        Produto produto;
        produto.value = arr[i];
        produto.index = i;
        lista_produtos[i] = produto;
    }


// Função de swap para trocar dois elementos do vetor
void swapProdutos(vector<Produto>& lista, int index1, int index2) {
    swap(lista[index1], lista[index2]);
}

// Função para calcular o tempo total de uma linha de produção
int calcularTempoTotal(const vector<Produto>& linha, const int matriz_troca_tempo[][6]) {
    int tempo_total = 0;
    int produto_anterior = -1;

    for (const Produto& produto : linha) {
        if (produto_anterior != -1) {
            tempo_total += matriz_troca_tempo[produto_anterior][produto.index];
        }
        tempo_total += produto.value;
        produto_anterior = produto.index;
    }

    return tempo_total;
}

// Função de reset para LinhaProducao e ListaProdutos
void reset(LinhaProducao& linha_producao, vector<Produto>& lista_produtos, const int arr[], const int size, const int matriz_troca_tempo[][6]) {
    linha_producao.ListaProdutos.clear();
    lista_produtos.clear();
    for (int i = 0; i < size; i++) {
        Produto produto;
        produto.value = arr[i];
        produto.index = i;
        lista_produtos.push_back(produto);
    }
    sort(lista_produtos.begin(), lista_produtos.end(), compareByValue);
    linha_producao.ListaProdutos = lista_produtos;
    linha_producao.tempo_total = calcularTempoTotal(lista_produtos, matriz_troca_tempo);
}


// Função para realizar a busca local
LinhaProducao buscaLocal(const LinhaProducao& linha_producao, const int matriz_troca_tempo[][6]) {
    LinhaProducao melhor_linha = linha_producao;
    bool melhoria = true;

    while (melhoria) {
        melhoria = false;

        vector<Produto>& produtos = melhor_linha.ListaProdutos;
        const int tempo_atual = melhor_linha.tempo_total;
        const int numero_de_produtos = produtos.size();

        for (int i = 0; i < numero_de_produtos - 1; i++) {
            for (int j = i + 1; j < numero_de_produtos; j++) {
                swapProdutos(produtos, i, j);
                const int novo_tempo = calcularTempoTotal(produtos, matriz_troca_tempo);

                if (novo_tempo < tempo_atual) {
                    melhor_linha.tempo_total = novo_tempo;
                    melhoria = true;
                } else {
                    // Desfazer a troca
                    swapProdutos(produtos, i, j);
                }
            }
        }
    }

    return melhor_linha;
}

  // Reinicialize a lista de produtos
    int arr[] = {5, 4, 3, 2, 3, 3};
    int size = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < size; i++) {
        Produto produto;
        produto.value = arr[i];
        produto.index = i;
        lista_produtos[i] = produto;
    }

    // Reordene a lista de produtos
    sort(lista_produtos.begin(), lista_produtos.end(), compareByValue);

    // Reinicialize a lista de produção e a melhor linha
    for (int i = 0; i < lista_producao.size(); i++) {
        lista_producao[i].ListaProdutos = lista_produtos;
        lista_producao[i].tempo_total = calcularTempoTotal(lista_produtos, matriz_troca_tempo);
    }
    melhor_linha = lista_producao[0];
}

for (int i = 0; i < maxIterations; i++) {
    reset(melhor_linha, lista_produtos, arr, size, matriz_troca_tempo);

// Função principal da ILS com reset
LinhaProducao ILS(int maxIterations, const int matriz_troca_tempo[][6], int resetIterations) {
// Função para realizar a perturbação na linha de produção
LinhaProducao perturbarLinha(const LinhaProducao& linha_producao, const int matriz_troca_tempo[][6]) {
    LinhaProducao linha_perturbada = linha_producao;
    vector<Produto>& produtos = linha_perturbada.ListaProdutos;
    const int numero_de_produtos = produtos.size();

    // Realizar uma perturbação simples invertendo a ordem dos produtos
    reverse(produtos.begin(), produtos.end());

    linha_perturbada.tempo_total = calcularTempoTotal(produtos, matriz_troca_tempo);

    return linha_perturbada;
}

for (int i = 0; i < maxIterations; i++) {
        // Reset após um certo número de iterações
        if (i != 0 && i % resetIterations == 0) {
            reset(lista_produtos, lista_producao, melhor_linha, matriz_troca_tempo);
        }

// Função principal da ILS
LinhaProducao ILS(int maxIterations, const int matriz_troca_tempo[][6]) {
    int numero_de_linhas = 2;
    int numero_de_produtos = 6;

    // Criando um vetor de structs Produto
    vector<Produto> lista_produtos;
    lista_produtos.reserve(numero_de_produtos);

    // Preenchendo o vetor de structs com os valores e índices correspondentes
    int arr[] = {5, 4, 3, 2, 3, 3};
    int size = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < size; i++) {
        Produto produto;
        produto.value = arr[i];
        produto.index = i;
        lista_produtos.push_back(produto);
    }


    // Ordenando o vetor de structs com base no valor usando o predicado compareByValue
    sort(lista_produtos.begin(), lista_produtos.end(), compareByValue);

    // Criando um vetor de LinhaProducao
    vector<LinhaProducao> lista_producao;
    lista_producao.reserve(numero_de_linhas);

    // Preenchendo o vetor de LinhaProducao com os produtos
    for (int i = 0; i < numero_de_linhas; i++) {
        LinhaProducao linha_producao;
        linha_producao.ListaProdutos = lista_produtos;
        linha_producao.tempo_total = calcularTempoTotal(lista_produtos, matriz_troca_tempo);
        lista_producao.push_back(linha_producao);
    }

    LinhaProducao melhor_linha = lista_producao[0];

    for (int i = 0; i < maxIterations; i++) {
        LinhaProducao linha_perturbada = perturbarLinha(melhor_linha, matriz_troca_tempo);
        LinhaProducao linha_busca_local = buscaLocal(linha_perturbada, matriz_troca_tempo);

        if (linha_busca_local.tempo_total < melhor_linha.tempo_total) {
            melhor_linha = linha_busca_local;
        }
    }

    return melhor_linha;
}

int main() {
    int maxIterations = 100; // Definir o número máximo de iterações
     int resetIterations = 50;  // Reiniciar após 50 iterações
    int matriz_troca_tempo[6][6] = {
        {0, 1, 2, 3, 2, 2},
        {10, 0, 5, 13, 7, 12},
        {7, 1, 0, 10, 4, 4},
        {1, 3, 1, 0, 3, 2},
        {9, 11, 2, 3, 0, 8},
        {1, 7, 3, 5, 1, 0}
    };

    LinhaProducao melhor_linha = ILS(maxIterations, matriz_troca_tempo,  resetIterations);

    // Imprimir a melhor linha de produção encontrada
    cout << "Melhor linha de producao: " << endl;
    for (const Produto& produto : melhor_linha.ListaProdutos) {
        cout << "Value: " << produto.value << ", Index: " << produto.index << endl;
    }

    cout << "Tempo total da linha: " << melhor_linha.tempo_total << endl;

    return 0;
}