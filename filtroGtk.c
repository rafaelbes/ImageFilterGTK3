#include <gtk/gtk.h>
#include <glib.h>
#include <stdlib.h>
#include <time.h>
#include "imagem.h"
#include "meufiltro.h"

GtkWidget *window, *image, *imagetextur;
GtkWidget *vbox, *hbox;
GtkWidget *label1, *label2;
char *nomeArquivo;
char *nomedaTextura;

void printImagemInfo(Imagem img) {
	printf("Imagem %d %d, ch %d\n", img.w, img.h, img.numCanais);
}

Imagem obterMatrizImagem() {
	int i, j, ch, rowstride;
	guchar ***m, *pixels, *p;
	Imagem img;
	
	GdkPixbuf *buffer = gtk_image_get_pixbuf(GTK_IMAGE(image));
	img.h = gdk_pixbuf_get_height(buffer);
	img.w = gdk_pixbuf_get_width(buffer);
	img.numCanais = gdk_pixbuf_get_n_channels(buffer);
	rowstride = gdk_pixbuf_get_rowstride(buffer);
	pixels = gdk_pixbuf_get_pixels(buffer);

	img.m = malloc(sizeof(guchar **)*img.h);
	for(i = 0; i < img.h; i++) {
		img.m[i] = malloc(sizeof(guchar *)*img.w);
		for(j = 0; j < img.w; j++)
			img.m[i][j] = malloc(sizeof(guchar)*img.numCanais);
	}

	for(i = 0; i < img.h; i++) {
		p = pixels + rowstride*i;
		for(j = 0; j < img.w; j++) {
			for(ch = 0; ch < img.numCanais; ch++) {
				img.m[i][j][ch] = *p;
				p++;
			}
		}
	}
	return img;
}


Imagem obterMatrizImagemTextura() {
	int i, j, ch, rowstride;
	guchar ***m, *pixels, *p;
	Imagem imgtext;
	
	GdkPixbuf *buffer = gtk_image_get_pixbuf(GTK_IMAGE(imagetextur));
	imgtext.h = gdk_pixbuf_get_height(buffer);
	imgtext.w = gdk_pixbuf_get_width(buffer);
	imgtext.numCanais = gdk_pixbuf_get_n_channels(buffer);
	rowstride = gdk_pixbuf_get_rowstride(buffer);
	pixels = gdk_pixbuf_get_pixels(buffer);

	imgtext.m = malloc(sizeof(guchar **)*imgtext.h);
	for(i = 0; i < imgtext.h; i++) {
		imgtext.m[i] = malloc(sizeof(guchar *)*imgtext.w);
		for(j = 0; j < imgtext.w; j++)
			imgtext.m[i][j] = malloc(sizeof(guchar)*imgtext.numCanais);
	}

	for(i = 0; i < imgtext.h; i++) {
		p = pixels + rowstride*i;
		for(j = 0; j < imgtext.w; j++) {
			for(ch = 0; ch < imgtext.numCanais; ch++) {
				imgtext.m[i][j][ch] = *p;
				p++;
			}
		}
	}
	return imgtext;
}

void carregarImagem(GtkWidget *widget, gpointer data) {
	GtkWidget *dialog = gtk_file_chooser_dialog_new("Abrir arquivo", GTK_WINDOW(window), GTK_FILE_CHOOSER_ACTION_OPEN, "_Cancel", GTK_RESPONSE_CANCEL, "_Open", GTK_RESPONSE_ACCEPT, NULL);

	if(gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
		nomeArquivo = gtk_file_chooser_get_filename( GTK_FILE_CHOOSER(dialog) );
		gtk_widget_destroy(dialog);
	}

	gtk_image_set_from_file(GTK_IMAGE(image), nomeArquivo);

	gtk_widget_queue_draw(image);

	gtk_label_set_text(GTK_LABEL(label1), "Imagem carregada");
	original = obterMatrizImagem();
}

void carregarTextura(GtkWidget *widget, gpointer data) {
	GtkWidget *dialog = gtk_file_chooser_dialog_new("Abrir arquivo de textura", GTK_WINDOW(window), GTK_FILE_CHOOSER_ACTION_OPEN, "_Cancel", GTK_RESPONSE_CANCEL, "_Open", GTK_RESPONSE_ACCEPT, NULL);

	if(gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
		nomedaTextura = gtk_file_chooser_get_filename( GTK_FILE_CHOOSER(dialog) );
		gtk_widget_destroy(dialog);
	}

	gtk_image_set_from_file(GTK_IMAGE(imagetextur), nomedaTextura);

	textura = obterMatrizImagemTextura(); 
}

