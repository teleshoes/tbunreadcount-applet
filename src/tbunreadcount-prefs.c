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

#include <panel-applet.h>
#include <panel-applet-gconf.h>

#include "tbunreadcount-prefs.h"

gboolean
valueExists (PanelApplet *applet, const char *key)
{
    GConfValue *val = panel_applet_gconf_get_value(applet, key, NULL);
    gboolean exists = val != NULL;
    return exists;
}

void
load_prefs (PanelApplet *applet, Prefs *prefs)
{
    int delay = panel_applet_gconf_get_int(applet, "delay", NULL);
    if(valueExists(applet, "delay"))
        prefs->delay = delay;
}

void
initialize_prefs (PanelApplet *applet)
{
  panel_applet_add_preferences (PANEL_APPLET (applet),
    SCHEMA_DIR, NULL);
}

