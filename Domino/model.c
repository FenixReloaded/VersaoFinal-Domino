struct stats_pieces {
	int lado1;
	int lado2;
	int jogador1;
	int jogador2;
	char stats;
	int buy;
	int index;
} pieces[28], aux;

struct stats_table {
	int lado1;
	int lado2;
	int proximo;
}table[28];

char jogador;