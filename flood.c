#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


//BOLLEANO usado para marcar nodos como visitados ou nao.


#define TRUE 1
#define FALSE 0

//VARIAVEIS GLOBAIS REFERENTES AO TAMANHO DA MATRIZ E QUANTIDADE DECORES


int NUM_LINHAS = 0;
int NUM_COLUNAS = 0;
int NUM_CORES = 0;


//VETOR DE NODOS  

typedef struct nodo{
	
	int position;
	int color;
	int visited;
	struct nodo *vd;
	struct nodo *vb;
	struct nodo *ve;
	struct nodo *vc;

}*nodo;

//Função que inicializa o grafo e define os valores iniciais
nodo criagrafo(nodo grafo, int dados[]){
	
	//Posição 1,1
	grafo[1].color = dados[1];
	grafo[1].position = 1;
	grafo[1].vb = &grafo[NUM_COLUNAS + 1];
	grafo[1].vd = &grafo[2];
	grafo[1].visited = TRUE;
	grafo[1].ve = NULL;
	grafo[1].vc = NULL;
	
	//Posição 1,C
	grafo[NUM_COLUNAS].color = dados[NUM_COLUNAS];
	grafo[NUM_COLUNAS].position = NUM_COLUNAS;
	grafo[NUM_COLUNAS].vb = &grafo[(NUM_COLUNAS * 2) + 1];
	grafo[NUM_COLUNAS].ve = &grafo[NUM_COLUNAS - 1];
	grafo[NUM_COLUNAS].visited = FALSE;
	grafo[NUM_COLUNAS].vc = NULL;
	grafo[NUM_COLUNAS].vd = NULL;
	//printf("%d\n", grafo[NUM_COLUNAS].position);

	//Posição L,1
	grafo[((NUM_LINHAS - 1) * NUM_COLUNAS) + 1].color = dados[((NUM_LINHAS - 1) * NUM_COLUNAS) + 1];
	grafo[((NUM_LINHAS - 1) * NUM_COLUNAS) + 1].position = ((NUM_LINHAS - 1) * NUM_COLUNAS) + 1;
	grafo[((NUM_LINHAS - 1) * NUM_COLUNAS) + 1].vc = &grafo[((NUM_LINHAS - 1) * (NUM_COLUNAS - 1)) + 1];
	grafo[((NUM_LINHAS - 1) * NUM_COLUNAS) + 1].vd = &grafo[((NUM_LINHAS - 1) * NUM_COLUNAS) + 2];
	grafo[((NUM_LINHAS - 1) * NUM_COLUNAS) + 1].visited = FALSE;
	grafo[((NUM_LINHAS - 1) * NUM_COLUNAS) + 1].vb = NULL;
	grafo[((NUM_LINHAS - 1) * NUM_COLUNAS) + 1].ve = NULL;
	//printf("%d\n", grafo[((NUM_LINHAS - 1) * NUM_COLUNAS) + 1].position );

	//Posição L,C
	grafo[NUM_COLUNAS * NUM_LINHAS].color = dados[NUM_COLUNAS * NUM_LINHAS];
	grafo[NUM_COLUNAS * NUM_LINHAS].position = NUM_COLUNAS * NUM_LINHAS;
	grafo[NUM_COLUNAS * NUM_LINHAS].ve = &grafo[NUM_COLUNAS * (NUM_LINHAS - 1)];
	grafo[NUM_COLUNAS * NUM_LINHAS].vc = &grafo[(NUM_COLUNAS * NUM_LINHAS) - 1];
	grafo[NUM_COLUNAS * NUM_LINHAS].visited = FALSE;
	grafo[NUM_COLUNAS * NUM_LINHAS].vb = NULL;
	grafo[NUM_COLUNAS * NUM_LINHAS].vd = NULL;
	//printf("%d\n", grafo[NUM_COLUNAS * NUM_LINHAS].position);

	//Linha Superior
	for(int i = 2; i < NUM_COLUNAS ; i++){
		grafo[i].color = dados[i];
		grafo[i].position = i;
		grafo[i].vb = &grafo[i + NUM_COLUNAS];
		grafo[i].vd = &grafo[i + 1];
		grafo[i].ve = &grafo[i - 1];
		grafo[i].visited = FALSE;
		grafo[i].vc = NULL;
	}

	//Linha Inferior
	for(int i = (NUM_LINHAS - 1) * NUM_COLUNAS + 2 ; i < NUM_LINHAS * NUM_COLUNAS ; i++){
		grafo[i].color = dados[i];
		grafo[i].position = i;
		grafo[i].ve = &grafo[i - 1];
		grafo[i].vc = &grafo[i - NUM_COLUNAS];
		grafo[i].vd = &grafo[i + 1];
		grafo[i].visited = FALSE;
		grafo[i].vb = NULL;
	}

	//Coluna Esquerda
	for (int i = NUM_COLUNAS + 1; i < (NUM_LINHAS - 1) * NUM_COLUNAS + 1 ; i += NUM_COLUNAS){
		grafo[i].color = dados[i];
		grafo[i].position = i;
		grafo[i].vc = &grafo[i - NUM_COLUNAS];
		grafo[i].vd = &grafo[i + 1];
		grafo[i].vb = &grafo[i + NUM_COLUNAS];	
		grafo[i].visited = FALSE;
		grafo[i].ve = NULL;	
	}

	//Coluna Direita
	for (int i = NUM_COLUNAS; i < NUM_COLUNAS * NUM_LINHAS; i += NUM_COLUNAS){
		grafo[i].color = dados[i];
		grafo[i].position = i;
		grafo[i].vc = &grafo[i - NUM_COLUNAS];
		grafo[i].ve = &grafo[i - 1];
		grafo[i].vb = &grafo[i + NUM_COLUNAS];	
		grafo[i].visited = FALSE;	
		grafo[i].vd = NULL;
	}

	//Posiçoes centrais
	//For anda por coluna
	for (int i = NUM_COLUNAS + 2; i < (2*NUM_COLUNAS); ++i){
		//For anda uma linha
		for (int j = i; j < ((NUM_LINHAS - 1) * NUM_COLUNAS) ; j += NUM_COLUNAS){
			grafo[j].color = dados[j];
			grafo[j].position = j;
			grafo[j].ve = &grafo[j - 1];
			grafo[j].vc = &grafo[j - NUM_COLUNAS];
			grafo[j].vd = &grafo[j + 1];
			grafo[j].vb = &grafo[j + NUM_COLUNAS];
			grafo[j].visited = FALSE;
		}
	}
	return grafo;
}

