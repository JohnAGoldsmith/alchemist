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
#include "parse.h"
#include "general.h"

Parse::Parse()
{
}


Parse::Parse(WordCollection* Mywordcollection, QString&  Key)
{
	ASSERT(Key != NULL); 
	m_Mywordcollection = Mywordcollection;
	m_Key = Key; 
	m_Keylength = Key.length(); 
	m_Numberofpieces = 1;
	m_Pieces.insert(0, 0);  
	m_PieceTypes.insert(0, 0); 
	m_PieceColors.insert(0, -1); 
	m_PieceScores.insert(0, 0); 
	m_PieceComments.insert(0, QString("")); 
	m_PieceAllormorphs.insert(0, QString("")); 
	m_Comments = ""; 
	
	
//	m_DefaultColorStartIndex =0;
//	m_RootColorStartIndex =1;
//	m_AffixColorStartIndex = 3; 
//	m_TotalColors = 5; 
	
}


Parse::~Parse()
{
}


int	 Parse::GetPiece(int i)
{
	if ((i < 0) || (i >= m_Numberofpieces ))
	{
		return -1; 
	}
	
	return m_Pieces[i];
}

int	 Parse::GetPieceType(int i)
{
	if ((i < 0) || (i >= m_Numberofpieces ))
	{
		return -1; 
	}
	
	return m_PieceTypes[i];
}


int	 Parse::GetPieceColor(int i)
{
	if ((i < 0) || (i >= m_Numberofpieces ))
	{
		return -1; 
	}
	
	return m_PieceColors[i];
}

 
int  Parse::GetPieceScore(int i)
{
	if ((i < 0) || (i >= m_Numberofpieces ))
	{
		return -1; 
	}
	
	return m_PieceScores[i];

}



QString  Parse::GetPieceAllomorph(int i)
{
	if ((i < 0) || (i >= m_Numberofpieces ))
	{
		return NULL; 
	}
	
	return m_PieceAllormorphs[i];
}

QString	Parse::GetPieceComment(int i)
{
	if ((i < 0) || (i >= m_Numberofpieces ))
	{
		return NULL; 
	}
	
	return m_PieceComments[i];
}

QString Parse::GetComment()
{
	return m_Comments;
}	



int  Parse::CutAt(int loc, int type, int color, bool newcut)
{
	int								i; 
	int								cutloc, cuttype, cutcolor, cutscore;
	QString							cutcomment, cutallomorph; 
	int								leftpiece;  
	IntToInt						Temppieceswap, Temptypeswap, Tempcolorswap, Tempscoreswap;
	IntToString						Tempcommentswap, Tempallomorphswap;  
	
	
	if (loc < 0 ) return -1;
	if ( loc >= m_Keylength) return -1;
	
	
	leftpiece=0;
	for ( i = 0; i< m_Numberofpieces; i++)
	{
		cutloc = m_Pieces[i]; 
		if (cutloc == loc) 
		{
			if ( newcut)
			{
				m_PieceTypes[i] = type; 
				m_PieceColors[i] = color;
				m_PieceScores[i] = 0; 
				m_PieceComments[i]= QString(""); 
				m_PieceAllormorphs[i] = QString("");  
			}
			return i;
		}
		if (cutloc < loc)
		{
			leftpiece = i; 
		}
		else
		{ 
			break;
		}
	}
	
	for ( i = leftpiece +1; i< m_Numberofpieces; i++)
	{
		cutloc = m_Pieces[i];
		cuttype = m_PieceTypes[i];
		cutcolor = m_PieceColors[i];
		cutscore = m_PieceScores[i]; 
		cutcomment = m_PieceComments[i];
		cutallomorph = m_PieceAllormorphs[i];
		
		
		Temppieceswap.insert(i, cutloc);
		Temptypeswap.insert(i, cuttype);
		Tempcolorswap.insert(i,cutcolor); 
		Tempscoreswap.insert(i, cutscore);
		Tempcommentswap.insert(i, cutcomment);
		Tempallomorphswap.insert(i, cutallomorph); 
		
	}  
	
	for ( i = leftpiece +1; i< m_Numberofpieces; i++)
	{
		m_Pieces.remove(i);
		m_PieceTypes.remove(i);
		m_PieceColors.remove(i);
		m_PieceScores.remove(i);
		m_PieceComments.remove(i);
		m_PieceAllormorphs.remove(i);
	
	}
	
	m_Pieces.insert(leftpiece +1, loc);
	m_PieceTypes.insert(leftpiece +1,type);
	m_PieceColors.insert(leftpiece +1, color);
	m_PieceScores.insert(leftpiece +1, 0);
	m_PieceComments.insert(leftpiece +1, QString(""));
	m_PieceAllormorphs.insert(leftpiece +1, QString(""));
	
	for ( i = leftpiece +1; i< m_Numberofpieces; i++)
	{
		cutloc = Temppieceswap[i];
		cuttype =  Temptypeswap[i];
		cutcolor = Tempcolorswap[i];
		cutscore = Tempscoreswap[i]; 
		cutcomment = Tempcommentswap[i];
		cutallomorph = Tempallomorphswap[i];
		
		
		m_Pieces.insert(i +1, cutloc);
		m_PieceTypes.insert(i +1, cuttype);
		m_PieceColors.insert(i +1, cutcolor);
		m_PieceScores.insert(i +1, cutscore);
		m_PieceComments.insert(i +1, cutcomment);
		m_PieceAllormorphs.insert(i +1, cutallomorph);
		
	}
	
	m_Numberofpieces ++;
	
	return leftpiece +1;

}


