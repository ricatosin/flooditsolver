# flooditsolver

FLOOD IT SOLVER IN C - ARTFICIAL INTELLIGENCE

Flood it é um jogo de estratégia simples, mas viciante, no qual você tem que inundar todo o tabuleiro 
de jogo com uma cor em menos que as etapas permitida.

AUTHOR: RICARDO TOSIN                                                  


1 -CONSIDERACOES INICIAIS E USO.

	##1.1 - PARA COMPILAR DIGITE MAKE, COMPILA flood.c e geramapadificil.c 

	      1.1.2 - PARA VER COMO UTILIZAR GERADOR DE MAPA IR PARA SECAO 7.1.
	      1.1.3 - PARA RODAR O RESOLVEDOR DO FLOOD IT DIGITE  ----> ./flood entrada.txt

	1.3 - PRIMEIRAMENTE HOUVE TENTATIVA DE DESENVOLVIMENTOCOM APENAS COM 2 VIZINHOS PARA CADA POSICAO, POREM QUANDO HAVIA
	      UM VIZINHO ACIMA E DE MESMA COR ELE NAO ERA ADICIONADO AO CLUSTER DE CORES E NAO JOGAVA CORRETAMENTE!
	      
	      AGORA RESOLVE MAPAS COM ESTE MODELO CUJA TEM VIZINHOS ACIMA
	      
	      1 2 1 3 1
	      1 2 1 3 1
	      1 2 1 3 1
	      1 1 1 1 3
	      
	
	1.4 - TESTADO ATE 100x100 COM 100 CORES E CONSEGUIU RESOLVER EM POUCOS SEGUNDOS COM UMA BOA MEDIA DE PASSOS.
	
	1.5 - PARA MOSTRAR O PASSO A PASSO DA IMPRESSAO DA MATRIZ  BASTA DESCOMENTAR A FUNCAO //IMPRIME_GRAFO() NO MAIN();
		
		1.5.1 - TAMBEM POSSIBILITA MOSTRAR VIZINHOS VIZITADOS OU APENAS CORES ALTERANDO A LINHA 143 - printf("%d ", grafo[i*NUM_COLUNAS + j].color	);
				PARA  ---> printf("%d ", grafo[i*NUM_COLUNAS + j].visited	); 
	  
########################################################################################################################################
2 - LEITURA DO ARQUIVO DE ENTRADA

	2.1 - LEITURA ATRAVES DA FUNCAO "fscanf" LE A PRIMEIRA LINHA GUARDA VALORES GLOBAIS LINHA X COLUNAS E CORES E ITERA ATE O FINAL DO ARQUIVO.

#######################################################################################################################################

3 - ESTRUTURA DO DE DADOS.

	3.1 - VETOR DE STRUCT CONTENDO.
		
		3.2 - POSICAO = INTEIRO.
		3.3 - COR = INTEIRO.
		3.4 - VISITADO = BOOL. DEFINICOES CRIADAS ATRAVES DO #DEFINE.
		3.5 - VIZINHOS DO TIPO NODO = VIZINHO CIMA, VIZINHO DIREITA, VIZINHO BAIXO, VIZINHO ESQUERDA.


#######################################################################################################################################


4 - INICIALIZACAO E RACIOCINIO TRATAMENTO DA ESTRUTURA DE DADOS
	NA FUNCAO CUJA CHAMO DE CRIAGRAFO(); TRATAMOS A ALOCACAO 
	DAS POSICOES DA MATRIZ EM NOSSA ESTRUTURA.


   
	4.1 - PARA TRATAR CASOS DE 2 VIZINHOS SENDO ELES APENAS VIZINHO DIREITA , BAIXO
	      POSICAO (1,1) = X DA MATRIZ RECEBE COMO VIZINHOS POSICAO (Y), OUTROS RECEBEM NULL. 
	

		X Y 3
		Y 2 3
		3 0 2 


	4.2 - PARA TRATAR CASOS DE 2 VIZINHOS SENDO ELES APENAS VIZINHO ESQUERDA , BAIXO
	      POSICAO (1,3) = X DA MATRIZ RECEBE COMO VIZINHOS AS POSICOES (Y), OUTROS RECEBEM NULL.


		1 Y X
		2 2 Y
		3 1 2  

	4.3 - PARA TRATAR CASOS DE 3 VIZINHOS SENDO ELES APENAS VIZINHO ESQUERDA , BAIXO
	      POSICAO (2,3) = X DA MATRIZ RECEBE COMO VIZINHOS AS POSICOES (Y) OUTRO RECEBE NULL.


		1 2 Y
		2 Y X
		3 1 Y  


	4.4 - PARA TRATAR CASOS DE 4 VIZINHOS SENDO ELES APENAS VIZINHO ESQUERDA , BAIXO
	      POSICAO (1,1) = X DA MATRIZ RECEBE COMO VIZINHOS AS POSICOES (Y).


		1 Y 3
		Y X Y
		3 Y 2  



	4.5 OS OUTROS CASOS SAO ANALOGOS MUDANDO APENAS OS VIZINHOS !


