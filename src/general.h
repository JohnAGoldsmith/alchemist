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

 #ifndef GENERAL_H
 #define GENERAL_H
 
 #include <qapplication.h>
 #include <qmainwindow.h>
 #include <qmessagebox.h>
 #include <qfiledialog.h>
 #include <qmap.h>
 #include <qdom.h>
 #include <qfiledialog.h>
 #include <qsettings.h>
 #include <qprogressbar.h>
 #include <qlabel.h>
 #include <qstatusbar.h>
 #include <qlineedit.h>
 #include <qcolordialog.h>
 #include <qfontdialog.h>
 #include <qtextedit.h>
 #include <qspinbox.h>
 #include <qpainter.h>
 #include <qrect.h>
 #include <qheader.h>
 #include <qinputdialog.h>
 #include <qgroupbox.h>
 #include <qcombobox.h>
 #include <qpushbutton.h>
 #include <qdialog.h>
 #include <qpopupmenu.h>
 #include <qcursor.h>
 #include <qaction.h> 
 
#include "math.h"

 #include "helpaboutdialog.h"
 #include "docinfodialog.h"
 #include "verifydialog.h" 
 #include "preferencesdialog.h"
 #include "wordcollection.h"
 #include "parse.h"
 #include "alchemistbase.h"
 #include "alchemist.h"

 enum eMorphemeType
{
  None,
  Root,
  Affix
};

enum eVerifyResult
{
  RESULT_CANCEL,
  RESULT_YES,
  RESULT_NO
};
 
#define AU_VERSION "v1.0.0"
 
 const int MAX_NUMBER_OF_DISTINCT_WORDS =	10000;
 const int MIN_NUMBER_OF_DISTINCT_WORDS =	100;
 const int NUMBER_OF_DISTINCT_WORDS_STEP =	100;

 
 const int NUMBER_COLOR_SETS = 12;
 
 
 QColor getColor( int );
 int getAltColorIndex( int );
 
 #endif // #ifndef GENERAL_H
