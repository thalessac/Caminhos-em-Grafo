//--------------------------------------------------------------
// NOME : Thales Simão do Amaral Camargo
//--------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>
#include <string.h>

// ######### ESCREVA O NROUSP AQUI
int nroUSP() {
    return 9017082;
}

//-------------------------------------------

// nos das listas de adjacencias
typedef struct adj {
	int v;
	struct adj* prox;
} NO;

// vertices
typedef struct {
	NO* inicio;
	int flag;
} VERTICE;


//---------------------------------------------------------
// FUNÇÕES AUXILIARES PARA FUNÇÃO PRINCIPAL
//---------------------------------------------------------

//Lista ligada para armazenar a solução

typedef struct {
    NO* inicio;
    int tam;
}LISTA;

void inicializarLista(LISTA* l){
    l->inicio = NULL;
    l->tam=0;
}

bool add_node(LISTA* l, int x){
    //Adiciona elemento no final da lista

    NO* novo = (NO*) malloc(sizeof(NO));
    novo->v = x;
    novo->prox = NULL;

    if (l->tam == 0){
        l->inicio = novo;
        l->tam += 1;
        return true;
    }

    NO* ultimo = l->inicio;
    while (ultimo->prox){
        ultimo = ultimo->prox;
    }
    ultimo->prox = novo;
    l->tam += 1;
    return true;

}

bool remove_node(LISTA* l){
    //Remove elemento no final da lista

    if (l->tam == 0) return true;

    NO* ultimo = l->inicio;

    if (l->tam == 1){
        free(ultimo);
        l->inicio = NULL;
        l->tam -= 1;
        return true;
    }

    while (ultimo->prox->prox){
        ultimo = ultimo->prox;
    }
    ultimo->prox = NULL;
    free(ultimo->prox);
    l->tam -= 1;
    return true;
}

void exibirlista(NO* inicio){
    if (inicio != NULL) printf("|");
    while(inicio != NULL){
        printf(" %d |", inicio->v);
        inicio = inicio->prox;
    }
    printf("\n\n");

}

//---------------------------------------------------------
// FUNÇÃO PRINCIPAL
//---------------------------------------------------------
void busca_prof(VERTICE* g, int x, int y, int d, LISTA* aux, LISTA* solution){
    /*
    Função que recebe um grafo, o tamanho do grafo, a posição inicial, posição final e distância máxima d, lista aux e lista solution e cria uma
    lista ligada com todos os caminhos simples existentes entre x e y.
    LISTA* aux ---> armazena um caminho simples encontrado
    LISTA* solution ---> armazena todos os caminhos simples existentes entre x e y.
    */

    //Adiciono a posição atual na lista aux
    add_node(aux, x);

    //Verifico se o critério de parada foi atindigo
    if (x==y && aux->tam - 1 <= d){
        NO* reg_aux = aux->inicio;
        for (int i = 0; i<aux->tam; i++){
            add_node(solution, reg_aux->v);
            reg_aux = reg_aux->prox;
        }
    }

    //Marco a posição atual como visitada
    g[x].flag = 1;

    //Uso chamadas recursivas para repetir a busca na próxima adjacência ainda não visitada
    NO* ad = g[x].inicio;
    while(ad){
        if(g[ad->v].flag == 0){ //Se o vértice não foi examinado
            busca_prof(g, ad->v, y, d, aux, solution);
        }
        ad = ad->prox;
    }

    //Esgotou o caminho, fazer backtracking
    //Desmarcar posição como visitada
    g[x].flag = 0;
    //Remover nó da lista de caminho auxiliar
    remove_node(aux);
}

NO* caminhos_max_d(VERTICE* g, int n, int x, int y, int d){
    /*
    Função que recebe um grafo, o tamanho do grafo, a posição inicial, posição final e distância máxima d e retorna uma
    lista ligada com todos os caminhos simples existentes entre x e y.
    Essa função chama a função de busca em profundidade e apresenta os resultados e assinatura conforme especificações do EP.
    */
    //Validação dos inputs
    if (x>n || x<1 || y>n || y<1) return NULL;

    //Criação das listas aux e solution para armazenar os resultados parcial e final respectivamente
    LISTA* aux = (LISTA*) malloc(sizeof(LISTA));
    inicializarLista(aux);

    LISTA* solution = (LISTA*) malloc(sizeof(LISTA));
    inicializarLista(solution);

    //Chamo o algoritmo de busca em profundidade
    busca_prof(g, x, y, d, aux, solution);

    //Verifica se pelo menos um caminho foi encontrado
    if (solution->tam == 0) return NULL;

    //Retorna a lista ligada solução do EP
    return solution->inicio;
}


//---------------------------------------------------------
// FUNÇÕES PARA CRIAR TESTES
//---------------------------------------------------------

/*Criar vértices do grafo*/
VERTICE *criaGrafo(int N){
    VERTICE* g = (VERTICE*) malloc(sizeof(VERTICE)*(N+1));
    int i;
    for (i=1; i<=N; i++) {
        g[i].inicio = NULL;
        g[i].flag = 0;
    }
    return g;
}

/*Adicionar arestas*/
int criaAresta(VERTICE* g, int vi, int vf, int N){
    if (!g) return(false);
    if ((vf<0 || (vf >= N+1)))
        return(false);
    if ((vi<0 || (vi >= N+1)))
        return(false);
    NO* novo = (NO*) malloc(sizeof(NO));
    novo->prox = g[vi].inicio;
    g[vi].inicio = novo;
    novo -> v = vf;
    return(true);

}

void imprimirGrafo(VERTICE *g, int N) {
    int i;
    for(i=1; i<=N; i++){
        printf("v%d: ",i);
        NO *ad = g[i].inicio;
        while(ad) {
            printf("v%d ", ad->v);
            ad = ad->prox;
        }
        printf("\n");
    }
    printf("\n");
}

//---------------------------------------------------------
// use main() para fazer chamadas de teste ao seu programa
// mas nao entregue o codido de main() nem inclua nada
// abaixo deste ponto
//---------------------------------------------------------
int main()
{
	if (nroUSP()==0) printf("\n\nNro USP nao informado!!!\n\n");

	// crie um grafo de teste aqui
	// chame a funcao caminhos_max_d implementada
	// verifique se a lista retornada está correta

	int N = 17;

    VERTICE * g = criaGrafo(N);

    criaAresta(g,1,5, N);
    criaAresta(g,1,3, N);
    criaAresta(g,2,1, N);
    criaAresta(g,3,8, N);
    criaAresta(g,3,6, N);
    criaAresta(g,5,8, N);
    criaAresta(g,7,2, N);
    criaAresta(g,7,3, N);
    criaAresta(g,8,6, N);
    criaAresta(g,8,11, N);
    criaAresta(g,8,13, N);
    criaAresta(g,9,6, N);
    criaAresta(g,11,13, N);
    criaAresta(g,13,9, N);
    criaAresta(g,13,10, N);
    criaAresta(g,15,14, N);
    criaAresta(g,17,15, N);

    imprimirGrafo(g, N);

    //Testes
    int x = 2;
    int y = 13;
    int d = 5;

    NO* resposta = caminhos_max_d(g, N, x, y, d);

    printf("-------------\nRESULTADO FINAL\n-------------\n");
    if (resposta == NULL) printf("Caminho nao encontrado OU entrada invalida\n");
    else printf("Caminhos encontrados entre vertice %d e %d com ate %d arestas\n", x, y, d);
    exibirlista(resposta);
}

