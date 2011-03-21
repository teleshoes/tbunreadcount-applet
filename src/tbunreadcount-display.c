/**************************************************************************
 *  TBUnreadCountApplet v0.1
 *  Copyright 2011 Elliot Wolk
 **************************************************************************
 *  This file is part of TBUnreadCountApplet.
 *
 *  TBUnreadCountApplet is free software: you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  TBUnreadCountApplet is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with TBUnreadCountApplet.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************/

#include <gtk/gtk.h>
#include <gtk/gtkbox.h>
#include <gtk/gtkwidget.h>

#include <panel-applet.h>

#include "tbunreadcount-display.h"
#include "tbunreadcount-prefs.h"

void
update_display (HUD *hud, Prefs *prefs)
{
    gtk_label_set_markup(hud->label, "hey");
}

void
init_display (HUD *hud, PanelApplet *applet)
{
    GtkWidget *hbox = gtk_hbox_new(TRUE, 1);
    hud->label = (GtkLabel*) gtk_label_new("<Status Unread>");
    
    gtk_box_pack_start(GTK_BOX(hbox), GTK_WIDGET(hud->label),
      TRUE, TRUE, 0);

    gtk_container_add (GTK_CONTAINER (applet), GTK_WIDGET(hbox));
	
    gtk_widget_show_all (GTK_WIDGET (applet));
}

