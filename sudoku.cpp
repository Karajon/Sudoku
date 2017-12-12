// SUDOKUentrega.cpp: Define o ponto de entrada para a aplicação de console.

#include "stdafx.h"
#include <stdlib.h>

//======================================================PROTÓTIPOS=============================================================================

void deslocamentoQ1(int, int, int*, int*);//calcula o deslocamento (i, j) de um quadro em relação ao quadro 1
void deslocamentoDeterminaQuadro(int, int, int*);//através dos valores de deslocamento, determina o quadro
void anda(int*, int, int);// movimentação encadeada linear [início...fim]
void andaQuadro(int*, int*);//movimentação encadeada dentro de um quadro 3 x 3
void limpaD2(int[9][9]);//zera uma matriz 9 x 9
void limpaD3(int[9][9][9]);// zera uma matriz 9 x 9 x 9
void imprimeD2(int[9][9]);//imprime uma matriz 9 x 9
void imprimeD3(int[9][9][9]);//imprime uma matriz 9 x 9 x 9
void iniciaSudoku(int[9][9], int[9][9][9]);//configura valores iniciais para sudoku e matrizes auxiliares
void iniciaMatrizNum(int[9][9], int[9][9][9]);//marca as posições que não podem ser inseridas com "1" para cada número [1..9]
void atualizaMatrizNumLinhaColuna(int[9][9], int[9][9][9], int, int);//atualiza linhas e colunas da matrizNum
void atualizaMatrizNumQuadro(int[9][9], int[9][9][9], int, int);//atualiza quadros da matrizNum
void atualizaMatrizNum(int[9][9], int[9][9][9], int, int);//une atualização de linha, coluna e quadro, além de marcar a posição inserida para todos os valores [1..9]
void atualizaVazioLinhaColuna(int[9][9][9], int[9][9], int, int, int[9][9], int[9][9]);//conta a quantidade de posições vazias por linha e coluna para cada número [1..9]
void atualizaVazioQuadro(int[9][9][9], int[9][9], int, int, int[9][9], int[9][9], int[9][9]);//conta a quantidade de posições vazias por quadro para cada número [1..9]
void atualizaVazio(int[9][9][9], int[9][9], int[9][9], int[9][9], int[9][9]);//atualiza as matrizes "Vazio"
void insere(int[9][9], int[9][9][9], int[9][9], int[9][9], int[9][9], int, int, int);//insere um elemento no sudoku e chama todas as atualizações necessárias
void vazioInsereLinha(int[9][9], int[9][9][9], int[9][9], int[9][9], int[9][9], int);//encontra linha que possui apenas um espaço vazio, e chama "insere" para o valor correto
void vazioInsereColuna(int[9][9], int[9][9][9], int[9][9], int[9][9], int[9][9], int);//encontra coluna que possui apenas um espaço vazio, e chama "insere" para o valor correto
void vazioInsereQuadro(int[9][9], int[9][9][9], int[9][9], int[9][9], int[9][9], int);//encontra quadro que possui apenas um espaço vazio, e chama "insere" para o valor correto
int vazioL(int[9][9]);//verifica se ainda é possível inserir em uma linha algum valor com certeza
int vazioC(int[9][9]);//verifica se ainda é possível inserir em uma coluna algum valor com certeza
int vazioQ(int[9][9]);//verifica se ainda é possível inserir em um quadro algum valor com certeza
void vazioInsereTudoLinha(int[9][9], int[9][9][9], int[9][9], int[9][9], int[9][9]);//enquanto for possível inserir um valor com certeza passa por todas as linhas chamando vazioInsereLinha
void vazioInsereTudoColuna(int[9][9], int[9][9][9], int[9][9], int[9][9], int[9][9]);//enquanto for possível inserir um valor com certeza passa por todas as colunas chamando vazioInsereColuna
void vazioInsereTudoQuadro(int[9][9], int[9][9][9], int[9][9], int[9][9], int[9][9]);//enquanto for possível inserir um valor com certeza passa por todos os quadros chamando vazioInsereQuadro
void vazioInsereTudo(int[9][9], int[9][9][9], int[9][9], int[9][9], int[9][9]);//chama as 3 funções acima enquanto for possível inserir um valor com certeza
void quadroLinhaEspecial(int[9][9][9], int, int, int);//ajusta quadros analisando confronto de linhas
void quadroColunaEspecial(int[9][9][9], int, int, int);//ajusta quadros analisando confront de colunas
void quadroEspecial(int[9][9][9]);//2 funções acima
void verificaEspaco(int[9][9], int[9][9][9], int[9][9], int[9][9], int[9][9]);//verifica para cada posição se apenas um número pode ser inserido
void resolve(int[9][9], int[9][9][9], int[9][9], int[9][9], int[9][9]);//busca a solução do sudoku

