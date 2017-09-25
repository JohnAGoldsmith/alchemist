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
#ifndef WORDCOLLECTION_H
#define WORDCOLLECTION_H

#include <qmessagebox.h>
#include <qmap.h>
#include  <qtable.h>
#include <qpalette.h>
#include <qpainter.h>
#include <qcolor.h>
#include <qpixmap.h>
#include <qwidget.h>
#include <qdom.h>
#include <qaction.h>

#include "alchemist.h"





class Alchemist;
class Parse;

typedef QMap<QString,int>					StringToInt;
typedef QMap<QString,QString>				StringToString;
typedef QMap<int,QString>					IntToString;
typedef QMap<int,int>						IntToInt;
typedef QMap<QString,IntToInt*>				StringToIntCollection;
typedef QMap<int,Parse*>					ParseCollection; 
typedef QMap<QString,ParseCollection*>		StringToParseCollection;
typedef QMap<int,QString>					IntToString;



/**
@author John Goldsmith, Yu Hu, Colin Sprague
*/
class WordCollection{

private:

	Alchemist*							m_Myalchemist; 
	StringToInt							m_Words;
	StringToString						m_ReverseWords;
	StringToInt							m_FilteredWords; 
	StringToInt							m_AnalysedOrNoAnalysedWords; 
	IntToString							m_TableDisplayRowString; 
	IntToInt							m_TableDisplayRowStringIndex; 
	IntToInt							m_TableDisplayRowStartLoc; 
	StringToInt							m_Deletestrings;
	StringToIntCollection				m_DeleteDuplicatestrings; 
	StringToIntCollection  				m_Affectedstrings;
	StringToParseCollection				m_WordParses;  
	int									m_NumberOfWords;
	int									m_NumberOfFilteredWords;  
	int									m_NumberOfAnalysedOrNoAnalysedWords;
	int									m_LenOfLongestWord; 
	int									m_LenOfLongestAnalysedWord; 
	QString								m_FilterIncludeString; 
	QString								m_FilterExcludeString;
	int									m_MostLetterLeftOfFilterIncludeString; 
	int									m_MostLetterRightOfFilterIncludeString; 
	int									m_CurrentDisplayType; 
	int									m_CurrentFilterType; 
	int									m_CurrentPage; 
	int									m_EntryPerPage; 
	int									m_DisplayedAllnumber; 
	

	

public:
    WordCollection();
	WordCollection( Alchemist* ); 
    ~WordCollection();
	
	
	int				InsertOneWord(QString&); 
	int				InsertOneWord2(QString&, int*); 
	QString			GetReverse(QString&); 
	void			DisplayOnTable(QTable*, int); //here, we should use enum later...
	void			FilterWords(QTable*,QString&, QString&, bool, int); 
	void			EditDelete(QTable*); 
	void			RecordChanges(int, int, int); 
	void			AcceptDelete(QTable*);
	void			NewRoot(QTable*);
	void			NewAffix(QTable*); 
	void			Save(QTextStream&);  
	void			ParseOneWord(QString&, int, int, int, bool, int, QString&, QString&, int, QString&); 
	void			CutWordAtOneLine(QTable*, int, int, int, int, int, QString&, QString&, int colorIndex = -1); 
	void			ClearCuts(QTable*); 
	void			CommitDespriptionInfo(QTable*, int, QString&, QString&);
	void			DisplayDespriptionInfo(QTable*); 
	void			ClearMe(); 
	void			FindAnalysedOrUnAnalysedWords(int); // 0 --> all 1 --> analysed 2 --> unanalysed 
	void			DuplicateWord(QTable*); 
	void			AdjustColsBecauseOfDisplayOrder(int,int*, int*);  
	int				GetCount();
	int				GetCurrentDisplayType(){return m_CurrentDisplayType;};
	
};


class	MyTableItem	: public	QTableItem
{
private:
	QColor				m_Color; 
	QFont				m_Font;
	bool				m_Italic, m_Bold;
	
public:
	MyTableItem(QTable * table, EditType et, const QString & text);
	
	void			setColor( QColor color ){ m_Color = color; } 
	void			setFont( QFont font ) { m_Font = font; }
	void			setBold( bool b = TRUE ) { m_Bold = b; }
	void			setItalic( bool b = TRUE ) { m_Italic = b; }
	
	void			paint(QPainter* p,const QColorGroup& cg, const QRect& cr, bool selected);	
};

#endif
