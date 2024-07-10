#include <gtk/gtk.h>

void
end_program (GtkWidget * wid, gpointer ptr)
{
	gtk_main_quit();
}

void
combo_changed (GtkWidget * wid, gpointer ptr)
{
	int sel = gtk_combo_box_get_active(GTK_COMBO_BOX(wid));
	printf("The value of the combo is %d\n", sel);
}

void
check_toggle (GtkWidget * wid, gpointer ptr)
{
	int state = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(wid));
	printf("The state of the button is %d\n", state);
}

int
main (int argc, char * argv[])
{
	int ret = 0;
	int pos = 0;
	gtk_init(&argc, &argv);
	
	GtkWidget * win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	GtkWidget * btn = gtk_button_new_with_label("Close window");
	
	g_signal_connect(btn, "clicked", G_CALLBACK(end_program), NULL);
	g_signal_connect(win, "delete_event", G_CALLBACK(end_program),
					 NULL);
					 
	GtkWidget * rad1 = gtk_radio_button_new_with_label(NULL,
													   "Button 1");
	GSList * group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(rad1));
	GtkWidget * rad2 = gtk_radio_button_new_with_label(group,
													   "Button 2");

	GtkListStore * ls = gtk_list_store_new(1, G_TYPE_STRING);
	gtk_list_store_insert_with_values(ls, NULL, pos, 0, "Option 1",
									  -1);
	pos++;
	gtk_list_store_insert_with_values(ls, NULL, pos, 0, "Option 2",
									  -1);
	pos++;
	gtk_list_store_insert_with_values(ls, NULL, pos, 0, "Option 3",
									  -1);
	
	GtkTreeModelSort * sorted = GTK_TREE_MODEL_SORT(
									gtk_tree_model_sort_new_with_model(
										GTK_TREE_MODEL(ls)));
	gtk_tree_sortable_set_sort_column_id(GTK_TREE_SORTABLE(sorted), 0,
										 GTK_SORT_ASCENDING);
	GtkWidget * comb =
				gtk_combo_box_new_with_model(GTK_TREE_MODEL(sorted));
	
	
	GtkCellRenderer * rend = gtk_cell_renderer_text_new();
	gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(comb), rend, FALSE);
	gtk_cell_layout_add_attribute(GTK_CELL_LAYOUT(comb), rend,
								  "text", 0);

	g_signal_connect(comb, "changed", G_CALLBACK(combo_changed), NULL);
	
	GtkWidget * tab = gtk_table_new(2, 2, TRUE);
	
	gtk_table_attach_defaults(GTK_TABLE(tab), rad1, 0, 1, 0, 1);
	gtk_table_attach_defaults(GTK_TABLE(tab), rad2, 1, 2, 0, 1);
	gtk_table_attach_defaults(GTK_TABLE(tab), btn, 0, 1, 1, 2);
	gtk_table_attach_defaults(GTK_TABLE(tab), comb, 1, 2, 1, 2);
	
	gtk_container_add(GTK_CONTAINER(win), tab);
	
	gtk_widget_show_all(win);
	
	gtk_main();
	
	return ret;
}
