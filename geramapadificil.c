// PROGRAMA EM C PRA CONSTRUIR UMA MATRIZ DIFICIAL NXNXN
// ONDE CADA LINHA E COLUNA TEM UM VALOR DISTINTO
#include <stdio.h>
#include <math.h>
	 
#define MAX 100

//VALOR MAXIMO 100X100X100
int mat[MAX][MAX];
 
// Preenche entradas não pertencentes a  coluna j
// DADO QUE EXISTE '1' NA POSICAO mat[i][j],
// PREENCHE OUTRAS ENTRADAS DA COLUNA j.
void colocaFaltantes(int i, int j, int n)
{
    // INICIALIZA VALOR PARA PREENCHER
    int x = 2;
 
    // ITERA PREENCHE ENTRE VALORES I, 2, 3
    for (int k=i+1; k<n; k++)
        mat[k][j] = x++;
 
    // PREENCHE OS VALORES p+1, p+2, .. n
    for (int k=0; k<i; k++)
        mat[k][j] = x++;
}
 
// PREENCHE TODA MATRIZ 
// DEFININDO AS REGRAS
void constroiMatriz(int n)
{
    // Em alternativa, preencha 1s a partir de
     // colunas mais à direita e à esquerda. Para
     // exemplo para n = 3, obtemos {{_ _ 1},
    // {1 _ _} {_ 1 _}}
    int direita = n-1, esquerda = 0;
    for (int i=0; i < n; i++)
    {
        // se for par, entao preenche a proxima coluna
        if (i%2 == 0)
        {
            mat[i][direita] = 1;
 
            // depois de preencher um preencha as restantes
            // para coluna direita
            colocaFaltantes(i, direita, n);
 
            // Move direita uma coluna para tras
            direita--;
        }
        else // preeencha proxima esquerda
        {
            mat[i][esquerda] = 1;
 
            // depois de preencher um preencha as restantes
            // para coluna "esquerda"
            colocaFaltantes(i, esquerda, n);
 
            // Move esquerda uma coluna a frente
            esquerda++;
        }
    }
}
 

int main(int argc, char **argv) {
 
	int n1,n2,n;
	n = atoi(argv[1]);
	n1 = n;
	n2 = n1;
	printf("%d ", n);
	printf("%d ", n1);
	printf("%d\n", n2);
	//scanf("%d",&n);
    // passa n para constroiMatriz 
    constroiMatriz(n);
 
    //imprime a matriz
    for (int i=0; i<n; i++)
    {
        for (int j=0 ; j<n; j++)
            printf("%d ",mat[i][j]);
        printf ("\n");
    }
    return 0;
}
