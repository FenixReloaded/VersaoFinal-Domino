#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "functions.h"
#include "model.c"
#include <Windows.h>

//Vez do Jogador
bool jogador1 = false;
bool jogador2 = false;

//Fun��o que ir� gerar as pe�as 
void generatePieces(){ 
	int i, j;
	int k = 0;

	for (i = 0; i <= 6; i++){ // ir� gerar o lado 1 das pe�as
		for (j = i; j <= 6; j++){ // ir� gerar o lado 2 das pe�as
			pieces[k].lado1 = i;
			pieces[k].lado2 = j;
			k++;
		}
	}
}

//Fun��o que ir� randomizar/aleatorizar as pe�as a cada nova jogada
void shufflePieces(){
	struct stats_pieces aux;
	int i, k;

	generatePieces(); // chamada da fun��o que gera as pe�as, para que gerem pe�as aleatorias

	srand (time(NULL)); //fun��o principal que faz o aleat�rio 

	for (i = 0; i < 28; i++){
		k = rand() % 28; // aleatorizando as 28 pe�as do jogo
		aux = pieces[i];
		pieces[i] = pieces[k];
		pieces[k] = aux;
	}
}

//Inicializa o jogo
void initializeGame(){
	int j;
	int i = 0;

	aux.stats = ' ';
	aux.lado1 = 0; 
	aux.lado2 = 1;

	//Verifica quais pe�as est�o sem status(dono)
	for (i = 0; i < 28; i++){
		pieces[i].stats = ' ';
	}

	shufflePieces(); //Emabaralha as pe�as do jogo

	//D� ao jogador 1 sete pe�as totalmente aleat�rias
	for (i = 0; i <= 6; i++){
		pieces[i].stats = '1';
	}

	//D� ao jogador 2 sete pe�as totalmente aleat�rias
	for (i = 7; i <= 13; i++){
		pieces[i].stats = '2';
	}

	//Renderiza o lado de cada pe�a distribu�da
	for (i = 0; i <= 13; i++){
		if (pieces[i].lado1 == pieces[i].lado2){
			if (aux.lado1 <= pieces[i].lado1){
				aux = pieces[i];
				j = i;
			}else{
				if (aux.lado1 + aux.lado2 <= pieces[i].lado1 + pieces[i].lado2){
					if (aux.lado1 || aux.lado2 > pieces[i].lado1 || pieces[i].lado2){
						aux = pieces[i];
						j = i;
					}
				}
			}
		}
	}

	//Verifica se o jogador 1 tem a maior pe�a
	if (pieces[j].stats == '1'){
		printf("\n\nPlayer 1 foi o primeiro a jogar na mesa.\n");
		jogador1 = false;
		jogador2 = true;
	}else{ //Caso n�o seja o primeiro jogador, ent�o o jogador 2 joga
		if (pieces[j].stats == '2'){
			printf("\n\nPlayer 2 foi o primeiro a jogar na mesa.\n");
			jogador1 = true;
			jogador2 = false;
		}
	}
	table[0].lado1 = aux.lado1; //Lado esquerdo da �ltima pe�a jogada
	table[0].lado2 = aux.lado2; //Lado direito da �ltima pe�a jogada

	pieces[j].stats = 'm';

	//Renderiza a smesa do jogo
	printf("------------------------------\n");
	printf("------------------------------\n");
	printf("||                          ||\n");
	printf("||      MESA - [%d|%d]        ||\n", table[0].lado1, table[0].lado2);
	printf("||                          ||\n");
	printf("------------------------------\n");
	printf("------------------------------\n");

	showPiecesTable(); //Mostra as pe�as do jogo
}

//O Jogador 1 comprar� uma pe�a
void buyPiecesPlayer1(){
	int k;

	//Verifica o status da pe�a do jogador 1 e realiza a compra
	for (k = 13; k < 28; k++) {
		if (pieces[k].stats == ' ') {
			pieces[k].stats = '1';
			k = 28;
		}
	}

	//Informa o Jogador 1 da Compra da pe�a realizada com sucesso
	printf("Jogador 1 comprou!\n");
	
}

//O Jogador 1 ter� suas pe�as reveladas
int showPiecesPlayer1(){
	int k, contador;
	char selecao;
	
	//Pergunta se o Jogador 1 est� pronto para visualizar as pe�as
	printf("O jogador 1 esta pronto para mostrar as pecas?(S/N)\t");
	scanf(" %c", &selecao);

	//Se a op��o selecionada for sim
	if(selecao == 'S'){
		for (k = 0; k < 28; k++) {
			if (pieces[k].stats == '1') {
				printf("Pe�as do jogador 1 s�o: {%d} [%d|%d]", pieces->index, pieces[k].lado1, pieces[k].lado2);
				printf("\n");
			}
			contador = k;
		}
		printf("\n");
		
	}
	//Caso seja n�o
	else if(selecao == 'N'){
		showPiecesPlayer1();
	}
	//Caso nenhuma op��o v�lida seja selecionada
	else {
		printf("Selecao invalida, insira novamente!\n");
		showPiecesPlayer1();
	}

}

