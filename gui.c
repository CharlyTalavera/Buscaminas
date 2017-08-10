#include <gtk/gtk.h>
#include <libintl.h>
#include <stdlib.h>
#include "buscaminas.h"
#define MENSAJE_DERROTA "¡Perdiste!"
#define MENSAJE_VICTORIA "¡GANASTE!"
#define show(x) gtk_statusbar_push (GTK_STATUSBAR(statusbar), 0, x)
#define WIDTH 250
#define HEIGHT 300


void show_board(int * campoMinado,GtkWidget *board){
  GtkWidget** buttons=g_object_get_data(G_OBJECT(board), "buttons");
  int *row,*column;
  gchar *new_label;
  for(int i=0;i<DIM*DIM;i++){
    row=g_object_get_data (G_OBJECT(buttons[i]), "row");
    column= g_object_get_data (G_OBJECT(buttons[i]), "column");
    if(ExisteMina((int(*)[])campoMinado,*row,*column))
      new_label=g_strdup_printf("%i",MINADO);
    else
      new_label=g_strdup_printf("%i",VACIO);
    gtk_button_set_label((GtkButton*)buttons[i],new_label);
  }
}

void check_move(char* campoExplorado,int* campoMinado, int* row, int* column,GtkButton* button, GtkWidget* board,GtkWidget* statusbar){
  if(campoInspeccionado((char(*)[DIM])campoExplorado,*row,*column))
    return;
  if(ExisteMina((int(*)[])campoMinado,*row,*column)){
    show_board(campoMinado,board);
    show(MENSAJE_DERROTA);
    return;
  }
  inspeccionar((char(*)[DIM])campoExplorado,*row,*column);
  gchar *aux=g_strdup_printf("%c",EXPLORADO);
  gtk_button_set_label(button,aux);
  if(verificarVictoria((int(*)[DIM])campoMinado,(char(*)[DIM])campoExplorado))
    show(MENSAJE_VICTORIA);
}

void on_button_clicked (GtkWidget *button, gpointer data){
   GtkWidget* board=data;
   GtkWidget* statusbar=g_object_get_data (G_OBJECT(board),"statusbar");
   int *column=  g_object_get_data (G_OBJECT(button), "column");
   int *row= g_object_get_data (G_OBJECT(button), "row");
   char *campoExplorado=g_object_get_data (G_OBJECT(board),"campoExplorado");
   int *campoMinado=g_object_get_data (G_OBJECT(board),"campoMinado");
   check_move(campoExplorado,campoMinado,row,column,(GtkButton*)button,board,statusbar);
}

int * get_pointer(int value){
  int * pointer_to_value=malloc(sizeof(int));
  * pointer_to_value=value;
  return pointer_to_value;
}

void fill_table(GtkWidget *board,GtkWidget *table1,GtkWidget* buttons[]){
  gint i=0;
  for (int x=0; x<DIM; x++)
    for (int y=0; y<DIM; y++,i++){
      int *column = get_pointer(x);
      int *row = get_pointer(y);
      gchar *aux=g_strdup_printf("%c",NO_EXPLORADO);
      buttons[i] = gtk_button_new_with_label (aux);
      gtk_grid_attach(GTK_GRID(table1),buttons[i], x,y,1,1);
      g_object_set_data (G_OBJECT(buttons[i]), "column", (gpointer) column);
      g_object_set_data (G_OBJECT(buttons[i]), "row", (gpointer) row);
      g_signal_connect(G_OBJECT(buttons[i]), "clicked", G_CALLBACK(on_button_clicked), board);
      g_free(aux);
    }

}
void refresh_table(GtkWidget *board,GtkWidget** buttons){
  char *campoExplorado=g_object_get_data (G_OBJECT(board),"campoExplorado");
  for(int i=0;i<DIM;i++){
    for(int j=0;j<DIM;j++){
      gchar *aux=g_strdup_printf("%c",((char(*)[DIM])campoExplorado)[i][j]);
      gtk_button_set_label(GTK_BUTTON(buttons[i+DIM*j]),aux);
    }
  }
}

void refresh_game(GtkWidget *button, gpointer data){
  GtkWidget* board=data;
  GtkWidget* statusbar=g_object_get_data (G_OBJECT(board),"statusbar");
  char *campoExplorado=g_object_get_data (G_OBJECT(board),"campoExplorado");
  GtkWidget **buttons=g_object_get_data (G_OBJECT(board),"buttons");
  int *campoMinado=g_object_get_data (G_OBJECT(board),"campoMinado");
  InicializarCampos((char(*)[])campoExplorado,(int(*)[])campoMinado);
  DibujarCampoMinado((int(*)[])campoMinado);
  refresh_table(board,buttons);
  show("Nueva Partida.");
}

