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

#include <stdlib.h>
#include <string.h>

#include <stdio.h>
#include <FL/Fl.H>
#include <FL/fl_draw.H>

#include "VCSdefines.h"
#include "gridTile.h"

void gridTile::draw() {
	int sx=0, sy=0, wid=0, hie=0, gx=0, gy=0, mx=0, my=0, i=0, nx=0, ny=0, pos=0, drawme=0, osize=0, ix=0, iy=0;
	int p_type, p_id, p_color, p_shadow, p_hidden, p_viewed, p_pviewed, p_pcolor;

	char text[8];
	Fl_Image *resizedIcon=NULL;

//printf("in gridTile::draw (%d: %d/%d)\n", gridType,gridWidth,gridHeight );

	sx = x(); sy = y();
	wid = w(); hie = h();
	nx = wid/gridSize; ny = hie/gridSize;

	fl_color(colorMap[0]); fl_rectf(sx,sy,wid, hie);

		// only draw the grid points we have to
for (int loop=0; loop < 2; loop++) {
	if (loop == 1) { // put in the grid lines
		fl_color(colorMap[1]);
		ix = 0;
		for (int i=0; i<wid; i+=gridSize) { fl_line(sx+i, sy, sx+i, sy+hie); if ((ix % 10) == 0 && gridType >= 0) { fl_line(sx+i+1, sy, sx+i+1, sy+hie); } ix++; }
		ix = 0;
		for (int i=0; i<hie; i+=gridSize) { fl_line(sx, sy+i, sx+wid, sy+i); if ((ix % 10) == 0 && gridType >= 0) { fl_line(sx, sy+i+1, sx+wid, sy+i+1); } ix++; }
	}
	for (gy=0; gy<ny; gy++) {
		if ((gy + gridTopY) > gridHeight) { break; }
		for (gx=0; gx<nx && gx < gridWidth; gx++) {
			if ((gx + gridTopX) > gridWidth) { break; }
			pos = (gx + gridTopX) + ((gy + gridTopY) * gridWidth);

			p_type = gridPoints[pos].i_objectType;
			p_id = gridPoints[pos].i_id;
			p_color = gridPoints[pos].i_currColor;
			p_pcolor = gridPoints[pos].i_prevColor;
			p_shadow = gridPoints[pos].f_shadow;
			p_hidden = gridPoints[pos].f_isHidden;
			p_viewed = gridPoints[pos].f_wasViewed;
			p_pviewed = gridPoints[pos].f_prevViewed;

			if (p_type != 0 && loop == 1) {
//printf("GP %d/%d = %d\n", (gx + gridTopX), (gy + gridTopY), i);
					// if it's the external grid, check to see if it's been viewed
				drawme = 0;
				osize = 1;
				if (gridType == 0) { drawme = 1; }
				else {
//printf("%d:%d %d:%d:%d:%d:%d:%d:%d:%d\n", gx, gy, gridPoints[pos].i_currColor, gridPoints[pos].i_prevColor, gridPoints[pos].f_wasViewed, gridPoints[pos].f_isHidden, gridPoints[pos].i_objectType, gridPoints[pos].i_mapLayer, gridPoints[pos].i_prevId, gridPoints[pos].i_id);
					if (p_type == GRID_PLAYER) { drawme = 1; }
					else if (p_hidden == 0 && p_viewed == 1) { drawme = 1; }
					else if (p_hidden != 0) {
						i = gridPoints[pos].i_prevColor;
						mx = sx + (gx * gridSize);
						my = sy + (gy * gridSize);
						fl_color(colorMap[i]); fl_rectf(mx+1,my+1,gridSize-1,gridSize-1);
					}
					if (p_type == GRID_MONSTER && playerData[p_id].flags.f_wasViewed == 1) { drawme = 1; }
				}

				if (drawme == 1) {
					mx = sx + (gx * gridSize);
					my = sy + (gy * gridSize);
					if (p_type == GRID_OBJECT) { 
						if (objectData != NULL && p_id >= 0 && p_id < MAX_OBJECTS) {
							if (objectIcons[p_id] != NULL) {
								ix = (objectData[p_id].i_width / 5) * gridSize;
								iy = (objectData[p_id].i_height / 5) * gridSize;
								if (ix < 1) { ix = gridSize; }
								if (iy < 1) { iy = gridSize; }
								if (resizedIcon != NULL) { delete resizedIcon; }
								resizedIcon = objectIcons[p_id]->copy(ix, iy);
								resizedIcon->draw(mx,my,ix,iy);
//printf("Draw object: %d %d:%d %d\n", i, ix, iy, gridSize);
								if (gridType == 0) {		// only draw object marker on the DM screen
									fl_font(FL_TIMES | FL_BOLD, (int )(gridSize/1.3));
									fl_color(FL_BLACK);		// draw the object ID on screen
									fl_draw("+", (int )(mx+(gridSize/3.3)), (int )(my+(gridSize/1.5)));
								}
							} else {
								if (gridType == 0) {		// only draw object on the DM screen
									fl_color(colorMap[2]); 
									fl_rectf(mx,my,gridSize,gridSize);
								}
							}
						}
					} else {
						// only draw real objects and not their shadows
						if (p_shadow == 0) { 
							if (p_type == GRID_PLAYER) { 
								if (playerData != NULL && p_id < MAX_MEMBERS && playerData[p_id].i_hp[HP_MAX] > 0 && playerData[p_id].c_name[0] != '\0') {
									if (playerData[p_id].i_space > 5) { osize = playerData[p_id].i_space / 5; }
								}
								fl_color(colorMap[3]); fl_rectf(mx+1,my+1,(gridSize*osize)-1,(gridSize*osize)-1); 
							} else if (p_type == GRID_MONSTER) {
								fl_color(colorMap[4]); 
//printf("%d = %d:%d:%d\n", pos, p_id, playerData[p_id].flags.f_wasViewed, gridType);
								if (playerData != NULL && (playerData[p_id].flags.f_wasViewed == 1 || gridType == 0)) {
									if (playerData != NULL && p_id < MAX_MEMBERS && playerData[p_id].i_hp[HP_MAX] > 0 && playerData[p_id].c_name[0] != '\0') {
										if (playerData[p_id].i_space > 5) { osize = playerData[p_id].i_space / 5; }
									}
									fl_rectf(mx,my,gridSize*osize,gridSize*osize);
								}
							}
							if (p_id > MAX_MEMBERS) { 
	//printf("BA = %d\n", i); 
								if (resizedIcon != NULL) { delete resizedIcon; }
								return;
							}
							if (playerIcons[p_id] != NULL && playerIcons[p_id]->w() > 0 &&  playerIcons[p_id]->h() > 0) {
								ix = iy = 0;
								if (playerIcons[p_id]->w() > playerIcons[p_id]->h()) {
									iy = (gridSize * osize * playerIcons[p_id]->h()) / playerIcons[p_id]->w();
									if (resizedIcon != NULL) { delete resizedIcon; }
									resizedIcon = playerIcons[p_id]->copy(gridSize*osize, iy);
									iy = ((gridSize * osize) - iy) / 2;
								} else {
									ix = (gridSize * osize * playerIcons[p_id]->w()) / playerIcons[p_id]->h();
									if (resizedIcon != NULL) { delete resizedIcon; }
									resizedIcon = playerIcons[p_id]->copy(ix, gridSize*osize);
									ix = ((gridSize * osize) - ix) / 2;
								}
//if (p_type == GRID_MONSTER) {
//	resizedIcon = rotate_image((Fl_Shared_Image *)resizedIcon, 90);
//}
								resizedIcon->draw(mx+ix,my+iy,gridSize*osize,gridSize*osize); 
	
								if (p_type == GRID_MONSTER && (playerData[p_id].flags.f_wasViewed == 1 || gridType == 0)) {
									fl_color(FL_BLACK);		// draw the monster ID on screen
									if (playerData[p_id].i_space > 5) {
										fl_font(FL_TIMES | FL_BOLD, (int )(gridSize/1.3));
									} else {
										fl_font(FL_TIMES | FL_BOLD, (int )(gridSize/1.6));
									}
									if (playerData[p_id].i_noInGroup > 0) {
										sprintf(text, "%d", playerData[p_id].i_noInGroup);
										fl_draw(text, (int )(mx+(gridSize*osize)-fl_width(text)), (int )(my+(gridSize*osize)-(fl_size()/4)));
									}
									text[0] = playerData[p_id].c_name[0]; text[1] = '\0';
									fl_draw(text, mx+2, (int )(my+2+(fl_height()/1.5)));
								}
							} else if (playerData != NULL && playerData[p_id].i_hp[HP_MAX] > 0 && playerData[p_id].c_name[0] != '\0') {
								fl_rectf(mx,my,gridSize*osize,gridSize*osize);
								text[0] = playerData[p_id].c_name[0]; text[1] = '\0';
								fl_color(FL_BLACK);
								if (playerData[p_id].i_space > 5) {
									fl_font(FL_TIMES | FL_BOLD, (int )(gridSize/1.3));
								} else {
									fl_font(FL_TIMES | FL_BOLD, (int )(gridSize/1.6));
								}
								if (playerData[p_id].i_noInGroup > 0) {
									fl_draw(text, mx, (int )(my+(fl_size()/1.3)));
									sprintf(text, "%d", playerData[p_id].i_noInGroup);
									fl_draw(text, (int )(mx+(gridSize*osize)-fl_width(text)), (int )(my+(gridSize*osize)-(fl_size()/4)));
								} else {
									fl_draw(text, (int )(mx+(gridSize/3.3)), (int )(my+(gridSize/1.5)));
								}
							}
							if (p_type == GRID_MONSTER || p_type == GRID_PLAYER) {
								if ((playerData[p_id].i_hp[HP_CUR] + playerData[p_id].i_hp[HP_ADJ]) < 0) {
									fl_color(FL_RED);
									fl_line(mx, my, mx+(gridSize*osize), my+(gridSize*osize));
									fl_line(mx+1, my, mx+(gridSize*osize), my+(gridSize*osize)-1);
									fl_line(mx+(gridSize*osize), my, mx, my+(gridSize*osize));
									fl_line(mx+(gridSize*osize)-1, my, mx, my+(gridSize*osize)-1);
								}
							}
	//printf("out draw: %d:%d:%s:%s\n", i, osize, playerData[i].c_iconFile, playerIcons[i]);
						}
					}
				}
			} else if (p_color != 0 && loop == 0) {
					// if it's the external grid, check to see if it's been viewed
				if (gridType == 0 || (gridType == 1 && p_hidden == 0 && (p_viewed == 1 || (p_type != 0 && p_pviewed == 1)))) {
					mx = sx + (gx * gridSize);
					my = sy + (gy * gridSize);
					if (p_color < 14) {		// check DM invisible line
						fl_color(colorMap[p_color]); fl_rectf(mx,my,gridSize,gridSize);
					} else {
						if (gridType == 0) { i = p_color; }
						else { i = p_pcolor; }
						fl_color(colorMap[i]); fl_rectf(mx,my,gridSize,gridSize);
					}
				}
//			} else if (gridType == 1 && loop == 0 && p_hidden == 0 && p_type != 0 && p_pviewed == 1 && p_viewed == 0) {
//				fl_color(p_pcolor); fl_rectf(mx,my,gridSize,gridSize);
			}
		}
	}
	if (resizedIcon != NULL) { delete resizedIcon; }
}

}

