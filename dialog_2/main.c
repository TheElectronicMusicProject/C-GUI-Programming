#include <gtk/gtk.h>

void
end_program (GtkWidget * wid, gpointer ptr)
{
	gtk_main_quit();
	
	return;
}

void
open_dialog (GtkWidget * wid, gpointer ptr)
{
	GtkWidget * dlg = gtk_dialog_new_with_buttons(
					"My dialog", GTK_WINDOW(ptr),
					GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
					"Cancel", 0, "OK", 1, NULL);
	GtkWidget * lbl = gtk_label_new("A question for the user");
	gtk_container_add(GTK_CONTAINER(
					gtk_dialog_get_content_area(GTK_DIALOG(dlg))), lbl);
	gtk_widget_show(lbl);
	int result = gtk_dialog_run(GTK_DIALOG(dlg));
	gtk_widget_destroy(dlg);
	printf("Return code = %d\n", result);
	
	return;
}

int
main (int argc, char * argv[])
{
	int ret = 0;
	gtk_init(&argc, &argv);
	GtkWidget * win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	GtkWidget * btn = gtk_button_new_with_label("Close window");
	GtkWidget * btn2 = gtk_button_new_with_label("Click me");
	g_signal_connect(btn, "clicked", G_CALLBACK(end_program), NULL);
	g_signal_connect(btn2, "clicked", G_CALLBACK(open_dialog), NULL);
	g_signal_connect(win, "delete_event", G_CALLBACK(end_program),
					 NULL);
					 
	GtkWidget * vbox = gtk_vbox_new(FALSE, 5);
	gtk_container_add(GTK_CONTAINER(win), vbox);
	
	gtk_box_pack_start(GTK_BOX(vbox), btn2, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), btn, TRUE, TRUE, 0);
	gtk_widget_show_all(win);
	gtk_main();
	
	return ret;
}