void salvarImagem(GtkWidget *widget, gpointer data) {

	GtkWidget *dialog = gtk_file_chooser_dialog_new("Nome arquivo", (GtkWindow *) window, GTK_FILE_CHOOSER_ACTION_SAVE, "_Cancel", GTK_RESPONSE_CANCEL, "_Open", GTK_RESPONSE_ACCEPT, NULL);
	char *nomeDestino;

	if(gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
		nomeDestino = gtk_file_chooser_get_filename( GTK_FILE_CHOOSER(dialog) );
		gtk_widget_destroy(dialog);
		GdkPixbuf *buffer = gtk_image_get_pixbuf(GTK_IMAGE(image));
		gdk_pixbuf_save(buffer, nomeDestino, "jpeg", NULL, "quality", "100", NULL);
		gtk_label_set_text(GTK_LABEL(label1), "Imagem salva");
	}
	
}

void atualizarGtkImage(Imagem img) {
	int i, j, ch;

	GdkPixbuf *buffer = gtk_image_get_pixbuf(GTK_IMAGE(image));
	//GdkPixbuf *newbuffer = gdk_pixbuf_copy(buffer);
	GdkPixbuf *newbuffer = gdk_pixbuf_new(gdk_pixbuf_get_colorspace(buffer), gdk_pixbuf_get_has_alpha(buffer), gdk_pixbuf_get_bits_per_sample(buffer), img.w, img.h);
	//printf("Novo buffer com colorspace %d, alpha %d, bits/sample %d, width %d, height %d\n", gdk_pixbuf_get_colorspace(buffer), gdk_pixbuf_get_has_alpha(buffer), gdk_pixbuf_get_bits_per_sample(buffer), img.w, img.h);

	int rowstride = gdk_pixbuf_get_rowstride(newbuffer);

	guchar *pixels = gdk_pixbuf_get_pixels(newbuffer);
	guchar *p;
	for(i = 0; i < img.h; i++) {
		p = pixels + rowstride*i;
		for(j = 0; j < img.w; j++)
			for(ch = 0; ch < img.numCanais; ch++) {
				*p = img.m[i][j][ch];
				p++;
			}
	}

	gtk_image_set_from_pixbuf(GTK_IMAGE(image), newbuffer);
}

void funcaoRestaurar(GtkWidget *widget, gpointer data) {

	gtk_image_set_from_file(GTK_IMAGE(image), nomeArquivo);
	gtk_widget_queue_draw(image);
	gtk_label_set_text(GTK_LABEL(label1), "Imagem restaurada");
}

void funcaoAplicar(GtkWidget *widget, gpointer data) {

	funcaoRestaurar(NULL, NULL);
	//Imagem img = obterMatrizImagem(image);
	Imagem res = meuFiltro(original, textura);
	atualizarGtkImage(res);
	desalocarImagem(res);
	gtk_label_set_text(GTK_LABEL(label1), "Filtro aplicado");
}   


