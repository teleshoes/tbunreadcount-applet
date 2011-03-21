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

#include <stdio.h>
#include <panel-applet.h>

#include "tbunreadcount-applet.h"
#include "tbunreadcount-display.h"
#include "tbunreadcount-prefs.h"


gboolean
update (TBUnreadCount *tbunreadcount)
{
    int newDelay = tbunreadcount->prefs->delay;
    if(newDelay > 0 && newDelay != tbunreadcount->currentDelay)
    {
        start_update(tbunreadcount);
        return FALSE;
    }

    load_prefs(tbunreadcount->applet, tbunreadcount->prefs);

    update_display(tbunreadcount->hud, tbunreadcount->prefs);

    return TRUE;
}

gboolean
stop_update (TBUnreadCount *tbunreadcount)
{
    if(tbunreadcount->timer != -1)
        g_source_remove (tbunreadcount->timer);

    tbunreadcount->timer = -1;

    return TRUE;
}

gboolean
start_update(TBUnreadCount *tbunreadcount)
{
    stop_update (tbunreadcount);

    tbunreadcount->currentDelay = tbunreadcount->prefs->delay;
    if(tbunreadcount->currentDelay <= 0)
        tbunreadcount->currentDelay = 1000;
    update(tbunreadcount);
    tbunreadcount->timer = g_timeout_add (
        tbunreadcount->currentDelay,
        (GSourceFunc) update,
        tbunreadcount);

    return TRUE;
}


gboolean
tbunreadcount_applet_fill (PanelApplet *applet,
   const gchar *iid,
   gpointer data)
{
	if (strcmp (iid, "OAFIID:TBUnreadCountApplet") != 0)
		return FALSE;

    initialize_prefs(applet);
    
    TBUnreadCount *tbunreadcount = g_new0(TBUnreadCount, 1);
    tbunreadcount->applet = applet;

    tbunreadcount->hud = malloc(sizeof(HUD));
    init_display(tbunreadcount->hud, applet);

    tbunreadcount->prefs = malloc(sizeof(Prefs));
    load_prefs(tbunreadcount->applet, tbunreadcount->prefs);

    start_update(tbunreadcount);
	
	return TRUE;
}

PANEL_APPLET_BONOBO_FACTORY ("OAFIID:TBUnreadCountApplet_Factory",
                             PANEL_TYPE_APPLET,
                             "Thunderbird Unread Count Applet",
                             "0",
                             tbunreadcount_applet_fill,
                             NULL);