//*****************************************************************************************
int gridTile::handle(int event) {
	int gx, gy, gpos, i;
	char buf[50];

	if (gridType == 1 || event == 0) { return 1; }		// dont handle events on the external grid map

//printf("Event: E=%d B=%d S=%d X=%d Y=%d T=%d\n", event, Fl::event_button(), Fl::event_state(), Fl::event_x(), Fl::event_y(), gridType);

	gx = gridTopX + ((Fl::event_x() - x()) / gridSize);
	gy = gridTopY + ((Fl::event_y() - y()) / gridSize);

	gpos = gx + (gy * gridWidth);

	if (gpos < 0) { return 1; }

	if (event == FL_DRAG) {
//printf("DRAG Event: E=%d B=%d S=%d X=%d Y=%d %d/%d M=%d\n", event, Fl::event_button(), Fl::event_state(), Fl::event_x(), Fl::event_y(), gx,gy, gridMode);
		switch (gridMode) {
			case MODE_COMBAT:
					fl_rect(Fl::event_x(),Fl::event_y(),gridSize,gridSize,FL_BLACK);
					break;
			case MODE_FREESTYLE:
					if (prevX != gx || prevY != gy) { setGridColor(gx, gy, currColor); prevX = gx; prevY = gy; }
					break;
			case MODE_LINES:
					break;
			case MODE_SHAPES:
					drawShape(gx, gy);
					break;
			case ACTION_10CORRIDOR:
					if (clickedX != gx || clickedY != gy) {
//printf("ACTION_10CORRIDOR: %d:%d %d:%d\n", clickedX, clickedY, gx, gy);
						setGridColor(gx, gy, currColor);
						if (clickedX == gx) { setGridColor(gx+3, gy, currColor); }
						else if (clickedY == gy) { setGridColor(gx, gy-3, currColor); }
						clickedX = gx; clickedY = gy;
					}
					break;
			case ACTION_20CORRIDOR:
					if (clickedX != gx || clickedY != gy) {
						if (clickedX == gx) { setGridColor(gx, gy, currColor); setGridColor(gx+5, gy, currColor); }
						else if (clickedY == gy) { setGridColor(gx, gy, currColor); setGridColor(gx, gy-5, currColor); }
						clickedX = gx; clickedY = gy;
					}
					break;
		}
		prevEvent = FL_DRAG;
	} else if (event == FL_RELEASE) {
//printf("RELS Event: E=%d B=%d S=%d X=%d Y=%d %d/%d\n", event, Fl::event_button(), Fl::event_state(), Fl::event_x(), Fl::event_y(), gx,gy);
		if (prevEvent == FL_DRAG && gridMode == MODE_COMBAT) {
			moveGridPoint(clickedX, clickedY, gx, gy);
		} else if (prevEvent == FL_PUSH && gridMode == MODE_LINES) {
			clickedX = gx; clickedY = gy;
			return 1;
		} else if (prevEvent == FL_PUSH && gridMode == MODE_COMBAT) {
			clickedX = gx; clickedY = gy;
			return 1;
		} else {
			clickedX = clickedY = -1;
			prevEvent = FL_RELEASE;
		}
	} else if (event == FL_PUSH) {
//printf("PUSH Event: E=%d B=%d S=%d X=%d Y=%d %d/%d. Mode = %d\n", event, Fl::event_button(), Fl::event_state(), Fl::event_x(), Fl::event_y(), gx,gy, gridMode);
		if (gridOutputText != NULL) {
			sprintf(buf, "Pressed at %d:%d", gx, gy);
			gridOutputText->text(5, buf);

			sprintf(buf, "C%d:c%d:V%d:H%d:T%d:L%d:i%d:I%d:v%d:h%d:s%d:t%d", gridPoints[gpos].i_currColor, gridPoints[gpos].i_prevColor, gridPoints[gpos].f_wasViewed, gridPoints[gpos].f_isHidden, gridPoints[gpos].i_objectType, gridPoints[gpos].i_mapLayer, gridPoints[gpos].i_prevId, gridPoints[gpos].i_id, gridPoints[gpos].f_prevViewed, gridPoints[gpos].f_prevHidden, gridPoints[gpos].f_shadow, gridPoints[gpos].i_prevType);
			gridOutputText->text(6, buf);

			if (clickedX != -1 && clickedY != -1) {
				if (clickedX == gx) { i = abs(clickedY - gy) * 5; }
				else {
					if (clickedY == gy) { i = abs(clickedX - gx) * 5; }
					else { i = (abs(clickedY - gy) * abs(clickedY - gy)) + (abs(clickedX - gx) * abs(clickedX - gx)); i = (int )sqrt(i)*5; }
				}
//printf("D = %d/%d %d/%d  = %d/%d = %d\n", clickedX, clickedY, gx, gy, abs(clickedX - gx), abs(clickedY - gy), i);
				sprintf(buf, "Distance = %d", i);
				gridOutputText->text(3, buf);
			} else {
				gridOutputText->text(3, "");
			}
		}
//printf("At location: %d/%d (%d)\n", gx, gy, gridPoints[gpos].i_objectType);

			// save a backup copy to undo just incase
		if (gridMode != MODE_COMBAT && gridMode != MODE_COPYOBJECT) { saveMapToTemp(); }

		switch (gridMode) {
			case MODE_COMBAT:
//					clickedX = gx; clickedY = gy;
//					if (Fl::event_button() == 3 && eventHandler != NULL) {	// RMB
//						(*eventHandler)();
//					}
					break;

			case MODE_FREESTYLE:
					if (Fl::event_button() == 1) {
						setGridColor(gx, gy, currColor);
						prevX = gx; prevY = gy;
					}
					break;

			case MODE_LINES:
					if (prevEvent == FL_PUSH && Fl::event_button() == 1) {
						drawLine(clickedX, clickedY, gx, gy);
					}
					break;

			case MODE_SHAPES:
					if (Fl::event_button() == 1) {
						drawShape(gx, gy);
					}
					break;

			case MODE_COPYOBJECT:
//printf("in CopyObj: %d/%d %d/%d\n", copyObjX, copyObjY, gx, gy);
					if (copyObjX == -1 || copyObjY == -1) {
						copyObjX = gx; copyObjY = gy;
					} else {
						copyObject(copyObjX, copyObjY, gx, gy);
					}
					break;
		}
		prevEvent = FL_PUSH;
		clickedX = gx; clickedY = gy;
		if (Fl::event_button() == 3 && eventMapHandler != NULL) {	// RMB - do popup menu
			(*eventMapHandler)();
		}
	} else {
		if ((i = gridPoints[gpos].i_objectType) != 0 && gridOutputText != NULL) {
			gpos = gridPoints[gpos].i_id;
			buf[0] = '\0';
			if (i == GRID_OBJECT && i < MAX_OBJECTS) { 
				if (objectData != NULL) {
					sprintf(buf, "Obj %d %s", gpos, objectData[gpos].c_description);
				}
			} else if (gpos < MAX_MEMBERS && (i == GRID_PLAYER || i == GRID_MONSTER)) { 
				if (playerData != NULL && playerData[gpos].i_hp[HP_MAX] > 0 && playerData[gpos].c_name[0] != '\0') {
					if ((playerData[gpos].i_hp[HP_CUR] + playerData[i].i_hp[HP_ADJ]) < 0) {
						sprintf(buf, "%d%% Attks: %d/%d", ((playerData[gpos].i_hp[HP_CUR] + playerData[i].i_hp[HP_ADJ]) * 10), playerData[gpos].i_doneAttacks, playerData[gpos].i_noAttacks);
					} else {
						sprintf(buf, "%d%% (%d) Attks: %d/%d", ((playerData[gpos].i_hp[HP_CUR] + playerData[i].i_hp[HP_ADJ]) * 100) / playerData[gpos].i_hp[HP_MAX], (playerData[gpos].i_hp[HP_CUR] + playerData[i].i_hp[HP_ADJ]), playerData[gpos].i_doneAttacks, playerData[gpos].i_noAttacks);
					}
					gridOutputText->text(2, buf);
					if (playerData[gpos].i_noInGroup > 0) {
						sprintf(buf, "#In Group: %d", playerData[gpos].i_noInGroup); gridOutputText->text(4, buf);
					}
					sprintf(buf, "Spd:%d %s", playerData[gpos].i_speed, playerData[gpos].c_name);
				}
			}
			gridOutputText->text(1, buf);
		} else {
			gridOutputText->text(1, "");
			gridOutputText->text(2, "");
			gridOutputText->text(4, "");
		}
//printf("Event: E=%d B=%d S=%d X=%d Y=%d\n", event, Fl::event_button(), Fl::event_state(), Fl::event_x(), Fl::event_y());
	}
	return 1;
}

