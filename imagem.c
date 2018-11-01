#include "imagem.h"

Imagem alocarImagem(Imagem referencia) {
	Imagem img;
	int i, j;
	img.h = referencia.h;
	img.w = referencia.w;
	img.numCanais = referencia.numCanais;
	img.m = malloc(sizeof(guchar **)*img.h);
	for(i = 0; i < img.h; i++) {
		img.m[i] = malloc(sizeof(guchar *)*img.w);
		for(j = 0; j < img.w; j++)
			img.m[i][j] = malloc(sizeof(guchar)*img.numCanais);
	}
	return img;
}

void desalocarImagem(Imagem referencia) {
	for(int i = 0; i < referencia.h; i++) {
		for(int j = 0; j < referencia.w; j++) {
			free(referencia.m[i][j]);
		}
		free(referencia.m[i]);
	}
	free(referencia.m);
}

