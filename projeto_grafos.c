/*
 * PROJETO DE PROGRAMACAO - GRUPO SOCIAL (PARTE 1)
 * Teoria dos Grafos - 2026-2
 * Prof. Roberto C. de Araujo
 *
 * Integrantes:
 *   Bruna Amorim Maia            - RA: 10431883
 *   Fabyani Tiva Yan             - RA: 10431835
 *   Rafael Araujo Cabral Moreira - RA: 10441919
 *
 * Descricao: modelagem da rede de contatos de 15 moradores de um
 * condominio residencial por meio de um grafo nao orientado.
 * Cada vertice representa um morador e cada aresta representa um
 * contato direto (e reciproco) entre dois moradores.
 *
 * Base: implementacao de grafos Grafo_2026-2.c fornecida na disciplina.
 */

 
/*
 * REPRESENTACAO DE GRAFOS
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
 * Declaracoes das funcoes acrescentadas para o projeto (Pessoa 2)
 */
int contarContatos(Vertice G[], int v);
void pessoasComUmContato(Vertice G[], int ordem);
void pessoasComMaisContatos(Vertice G[], int ordem);

/*
 * Declaracao da funcao acrescentada para o projeto (Pessoa 3)
 */
void gruposIsolados(Vertice G[], int ordem);


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
 * Funcao auxiliar para contar o numero de contatos (grau) de um vertice
 */
int contarContatos(Vertice G[], int v) {
	int count = 0;
	Aresta *aux = G[v].a;
	while(aux != NULL) {
		count++;
		aux = aux->prox;
	}
	return count;
}

/*
 * Funcao para encontrar pessoas com exatamente 1 contato
 */
void pessoasComUmContato(Vertice G[], int ordem) {
	int i, count;
	int encontrou = 0;

	printf("\nMoradores com exatamente um contato na rede:\n");

	for(i = 0; i < ordem; i++) {
		count = contarContatos(G, i);
		if(count == 1) {
			printf("%s\n", G[i].nomePessoa);
			encontrou = 1;
		}
	}

	if(encontrou == 0) {
		printf("Nao existem moradores com exatamente um contato.\n");
	}
	printf("\n");
}

/*
 * Funcao para encontrar quem possui mais contatos na rede
 */
void pessoasComMaisContatos(Vertice G[], int ordem) {
	int i, count;
	int max = -1;

	/* Primeiro passo: descobre qual e o numero maximo de contatos */
	for(i = 0; i < ordem; i++) {
		count = contarContatos(G, i);
		if(count > max) {
			max = count;
		}
	}

	printf("\nMorador(es) com mais contatos na rede (%d contatos):\n", max);
	if (max == 0) {
		printf("Nenhum morador possui contatos.\n");
		return;
	}

	/* Segundo passo: imprime quem possui essa quantidade maxima de contatos */
	for(i = 0; i < ordem; i++) {
		count = contarContatos(G, i);
		if(count == max) {
			printf("%s\n", G[i].nomePessoa);
		}
	}
	printf("\n");
}


/*
 * Funcao que verifica se existem grupos
 * isolados na rede, isto e, grupos de moradores em que nenhum morador
 * de dentro do grupo tem contato com algum morador de fora do grupo.
 *
 * Cada grupo isolado corresponde a um componente
 * conexo do grafo. Para encontrar os componentes e usada uma busca em
 * largura (BFS):
 *   1. Todos os moradores comecam marcados como "nao visitados" (0).
 *   2. Para cada morador ainda nao visitado, um novo grupo e iniciado:
 *      o morador entra na fila e e marcado com o numero do grupo.
 *   3. Enquanto a fila nao estiver vazia, retira-se um morador da fila
 *      e percorre-se a sua lista de contatos. Cada contato ainda nao
 *      visitado e marcado com o mesmo numero do grupo e entra na fila.
 *   4. Quando a fila esvazia, todos os moradores alcancaveis a partir
 *      do primeiro ja foram marcados, e o grupo esta completo.
 * Ao final, se existir mais de um grupo, a rede possui grupos isolados.
 */
void gruposIsolados(Vertice G[], int ordem){
	int *grupo;   /* grupo[i] = numero do grupo do morador i (0 = nao visitado) */
	int *fila;    /* fila usada na busca em largura */
	int inicio, fim;
	int i, j, v, w;
	int qtdGrupos = 0;
	int tamanho;
	Aresta *aux;

	grupo = (int*) malloc(sizeof(int) * ordem);
	fila  = (int*) malloc(sizeof(int) * ordem);

	if(grupo == NULL || fila == NULL){
		printf("Erro de memoria ao procurar grupos isolados.\n");
		free(grupo);
		free(fila);
		return;
	}

	/* passo 1: ninguem foi visitado ainda */
	for(i = 0; i < ordem; i++)
		grupo[i] = 0;

	/* passos 2 a 4: uma busca em largura para cada grupo novo */
	for(i = 0; i < ordem; i++){

		if(grupo[i] != 0)
			continue; /* morador ja pertence a um grupo encontrado */

		qtdGrupos++;
		inicio = 0;
		fim = 0;

		fila[fim++] = i;
		grupo[i] = qtdGrupos;

		while(inicio < fim){
			v = fila[inicio++];

			for(aux = G[v].a; aux != NULL; aux = aux->prox){
				w = aux->outroExtremo;

				if(grupo[w] == 0){
					grupo[w] = qtdGrupos;
					fila[fim++] = w;
				}
			}
		}
	}

	printf("\nGrupos isolados na rede:\n");

	if(qtdGrupos == 1){
		printf("Nao existem grupos isolados. Todos os moradores estao ligados,\n");
		printf("direta ou indiretamente, em um unico grupo.\n\n");
	}
	else{
		printf("A rede possui %d grupos isolados. Nenhum morador de um grupo\n", qtdGrupos);
		printf("tem contato com moradores de outro grupo.\n\n");

		for(j = 1; j <= qtdGrupos; j++){

			/* conta quantos moradores o grupo j possui */
			tamanho = 0;
			for(i = 0; i < ordem; i++)
				if(grupo[i] == j)
					tamanho++;

			if(tamanho == 1)
				printf("Grupo %d (1 morador, sem contatos): ", j);
			else
				printf("Grupo %d (%d moradores): ", j, tamanho);

			/* exibe os moradores do grupo j */
			for(i = 0; i < ordem; i++)
				if(grupo[i] == j)
					printf("%s  ", G[i].nomePessoa);

			printf("\n");
		}
		printf("\n");
	}

	free(grupo);
	free(fila);
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
	 * Nomes dos moradores
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
	 * Contatos entre os moradores
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
	 * Verifica moradores que nao possuem nenhum contato
	 */
	pessoasSemContato(G, ordemG);

	/*
	 * Verifica moradores que possuem exatamente 1 contato
	 */
	pessoasComUmContato(G, ordemG);

	/*
	 * Verifica moradores com o maior numero de contatos
	 */
	pessoasComMaisContatos(G, ordemG);

	/*
	 * Verifica se existem grupos isolados na rede
	 */
	gruposIsolados(G, ordemG);


	destruirGrafo(&G, ordemG);


	printf("Pressione uma tecla para terminar\n");

	getchar();

	return 0;
}