//*****************************************************************************************
gridTile::gridTile(int X, int Y, int W, int H) : Fl_Tile(X,Y,W,H) {
	int i;

	colorMap[0] = FL_WHITE;		// backgroup color
	colorMap[1] = (Fl_Color)16;		// grid line color
	colorMap[2] = FL_RED;		// object color
	colorMap[3] = FL_YELLOW;	// player color
	colorMap[4] = (Fl_Color)61;		// monster color

	colorMap[5] = (Fl_Color)92;	
	colorMap[6] = (Fl_Color)2;	
	colorMap[7] = (Fl_Color)1;	
	colorMap[8] = (Fl_Color)61;	
	colorMap[9] = (Fl_Color)140;	
	colorMap[10] = (Fl_Color)5;	
	colorMap[11] = (Fl_Color)6;	
	colorMap[12] = (Fl_Color)16;	
	colorMap[13] = (Fl_Color)24;	
	colorMap[14] = (Fl_Color)59;	
	colorMap[15] = (Fl_Color)219;	

	gridSize = gridWidth = gridHeight = gridSizePtr = 0;
	gridTopX = gridTopY = gridMode = gridLayer = 0;
	clickedX = clickedY = prevEvent = gridType = gridVisibility = 0;
	deltaX = deltaY = currColor = currShape = 0;
	shapeWidth = shapeHeight = shapeFill = 0;
	prevX = prevY = undoMapCnt = 0;
	prevCentreX = prevCentreY = 0;
	copyObjX = copyObjY = 0;

	losAlgorithm = 0;

	gridSizes[0]=-1;
	gridSizes[1]=4;
	for (i=2; i<25; i++) {
		gridSizes[i] = 3 + (2 * (i-1));
	}
	gridSizes[i]=-1;
	gridPoints = NULL;

	gridSize = GRIDSIZE;
	gridSizePtr=13;

	gridTopX = gridTopY = 0;

	gridMode = ACTION_COMBAT;
	clickedX = clickedY = -1;

	gridOutputText = NULL;

	externalTile = NULL;

	eventMapHandler = NULL;
	eventTileHandler = NULL;

	gridType = deltaX = deltaY = 0;
	prevCentreX = prevCentreY = -1;

	gridVisibility = 13;		// 60'

	currColor = 1;

	shapeWidth = shapeHeight = 20; shapeFill = 0;

	f_fogOfWar = undoMapCnt = 0;

	playerData = NULL; objectData = NULL;
	for (i=0; i<MAX_MEMBERS; i++) { playerIcons[i] = NULL; }
	for (i=0; i<MAX_OBJECTS; i++) { objectIcons[i] = NULL; }

//	losGridSize = 21; 
//	if ((losGrid = (losPoint *)malloc(losGridSize*losGridSize*sizeof(losPoint))) == NULL) {
//		printf("Unable to make losGrid .. bye\n");
//		exit(0);
//	}
//	memset(losGrid, '\0', (losGridSize*losGridSize*sizeof(losPoint)));

	vbar = hbar = NULL;

	setGridSize(MAPSIZE,MAPSIZE);		// make the memory array
}

//*****************************************************************************************
int gridTile::getGridSize() {
	return gridSize;
}

//*****************************************************************************************
int gridTile::setGridSize(int sz) {
	gridSizePtr += sz;
	if (gridSizes[gridSizePtr] == -1) { gridSizePtr -= sz; return 0; }
	gridSize = gridSizes[gridSizePtr];
//printf("gridTile::setGridSize = %d:%d\n", gridSizePtr, gridSizes[gridSizePtr]);
	repaint();
	return 0;
}

//*****************************************************************************************
int gridTile::setGridSize(int sx, int sy) {
//printf("gridTile::setGridSize %d = %d:%d\n", gridType, sx, sy);
	gridWidth = sx; gridHeight = sy;

	if (gridType == 1) { return 1; }
	if (gridPoints != NULL) { free(gridPoints); }

	gridPoints = (gridPoint *)malloc(sy*sx*sizeof(gridPoint));

	memset(gridPoints, '\0', (sy*sx*sizeof(gridPoint)));

	if (externalTile != NULL) { externalTile->setGridArray(gridPoints); externalTile->setGridSize(sx, sy); }

	if (vbar != NULL) { vbar->maximum(sx); vbar->linesize(sx/13); }
	if (hbar != NULL) { hbar->maximum(sy); hbar->linesize(sy/13); }

	return 0;
}

//*****************************************************************************************
int gridTile::setGridColor(int sx, int sy, int color) {
	int pos;

	pos = sx+(sy*gridWidth);

//printf("gridTile::setGridColor %d %d = %d/%d\n", sx, sy, color, gridPoints[pos].i_prevColor );
	if (gridType == 1) { return 1; }

	if (sx < 0 || sy < 0) { return 0; }
	if (sx > gridWidth) { sx = gridWidth; }
	if (sy > gridHeight) { sy = gridHeight; }

	gridPoints[pos].i_prevColor = gridPoints[pos].i_currColor;
	gridPoints[pos].i_currColor = color;
//	if (gridPoints[pos].i_objectType != 0) { gridPoints[pos].i_prevColor = color; }
//	if (gridType == 1 && externalTile != NULL) { externalTile->setGridPoint(pos, &gridPoints[pos]); }
	repaint();
	return 0;
}

//*****************************************************************************************
int gridTile::setGridType(int sx, int sy, int type, int id) {
	int pos;

	if (gridType == 1) { return 1; }

	if (sx < 0 || sy < 0) { return 0; }
	if (sx > gridWidth) { sx = gridWidth; }
	if (sy > gridHeight) { sy = gridHeight; }

	pos = sx+(sy*gridWidth);
	gridPoints[pos].i_objectType = type;
	gridPoints[pos].i_id = id;

	if (gridType == 0 && type == GRID_PLAYER) {
		setLineOfSight(sx, sy, gridVisibility, id);
	}
	if (externalTile != NULL) { externalTile->redraw(); }
	if (type != 0) {
		gridPoints[pos].i_prevColor = gridPoints[pos].i_currColor;
	}
	if (playerData != NULL && (type == GRID_PLAYER || type == GRID_MONSTER)) {
		if (playerData[id].i_mapX != -1 || playerData[id].i_mapY != -1) {
			pos = playerData[id].i_mapX + (playerData[id].i_mapY * gridWidth);
			type = gridPoints[pos].i_objectType;
			if ((type == GRID_PLAYER || type == GRID_MONSTER) && gridPoints[pos].i_id == id) {
				gridPoints[pos].i_objectType = gridPoints[pos].i_id = gridPoints[pos].i_prevId = 0;
			}
		}
		playerData[id].i_mapX = sx; playerData[id].i_mapY = sy;
		setShadow(sx, sy, id, type, (playerData[id].i_space/5), 1);
	}
//	if (gridType == 1 && externalTile != NULL) { externalTile->setGridPoint(pos, &gridPoints[pos]); }
	return 0;
}

//*****************************************************************************************
int gridTile::setColorMap(int x, Fl_Color color) {
	if (x < 0 || x > 15) { printf("gridTile::setColorMap: error (%d)\n", x); return 0; }
	colorMap[x] = color;
	if (externalTile != NULL) { externalTile->setColorMap(x, color); }
	return 0;
}

//*****************************************************************************************
Fl_Color gridTile::getColorMap(int x) {
	if (x < 0 || x > 15) { printf("gridTile::getColorMap: error (%d)\n", x); return colorMap[0]; }
	return colorMap[x];
}

//*****************************************************************************************
int gridTile::setGridTop(int x, int y) {
	int nx, ny;

//printf("gridTile::setGridTop %d:%d\n", x, y);
	nx = (w() / gridSize);
	ny = (h() / gridSize);

	if (x < 0) { x = 0; }
	if (y < 0) { y = 0; }

	if ((x + nx) > gridWidth) { x =  gridWidth - nx; }
	if ((y + ny) > gridHeight) { y = gridHeight - ny; }

	gridTopX = x; gridTopY = y;

	repaint();
	return 0;
}

//*****************************************************************************************
int gridTile::getGridTopX() {
	return gridTopX;
}

//*****************************************************************************************
int gridTile::getGridTopY() {
	return gridTopY;
}

