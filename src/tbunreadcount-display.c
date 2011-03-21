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

int accountSize = 3;
const char *accounts[3] = {
  "Gmail",
  "LilleGroup",
  "AOL - LiberiFataliVIII"};

void
update_display (HUD *hud, Prefs *prefs)
{
    char *disp = malloc(256);
    disp[0] = '\0';

    int buflen = 256;
    char *buf = malloc(buflen);
    strcpy(buf, "cat ");
    strcat(buf, COUNT_FILE);
    strcat(buf, "");

    FILE *fp = popen(buf, "r");

    char *count = malloc(8);
    char *name = malloc(256);
    char *dispBuf = malloc(256);
    while(fgets(buf, buflen, fp))
    {
        int len = strlen(buf);
        count[0] = '\0';
        name[0] = '\0';
        int i=0;
        for(; i<len; i++)
        {
            char c = buf[i];
            if(c == ':')
                break;
            else
                count[i] = c;
        }
        count[i] = '\0';
        i++;
        int offset = i;
        for(; i<len; i++)
        {
            char c = buf[i];
            if(c == '\n')
                break;
            else
                name[i-offset] = c;
        }
        name[i-offset] = '\0';

        for(i=0; i<accountSize; i++)
        {
            if(strcmp(accounts[i], name) == 0)
            {
                int cnt = atoi(count);
                if(cnt > 0)
                {
                    char firstLetter = accounts[i][0];
                    sprintf(dispBuf,
                      "<tt>"
                      "<span weight=\"bold\" fgcolor=\"green\">"
                      "%s%c"
                      "</span>"
                      "</tt> ",
                      count, firstLetter);
                    strcat(disp, dispBuf);
                }
            }
        }
    }
    if(strlen(disp) == 0)
    {
        strcat(disp,
          "<tt><span weight=\"bold\" fgcolor=\"white\">[]</span></tt> ");
    }
    gtk_label_set_markup(hud->label, disp);
    free(disp);
    free(dispBuf);
    free(buf);
    free(count);
    free(name);
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

