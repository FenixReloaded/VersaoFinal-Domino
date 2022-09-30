#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "functions.h"
#include "model.c"
#include <Windows.h>

extern bool jogador1; //Traz a boolean do Jogador 1 do controller.c
extern bool jogador2; //Traz a boolean do Jogador 2 do controller.c

//Abertura Visual do jogo
void visualArtGame() {

	printf("\n**************   Bem Vindo ao Dominos'   *************");
	printf("\n");
	printf("**             //\\                       //\\        **\n");
	printf("**            //  \\                     //. \\       **\n");
	printf("**           // .' \\                   //.   \\      **\n");
	printf("**          //\\' .'/                  //\\   '/      **\n");
	printf("**         //  \\' /                  //  \\ '/       **\n");
	printf("**        //    \\/                  // '  \\/        **\n");
	printf("**         \\'  '/                   \\  '  /         **\n");
	printf("**          \\  /                     \\ ' /          **\n");
	printf("**           \\/                       \\ /           **\n");
	printf("******************************************************");
	printf("\n\n");
}

//Mostra o menu dentro do jogo
int gameMenu() {

	struct stats_pieces pieces[28];
	struct stats_pieces jogador1[21];
	struct stats_pieces jogador2[21];
	struct stats_pieces buy[14];
	int i, j, statspieces, jogador;
	int counter = 0;
	int option = 0;

	printf("\n\n");
	printf("1 --> Jogar\n");
	printf("2 --> Comprar pe�a\n");
	printf("3 --> Passar a vez\n");
	printf("4 --> Ver pe�as do jogador\n");
	printf("5 --> Ver pe�as para comprar\n");
	printf("6 --> Finalizar o jogo\n");
	printf("7 --> Reiniciar o jogo\n");
	scanf("%d", &option);

	//Controlador de sele��o
	switch (option) {

		char escolha;

		case 1: //Jogar pe�a
			jogarPeca();
			break;

		case 2: //Comprar pe�a
			printf("Para qual jogador?");
			scanf("%d", &jogador);
			Sleep(1500);

			if (jogador == 1) {
				buyPiecesPlayer1();
			}else{
				buyPiecesPlayer2();
			}
			gameMenu();
			break;

		case 3: //Passar a vez
			passarVez();
			gameMenu();
			break;
		
		case 4: //Ver pe�as do jogador
			printf("De qual jogador?\t");
			scanf("%d", &jogador);
			Sleep(1500);

			if (jogador == 1) {
				showPiecesPlayer1();
			}else{
				showPiecesPlayer2();
			}
			gameMenu();
			break;

		case 5: //Ver Pe�as para compra
			showPiecesToBuy();
			gameMenu();
			break;

		case 6:
			printf("Tem certeza que deseja finalizar o jogo em andamento? (S/N)\n");
			scanf(" %c", &escolha);
			Sleep(1500);

			if (escolha == 'S') {
				printf("O jogo ser� finalizado\n\n");
				optionMenu();

			}
			else if (escolha == 'N') {
				gameMenu();
			}
			else {
				printf("A op��o selecionada � inv�lida! Selecione S para reiniciar e N para n�o reiniciar\n");
				gameMenu();
			}
			break;
			break;

		case 7:
			printf("Tem certeza que deseja reiniciar o jogo em andamento? (S/N)\n");
			scanf(" %c", &escolha);
			

			if (escolha == 'S') {
				printf("O jogo ser� reinicado\n\n");
				Sleep(1500);
				initializeGame(); //Inicia o jogo
				gameMenu(); //Mostra o menu do jogo

			}
			else if (escolha == 'N') {
				Sleep(1500);
				gameMenu();
			}
			else {
				printf("A op��o selecionada � inv�lida! Selecione S para reiniciar e N para n�o reiniciar\n");
				gameMenu();
			}
			break;

		default:
			optionMenu();
		break;
	}
}

//Ir� mostrar as pe�as do jogador em que for o turno correto
int showPiecesTable() {

	int k;
	int contadorPlayer1 = 0;
	int	contadorPlayer2 = 0;
	int id = 0;

	if (jogador1 == true) {
		printf("\nAgora � a vez do Jogador 1 jogar a pe�a!\n");
	}
	else {
		printf("\nAgora � a vez do Jogador 2 jogar a pe�a!\n");
	}

	printf("\n\n ID |      Jogador      |  Pe�a\n");
	printf("----+-------------------+------");

	for (k = 0; k < 28; k++) {
		if (jogador1 == true) {
			if (pieces[k].stats == '1') {		
				pieces[k].index = pieces->index;
				printf("\n{%d} | Pe�a do Jogador 1 | [%d|%d]", pieces->index, pieces[k].lado1, pieces[k].lado2);
				contadorPlayer1 = contadorPlayer1 + 1;
				id++;
				pieces->index = id;
			}
		}
		else if (jogador2 == true) {
			if (pieces[k].stats == '2') {
				pieces[k].index = pieces->index;
				printf("\n{%d} | Pe�a do Jogador 2 | [%d|%d]", pieces->index, pieces[k].lado1, pieces[k].lado2);
				contadorPlayer2 = contadorPlayer2 + 1;
				id++;
				pieces->index = id;
			}
		}
		else {
			printf("Jogador Invalido. Uma anormalidade foi encontrada.\n\n");
			showPiecesTable();
		}
	}

	printf("\n----+-------------------+------\n");

	if (jogador1 == true) {
		printf("\n");
		printf("Voc� ainda tem %d pe�as", contadorPlayer1);
		Sleep(1500);
	}
	else {
		printf("\n");
		printf("Voc� ainda tem %d pe�as", contadorPlayer2);
		Sleep(1500);
	}
}

