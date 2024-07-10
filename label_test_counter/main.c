#include <gtk/gtk.h>

void end_program(GtkWidget * wid, gpointer ptr);
void count_button(GtkWidget * wid, gpointer ptr);

int g_count = 0;

int
main (int argc, char * argv[])
{
	gtk_init(&argc, &argv);
	GtkWidget * win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	GtkWidget * btn = gtk_button_new_with_label("Close window");
	GtkWidget * btn2 = gtk_button_new_with_label("Count button");
	GtkWidget * lbl = gtk_label_new("My label");
	GtkWidget * box = gtk_vbox_new(FALSE, 5);
	//gtk_container_add(GTK_CONTAINER(win), btn);
	
	g_signal_connect(btn, "clicked", G_CALLBACK(end_program), NULL);
	g_signal_connect(btn2, "clicked", G_CALLBACK(count_button), lbl);
	g_signal_connect(win, "delete_event", G_CALLBACK(end_program),
					 NULL);
	
	// Metto prima la label e poi il bottone!
	gtk_box_pack_start(GTK_BOX(box), btn2, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(box), lbl, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(box), btn, TRUE, TRUE, 0);
	gtk_container_add(GTK_CONTAINER(win), box);
	
	gtk_widget_show_all(win);
	gtk_main();
	return 0;
}

void
end_program (GtkWidget * wid, gpointer ptr)
{
	gtk_main_quit();
}

void
count_button (GtkWidget * wid, gpointer ptr)
{
	char buffer[30];
	++g_count;
	sprintf(buffer, "Button pressed %d times", g_count);
	gtk_label_set_text(GTK_LABEL(ptr), buffer);
}