//======================================================FUNÇÕES==========================================================================

void deslocamentoQ1(int linha, int coluna, int *iDeslocamento, int *jDeslocamento)
{
	*iDeslocamento = linha;
	*iDeslocamento -= linha % 3;

	*jDeslocamento = coluna;
	*jDeslocamento -= coluna % 3;
}

void deslocamentoDeterminaQuadro(int iDeslocamento, int jDeslocamento, int *quadro)
{
	//determina coluna de quadro através dos jDeslocamentos
	if (jDeslocamento == 0)
		*quadro = 1;

	if (jDeslocamento == 3)
		*quadro = 2;

	if (jDeslocamento == 6)
		*quadro = 3;

	//determina linha de quadro através dos iDeslocamentos
	if (iDeslocamento == 3)
		*quadro += 3;

	if (iDeslocamento == 6)
		*quadro += 6;
}

void anda(int *indice, int inicio, int fim)
{
	if (*indice == fim)
		*indice = inicio;
	else
		*indice += 1;
}

void andaQuadro(int *indiceLinha, int *indiceColuna)
{
	if (*indiceColuna == 2)
		anda(indiceLinha, 0, 2);

	anda(indiceColuna, 0, 2);
}

//======================================================================================================================================

void limpaD2(int matriz[9][9])
{
	int i, j;

	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
			matriz[i][j] = 0;
	}
}

void limpaD3(int matrizNum[9][9][9])
{
	int i, j, k;

	for (k = 0; k < 9; k++)
	{
		for (i = 0; i < 9; i++)
		{
			for (j = 0; j < 9; j++)
			{
				matrizNum[k][i][j] = 0;
			}
		}
	}
}

//======================================================================================================================================

void imprimeD2(int matriz[9][9])
{
	int i, j;

	printf("\n\t\t\t-------------------------------\n\t\t\t");

	for (i = 0; i < 9; i++)
	{
		printf("|");
		for (j = 0; j < 9; j++)
		{
			if (matriz[i][j] == 0)
				printf(" - ");
			else
				printf(" %d ", matriz[i][j]);

			if (j % 3 == 2)
				printf("|");
		}
		printf("\n\t\t\t");

		if (i % 3 == 2)
			printf("-------------------------------\n\t\t\t");
	}
}

void imprimeD3(int matriz[9][9][9])
{
	int i, j, k;

	for (k = 0; k < 9; k++)
	{
		printf("\n%d\n\n", k + 1);

		for (i = 0; i < 9; i++)
		{
			for (j = 0; j < 9; j++)
			{
				if (matriz[k][i][j] == 0)
					printf(" - ");
				else
					printf(" %d ", matriz[k][i][j]);
			}
			printf("\n");
		}
	}
	printf("\n\n");
}

//======================================================================================================================================

void iniciaSudoku(int sudoku[9][9], int matrizNum[9][9][9], int vazioLinha[9][9], int vazioColuna[9][9], int vazioQuadro[9][9])
{

	int i, j;

	limpaD2(sudoku);

	///*
	//=> inserir valores manualmente
	printf("\t\t\tPreenche com um sudoku valido\n\n");

	for (i = 0; i < 9; i++)
	{
		for(j = 0; j < 9; j++)
		{
			printf("[%d,%d]\n", i, j);
			scanf_s("%d", &sudoku[i][j]);
		}
	}
	//*/

	/*
	//=> very hard

	//1
	sudoku[0][0] = 2;
	//2
	sudoku[0][1] = 8;
	//3
	sudoku[0][4] = 4;
	//4
	sudoku[1][7] = 3;
	//5
	sudoku[1][8] = 1;
	//6
	sudoku[2][7] = 6;
	//7
	sudoku[3][0] = 7;
	//8
	sudoku[3][3] = 2;
	//9
	sudoku[3][6] = 8;
	//10
	sudoku[4][1] = 3;
	//11
	sudoku[4][3] = 1;
	//12
	sudoku[5][3] = 6;
	//13
	sudoku[5][5] = 8;
	//14
	sudoku[6][4] = 7;
	//15
	sudoku[6][6] = 5;
	//16
	sudoku[7][2] = 1;
	//17
	sudoku[8][0] = 4;
	*/

	/*
	//=> medium

	//1
	sudoku[0][2] = 5;
	//2
	sudoku[0][3] = 9;
	//3
	sudoku[0][8] = 7;

	//4
	sudoku[1][1] = 7;
	//5
	sudoku[1][4] = 6;
	//6
	sudoku[1][8] = 1;

	//7
	sudoku[2][0] = 4;
	//8
	sudoku[2][1] = 3;
	//9
	sudoku[2][3] = 2;

	//10
	sudoku[3][2] = 7;
	//11
	sudoku[3][3] = 6;
	//12
	sudoku[3][5] = 3;
	//13
	sudoku[3][7] = 8;

	//14
	sudoku[4][1] = 2;
	//15
	sudoku[4][7] = 7;

	//16
	sudoku[5][1] = 4;
	//17
	sudoku[5][3] = 8;
	//18
	sudoku[5][5] = 7;
	//19
	sudoku[5][6] = 2;

	//20
	sudoku[6][5] = 1;
	//21
	sudoku[6][7] = 4;
	//22
	sudoku[6][8] = 2;

	//23
	sudoku[7][0] = 5;
	//24
	sudoku[7][4] = 9;
	//25
	sudoku[7][7] = 1;

	//26
	sudoku[8][0] = 6;
	//27
	sudoku[8][5] = 2;
	//28
	sudoku[8][6] = 8;
	*/

	iniciaMatrizNum(sudoku, matrizNum);
	atualizaVazio(matrizNum, sudoku, vazioLinha, vazioColuna, vazioQuadro);
	imprimeD2(sudoku);
}

