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

#ifndef gridTile_H
#define gridTile_H

#ifndef Fl_Tile_H
#include "FL/Fl_Tile.H"
#endif
#include "FL/Fl_Browser.H"
#include "FL/Fl_Window.H"
#include "FL/Fl_Button.H"
#include "FL/Fl_Scrollbar.H"
#include "FL/Fl_Image.H"
#include "FL/Fl_Shared_Image.H"
#include "FL/Fl_PNG_Image.H"
#include "FL/Fl_JPEG_Image.H"
#include <stdlib.h>
#include <math.h>

#include "gridPoint.h"
#include "VCSdefines.h"

#ifndef ADMPDATA_H
#include "ADMPdata.h"
#endif

class FL_EXPORT gridTile : public Fl_Tile {
	gridPoint *gridPoints;
	Fl_Color colorMap[16];
	int gridSize, gridWidth, gridHeight, gridSizes[36], gridSizePtr;
	int gridTopX, gridTopY, gridMode, gridLayer;
	int clickedX, clickedY, prevEvent, gridType, gridVisibility;
	int deltaX, deltaY, currColor, currShape;
	int shapeWidth, shapeHeight, shapeFill;
	int prevX, prevY, undoMapCnt;
	int prevCentreX, prevCentreY;
	int copyObjX, copyObjY;

	losPoint *losGrid;
	uchar losGridSize;

	uchar losAlgorithm;

	Fl_Browser *gridOutputText;
	Fl_Window *actionWindow;

	ADMPobject *objectData;

	Fl_Image *playerIcons[MAX_MEMBERS+2], *objectIcons[MAX_OBJECTS+2];

	gridTile *externalTile;

	ADMPplayer *playerData;

	int (*eventTileHandler)();
	int (*eventMapHandler)();

	Fl_Scrollbar *vbar, *hbar;

	char f_fogOfWar;

	ADMPgroup *groupData;

protected:

  virtual void draw();

public:

  virtual int handle(int);

  gridTile(int,int,int,int);

	int getGridSize();
	int setGridSize(int);
	int setGridSize(int, int);
	int setGridColor(int, int, int);
	int setGridType(int, int, int, int);
	int setColorMap(int, Fl_Color);
	Fl_Color getColorMap(int);
	int setGridTop(int, int);
	int getGridTopX();
	int getGridTopY();
	int getGridWidth() { return w(); }
	int getGridHeight() { return h(); }
	int getGridSzWidth() { return gridWidth; }
	int getGridSzHeight() { return gridHeight; }

	void setScrollBars(Fl_Scrollbar *v, Fl_Scrollbar *h) { vbar = v; hbar = h; }

	void repaint() { redraw(); if (externalTile != NULL) { externalTile->redraw(); } }

	void setGridText(Fl_Browser *o) { gridOutputText = o; }

	void setMode(int );

	void setExternalTile(gridTile *t) { externalTile = t; }

	void moveGridPoint(int , int , int , int );

	void setActionWindow(Fl_Window *w) { actionWindow = w; }

	void setGridType(int t) { gridType = t; }
	void setGridLayer(int l) { gridLayer = l; }

	void setPlayerData(ADMPplayer *p) { playerData = p; }
	void setObjectData(ADMPobject *p) { objectData = p; if (gridType == 0 && externalTile != NULL) { externalTile->setObjectData(p); } }

	void setGridVisibility(int );

	void saveGridMap(char *);
	void loadGridMap(char *);

	gridPoint *getGridPointArray() { return gridPoints; }

	void setMapEventHandler(int (*e)()) { eventMapHandler = e; }
	void setTileEventHandler(int (*e)()) { eventTileHandler = e; }

	int getClickedX() { return clickedX; }
	int getClickedY() { return clickedY; }

	int getClickedGridID() { int i = clickedX+(clickedY*gridWidth); if (gridPoints[i].i_objectType == 0) { return -1; } return (gridPoints[i].i_id); }
	int getClickedGridType() { int i = clickedX+(clickedY*gridWidth); return gridPoints[i].i_objectType; }

	int getGridPointHidden(int sx, int sy) { return gridPoints[sx+(sy*gridWidth)].f_isHidden; }
	int getGridPointViewed(int sx, int sy) { return gridPoints[sx+(sy*gridWidth)].f_wasViewed; }
	int getGridPointType(int sx, int sy) { return gridPoints[sx+(sy*gridWidth)].i_objectType; }
	int getGridPointColor(int sx, int sy) { return gridPoints[sx+(sy*gridWidth)].i_currColor; }
	int getGridPointPrevColor(int sx, int sy) { return gridPoints[sx+(sy*gridWidth)].i_prevColor; }

	void setGridPointHidden(int sx, int sy, int h) { if (sx < 0 || sy < 0) { return; } gridPoints[sx+(sy*gridWidth)].f_isHidden = h; repaint(); }
	void setGridPointViewed(int sx, int sy, int v) { if (sx < 0 || sy < 0) { return; } gridPoints[sx+(sy*gridWidth)].f_wasViewed = v; repaint(); }
	void setGridPointColor(int sx, int sy, int c) { gridPoints[sx+(sy*gridWidth)].i_currColor = c; }

	void drawLineOfSight(int , int , int, int, int);
	void checkLineOfSight(int ,int ,int, int, int);
	void setLineOfSight(int , int , int, int);

	void drawCirclePoints(int, int, int, int);
	void drawLine(int , int , int , int );
	void drawCircle(int , int , int );
	void drawSquare(int , int , int , int );
	void drawCorridor(int , int , int);

	void setPlayerIcon(int p, Fl_Image *i) { if (p < 0 || p > MAX_MEMBERS) { printf("setPlayerIcon: error (%d)\n", p); return; } playerIcons[p] = i; }
	void setObjectIcon(int p, Fl_Image *i) { if (p < 0 || p > MAX_OBJECTS) { printf("setObjectIcon: error (%d)\n", p); return; } objectIcons[p] = i; if (gridType == 0 && externalTile != NULL) { externalTile->setObjectIcon(p, i); } }
	void setActiveColor(int c) { currColor = c; }

	void resizeGridMap(int , int );
	void clearGridMap();
	void centreMap(int, int);

	void setAllViewed();

	void setGridPoint(int, gridPoint *);

	void setGridArray(gridPoint *gp) { gridPoints = gp; }

	void setCurrentShape(int i) { currShape = i; }
	void drawShape(int, int);
	void drawBox(int, int, int, int);

	void removeObject(int, int);

	void setShapeSize(int w, int h) { shapeWidth = w; shapeHeight = h; }
	void setShapeFill(int w) { shapeFill = w; }

	void setCurrentAsViewed(int);

	void setLOSAll();

	void remapColors(int, int);

	void setFogOfWar(int);
	void doFogOfWar();

	void saveMapToTemp();
	void undoMapDrawing(int);
	void setGridPointId(int, int, int);

	void copyObject(int, int, int, int);

	void setMapCentre();

	void setGroupData(ADMPgroup *g) { groupData = g; }

	void cleanUp() { if (gridType != 1 && gridPoints != NULL) { free(gridPoints); } } // printf("Free gridPoints\n"); } }

	void setLOSGrid(int, int, int);

	void setShadow(int, int, int, int, int, int);

	Fl_Shared_Image *rotate_image(Fl_Shared_Image *, int );
};

#endif
