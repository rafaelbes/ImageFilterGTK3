#ifndef IMAGEM_H
#define IMAGEM_H

#include <gtk/gtk.h>
#include <glib.h>
#include <stdlib.h>

typedef struct Imagem {
	unsigned char ***m;
	int w;
	int h;
	int numCanais;
} Imagem;

// typedef struct GdkRGBA{
//   gdouble red;
//   gdouble green;
//   gdouble blue;
//   gdouble alpha;
// } GdkRGBA;

typedef struct _GtkColorChooser GtkColorChooser;


Imagem original, resultado, textura;
Imagem alocarImagem(Imagem referencia);
Imagem alocarImagemDimensao(int w, int h, int numCanais);
void desalocarImagem(Imagem referencia);

#endif