void iniciaMatrizNum(int sudoku[9][9], int matrizNum[9][9][9])
{
	int i, j, k;

	limpaD3(matrizNum);

	for (k = 0; k < 9; k++)
	{
		for (i = 0; i < 9; i++)
		{
			for (j = 0; j < 9; j++)
			{
				if (sudoku[i][j] != 0)
					atualizaMatrizNum(sudoku, matrizNum, i, j);
			}
		}
	}

	//imprimeD3(matrizNum);
}

void atualizaMatrizNumLinhaColuna(int sudoku[9][9], int matrizNum[9][9][9], int linha, int coluna)
{
	int k;

	int indiceLinha, indiceColuna, indiceNum;

	indiceLinha = linha;
	indiceColuna = coluna;
	indiceNum = sudoku[linha][coluna] - 1;

	for (k = 0; k < 8; k++)//há 8 posições para percorrer exceto a própria
	{
		anda(&indiceLinha, 0, 8);
		anda(&indiceColuna, 0, 8);
		matrizNum[indiceNum][linha][indiceColuna] = 1;
		matrizNum[indiceNum][indiceLinha][coluna] = 1;
	}
}

void atualizaMatrizNumQuadro(int sudoku[9][9], int matrizNum[9][9][9], int linha, int coluna)
{
	int linhaQuadro, colunaQuadro, iDeslocamento, jDeslocalmento, indice, k;

	indice = sudoku[linha][coluna] - 1;

	linhaQuadro = linha % 3;
	colunaQuadro = coluna % 3;

	deslocamentoQ1(linha, coluna, &iDeslocamento, &jDeslocalmento);

	for (k = 0; k < 8; k++)
	{
		andaQuadro(&linhaQuadro, &colunaQuadro);
		matrizNum[indice][linhaQuadro + iDeslocamento][colunaQuadro + jDeslocalmento] = 1;
	}
}

void atualizaMatrizNum(int sudoku[9][9], int matrizNum[9][9][9], int linha, int coluna)
{
	int k;

	for (k = 0; k < 9; k++)
	{
		matrizNum[k][linha][coluna] = 1;//marca na matriz de cada número que um elemento foi inserido ali
	}

	atualizaMatrizNumLinhaColuna(sudoku, matrizNum, linha, coluna);//marca o quadro na matriz do número inserido
	atualizaMatrizNumQuadro(sudoku, matrizNum, linha, coluna);//marca o quadro na matriz do número inserido
}

//======================================================================================================================================

void atualizaVazioLinhaColuna(int matrizNum[9][9][9], int sudoku[9][9], int linha, int coluna, int vazioLinha[9][9], int vazioColuna[9][9])
{
	int k;

	int indiceLinha, indiceColuna, indiceNum, contColuna = 0, contLinha = 0;

	indiceLinha = linha;
	indiceColuna = coluna;
	//indiceNum = sudoku[linha][coluna] - 1;

	for (indiceNum = 0; indiceNum < 9; indiceNum++)
	{
		contLinha = 0;
		contColuna = 0;

		for (k = 0; k < 9; k++)
		{
			anda(&indiceLinha, 0, 8);
			anda(&indiceColuna, 0, 8);
			if (matrizNum[indiceNum][linha][indiceColuna] == 0)//varre a linha
				contLinha++;
			if (matrizNum[indiceNum][indiceLinha][coluna] == 0)//varre a coluna
				contColuna++;
		}

		//if (contColuna == 1)
		vazioColuna[indiceNum][coluna] = contColuna;
		//printf("vazioColuna[%d][%d] = %d\n", indiceNum, coluna, contColuna);//printf para visualização e teste

		//if (contLinha == 1)
		vazioLinha[indiceNum][linha] = contLinha;
		//printf("vazioLinha[%d][%d] = %d\n", indiceNum + 1, linha, contLinha);//printf para visualização e teste
	}
}

