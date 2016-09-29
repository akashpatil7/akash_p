#include <gtk/gtk.h>
#include <stdio.h>
#import  <objc/runtime.h>
#include <cairo.h>

  GtkWidget *window;
  GtkWidget *box;
  GtkWidget *grid, *grid1;
  GtkWidget *switcherbtn, *toggle1, *toggle2, *bulb, *And, *Or, *Not, *Nand, *Nor, *Xor, *Xnor;
  GtkWidget *vpaned;
  GtkWidget *frame;
  GtkWidget *combo;
  GtkWidget *label;
  GtkWidget *label1, *label2, *l;
  GtkWidget *switcher1;
  GtkWidget *switcher2;
  GtkWidget *vseperator;
  GtkWidget *file_menu, *help_menu, *menu_bar, *root_menu, *menu_item;
  GtkWidget *image;
  GtkWidget *toggleinput, *toggleoutput;

static void addswitch(GtkWidget *widget, gpointer data)
{
	widget = gtk_switch_new();
	gtk_switch_set_active(GTK_SWITCH(widget),TRUE);
	gtk_grid_attach(GTK_GRID(grid1),widget,1,3,1,1);
	gtk_widget_show(widget);
	gtk_widget_show(grid1);
}

static void addtoggle(GtkWidget *widget, gpointer data)
{
	widget = gtk_toggle_button_new_with_label("Togggle");
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widget),TRUE);
	gtk_grid_attach(GTK_GRID(grid1),widget,1,4,1,1);
	gtk_widget_show(widget);
	gtk_widget_show(grid1);
}

static void and(GtkWidget *widget, gpointer data)
{
	image = gtk_image_new_from_file("AND.png");
        gtk_grid_attach(GTK_GRID(grid1),image,2,5,1,1);
        gtk_widget_show(image);
        gtk_widget_show(grid1);
}

static void or(GtkWidget *widget, gpointer data)
{
	image = gtk_image_new_from_file("OR.png");
        gtk_grid_attach(GTK_GRID(grid1),image,2,6,1,1);
        gtk_widget_show(image);
        gtk_widget_show(grid1);
}

static void not(GtkWidget *widget, gpointer data)
{
	image = gtk_image_new_from_file("NOT.png");
        gtk_grid_attach(GTK_GRID(grid1),image,2,7,1,1);
        gtk_widget_show(image);
        gtk_widget_show(grid1);
}

static void nand(GtkWidget *widget, gpointer data)
{
	image = gtk_image_new_from_file("NAND.png");
        gtk_grid_attach(GTK_GRID(grid1),image,2,8,1,1);
        gtk_widget_show(image);
        gtk_widget_show(grid1);
}

static void nor(GtkWidget *widget, gpointer data)
{
	image = gtk_image_new_from_file("NOR.png");
        gtk_grid_attach(GTK_GRID(grid1),image,2,9,1,1);
        gtk_widget_show(image);
        gtk_widget_show(grid1);
}

static void xor(GtkWidget *widget, gpointer data)
{
	image = gtk_image_new_from_file("XOR.png");
        gtk_grid_attach(GTK_GRID(grid1),image,2,10,1,1);
        gtk_widget_show(image);
        gtk_widget_show(grid1);
}

static void xnor(GtkWidget *widget, gpointer data)
{
	image = gtk_image_new_from_file("XNOR.png");
        gtk_grid_attach(GTK_GRID(grid1),image,2,11,1,1);
        gtk_widget_show(image);
        gtk_widget_show(grid1);
}

gboolean supports_alpha = FALSE;
static void screen_changed(GtkWidget *widget, GdkScreen *old_screen, gpointer userdata)
{
    /* To check if the display supports alpha channels, get the visual */
    GdkScreen *screen = gtk_widget_get_screen(widget);
    GdkVisual *visual = gdk_screen_get_rgba_visual(screen);

    if (!visual)
    {
        printf("Your screen does not support alpha channels!\n");
        visual = gdk_screen_get_system_visual(screen);
        supports_alpha = FALSE;
    }
    else
    {
        printf("Your screen supports alpha channels!\n");
        supports_alpha = TRUE;
    }

    gtk_widget_set_visual(widget, visual);
}

static gboolean draw(GtkWidget *widget, cairo_t *cr, gpointer userdata)
{
   cairo_t *new_cr = gdk_cairo_create(gtk_widget_get_window(widget));

    if (supports_alpha)
    {
        cairo_set_source_rgba (new_cr, 1.0, 0.2, 0.2, 0.6); /* transparent */
    }
    else
    {
        cairo_set_source_rgb (new_cr, 1.0, 1.0, 1.0); /* opaque white */
    }

    /* draw the background */
    cairo_set_operator (new_cr, CAIRO_OPERATOR_SOURCE);
    cairo_paint (new_cr);

    cairo_destroy(new_cr);

    return FALSE;
}