//*****************************************************************************************
void gridTile::moveGridPoint(int px, int py, int nx, int ny) {
	int opos, npos, sz=1, id=-1, ty=-1;

//printf("gridTile::moveGridPoint %d/%d = %d/%d\n", px,py,nx,ny);
	if (gridType == 1) { return; }

	if (px == nx && py == ny) { return; }
	if (nx < 0 || ny < 0) { return; }
	if (px > gridWidth) { return; }
	if (py > gridHeight) { return; }
	if (nx > gridWidth) { nx = gridWidth; }
	if (ny > gridHeight) { ny = gridHeight; }

	opos = px+(py*gridWidth); npos = nx+(ny*gridWidth);

		// dont allow them to drag a shadow
	if (gridPoints[opos].i_objectType != 0 && gridPoints[opos].f_shadow == 1) {
		return;
	}

//	if (gridPoints[opos].i_id != 0 && (gridPoints[opos].i_objectType == GRID_PLAYER || gridPoints[opos].i_objectType == GRID_MONSTER)) {
	if (gridPoints[opos].i_objectType == GRID_PLAYER || gridPoints[opos].i_objectType == GRID_MONSTER) {
		if (playerData != NULL) {
			sz = playerData[gridPoints[opos].i_id].i_space / 5;
		}
		id = gridPoints[opos].i_id;
		ty = gridPoints[opos].i_objectType;
		if (sz > 1) { setShadow(px, py, id, ty, sz, 0); }
	}

	if ((gridPoints[npos].i_id == 0 && gridPoints[npos].i_objectType == 0) || gridPoints[npos].f_shadow == 1) {
		gridPoints[npos].f_prevViewed = gridPoints[npos].f_wasViewed;		// save what is there
		gridPoints[npos].f_prevHidden = gridPoints[npos].f_isHidden;
		gridPoints[npos].i_prevType = gridPoints[npos].i_objectType;
		gridPoints[npos].i_prevColor = gridPoints[npos].i_currColor;
//		gridPoints[npos].i_prevId = gridPoints[npos].i_Id;
		if (gridPoints[npos].f_shadow == 1) {
			gridPoints[npos].f_shadow = 0;
			gridPoints[npos].i_prevType = 0;
		}

		gridPoints[npos].i_currColor = gridPoints[opos].i_currColor;
		gridPoints[opos].i_currColor = gridPoints[opos].i_prevColor;
		gridPoints[npos].f_wasViewed = gridPoints[opos].f_wasViewed;
		gridPoints[npos].f_isHidden = gridPoints[opos].f_isHidden;
		gridPoints[npos].i_objectType = gridPoints[opos].i_objectType;
		gridPoints[npos].i_id = gridPoints[opos].i_id;

		gridPoints[opos].f_isHidden = gridPoints[opos].i_id = gridPoints[opos].i_prevId = gridPoints[opos].i_objectType = 0;
		gridPoints[opos].f_wasViewed = gridPoints[opos].f_prevViewed;		// restore what was there
		gridPoints[opos].f_isHidden = gridPoints[opos].f_prevHidden;
		gridPoints[opos].i_objectType = gridPoints[opos].i_prevType;
//		gridPoints[opos].i_Id = gridPoints[opos].i_prevId;

		if (gridType == 0 && (ty == GRID_PLAYER || ty == GRID_MONSTER)) {
			gridPoints[npos].i_currColor = 0;
		}
	}
//	if (externalTile != NULL) { externalTile->moveGridPoint(px,py,nx,ny); }

	if (id != -1 && (ty == GRID_PLAYER || ty == GRID_MONSTER) && sz > 1) {
		setShadow(nx, ny, id, ty, sz, 1);
	}

//	if (gridType == 0 && (gridPoints[npos].i_objectType == GRID_PLAYER || gridPoints[npos].i_objectType == GRID_MONSTER)) {
//		opos = gridPoints[npos].i_id;
	if (gridType == 0 && (ty == GRID_PLAYER || ty == GRID_MONSTER)) {
		playerData[id].i_mapX = nx; playerData[id].i_mapY = ny;
	}

	if (gridType == 0 && f_fogOfWar != 0) { doFogOfWar(); }

	if (gridType == 0 && gridPoints[npos].i_objectType == GRID_PLAYER) {
			// do a LOS at the midpoint .. you could do another but ...
		opos = (px + nx) / 2;
		npos = (py + ny) / 2;
		setLineOfSight(opos, npos, gridVisibility, gridPoints[npos].i_id);

//		if (gridType == 0 && f_fogOfWar != 0) { 
//			doFogOfWar(); setLOSAll(); 
//		} else {
		if (gridType == 0 && f_fogOfWar == 0) { 
			setLineOfSight(nx, ny, gridVisibility, gridPoints[npos].i_id);
		}
//	} else if (gridPoints[npos].i_objectType == GRID_MONSTER) {
//		setLOSAll();
	}
	if (gridType == 0 && f_fogOfWar != 0) { setLOSAll(); }
	repaint();
}

//*****************************************************************************************
void gridTile::setGridVisibility(int v) {
	switch (v) {
		case 0: gridVisibility = 7; break;
		case 1: gridVisibility = 13; break;
		case 2: gridVisibility = 19; break;
		case 3: gridVisibility = 25; break;
		case 4: gridVisibility = 41; break;
	}
}

//*****************************************************************************************
void gridTile::saveGridMap(char *n) {
	FILE *sm;
	int i=0, x, y;

	if ((sm = fopen(n, "w+")) != NULL) {
		fprintf(sm, "145\n"); 													// data version
		fprintf(sm, "1 %d %d\n", gridWidth, gridHeight);				// grid dimensions
		fprintf(sm, "2 ");
		for (i=0; i<16; i++) { fprintf(sm, "%d ", colorMap[i]); }	// color map
		fprintf(sm, "\n");
			// dump object data
//		x = 0;
//		for (i=0; i<MAX_OBJECTS; i++) {
//			if (objectData[i].c_description[0] != '\0' || objectData[i].c_iconFile[0] != '\0') { x++; }
//		}
//
//		fprintf(sm, "%d\n", x);
		for (i=0; i<MAX_OBJECTS; i++) {
			y = strlen(objectData[i].c_description);
			if (objectData[i].c_description[y] == '\n') { objectData[i].c_description[y] = '\0'; }
			if (objectData[i].c_description[y+1] == '\n') { objectData[i].c_description[y+1] = '\0'; }
			if (objectData[i].c_description[y-1] == '\n') { objectData[i].c_description[y-1] = '\0'; }
			if (objectData[i].c_description[y-2] == '\n') { objectData[i].c_description[y-2] = '\0'; }
			y = strlen(objectData[i].c_iconFile);
			if (objectData[i].c_iconFile[y] == '\n') { objectData[i].c_iconFile[y] = '\0'; }
			if (objectData[i].c_iconFile[y+1] == '\n') { objectData[i].c_iconFile[y+1] = '\0'; }
			if (objectData[i].c_iconFile[y-1] == '\n') { objectData[i].c_iconFile[y-1] = '\0'; }
			if (objectData[i].c_iconFile[y-2] == '\n') { objectData[i].c_iconFile[y-2] = '\0'; }
			if (objectData[i].c_description[0] != '\0' || objectData[i].c_iconFile[0] != '\0') { 
				fprintf(sm, "3 %d|%s |%s |%d|%d\n", objectData[i].i_id, objectData[i].c_description, objectData[i].c_iconFile, objectData[i].i_width, objectData[i].i_height); 
			}
		}
			// save group name data
//		i = MAX_GROUPS; fprintf(sm, "%d\n", i);
		for (i=0; i<MAX_GROUPS; i++) { fprintf(sm, "4 %s\n", groupData[i].c_description); }

			// TODO - screen size
		fprintf(sm, "5 %d %d %d %d %d 0 0\n", gridTopX, gridTopY, gridSizePtr, vbar->value(), hbar->value());

		for (y=0; y<gridHeight; y++) {
			i = y * gridWidth;
			for (x=0; x<gridWidth; x++) {
				if (gridPoints[i].i_currColor !=0 || gridPoints[i].i_prevColor != 0 || gridPoints[i].i_objectType != 0) {
fprintf(sm, "9 %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n", x, y,
gridPoints[i].i_currColor,
gridPoints[i].i_prevColor,
gridPoints[i].f_wasViewed,
gridPoints[i].f_isHidden,
gridPoints[i].i_objectType,
gridPoints[i].i_mapLayer,
gridPoints[i].i_prevId,
gridPoints[i].i_id,
gridPoints[i].f_prevViewed,
gridPoints[i].f_prevHidden,
gridPoints[i].i_prevType,
gridPoints[i].f_shadow);
				}
				i++;
			}
		}
		fclose(sm);
	}
}