void Parse::Commitdespinfo(int piece, int score, QString& allormorph, QString& comment)
{
	if ((piece < 0) || (piece >= m_Numberofpieces ))
	{
		return; 
	}
	
	if ( !m_PieceScores.contains(piece))
	{
		QMessageBox::information( NULL, "Error", "Please debug your piecescores!","OK" );
		return; 
	}
	
	if ( !m_PieceAllormorphs.contains(piece))
	{
		QMessageBox::information( NULL, "Error", "Please debug your pieceallomorphs!","OK" );
		return; 
	}
	
	if ( !m_PieceComments.contains(piece))
	{
		QMessageBox::information( NULL, "Error", "Please debug your piececomments!","OK" );
		return; 
	}
	
	m_PieceScores[piece] = score;
	m_PieceAllormorphs[piece]= allormorph;
	m_PieceComments[piece] = comment; 
	

}

int	 Parse::WhichPiece(int loc)
{
	int				piece; 
	int				i; 
	int				cutloc; 
	
	
	if ( loc < 0 ) return -1;
	if (loc >= m_Keylength ) return -1;
	
	piece = 0; 
	for ( i = 0; i< m_Numberofpieces; i++)
	{
		cutloc = m_Pieces[i]; 
		
		if (cutloc < loc)
		{
			piece = i;
			continue;
		}
		
		if (cutloc == loc)
		{
			piece = i; 
			return piece; 
		}
		
		if (cutloc > loc)
		{
			break;
		}
		
	}
	
	return piece; 
	
}


void  Parse::DeletePiece(int piece)
{
	int						i;
	int						cutloc,cuttype,cutcolor, cutscore;
	QString					cutcomment, cutallomorph; 
	IntToInt				Temppieceswap, Temptypeswap, Tempcolorswap, Tempscoreswap;
	IntToString				Tempcommentswap, Tempallomorphswap;  
	

	
		
	if ( piece <= 0) return;
	if ( piece >= m_Numberofpieces ) return; 
	
	for ( i = piece+1; i< m_Numberofpieces; i++)
	{
		cutloc = m_Pieces[i];
		cuttype = m_PieceTypes[i];
		cutcolor = m_PieceColors[i];
		cutscore = m_PieceScores[i]; 
		cutcomment = m_PieceComments[i];
		cutallomorph = m_PieceAllormorphs[i];
		
		Temppieceswap.insert(i, cutloc);
		Temptypeswap.insert(i, cuttype);
		Tempcolorswap.insert(i,cutcolor); 
		Tempscoreswap.insert(i, cutscore);
		Tempcommentswap.insert(i, cutcomment);
		Tempallomorphswap.insert(i, cutallomorph); 
		
	}  
	
	m_Pieces.remove(piece);
	m_PieceTypes.remove(piece);
	m_PieceColors.remove(piece);
	m_PieceScores.remove(piece);
	m_PieceComments.remove(piece);
	m_PieceAllormorphs.remove(piece);
	
	for ( i = piece +1; i< m_Numberofpieces; i++)
	{
		cutloc = Temppieceswap[i];
		cuttype =  Temptypeswap[i];
		cutcolor = Tempcolorswap[i];
		cutscore = Tempscoreswap[i]; 
		cutcomment = Tempcommentswap[i];
		cutallomorph = Tempallomorphswap[i];
		
			
		m_Pieces.insert(i-1, cutloc);
		m_PieceTypes.insert(i -1, cuttype);
		m_PieceColors.insert(i -1, cutcolor);
		m_PieceScores.insert(i -1, cutscore);
		m_PieceComments.insert(i -1, cutcomment);
		m_PieceAllormorphs.insert(i -1, cutallomorph);	
	}
	
	m_Numberofpieces --;

} 

void  Parse::ClearAllParse()
{
	m_Numberofpieces = 1; 
	m_Pieces.clear();
	m_PieceTypes.clear();
	m_PieceColors.clear();
	m_PieceScores.clear();
	m_PieceComments.clear();
	m_PieceAllormorphs.clear();
	
	m_Pieces.insert(0, 0);  
	m_PieceTypes.insert(0, 0); 
	m_PieceColors.insert(0, -1); 
	m_PieceScores.insert(0, 0); 
	m_PieceComments.insert(0, QString("")); 
	m_PieceAllormorphs.insert(0, QString("")); 
	
}


