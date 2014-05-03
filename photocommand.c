#include <stdio.h>

#define MAX_COL 250
#define MAX_LIN 250

int colunas = 0;
int linhas = 0;

void zero(char bitmap[MAX_LIN][MAX_COL]){
	int i, j;
	for(i = 0; i < linhas; i++)
		for(j = 0; j < colunas; j++)
			bitmap[i][j] = 'O';
}

void colorir(char bitmap[MAX_LIN][MAX_COL], int x, int y, char cor){
	if(x < linhas && y < colunas)
		bitmap[x-1][y-1] = cor;
}

void colorir_linha_vertical(char bitmap[MAX_LIN][MAX_COL], int x, int y1, int y2, char c){
	int j;
	for(j = y1; j <= y2; j++)
		colorir(bitmap, x, j, c);
}

void colorir_linha_horizontal(char bitmap[MAX_LIN][MAX_COL], int x1, int x2, int y, char c){
	int i;
	for(i = x1; i <= x2; i++)
		colorir(bitmap, i, y, c);
}

void desenhar_retangulo(char bitmap[MAX_LIN][MAX_COL], int x1, int x2, int y1, int y2, char c){
	int i;
	for(i = y1; i <= y2; i++)
		colorir_linha_horizontal(bitmap, x1,x2, i, c);
}

void desenhar_bitmap(char bitmap[MAX_LIN][MAX_COL], char *nome, int lin, int col){
	printf("%s\n", nome);
	int i, j;
	for(i = 0; i < lin; i++){
		for(j = 0; j < col; j++)
			printf("%c", bitmap[j][i]);
		printf("\n");
	}
		
}

int main(){
	char bitmap[MAX_LIN][MAX_COL];
	char nome[13];
	nome[0]='\0';
	char command;

	int x1, x2, y1, y2;
	char c;
	do{
		scanf("%c", &command);
		switch(command){
			case 'I':
				scanf("%d %d ", &colunas, &linhas);
				zero(bitmap);
				break;
			case 'Z':
				zero(bitmap);
				break;
			case 'C':
				scanf("%d %d %c", &x1, &y1, &c);
				colorir(bitmap, x1, y1, c);
				break;
			case 'V':
				scanf("%d %d %d %c", &x1, &y1, &y2, &c);
				colorir_linha_vertical(bitmap, x1, y1, y2, c);
				break;
			case 'H':
				scanf("%d %d %d %c", &x1, &x2, &y1, &c);
				colorir_linha_horizontal(bitmap, x1, x2, y1, c);
				break;
			case 'R':
				scanf("%d %d %d %d %c", &x1, &y1, &x2, &y2, &c);
				desenhar_retangulo(bitmap, x1, x2, y1, y2, c);
				break;
			case 'S':
				scanf("%12s", nome);
				break;
			case 'F':
				desenhar_bitmap(bitmap, nome, linhas, colunas);
				break;
		}
	}
	while( command != 'F');
	return 0;
}