//*****************************************************************************************
void gridTile::loadGridMap(char *n) {
	FILE *sm;
	unsigned int i=0, x, y, version, j;
	int k;
	unsigned int i_currColor=0, i_prevColor=0, f_wasViewed=0, f_isHidden=0, i_objectType=0, i_mapLayer=0, i_prevId=0, 
					i_id=0, i_prevObjectType=0, f_prevViewed=0, f_prevHidden=0, i_prevType=0, i_lastX, i_lastY, i_lastZoom,
					f_shadow=0;
	char buf[200], *cp, *cp2;
	int sliderX, sliderY;
	int grpIndx=0, objIndx=0;

	if ((sm = fopen(n, "r")) != NULL) {
		if (fgets(buf, 100, sm) == NULL) { return; }
		version = atoi(buf);

		if (version > 130) {
			while (fgets(buf, 190, sm) != NULL) {
				switch (buf[0]) {
					case '1':	// map dimensions
								k=sscanf(&buf[2], "%d %d", &gridWidth, &gridHeight);
//printf("gridTile::loadGridMap WH = %s %d/%d %d\n", n, gridWidth, gridHeight, version);
								setGridSize(gridWidth, gridHeight);
								break;
					case '2':	// color map
								cp = strtok(&buf[2], " "); colorMap[0] = (Fl_Color )atoi(cp);
								if (externalTile != NULL) { externalTile->setColorMap(0, colorMap[0]); }
								for (i=1; i<16; i++) {
									cp = strtok(NULL, " ");
									colorMap[i] = (Fl_Color )atoi(cp);
									if (externalTile != NULL) { externalTile->setColorMap(i, colorMap[i]); }
								}
								break;
					case '3':	// object data
								if (objectData != NULL) { 
									cp = strtok(&buf[2], "|");
									if ((j = atoi(cp)) < MAX_OBJECTS) {
//printf("gridTile::loadGridMap = %d %d/%s\n", i, j, buf);
										objectData[j].i_id = j;
										if ((cp = strtok(NULL, "|")) != NULL) {
											strncpy(objectData[j].c_description, cp, MAX_OBJECTDESC-1); objectData[j].c_description[MAX_OBJECTDESC] = '\0';
											if ((cp2 = rindex(objectData[j].c_description, ' ')) != NULL) {
												*cp2 = '\0';
											}
										}
										if ((cp = strtok(NULL, "|")) != NULL) {
											strncpy(objectData[j].c_iconFile, cp, 59); objectData[j].c_iconFile[59] = '\0';
											if ((cp2 = rindex(objectData[j].c_iconFile, ' ')) != NULL) {
												*cp2 = '\0';
											}
										}
										if ((cp = strtok(NULL, "|")) != NULL) { objectData[j].i_width = atoi(cp); }
										if ((cp = strtok(NULL, "|")) != NULL) { objectData[j].i_height = atoi(cp); }
//printf("gridTile::loadGridMap = %d:%s:%s:\n", j, objectData[j].c_description, objectData[j].c_iconFile);
									}
								}
								break;
					case '4':	// group data
								i = grpIndx; grpIndx++;
								strncpy(groupData[i].c_description, &buf[2], 29); 
								x = strlen(groupData[i].c_description);
								if (groupData[i].c_description[x] == '\n') { groupData[i].c_description[x] = '\0'; }
								if (groupData[i].c_description[x-1] == '\n') { groupData[i].c_description[x-1] = '\0'; }
								if (groupData[i].c_description[x-2] == '\n') { groupData[i].c_description[x-2] = '\0'; }
								if (x < 2) { sprintf(groupData[i].c_description, "Group - %d", grpIndx); }
								break;
					case '5':	// screen size, location etc
								k=sscanf(&buf[2], "%d %d %d %d %d %d %d", &i_lastX, &i_lastY, &i_lastZoom, &sliderX, &sliderY, &i, &k);
								vbar->value(sliderX);
								hbar->value(sliderY);
								vbar->redraw();
								hbar->redraw();
								gridTopX = i_lastX; gridTopY = i_lastY;
								gridSize = gridSizes[i_lastZoom];
								gridSizePtr = i_lastZoom;
								if (externalTile != NULL) { externalTile->centreMap(i_lastX, i_lastY); }
								break;
					case '6':	//
								break;
					case '7':	//
								break;
					case '8':	//
								break;
					case '9':	// grid point data
								if (version > 140) {
									k=sscanf(&buf[2], "%d %d %d %d %d %d %d %d %d %d %d %d %d %d", &x, &y,
									&i_currColor, &i_prevColor, &f_wasViewed, &f_isHidden, &i_objectType, &i_mapLayer, &i_prevId, &i_id,
									&f_prevViewed, &f_prevHidden, &i_prevType, &f_shadow);
								} else {
									k=sscanf(&buf[2], "%d %d %d %d %d %d %d %d %d %d %d %d %d", &x, &y,
									&i_currColor, &i_prevColor, &f_wasViewed, &f_isHidden, &i_objectType, &i_mapLayer, &i_prevId, &i_id,
									&f_prevViewed, &f_prevHidden, &i_prevType);
								}
								if (x < gridWidth && y < gridHeight) {
									i = x + (y * gridWidth);
									gridPoints[i].i_currColor = i_currColor;
									gridPoints[i].i_prevColor = i_prevColor;
									gridPoints[i].f_wasViewed = f_wasViewed;
									gridPoints[i].f_isHidden = f_isHidden;
									gridPoints[i].i_objectType = i_objectType;
									gridPoints[i].i_mapLayer = i_mapLayer;
									gridPoints[i].i_prevId = i_prevId;
									gridPoints[i].i_id = i_id;
									gridPoints[i].f_prevViewed = f_prevViewed;
									gridPoints[i].f_prevHidden = f_prevHidden;
									gridPoints[i].i_prevType = i_prevType;
									gridPoints[i].f_shadow = f_shadow;
									if (playerData != NULL && (i_objectType == GRID_PLAYER || i_objectType == GRID_MONSTER) && f_shadow == 0) {
										if (i_id < MAX_MEMBERS) { playerData[i_id].i_mapX = x; playerData[i_id].i_mapY = y; }
									}
								}
								break;
				}
			}
		} else {
			fgets(buf, 100, sm); cp = strtok(buf, " "); gridWidth = atoi(cp); cp = strtok(NULL, " "); gridHeight = atoi(cp);
	//printf("gridTile::loadGridMap WH = %s %d/%d %d\n", n, gridWidth, gridHeight, version);
			setGridSize(gridWidth, gridHeight);
			fgets(buf, 100, sm); cp = strtok(buf, " "); colorMap[0] = (Fl_Color )atoi(cp);
			for (i=1; i<16; i++) {
				cp = strtok(NULL, " ");
				colorMap[i] = (Fl_Color )atoi(cp);
				if (externalTile != NULL) { externalTile->setColorMap(i, colorMap[i]); }
			}
	//printf("gridTile::loadGridMap CM0 = %d\n", colorMap[0]);
			fgets(buf, 100, sm); i = atoi(buf);
			for (; i>0; i--) {
				fgets(buf, 100, sm);
	//printf("gridTile::loadGridMap = %d %d/%s\n", i, j, buf);
				if (objectData != NULL) { 
					cp = strtok(buf, "|");
					if ((j = atoi(cp)) < MAX_OBJECTS) {
	//printf("gridTile::loadGridMap = %d %d/%s\n", i, j, buf);
						objectData[j].i_id = j;
						if ((cp = strtok(NULL, "|")) != NULL) {
							strncpy(objectData[j].c_description, cp, MAX_OBJECTDESC-1); objectData[j].c_description[MAX_OBJECTDESC] = '\0';
							if ((cp2 = rindex(objectData[j].c_description, ' ')) != NULL) {
								*cp2 = '\0';
							}
						}
						if ((cp = strtok(NULL, "|")) != NULL) {
							strncpy(objectData[j].c_iconFile, cp, 59); objectData[j].c_iconFile[59] = '\0';
							if ((cp2 = rindex(objectData[j].c_iconFile, ' ')) != NULL) {
								*cp2 = '\0';
							}
						}
						if ((cp = strtok(NULL, "|")) != NULL) { objectData[j].i_width = atoi(cp); }
						if ((cp = strtok(NULL, "|")) != NULL) { objectData[j].i_height = atoi(cp); }
	//printf("gridTile::loadGridMap = %d:%s:%s:\n", j, objectData[j].c_description, objectData[j].c_iconFile);
					}
				}
			}
			if (version > 110) {		// group info is now here
				fgets(buf, 100, sm); k = atoi(buf);
				for (i=0; i<k; i++) { 
					fgets(groupData[i].c_description, 29, sm); 
					x = strlen(groupData[i].c_description);
					if (groupData[i].c_description[x] == '\n') { groupData[i].c_description[x] = '\0'; }
					if (groupData[i].c_description[x-1] == '\n') { groupData[i].c_description[x-1] = '\0'; }
					if (groupData[i].c_description[x-2] == '\n') { groupData[i].c_description[x-2] = '\0'; }
	//printf("gridTile::loadGridMap = %s/%d\n", groupData[i].c_description, i);
	}
			}
	
			if (version > 120) {		// last location etc here
					// TODO - screen size
				k=fscanf(sm, "%d %d %d %d %d %d %d", &i_lastX, &i_lastY, &i_lastZoom, &sliderX, &sliderY, &i, &k);
				vbar->value(sliderX);
				hbar->value(sliderY);
				vbar->redraw();
				hbar->redraw();
				gridTopX = i_lastX; gridTopY = i_lastY;
				gridSize = gridSizes[i_lastZoom];
				gridSizePtr = i_lastZoom;
				if (externalTile != NULL) { externalTile->centreMap(i_lastX, i_lastY); }
			}
	
			if (version == 100) {
				k=fscanf(sm, "%d %d %d %d %d %d %d %d %d %d", &x, &y,
				&i_currColor, &i_prevColor, &f_wasViewed, &f_isHidden, &i_objectType, &i_mapLayer, &i_prevId, &i_id);
			} else {
				k=fscanf(sm, "%d %d %d %d %d %d %d %d %d %d %d %d %d", &x, &y,
				&i_currColor, &i_prevColor, &f_wasViewed, &f_isHidden, &i_objectType, &i_mapLayer, &i_prevId, &i_id,
				&f_prevViewed, &f_prevHidden, &i_prevType);
			}
			while (k != EOF) {
	//printf("gridTile::loadGridMap = %d/%d\n", x, y);
				if (x < gridWidth && y < gridHeight) {
					i = x + (y * gridWidth);
					gridPoints[i].i_currColor = i_currColor;
					gridPoints[i].i_prevColor = i_prevColor;
					gridPoints[i].f_wasViewed = f_wasViewed;
					gridPoints[i].f_isHidden = f_isHidden;
					gridPoints[i].i_objectType = i_objectType;
					gridPoints[i].i_mapLayer = i_mapLayer;
					gridPoints[i].i_prevId = i_prevId;
					gridPoints[i].i_id = i_id;
					gridPoints[i].f_prevViewed = f_prevViewed;
					gridPoints[i].f_prevHidden = f_prevHidden;
					gridPoints[i].i_prevType = i_prevType;
					if (playerData != NULL && (i_objectType == GRID_PLAYER || i_objectType == GRID_MONSTER)) {
						if (i_id < MAX_MEMBERS) { playerData[i_id].i_mapX = x; playerData[i_id].i_mapY = y; }
					}
				}
				if (version == 100) {
					k=fscanf(sm, "%d %d %d %d %d %d %d %d %d %d", &x, &y,
					&i_currColor, &i_prevColor, &f_wasViewed, &f_isHidden, &i_objectType, &i_mapLayer, &i_prevId, &i_id);
				} else {
					k=fscanf(sm, "%d %d %d %d %d %d %d %d %d %d %d %d %d", &x, &y,
					&i_currColor, &i_prevColor, &f_wasViewed, &f_isHidden, &i_objectType, &i_mapLayer, &i_prevId, &i_id,
					&f_prevViewed, &f_prevHidden, &i_prevType);
				}
			}	
		}
	}
	repaint();
}

