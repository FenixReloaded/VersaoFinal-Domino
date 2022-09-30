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

//Função que irá gerar as peças 
void generatePieces(){ 
	int i, j;
	int k = 0;

	for (i = 0; i <= 6; i++){ // irá gerar o lado 1 das peças
		for (j = i; j <= 6; j++){ // irá gerar o lado 2 das peças
			pieces[k].lado1 = i;
			pieces[k].lado2 = j;
			k++;
		}
	}
}

//Função que irá randomizar/aleatorizar as peças a cada nova jogada
void shufflePieces(){
	struct stats_pieces aux;
	int i, k;

	generatePieces(); // chamada da função que gera as peças, para que gerem peças aleatorias

	srand (time(NULL)); //função principal que faz o aleatório 

	for (i = 0; i < 28; i++){
		k = rand() % 28; // aleatorizando as 28 peças do jogo
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

	//Verifica quais peças estão sem status(dono)
	for (i = 0; i < 28; i++){
		pieces[i].stats = ' ';
	}

	shufflePieces(); //Emabaralha as peças do jogo

	//Dá ao jogador 1 sete peças totalmente aleatórias
	for (i = 0; i <= 6; i++){
		pieces[i].stats = '1';
	}

	//Dá ao jogador 2 sete peças totalmente aleatórias
	for (i = 7; i <= 13; i++){
		pieces[i].stats = '2';
	}

	//Renderiza o lado de cada peça distribuída
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

	//Verifica se o jogador 1 tem a maior peça
	if (pieces[j].stats == '1'){
		printf("\n\nPlayer 1 foi o primeiro a jogar na mesa.\n");
		jogador1 = false;
		jogador2 = true;
	}else{ //Caso não seja o primeiro jogador, então o jogador 2 joga
		if (pieces[j].stats == '2'){
			printf("\n\nPlayer 2 foi o primeiro a jogar na mesa.\n");
			jogador1 = true;
			jogador2 = false;
		}
	}
	table[0].lado1 = aux.lado1; //Lado esquerdo da última peça jogada
	table[0].lado2 = aux.lado2; //Lado direito da última peça jogada

	pieces[j].stats = 'm';

	//Renderiza a smesa do jogo
	printf("------------------------------\n");
	printf("------------------------------\n");
	printf("||                          ||\n");
	printf("||      MESA - [%d|%d]        ||\n", table[0].lado1, table[0].lado2);
	printf("||                          ||\n");
	printf("------------------------------\n");
	printf("------------------------------\n");

	showPiecesTable(); //Mostra as peças do jogo
}

//O Jogador 1 comprará uma peça
void buyPiecesPlayer1(){
	int k;

	//Verifica o status da peça do jogador 1 e realiza a compra
	for (k = 13; k < 28; k++) {
		if (pieces[k].stats == ' ') {
			pieces[k].stats = '1';
			k = 28;
		}
	}

	//Informa o Jogador 1 da Compra da peça realizada com sucesso
	printf("Jogador 1 comprou!\n");
	
}

//O Jogador 1 terá suas peças reveladas
int showPiecesPlayer1(){
	int k, contador;
	char selecao;
	
	//Pergunta se o Jogador 1 está pronto para visualizar as peças
	printf("O jogador 1 esta pronto para mostrar as pecas?(S/N)\t");
	scanf(" %c", &selecao);

	//Se a opção selecionada for sim
	if(selecao == 'S'){
		for (k = 0; k < 28; k++) {
			if (pieces[k].stats == '1') {
				printf("Peças do jogador 1 são: {%d} [%d|%d]", pieces->index, pieces[k].lado1, pieces[k].lado2);
				printf("\n");
			}
			contador = k;
		}
		printf("\n");
		
	}
	//Caso seja não
	else if(selecao == 'N'){
		showPiecesPlayer1();
	}
	//Caso nenhuma opção válida seja selecionada
	else {
		printf("Selecao invalida, insira novamente!\n");
		showPiecesPlayer1();
	}

}

//O Jogador 2 comprará uma peça
void buyPiecesPlayer2(){
	int k, contador;

	//Verifica o status da peça do jogador 2 e realiza a compra
	for (k = 13; k < 28; k++) {
		if (pieces[k].stats == ' ') {
			pieces[k].stats = '2';
			k = 28;
		}
		contador = k;
	}

	//Informa o Jogador 2 da Compra da peça realizada com sucesso
	printf("Jogador 2 comprou!\n");
}

//O Jogador 2 terá suas peças reveladas
int showPiecesPlayer2(){
	int k;
	char selecao;

	//Pergunta se o Jogador 2 está pronto para visualizar as peças
	printf("O jogador 2 esta pronto para mostrar as pecas?(S/N)\t");
	scanf(" %c", &selecao);

	//Se a opção selecionada for sim
	if (selecao == 'S') {
		for (k = 0; k < 28; k++) {
			if (pieces[k].stats == '2') {
				printf("Peças do jogador 2 são: {%d}  [%d|%d]", pieces->index, pieces[k].lado1, pieces[k].lado2);
				printf("\n");
			}
		}
		printf("\n");
	}
	//Caso seja não
	else if (selecao == 'N') {
		showPiecesPlayer2();
	}
	//Caso nenhuma opção válida seja selecionada
	else {
		printf("Selecao invalida, insira novamente!\n");
		showPiecesPlayer2();
	}
}

//Mostra todas as peças que estão disponíveis para compra
void showPiecesToBuy(){
	int k;

	//Carrega todas as peças que não estiverem nenhuma stats(dono) e mostra para os jogadores
	for (k = 0; k < 28; k++) {
		if (pieces[k].stats == ' ') {
			printf("Peças para comprar: [%d|%d]", pieces[k].lado1, pieces[k].lado2);
			printf("\n\n");
		}
	}
	printf("\n");
}

//Os jogadores poderão jogar uma peça na mesa
int jogarPeca() {
	int k = 0;

	if (jogador1 == true) {

		printf("Qual peça você deseja jogar na mesa?\n");
		scanf("%d", &pieces->index);

		printf("Peça selecionada: {%d} [%d|%d]", pieces->index, pieces[k].lado1, pieces[k].lado2);

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

		printf("Qual peça você deseja jogar na mesa?\n");
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

	printf("Você realmente deseja sair do jogo? (S/N)\t");
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
		printf("Opção Inválida! Levando você para o menu do jogo...\n\n");
		Sleep(1500);
		optionMenu();
	}
}
 