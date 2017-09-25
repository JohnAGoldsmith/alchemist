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
#ifndef PARSE_H
#define PARSE_H

/**
@author John Goldsmith, Yu Hu, Colin Sprague
*/

#include "wordcollection.h"

class		WordCollection; 


class Parse{

public:
	WordCollection*			m_Mywordcollection;
	QString					m_Key;  	
	int						m_Keylength; 
	int						m_Numberofpieces; 			
	IntToInt				m_Pieces; 
	IntToInt				m_PieceTypes; // Now: 0 --> NoneType; 1 --> Root; 2 --> Affix.    ? I should Check it later
	IntToInt				m_PieceColors; 
	IntToInt				m_PieceScores; 
	IntToString				m_PieceComments; 
	IntToString				m_PieceAllormorphs; 
	QString					m_Comments; 
	
	
//public:
	// Color management	
//	int						m_DefaultColorStartIndex;
//	int						m_RootColorStartIndex;
//	int						m_AffixColorStartIndex; 
//	int						m_TotalColors; 


public:
    Parse();
	Parse(WordCollection*, QString&);
    ~Parse();
	
	QString					GetKey() {return m_Key;};
	int						KeyLength() {return m_Keylength;};
	int						NumberOfPieces() { return m_Numberofpieces;};
	int						GetPiece(int);
	int						GetPieceType(int);
	int						GetPieceColor(int); 
	int						GetPieceScore(int);
	QString					GetPieceAllomorph(int);
	QString					GetPieceComment(int);
	QString					GetComment();	
	void					SetPieceType(int loc, int type) { ASSERT((loc>=0)&&(loc<m_Numberofpieces));  m_PieceTypes[loc]= type; };
	void					SetPieceColor(int loc, int color) {ASSERT((loc>=0)&&(loc<m_Numberofpieces)); m_PieceColors[loc] = color;};
	void					SetPieceScore(int loc, int score) {ASSERT((loc>=0)&&(loc<m_Numberofpieces)); m_PieceScores[loc] = score;};
	void					SetPieceAllormorph(int loc, QString allormorph) {ASSERT((loc>=0)&&(loc<m_Numberofpieces)); m_PieceAllormorphs[loc] = allormorph;};
	void					SetPieceComment(int loc, QString comment){ASSERT((loc>=0)&&(loc<m_Numberofpieces)); m_PieceComments[loc] = comment;};
	int						CutAt(int, int, int, bool); 
	int						WhichPiece(int); 
	void					DeletePiece(int); 
	void					ClearAllParse();
	void					ClearPartParse(int, int);
	void					ColorAdjustment();  
	void					Commitdespinfo(int, int, QString&, QString&);
	void					MergeDefaultPieces(); 
	bool					IsAnalysed(); 
	
};

#endif
