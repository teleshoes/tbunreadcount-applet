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

#ifndef TBUNREADCOUNT_DISPLAY_H
#define TBUNREADCOUNT_DISPLAY_H

#include <panel-applet.h>
#include <gtk/gtklabel.h>

#include "tbunreadcount-prefs.h"

#define COUNT_FILE "~/.thunderbird/*.default/unread-counts"

#define PIXMAP_DIR "/usr/share/pixmaps/tbunreadcount-applet"
#define IMAGE_HEIGHT 24
#define IMAGE_WIDTH 24

typedef struct {
    GtkLabel *label;
} HUD;

void update_display (HUD *hud, Prefs *prefs);

void init_display (HUD *hud, PanelApplet *applet);

#endif /* TBUNREADCOUNT_DISPLAY_H */
