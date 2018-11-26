#ifndef MEUFILTRO_H
#define MEUFILTRO_H

#include <gtk/gtk.h>
#include <glib.h>
#include <stdlib.h>
#include <time.h>
#include "imagem.h"

//declare aqui os seus widgets
GtkWidget *widgetControleTamanho;
GtkWidget *widgetControleDistancia;
GtkWidget *widgetcheckhorizontal;
GtkWidget *widgetcheckverticais;

GtkWidget *widgetColorRed;
GtkWidget *widgetColorBlue;
GtkWidget *widgetColorGreen;

GtkWidget *widgetLabelContTamanho;
GtkWidget *widgetLabelContDistancia;
GtkWidget *widgetLabelCorRed;
GtkWidget *widgetLabelCorBlue;
GtkWidget *widgetLabelCorGreen;

Imagem meuFiltro(Imagem origem, Imagem textura);
void inicializarWidgetsMeuFiltro();
void adicionarWidgetsMeuFiltro(GtkWidget *container);

//esta funcao esta implementada em filtroGtk.c, nao precisa alterar
void funcaoAplicar(GtkWidget *widget, gpointer data);

#endif


