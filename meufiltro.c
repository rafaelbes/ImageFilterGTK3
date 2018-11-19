#include "meufiltro.h"

void inicializarWidgetsMeuFiltro() {
	//widgets das opcoes de filtro
	widgetControleNivel = 	gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0, 30, 1);
	widgetMisturarCanais = gtk_check_button_new_with_label("Misturar canais");
	g_signal_connect(G_OBJECT(widgetControleNivel), "value-changed", G_CALLBACK(funcaoAplicar), NULL);
}

void adicionarWidgetsMeuFiltro(GtkWidget *container) {

	GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_container_set_border_width(GTK_CONTAINER(vbox), 20);
	gtk_container_add(GTK_CONTAINER(container), vbox);
	gtk_container_add(GTK_CONTAINER(vbox), widgetControleNivel);
	gtk_container_add(GTK_CONTAINER(vbox), widgetMisturarCanais);
}

Imagem meuFiltro(Imagem origem) {
	int i, j;
	Imagem destino = alocarImagem(origem);
	int nivel = (int) gtk_range_get_value(GTK_RANGE(widgetControleNivel));
	/*int ch1, ch2, ch3;

	ch1 = 0;
	ch2 = 1;
	ch3 = 2;
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widgetMisturarCanais))) {
		ch1 = rand()%3;
		ch2 = (ch1+1+rand()%2)%3;
		ch3 = 3 - ch2 - ch1;
	}
	*/
	for(j = 0; j < destino.w; j++) {
		for(i = 0; i < destino.h; i++) {
			destino.m[i][j][0] = origem.m[i][j][0];
			destino.m[i][j][1] = origem.m[i][j][1];
			destino.m[i][j][2] = origem.m[i][j][2];
		}
	}

	for(j = 0; j < destino.w; j++) {
		for(i = 0; i < destino.h; i=i+nivel) {
			int cor1=destino.m[i][j][0];
			int cor2=destino.m[i][j][1];
			int cor3=destino.m[i][j][2];
			
			for(int c=i; c<i+nivel; c++){
				destino.m[c][j][0] = cor1;
				destino.m[c][j][1] = cor2;
				destino.m[c][j][2] = cor3;
			}
			// destino.m[i][j][0] = 125;
			// destino.m[i][j][1] = 125;
			// destino.m[i][j][2] = 125;
		}
	}
	for(j = 0; j < destino.w; j=j+nivel) {
		for(i = 0; i < destino.h; i++) {
			int cor1=destino.m[i][j][0];
			int cor2=destino.m[i][j][1];
			int cor3=destino.m[i][j][2];
			
			for(int c=j; c<j+nivel; c++){
				destino.m[i][c][0] = cor1;
				destino.m[i][c][1] = cor2;
				destino.m[i][c][2] = cor3;
			}
			// destino.m[i][j][0] = 125;
			// destino.m[i][j][1] = 125;
			// destino.m[i][j][2] = 125;
		}
	}
	return destino;
}