//*****************************************************************************************
void gridTile::drawLineOfSight(int x1, int y1, int x2, int y2, int pid) {
int deltax, deltay, x, y, xinc1, xinc2, yinc1, yinc2, den, num, numadd, numpixels, curpixel, pos, id;

//if (pid == 0) printf("gridTile::drawLineOfSight %d:%d - %d:%d\n", x1,y1, x2,y2);
	if (x2 > gridWidth) { x2 = gridWidth; }
	if (y2 > gridHeight) { y2 = gridHeight; }

	deltax = abs(x2 - x1);        // The difference between the x's
	deltay = abs(y2 - y1);        // The difference between the y's
	x = x1;                       // Start x off at the first pixel
	y = y1;                       // Start y off at the first pixel
		
	if (x2 >= x1)                 // The x-values are increasing
	{
		xinc1 = 1; xinc2 = 1;
	}
	else                          // The x-values are decreasing
	{
		xinc1 = -1; xinc2 = -1;
	}
		
	if (y2 >= y1)                 // The y-values are increasing
	{
		yinc1 = 1; yinc2 = 1;
	}
	else                          // The y-values are decreasing
	{
		yinc1 = -1; yinc2 = -1;
	}
		
	if (deltax >= deltay)         // There is at least one x-value for every y-value
	{
		xinc1 = 0;                  // Don't change the x when numerator >= denominator
		yinc2 = 0;                  // Don't change the y for every iteration
		den = deltax;
		num = deltax / 2;
		numadd = deltay;
		numpixels = deltax;         // There are more x-values than y-values
	}
	else                          // There is at least one y-value for every x-value
	{
		xinc2 = 0;                  // Don't change the x for every iteration
		yinc1 = 0;                  // Don't change the y when numerator >= denominator
		den = deltay;
		num = deltay / 2;
		numadd = deltax;
		numpixels = deltay;         // There are more y-values than x-values
	}
		
	for (curpixel = 0; curpixel <= numpixels; curpixel++) {
		if (x > -1 && y > -1) {
			pos = x + (y*gridWidth);
			if (gridPoints[pos].i_currColor != 0 || gridPoints[pos].i_objectType != 0) {		// if we hit a wall stop
				gridPoints[pos].f_wasViewed = 1;
				id = gridPoints[pos].i_id;
//if (pid == 0) printf("LoS: %d:%d = %d:%d\n", x, y, id, gridPoints[pos].i_currColor);
				if (gridPoints[pos].i_objectType == GRID_MONSTER && id != 0 && playerData[id].flags.f_invisible == 0) {
					playerData[id].flags.f_wasViewed = 1;
//if (pid == 0) printf("LoS: %d:%d = %d\n", x, y, id);
				}
			}
			if (gridPoints[pos].i_currColor > 7) {		// if we hit anything stop
				if (gridPoints[pos].i_objectType == GRID_PLAYER) {								// JIC ignore the players initial spot
					if (playerData[id].i_mapX != x && playerData[id].i_mapY != y) {
						break;
					}
				} else {
					break;
				}
			}
			num += numadd;              // Increase the numerator by the top of the fraction
			if (num >= den)             // Check if numerator >= denominator
			{
				num -= den;               // Calculate the new numerator value
				x += xinc1;               // Change the x as appropriate
				y += yinc1;               // Change the y as appropriate
			}
			x += xinc2;                 // Change the x as appropriate
			y += yinc2;                 // Change the y as appropriate
		}
	}
}

//*****************************************************************************************
void gridTile::checkLineOfSight(int cx, int cy, int x, int y, int id) {
	if (x > gridWidth) { x = gridWidth; }
	if (y > gridHeight) { y = gridHeight; }

	if (x == 0) {
		drawLineOfSight(cx, cy, cx, cy + y, id);
		drawLineOfSight(cx, cy, cx, cy - y, id);
		drawLineOfSight(cx, cy, cx + y, cy, id);
		drawLineOfSight(cx, cy, cx - y, cy, id);
	} else if (x == y) {
		drawLineOfSight(cx, cy, cx + x, cy + y, id);
		drawLineOfSight(cx, cy, cx - x, cy + y, id);
		drawLineOfSight(cx, cy, cx + x, cy - y, id);
		drawLineOfSight(cx, cy, cx - x, cy - y, id);
	} else if (x < y) {
		drawLineOfSight(cx, cy, cx + x, cy + y, id);
		drawLineOfSight(cx, cy, cx - x, cy + y, id);
		drawLineOfSight(cx, cy, cx + x, cy - y, id);
		drawLineOfSight(cx, cy, cx - x, cy - y, id);
		drawLineOfSight(cx, cy, cx + y, cy + x, id);
		drawLineOfSight(cx, cy, cx - y, cy + x, id);
		drawLineOfSight(cx, cy, cx + y, cy - x, id);
		drawLineOfSight(cx, cy, cx - y, cy - x, id);
	}
}

//*****************************************************************************************
void gridTile::setLOSGrid(int px, int py, int d) {
int sx, sy, mx, my, i=0, j=0, k, gp, lp;
char losID[MAX_MEMBERS];

	if (losAlgorithm != 1) { return; }

	if (d > losGridSize) {		// should we resize the losGrid
//printf("gridTile::setLOSGrid = %d/%d\n", d, losGridSize);
		d = losGridSize;
	}

	memset(losGrid, '\0', (losGridSize*losGridSize*sizeof(losPoint)));
	memset(losID, 255, MAX_MEMBERS);

	sx = px-d; if (sx < 0) { sy = 0; } 
	mx = px+d; if (mx >gridWidth) { mx = gridWidth; }

	sy = py-d; if (sy < 0) { sy = 0; } 
	my = py+d; if (my >gridHeight) { my = gridHeight; }
//printf("gridTile::setLOSGrid = %d/%d/%d %d:%d %d:%d\n", px, py, d, sx, sy, mx, my);

	j = i = 0;
	for ( ; sy <= my; sy++) {
		gp = (sy * gridWidth) + sx;
		lp = (j * losGridSize);
		k = sx;
printf("\n%2.2d = ", j);
		for ( ; k <= mx; k++) {
			losGrid[lp].i_currColor = gridPoints[gp].i_currColor;
			losGrid[lp].i_objectType = gridPoints[gp].i_objectType;
			losGrid[lp].i_id = gridPoints[gp].i_id;
printf(" %d:%d:%d", losGrid[lp].i_objectType, losGrid[lp].i_id, losGrid[lp].i_currColor);
			lp++; gp++;
		}
		j++;
	}
printf("\n");

	for (j=0; j<losGridSize; j++) {
		lp = (j * losGridSize);
		for (i=0; i<losGridSize; i++) {
			if (losGrid[lp].i_objectType == GRID_MONSTER || losGrid[lp].i_objectType == GRID_PLAYER) {
				sx = losGrid[lp].i_id; k = (playerData[sx].i_space/5) - 1;
				if (losID[sx] != -1) { k = -1; }
printf("Found %d = %d\n", sx, k);
				while (k > -1) {
					sy = (playerData[sx].i_space/5) - 1;
					gp = lp + (k * losGridSize);
					while (sy > -1) {
						if (losGrid[gp].i_objectType == 0 || losGrid[gp].i_currColor < 8) {
							losGrid[gp].i_objectType = losGrid[lp].i_objectType;
							losGrid[gp].i_id = losGrid[lp].i_id;
						}
						gp++; sy--;
					}
					k--;
				}
				losID[sx] = sx;
			}
			lp++;
		}
	}

	for (j=0; j<(d*2); j++) {
		lp = (j * losGridSize);
printf("\n%2.2d = ", j);
		for (i=0; i<(d*2); i++) {
printf(" %d:%d:%d", losGrid[lp].i_objectType, losGrid[lp].i_id, losGrid[lp].i_currColor);
			lp++;
		}
	}
printf("\n");
}

//*****************************************************************************************
void gridTile::setLineOfSight(int sx, int sy, int d, int id) {
int x = 0, y = d, p = (5 - d*4)/4, i, j, lp=0, nx, ny;

	if (gridType == 1) { return; }
//printf("gridTile::setLineOfSight %d:%d:%d:%d\n", sx,sy,d,id);

//	if (losAlgorithm == 1) {
//		setLOSGrid(sx, sy, d+3);
//		nx = -1; ny = -1;
//		for (j=0; j<losGridSize; j++) {
//			for (i=0; i<losGridSize; i++) {
//				if (losGrid[p].i_id == id && losGrid[p].i_objectType == GRID_PLAYER) {
//					nx = i; ny = j;
//					break;
//				}
//			}
//		}
//printf("gridTile::setLineOfSight %d:%d:%d\n", nx,ny,losGridSize);
//		if (nx == -1 || ny == -1) { return; }
//	} else {
		nx = sx; ny = sy;
//	}

	checkLineOfSight(nx, ny, x, y, id);
	while (x < y) {
		x++;
		if (p < 0) {
			p += 2*x+1;
		} else {
			y--;
			p += 2*(x-y)+1;
		}
		checkLineOfSight(nx, ny, x, y, id);
	}
}