//Função que imprime o grafo
void imprimeGrafo (nodo grafo){
	for (int i = 0; i < NUM_LINHAS; i++){
		for (int j = 1; j <= NUM_COLUNAS; j++){
			printf("%d ", grafo[i*NUM_COLUNAS + j].color	);
			
		}
		printf("\n");
	}
}

//Função que procura nós ajacentes aos ja visitados e que ainda não foram adicionados ao cluster
int vizinhoLost (nodo grafo, nodo perdido, int cor, int chamador){
	int i = perdido->position;
	int found;
	if(i < chamador){
		if (grafo[i].visited == TRUE){	
			if ((grafo[i].vb != NULL) && (grafo[i].vb->color == cor) && (grafo[i].vb->visited == FALSE)){
				grafo[i].vb->visited = TRUE;
				found = vizinhoLost (grafo, grafo[i].vb, cor, chamador);
			}
			if ((grafo[i].vd != NULL) && (grafo[i].vd->color == cor) && (grafo[i].vd->visited == FALSE)){
				grafo[i].vd->visited = TRUE;
				found = vizinhoLost (grafo, grafo[i].vd, cor, chamador);
			}
			if ((grafo[i].ve != NULL) && (grafo[i].ve->color == cor) && (grafo[i].ve->visited == FALSE)){
				grafo[i].ve->visited = TRUE;
				found = vizinhoLost (grafo, grafo[i].ve, cor, chamador);
			}
			if ((grafo[i].vc != NULL) && (grafo[i].vc->color == cor) && (grafo[i].vc->visited == FALSE)){
				grafo[i].vc->visited = TRUE;
				found = vizinhoLost (grafo, grafo[i].vc, cor, chamador);
			}
		}
	}
	return found;
}