void atualizaVazioQuadro(int matrizNum[9][9][9], int sudoku[9][9], int linha, int coluna, int vazioLinha[9][9], int vazioColuna[9][9], int vazioQuadro[9][9])
{
	int linhaQuadro, colunaQuadro, iDeslocamento, jDeslocamento, indice, k, count = 0, quadro, linhaAux, colunaAux;
	//quadros vizinhos
	int iDeslocamentoA, jDeslocamentoA;
	int iDeslocamentoB, jDeslocamentoB;
	int iDeslocamentoC, jDeslocamentoC;
	int iDeslocamentoD, jDeslocamentoD;
	int iAux, jAux;
	int countA, countB, countC, countD;
	int quadroA, quadroB, quadroC, quadroD;

	//indice = sudoku[linha][coluna] - 1;
	linhaQuadro = linha % 3;
	colunaQuadro = coluna % 3;
	linhaAux = linha % 3;
	colunaAux = coluna % 3;
	//auxiliares de posição para encontrar deslocamento dos quadros vizinhos
	iAux = linha;
	jAux = coluna;

	deslocamentoQ1(linha, coluna, &iDeslocamento, &jDeslocamento);
	//deslocamentos dos quadros vizinhos
	anda(&jAux, 0, 8);
	anda(&jAux, 0, 8);
	anda(&jAux, 0, 8);
	//desloca para quadro à direita
	deslocamentoQ1(iAux, jAux, &iDeslocamentoA, &jDeslocamentoA);
	anda(&jAux, 0, 8);
	anda(&jAux, 0, 8);
	anda(&jAux, 0, 8);
	//desloca para quadro à direita novamente
	deslocamentoQ1(iAux, jAux, &iDeslocamentoB, &jDeslocamentoB);
	anda(&jAux, 0, 8);
	anda(&jAux, 0, 8);
	anda(&jAux, 0, 8);
	//desloca para quadro à direita mais uma vez, retornando à posição original
	anda(&iAux, 0, 8);
	anda(&iAux, 0, 8);
	anda(&iAux, 0, 8);
	//desloca para quadro abaixo
	deslocamentoQ1(iAux, jAux, &iDeslocamentoC, &jDeslocamentoC);
	anda(&iAux, 0, 8);
	anda(&iAux, 0, 8);
	anda(&iAux, 0, 8);
	//desloca para quadro abaixo novamente
	deslocamentoQ1(iAux, jAux, &iDeslocamentoD, &jDeslocamentoD);

	deslocamentoDeterminaQuadro(iDeslocamento, jDeslocamento, &quadro);
	//quadros vizinhos
	deslocamentoDeterminaQuadro(iDeslocamentoA, jDeslocamentoA, &quadroA);
	deslocamentoDeterminaQuadro(iDeslocamentoB, jDeslocamentoB, &quadroB);
	deslocamentoDeterminaQuadro(iDeslocamentoC, jDeslocamentoC, &quadroC);
	deslocamentoDeterminaQuadro(iDeslocamentoD, jDeslocamentoD, &quadroD);

	//prints para visualização e testes
	//printf("atualizaVazioQuadro [%d,%d] -> q:%d\n", linha, coluna, quadro);

	for (indice = 0; indice < 9; indice++)//varia os números em relação à matrizNum
	{
		count = 0;
		//quadros vizinhos
		countA = 0;
		countB = 0;
		countC = 0;
		countD = 0;

		for (k = 0; k < 9; k++)
		{
			andaQuadro(&linhaQuadro, &colunaQuadro);

			if (matrizNum[indice][linhaQuadro + iDeslocamento][colunaQuadro + jDeslocamento] == 0)
				count++;

			//quadro vizinhos
			//usa o mesmo andaQuadro, com deslocamentos diferentes
			if (matrizNum[indice][linhaQuadro + iDeslocamentoA][colunaQuadro + jDeslocamentoA] == 0)
				countA++;
			if (matrizNum[indice][linhaQuadro + iDeslocamentoB][colunaQuadro + jDeslocamentoB] == 0)
				countB++;
			if (matrizNum[indice][linhaQuadro + iDeslocamentoC][colunaQuadro + jDeslocamentoC] == 0)
				countC++;
			if (matrizNum[indice][linhaQuadro + iDeslocamentoD][colunaQuadro + jDeslocamentoD] == 0)
				countD++;
		}

		//varre a diagonal do quadro, para atualizar linhas e colunas que se relacionam ao quadro
		//atualizaVazioLinhaColuna(matrizNum, sudoku, (linhaAux + iDeslocamento), (colunaAux + jDeslocamento), vazioLinha, vazioColuna);
		/*anda(&linhaAux, 0, 2);
		anda(&colunaAux, 0, 2);
		atualizaVazioLinhaColuna(matrizNum, sudoku, (linhaAux + iDeslocamento), (colunaAux + jDeslocamento), vazioLinha, vazioColuna);
		anda(&linhaAux, 0, 2);
		anda(&colunaAux, 0, 2);
		atualizaVazioLinhaColuna(matrizNum, sudoku, (linhaAux + iDeslocamento), (colunaAux + jDeslocamento), vazioLinha, vazioColuna);
		anda(&linhaAux, 0, 2);
		anda(&colunaAux, 0, 2);
		*/

		//if (count == 1)
		//printf("atualizaVazioQuadro vazioQuadro[%d][%d] = %d\n", indice, quadro, count);//printf para visualização e teste
		vazioQuadro[indice][quadro - 1] = count;
		//quadros vizinhos
		//printf("atualizaVazioQuadro vazioQuadroA[%d][%d] = %d\n", indice, quadroA, countA);//printf para visualização e teste
		//printf("atualizaVazioQuadro vazioQuadroB[%d][%d] = %d\n", indice, quadroB, countB);//printf para visualização e teste
		//printf("atualizaVazioQuadro vazioQuadroC[%d][%d] = %d\n", indice, quadroC, countC);//printf para visualização e teste
		//printf("atualizaVazioQuadro vazioQuadroD[%d][%d] = %d\n", indice, quadroD, countD);//printf para visualização e teste
		vazioQuadro[indice][quadroA - 1] = countA;
		vazioQuadro[indice][quadroB - 1] = countB;
		vazioQuadro[indice][quadroC - 1] = countC;
		vazioQuadro[indice][quadroD - 1] = countD;

	}

}