//Mostra o menu principal do jogo
int optionMenu() {

	int option;

	printf("Selecione uma op��o para continuar: \n");
	printf("1 --> Iniciar o jogo em modo sozinho (contra a m�quina)\n");
	printf("2 --> Iniciar o jogo em modo multiplayer (2 jogadores)\n");
	printf("3 --> Retornar ao jogo em pause\n");
	printf("4 --> Manual de como jogar\n");
	printf("5 --> Salvar o jogo\n");
	printf("6 --> Carregar o jogo\n");
	printf("7 --> Sair do jogo\n");
	scanf("%d", &option);

	//Controlador de sele��o
	switch (option) {

		case 1: //Modo de Apenas 1 jogador
			printf("Modo de jogo contra a m�quina selecionado\n");
			printf("Carregando o jogo...\n\n");
			Sleep(1500);

			printf("ainda nao foi implementado\n\n");
			initializeGame(); //Inicia o jogo

			break;

		case 2: //Modo de 2 jogadores
			printf("Modo de jogo contra outro jogador selecionado\n");
			printf("Carregando o jogo...\n\n");
			Sleep(1500);

			initializeGame(); //Inicia o jogo
			gameMenu(); //Mostra o menu do jogo

			break;

		case 3: //Retornar ao jogo que foi pausado
			printf("ainda n�o implementado\n\n");
			optionMenu();
			break;

		case 4: //Regras do jogo
			printf("Como jogar o domino?\n\n");
			printf("Cada jogador recebe 7 pedras quando come�a a rodada. Se na partida houver menos de 4 jogadores, as pedras restantes ficam no dorme para serem compradas.\n");
			printf("O jogo come�a pelo jogador que tenha a pedra dobrada mais alta (se jogam 4 pessoas, sempre come�a quem tem o seis d�bre ou carrilh�o). No caso de que nenhum jogador tenha dobradas, come�ar� o jogador que tenha a pedra mais alta. A partir desse momento, os jogadores realizam suas jogadas, por turnos e no sentido anti-hor�rio.\n");
			printf("O jogador que come�a a partida leva vantagem. Este � um conceito importante para a estrat�gia do domino, pois o jogador ou dupla que come�a, normalmente, � o que leva a vantagem durante a partida.\n\n");
			Sleep(1500);

			printf("Desenvolvimento do jogo:\n\n");
			printf("Cada jogador, no seu turno, deve colocar uma das suas pedras em uma das 2 extremidades abertas, de forma que os pontos de um dos lados coincida com os pontos da extremidade onde est� sendo colocada. As dobradas s�o colocadas de maneira transversal para facilitar sua localiza��o.\n");
			printf("Quando o jogador coloca sua pedra sobre a mesa, seu turno se acaba e passa-se ao seguinte jogador.\n");
			printf("Se um jogador n�o puder jogar, dever� 'comprar' do dorme tantas pedras como forem necess�rias. Se n�o houver pedras no dorme, passar� o turno ao seguinte jogador.\n\n");
			Sleep(1500);
			
			printf("Rodada Seguinte\n\n");
			printf("Nas rodadas seguintes, o jogador que come�a o jogo � o seguinte da vez. Este pode come�ar o jogo com a pedra que quiser mesmo que n�o seja uma dobrada.\n\n");
			Sleep(1500);

			printf("Fim de jogo\n\n");
			printf("O jogo terminar� quando um jogador ou dupla conseguir a quantidade de pontos necess�rios para ganhar.\n\n");
			Sleep(1500);

			gameMenu();

			break;

		case 5: //Salva um jogo em execu��o para mais tarde
			printf("ainda n�o implementado\n\n");
			optionMenu();
			break;

		case 6: //Retomar um jogo j� iniciado
			printf("ainda n�o implementado\n\n");
			optionMenu();
			break;

		default: //Sair do jogo
			leaveGame(); //Faz o jogador sair do jogo atual
			break;
	};
}