######################################################################################################################################



5 - AGENTE DE BUSCA E HEURISTICA, CLUSTER DE CORES.

	5.1 - INICIALMENTE O CLUSTER COMECA COM A POSICAO (1,1) MATRIZ CANTO SUPERIOR ESQUERDO MARCADA COMO VISITADA
	      APARTIR DESTE MOMENTO JA INICIAMOS UMA BUSCA POR ALGUMA COR DE VIZINHO IGUAL PARA AUMENTAR
	      O TAMANHO DO CLUSTER INICIAL, ELE VAI PERCORRER TODA A "MATRIZ" EM ORDEM (CADA COLUNA POR LINHA), 
	      CASO O NÓ ATUAL (Q PERTENÇA AO CLUSTER) ACHE ALGUM VIZINHO ANTERIOR DE MESMA COR Q DEVERIA ESTAR NO CLUSTER, ELE ENTRA 
	      EM RECURSAO PROCURANDO VIZINHOS DE COR IGUAL Q DEVERIA ESTAR NO CLUSTER. ELE PERCORRE ATÉ :
	      	1: NAO ACHA MAIS VIZINHOS DE COR IGUAL
             		 2: ENCONTRA VIZINHO DE COR IGUAL, MAS NUMA POSIÇAO MAIOR DO Q A Q CHAMOU A RECURSAO


	5.3 - AGENTE

		5.3.1 - VERIFICA POSICOES DO CLUSTER E SEUS VIZINHOS A PROCURA DA MAIOR COR NA FRONTEIRA DIFERENTE DA COR ATUAL PARA PINTAR.
		5.3.2 - CONTA VALOR DE CORES MAIOR COR QUE APARECE SERA PINTADA COMO NOVO CLUSTER.


	5.4 - HEURISTICA - MAIOR COR QUE APARECE NA FRONTEIRA DO CLUSTER ! 



6 - OUTRAS TENTATIVAS DE HEURISTICA DESCARTADAS

	6.1 - HOUVE TENTATIVA DE HEURISTICA DIFERENTE PARA O AGENTE DE BUSCA MAS NAO FUNCIONOU MUITO BEM E AUMENTO CONSIDERAVELMENTE OS 
	PASSOS E CONSEQUENTEMENTE O TEMPO ELA SE BASEAVA EM BUSCAR A MAIOR COR QUE APARECIA DIFERENTE DO CLUSTER SEM OLHAR FRONTEIRAS E 
	ENTAO PINTAVA VERIFICAVA TAMANHO DO CLUSTER SE AUMENTA CONTINUAVA SE NAO AUMENTA RETROCEDE 
	E PINTA DE OUTRA COR E ASSIM IA ATERESOLVER. 


########################################################################################################################################
	      
7 -  GERA UM MAPA DIFICIL - geramapadificil.c

	7.1 - USO 
		MAKE IRA COMPILAR O ARQUIVO
		
		EXEMPLOS DE USO:

		./geramapadificil 10 > saida.out 
		./geramapadificil 20 > saida.out
		./geramapadificil 100 > saida.out
			


	7.1 - GERA UM MAPA DIFICIL DO TAMANHO N X N X N OU SEJA EXEMPLO 10 LINHAS X 10 COLUNAS X 10 CORES 
	      QUALQUER MAPA GERADO IRA USAR A ESTRATEGIA DE NUNCA COLOCAR UMA MESMA COR EM UMA MESMA LINHA OU EM UMA MESMA COLUNA
	      NA TENTATIVA DE MAXIMIZAR O TAMANHO DA BUSCA PARA ENCONTRAR UM CLUSTER.

	
	7.2 - EXEMPLO DE MAPA GERADO 10 X 10 X 10

			10 10 10
			10 8 6 4 2 3 5 7 9 1 
			1 9 7 5 3 4 6 8 10 2 
			2 10 8 6 4 5 7 9 1 3 
			3 1 9 7 5 6 8 10 2 4 
			4 2 10 8 6 7 9 1 3 5 
			5 3 1 9 7 8 10 2 4 6 
			6 4 2 10 8 9 1 3 5 7 
			7 5 3 1 9 10 2 4 6 8 
			8 6 4 2 10 1 3 5 7 9 
			9 7 5 3 1 2 4 6 8 10 	