void atualizaVazio(int matrizNum[9][9][9], int sudoku[9][9], int vazioLinha[9][9], int vazioColuna[9][9], int vazioQuadro[9][9])
{
	int i = 0, j = 0, k;
	int a, b;

	for (a = 0; a < 9; a++)
	{
		for (b = 0; b < 9; b++)
		{
			vazioLinha[a][b] = 0;
			vazioColuna[a][b] = 0;
			vazioQuadro[a][b] = 0;
			//limpa as matrizes "vazio"
		}
	}

	for (k = 0; k < 9; k++)
	{
		atualizaVazioLinhaColuna(matrizNum, sudoku, k, k, vazioLinha, vazioColuna);
		atualizaVazioQuadro(matrizNum, sudoku, i * 3, j * 3, vazioLinha, vazioColuna, vazioQuadro);//percorre os 9 quadros
		andaQuadro(&i, &j);//o movimento de posições em um quadro 3 x 3 é transformado no movimento entre quadro ao se multiplicar os índices por 3
	}
}

void insere(int sudoku[9][9], int matrizNum[9][9][9], int vazioLinha[9][9], int vazioColuna[9][9], int vazioQuadro[9][9], int linha, int coluna, int valor)
{
	int i = 0;

	sudoku[linha][coluna] = valor;
	//printf("insere sudoku[%d,%d] <- %d\n", linha, coluna, valor);//printf para visualização e teste
	atualizaMatrizNum(sudoku, matrizNum, linha, coluna);
	atualizaVazio(matrizNum, sudoku, vazioLinha, vazioColuna, vazioQuadro);

	system("pause");
	system("cls");
	imprimeD2(sudoku);
}

//======================================================================================================================================

void vazioInsereLinha(int sudoku[9][9], int matrizNum[9][9][9], int vazioLinha[9][9], int vazioColuna[9][9], int vazioQuadro[9][9], int numero)
{
	int i, coluna;

	for (i = 0; i < 9; i++)
	{
		//printf("vazioLinha[%d][%d]:%d\n", numero, i, vazioLinha[numero][i]);//para visualização e teste

		if (vazioLinha[numero][i] == 1)//encontrou a única posição vazia
		{
			coluna = 0;
			while (matrizNum[numero][i][coluna] != 0)
				coluna++;

			//printf("vazioInsereLinha sudoku[%d, %d] <= %d\n", i, coluna, (numero + 1));//para visualização e teste
			insere(sudoku, matrizNum, vazioLinha, vazioColuna, vazioQuadro, i, coluna, (numero + 1));
		}
	}
}

void vazioInsereColuna(int sudoku[9][9], int matrizNum[9][9][9], int vazioLinha[9][9], int vazioColuna[9][9], int vazioQuadro[9][9], int numero)
{
	int i, linha;

	for (i = 0; i < 9; i++)
	{
		if (vazioColuna[numero][i] == 1)//encontrou a única posição vazia
		{
			linha = 0;
			while (matrizNum[numero][i][linha] != 0 && linha < 9)
				linha++;

			//printf("vazioInsereColuna sudoku[%d, %d] <= %d\n", linha, i, (numero + 1));//para visualização e teste
			insere(sudoku, matrizNum, vazioLinha, vazioColuna, vazioQuadro, linha, i, (numero + 1));
		}
	}
}

