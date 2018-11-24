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
	int nivel = (int) gtk_range_get_value(GTK_RANGE(widgetControleNivel));
	Imagem destino = alocarImagem(origem, nivel);
	
	//Kernel de Sharpen
    int kernel[3][3] = {{0,-1,0},
                        {-1, 5,-1},
                        {0,-1,0},
                        };
	
	for(j = 0; j < destino.w; j++) {
		for(i = 0; i < destino.h; i++) {
			destino.m[i][j][0] = origem.m[i][j][0];
			destino.m[i][j][1] = origem.m[i][j][1];
			destino.m[i][j][2] = origem.m[i][j][2];
		}
	}
		int cornew0=0;
		int cornew1=0;
		int cornew2=0;


		for(j = 1; j < origem.w-1; j++) {
			for(i = 1; i < origem.h-1; i++) {
				
				for( int y = 0; y < 3; y++ )
				{
					for( int x = 0; x < 3; x++ )
					{	
						printf("colune e linha :%d, %d\n", j+y, i+x );
						printf("cores: %d, %d, %d\n", cornew0, cornew1, cornew2 );
						int jy=j+y-1;
						int ix=i+x-1;
						printf("asd: %d, %d \n", jy, ix );
						if( jy < destino.w && jy >= 0 && ix < destino.h && ix >= 0)
						{
							cornew0=cornew0+(kernel[y][x]+destino.m[jy][ix][0]);
							cornew1=cornew1+(kernel[y][x]+destino.m[jy][ix][1]);
							cornew2=cornew2+(kernel[y][x]+destino.m[jy][ix][2]);
						}
						
					}
					

				}
				printf("cores que devem pintar :  %d, %d, %d\n", cornew0/4, cornew1/4, cornew2/4 );
				destino.m[i][j][0] = cornew0/4;
				destino.m[i][j][1] = cornew1/4;
				destino.m[i][j][2] = cornew2/4;
				cornew0=0;
				cornew1=0;
				cornew2=0;
			}
		
		}
	



	return destino;
}


