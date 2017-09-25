/***************************************************************************
 *   Copyright (C) 2004 by John Goldsmith, Yu Hu, Colin Sprague            *
 *   jagoldsm@uchicago.edu                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

 #include "general.h"
 
QColor getColor( int index )
{
	if( index < 0 ) return "#ffffff";
	
	char* colors[2*NUMBER_COLOR_SETS] = 
 	{ 
		"#ff9999", "#99ff99", "#9999ff", "#ffcc99", "#99ffcc", "#cc99ff", "#ccff99", "#99ccff", "#ff99cc", "#ffff99", "#99ffff", "#ff99ff",
		"#ff6666", "#66ff66", "#6666ff", "#ffb266", "#66ffb2", "#b266ff", "#b2ff66", "#66b2ff", "#ff66b2", "#ffff66", "#66ffff", "#ff66ff"
 	}; 
	return QColor( colors[ index ] );
}
 
int getAltColorIndex( int index )
{
	return NUMBER_COLOR_SETS + index;
}