void vazioInsereQuadro(int sudoku[9][9], int matrizNum[9][9][9], int vazioLinha[9][9], int vazioColuna[9][9], int vazioQuadro[9][9], int numero)
{
	int q, k, linha, coluna, linhaInicioQuadro = 0, colunaInicioQuadro = 0, auxLinha, auxColuna;

	for (q = 0; q < 9; q++)
	{
		if (vazioQuadro[numero][q] == 1)//encontrou a única posição vazia
		{
			linha = 3 * linhaInicioQuadro;
			coluna = 3 * colunaInicioQuadro;
			auxLinha = 0;
			auxColuna = 0;

			k = 0;
			while (matrizNum[numero][linha + auxLinha][coluna + auxColuna] != 0 && k < 9)
			{
				//printf("....... q(%d, %d) -> [%d, %d]\n", linhaInicioQuadro, colunaInicioQuadro, linha + auxLinha, coluna + auxColuna);//printf para visualização e teste
				andaQuadro(&auxLinha, &auxColuna);
				k++;
			}

			//printf("vazioInsereQuadro sudoku[%d, %d] <= %d\n", linha + auxLinha, coluna + auxColuna, (numero + 1));//para visualização e teste
			insere(sudoku, matrizNum, vazioLinha, vazioColuna, vazioQuadro, linha + auxLinha, coluna + auxColuna, (numero + 1));
		}
		andaQuadro(&linhaInicioQuadro, &colunaInicioQuadro);//o movimento de posições em um quadro 3 x 3 é transformado no movimento entre quadro ao se multiplicar os índices por 3
	}
}

//======================================================================================================================================

int vazioL(int vazioLinha[9][9])
{
	int i, j;

	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			if (vazioLinha[i][j] == 1)
				return true;
		}
	}
	return false;
}

int vazioC(int vazioColuna[9][9])
{
	int i, j;

	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			if (vazioColuna[i][j] == 1)
				return true;
		}
	}
	return false;
}

int vazioQ(int vazioQuadro[9][9])
{
	int i, j;

	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			if (vazioQuadro[i][j] == 1)
				return true;
		}
	}
	return false;
}

//======================================================================================================================================

void vazioInsereTudoLinha(int sudoku[9][9], int matrizNum[9][9][9], int vazioLinha[9][9], int vazioColuna[9][9], int vazioQuadro[9][9])
{
	int numero;

	while (vazioL(vazioLinha))
	{
		for (numero = 0; numero < 9; numero++)
		{
			//vazioInsereQuadro(sudoku, matrizNum, vazioLinha, vazioColuna, vazioQuadro, numero);
			vazioInsereLinha(sudoku, matrizNum, vazioLinha, vazioColuna, vazioQuadro, numero);
			//vazioInsereColuna(sudoku, matrizNum, vazioLinha, vazioColuna, vazioQuadro, numero);
		}
	}
}

void vazioInsereTudoColuna(int sudoku[9][9], int matrizNum[9][9][9], int vazioLinha[9][9], int vazioColuna[9][9], int vazioQuadro[9][9])
{
	int numero;

	while (vazioC(vazioColuna))
	{
		for (numero = 0; numero < 9; numero++)
		{
			//vazioInsereQuadro(sudoku, matrizNum, vazioLinha, vazioColuna, vazioQuadro, numero);
			//vazioInsereLinha(sudoku, matrizNum, vazioLinha, vazioColuna, vazioQuadro, numero);
			vazioInsereColuna(sudoku, matrizNum, vazioLinha, vazioColuna, vazioQuadro, numero);
		}
	}
}

void vazioInsereTudoQuadro(int sudoku[9][9], int matrizNum[9][9][9], int vazioLinha[9][9], int vazioColuna[9][9], int vazioQuadro[9][9])
{
	int numero;

	while (vazioQ(vazioQuadro))
	{
		for (numero = 0; numero < 9; numero++)
		{
			vazioInsereQuadro(sudoku, matrizNum, vazioLinha, vazioColuna, vazioQuadro, numero);
			//vazioInsereLinha(sudoku, matrizNum, vazioLinha, vazioColuna, vazioQuadro, numero);
			//vazioInsereColuna(sudoku, matrizNum, vazioLinha, vazioColuna, vazioQuadro, numero);
		}
	}
}