int main(int argc, char **argv) {


	//inicializa a semente de acordo com time
	srand(time(NULL));

	//inicializa o gtk
	gtk_init(&argc, &argv);

	//o argumento pode ser GTK_WINDOW_TOPLEVEL ou GTK_WINDOW_POPUP
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	//altera o titulo da janela
	gtk_window_set_title(GTK_WINDOW(window), "Aplicação de Filtros");
	
	//altera a posicao da janela para estar centralizada
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

	//altera o tamanho da janela
	gtk_window_set_default_size(GTK_WINDOW(window), 700, 500);

	//a janela pode ser redimensionada
	gtk_window_set_resizable(GTK_WINDOW(window), TRUE);

	//espessura da borda da janela (espaco sem widgets)
	gtk_container_set_border_width(GTK_CONTAINER(window), 20);

	//GtkVBox eh um container vertical para widgets
	//o primeiro argumento significa se os widgets sao igualmente distribuidos
	//o segundo argumento significa o espacamento entre os widgets em pixels
	vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

	//GtkHBox eh um container horizontal para widgets
	hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 3);

	//cria um botao com titulo carregar imagem
	GtkWidget *botaoCarregar = gtk_button_new_with_label("Carregar Imagem");

	//cria um botao com titulo carregar imagem de textura
	GtkWidget *botaoCarregarTextura = gtk_button_new_with_label("Carregar Textura");

	//cria um botao com titulo aplicar filtro
	GtkWidget *botaoAplicar = gtk_button_new_with_label("Aplicar Filtro");

	//cria um botao para restaurar imagem
	GtkWidget *botaoRestaurar = gtk_button_new_with_label("Restaurar Imagem");
	
	//cria um botao para salvar imagem
	GtkWidget *botaoSalvar = gtk_button_new_with_label("Salvar Imagem");

	//cria um frame para colocar as opcoes do filtro
	GtkWidget *frameFiltro = gtk_frame_new("Opções do filtro");

	//cria um scrolled window para inserir a imagem
	GtkWidget *scrolledWindow = gtk_scrolled_window_new(gtk_adjustment_new(0, 0, 100, 1, 1, 1), gtk_adjustment_new(0, 0, 100, 1, 1, 1));
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW (scrolledWindow), GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);

	inicializarWidgetsMeuFiltro();

	//altera o tamanho do botao carregar
	gtk_widget_set_size_request(botaoCarregar, 70, 30);
	//altera o tamanho do botao aplicar
	gtk_widget_set_size_request(botaoAplicar, 70, 30);

	//adiciona os botoes no container horizontal (hbox)
	gtk_container_add(GTK_CONTAINER(hbox), botaoCarregar);
	gtk_container_add(GTK_CONTAINER(hbox), botaoCarregarTextura);
	gtk_container_add(GTK_CONTAINER(hbox), botaoAplicar);
	gtk_container_add(GTK_CONTAINER(hbox), botaoRestaurar);
	gtk_container_add(GTK_CONTAINER(hbox), botaoSalvar);

	//cria labels
	label1 = gtk_label_new("Carregue uma imagem");
	label2 = gtk_label_new("Aplicação de Filtros");

	//adiciona um widget imagem vazio
	image = gtk_image_new();
	imagetextur = gtk_image_new();

	//adiciona os demais widgets no container vertical (vbox)
	//a funcao gtk_box_pack_start eh similar a gtk_container_add
	//mas com mais parametros
	gtk_box_pack_start(GTK_BOX(vbox), scrolledWindow, TRUE, TRUE, 0);
	gtk_container_add(GTK_CONTAINER(scrolledWindow), image);

	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), label1, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), label2, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), frameFiltro, FALSE, FALSE, 0);

	adicionarWidgetsMeuFiltro(frameFiltro);

	//adiciona o vbox na janela (window)
	gtk_container_add(GTK_CONTAINER(window), vbox);

	if(argc > 1) {
		nomeArquivo = argv[1];
		FILE *arq = fopen(nomeArquivo, "r");
		if(arq) {
			gtk_image_set_from_file(GTK_IMAGE(image), nomeArquivo);
			gtk_widget_queue_draw(image);
	
			gtk_label_set_text(GTK_LABEL(label1), "Imagem carregada");
			original = obterMatrizImagem();
			fclose(arq);
		}
	}
	//conecta o evento clicked do botaoCarregar a funcao carregarImagem
	g_signal_connect(G_OBJECT(botaoCarregar), "clicked", G_CALLBACK(carregarImagem), NULL);

	//conecta o evento clicked do botaoCarregarTextura a funcao carregarImagem
	g_signal_connect(G_OBJECT(botaoCarregarTextura), "clicked", G_CALLBACK(carregarTextura), NULL);

	//conecta o evento clicked do botaoAplicar a funcaoTeste (argv[0] eh o argumento)
	g_signal_connect(G_OBJECT(botaoAplicar), "clicked", G_CALLBACK(funcaoAplicar), NULL);
	
	//conecta o evento clicked do botaoRestaurar a funcaoRestaurar
	g_signal_connect(G_OBJECT(botaoRestaurar), "clicked", G_CALLBACK(funcaoRestaurar), NULL);

	//conecta o evento clicked do botaoSalvar a funcao salvarImagem
	g_signal_connect(G_OBJECT(botaoSalvar), "clicked", G_CALLBACK(salvarImagem), NULL);

	//conecta o evento destroy da janela a
	g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	//exibe a janela window e todos os widgets e assim sucessivamente
	gtk_widget_show_all(window);

	//main loop do gtk
	gtk_main();

	//so escreve quando finalizar a interface grafica
	printf("fim do programa\n");

	return 0;
}