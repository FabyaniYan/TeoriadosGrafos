/* 
 * REPRESENTACAO DE GRAFOS - Versao 2026-2
 */

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<memory.h>


/* 
 * Estrutura de dados para representar grafos
 */
typedef struct aresta{ /* Celula de uma lista de arestas */
	int outroExtremo;
	struct aresta *prox;
}Aresta;

typedef struct vertice{  /* Cada vertice tem um ponteiro para uma lista de arestas incidentes nele */
	int nome;
	Aresta *a;
}Vertice;


/*
 * Declaracoes das funcoes para manipulacao de grafos 
 */
void criarGrafo(Vertice **G, int ordem);
void destruirGrafo(Vertice **G, int ordem);
int acrescentarAresta(Vertice G[], int ordem, int v1, int v2);
void imprimirGrafo(Vertice G[], int ordem);


/*
 * Funcao acrescentada para o projeto, que verifica se existem pessoas que nao possuem nenhum contato com outras pessoas cadastradas na rede.
 */
void pessoasSemContato(Vertice G[], int ordem);


/*
 * Criacao de um grafo com ordem predefinida (passada como argumento),
 * e, inicialmente, sem nenhuma aresta 
 */
void criarGrafo(Vertice **G, int ordem){
	int i;

	*G = (Vertice*) malloc(sizeof(Vertice) * ordem);

	for(i = 0; i < ordem; i++){
		(*G)[i].nome = i;
		(*G)[i].a = NULL;
	}
}


/*
 * Desaloca a memoria dinamica usada para armazenar um grafo.
 */
void destruirGrafo(Vertice **G, int ordem){
	int i;
	Aresta *p, *n;

	for(i = 0; i < ordem; i++){
		p = (*G)[i].a;

		while(p != NULL){
			n = p->prox;
			free(p);
			p = n;
		}
	}

	free(*G);
}


/*  
 * Acrescenta uma nova aresta em um grafo previamente criado.
 * Devem ser passados os extremos v1 e v2 da aresta a ser acrescentada.
 *
 * Como o grafo nao e orientado, para uma aresta com extremos i e j,
 * quando i != j, serao criadas na estrutura as arestas (i,j) e (j,i).
 */
int acrescentarAresta(Vertice G[], int ordem, int v1, int v2){
	Aresta *A1, *A2;

	if(v1 < 0 || v1 >= ordem)
		return 0;

	if(v2 < 0 || v2 >= ordem)
		return 0;

	/* acrescenta aresta na lista do vertice v1 */
	A1 = (Aresta*) malloc(sizeof(Aresta));

	A1->outroExtremo = v2;
	A1->prox = G[v1].a;
	G[v1].a = A1;

	/* se for um laco */
	if(v1 == v2)
		return 1;

	/* acrescenta aresta na lista do vertice v2 */
	A2 = (Aresta*) malloc(sizeof(Aresta));

	A2->outroExtremo = v1;
	A2->prox = G[v2].a;
	G[v2].a = A2;

	return 1;
}


/*  
 * Imprime um grafo com uma notacao similar a uma lista de adjacencia.
 */
void imprimirGrafo(Vertice G[], int ordem){
	int i;
	Aresta *aux;

	printf("\nOrdem: %d", ordem);
	printf("\nLista de Adjacencia:\n");

	for(i = 0; i < ordem; i++){

		printf("\n    v%d: ", i);

		aux = G[i].a;

		for(; aux != NULL; aux = aux->prox){
			printf("  v%d", aux->outroExtremo);
		}
	}

	printf("\n\n");
}


/*
 * Funcao acrescentada para o projeto, que verifica se existem pessoas que nao possuem nenhum contato com outras pessoas cadastradas na rede.
 */
void pessoasSemContato(Vertice G[], int ordem){
	int i;
	int encontrou = 0;

	printf("\nPessoas sem nenhum contato na rede:\n");

	for(i = 0; i < ordem; i++){

		/*
		 * Se o ponteiro da lista de arestas for NULL,
		 * o vertice nao possui nenhuma aresta incidente.
		 */
		if(G[i].a == NULL){

			printf("Pessoa %d\n", G[i].nome);

			encontrou = 1;
		}
	}

	/*
	 * Caso todos os vertices possuam pelo menos
	 * um contato.
	 */
	if(encontrou == 0){
		printf("Nao existem pessoas sem contato na rede.\n");
	}

	printf("\n");
}


/*
 * Programa simples para testar a representacao de grafo
 */
int main(int argc, char *argv[]) {

	Vertice *G;

	int ordemG = 8; /* vertices identificados de 0 ate 7 */

	criarGrafo(&G, ordemG);


	acrescentarAresta(G, ordemG, 0, 1);

	acrescentarAresta(G, ordemG, 0, 2);

	acrescentarAresta(G, ordemG, 0, 7);

	acrescentarAresta(G, ordemG, 2, 4);

	acrescentarAresta(G, ordemG, 2, 5);

	acrescentarAresta(G, ordemG, 2, 5);

	acrescentarAresta(G, ordemG, 3, 5);

	acrescentarAresta(G, ordemG, 4, 6);

	acrescentarAresta(G, ordemG, 3, 6);

	acrescentarAresta(G, ordemG, 7, 7);


	/*
	 * Exibe o grafo
	 */
	imprimirGrafo(G, ordemG);


	/*
	 * verifica pessoas que nao possuem nenhum contato
	 */
	pessoasSemContato(G, ordemG);


	destruirGrafo(&G, ordemG);


	printf("Pressione uma tecla para terminar\n");

	getchar();

	return 0;
}
