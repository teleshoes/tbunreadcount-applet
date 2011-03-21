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

#ifndef TBUNREADCOUNT_PREFS_H
#define TBUNREADCOUNT_PREFS_H

#include <panel-applet.h>

#define SCHEMA_DIR "/schemas/apps/tbunreadcount_applet/prefs"

typedef struct {
    int delay;
} Prefs;

void load_prefs (PanelApplet *applet, Prefs *prefs);
void initialize_prefs (PanelApplet *applet);

#endif /* TBUNREADCOUNT_PREFS_H */