//O Jogador 2 comprar� uma pe�a
void buyPiecesPlayer2(){
	int k, contador;

	//Verifica o status da pe�a do jogador 2 e realiza a compra
	for (k = 13; k < 28; k++) {
		if (pieces[k].stats == ' ') {
			pieces[k].stats = '2';
			k = 28;
		}
		contador = k;
	}

	//Informa o Jogador 2 da Compra da pe�a realizada com sucesso
	printf("Jogador 2 comprou!\n");
}

//O Jogador 2 ter� suas pe�as reveladas
int showPiecesPlayer2(){
	int k;
	char selecao;

	//Pergunta se o Jogador 2 est� pronto para visualizar as pe�as
	printf("O jogador 2 esta pronto para mostrar as pecas?(S/N)\t");
	scanf(" %c", &selecao);

	//Se a op��o selecionada for sim
	if (selecao == 'S') {
		for (k = 0; k < 28; k++) {
			if (pieces[k].stats == '2') {
				printf("Pe�as do jogador 2 s�o: {%d}  [%d|%d]", pieces->index, pieces[k].lado1, pieces[k].lado2);
				printf("\n");
			}
		}
		printf("\n");
	}
	//Caso seja n�o
	else if (selecao == 'N') {
		showPiecesPlayer2();
	}
	//Caso nenhuma op��o v�lida seja selecionada
	else {
		printf("Selecao invalida, insira novamente!\n");
		showPiecesPlayer2();
	}
}

//Mostra todas as pe�as que est�o dispon�veis para compra
void showPiecesToBuy(){
	int k;

	//Carrega todas as pe�as que n�o estiverem nenhuma stats(dono) e mostra para os jogadores
	for (k = 0; k < 28; k++) {
		if (pieces[k].stats == ' ') {
			printf("Pe�as para comprar: [%d|%d]", pieces[k].lado1, pieces[k].lado2);
			printf("\n\n");
		}
	}
	printf("\n");
}

//Os jogadores poder�o jogar uma pe�a na mesa
int jogarPeca() {
	int k = 0;

	if (jogador1 == true) {

		printf("Qual pe�a voc� deseja jogar na mesa?\n");
		scanf("%d", &pieces->index);

		printf("Pe�a selecionada: {%d} [%d|%d]", pieces->index, pieces[k].lado1, pieces[k].lado2);

		for(k = 0; k < 28; k++){
			if (table[0].lado1 == aux.lado1) {
				if (pieces[k].stats == '1') {
					pieces[k].stats = 'm';
				}
			}
			else if (table[0].lado2 == aux.lado2) {
				if (pieces[k].stats == '1') {
					pieces[k].stats = 'm';
				}
			}
			else {
				printf("Jogada Invalida. Tente Novamente\n\n");
			}
		}

		jogador1 = false;
		jogador2 = true;
	}
	else {

		printf("Qual pe�a voc� deseja jogar na mesa?\n");
		scanf("%d", &pieces->index);

		for (k = 0; k < 28; k++) {
			if (table[0].lado1 == aux.lado1) {
				if (pieces[k].stats == '2') {
					pieces[k].stats = 'm';
				}
			}
			else if (table[0].lado2 == aux.lado2) {
				if (pieces[k].stats == '2') {
					pieces[k].stats = 'm';
				}
			}
			else {
				printf("Jogada Invalida. Tente Novamente\n\n");
			}
		}

		jogador1 = true;
		jogador2 = false;
	}

	gameMenu();
}

void passarVez() {
	if (jogador1 == true) {
		printf("\nO Jogador 1 passou a vez!\n");
		jogador1 = false;
		jogador2 = true;
		showPiecesTable();
	}
	else {
		printf("\nO Jogador 2 passou a vez!\n");
		jogador1 = true;
		jogador2 = false;
		showPiecesTable();
	}
}

//Mostra aviso e sai do jogo
void leaveGame(){

	char confirmacao;

	printf("Voc� realmente deseja sair do jogo? (S/N)\t");
	scanf(" %c", &confirmacao);

	if (confirmacao == 'S') {
		printf("\n");
		printf("Obrigado por jogar Dominos'!\n");
		printf("Saindo do jogo...\n\n");
		Sleep(1500);
		exit(1);
	}
	else if (confirmacao == 'N') {
		printf("Carregando o menu do jogo. Por favor aguarde...\n\n");
		Sleep(1500);
		optionMenu();
	}
	else {
		printf("Op��o Inv�lida! Levando voc� para o menu do jogo...\n\n");
		Sleep(1500);
		optionMenu();
	}
}
 