//*****************************************************************************************
void gridTile::drawLine(int x1, int y1, int x2, int y2) {
int deltax, deltay, x, y, xinc1, xinc2, yinc1, yinc2, den, num, numadd, numpixels, curpixel;

	if (gridType == 1) { return; }

	if (x2 > gridWidth) { x2 = gridWidth; }
	if (y2 > gridHeight) { y2 = gridHeight; }

	deltax = abs(x2 - x1);        // The difference between the x's
	deltay = abs(y2 - y1);        // The difference between the y's
	x = x1;                       // Start x off at the first pixel
	y = y1;                       // Start y off at the first pixel
		
	if (x2 >= x1)                 // The x-values are increasing
	{
		xinc1 = 1; xinc2 = 1;
	}
	else                          // The x-values are decreasing
	{
		xinc1 = -1; xinc2 = -1;
	}
		
	if (y2 >= y1)                 // The y-values are increasing
	{
		yinc1 = 1; yinc2 = 1;
	}
	else                          // The y-values are decreasing
	{
		yinc1 = -1; yinc2 = -1;
	}
		
	if (deltax >= deltay)         // There is at least one x-value for every y-value
	{
		xinc1 = 0;                  // Don't change the x when numerator >= denominator
		yinc2 = 0;                  // Don't change the y for every iteration
		den = deltax;
		num = deltax / 2;
		numadd = deltay;
		numpixels = deltax;         // There are more x-values than y-values
	}
	else                          // There is at least one y-value for every x-value
	{
		xinc2 = 0;                  // Don't change the x for every iteration
		yinc1 = 0;                  // Don't change the y when numerator >= denominator
		den = deltay;
		num = deltay / 2;
		numadd = deltax;
		numpixels = deltay;         // There are more y-values than x-values
	}
		
	for (curpixel = 0; curpixel <= numpixels; curpixel++) {
		setGridColor(x, y, currColor);             // Draw the current pixel
		num += numadd;              // Increase the numerator by the top of the fraction
		if (num >= den)             // Check if numerator >= denominator
		{
			num -= den;               // Calculate the new numerator value
			x += xinc1;               // Change the x as appropriate
			y += yinc1;               // Change the y as appropriate
		}
		x += xinc2;                 // Change the x as appropriate
		y += yinc2;                 // Change the y as appropriate
	}
}

//*****************************************************************************************
void gridTile::drawSquare(int sx, int sy, int ex, int ey) {
	if (gridType == 1) { return; }
}

//*****************************************************************************************
void gridTile::drawCirclePoints(int cx, int cy, int x, int y) {
	if (x == 0) {
		setGridColor(cx, cy + y, currColor);
		setGridColor(cx, cy - y, currColor);
		setGridColor(cx + y, cy, currColor);
		setGridColor(cx - y, cy, currColor);
		if (shapeFill != 0) {
			drawLine(cx, cy, cx, cy + y);
			drawLine(cx, cy, cx, cy - y);
			drawLine(cx, cy, cx + y, cy);
			drawLine(cx, cy, cx - y, cy);
		}
	} else if (x == y) {
		setGridColor(cx + x, cy + y, currColor);
		setGridColor(cx - x, cy + y, currColor);
		setGridColor(cx + x, cy - y, currColor);
		setGridColor(cx - x, cy - y, currColor);
		if (shapeFill != 0) {
			drawLine(cx,cy,cx + x, cy + y);
			drawLine(cx,cy,cx - x, cy + y);
			drawLine(cx,cy,cx + x, cy - y);
			drawLine(cx,cy,cx - x, cy - y);
		}
	} else if (x < y) {
		setGridColor(cx + x, cy + y, currColor);
		setGridColor(cx - x, cy + y, currColor);
		setGridColor(cx + x, cy - y, currColor);
		setGridColor(cx - x, cy - y, currColor);
		setGridColor(cx + y, cy + x, currColor);
		setGridColor(cx - y, cy + x, currColor);
		setGridColor(cx + y, cy - x, currColor);
		setGridColor(cx - y, cy - x, currColor);
		if (shapeFill != 0) {
			drawLine(cx,cy,cx + x, cy + y);
			drawLine(cx,cy,cx - x, cy + y);
			drawLine(cx,cy,cx + x, cy - y);
			drawLine(cx,cy,cx - x, cy - y);
			drawLine(cx,cy,cx + y, cy + x);
			drawLine(cx,cy,cx - y, cy + x);
			drawLine(cx,cy,cx + y, cy - x);
			drawLine(cx,cy,cx - y, cy - x);
		}
	}
}

//*****************************************************************************************
void gridTile::drawCircle(int xCenter, int yCenter, int radius) {
int x = 0, y = radius, p = (5 - radius*4)/4;
	if (gridType == 1) { return; }

	drawCirclePoints(xCenter, yCenter, x, y);
	while (x < y) {
		x++;
		if (p < 0) {
			p += 2*x+1;
		} else {
			y--;
			p += 2*(x-y)+1;
		}
		drawCirclePoints(xCenter, yCenter, x, y);
	}
}

//*****************************************************************************************
void gridTile::drawCorridor(int x, int y, int width) {
	if (gridType == 1) { return; }
	setGridColor(x, y, currColor);
	setGridColor(x+width, y, currColor);
}

//*****************************************************************************************
void gridTile::clearGridMap() {
	if (gridType == 1) { return; }

	memset(gridPoints, '\0', (gridWidth*gridHeight*sizeof(gridPoint)));

	if (playerData != NULL) {
		for (int i=0; i<MAX_MEMBERS; i++) {
			playerData[i].i_mapX = playerData[i].i_mapY = -1;
		}
	}

	repaint();
}

//*****************************************************************************************
void gridTile::resizeGridMap(int w, int h) {
	int i,j;
	gridPoint *ngp;

	if (gridType == 1) { return; }

	ngp = (gridPoint *)malloc(w*h*sizeof(gridPoint));
	memset(ngp, '\0', (w*h*sizeof(gridPoint)));
	for (i=0; i<gridHeight; i++) {
		j = i*gridWidth;
		memcpy((char *)&ngp[i*w], (char *)&gridPoints[j], sizeof(gridPoint) * gridWidth);
	}
	gridWidth = w;
	gridHeight = h;

//printf("GA free %d\n", gridPoints);
	if (gridPoints != NULL ) { free(gridPoints); }
	gridPoints = ngp;
//printf("GA malloc %d\n", gridPoints);
	if (externalTile != NULL) { externalTile->setGridArray(gridPoints); }

	if (vbar != NULL) { vbar->maximum(w); vbar->linesize(w/13); }
	if (hbar != NULL) { hbar->maximum(h); hbar->linesize(h/13); }

}

//*****************************************************************************************
void gridTile::setMapCentre() {
	prevCentreX = gridTopX + ((w() / gridSize) / 2);
	prevCentreY = gridTopY + ((h() / gridSize) / 2);
}

//*****************************************************************************************
void gridTile::centreMap(int x, int y) {

//printf("gridTile::centreMap %d:%d %d:%d\n", prevCentreX, prevCentreY, x, y);
	if (x == -1 && y == -1) { x = prevCentreX, y = prevCentreY; }

	prevCentreX = x; prevCentreY = y;

	x = x - ((w() / gridSize) / 2);
	y = y - ((h() / gridSize) / 2);

	setGridTop(x,y);
}

//*****************************************************************************************
void gridTile::setAllViewed() {
int id;

	if (gridType == 1) { return; }

	for (int i=(gridWidth*gridHeight)-1; i>-1; i--) {
			// only do those that are set
		if (gridPoints[i].i_currColor != 0 || gridPoints[i].i_objectType != 0) {
			gridPoints[i].f_wasViewed = 1;

         id = gridPoints[i].i_id;
         if (gridPoints[i].i_objectType == GRID_MONSTER && id != 0) {
            playerData[id].flags.f_wasViewed = 1;
         }
		}
	}
}

//*****************************************************************************************
void gridTile::setGridPoint(int pos, gridPoint *gp) {
	if (gridType == 1) { return; }

	gridPoints[pos].i_prevColor = gp->i_currColor;
	gridPoints[pos].i_currColor = gp->i_currColor;
	gridPoints[pos].f_wasViewed = gp->f_wasViewed;
	gridPoints[pos].f_isHidden = gp->f_isHidden;
	gridPoints[pos].i_objectType = gp->i_objectType;
	gridPoints[pos].i_id = gp->i_id;
	gridPoints[pos].i_mapLayer = gp->i_mapLayer;
	gridPoints[pos].i_prevId = gp->i_prevId;
	gridPoints[pos].f_shadow = gp->f_shadow;
}

//*****************************************************************************************
void gridTile::drawShape(int gx, int gy) {
	int i, j;
//printf("Shape: %d @ %d/%d\n", currShape, gx, gy);

	i = shapeWidth/5;
	switch (currShape) {		// type
		case 0:	// circle 
				drawCircle(gx, gy, shapeWidth/5);
				break;

		case 1:	// rectangle
				drawBox(gx, gy, (shapeWidth/5)+1, (shapeHeight/5)+1);
				if (shapeFill != 0) {
					for (j=(shapeHeight/5); j>0; j--) {
						drawLine(gx, gy+j, gx+i, gy+j);
					}
				}
				break;
	}
}

