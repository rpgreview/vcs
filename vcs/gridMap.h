/**********************************************************************
 *    Copyright Torquil Gault 2005+
 * #       This program is free software; you can redistribute it and/or
 * #       modify it under the terms of the GNU General Public License
 * #       as published by the Free Software Foundation; either version 2
 * #       of the License, or (at your option) any later version.
 * #
 * #       This program is distributed in the hope that it will be useful,
 * #       but WITHOUT ANY WARRANTY; without even the implied warranty of
 * #       MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * #       GNU General Public License for more details.
 * #
 * #       You should have received a copy of the GNU General Public License
 * #       along with this program; if not, write to the Free Software
 * #       Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 * #
 * #
 * #####################################################################
 **********************************************************************/
#ifndef gridMap_H
#define gridMap_H

#ifndef Fl_Widget_H
#include "FL/Fl_Widget.H"
#endif

#include "FL/Fl_Button.H"
#include "FL/Fl_Scrollbar.H"
#include "FL/Fl_Tile.H"
#include "FL/Fl_Browser.H"
#include "FL/Fl_Button.H"
#include "FL/Fl_Image.H"
#include "FL/Fl_PNG_Image.H"
#include "FL/Fl_JPEG_Image.H"
#include "gridTile.h"

class FL_EXPORT gridMap : public Fl_Widget {

	gridTile *mapTile;

	Fl_Scrollbar *vbar, *hbar;

	int gridWidth, gridHeight, gridMode;

	gridMap *externalGrid;

	char gridID[53], gridXID[53];

	int ignoreX, ignoreY;

protected:

  virtual void draw();

public:

	gridMap(int,int,int,int,const char * = 0);

	void size(int, int);

	int setGridSize(int);

	void end() { ; }

	void setGridTop(int x, int y) { mapTile->setGridTop(x,y); }
	void setGridColor(int x, int y, int c) { mapTile->setGridColor(x,y,c); if (externalGrid != NULL) { externalGrid->setGridColor(x,y,c); } }
	void setGridType(int x, int y, int t, int i) { mapTile->setGridType(x,y,t,i); if (externalGrid != NULL) { externalGrid->setGridType(x,y,t,i); } }

	int drawRowHeaders();
	int drawColumnHeaders();
	void cb_scrollbar(Fl_Widget *w);
	static void my_cb_scrollbar(Fl_Widget *w, void *f) { ((gridMap *)f)->cb_scrollbar(w); }

	void setGridText(Fl_Browser *);

	void setExternalGrid(gridMap *g) { externalGrid = g; }

	void setColorMap(int i, Fl_Color c) { mapTile->setColorMap(i, c); }
	Fl_Color getColorMap(int i) { return mapTile->getColorMap(i); }
	void setMode(int m) { gridMode = m; mapTile->setMode(m); }

	gridTile *getGridTile() { return mapTile; }
	void setGridTile(gridTile *t) { mapTile->setExternalTile(t); }

	void setActionWindow(Fl_Window *w) { mapTile->setActionWindow(w); }

	void setGridType(int t) { mapTile->setGridType(t); if (t == 1) { vbar->hide(); hbar->hide(); } }
//	void setGridType(int t) { mapTile->setGridType(t); if (t == 1) { vbar->deactivate(); hbar->deactivate(); } }
	void setGridLayer(int l) { mapTile->setGridLayer(l); }

	void setPlayerData(ADMPplayer *p) { mapTile->setPlayerData(p); }

	void setGridVisibility(int v) { mapTile->setGridVisibility(v); }

	void saveGridMap(char *n) { mapTile->saveGridMap(n); }
	void loadGridMap(char *n) { mapTile->loadGridMap(n); } //setGridType(9,8,GRID_PLAYER, 1); setGridType(9,4,GRID_MONSTER, 8); }

	void setMapEventHandler(int (*fp)()) { mapTile->setMapEventHandler(fp); }
	void setTileEventHandler(int (*fp)()) { mapTile->setTileEventHandler(fp); }

	int getClickedGridType() { return mapTile->getClickedGridType(); }
	int getClickedGridID() { return mapTile->getClickedGridID(); }

	void drawLine(int sx, int sy, int ex, int ey) { mapTile->drawLine(sx,sy,ex,ey); }

	void drawCircle(int sx, int sy, int r) { mapTile->drawCircle(sx,sy,r); }

	void drawSquare(int sx, int sy, int ex, int ey) { mapTile->drawSquare(sx,sy,ex,ey); }

	int getClickedX() { return mapTile->getClickedX(); }
	int getClickedY() { return mapTile->getClickedY(); }

	void setPlayerIcon(int p, Fl_Image *i) { mapTile->setPlayerIcon(p, i); if (externalGrid != NULL) { externalGrid->setPlayerIcon(p, i); externalGrid->redraw(); } }

	void setActiveColor(int c) { mapTile->setActiveColor(c); }

	void resizeGridMap(int , int);
	void resizeScrollbars(int , int);

	void clearGridMap() { mapTile->clearGridMap(); }

	void repaint() { redraw(); mapTile->redraw(); if (externalGrid != NULL) { externalGrid->redraw(); } }

	void markPlayerLocation(int, int);
	void clearlayerLocation() { ignoreX = ignoreY = -1; }

};

#endif
