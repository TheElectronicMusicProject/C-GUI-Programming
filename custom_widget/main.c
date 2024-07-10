#include <gtk/gtk.h>

#define TEST6

void
end_program (GtkWidget * wid, gpointer ptr)
{
	gtk_main_quit();
	
	return;
}

int
main (int argc, char * argv[])
{
	int ret = 0;
	gtk_init(&argc, &argv);
	GtkWidget * win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	GtkWidget * btn = gtk_button_new_with_label("Close window");
	
	g_signal_connect(btn, "clicked", G_CALLBACK(end_program), NULL);
	g_signal_connect(win, "delete_event", G_CALLBACK(end_program),
					 NULL);
					 
	GtkWidget * vbox = gtk_vbox_new(FALSE, 5);
	gtk_container_add(GTK_CONTAINER(win), vbox);
	
	// Test 1
#ifdef TEST1
	GtkWidget * btn2 = gtk_button_new_with_label("My button");
	g_object_set(G_OBJECT(btn2), "relief", GTK_RELIEF_NONE, NULL);
	// Test 2
#elif defined(TEST2)
	GtkWidget * btn2 = gtk_button_new_with_label("My_button");
	g_object_set(G_OBJECT(btn2), "use-underline", TRUE, NULL);
	// Test 3
#elif defined(TEST3)
	GtkWidget * btn2 = gtk_label_new("My label");
	g_object_set(G_OBJECT(btn2), "angle", 45.0, NULL);
#elif defined(TEST4)
	GtkWidget * btn2 = gtk_button_new_with_label("My button");
	gtk_button_set_relief(GTK_BUTTON(btn2), GTK_RELIEF_HALF);
#elif defined(TEST5)
	GtkWidget * btn2 = gtk_button_new_with_label("My _button");
	gtk_button_set_use_underline(GTK_BUTTON(btn2), TRUE);
#elif defined(TEST6)
	GtkWidget * btn2 = gtk_label_new("My label");
	gtk_label_set_angle(GTK_LABEL(btn2), 137.8);
#endif
	
	gtk_box_pack_start(GTK_BOX(vbox), btn2, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), btn, TRUE, TRUE, 0);
	gtk_widget_show_all(win);
	gtk_main();
	
	return ret;
}
