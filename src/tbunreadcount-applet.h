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

#ifndef TBUNREADCOUNT_APPLET_H
#define TBUNREADCOUNT_APPLET_H

#include <panel-applet.h>

#include "tbunreadcount-battinfo.h"
#include "tbunreadcount-display.h"
#include "tbunreadcount-prefs.h"

typedef struct {
    HUD *hud;
    PanelApplet *applet;
    BatteryStatus *status;
    Prefs *prefs;
    int currentDelay;
    int timer;
} TBUnreadCount;

void desktop_log (char *msg);

#endif /* TBUNREADCOUNT_APPLET_H */