void open_game(GtkWidget *button, gpointer data){
  GtkWidget* board=data;
  GtkWidget* statusbar=g_object_get_data (G_OBJECT(board),"statusbar");
  GtkWidget **buttons=g_object_get_data (G_OBJECT(board),"buttons");
  char *campoExplorado=g_object_get_data (G_OBJECT(board),"campoExplorado");
  int *campoMinado=g_object_get_data (G_OBJECT(board),"campoMinado");
  if (!cargar_partida((int(*)[])campoMinado, (char(*)[])campoExplorado)){
    show("Error al cargar partida.");
    return;
  }
  DibujarCampoMinado((int(*)[])campoMinado);
  refresh_table(board,buttons);
  show("Partida Cargada.");
}

void save_game(GtkWidget *button, gpointer data){
  GtkWidget* board=data;
  GtkWidget* statusbar=g_object_get_data (G_OBJECT(board),"statusbar");
  char *campoExplorado=g_object_get_data (G_OBJECT(board),"campoExplorado");
  int *campoMinado=g_object_get_data (G_OBJECT(board),"campoMinado");
  if(!guardar_partida((int(*)[])campoMinado, (char(*)[])campoExplorado))
    show("Error al guardar partida.");
  else
    show("Partida Guardada.");
}
void create_status_bar(GtkWidget* board, GtkWidget *statusbar){
    statusbar = gtk_statusbar_new ();
    //gtk_statusbar_set_has_resize_grip (GTK_STATUSBAR(statusbar), FALSE);
    gtk_statusbar_push (GTK_STATUSBAR(statusbar), 0, "¡Bienvenido!");
    gtk_box_pack_start (GTK_BOX (board), statusbar, FALSE, FALSE, 0);
    g_object_set_data(G_OBJECT(board),"statusbar",statusbar);
}

void create_toolbar(GtkWidget *board,GtkWidget *toolbar){
  GtkWidget* new_button,*save_button, *open_button;
  GtkWidget* new_icon=gtk_image_new_from_icon_name("gtk-new",GTK_ICON_SIZE_LARGE_TOOLBAR);
  GtkWidget* save_icon=gtk_image_new_from_icon_name("gtk-save",GTK_ICON_SIZE_LARGE_TOOLBAR);
  GtkWidget* open_icon=gtk_image_new_from_icon_name("gtk-open",GTK_ICON_SIZE_LARGE_TOOLBAR);
  toolbar = gtk_toolbar_new ();
  gtk_box_pack_start (GTK_BOX (board), toolbar, FALSE, FALSE, 0);
  gtk_toolbar_set_style (GTK_TOOLBAR (toolbar), GTK_TOOLBAR_BOTH);
  new_button = (GtkWidget*) gtk_tool_button_new(new_icon,"New");
  save_button = (GtkWidget*) gtk_tool_button_new(save_icon,"Save");
  open_button = (GtkWidget*) gtk_tool_button_new (open_icon,"Open");
  g_signal_connect(G_OBJECT(new_button), "clicked", G_CALLBACK(refresh_game), board);
  g_signal_connect(G_OBJECT(save_button), "clicked", G_CALLBACK(save_game), board);
  g_signal_connect(G_OBJECT(open_button), "clicked", G_CALLBACK(open_game), board);
  gtk_container_add (GTK_CONTAINER(toolbar), new_button);
  gtk_container_add (GTK_CONTAINER(toolbar), save_button);
  gtk_container_add (GTK_CONTAINER(toolbar), open_button);
}

GtkWidget* create_main_window(char campoExplorado[][DIM],int campoMinado[][DIM],GtkWidget *main_window,GtkWidget *board, \
                              GtkWidget *table1, GtkWidget *toolbar,GtkWidget *statusbar,GtkWidget* buttons[]){
    main_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (main_window), "Buscaminas v1.0");
    board = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER (main_window), board);
    create_toolbar(board,toolbar);
    g_object_set_data(G_OBJECT(board),"campoMinado",campoMinado);
    g_object_set_data(G_OBJECT(board),"campoExplorado",campoExplorado);
    g_object_set_data(G_OBJECT(board),"buttons",buttons);
    table1 = gtk_grid_new ();
    fill_table(board,table1,buttons);
    gtk_box_pack_start(GTK_BOX(board), table1,true,true,10);
    create_status_bar(board,statusbar);
    gtk_window_set_default_size(GTK_WINDOW(main_window),WIDTH,HEIGHT);
    gtk_widget_set_margin_start(board,HEIGHT*0.1);
    return main_window;
}

int main (int argc, char *argv[]){
    GtkWidget *main_window=NULL, *board =NULL,
              *table1=NULL,*toolbar = NULL,
              *statusbar=NULL,*buttons[DIM*DIM];

    char campoExplorado[DIM][DIM];
    int campoMinado[DIM][DIM];
    InicializarCampos(campoExplorado,campoMinado);
    DibujarCampoMinado(campoMinado);
    gtk_init (&argc, &argv);

    main_window = create_main_window (campoExplorado,campoMinado,main_window,board,table1,toolbar,statusbar,buttons);
    gtk_widget_show_all (main_window);

    gtk_main ();
    return 0;

}