int main(int argc, char *argv[]) {
    
 /* GtkWidget *window;
  GtkWidget *box;
  GtkWidget *grid, *grid1;
  GtkWidget *switcherbtn, *toggle1, *toggle2, *bulb, *And, *Or, *Not, *Nand, *Nor, *Xor, *Xnor;
  GtkWidget *vpaned;
  GtkWidget *frame;
  GtkWidget *combo;
  GtkWidget *label;
  GtkWidget *label1, *label2, *l;
  GtkWidget *switcher1;
  GtkWidget *switcher2;
  GtkWidget *vseperator;
  GtkWidget *file_menu, *help_menu, *menu_bar, *root_menu, *menu_item;
  GtkWidget *image;
  GtkWidget *button; */
  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "Logic Gate Simulator");
  gtk_window_set_default_size (GTK_WINDOW (window), 600, 400);
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  
  GtkSettings *default_settings = gtk_settings_get_default();
  g_object_set(default_settings, "gtk-button-images", TRUE, NULL); 

  
  //-----------background colour
  gtk_widget_set_app_paintable(window, TRUE);

  g_signal_connect(G_OBJECT(window), "draw", G_CALLBACK(draw), NULL);
  g_signal_connect(G_OBJECT(window), "screen-changed", G_CALLBACK(screen_changed), NULL);

  gtk_window_set_decorated(GTK_WINDOW(window), FALSE);
  gtk_widget_add_events(window, GDK_BUTTON_PRESS_MASK);
  gtk_window_set_decorated(GTK_WINDOW(window),TRUE);
  //GtkWidget* fixed_container = gtk_fixed_new();
  //gtk_container_add(GTK_CONTAINER(window), fixed_container);

  screen_changed(window, NULL, NULL);
  //----------
  
  vpaned = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
  gtk_container_add(GTK_CONTAINER(window),vpaned);
  gtk_paned_set_position(GTK_PANED(vpaned),175);
  gtk_widget_show(vpaned);
  
  /*vseperator = gtk_seperator_new(GTK_ORIENTATION_VERTICAL);
  gtk_widget_show(vseperator);
  layout = gtk_layout_new(NULL,NULL);
  gtk_container_add(GTK_CONTAINER(window),vpaned);
  gtk_widget_show(layout);*/
  
  /*gtk_layout_put(GTK_LAYOUT(layout),image,0,0);*/
  
  grid = gtk_grid_new();
  gtk_grid_set_column_spacing (GTK_GRID (grid), 10);
  gtk_grid_set_row_spacing (GTK_GRID (grid), 10);
  
  grid1 = gtk_grid_new();
 // gtk_widget_set_size_request(vpaned,200,-1);
  
  gtk_paned_pack1(GTK_PANED(vpaned),grid,TRUE,TRUE);
  
  gtk_paned_pack2(GTK_PANED(vpaned),grid1,TRUE,TRUE);
  
  //button = gtk_button_new_with_label("Akash");
  //gtk_grid_attach(GTK_GRID(grid1),button,0,0,1,1);

  menu_bar = gtk_menu_bar_new();
  file_menu = gtk_menu_new();
  help_menu = gtk_menu_new();
  
  menu_item=gtk_menu_item_new_with_label("File");
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item),file_menu);
  gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar),menu_item);

  menu_item=gtk_menu_item_new_with_label("Help");
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item),help_menu);
  gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar),menu_item);

  menu_item=gtk_menu_item_new_with_label("New");
  gtk_menu_shell_append(GTK_MENU_SHELL(file_menu),menu_item);

  menu_item=gtk_menu_item_new_with_label("Exit");
  gtk_menu_shell_append(GTK_MENU_SHELL(file_menu),menu_item);
  g_signal_connect(G_OBJECT(menu_item), "activate",G_CALLBACK(gtk_main_quit), NULL);

  menu_item=gtk_menu_item_new_with_label("About");
  gtk_menu_shell_append(GTK_MENU_SHELL(help_menu),menu_item);

  gtk_grid_attach(GTK_GRID(grid),menu_bar,0,0,2,1);
  
  label = gtk_label_new("Input Controls:");
  PangoFontDescription *font_desc = pango_font_description_from_string ("sans 15");
  gtk_widget_modify_font (label, font_desc);
  pango_font_description_free (font_desc);
  GdkColor color;
  gdk_color_parse ("white", &color);
  gtk_widget_modify_fg (label, GTK_STATE_NORMAL, &color);
  gtk_grid_attach(GTK_GRID(grid),label,0,1,2,1);
  
  switcherbtn = gtk_button_new_with_label("Switch");
  gtk_grid_attach(GTK_GRID(grid),switcherbtn,0,2,1,1);
  g_signal_connect(GTK_BUTTON(switcherbtn),"clicked", G_CALLBACK(addswitch),NULL);  
  
  toggle1 = gtk_button_new_with_label("Toggle");
  gtk_grid_attach(GTK_GRID(grid),toggle1,1,2,1,1);
  g_signal_connect(GTK_BUTTON(toggle1),"clicked", G_CALLBACK(addtoggle),NULL);  


  label1 = gtk_label_new("Output Controls:");
  PangoFontDescription *font_desc1 = pango_font_description_from_string ("sans 15");
  gtk_widget_modify_font (label1, font_desc1);
  pango_font_description_free (font_desc1);
  GdkColor color1;
  gdk_color_parse ("white", &color1);
  gtk_widget_modify_fg (label1, GTK_STATE_NORMAL, &color1);
  gtk_grid_attach(GTK_GRID(grid),label1,0,3,2,1);

  bulb = gtk_button_new_with_label("Bulb");
  gtk_grid_attach(GTK_GRID(grid),bulb,0,4,1,1);

  toggle2 = gtk_button_new_with_label("Toggle");
  gtk_grid_attach(GTK_GRID(grid),toggle2,1,4,1,1);
  
  label2 = gtk_label_new("Gates:");
  PangoFontDescription *font_desc2 = pango_font_description_from_string ("sans 15");
  gtk_widget_modify_font (label2, font_desc2);
  pango_font_description_free (font_desc2);
  GdkColor color2;
  gdk_color_parse ("white", &color2);
  gtk_widget_modify_fg (label2, GTK_STATE_NORMAL, &color2);
  gtk_grid_attach(GTK_GRID(grid),label2,0,5,2,1);
  
  And = gtk_button_new_with_label(NULL);
  image = gtk_image_new_from_file("/akashpatil/Desktop/project/GateImages/AND.png");
  gtk_button_set_image(GTK_BUTTON(And), image);
  gtk_button_set_always_show_image(GTK_BUTTON(And),TRUE);
  gtk_grid_attach(GTK_GRID(grid),And,0,6,1,1);
  g_signal_connect(GTK_BUTTON(And),"clicked", G_CALLBACK(and),NULL);  
  
  Or = gtk_button_new_with_label("Or");
  gtk_grid_attach(GTK_GRID(grid),Or,1,6,1,1);
  g_signal_connect(GTK_BUTTON(Or),"clicked", G_CALLBACK(or),NULL);  
  
  Not = gtk_button_new_with_label("Not");
  gtk_grid_attach(GTK_GRID(grid),Not,0,7,1,1);
  g_signal_connect(GTK_BUTTON(Not),"clicked", G_CALLBACK(not),NULL);  

  Nand = gtk_button_new_with_label("Nand");
  gtk_grid_attach(GTK_GRID(grid),Nand,1,7,1,1);
  g_signal_connect(GTK_BUTTON(Nand),"clicked", G_CALLBACK(nand),NULL);  
  
  Nor = gtk_button_new_with_label("Nor");
  gtk_grid_attach(GTK_GRID(grid),Nor,0,8,1,1);
  g_signal_connect(GTK_BUTTON(Nor),"clicked", G_CALLBACK(nor),NULL);  
  
  Xor = gtk_button_new_with_label("Xor");
  gtk_grid_attach(GTK_GRID(grid),Xor,1,8,1,1);
  g_signal_connect(GTK_BUTTON(Xor),"clicked", G_CALLBACK(xor),NULL);  
  
  Xnor = gtk_button_new_with_label("Xnor");
  gtk_grid_attach(GTK_GRID(grid),Xnor,0,9,1,1);	
  g_signal_connect(GTK_BUTTON(Xnor),"clicked", G_CALLBACK(xnor),NULL);  
   
/*  switcher1 = gtk_switch_new();
  gtk_switch_set_active(GTK_SWITCH(switcher1),TRUE);
  g_signal_connect(GTK_SWITCH(switcher1),"notify::active", G_CALLBACK(activate_cb) , btn);
  gtk_grid_attach(GTK_GRID(grid),switcher1,1,1,1,1);
  
  switcher2 = gtk_switch_new();
  gtk_switch_set_active(GTK_SWITCH(switcher2),TRUE);
  g_signal_connect(GTK_SWITCH(switcher2),"notify::active", NULL ,NULL);
  gtk_grid_attach(GTK_GRID(grid),switcher2,1,2,1,1);*/
 
  g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
  
  gtk_widget_show_all(window);
  
  gtk_main();

}


