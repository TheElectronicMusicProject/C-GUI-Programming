#include <gtk/gtk.h>

void
end_program (GtkWidget * wid, gpointer ptr)
{
	gtk_main_quit();
	
	return;
}

int
main (int argc, char * argv[])
{
	GError * error = NULL;
	
	gtk_init(&argc, &argv);
	
	GtkBuilder * builder = gtk_builder_new();
	
	if (0 == gtk_builder_add_from_file(builder, "mylayout.glade",
									   &error))
    {
      g_printerr("Error loading file: %s\n", error->message);
      g_clear_error(&error);
      
      return 1;
    }

	GtkWidget * win = (GtkWidget *) gtk_builder_get_object(builder,
														   "window1");
	GtkWidget * btn = (GtkWidget *) gtk_builder_get_object(builder,
														   "button2");
	
	g_signal_connect(btn, "clicked", G_CALLBACK(end_program), NULL);
														   
	gtk_widget_show_all(win);
	gtk_main();
	
	return 0;
}
