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

typedef unsigned char uchar;

typedef struct gridPoint {
	uchar i_currColor:4;        // current background color - 16 slots
   uchar i_prevColor:4;        // previous background color - 16 slots

   uchar f_wasViewed:1;        // has it been viewed
   uchar f_isHidden:1;         // has the DM marked it as hidden from player view
   uchar i_objectType:2;       // is it an object like a trap/note. 0=none/wall, 2=player, 3=monster, 1=object
   uchar i_mapLayer:2;         // map layers ie. things like tunnels that go under another. 0 = L1, 1 = L2, 2 = both
   uchar i_prevObjectType:2;   // 0=none/wall, 2=player, 3=monster, 1=object

   uchar i_id;      			  // the ID of the object/player/monster (256)

   uchar i_prevId:3;	        // the previous ID of the object/player/monster (256)
   uchar f_prevViewed:1;     // has it been viewed
   uchar f_prevHidden:1;     // has the DM marked it as hidden from player view
   uchar f_shadow:1;         // is it a shadow of a monster ie. if it has size
   uchar i_prevType:2;       // is it an object like a trap/note. 0=none/wall, 2=player, 3=monster, 1=object
} gridPoint;

typedef struct losPoint {
	uchar i_currColor:4;        // current background color - 16 slots
   uchar i_objectType:2;       // is it an object like a trap/note. 0=none/wall, 2=player, 3=monster, 1=object
   uchar f_wasViewed:1;        // has it been viewed
   uchar i_id;      			  // the ID of the object/player/monster (256)
} losPoint;
