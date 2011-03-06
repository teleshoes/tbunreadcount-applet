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
#include "tbunreadcount-battinfo.h"
#include "tbunreadcount-display.h"
#include "tbunreadcount-prefs.h"

void
desktop_log (char *msg)
{
    char *cmd = malloc(256);
    sprintf(cmd, "echo `date`: \"%s\" >> /home/wolke/Desktop/out", msg);
    system(cmd);
    g_free(cmd);
} 

void
verb_statistics (BonoboUIComponent *ui_container,
               gpointer           user_data,
               const              char *cname)
{
    system("gnome-power-statistics &");
}
const char context_menu_xml [] =
    "<popup name=\"button3\">\n"
    "   <menuitem name=\"Properties Item\" "
    "             verb=\"Statistics\" "
    "           _label=\"_Statistics\"\n"
    "          pixtype=\"stock\" "
    "          pixname=\"gtk-properties\"/>\n"
    "</popup>\n";
const BonoboUIVerb context_menu_verbs [] = {
        BONOBO_UI_VERB ("Statistics", verb_statistics),
        BONOBO_UI_VERB_END
};




gboolean
update (TBUnreadCount *tbunreadcount)
{
    int newDelay = tbunreadcount->prefs->delay;
    if(newDelay > 0 && newDelay != tbunreadcount->currentDelay)
    {
        start_update(tbunreadcount);
        return FALSE;
    }

    get_battery_status(tbunreadcount->status);

    load_prefs(tbunreadcount->applet, tbunreadcount->prefs);
    tbunreadcount->status->msg = "";
    perhaps_inhibit_charge(
            tbunreadcount->status,
            tbunreadcount->prefs->chargeStrategy,
            tbunreadcount->prefs->chargeLeapfrogThreshold,
            tbunreadcount->prefs->chargeBrackets,
            tbunreadcount->prefs->chargeBracketsSize,
            tbunreadcount->prefs->chargeBracketsPrefBattery);
    perhaps_force_discharge(
            tbunreadcount->status,
            tbunreadcount->prefs->dischargeStrategy,
            tbunreadcount->prefs->dischargeLeapfrogThreshold);

    update_display(tbunreadcount->hud, tbunreadcount->status, tbunreadcount->prefs);

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

    panel_applet_setup_menu (PANEL_APPLET (applet),
	                         context_menu_xml,
	                         context_menu_verbs,
	                         applet);	
    
    tbunreadcount->status = malloc(sizeof(BatteryStatus));
    tbunreadcount->status->count = 0;
    tbunreadcount->status->bat0 = malloc(sizeof(Battery));
    tbunreadcount->status->bat1 = malloc(sizeof(Battery));

    tbunreadcount->prefs = malloc(sizeof(Prefs));
    tbunreadcount->prefs->chargeBrackets = NULL;
    load_prefs(tbunreadcount->applet, tbunreadcount->prefs);

    start_update(tbunreadcount);
	
	return TRUE;
}

PANEL_APPLET_BONOBO_FACTORY ("OAFIID:TBUnreadCountApplet_Factory",
                             PANEL_TYPE_APPLET,
                             "ThinkPad Battery Status Applet",
                             "0",
                             tbunreadcount_applet_fill,
                             NULL);