void vazioInsereTudo(int sudoku[9][9], int matrizNum[9][9][9], int vazioLinha[9][9], int vazioColuna[9][9], int vazioQuadro[9][9])
{
	while (vazioQ(vazioQuadro) || vazioL(vazioLinha) || vazioC(vazioColuna))
	{
		vazioInsereTudoQuadro(sudoku, matrizNum, vazioLinha, vazioColuna, vazioQuadro);
		vazioInsereTudoLinha(sudoku, matrizNum, vazioLinha, vazioColuna, vazioQuadro);
		vazioInsereTudoColuna(sudoku, matrizNum, vazioLinha, vazioColuna, vazioQuadro);
	}
}

//======================================================================================================================================

void quadroLinhaEspecial(int matrizNum[9][9][9], int indiceLinha, int indiceColuna, int num)//coluna deve ser a primeira posição
{
	int somaLinha[3], iDeslocamento, jDeslocamento, i, j, k, linha, coluna;

	deslocamentoQ1(indiceLinha, indiceColuna, &iDeslocamento, &jDeslocamento);
	linha = indiceLinha % 3;
	coluna = indiceColuna % 3;

	//printf("\n\n\n\ >>>> LINHA ESPECIAL\nNUMERO %d   POSICAO[%d,%d] <<<<<<<<\n\n", num + 1, indiceLinha, indiceColuna);//printf para visualização e teste

	for (j = 0; j < 3; j++)
	{
		somaLinha[j] = 0;//soma dos valores de matrizNum para cada coluna é inicializado com 0
						 //printf("somaLinha[%d] = 0\n", j);//printf para visualização e teste
	}

	for (i = 0; i < 3; i++)//varre o quadro(3 colunas)
	{
		for (j = 0; j < 3; j++)//varre cada coluna
		{
			somaLinha[i] += matrizNum[num][linha + iDeslocamento][coluna + jDeslocamento];//soma dos valores de matrizNum para cada linha do quadro
																						  //printf("somaLinha[%d] += matrizNum[%d][%d][%d](%d)\n", i, num + 1, linha + iDeslocamento, coluna + jDeslocamento, matrizNum[num][linha + iDeslocamento][coluna + jDeslocamento]);//printf para visualização e teste
			andaQuadro(&linha, &coluna);//move para a próxima posição do quadro
										//printf("\nandaQuadro andou para [%d, %d]\n\n", linha, coluna);//printf para visualização e teste
		}

		for (j = 0; j < 3; j++)
		{
			//printf("\nsomaLinha[%d] = %d / somaLinha[%d] = %d/ somaLinha[%d] = %d\n\n", j % 3, somaLinha[j % 3], (j + 1) % 3, somaLinha[(j + 1) % 3], (j + 2) % 3, somaLinha[(j + 2) % 3]);//printf para visualização e test
		}
	}

	coluna = indiceColuna;
	//printf("COLUNA: %d\n", coluna);
	//passa coluna ao quadro "à direita"
	anda(&coluna, 0, 8);
	anda(&coluna, 0, 8);
	anda(&coluna, 0, 8);
	//printf("COLUNA: %d\n", coluna);

	for (j = 0; j < 3; j++)
	{
		if (somaLinha[j % 3] < 3 && somaLinha[(j + 1) % 3] == 3 && somaLinha[(j + 2) % 3] == 3)
		{
			//printf("\nsomaLinha[%d] < 3 e somaLinha[%d/%d] == 3\n\n", j % 3, (j + 1) % 3, (j + 2) % 3);//printf para visualização e teste

			for (k = 0; k < 6; k++)
			{
				matrizNum[num][(j % 3) + iDeslocamento][coluna] = 1;
				//printf("\n=====> matrizNum[%d][%d][%d] = 1\n", num + 1, (j % 3) + iDeslocamento, coluna);//printf para visualização e teste
				anda(&coluna, 0, 8);
			}
		}
	}
}