//*****************************************************************************************
void gridTile::drawBox(int sx, int sy, int dx, int dy) {
	drawLine(sx, sy, sx+dx, sy);
	drawLine(sx+dx, sy, sx+dx, sy+dy);
	drawLine(sx, sy, sx, sy+dy);
	drawLine(sx, sy+dy, sx+dx, sy+dy);
}

//*****************************************************************************************
void gridTile::removeObject(int x, int y) {
int gpos, id;

	if (gridType == 1) { return; }
	gpos = x + (y * gridWidth);

	id = gridPoints[gpos].i_id;
//printf("rO: %d:%d = %d:%d\n", x, y, gridPoints[gpos].i_objectType, gridPoints[gpos].i_id);

	if (gridPoints[gpos].i_objectType == GRID_OBJECT) {
		if (objectData != NULL) {
			objectData[id].c_description[0] = objectData[id].c_iconFile[0] = '\0';
			objectData[id].i_id = objectData[id].i_width = objectData[id].i_height = 0;
		}
	} else if ((gridPoints[gpos].i_objectType == GRID_PLAYER || gridPoints[gpos].i_objectType == GRID_MONSTER) && playerData != NULL) {
			setShadow(x, y, id, gridPoints[gpos].i_objectType, (playerData[id].i_space/5), 0);
			playerData[id].i_mapX = playerData[id].i_mapY = -1;
			playerData[id].flags.f_wasViewed = 0;
	} else {
		gridPoints[x].i_prevColor = 0;
	}
	gridPoints[gpos].i_currColor = gridPoints[gpos].i_prevColor;
	gridPoints[gpos].i_objectType = gridPoints[gpos].i_prevId = gridPoints[gpos].i_id = 0;
	gridPoints[gpos].f_isHidden = gridPoints[gpos].i_prevColor = 0;

	repaint();
}

//*****************************************************************************************
void gridTile::setCurrentAsViewed(int v) {
int j,k,id;

	if (gridType == 1) { return; }

	for (int i=h()/gridSize; i>0; i--) {
		j = ((gridTopY + i) * gridWidth) + gridTopX;
		for (k = w()/gridSize; k>0; k--) {
			// only do those that are set
			if (gridPoints[j].i_currColor != 0 || gridPoints[j].i_objectType != 0) {
				gridPoints[j].f_wasViewed = v;
				id = gridPoints[j].i_id;
				if (gridPoints[j].i_objectType == GRID_MONSTER && id != 0) {
					playerData[id].flags.f_wasViewed = 1;
				}
			}
			j++;
		}
	}
}

//*****************************************************************************************
void gridTile::setLOSAll() {
int pos;

	if (gridType == 1) { return; }
//printf("sLA: setLOSAll\n");

	if (playerData != NULL) {
		for (int i=0; i<MAX_PLAYERS; i++) {
			if (playerData[i].i_mapX != -1 && playerData[i].i_mapY != -1 
			 && playerData[i].flags.f_disabled == 0 && playerData[i].i_hp[HP_MAX] > 0) {
				setLineOfSight(playerData[i].i_mapX, playerData[i].i_mapY, gridVisibility, i);
			}
		}
	}
}

//*****************************************************************************************
void gridTile::remapColors(int from, int to) {
int i=(gridHeight * gridWidth)-1;
	for (; i>-1; i--) {
		if (gridPoints[i].i_currColor == from) { gridPoints[i].i_currColor = to; } // printf("rmC: %d %d\n", i, to); }
	}
	repaint();
}

//*****************************************************************************************
void gridTile::setFogOfWar(int s) {
	f_fogOfWar = s;
//printf("sFOW: %d\n", s);
}

//*****************************************************************************************
void gridTile::doFogOfWar() {
int i;

	if (playerData != NULL) {
		for (i=MAX_PLAYERS; i<MAX_MEMBERS; i++) { 
			if (playerData[i].i_mapX > 0 && playerData[i].i_mapY > 0) {
//printf("dFOW: %d %d/%d\n", i, playerData[i].i_mapX, playerData[i].i_mapY);
				setGridPointViewed(playerData[i].i_mapX, playerData[i].i_mapY, 0);
				playerData[i].flags.f_wasViewed = 0;
			}
		}
	}
}

//*****************************************************************************************
void gridTile::saveMapToTemp() {
char buf[20];

	undoMapCnt++;
	if (undoMapCnt > 5) { undoMapCnt = 1; }
	sprintf(buf, "tmpMap%d.map", undoMapCnt);
//printf("sMTT: %d = %s\n", undoMapCnt, buf);

	saveGridMap(buf);
}

//*****************************************************************************************
void gridTile::undoMapDrawing(int n) {
char buf[20];

	sprintf(buf, "tmpMap%d.map", undoMapCnt);
//printf("uMD: %d = %s\n", undoMapCnt, buf);
	undoMapCnt -= n;
	if (undoMapCnt < 1) { undoMapCnt = 5; }

	loadGridMap(buf);
}

//*****************************************************************************************
void gridTile::setGridPointId(int x, int y, int id) {
int i=(y * gridWidth) + x;

	gridPoints[i].i_id = id;
}

//*****************************************************************************************
void gridTile::setMode(int m) {
	gridMode = m;
	clickedX = clickedY = -1;

	if (m == MODE_COPYOBJECT) {
		copyObjX = copyObjY = -1;
	}
//printf("gridTile::setMode = %d\n", m);
}

//*****************************************************************************************
void gridTile::copyObject(int copyObjX, int copyObjY, int clickedX, int clickedY) {
int opos, npos;

//printf("gridTile::copyObject %d/%d = %d/%d\n", copyObjX, copyObjY, clickedX, clickedY);

	opos = copyObjX+(copyObjY*gridWidth); npos = clickedX+(clickedY*gridWidth);

	if (gridPoints[npos].i_objectType == 0) {
		gridPoints[npos].i_objectType = gridPoints[opos].i_objectType;
		gridPoints[npos].i_id = gridPoints[opos].i_id;
	}
	repaint();
}

//*****************************************************************************************
void gridTile::setShadow(int xpos, int ypos, int id, int type, int size, int flag) {
int opos, i, j;

//printf("setShadow = %d/%d %d:%d %d:%d\n", xpos, ypos, id, type, size, flag);
	if (xpos < 0 || ypos < 0) { return; }
	if (id < 0 || id > MAX_MEMBERS) { return; }
	if (size < 1) { return; }
	if (playerData == NULL) { return; }

	for (j=0; j<size; j++) {
		opos = xpos+(ypos*gridWidth)+(j*gridWidth);
		for (i=1; i<=size; i++) {
			if (flag == 0) {
				if (gridPoints[opos].i_id == id && (gridPoints[opos].i_objectType == GRID_PLAYER || gridPoints[opos].i_objectType == GRID_MONSTER)) {
					gridPoints[opos].i_id = gridPoints[opos].i_objectType = 0;
					gridPoints[opos].f_shadow = flag;
				}
			} else {
				if (gridPoints[opos].i_currColor < 8 && gridPoints[opos].i_objectType == 0) {
					if (gridPoints[opos].i_objectType == 0) {
						gridPoints[opos].i_id = id;
						gridPoints[opos].i_objectType = type;
						gridPoints[opos].f_shadow = flag;
					}
				} else {
					if (gridPoints[opos].i_objectType == 0) {
						if (i == 1) { j = size; }
						break;
					}
				}
			}
			opos++;
		}
	}
	opos = xpos+(ypos*gridWidth);
//	gridPoints[opos].i_id = id;
//	gridPoints[opos].i_objectType = type;
	gridPoints[opos].f_shadow = 0;
}

//**************************************************************************
Fl_Shared_Image * gridTile::rotate_image(Fl_Shared_Image *img, int angle) {
Fl_Shared_Image *rot;
int x, y, xstep, ystep;
const uchar	*imgptr;
uchar	*rotptr, *rotbase, *rotend;

  rot     = (Fl_Shared_Image *)img->copy(img->h(), img->w());
  rotbase = (uchar *)rot->data()[0];
  rotend  = rotbase + rot->w() * rot->h() * rot->d();

  if (angle == 90) {
    // Rotate 90 clockwise...
    rotptr = rotbase + (rot->h() - 1) * rot->w() * rot->d();
    xstep  = -rot->w() * rot->d() - rot->d();
    ystep  = (rot->w() * rot->h() + 1) * rot->d();
  } else {
    // Rotate 90 counter-clockwise...
    rotptr = rotbase + (rot->w() - 1) * rot->d();
    xstep  = rot->w() * rot->d() - rot->d();
    ystep  = -(rot->w() * rot->h() + 1) * rot->d();
  }

  if (img->d() == 1) {
    // Rotate grayscale image...
    for (y = 0, imgptr = (const uchar *)img->data()[0]; y < img->h(); y ++, rotptr += ystep) {
      for (x = img->w(); x > 0; x --, rotptr += xstep)
			if (rotptr < rotbase || rotptr >= rotend) {
	  			y = 1;
			 	break;
			} else
          *rotptr++ = *imgptr++;
    }
  } else {
    // Rotate color image...
    for (y = 0, imgptr = (const uchar *)img->data()[0]; y < img->h(); y ++, rotptr += ystep) {
      for (x = img->w(); x > 0; x --, rotptr += xstep)
			if (rotptr < rotbase || rotptr >= rotend) {
	  			y = 1;
	  			break;
			} else {
          *rotptr++ = *imgptr++;
          *rotptr++ = *imgptr++;
          *rotptr++ = *imgptr++;
			}
    }
  }

  return (rot);
}
