/*Grupo - Jogo Domino - COM - MA2A - Profº Julio - PUCSP - 2022
	Alice de Oliveira Duarte - RA 00319006
	Bruno dos Santos Torres Novo - RA 00320039
	Caio Pereira Guimaraes - RA 00318945
	Joao Pedro do Carmo Ribeiro - RA00319514
*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include "functions.h"
#include "model.c"



int main()
{
	setlocale(LC_ALL, "Portuguese"); //Pegando as informações dos carecteres de acordo com a região especificada

	visualArtGame(); //Mostra a abertura principal do jogo
	optionMenu(); //Mostra o Menu Principal do jogo

	return 0;
}