void quadroColunaEspecial(int matrizNum[9][9][9], int indiceLinha, int indiceColuna, int num)//linha deve ser a primeira posição
{
	int somaColuna[3], iDeslocamento, jDeslocamento, i, j, k, linha, coluna;

	deslocamentoQ1(indiceLinha, indiceColuna, &iDeslocamento, &jDeslocamento);
	linha = indiceLinha % 3;
	coluna = indiceColuna % 3;

	//printf("\n\n\n\ >>>>> COLUNA ESPECIAL\nNUMERO %d   POSICAO[%d,%d] <<<<<<<<\n\n", num + 1, indiceLinha, indiceColuna);//printf para visualização e teste

	for (j = 0; j < 3; j++)
	{
		somaColuna[j] = 0;//soma dos valores de matrizNum para cada coluna é inicializado com 0
						  //printf("somaColuna[%d] = 0\n", j);//printf para visualização e teste
	}

	for (i = 0; i < 3; i++)//varre o quadro(3 colunas)
	{
		for (j = 0; j < 3; j++)//varre cada coluna
		{
			somaColuna[j] += matrizNum[num][linha + iDeslocamento][coluna + jDeslocamento];//soma dos valores de matrizNum para cada linha do quadro
																						   //printf("somaColuna[%d] += matrizNum[%d][%d][%d](%d)\n", j, num + 1, linha + iDeslocamento, coluna + jDeslocamento, matrizNum[num][linha + iDeslocamento][coluna + jDeslocamento]);//printf para visualização e teste
			andaQuadro(&linha, &coluna);//move para a próxima posição do quadro
										//printf("\nandaQuadro andou para [%d, %d]\n\n", linha, coluna);//printf para visualização e teste
		}

		for (j = 0; j < 3; j++)
		{
			//printf("\nsomaColuna[%d] = %d / somaColuna[%d] = %d/ somaColuna[%d] = %d\n\n", j % 3, somaColuna[j % 3], (j + 1) % 3, somaColuna[(j + 1) % 3], (j + 2) % 3, somaColuna[(j + 2) % 3]);//printf para visualização e test
		}
	}

	linha = indiceLinha;
	//printf("LINHA: %d\n", linha);
	//passa linha ao quadro "abaixo"
	anda(&linha, 0, 8);
	anda(&linha, 0, 8);
	anda(&linha, 0, 8);
	//printf("LINHA: %d\n", linha);

	for (j = 0; j < 3; j++)
	{
		if (somaColuna[j % 3] < 3 && somaColuna[(j + 1) % 3] == 3 && somaColuna[(j + 2) % 3] == 3)
		{
			//printf("\nsomaColuna[%d] < 3 e somaColuna[%d/%d] == 3\n\n", j % 3, (j + 1) % 3, (j + 2) % 3);//printf para visualização e teste

			for (k = 0; k < 6; k++)
			{
				matrizNum[num][linha][(j % 3) + jDeslocamento] = 1;
				//printf("\n=====> matrizNum[%d][%d][%d] = 1\n", num + 1, linha, (j % 3) + jDeslocamento);//printf para visualização e teste
				anda(&linha, 0, 8);
			}
		}
	}
}

void quadroEspecial(int matrizNum[9][9][9])
{
	int linha = 0, coluna = 0, k, num, indiceLinha, indiceColuna;

	//printf("\nQuadro Especial\n");
	for (num = 0; num < 9; num++)
	{
		for (k = 0; k < 9; k++)//anda por todos os quadros
		{
			indiceLinha = linha * 3;//transforma o movimento em um quadro 3 x 3 em movimento entre quadros
			indiceColuna = coluna * 3;//transforma o movimento em um quadro 3 x 3 em movimento entre quadros

									  //para cada quadro, verifica se possui uma linha ou coluna especial
			quadroLinhaEspecial(matrizNum, indiceLinha, indiceColuna, num);
			quadroColunaEspecial(matrizNum, indiceLinha, indiceColuna, num);
			andaQuadro(&linha, &coluna);//movimento em um quadro 3 x 3
		}
	}
}
//======================================================================================================================================

void verificaEspaco(int sudoku[9][9], int matrizNum[9][9][9], int vazioLinha[9][9], int vazioColuna[9][9], int vazioQuadro[9][9])
{
	int i, j, k, count, valor;

	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			count = 9;

			for (k = 0; k < 9; k++)
			{
				//printf("1 - cont:%d\n", count);//teste
				if (matrizNum[k][i][j] == 0)
				{
					count--;
					valor = k;
					//printf("2 - cont:%d\n", count);//teste
				}
			}
			if (count == 8)
			{
				insere(sudoku, matrizNum, vazioLinha, vazioColuna, vazioQuadro, i, j, valor + 1);
				//printf("\n => insere %d na posicao [%d,%d]\n", valor + 1, i, j);//para teste
			}
		}
	}

}

void resolve(int sudoku[9][9], int matrizNum[9][9][9], int vazioLinha[9][9], int vazioColuna[9][9], int vazioQuadro[9][9])
{
	do
	{
		vazioInsereTudo(sudoku, matrizNum, vazioLinha, vazioColuna, vazioQuadro);
		quadroEspecial(matrizNum);
		verificaEspaco(sudoku, matrizNum, vazioLinha, vazioColuna, vazioQuadro);
	} while (vazioQ(vazioQuadro) || vazioL(vazioLinha) || vazioC(vazioColuna));
}

//=============================================================MAIN======================================================================

int main()
{
	int sudoku[9][9], matrizNum[9][9][9], vazioLinha[9][9], vazioColuna[9][9], vazioQuadro[9][9];

	iniciaSudoku(sudoku, matrizNum, vazioLinha, vazioColuna, vazioQuadro);

	resolve(sudoku, matrizNum, vazioLinha, vazioColuna, vazioQuadro);

	system("pause");
	return 0;
}