void  Parse::ClearPartParse(int startloc, int endloc)
{

	if ( startloc < 0) startloc = 0;
	
	if (( startloc == 0) && (endloc >= m_Keylength ))
	{
		ClearAllParse();
		return;
	}
	
	
	int						i;
	int						cutloc,cuttype,cutcolor, cutscore;
	QString					cutcomment, cutallomorph; 
	int						newi;
	IntToInt				Temppieceswap, Temptypeswap, Tempcolorswap, Tempscoreswap;
	IntToString				Tempcommentswap, Tempallomorphswap;  

	
	if ( m_Numberofpieces == 1 ) return; 
	
	newi =0;
	for ( i = 0; i< m_Numberofpieces; i++)
	{
		cutloc = m_Pieces[i];
		cuttype = m_PieceTypes[i];
		cutcolor = m_PieceColors[i];
		cutscore = m_PieceScores[i]; 
		cutcomment = m_PieceComments[i];
		cutallomorph = m_PieceAllormorphs[i];
		
		
		if (( cutloc > startloc ) && (cutloc < endloc))
		{
			continue;
		}
		else
		{
			Temppieceswap.insert(newi, cutloc);
			Temptypeswap.insert(newi, cuttype);
			Tempcolorswap.insert(newi,cutcolor);
			Tempscoreswap.insert(newi, cutscore);
			Tempcommentswap.insert(newi, cutcomment);
			Tempallomorphswap.insert(newi, cutallomorph); 	
			newi++; 
		} 
	}  
	
	m_Pieces.clear();
	m_PieceTypes.clear();
	m_PieceColors.clear();
	m_PieceScores.clear();
	m_PieceComments.clear();
	m_PieceAllormorphs.clear();
	
	m_Pieces = Temppieceswap;
	m_PieceTypes = Temptypeswap ;
	m_PieceColors = Tempcolorswap;
	m_PieceScores = Tempscoreswap;
	m_PieceComments = Tempcommentswap;
	m_PieceAllormorphs = Tempallomorphswap; 
	
	m_Numberofpieces = newi; 

}



void	Parse::ColorAdjustment()
{
	int								color1, color2; 
	
	for ( int i = 0; i < m_Numberofpieces-1; i++ )
	{
		color1 = GetPieceColor(i);
		color2 = GetPieceColor(i+1);
		
		if( color1 == color2 ) 
		{
			if( color2 < NUMBER_COLOR_SETS )
				SetPieceColor( i+1, color2 + NUMBER_COLOR_SETS );
			else
				SetPieceColor( i+1, color2 - NUMBER_COLOR_SETS );
		}
	}
		 

}

void  Parse::MergeDefaultPieces()
{
	bool							hasprecededefaultpiece = FALSE; 
	int								type; 	
	int								i;
	int								cutloc,cuttype,cutcolor, cutscore;
	QString							cutcomment, cutallomorph; 
	int								newi;
	IntToInt						Temppieceswap, Temptypeswap, Tempcolorswap, Tempscoreswap;
	IntToString						Tempcommentswap, Tempallomorphswap;  

	
	if ( m_Numberofpieces == 1 ) return; 
	
	newi =0;
	for ( i = 0; i< m_Numberofpieces; i++)
	{
		cutloc = m_Pieces[i];
		cuttype = m_PieceTypes[i];
		cutcolor = m_PieceColors[i];
		cutscore = m_PieceScores[i]; 
		cutcomment = m_PieceComments[i];
		cutallomorph = m_PieceAllormorphs[i];
		
		
		if (hasprecededefaultpiece && (cuttype == 0))
		{
			continue;
		}
		
		if ( !hasprecededefaultpiece && (cuttype == 0))
		{
			hasprecededefaultpiece = TRUE;
			Temppieceswap.insert(newi, cutloc);
			Temptypeswap.insert(newi, cuttype);
			Tempcolorswap.insert(newi,cutcolor);
			Tempscoreswap.insert(newi, cutscore);
			Tempcommentswap.insert(newi, cutcomment);
			Tempallomorphswap.insert(newi, cutallomorph); 	
			newi++;
			continue;
		}
		
		else
		{
			hasprecededefaultpiece = FALSE;
			Temppieceswap.insert(newi, cutloc);
			Temptypeswap.insert(newi, cuttype);
			Tempcolorswap.insert(newi,cutcolor);
			Tempscoreswap.insert(newi, cutscore);
			Tempcommentswap.insert(newi, cutcomment);
			Tempallomorphswap.insert(newi, cutallomorph); 	
			newi++; 
		} 
	}  
	
	m_Pieces.clear();
	m_PieceTypes.clear();
	m_PieceColors.clear();
	m_PieceScores.clear();
	m_PieceComments.clear();
	m_PieceAllormorphs.clear();
	
	m_Pieces = Temppieceswap;
	m_PieceTypes = Temptypeswap ;
	m_PieceColors = Tempcolorswap;
	m_PieceScores = Tempscoreswap;
	m_PieceComments = Tempcommentswap;
	m_PieceAllormorphs = Tempallomorphswap; 
	
	m_Numberofpieces = newi; 


}

bool Parse::IsAnalysed()
{
	if ( m_Numberofpieces > 1)
	{
		return true; 
	}
	
	if (m_PieceTypes[0] != 0)
	{
		return true; 
	}
	
	return false; 

}  


  
 


