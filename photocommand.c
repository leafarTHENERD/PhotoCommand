#include <stdio.h>

#define MAX_COL 250
#define MAX_LIN 250

#define MAX_BITMAPS 20

struct bitmap{
	int linhas;
	int colunas;
	char nome[13];
	char dados[MAX_LIN][MAX_COL];
};
typedef struct bitmap bitmap;

void zero(char dados[MAX_LIN][MAX_COL], int colunas, int linhas){
	int i, j;
	for(i = 0; i < linhas; i++)
		for(j = 0; j < colunas; j++)
			dados[i][j] = 'O';
}

void colorir(char dados[MAX_LIN][MAX_COL], int x, int y, char cor, int colunas, int linhas){
	if(x <= colunas && y <= linhas)
		dados[y-1][x-1] = cor;
}

void colorir_linha_vertical(char dados[MAX_LIN][MAX_COL], int x, int y1, int y2, char c, int colunas, int linhas){
	int j;
	// corrigindo linhas com coordenadas invertidas (y2 < y1)
	if(y1 > y2){
		int aux = y2;
		y2 = y1;
		y1 = aux;
	}
	for(j = y1; j <= y2; j++)
		colorir(dados, x, j, c, colunas, linhas);
}

void colorir_linha_horizontal(char dados[MAX_LIN][MAX_COL], int x1, int x2, int y, char c, int colunas, int linhas){
	int i;
	// corrigindo linhas com coordenadas invertidas (x2 < x1)
	if(x1 > x2){
		int aux = x2;
		x2 = x1;
		x1 = aux;
	}
	for(i = x1; i <= x2; i++)
		colorir(dados, i, y, c, colunas, linhas);
}

void desenhar_retangulo(char dados[MAX_LIN][MAX_COL], int x1, int x2, int y1, int y2, char c, int colunas, int linhas){
	int i;
	// corrigindo retangulos com coordenadas invertidas (y2 < y1)
	// x2 < x1 é corrigido na funcao colorir_linha_horizontal
	if(y1 > y2){
		int aux = y2;
		y2 = y1;
		y1 = aux;
	}
	for(i = y1; i <= y2; i++)
		colorir_linha_horizontal(dados, x1,x2, i, c, colunas, linhas);
}

void desenhar_bitmap(bitmap bitmapsSalvos[MAX_BITMAPS], int numBitmaps){
	int bmpAtual;
	for(bmpAtual = 0; bmpAtual < numBitmaps; bmpAtual++){
		bitmap atual = bitmapsSalvos[bmpAtual];
		printf("%s\n", atual.nome);
		int i, j;
		for(i = 0; i < atual.linhas; i++){
			for(j = 0; j < atual.colunas; j++)
				printf("%c", atual.dados[i][j]);
			printf("\n");
		}
	}
}

int main(){
	bitmap bitmapAtual;
	bitmapAtual.nome[0] = '\0';

	bitmap bitmapsSalvos[MAX_BITMAPS];
	int numBitmaps = 0;

	int x1, x2, y1, y2;
	char c;
	char command;
	do{
		scanf("%c", &command);
		switch(command){
			case 'I':
				scanf("%d %d ", &bitmapAtual.colunas, &bitmapAtual.linhas);
				zero(bitmapAtual.dados, bitmapAtual.colunas, bitmapAtual.linhas);
				break;
			case 'Z':
				zero(bitmapAtual.dados, bitmapAtual.colunas, bitmapAtual.linhas);
				break;
			case 'C':
				scanf("%d %d %c", &x1, &y1, &c);
				colorir(bitmapAtual.dados, x1, y1, c, bitmapAtual.colunas, bitmapAtual.linhas);
				break;
			case 'V':
				scanf("%d %d %d %c", &x1, &y1, &y2, &c);
				colorir_linha_vertical(bitmapAtual.dados, x1, y1, y2, c, bitmapAtual.colunas, bitmapAtual.linhas);
				break;
			case 'H':
				scanf("%d %d %d %c", &x1, &x2, &y1, &c);
				colorir_linha_horizontal(bitmapAtual.dados, x1, x2, y1, c, bitmapAtual.colunas, bitmapAtual.linhas);
				break;
			case 'R':
				scanf("%d %d %d %d %c", &x1, &y1, &x2, &y2, &c);
				desenhar_retangulo(bitmapAtual.dados, x1, x2, y1, y2, c, bitmapAtual.colunas, bitmapAtual.linhas);
				break;
			case 'S':
				scanf("%12s", bitmapAtual.nome);
				bitmapsSalvos[numBitmaps] = bitmapAtual;
				numBitmaps++;
				bitmapAtual.nome[0] = '\0';
				break;
			case 'F':
				desenhar_bitmap(bitmapsSalvos, numBitmaps);
				break;
			default:
				for(;getchar()!='\n';);
		}
	}
	while( command != 'F');
	return 0;
}
