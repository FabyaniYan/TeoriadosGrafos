/* 
 * REPRESENTACAO DE GRAFOS - Versao 2026-2
 */

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<memory.h>
#include<string.h>


/* 
 * Estrutura de dados para representar grafos
 */
typedef struct aresta{ /* Celula de uma lista de arestas */
	int outroExtremo;
	struct aresta *prox;
}Aresta;

typedef struct vertice{  /* Cada vertice tem um ponteiro para uma lista de arestas incidentes nele */
	int nome;
	char nomePessoa[50];
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
		(*G)[i].nomePessoa[0] = '\0';
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
 * Imprime os moradores e seus contatos
 */
void imprimirGrafo(Vertice G[], int ordem){
	int i;
	Aresta *aux;

	printf("\nRede de contatos do condominio:\n");

	for(i = 0; i < ordem; i++){

		printf("\n%s: ", G[i].nomePessoa);

		aux = G[i].a;

		if(aux == NULL){
			printf("sem contatos");
		}

		for(; aux != NULL; aux = aux->prox){
			printf("%s  ", G[aux->outroExtremo].nomePessoa);
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

	printf("\nMoradores sem nenhum contato na rede:\n");

	for(i = 0; i < ordem; i++){

		/*
		 * Se a lista de arestas estiver vazia,
		 * o morador nao possui contato com nenhum outro morador.
		 */
		if(G[i].a == NULL){

			printf("%s\n", G[i].nomePessoa);

			encontrou = 1;
		}
	}

	if(encontrou == 0){
		printf("Nao existem moradores sem contato na rede.\n");
	}

	printf("\n");
}


/*
 * Programa para representar a rede social de moradores
 * de um condominio.
 */
int main(int argc, char *argv[]) {

	Vertice *G;

	int ordemG = 15; /* 15 moradores identificados de 0 ate 14 */

	criarGrafo(&G, ordemG);


	/*
	 * nomes dos moradores
	 */
	strcpy(G[0].nomePessoa, "Ana");
	strcpy(G[1].nomePessoa, "Bruno");
	strcpy(G[2].nomePessoa, "Carla");
	strcpy(G[3].nomePessoa, "Daniel");
	strcpy(G[4].nomePessoa, "Eduardo");
	strcpy(G[5].nomePessoa, "Fernanda");
	strcpy(G[6].nomePessoa, "Gabriel");
	strcpy(G[7].nomePessoa, "Helena");
	strcpy(G[8].nomePessoa, "Igor");
	strcpy(G[9].nomePessoa, "Juliana");
	strcpy(G[10].nomePessoa, "Lucas");
	strcpy(G[11].nomePessoa, "Mariana");
	strcpy(G[12].nomePessoa, "Natalia");
	strcpy(G[13].nomePessoa, "Otavio");
	strcpy(G[14].nomePessoa, "Olivia");


	/*
	 * contatos entre os moradores
	 */

	acrescentarAresta(G, ordemG, 0, 1);
	acrescentarAresta(G, ordemG, 0, 2);
	acrescentarAresta(G, ordemG, 0, 3);

	acrescentarAresta(G, ordemG, 1, 2);

	acrescentarAresta(G, ordemG, 2, 3);
	acrescentarAresta(G, ordemG, 2, 4);

	acrescentarAresta(G, ordemG, 3, 4);

	acrescentarAresta(G, ordemG, 5, 6);
	acrescentarAresta(G, ordemG, 5, 7);

	acrescentarAresta(G, ordemG, 6, 7);
	acrescentarAresta(G, ordemG, 6, 8);

	acrescentarAresta(G, ordemG, 7, 8);

	acrescentarAresta(G, ordemG, 9, 10);
	acrescentarAresta(G, ordemG, 10, 11);
	acrescentarAresta(G, ordemG, 11, 12);
	acrescentarAresta(G, ordemG, 12, 13);

	/*
	 * Olivia, vertice 14, nao possui contato
	 */


	/*
	 * Exibe a rede social
	 */
	imprimirGrafo(G, ordemG);


	/*
	 * verifica moradores que nao possuem nenhum contato
	 */
	pessoasSemContato(G, ordemG);


	destruirGrafo(&G, ordemG);


	printf("Pressione uma tecla para terminar\n");

	getchar();

	return 0;
}