//Função que atualiza o cluster adicionano vizinhos que possuem a mesma cor que o cluster anterior
nodo maiorCluster(nodo grafo){
	
	for (int i = 1; i < NUM_LINHAS * NUM_COLUNAS; ++i){
		if (grafo[i].visited == TRUE){	
			if ((grafo[i].vb != NULL) && (grafo[i].vb->color == grafo[i].color)){
				grafo[i].vb->visited = TRUE;
			}
			if ((grafo[i].vd != NULL) && (grafo[i].vd->color == grafo[i].color)){
				grafo[i].vd->visited = TRUE;
			}
			if ((grafo[i].ve != NULL) && (grafo[i].ve->color == grafo[i].color) && (grafo[i].ve->visited == FALSE)){
				grafo[i].ve->visited = TRUE;
				int found = vizinhoLost (grafo, grafo[i].ve, grafo[i].color, i);
			}
			if ((grafo[i].vc != NULL) && (grafo[i].vc->color == grafo[i].color) && (grafo[i].vc->visited == FALSE)){
				grafo[i].vc->visited = TRUE;
				int found = vizinhoLost (grafo, grafo[i].vc, grafo[i].color, i);
			}
		}
	}	
	return grafo;
}

int vizinhanca (nodo grafo){
	int maior = 0;
	int cor = 0;
	int cores[NUM_CORES + 1];

	for (int c = 0; c <= NUM_CORES + 1; ++c){
		cores[c] = 0;
	}

	for (int i = 1; i <= NUM_LINHAS * NUM_COLUNAS; ++i){
		//printf("%d\n", grafo[i].position);
		if (grafo[i].visited == TRUE){	
			if ((grafo[i].vb != NULL) && (grafo[i].color != grafo[i].vb->color)&& (grafo[i].vb->visited == FALSE)){
				cores[grafo[i].vb->color] += 1; 
			}
			if ((grafo[i].vd != NULL) && (grafo[i].vd->color != grafo[i].color)&& (grafo[i].vd->visited == FALSE)){
				cores[grafo[i].vd->color] += 1;
			}
			if ((grafo[i].ve != NULL) && (grafo[i].ve->color != grafo[i].color) && (grafo[i].ve->visited == FALSE)){
				cores[grafo[i].ve->color] += 1;
			}
			if ((grafo[i].vc != NULL) && (grafo[i].vc->color != grafo[i].color) && (grafo[i].vc->visited == FALSE)){
				cores[grafo[i].vc->color] += 1;
			}
		}
	}
	for (int k = 1; k <= NUM_CORES; k++){
		if (cores[k] > maior){
			maior = cores[k];
			cor = k;
		}

	}
	return cor;
}


//Função que altera a cor do cluster para a cor definida anteriormente como a melhor opção
nodo alteraCor(nodo grafo, int cor){
	for (int i = 1; i <= NUM_LINHAS * NUM_COLUNAS; ++i){
		if(grafo[i].visited == TRUE)
			grafo[i].color = cor;
	}
	return grafo;
}

void imprimePassos (int *passos){
	printf("%d\n", passos[0]);
	for(int i = 1; i <= passos[0]; i++){
		printf("%d ", passos[i]);
	}
	printf("\n");
}

int main(int argc, char *argv[]){
	//LE O ARQUIVO DE ENTRADA DO CONSOLE
	int *passos;

	if(argc == 1){
		printf("INFORME O NOME DO ARQUIVO DE ENTRADA \n");
		printf("%s", argv[1]);
		return 0;	
	}
		//printf("Carregando arquivo: %s \n", argv[1]);
	
	//LEITURA DO ARQUIVO
	FILE *fp;
	fp = fopen(argv[1],"r");
	int conter;
	fscanf(fp,"%d \t %d \t %d",&NUM_LINHAS,&NUM_COLUNAS, &NUM_CORES);
	
	int lxc = (NUM_LINHAS * NUM_COLUNAS) + 1;
	int vetor[lxc];
    	
	conter = 1;
	while(conter < lxc){
		fscanf(fp,"%d", &vetor[conter]);
		conter++;
	}

	fclose(fp);

	int cor = 4;

	passos = (int *) malloc(5000); //Memoria alocada para garantir a quantidade de passos seja mostrada 

	passos[0] = 0;

	nodo grafo = malloc (sizeof(struct nodo)*(lxc));
	
	grafo = criagrafo(grafo, vetor);

	//printf("antes\n");
	//imprimeGrafo(grafo);
	while (cor > 0){
		//printf("\n");
		grafo = maiorCluster(grafo);

		cor = vizinhanca(grafo);
		if (cor != 0){
			passos[0] += 1;
			//printf("%d\n", cor);
			passos[passos[0]] = cor;

			alteraCor(grafo, cor);
		}
		//printf("\n");
		//imprimeGrafo(grafo);
		
	}
	
	imprimePassos(passos);



	return 0;

	free(passos);
	free(grafo);
}




	

