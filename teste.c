#include <gtk/gtk.h>
#include <glib.h>

GtkWidget *window, *image;
GtkWidget *vbox, *valign, *hbox, *halign;
GtkWidget *label1, *label2;

char* get_file() {
	return NULL;
}

void carregarImagem(GtkWidget *widget, gpointer data)
{
	char *nomeArquivo;

	GtkWidget *dialog = gtk_file_chooser_dialog_new("Abrir arquivo", (GtkWindow *) window, GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT, NULL);

	if(gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
		nomeArquivo = gtk_file_chooser_get_filename( GTK_FILE_CHOOSER(dialog) );
		gtk_widget_destroy(dialog);
	}

	gtk_image_set_from_file(image, nomeArquivo);

	gtk_widget_queue_draw(image);

	gtk_label_set_text(GTK_LABEL(label1), "Imagem carregada");
}

void funcaoTeste(GtkWidget *widget, gpointer data) {
	char *s;
	s = (char *) data;
	gtk_label_set_text(GTK_LABEL(label1), s); 
}   


int main(int argc, char **argv) {

	//inicializa o gtk
	gtk_init(&argc, &argv);

	//mais detalhes sobre janelas em: https://developer.gnome.org/gtk3/stable/GtkWindow.html
	
	//o argumento pode ser GTK_WINDOW_TOPLEVEL ou GTK_WINDOW_POPUP
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	//altera o titulo da janela
	gtk_window_set_title(GTK_WINDOW(window), "Filtros de Imagens da turma ITP 2018.1");
	
	//altera a posicao da janela para estar centralizada
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

	//altera o tamanho da janela
	gtk_window_set_default_size(GTK_WINDOW(window), 700, 700);

	//a janela pode ser redimensionada
	gtk_window_set_resizable(GTK_WINDOW(window), TRUE);

	//espessura da borda da janela (espaco sem widgets)
	gtk_container_set_border_width(GTK_CONTAINER(window), 20);

	//GtkVBox eh um container vertical para widgets
	//o primeiro argumento significa se os widgets sao igualmente distribuidos
	//o segundo argumento significa o espacamento entre os widgets em pixels
	vbox = gtk_vbox_new(FALSE, 5);

	//GtkHBox eh um container horizontal para widgets
	hbox = gtk_hbox_new(TRUE, 3);

	//cria um botao com titulo carregar imagem
	GtkWidget *botaoCarregar = gtk_button_new_with_label("Carregar Imagem");

	//cria um botao com titulo aplicar filtro
	GtkWidget *botaoAplicar = gtk_button_new_with_label("Aplicar Filtro");

	//cria um botao so para testes
	GtkWidget *botaoTeste = gtk_button_new_with_label("Aplicar teste");

	//altera o tamanho do botao carregar
	gtk_widget_set_size_request(botaoCarregar, 70, 30);
	//altera o tamanho do botao aplicar
	gtk_widget_set_size_request(botaoAplicar, 70, 30);

	//adiciona os botoes no container horizontal (hbox)
	gtk_container_add(GTK_CONTAINER(hbox), botaoCarregar);
	gtk_container_add(GTK_CONTAINER(hbox), botaoAplicar);
	gtk_container_add(GTK_CONTAINER(hbox), botaoTeste);

	//cria labels
	label1 = gtk_label_new("Carregue uma imagem");
	label2 = gtk_label_new("Autores: turma de ITP 2018.1");

	//adiciona um widget imagem vazio
	image = gtk_image_new();

	//adiciona os demais widgets no container vertical (vbox)
	//a funcao gtk_box_pack_start eh similar a gtk_container_add
	//mas com mais parametros
	gtk_box_pack_start(GTK_BOX(vbox), image, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), label1, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), label2, FALSE, FALSE, 0);

	//adiciona o vbox na janela (window)
	gtk_container_add(GTK_CONTAINER(window), vbox);

	//conecta o evento clicked do botaoCarregar a funcao carregarImagem
	g_signal_connect(G_OBJECT(botaoCarregar), "clicked", G_CALLBACK(carregarImagem), NULL);

	//conecta o evento clicked do botaoTeste a funcaoTeste (argv[0] eh o argumento)
	g_signal_connect(G_OBJECT(botaoTeste), "clicked", G_CALLBACK(funcaoTeste), argv[0]);

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
