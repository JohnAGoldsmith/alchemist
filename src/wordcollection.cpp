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
#include "wordcollection.h"
#include "general.h"

WordCollection::WordCollection()
{
	m_NumberOfWords = 0; 
	m_LenOfLongestWord =0; 

}

WordCollection::WordCollection(Alchemist* Myalchemist)
{
	m_NumberOfWords = 0; 
	m_LenOfLongestWord =0; 
	m_Myalchemist = Myalchemist;
	m_LenOfLongestAnalysedWord =0; 
	m_MostLetterLeftOfFilterIncludeString =0; 
	m_MostLetterRightOfFilterIncludeString =0; 
	m_CurrentDisplayType =0; 
	m_CurrentFilterType = 0; 
	m_NumberOfFilteredWords = 0; 
	
	
	
} 


WordCollection::~WordCollection()
{
}


QString  WordCollection::GetReverse(QString& OneString)
{
	int				Length = OneString.length();
	int				i; 
	QChar			OneLetter;
	QString			ReversedString; 
	
	
	for (i = Length-1; i>=0; i--)
	{
		OneLetter = OneString[i];
		ReversedString += OneLetter; 
	}
	
	return ReversedString; 

} 



int	WordCollection::InsertOneWord(QString& OneWord)
{
	if ( ! m_Words.contains(OneWord) )
	{
		QString					ReversedString; 
		Parse*					Onewordparse; 
		ParseCollection*		parsecollection; 
		
		ReversedString = GetReverse(OneWord);
		
		m_Words.insert(OneWord, 1); 
		m_ReverseWords.insert(ReversedString, OneWord); 
		
		Onewordparse = new Parse(this, OneWord); 
		parsecollection = new ParseCollection();
		parsecollection ->insert(1, Onewordparse); 
		m_WordParses.insert(OneWord,parsecollection);
		 
		//QMessageBox::information( NULL, "Data",	QString("--")+OneWord+QString("--"),"OK" );
		m_NumberOfWords ++; 
	
		if ( OneWord.length() > (uint) m_LenOfLongestWord)
		{
			m_LenOfLongestWord = OneWord.length();	
		}
	
	}

	return m_NumberOfWords;
}

int	WordCollection::InsertOneWord2(QString& OneWord, int* Index)
{
	if ( ! m_Words.contains(OneWord) )
	{
		QString					ReversedString; 
		Parse*					Onewordparse; 
		ParseCollection*		parsecollection; 
		
		ReversedString = GetReverse(OneWord);
		
		m_Words.insert(OneWord, 1); 
		m_ReverseWords.insert(ReversedString, OneWord); 
		
		Onewordparse = new Parse(this, OneWord); 
		parsecollection = new ParseCollection();
		parsecollection ->insert(1, Onewordparse); 
		m_WordParses.insert(OneWord,parsecollection);
		 
		//QMessageBox::information( NULL, "Data",	QString("--")+OneWord+QString("--"),"OK" );
		m_NumberOfWords ++; 
	
		if ( OneWord.length() > (uint) m_LenOfLongestWord)
		{
			m_LenOfLongestWord = OneWord.length();	
		}
		*Index = 1; 
		
	}
	else
	{
		
		Parse*					Onewordparse; 
		ParseCollection*		parsecollection; 
		int						NewIndex; 
		
		
		m_Words[OneWord] ++;  
		parsecollection = m_WordParses[OneWord];
		NewIndex = parsecollection ->size() + 1; 
		
		//QMessageBox::information( NULL, "debug",	QString("%1").arg(NewIndex),"OK" );
		
		Onewordparse = new Parse(this, OneWord); 
		parsecollection ->insert(NewIndex, Onewordparse); 
		m_NumberOfWords ++; 
		*Index = NewIndex; 
	}
	

	return m_NumberOfWords;
}


void  WordCollection::DisplayOnTable(QTable* Table, int SortType)
{

		QHeader*			Vheader, *Hheader; 
		int					type = 0;
		bool				LeftToRight; 
		int					page; 
		int					entryperpage; 
		int					startdisplayentry, enddisplayentry; 
		int					Currentrows, Newrows;
		int					Currentcols, Newcols;  


		m_Myalchemist ->setStatusBar1( "Display Words to Table..." );
		m_Myalchemist ->resetCountDown();
		
//		LeftToRight = true; 
		LeftToRight = m_Myalchemist ->m_leftToRight->isOn(); 
		page = m_Myalchemist ->getPageNumber(); 
		entryperpage = m_Myalchemist ->getEntryPerPage();
		m_CurrentPage = page; 
		m_EntryPerPage = entryperpage;
		//QMessageBox::information( NULL, "debug", QString("%1").arg(page), "OK" );		
		//QMessageBox::information( NULL, "debug", QString("%1").arg(entryperpage), "OK" );		
		
		if (  SortType < 4)
		{

			// Clear the Table display
			
			int					cleari, clearj; 
		
			m_TableDisplayRowString.clear(); 
			m_TableDisplayRowStartLoc.clear(); 
			m_TableDisplayRowStringIndex.clear(); 
			
			Currentrows = Table ->numRows();
			Currentcols = Table ->numCols(); 
			
			for (cleari = 0; cleari < Currentrows; cleari++)		
			{
				for (clearj = 0; clearj < Currentcols ; clearj++)
				{
					Table ->clearCell(cleari, clearj);
				}
			
			}
			
				
			Newrows = m_NumberOfWords;
			Newcols = m_LenOfLongestWord + 1;
			
			m_DisplayedAllnumber = m_NumberOfWords;
			
			//Table ->insertRows(-1, Newrows); 
			//Table ->insertColumns(-1, Newcols); 
		
			
			startdisplayentry = page * entryperpage;
			enddisplayentry = m_NumberOfWords - 1;
			if ( enddisplayentry >	(page + 1)*entryperpage -1)
			{
				enddisplayentry = (page + 1)*entryperpage-1;
			}
			
			Newrows = enddisplayentry - startdisplayentry + 1;
			
			Table ->setNumRows(Newrows); 
			Table ->setNumCols(Newcols); 
			
			
		}
		else if (SortType >= 4)
		{
		
			if ( m_NumberOfFilteredWords == 0) 
			{
				QMessageBox::information( NULL, "FilterDisplay","Sorry, no word in the collection matched the \"Include\" filter criterion.","OK" );	
				
				m_Myalchemist ->setStatusBar1( "" );
				m_Myalchemist ->resetCountDown();
				
				return; 
			}
		
			m_TableDisplayRowString.clear(); 
			m_TableDisplayRowStartLoc.clear(); 
			m_TableDisplayRowStringIndex.clear();
			
			
			// Clear the Table display
			int					cleari, clearj; 
		
			Currentrows = Table ->numRows();
			Currentcols = Table ->numCols(); 
			
			
			for (cleari = 0; cleari < Currentrows; cleari++)		
			{
				for (clearj = 0; clearj < Currentcols ; clearj++)
				{
					Table ->clearCell(cleari, clearj);
				}
			
			}
			
			
			Newrows = m_NumberOfFilteredWords ;
			Newcols = m_MostLetterLeftOfFilterIncludeString + m_FilterIncludeString.length() + m_MostLetterRightOfFilterIncludeString +1;
			
			m_DisplayedAllnumber = m_NumberOfFilteredWords;
			
			startdisplayentry = page * entryperpage;
			enddisplayentry = m_NumberOfFilteredWords - 1;
			if ( enddisplayentry >	(page + 1)*entryperpage -1)
			{
				enddisplayentry = (page + 1)*entryperpage-1;
			}
			
			Newrows = enddisplayentry - startdisplayentry + 1;
			
			Table ->setNumRows(Newrows); 
			Table ->setNumCols(Newcols); 
			
		}
		
		
		//QMessageBox::information( NULL, "debug", QString("%1").arg(startdisplayentry), "OK" );		
		//QMessageBox::information( NULL, "debug", QString("%1").arg(enddisplayentry), "OK" );		
		
		
		// Display the words in this table according to SortType
		
		// Case 1: forward alphebatically
		if ( SortType == 0) 
		{
			int 					rows, cols,totalcols;
			int 					i, j, subi;
			QString					OneWord; 
			QChar					OneLetter;
			StringToInt::Iterator	StringToIntIt; 
			MyTableItem*			MyOneItem;
			ParseCollection*		Onewordparsecollection;
			Parse*					Onewordparse; 
			int						Displaycolortype; 
			int						WordIndex;
			int						realj;
			int						displayi; 
			bool					viewed; 
			int						CombiningClass;
			
			//Assert(m_NumberOfWords == m_Words.size()); 
		
			
			rows = m_NumberOfWords ;
			StringToIntIt = m_Words.begin(); 
			
			totalcols = m_LenOfLongestWord + 1;
			
			//Table ->setNumRows(Newrows);
			//Table ->setNumCols(m_LenOfLongestWord + 1);
			
			Vheader = Table -> verticalHeader();
			Hheader = Table -> horizontalHeader(); 
			
			viewed = FALSE; 
			displayi = -1; 
			for ( i=0; i< rows; )
			{
				OneWord = StringToIntIt.key(); 
				WordIndex = StringToIntIt.data(); 
				StringToIntIt ++;
				cols = OneWord.length();
				
				if ( ! m_WordParses.contains(OneWord))
				{
					QMessageBox::information( NULL, "Error","Please check your m_WordParses!","OK" );
					
					m_Myalchemist ->setStatusBar1( "" );
					m_Myalchemist ->resetCountDown();
					
					return;
				}
				
				Onewordparsecollection = m_WordParses[OneWord];
				
				for (subi = 1; subi<= WordIndex; subi++)
				{ 
				
					Onewordparse = NULL;
					Onewordparse = (*Onewordparsecollection)[subi]; 
					
					m_TableDisplayRowString.insert(i,OneWord);
					m_TableDisplayRowStringIndex.insert(i, subi);  
					m_TableDisplayRowStartLoc.insert(i, 1); 
					
					
					if ( (i >= startdisplayentry) && (i <= enddisplayentry))
					{
						viewed = TRUE; 
						displayi = i - startdisplayentry;
					} 
					
					if ( i > enddisplayentry )
					{
						viewed = FALSE;
						displayi = -1; 
					}
					
					
					if ( viewed )
					{
					
						MyOneItem = new MyTableItem( Table, QTableItem::Never, OneWord );
						MyOneItem->setFont( m_Myalchemist->getTableFont() );
						Table ->setItem (displayi, 0, MyOneItem );
						Table ->setColumnWidth(0,10*m_Myalchemist->getTableFont().pointSize());
						Table ->setRowHeight(displayi,2*m_Myalchemist->getTableFont().pointSize());
						
						for (j=1; j<= cols; j++)
						{
							if ( LeftToRight )
							{
								OneLetter = OneWord[j-1];
								realj = j-1; 
							}
							else
							{
								OneLetter = OneWord[cols -j];
								realj = cols - j; 	
							}


/*	This was a test to see if we could tell when we had a combining character.
	It didn't work, at least in Fedora.
							switch( OneLetter.combiningClass() )
							{
								case 200:
								case 208:
								case 212:
								case 218:
								case 224:
								case 228:
									QMessageBox::information( NULL, "Debug : Left Side", QString("%1").arg(OneLetter),"OK" );
									break;
								default:
									break;
							}
*/	
							Displaycolortype = Onewordparse->GetPieceColor( Onewordparse->WhichPiece(realj ) );
							type = Onewordparse->GetPieceType( Onewordparse->WhichPiece( realj ) );
							
							MyOneItem = new MyTableItem(Table, QTableItem::Never, QString("%1").arg(OneLetter) ); 
							MyOneItem ->setColor( getColor( Displaycolortype ) );
							MyOneItem->setFont( m_Myalchemist->getTableFont() );
							if( type == 0 )
							{			
								MyOneItem->setBold( FALSE );
								MyOneItem->setItalic( FALSE );
							}
							else if( type == 1 ) MyOneItem->setBold( TRUE );
							else if( type == 2 ) MyOneItem->setItalic( TRUE );
							Table ->setItem(displayi,j,MyOneItem);
							Table ->setColumnWidth(j,2*m_Myalchemist->getTableFont().pointSize()); 
							
						}
			
						
						for ( j=cols+1; j<totalcols; j++)
						{
							Table ->setText (displayi, j,"");
						}
						
						Vheader ->setLabel(displayi, QString("%1").arg(displayi)); 
						
					}
					
					m_Myalchemist ->countDownOnProgressBar( i, 
											rows/100*100, 
											rows/100 );
					
					//QMessageBox::information( NULL, "debug",QString("%1").arg(i),"OK" );
					i++; 
					
				}
			}
			
			
			// Set horizontal headers 
			for ( j=0; j<totalcols; j++)
			{	
				Hheader ->setLabel(j, QString("%1").arg(j)); 
			}
			
			m_CurrentDisplayType = SortType;
			//QMessageBox::information( NULL, "display",QString("%1").arg(m_CurrentDisplayType),"OK" );	
			
			
			m_Myalchemist ->setStatusBar1( "" );
			m_Myalchemist ->resetCountDown();
			
			return; 
		}
		
		// Case2: Backforward alphebatically
		if ( SortType == 1)
		{
			int 					rows, cols,totalcols;
			int 					i, j, subi;
			QString					OneWord; 
			QChar					OneLetter;
			StringToInt::Iterator	StringToIntIt; 
			MyTableItem*			MyOneItem;
			ParseCollection*		Onewordparsecollection;
			Parse*					Onewordparse; 
			int						Displaycolortype;
			int						WordIndex; 
			int						realj; 
			int						displayi; 
			bool					viewed;
					
			
			//Assert(m_NumberOfWords == m_Words.size()); 
			
			rows = m_NumberOfWords ;
			StringToIntIt = m_Words.end(); 
			totalcols = m_LenOfLongestWord + 1;
			
			//Table ->setNumRows(rows);
			//Table ->setNumCols(m_LenOfLongestWord + 1);
			
			Vheader = Table -> verticalHeader();
			Hheader = Table -> horizontalHeader(); 
			
			viewed = FALSE; 
			displayi = -1; 
			for ( i=0; i< rows; )
			{
				StringToIntIt --;
				OneWord = StringToIntIt.key(); 
				WordIndex = StringToIntIt.data(); 
				cols = OneWord.length(); 
				
				if ( ! m_WordParses.contains(OneWord))
				{
					QMessageBox::information( NULL, "Error","Please check your m_WordParses!","OK" );
					
					m_Myalchemist ->setStatusBar1( "" );
					m_Myalchemist ->resetCountDown();
					
					return;
				}
				
				Onewordparsecollection = m_WordParses[OneWord];
				
				for (subi = 1; subi<= WordIndex; subi++)
				{ 
	
					Onewordparse = (*Onewordparsecollection)[subi]; 
					
					m_TableDisplayRowString.insert(i,OneWord); 
					m_TableDisplayRowStringIndex.insert(i, subi); 
					m_TableDisplayRowStartLoc.insert(i, 1); 
					
					
					if ( (i >= startdisplayentry) && (i <= enddisplayentry))
					{
						viewed = TRUE; 
						displayi = i - startdisplayentry;
					} 
					
					if ( i > enddisplayentry )
					{
						viewed = FALSE;
						displayi = -1; 
					}
					
					if ( viewed )
					{
						
						MyOneItem = new MyTableItem( Table, QTableItem::Never, OneWord );
						MyOneItem->setFont( m_Myalchemist->getTableFont() );
						Table ->setItem (displayi, 0, MyOneItem );
						Table ->setColumnWidth(0,10*m_Myalchemist->getTableFont().pointSize()); 
						Table ->setRowHeight(displayi,2*m_Myalchemist->getTableFont().pointSize());
						
						
						for (j=1; j<= cols; j++)
						{
							if ( LeftToRight )
							{
								OneLetter = OneWord[j-1];
								realj = j-1; 
							}
							else
							{
								OneLetter = OneWord[cols -j];	
								realj = cols - j; 
							}
							
							Displaycolortype = Onewordparse ->GetPieceColor(Onewordparse ->WhichPiece(realj));
							type = Onewordparse->GetPieceType( Onewordparse->WhichPiece( realj ) );
							
							MyOneItem = new MyTableItem(Table, QTableItem::Never,QString("%1").arg(OneLetter) ); 
							MyOneItem ->setColor( getColor( Displaycolortype ) );
							MyOneItem->setFont( m_Myalchemist->getTableFont() );
							if( type == 0 )
							{
								MyOneItem->setBold( FALSE );
								MyOneItem->setItalic( FALSE );
							}
							else if( type == 1 ) MyOneItem->setBold( TRUE );
							else if( type == 2 ) MyOneItem->setItalic( TRUE );
							Table ->setItem(displayi,j,MyOneItem);
							Table ->setColumnWidth(j,2*m_Myalchemist->getTableFont().pointSize()); 
						}
						
						
						for ( j=cols+1; j<totalcols; j++)
						{
							Table ->setText (displayi, j,"");
						}
						
						Vheader ->setLabel(displayi, QString("%1").arg(displayi)); 
						
					}
					
					m_Myalchemist ->countDownOnProgressBar( i, 
											rows/100*100, 
											rows/100 );
					i++; 
				}
				
				
				
			}
			// Set horizontal headers 
			for ( j=0; j<totalcols; j++)
			{	
				Hheader ->setLabel(j, QString("%1").arg(j)); 
			}
			
			m_CurrentDisplayType = SortType;	
			
			
			m_Myalchemist ->setStatusBar1( "" );
			m_Myalchemist ->resetCountDown();
			
			return; 
		}
		
		// Case3: Backword forward
		if ( SortType == 2 )
		{
			int 						rows, cols,totalcols;
			int							startcol; 
			int 						i, j, subi;
			QString						OneWord; 
			QChar						OneLetter;
			StringToString::Iterator	StringToStringIt; 
			MyTableItem*				MyOneItem;
			ParseCollection*			Onewordparsecollection;
			Parse*						Onewordparse; 
			int							Displaycolortype;
			int							WordIndex; 
			int							realj; 
			int							displayi; 
			bool						viewed;
			
			
			//Assert(m_NumberOfWords == m_ReverseWords.size()); 
			
			rows = m_NumberOfWords ;
			StringToStringIt = m_ReverseWords.begin(); 
			totalcols = m_LenOfLongestWord + 1;
			
			//Table ->setNumRows(Newrows);
			//Table ->setNumCols(m_LenOfLongestWord + 1);
			
			Vheader = Table -> verticalHeader();
			Hheader = Table -> horizontalHeader(); 
			
			viewed = FALSE; 
			displayi = -1; 
			for ( i=0; i< rows; )
			{
				OneWord = StringToStringIt.data(); 
				WordIndex = m_Words[OneWord];
				StringToStringIt ++;
				
				startcol = m_LenOfLongestWord - OneWord.length(); 
				cols = m_LenOfLongestWord; 
				
				if ( ! m_WordParses.contains(OneWord))
				{
					QMessageBox::information( NULL, "Error","Please check your m_WordParses!","OK" );
					
					
					m_Myalchemist ->setStatusBar1( "" );
					m_Myalchemist ->resetCountDown();
					
					return;
				}
				
				Onewordparsecollection = m_WordParses[OneWord];
				
				for (subi = 1; subi<= WordIndex; subi++)
				{ 
				
					Onewordparse = (*Onewordparsecollection)[subi]; 	
					
					m_TableDisplayRowString.insert(i,OneWord); 
					m_TableDisplayRowStringIndex.insert(i, subi); 
					m_TableDisplayRowStartLoc.insert(i, startcol+1); 
					
					if ( (i >= startdisplayentry) && (i <= enddisplayentry))
					{
						viewed = TRUE; 
						displayi = i - startdisplayentry;
					} 
					
					if ( i > enddisplayentry )
					{
						viewed = FALSE;
						displayi = -1; 
					}
					
					if ( viewed)
					{
					
						MyOneItem = new MyTableItem( Table, QTableItem::Never, OneWord );
						MyOneItem->setFont( m_Myalchemist->getTableFont() );
						Table ->setItem(displayi,0,MyOneItem);
						Table ->setColumnWidth(0,10*m_Myalchemist->getTableFont().pointSize()); 
						Table ->setRowHeight(displayi,2*m_Myalchemist->getTableFont().pointSize());
						
						
						for ( j=1; j<=startcol; j++)
						{
							Table ->setText (displayi, j,""); 
						}
						
						for (j=startcol+1; j<= cols; j++)
						{
							//OneLetter = OneWord[j-startcol-1];
							
							if ( LeftToRight )
							{
								OneLetter = OneWord[j-startcol-1];
								realj = j-startcol-1 ;
							}
							else
							{
								OneLetter = OneWord[cols -j];
								realj = cols -j;  	
							}
	
	
							Displaycolortype = Onewordparse ->GetPieceColor(Onewordparse ->WhichPiece(realj));
							type = Onewordparse->GetPieceType( Onewordparse->WhichPiece( realj ) );
							
							MyOneItem = new MyTableItem(Table, QTableItem::Never,QString("%1").arg(OneLetter) ); 
							MyOneItem ->setColor( getColor( Displaycolortype ) );
							MyOneItem->setFont( m_Myalchemist->getTableFont() );
							if( type == 0 )
							{
								MyOneItem->setBold( FALSE );
								MyOneItem->setItalic( FALSE );
							}
							else if( type == 1 ) MyOneItem->setBold( TRUE );
							else if( type == 2 ) MyOneItem->setItalic( TRUE );
							Table ->setItem(displayi,j,MyOneItem);
							Table ->setColumnWidth(j,2*m_Myalchemist->getTableFont().pointSize()); 
						}
			
						Vheader ->setLabel(displayi, QString("%1").arg(displayi)); 
					}	
					m_Myalchemist ->countDownOnProgressBar( i, 
											rows/100*100, 
											rows/100 );
				
					i++;	
				}
			
				
			}			
			// Set horizontal headers 
			for ( j=0; j<totalcols; j++)
			{	
				Hheader ->setLabel(j, QString("%1").arg(j)); 
			}
			
			m_CurrentDisplayType = SortType;	
			
			
			m_Myalchemist ->setStatusBar1( "" );
			m_Myalchemist ->resetCountDown();
			
			return; 
		
		}
		
		// Case4: Backword backword
		if ( SortType == 3 )
		{
			int 						rows, cols,totalcols;
			int							startcol; 
			int 						i, j, subi;
			QString						OneWord; 
			QChar						OneLetter;
			StringToString::Iterator	StringToStringIt; 
			MyTableItem*				MyOneItem;
			ParseCollection*			Onewordparsecollection;
			Parse*						Onewordparse; 
			int							Displaycolortype;
			int							WordIndex;
			int							realj;
			int							displayi; 
			bool						viewed;
			
			
			//Assert(m_NumberOfWords == m_ReverseWords.size()); 
			
			rows = m_NumberOfWords ;
			StringToStringIt = m_ReverseWords.end(); 
			totalcols = m_LenOfLongestWord + 1;
			
			//Table ->setNumRows(rows);
			//Table ->setNumCols(m_LenOfLongestWord + 1);
			
			Vheader = Table -> verticalHeader();
			Hheader = Table -> horizontalHeader(); 
			
			viewed = FALSE; 
			displayi = -1; 
			for ( i=0; i< rows; )
			{
				StringToStringIt --;
				OneWord = StringToStringIt.data(); 
				WordIndex = m_Words[OneWord]; 
				
				startcol = m_LenOfLongestWord - OneWord.length(); 
				cols = m_LenOfLongestWord;
				
				if ( ! m_WordParses.contains(OneWord))
				{
					QMessageBox::information( NULL, "Error","Please check your m_WordParses!","OK" );
					
					
					m_Myalchemist ->setStatusBar1( "" );
					m_Myalchemist ->resetCountDown();
					
					return;
				}
				
				Onewordparsecollection = m_WordParses[OneWord];
				
				for (subi = 1; subi<= WordIndex; subi++)
				{ 
				
					Onewordparse = (*Onewordparsecollection)[subi];
					
					m_TableDisplayRowString.insert(i,OneWord); 
					m_TableDisplayRowStringIndex.insert(i, subi); 
					m_TableDisplayRowStartLoc.insert(i, startcol+1); 
					
					if ( (i >= startdisplayentry) && (i <= enddisplayentry))
					{
						viewed = TRUE; 
						displayi = i - startdisplayentry;
					} 
					
					if ( i > enddisplayentry )
					{
						viewed = FALSE;
						displayi = -1; 
					}
					
					if ( viewed )
					{
					
						MyOneItem = new MyTableItem( Table, QTableItem::Never, OneWord );
						MyOneItem->setFont( m_Myalchemist->getTableFont() );
						Table ->setItem (displayi, 0, MyOneItem );
						Table ->setColumnWidth(0,10*m_Myalchemist->getTableFont().pointSize()); 
						Table ->setRowHeight(displayi,2*m_Myalchemist->getTableFont().pointSize());
						
						
						for ( j=1; j<=startcol; j++)
						{
							Table ->setText (displayi, j,"");
						
						}
						
						
						for (j=startcol+1; j<= cols; j++)
						{
							//OneLetter = OneWord[j-startcol-1];
							
							if ( LeftToRight )
							{
								OneLetter = OneWord[j-startcol-1];
								realj = j-startcol-1; 
							}
							else
							{
								OneLetter = OneWord[cols -j];
								realj = cols -j; 	
							}
	
							Displaycolortype = Onewordparse ->GetPieceColor(Onewordparse ->WhichPiece(realj));
							type = Onewordparse->GetPieceType( Onewordparse->WhichPiece( realj) );
							
							MyOneItem = new MyTableItem(Table, QTableItem::Never,QString("%1").arg(OneLetter) ); 
							MyOneItem ->setColor( getColor( Displaycolortype ) );
							MyOneItem->setFont( m_Myalchemist->getTableFont() );
							if( type == 0 )
							{
								MyOneItem->setBold( FALSE );
								MyOneItem->setItalic( FALSE );
							}
							else if( type == 1 ) MyOneItem->setBold( TRUE );
							else if( type == 2 ) MyOneItem->setItalic( TRUE );
							Table ->setItem(displayi,j,MyOneItem);
							Table ->setColumnWidth(j,2*m_Myalchemist->getTableFont().pointSize()); 
						}
			
						Vheader ->setLabel(displayi, QString("%1").arg(displayi)); 
					}	
					m_Myalchemist ->countDownOnProgressBar( i, 
											rows/100*100, 
											rows/100 );
					i++; 
				}

			}			
			// Set horizontal headers 
			for ( j=0; j<totalcols; j++)
			{	
				Hheader ->setLabel(j, QString("%1").arg(j)); 
			}
			
			m_CurrentDisplayType = SortType;	
			
			
			m_Myalchemist ->setStatusBar1( "" );
			m_Myalchemist ->resetCountDown();
			
			return; 
		
		}
		
		// Casse5: This is case is special, it only display those filtered words
		if ( SortType == 4 )
		{
			
			// QMessageBox::information( NULL, "m_LenOfLongestWordFilterDisplay",QString("Yes, we got some strings!"),"OK" );	
			
			int							rows,cols,totalcols;
			int							startlocinstring, startlocintable; 
			int 						i, j, subi;
			StringToInt::Iterator		StringToIntIt; 
			QString						OneWord; 
			MyTableItem*				MyOneItem;
			QChar						OneLetter;
			int							LenOfOneWord;
			ParseCollection*			Onewordparsecollection;
			Parse*						Onewordparse; 
			int							Displaycolortype;
			int							WordIndex;
			int							realj; 
			bool						viewed; 
			int							displayi; 
			
			
			rows = m_NumberOfFilteredWords; 
			cols = m_MostLetterLeftOfFilterIncludeString + m_FilterIncludeString.length() + m_MostLetterRightOfFilterIncludeString; 
			totalcols = cols +1; 
			
			//Table ->setNumRows(rows);
			Table ->setNumCols(cols + 1);
			
			StringToIntIt = m_FilteredWords.begin(); 
			Vheader = Table -> verticalHeader();
			Hheader = Table -> horizontalHeader(); 
			
			viewed = FALSE; 
			displayi = -1; 
			for ( i=0; i< rows; )
			{
				OneWord = StringToIntIt.key();
				WordIndex = m_Words[OneWord];
				LenOfOneWord = OneWord.length();
				startlocinstring = StringToIntIt.data();
				StringToIntIt ++;	
				
				if ( ! m_WordParses.contains(OneWord))
				{
					QMessageBox::information( NULL, "Error","Please check your m_WordParses!","OK" );
					
					m_Myalchemist ->setStatusBar1( "" );
					m_Myalchemist ->resetCountDown();
					
					return;
				}
				
				
				
				Onewordparsecollection = m_WordParses[OneWord];
				
				for (subi = 1; subi<= WordIndex; subi++)
				{ 
				
					startlocintable = 1+ m_MostLetterLeftOfFilterIncludeString - startlocinstring; 
					
					Onewordparse = (*Onewordparsecollection)[subi];
					
					m_TableDisplayRowString.insert(i,OneWord); 
					m_TableDisplayRowStringIndex.insert(i, subi); 
					m_TableDisplayRowStartLoc.insert(i, startlocintable); 
					
					if ( (i >= startdisplayentry) && (i <= enddisplayentry))
					{
						viewed = TRUE; 
						displayi = i - startdisplayentry;
					} 
					
					if ( i > enddisplayentry )
					{
						viewed = FALSE;
						displayi = -1; 
					}
					
					if ( viewed )
					{
						
						MyOneItem = new MyTableItem( Table, QTableItem::Never, OneWord );
						MyOneItem->setFont( m_Myalchemist->getTableFont() );
						Table ->setItem (displayi, 0, MyOneItem );
						Table ->setColumnWidth(0,10*m_Myalchemist->getTableFont().pointSize());
						Table ->setRowHeight(displayi,2*m_Myalchemist->getTableFont().pointSize());
						
						
						for (j=1; j< startlocintable; j++)
						{
							Table ->setText (displayi, j,"");
							Table ->setColumnWidth(j,2*m_Myalchemist->getTableFont().pointSize()); 
						}
		
						
						
						for (j=0; j< LenOfOneWord; j++)
						{
							//OneLetter = OneWord[j];
								
							if ( LeftToRight )
							{
								OneLetter = OneWord[j];
								realj = j; 
							}
							else
							{
								OneLetter = OneWord[LenOfOneWord -j-1];	
								realj = LenOfOneWord -j-1;
							}
	
	
							Displaycolortype = Onewordparse ->GetPieceColor(Onewordparse ->WhichPiece(realj));
							type = Onewordparse->GetPieceType( Onewordparse->WhichPiece( realj ) );
							
							MyOneItem = new MyTableItem(Table, QTableItem::Never,QString("%1").arg(OneLetter) ); 
							MyOneItem ->setColor( getColor( Displaycolortype ) );
							MyOneItem->setFont( m_Myalchemist->getTableFont() );
							if( type == 0 )
							{
								MyOneItem->setBold( FALSE );
								MyOneItem->setItalic( FALSE );
							}
							else if( type == 1 ) MyOneItem->setBold( TRUE );
							else if( type == 2 ) MyOneItem->setItalic( TRUE );
							Table ->setItem(displayi,j+startlocintable,MyOneItem);
							Table ->setColumnWidth(j+startlocintable,2*m_Myalchemist->getTableFont().pointSize()); 
							
						}
			
					
						for (j=LenOfOneWord+startlocintable; j<totalcols; j++)
						{
							Table ->setText (displayi, j,"");
							Table ->setColumnWidth(j,2*m_Myalchemist->getTableFont().pointSize()); 
						}
						
						
						Vheader ->setLabel(displayi, QString("%1").arg(displayi));
					}	
					m_Myalchemist ->countDownOnProgressBar( i, 
											rows/10*10, 
											rows/10 );
					i++; 		
				}
			
			}
							
			// Set horizontal headers 
			for ( j=0; j<totalcols; j++)
			{	
				Hheader ->setLabel(j, QString("%1").arg(j)); 
			}
			
			
			m_Myalchemist ->countDownOnProgressBar( rows, 
										rows/10*10, 
										rows/10 );
				
			m_CurrentDisplayType = SortType;
			
			
			m_Myalchemist ->setStatusBar1( "" );
			m_Myalchemist ->resetCountDown();
			
			return; 
			
		}
		
		// Case6: Display unanalysed words
		if ( SortType == 5) 
		{
			int 					rows, cols,totalcols;
			int 					i, j, subi;
			QString					OneWord; 
			QChar					OneLetter;
			StringToInt::Iterator	StringToIntIt; 
			MyTableItem*			MyOneItem;
			ParseCollection*		Onewordparsecollection;
			Parse*					Onewordparse; 
			int						Displaycolortype;
			int						WordIndex;
			int						realj; 
			bool					viewed;
			int						displayi; 
			
			//Assert(m_NumberOfWords == m_Words.size()); 
		
			
			rows = m_NumberOfFilteredWords;
			StringToIntIt = m_FilteredWords.begin(); 
			
			totalcols = m_LenOfLongestAnalysedWord + 1;
			
			//Table ->setNumRows(rows);
			Table ->setNumCols(m_LenOfLongestAnalysedWord + 1);
			
			Vheader = Table -> verticalHeader();
			Hheader = Table -> horizontalHeader(); 
			
			viewed = FALSE; 
			displayi = -1; 
			for ( i=0; i< rows; )
			{
				OneWord = StringToIntIt.key();
				WordIndex = m_Words[OneWord]; 
				StringToIntIt ++;
				cols = OneWord.length();
				
				if ( ! m_WordParses.contains(OneWord))
				{
					QMessageBox::information( NULL, "Error","Please check your m_WordParses!","OK" );
					
					m_Myalchemist ->setStatusBar1( "" );
					m_Myalchemist ->resetCountDown();
					
					return;
				}
				
				Onewordparsecollection = m_WordParses[OneWord];
				
				for (subi = 1; subi<= WordIndex; subi++)
				{ 
					
					Onewordparse = (*Onewordparsecollection)[subi];
					m_TableDisplayRowString.insert(i,OneWord); 
					m_TableDisplayRowStringIndex.insert(i, subi); 
					m_TableDisplayRowStartLoc.insert(i, 1); 
					
					if ( (i >= startdisplayentry) && (i <= enddisplayentry))
					{
						viewed = TRUE; 
						displayi = i - startdisplayentry;
					} 
					
					if ( i > enddisplayentry )
					{
						viewed = FALSE;
						displayi = -1; 
					}
					
					if ( viewed )
					{
					
					
						MyOneItem = new MyTableItem( Table, QTableItem::Never, OneWord );
						MyOneItem->setFont( m_Myalchemist->getTableFont() );
						Table ->setItem (displayi, 0, MyOneItem );
						Table ->setColumnWidth(0,10*m_Myalchemist->getTableFont().pointSize());
						Table ->setRowHeight(displayi,2*m_Myalchemist->getTableFont().pointSize());
						
						for (j=1; j<= cols; j++)
						{
							//OneLetter = OneWord[j-1];
							
							if ( LeftToRight )
							{
								OneLetter = OneWord[j-1];
								realj = j-1; 
							}
							else
							{
								OneLetter = OneWord[cols -j];
								realj = cols -j; 	
							} 						
	
							Displaycolortype = Onewordparse->GetPieceColor( Onewordparse->WhichPiece( realj ) );
							type = Onewordparse->GetPieceType( Onewordparse->WhichPiece( realj ) );
							
							MyOneItem = new MyTableItem(Table, QTableItem::Never, QString("%1").arg(OneLetter) ); 
							MyOneItem ->setColor( getColor( Displaycolortype ) );
							MyOneItem->setFont( m_Myalchemist->getTableFont() );
							if( type == 0 )
							{			
								MyOneItem->setBold( FALSE );
								MyOneItem->setItalic( FALSE );
							}
							else if( type == 1 ) MyOneItem->setBold( TRUE );
							else if( type == 2 ) MyOneItem->setItalic( TRUE );
							Table ->setItem(displayi,j,MyOneItem);
							Table ->setColumnWidth(j,2*m_Myalchemist->getTableFont().pointSize()); 
							
						}
			
						
						for ( j=cols+1; j<totalcols; j++)
						{
							Table ->setText (displayi, j,"");
						}
						
						Vheader ->setLabel(displayi, QString("%1").arg(displayi)); 
					}	
					m_Myalchemist ->countDownOnProgressBar( i, 
											rows/100*100, 
											rows/100 );
					
					//QMessageBox::information( NULL, "debug",QString("%1").arg(i),"OK" );
					i++; 
				}

			}			
			
			// Set horizontal headers 
			for ( j=0; j<totalcols; j++)
			{	
				Hheader ->setLabel(j, QString("%1").arg(j)); 
			}
			
			m_CurrentDisplayType = SortType;
			//QMessageBox::information( NULL, "display",QString("%1").arg(m_CurrentDisplayType),"OK" );	
			
			
			m_Myalchemist ->setStatusBar1( "" );
			m_Myalchemist ->resetCountDown();
			
			return; 
		}
		
		m_Myalchemist ->setStatusBar1( "" );
		m_Myalchemist ->resetCountDown();
		
		m_CurrentDisplayType = -1; 
		return; 
}


void	WordCollection::FilterWords(QTable* Table, QString& IncludeString, QString& ExcludeString, bool Newdisplay, int FilterType)
{
	// QMessageBox::information( NULL, "Filter",	IncludeString+QString(" and ")+ExcludeString,"OK" );	
	
	StringToInt::Iterator				StringToIntIt; 
	bool								NeedConsiderExcludeString; 
	int									StartLoc; 
	QString								OneWord; 
	int									ThisLeftLetters, ThisRightLetters; 
	int									WordIndex; 
	bool								LeftToRight;  
	
	LeftToRight = m_Myalchemist ->m_leftToRight->isOn(); 

	
	m_CurrentFilterType = FilterType; 
	
	if ( FilterType == 0 )
	{
		m_FilteredWords = m_AnalysedOrNoAnalysedWords; 
		m_NumberOfFilteredWords = m_NumberOfAnalysedOrNoAnalysedWords;
		m_FilterIncludeString = "";
		m_FilterExcludeString = "";
		if ( Newdisplay)
		{
			DisplayOnTable(Table, 5);
		}
		return; 
	}
	
	
	if ( FilterType == 1)
	{
		m_FilteredWords.clear(); 
		m_FilterIncludeString = IncludeString;
		m_FilterExcludeString = ExcludeString;
		
		if ( m_FilterExcludeString.length() > 0)
		{
		
			NeedConsiderExcludeString = true;
		}
		else
		{
			NeedConsiderExcludeString = false;
		}
		
		m_MostLetterLeftOfFilterIncludeString =0;
		m_MostLetterRightOfFilterIncludeString =0;
		m_NumberOfFilteredWords = 0; 
		
		
		for ( StringToIntIt = m_AnalysedOrNoAnalysedWords.begin(); StringToIntIt != m_AnalysedOrNoAnalysedWords.end(); StringToIntIt++)
		{
			OneWord = StringToIntIt.key();
			WordIndex = m_Words[OneWord];
			StartLoc = OneWord.find(IncludeString); 
			if ( StartLoc == -1) continue; 
		
			if ( ! NeedConsiderExcludeString )
			{
				ThisLeftLetters = StartLoc; 	
				ThisRightLetters = OneWord.length() - ThisLeftLetters - IncludeString.length();	
				
				if ( !LeftToRight)
				{
					StartLoc = ThisRightLetters;
				}
				
				m_FilteredWords.insert(OneWord, StartLoc);
				m_NumberOfFilteredWords += WordIndex; 
				
				if ( ThisLeftLetters > m_MostLetterLeftOfFilterIncludeString)
				{
					m_MostLetterLeftOfFilterIncludeString = ThisLeftLetters;
				}
				
				if ( ThisRightLetters > m_MostLetterRightOfFilterIncludeString)
				{
					m_MostLetterRightOfFilterIncludeString = ThisRightLetters;
				}
				
			}
			else
			{
				if ( OneWord.find(ExcludeString) == -1)
				{
					ThisLeftLetters = StartLoc; 	
					ThisRightLetters = OneWord.length() - ThisLeftLetters - IncludeString.length();	
				
					if ( !LeftToRight)
					{
						StartLoc = ThisRightLetters;
					}
					
					m_FilteredWords.insert(OneWord, StartLoc);
					m_NumberOfFilteredWords += WordIndex; 
					
					if ( ThisLeftLetters > m_MostLetterLeftOfFilterIncludeString)
					{
						m_MostLetterLeftOfFilterIncludeString = ThisLeftLetters;
					}
				
					if ( ThisRightLetters > m_MostLetterRightOfFilterIncludeString)
					{
						m_MostLetterRightOfFilterIncludeString = ThisRightLetters;
					}
					
					
				}
				else
				{
					continue; 
				}
			
			}
		
		
		}
		
		if ( ! LeftToRight)
		{
			int					swap; 
			swap = m_MostLetterLeftOfFilterIncludeString;
			m_MostLetterLeftOfFilterIncludeString = m_MostLetterRightOfFilterIncludeString;
			m_MostLetterRightOfFilterIncludeString = swap ; 	
		} 
		
		
		if ( Newdisplay)
		{
			DisplayOnTable(Table, 4);
		}
		
		return; 
	}
	
} 


void  WordCollection::EditDelete(QTable* Table)
{
	int							NumberOfSelections =0; 
	int							i; 
	QTableSelection				OneSelection; 
	int							toprow,bottomrow, leftcol, rightcol, bakleftcol, bakrightcol;  
	int							cleari, clearj;
	bool						LeftToRight; 
	int							reali; 
	
	
	LeftToRight = m_Myalchemist ->m_leftToRight->isOn(); 					
	
	
	NumberOfSelections = Table ->numSelections(); 
	
	//QMessageBox::information( NULL, "NumberOfSelections",	QString("%1").arg(NumberOfSelections),"OK" );
	
	for ( i=0; i<NumberOfSelections; i++)
	{
		OneSelection = Table ->selection(i); 
		toprow = OneSelection.topRow();
		bottomrow = OneSelection.bottomRow();
		leftcol = OneSelection.leftCol();
		rightcol = OneSelection.rightCol();
		bakleftcol = leftcol; 
		bakrightcol = rightcol; 
		//QMessageBox::information( NULL, "OneSelection",	QString("%1,%2,%3,%4").arg(toprow).arg(bottomrow).arg(leftcol).arg(rightcol),"OK" );
		
		for (cleari= toprow; cleari<=bottomrow; cleari++)
		{
			for (clearj=bakleftcol; clearj <= bakrightcol; clearj++)
			{
				Table ->setText(cleari, clearj, QString(""));
			}
			
			reali = cleari + m_CurrentPage * m_EntryPerPage; 
			
			if ( !LeftToRight)
			{
				AdjustColsBecauseOfDisplayOrder(reali, &leftcol, &rightcol); 
			}
			RecordChanges(reali, leftcol, rightcol); 
			
		}
		
	}
	
} 


void  WordCollection::RecordChanges(int row, int leftcol, int rightcol )
{
	QString					thisstring; 
	int						startlocinrow; 
	int						lenofthisstring; 
	int						endlocinrow; 
	int						startaffectcol, endaffectcol; 
	IntToInt*				PtrIntCollection; 
	int						affecti; 
	int						affectiinstring; 
	int						Index; 
	int						TotalIndexes; 
	IntToInt*				DeletedCopies; 
	
		
	
	if (!m_TableDisplayRowString.contains(row))
	{
	 QMessageBox::information( NULL, "Attention", "The row is out of range","OK" );
	 return; 
	}
	
	thisstring = m_TableDisplayRowString[row];
	Index = m_TableDisplayRowStringIndex[row];
	TotalIndexes = m_Words[thisstring];
	startlocinrow = m_TableDisplayRowStartLoc[row]; 
	lenofthisstring = thisstring.length();
	endlocinrow = startlocinrow + lenofthisstring -1; 
	
	
	if ( m_Deletestrings.contains(thisstring))
	{
		return; 
	}
	
	if ( ( leftcol <= startlocinrow ) && ( endlocinrow <= rightcol ) && (TotalIndexes == 1))
	{
		m_Deletestrings.insert(thisstring, 1); 
		return; 
	}
	
	
	// Case1: all the word is selected
	if ( ( leftcol <= startlocinrow ) && ( endlocinrow <= rightcol ))
	{
		if ( m_DeleteDuplicatestrings.contains(thisstring))
		{
			DeletedCopies = m_DeleteDuplicatestrings[thisstring];
			DeletedCopies ->insert(Index, 1); 
		}
		else
		{
			DeletedCopies = new IntToInt(); 
			DeletedCopies ->insert(Index, 1); 
			m_DeleteDuplicatestrings.insert(thisstring, DeletedCopies); 
		}
		
		if ( DeletedCopies->size() >= TotalIndexes)
		{
			m_Deletestrings.insert(thisstring, 1); 
			m_DeleteDuplicatestrings.remove(thisstring); 
			delete DeletedCopies;
		}
		
		return;
	}
	
	// Next cases are only part of the word is affected from startaffectcol to endaffectcol
	
	
	if ( TotalIndexes >1 )
	{
		return; 
	}
	
	
	startaffectcol = leftcol; 
	endaffectcol = rightcol; 
	
	if ( startlocinrow > startaffectcol)
	{
		startaffectcol = startlocinrow;	
	}
	
	if ( endlocinrow < endaffectcol)
	{
		endaffectcol = endlocinrow;
	} 
	
	if ( m_Affectedstrings.contains(thisstring))
	{
		PtrIntCollection = m_Affectedstrings[thisstring];
	}
	else
	{
		PtrIntCollection = new IntToInt(); 
		m_Affectedstrings.insert(thisstring, PtrIntCollection);
	}
	 
	for ( affecti = startaffectcol; affecti<= endaffectcol; affecti++)
	{
		affectiinstring = affecti -  startlocinrow;
		PtrIntCollection ->insert(affectiinstring, 1); 	
	}
	
	// further check whether all letters of the word have been deleted
	if ( PtrIntCollection ->size() >= (uint)lenofthisstring)
	{
		m_Deletestrings.insert(thisstring, 1); 
		m_Affectedstrings.remove(thisstring); 
		delete PtrIntCollection;
	}
	
}

void  WordCollection::AcceptDelete(QTable* Table)
{
	
	
	if (( m_Deletestrings.size() == 0) && (m_Affectedstrings.size() ==0) && (m_DeleteDuplicatestrings.size() ==0)) return; 
	
	
	
	StringToInt::Iterator				StringToIntIt; 
	StringToIntCollection::Iterator		StringToIntCollectionIt; 
	QString								OneString, ReverseOneString; 
	QString								NewString, ReverseNewString; 
	int									LenOfOneString; 
	int									i, subi; 
	IntToInt*							PtrIntCollection; 
	QChar								OneLetter; 
	ParseCollection*					Onewordparsecollection;
	ParseCollection*					Tempparsecollection;
	ParseCollection::Iterator			ParseCollectionIt; 
	Parse*								OneParse;
	int									NumberOfCopies; 
	int									Newindex; 
	int									CurrentIndex; 
	

	
	
	
	// delete the words
	for ( StringToIntIt = m_Deletestrings.begin(); StringToIntIt != m_Deletestrings.end(); StringToIntIt++)
	{
		OneString = StringToIntIt.key();
		NumberOfCopies = m_Words[OneString];  
		ReverseOneString = GetReverse(OneString);
		
		m_Words.remove(OneString);
		Onewordparsecollection = m_WordParses[OneString];
		m_ReverseWords.remove( ReverseOneString); 
		
		m_WordParses.remove(OneString);
		for ( subi = 1; subi <= NumberOfCopies; subi++)
		{
			OneParse = (*Onewordparsecollection)[subi];
			ASSERT(OneParse != NULL);
			delete OneParse;
		}
		delete Onewordparsecollection;
		m_NumberOfWords -= NumberOfCopies;
	}
	
	// delete some copies of words, not delete these words
	for ( StringToIntCollectionIt = m_DeleteDuplicatestrings.begin(); StringToIntCollectionIt != m_DeleteDuplicatestrings.end(); StringToIntCollectionIt++)
	{
		OneString = StringToIntCollectionIt.key(); 
		PtrIntCollection = StringToIntCollectionIt.data(); 
		
		Onewordparsecollection = m_WordParses[OneString];
		Newindex = 1;
		Tempparsecollection = new ParseCollection();
		  
		for ( ParseCollectionIt = Onewordparsecollection ->begin(); ParseCollectionIt != Onewordparsecollection ->end();ParseCollectionIt++)
		{
			CurrentIndex = ParseCollectionIt.key(); 
			OneParse = ParseCollectionIt.data(); 
			
			if ( PtrIntCollection ->contains(CurrentIndex))
			{ 
				m_NumberOfWords --; 
				continue; 
			}
			
			Tempparsecollection ->insert(Newindex, OneParse); 
			Newindex ++; 
		}
		
		m_WordParses[OneString] = Tempparsecollection;
		delete Onewordparsecollection; 
		m_Words[OneString] = (Newindex -1);
		
	}
	
	// modify some words , this case only happen we have one copy of the word !!
	for ( StringToIntCollectionIt = m_Affectedstrings.begin(); StringToIntCollectionIt != m_Affectedstrings.end(); StringToIntCollectionIt++)
	{
		OneString = StringToIntCollectionIt.key(); 
		ReverseOneString = GetReverse(OneString);
		LenOfOneString = OneString.length();
		
		PtrIntCollection = StringToIntCollectionIt.data(); 
		
		NewString = QString("");
		for (i=0; i< LenOfOneString; i++)
		{
			if ( PtrIntCollection ->contains(i) ) continue; 
			OneLetter = OneString[i];
			NewString.append(OneLetter); 
		}
		 
		ReverseNewString = GetReverse(NewString);
		
		NumberOfCopies = m_Words[OneString];
		m_Words.remove(OneString);
		Onewordparsecollection =  m_WordParses[OneString];
		ASSERT(Onewordparsecollection != NULL);
		m_WordParses.remove(OneString);
		OneParse = (*Onewordparsecollection)[1]; 
		delete OneParse; 
		delete Onewordparsecollection;
		m_ReverseWords.remove( ReverseOneString);
		
		if (! m_Words.contains(NewString))
		{
			m_Words.insert(NewString, 1); 
			OneParse = new Parse(this, NewString);
			Onewordparsecollection = new ParseCollection();
			Onewordparsecollection->insert(1, OneParse); 
			m_WordParses.insert(NewString, Onewordparsecollection);
			m_ReverseWords.insert(ReverseNewString, NewString);
			
		}  
		else
		{
			m_NumberOfWords -= NumberOfCopies;
		}
		
	}
	
	// clear the delete information maps
	m_Deletestrings.clear();
	m_Affectedstrings.clear();
	m_DeleteDuplicatestrings.clear(); 
	
	// Update the newest m_LenOfLongestWord
	m_LenOfLongestWord = 0; 
	for ( StringToIntIt = m_Words.begin(); StringToIntIt != m_Words.end(); StringToIntIt++)
	{
		OneString = StringToIntIt.key(); 
		if (OneString.length() > (uint)m_LenOfLongestWord ) 
		{
			m_LenOfLongestWord = OneString.length();
		}
	}
	
	//update the Analysed/UnAnalysedWords
	FindAnalysedOrUnAnalysedWords(m_Myalchemist ->getfiltertype()); 
	// update the m_FilteredWords information;
	 FilterWords(Table,m_FilterIncludeString, m_FilterExcludeString, false, m_CurrentFilterType); 
	 //QMessageBox::information( NULL, "debug", QString("%1").arg(m_CurrentDisplayType),"OK" );
	 DisplayOnTable(Table, m_CurrentDisplayType);

}

void  WordCollection::NewRoot(QTable* Table)
{
	
	int							NumberOfSelections =0; 
	int							i; 
	QTableSelection				OneSelection; 
	int							toprow,bottomrow, leftcol, rightcol;  
	int							cuti;	
	int							NextColorIndex = m_Myalchemist->getNextColorIndex();
	
	
	if ( ( m_Deletestrings.size() != 0) || (m_Affectedstrings.size() !=0) || (m_DeleteDuplicatestrings.size() != 0))		
	{
		QMessageBox::information( NULL, "Attention", "Please commit your deletion before make the cut","OK" );
		return; 
	}			

	
	int							score;
	QString						allormorph, comment; 
	bool						LeftToRight;
	int							reali; 
	
	LeftToRight = m_Myalchemist ->m_leftToRight->isOn(); 
	
	
	allormorph = m_Myalchemist ->m_allomorphyLineEdit ->text();
	comment = m_Myalchemist ->m_remarksTextEdit ->text();
	
	if ( allormorph == NULL)
	{
		allormorph = QString("");
	}
	
	if (comment == NULL)
	{
		comment = QString("");
	}
	
	score = 1; // Default to 'certain' // m_Myalchemist ->m_Score; 
	
	NumberOfSelections = Table ->numSelections(); 
	
	//QMessageBox::information( NULL, "NumberOfSelections",	QString("%1").arg(NumberOfSelections),"OK" );
	
	for ( i=0; i<NumberOfSelections; i++)
	{
		OneSelection = Table ->selection(i); 
		toprow = OneSelection.topRow();
		bottomrow = OneSelection.bottomRow();
			
		for (cuti= toprow; cuti<=bottomrow; cuti++)
		{
			leftcol = OneSelection.leftCol();
			rightcol = OneSelection.rightCol(); 
			
			reali = cuti + m_CurrentPage * m_EntryPerPage; 
			
			if (! LeftToRight)
			{
				AdjustColsBecauseOfDisplayOrder(reali, &leftcol, &rightcol);
			}	
			CutWordAtOneLine(Table, reali, leftcol, rightcol+1, 1, score, allormorph, comment , NextColorIndex); 
		}
		
	}

}

void  WordCollection::NewAffix(QTable* Table)
{
	int							NumberOfSelections =0; 
	int							i; 
	QTableSelection				OneSelection; 
	int							toprow,bottomrow, leftcol, rightcol;  
	int							cuti;	
	int							NextColorIndex = m_Myalchemist->getNextColorIndex();
	
	
						

	if ( ( m_Deletestrings.size() != 0) || (m_Affectedstrings.size() !=0) || (m_DeleteDuplicatestrings.size() != 0))		
	{
		QMessageBox::information( NULL, "Attention", "Please commit your deletion before make the cut","OK" );
		return; 
	}	
	
	
	int							score;
	QString						allormorph, comment; 
	bool						LeftToRight;
	int							reali; 
	
	
	LeftToRight = m_Myalchemist ->m_leftToRight->isOn(); 
	
	allormorph = m_Myalchemist ->m_allomorphyLineEdit ->text();
	comment = m_Myalchemist ->m_remarksTextEdit ->text();
	
	if ( allormorph == NULL)
	{
		allormorph = QString("");
	}
	
	if (comment == NULL)
	{
		comment = QString("");
	}
	
	score = 1; // Default to 'certain' // m_Myalchemist ->m_Score; 
	
	
	
	NumberOfSelections = Table ->numSelections(); 
	
	//QMessageBox::information( NULL, "NumberOfSelections",	QString("%1").arg(NumberOfSelections),"OK" );
	
	for ( i=0; i<NumberOfSelections; i++)
	{
		OneSelection = Table ->selection(i); 
		toprow = OneSelection.topRow();
		bottomrow = OneSelection.bottomRow();
			
		for (cuti= toprow; cuti<=bottomrow; cuti++)
		{
			leftcol = OneSelection.leftCol();
			rightcol = OneSelection.rightCol(); 
			
			reali = cuti + m_CurrentPage * m_EntryPerPage; 
			
			if (! LeftToRight)
			{
				AdjustColsBecauseOfDisplayOrder(reali, &leftcol, &rightcol);
			}		
			
			CutWordAtOneLine(Table, reali, leftcol, rightcol+1, 2, score, allormorph, comment, NextColorIndex); 
		}
		
	}
}


void  WordCollection::CutWordAtOneLine(QTable* Table, int realrow, int leftcol, int rightcol, int type,int score, QString& allormorph, QString& comment, int colorIndex )
{
	// currently, type: 0 --> ordinary, 1 --> root, 2--> affix
	QString					thisstring; 
	Parse*					Onewordparse;
	int						lenofthisstring; 
	int						startlocinrow; 
	int						endlocinrow; 
	int						startaffectcol, endaffectcol; 
	int						colortype, oldcolortype; 
	int						needrefreshleftcol, needrefreshrightcol;
	int						clearj, addj; 
	QChar					OneLetter;
	MyTableItem*			MyOneItem;
	int						Displaycolortype;
	int						Keeptype; 
	int						leftpiece; 
	int						piece; 
	ParseCollection*		Onewordparsecollection;
	int						Index; 
	bool					LeftToRight;
	int						realj; 
	int						row; 
	
	
	row = realrow - m_CurrentPage * m_EntryPerPage; 
	
	
	LeftToRight = m_Myalchemist ->m_leftToRight->isOn(); 
	
		
	
	if (!m_TableDisplayRowString.contains(realrow))
	{
	 QMessageBox::information( NULL, "Attention", "The row is out of range","OK" );
	 return; 
	}
	
	thisstring = m_TableDisplayRowString[realrow];
	
	if ( ! m_WordParses.contains(thisstring))
	{
		QMessageBox::information( NULL, "Error","Please check your m_WordParses!","OK" );
		return; 
	}
	
	Onewordparsecollection = m_WordParses[thisstring];
	Index = m_TableDisplayRowStringIndex[realrow]; 
	Onewordparse = (*Onewordparsecollection)[Index];	
	
	startlocinrow = m_TableDisplayRowStartLoc[realrow]; 
	lenofthisstring = thisstring.length();
	endlocinrow = startlocinrow + lenofthisstring -1; 
	

	
	startaffectcol = leftcol - startlocinrow; 
	endaffectcol = rightcol - startlocinrow; 
	
	
	
	if ( endaffectcol <= 0) 
	{
		return; 
	}
	
	if ( startaffectcol >= lenofthisstring)
	{
		return;
	}
	
	if ( startaffectcol < 0) startaffectcol = 0; 
	
	if ( endaffectcol > lenofthisstring) endaffectcol = lenofthisstring;
	
	
	
	
	leftpiece = Onewordparse ->WhichPiece(startaffectcol);
	//Onewordparse ->SetPieceScore(leftpiece, 0);
	//Onewordparse ->SetPieceComment(leftpiece, QString("")); 
	//Onewordparse ->SetPieceAllormorph(leftpiece, QString(""));
	
	
	oldcolortype = Onewordparse->GetPieceColor( Onewordparse->WhichPiece(endaffectcol) );
	Keeptype = Onewordparse->GetPieceType (Onewordparse->WhichPiece(endaffectcol) );

	Onewordparse ->ClearPartParse(startaffectcol, endaffectcol); 
	
//	colortype = DefaultCutColor;
	colortype = colorIndex; 
	piece = Onewordparse ->CutAt(startaffectcol, type, colortype, true);
	Onewordparse ->SetPieceScore(piece, score);
	Onewordparse ->SetPieceAllormorph(piece, allormorph);
	Onewordparse ->SetPieceComment(piece, comment); 
	
	colortype = Keeptype; 
	Onewordparse ->CutAt(endaffectcol, Keeptype, oldcolortype, false);
	
	Onewordparse ->ColorAdjustment(); 
	
	// Refresh updates
	needrefreshleftcol = leftcol; 
	needrefreshrightcol = rightcol -1; 

	
	for (clearj = startlocinrow; clearj < startlocinrow+lenofthisstring ; clearj++)
	{
		Table ->clearCell(row, clearj);
	}
			
	for (addj=startlocinrow; addj< startlocinrow+lenofthisstring ; addj++)
	{
		if ( LeftToRight)
		{
			OneLetter = thisstring[ addj-startlocinrow];					
			realj =  addj-startlocinrow;
		}
		else
		{
			OneLetter = thisstring[lenofthisstring - addj+startlocinrow-1 ];					
			realj = lenofthisstring - addj+startlocinrow-1 ;
		}
		
		//QMessageBox::information( NULL, "debug",QString("%1").arg(OneLetter),"OK" );
		Displaycolortype = Onewordparse ->GetPieceColor(Onewordparse ->WhichPiece(realj));
		type = Onewordparse->GetPieceType( Onewordparse->WhichPiece( realj ) );
					
		MyOneItem = new MyTableItem(Table, QTableItem::Never,QString("%1").arg(OneLetter) ); 
		MyOneItem ->setColor( getColor( Displaycolortype ) );
		MyOneItem->setFont( m_Myalchemist->getTableFont() );
		if( type == 0 )
		{
			MyOneItem->setBold( FALSE );
			MyOneItem->setItalic( FALSE );
		}
		else if( type == 1 ) MyOneItem->setBold( TRUE );
		else if( type == 2 ) MyOneItem->setItalic( TRUE );
		Table ->setItem(row,addj,MyOneItem);
		Table ->setColumnWidth(addj,2*m_Myalchemist->getTableFont().pointSize()); 
	}
	
	
	
} 

void  WordCollection::Save(QTextStream& Output)
{

	if ( ( m_Deletestrings.size() != 0) || (m_Affectedstrings.size() !=0) || (m_DeleteDuplicatestrings.size() != 0))		
	{
		QMessageBox::information( NULL, "Attention", "Please commit your deletion before saving","OK" );
		return; 
	}			


	QDomElement* oneinfo;
	
	QDomDocument doc( "Goldstandard" );
	QDomElement root = doc.createElement( "GDS" );
  	doc.appendChild( root );
	
	// Attach the header info
//	QDomElement docinfo = doc.createElement( "docinfo" );	
	root.appendChild( m_Myalchemist->getDocInfo() );
	
	QDomElement direction = doc.createElement( "directionality" );
	if( m_Myalchemist->m_leftToRight->isOn() ) direction.setAttribute( "left2right", "true" );
	else direction.setAttribute( "left2right", "false" );
	root.appendChild( direction );
	
	
	// Construct main content
	
	QDomElement content = doc.createElement( "content" );
	content.setAttribute( "number", m_NumberOfWords);
	root.appendChild(content);
	
	// Add each word info as one child of the content
	
	StringToInt::Iterator			StringToIntIt;
	QString							OneWord;
	Parse*							OneParse;  
	int								NumberOfPieces; 
	int								i; 
	ParseCollection*				Onewordparsecollection;
	ParseCollection::Iterator		ParseCollectionIt; 
	int								Index; 
		
	
	
	for ( StringToIntIt = m_Words.begin(); StringToIntIt != m_Words.end(); StringToIntIt++)
	{
		OneWord = StringToIntIt.key();
		
		if ( !m_WordParses.contains(OneWord))
		{
			QMessageBox::information( NULL, "Error", "Something wrong with your Parses collection, please check!", "OK" );
			return; 
		}
		
		
		Onewordparsecollection = m_WordParses[OneWord];
		
		for ( ParseCollectionIt = Onewordparsecollection ->begin(); ParseCollectionIt != Onewordparsecollection ->end(); ParseCollectionIt++)
		{
		
			OneParse = ParseCollectionIt.data(); 
			ASSERT(OneParse); 
			NumberOfPieces = OneParse ->NumberOfPieces();
			
			QDomElement oneline = doc.createElement( "word" );
			oneline.setAttribute( "key", OneWord);
			oneline.setAttribute("morphemes", NumberOfPieces);
			oneline.setAttribute("comment", OneParse ->m_Comments);
			content.appendChild(oneline);
			
			for ( i=0; i< NumberOfPieces; i++)
			{
				QDomElement onepiece = doc.createElement( "morpheme" );
				onepiece.setAttribute("start", OneParse ->m_Pieces[i]);
				onepiece.setAttribute("type", OneParse ->m_PieceTypes[i]); 
				onepiece.setAttribute("color", OneParse ->m_PieceColors[i]);
				onepiece.setAttribute("score", OneParse ->m_PieceScores[i]); 
				onepiece.setAttribute("allomorph", OneParse ->m_PieceAllormorphs[i]);
				onepiece.setAttribute("comment", OneParse ->m_PieceComments[i]);
				oneline.appendChild(onepiece);
			}
		
		}
	}
	
	
	Output<< doc.toString();
	
}  


void  WordCollection::ParseOneWord(QString& OneWord, int loc, int type, int color, bool newcut, int score, QString& allormorph, QString& comment, int Index, QString& wordcomment)
{
	Parse*							OneParse;
	int								piece; 
	ParseCollection*				Onewordparsecollection;
	
	if (!m_WordParses.contains(OneWord))
	{
		QMessageBox::information( NULL, "Attention", "The parses collection didn't contain this word","OK" );
		return;
	}

	Onewordparsecollection = m_WordParses[OneWord];
	OneParse = (*Onewordparsecollection)[Index];
	OneParse ->m_Comments = wordcomment; 
	piece = OneParse ->CutAt(loc, type, color, newcut); 
	OneParse ->Commitdespinfo(piece, score, allormorph, comment); 
} 


void  WordCollection::ClearCuts(QTable* Table)
{
	int							NumberOfSelections =0; 
	int							i; 
	QTableSelection				OneSelection; 
	int							toprow,bottomrow, leftcol, rightcol;  
	int							leftcolinword, rightcolinword; 
	int							cleari, clearj, addj;
	Parse*						OneParse; 
	QString						OneWord; 
	int							leftpiece, rightpiece; 
	int							wordstartloc; 
	int							Displaycolortype; 
	QChar						OneLetter;
	MyTableItem*				MyOneItem;
	ParseCollection*			Onewordparsecollection;
	int							Index; 
	int							realrow; 
	
	
							
	if ( ( m_Deletestrings.size() != 0) || (m_Affectedstrings.size() !=0) || (m_DeleteDuplicatestrings.size() != 0))		
	{
		QMessageBox::information( NULL, "Attention", "Please commit your deletion before saving","OK" );
		return; 
	}	
	
	
	bool						LeftToRight;
	int							realj; 
	int							LenOfOneWord; 
	
	LeftToRight = m_Myalchemist ->m_leftToRight->isOn(); 
	
	
	NumberOfSelections = Table ->numSelections(); 
	
	
	for ( i=0; i<NumberOfSelections; i++)
	{
		OneSelection = Table ->selection(i); 
		toprow = OneSelection.topRow();
		bottomrow = OneSelection.bottomRow();
		
		for (cleari= toprow; cleari<=bottomrow; cleari++)
		{
			leftcol = OneSelection.leftCol();
			rightcol = OneSelection.rightCol(); 
			realrow = cleari + m_CurrentPage* m_EntryPerPage; 
			OneWord = m_TableDisplayRowString[realrow];
			Onewordparsecollection = m_WordParses[OneWord];
			Index = m_TableDisplayRowStringIndex[realrow]; 
			OneParse = (*Onewordparsecollection)[Index];
			LenOfOneWord = OneWord.length(); 
			
			wordstartloc = m_TableDisplayRowStartLoc[realrow];
			
			if ( ! LeftToRight)
			{
				AdjustColsBecauseOfDisplayOrder(realrow, &leftcol, &rightcol); 
			}
			
			leftcolinword = leftcol - wordstartloc;
			rightcolinword = rightcol - wordstartloc;
			
			if ( leftcolinword < 0) leftcolinword = 0;
			if (rightcolinword >= OneWord.length()) rightcolinword =  OneWord.length() -1; 
				
			leftpiece = OneParse ->WhichPiece(leftcolinword); 
			rightpiece = OneParse ->WhichPiece(rightcolinword);
			
			
			OneParse ->SetPieceColor(leftpiece, -1); 
			OneParse ->SetPieceType(leftpiece, 0); 
			OneParse ->SetPieceScore(leftpiece, 0);  
			OneParse ->SetPieceAllormorph(leftpiece, QString("")); 
			OneParse ->SetPieceComment(leftpiece, QString(""));  				
			OneParse ->ClearPartParse(leftcolinword, rightcolinword+1); 
			
			OneParse ->MergeDefaultPieces(); 
			
			for (clearj = wordstartloc ; clearj < wordstartloc +LenOfOneWord ; clearj++)
			{
				Table ->clearCell(cleari, clearj);
			}
			
			for (addj= wordstartloc; addj< wordstartloc+LenOfOneWord ; addj++)
			{
				if ( LeftToRight)
				{
					OneLetter = OneWord[addj-wordstartloc];					
					realj = addj-wordstartloc;
				}
				else
				{
					OneLetter = OneWord[LenOfOneWord - addj+wordstartloc-1];	
					realj = 	LenOfOneWord - addj+wordstartloc-1;			
				
				}
				
				Displaycolortype = OneParse ->GetPieceColor(OneParse ->WhichPiece(realj));
							
				MyOneItem = new MyTableItem(Table, QTableItem::Never,QString("%1").arg(OneLetter) ); 
				MyOneItem ->setColor( getColor( Displaycolortype ) );
				MyOneItem->setFont( m_Myalchemist->getTableFont() );
				Table ->setItem(cleari,addj,MyOneItem);
				Table ->setColumnWidth(addj,30); 
			}		
						
		}
		
	}
	
	
	
		
	//DisplayOnTable(Table, m_CurrentDisplayType);
	
} 

void WordCollection::CommitDespriptionInfo(QTable* Table, int score, QString& allomorph, QString& comment)
{

	if ( ( m_Deletestrings.size() != 0) || (m_Affectedstrings.size() !=0) || (m_DeleteDuplicatestrings.size() != 0))		
	{
		QMessageBox::information( NULL, "Attention", "Please commit your deletion before saving","OK" );
		return; 
	}	

	
	int							NumberOfSelections =0; 
	int							i; 
	QTableSelection				OneSelection; 
	int							toprow,bottomrow, leftcol, rightcol;  
	int							leftcolinword, rightcolinword; 
	int							cleari;
	Parse*						OneParse; 
	QString						OneWord; 
	int							leftpiece, rightpiece; 
	int							wordstartloc;
	int							piecei; 
	ParseCollection*			Onewordparsecollection;
	int							Index; 
	bool						LeftToRight; 
	int							LenOfOneWord; 
	int							realrow; 
	
	
	LeftToRight = m_Myalchemist ->m_leftToRight->isOn(); 
							
	

	NumberOfSelections = Table ->numSelections(); 
	
	
	for ( i=0; i<NumberOfSelections; i++)
	{
		OneSelection = Table ->selection(i); 
		toprow = OneSelection.topRow();
		bottomrow = OneSelection.bottomRow();
		
		for (cleari= toprow; cleari<=bottomrow; cleari++)
		{
			leftcol = OneSelection.leftCol();
			rightcol = OneSelection.rightCol(); 
			realrow = cleari + m_CurrentPage * m_EntryPerPage; 
			
			if ( ( leftcol == 0) && (rightcol == 0) )
			{
				OneWord = m_TableDisplayRowString[realrow];
				Onewordparsecollection = m_WordParses[OneWord];
				Index = m_TableDisplayRowStringIndex[realrow]; 
				OneParse = (*Onewordparsecollection)[Index];
				OneParse ->m_Comments = comment; 
				continue;
			}
			
			OneWord = m_TableDisplayRowString[realrow];
			Onewordparsecollection = m_WordParses[OneWord];
			Index = m_TableDisplayRowStringIndex[realrow]; 
			OneParse = (*Onewordparsecollection)[Index];
			
			wordstartloc = m_TableDisplayRowStartLoc[realrow];
			
			if ( !LeftToRight)
			{
				AdjustColsBecauseOfDisplayOrder(realrow, &leftcol, &rightcol); 
			}
			
			leftcolinword = leftcol - wordstartloc;
			rightcolinword = rightcol - wordstartloc;
			
			if ( leftcolinword < 0) leftcolinword = 0;
			if (rightcolinword >= OneWord.length()) rightcolinword =  OneWord.length() -1; 
				
			leftpiece = OneParse ->WhichPiece(leftcolinword); 
			rightpiece = OneParse ->WhichPiece(rightcolinword); 
			
			for ( piecei = leftpiece; piecei<= rightpiece; piecei++)
			{
				OneParse ->Commitdespinfo(piecei, score, allomorph, comment); 
			}
			
						
		}
		
	}
	
	
}


void WordCollection::DisplayDespriptionInfo(QTable* Table)
{
	// if only select on morpheme, then we display its information
	
	int							NumberOfSelections =0; 
	QTableSelection				OneSelection; 
	int							toprow,bottomrow, leftcol, rightcol;  
	int							leftcolinword, rightcolinword; 
	Parse*						OneParse; 
	QString						OneWord; 
	int							leftpiece, rightpiece; 
	int							wordstartloc;
	ParseCollection*			Onewordparsecollection;
	int							Index; 
	bool						LeftToRight; 
	int							realrow; 
	
	
	LeftToRight = m_Myalchemist ->m_leftToRight->isOn(); 						
	
	//QMessageBox::information( NULL, "debug", "come to display the morphemeinfo","OK" );

	NumberOfSelections = Table ->numSelections(); 
	
	if ( NumberOfSelections != 1) return; 
	
	OneSelection = Table ->selection(0); 
		
	toprow = OneSelection.topRow();
	bottomrow = OneSelection.bottomRow();
	
	if ( toprow != bottomrow ) 
	{
		m_Myalchemist ->m_scoringComboBox ->setCurrentItem(0);
		m_Myalchemist ->m_allomorphyLineEdit ->setText("");
		m_Myalchemist ->m_remarksTextEdit ->setText(""); 
		return; 
	}
	leftcol = OneSelection.leftCol();
	rightcol = OneSelection.rightCol(); 
	
	realrow = toprow + m_CurrentPage * m_EntryPerPage; 	
	
	if ( ( leftcol == 0) && (rightcol == 0) )
	{
		OneWord = m_TableDisplayRowString[realrow];
		Onewordparsecollection = m_WordParses[OneWord];
		Index = m_TableDisplayRowStringIndex[realrow]; 
		OneParse = (*Onewordparsecollection)[Index];
		m_Myalchemist ->m_remarksTextEdit ->setText(OneParse ->m_Comments); 
		return;
	}
			
			
	OneWord = m_TableDisplayRowString[realrow];
	Onewordparsecollection = m_WordParses[OneWord];
	Index = m_TableDisplayRowStringIndex[realrow]; 
	OneParse = (*Onewordparsecollection)[Index];
	

	wordstartloc = m_TableDisplayRowStartLoc[realrow];
	
	if ( !LeftToRight)
	{
		AdjustColsBecauseOfDisplayOrder(realrow, &leftcol, &rightcol); 
	}
	
	leftcolinword = leftcol - wordstartloc;
	rightcolinword = rightcol - wordstartloc;
	
	if ( leftcolinword >= OneWord.length())
	{
		m_Myalchemist ->m_scoringComboBox ->setCurrentItem(0);
		m_Myalchemist ->m_allomorphyLineEdit ->setText("");
		m_Myalchemist ->m_remarksTextEdit ->setText(""); 
		return; 
	}
	
	if ( leftcolinword < 0) leftcolinword = 0;
	if (rightcolinword >= OneWord.length()) rightcolinword =  OneWord.length() -1; 
		
	leftpiece = OneParse ->WhichPiece(leftcolinword); 
	rightpiece = OneParse ->WhichPiece(rightcolinword); 
	
	if ( leftpiece != rightpiece)
	{
	 	m_Myalchemist ->m_scoringComboBox ->setCurrentItem(0);
		m_Myalchemist ->m_allomorphyLineEdit ->setText("");
		m_Myalchemist ->m_remarksTextEdit ->setText(""); 
		return;  
	}
	m_Myalchemist ->m_scoringComboBox ->setCurrentItem(OneParse ->m_PieceScores[leftpiece]);
	m_Myalchemist ->m_allomorphyLineEdit ->setText(OneParse ->m_PieceAllormorphs[leftpiece]);
	m_Myalchemist ->m_remarksTextEdit ->setText(OneParse ->m_PieceComments[leftpiece]); 
			
}


void	WordCollection::ClearMe()
{
	m_Words.clear();
	m_ReverseWords.clear();
	m_FilteredWords.clear(); 
	m_TableDisplayRowString.clear(); 
	m_TableDisplayRowStartLoc.clear(); 
	m_Deletestrings.clear();
	m_Affectedstrings.clear();
	m_WordParses.clear();  
	m_NumberOfWords = 0;  
	m_LenOfLongestWord =0; 
	m_LenOfLongestAnalysedWord =0; 
	m_FilterIncludeString = ""; 
	m_FilterExcludeString ="";
	m_MostLetterLeftOfFilterIncludeString =0; 
	m_MostLetterRightOfFilterIncludeString =0; 
	m_CurrentDisplayType =0; 
	m_CurrentFilterType =0; 
	

} 


void  WordCollection::FindAnalysedOrUnAnalysedWords(int AnalysedType)
{

	m_AnalysedOrNoAnalysedWords.clear(); 
	m_LenOfLongestAnalysedWord = 0; 
	m_NumberOfAnalysedOrNoAnalysedWords = 0; 
	
	if ( AnalysedType == 0) 
	{
		m_AnalysedOrNoAnalysedWords = m_Words;	
		m_LenOfLongestAnalysedWord = m_LenOfLongestWord;
		m_NumberOfAnalysedOrNoAnalysedWords = m_NumberOfWords;  
		return; 
	}
	
	if ( AnalysedType == 1)
	{
		StringToParseCollection::Iterator				StringToParseCollectionIt;
		ParseCollection*								Onewordparsecollection;
		Parse*											OneParse; 
		QString											OneWord; 
		
		for ( StringToParseCollectionIt = m_WordParses.begin(); 	StringToParseCollectionIt != m_WordParses.end(); StringToParseCollectionIt ++)
		{
			OneWord = StringToParseCollectionIt.key(); 
			Onewordparsecollection = StringToParseCollectionIt.data(); 
			
			//QMessageBox::information( NULL, "debug", QString("%1").arg(m_NumberOfAnalysedOrNoAnalysedWords),"OK" );
			
			
			if ( Onewordparsecollection ->size() >1) 
			{
				m_AnalysedOrNoAnalysedWords.insert(OneWord, 1); 
				
				if (OneWord.length() > m_LenOfLongestAnalysedWord)
				{
					m_LenOfLongestAnalysedWord = OneWord.length();
				}
				
				m_NumberOfAnalysedOrNoAnalysedWords += Onewordparsecollection ->size();
				continue;  
			}
			
			OneParse = 	(*Onewordparsecollection)[1]; 
			
			if ( OneParse ->IsAnalysed() )
			{
				m_AnalysedOrNoAnalysedWords.insert(OneWord, 1);
				 
				if (OneWord.length() > m_LenOfLongestAnalysedWord)
				{
					m_LenOfLongestAnalysedWord = OneWord.length();
				}
				
				m_NumberOfAnalysedOrNoAnalysedWords++;
			}
			
			
		}
	
		
		return; 
	}  
	
	if ( AnalysedType == 2)
	{
		StringToParseCollection::Iterator				StringToParseCollectionIt;
		ParseCollection*								Onewordparsecollection;
		Parse*											OneParse; 
		QString											OneWord; 
		
		for ( StringToParseCollectionIt = m_WordParses.begin(); 	StringToParseCollectionIt != m_WordParses.end(); StringToParseCollectionIt ++)
		{
			OneWord = StringToParseCollectionIt.key(); 
			Onewordparsecollection = 	StringToParseCollectionIt.data(); 
			
			if ( Onewordparsecollection ->size() >1) 
			{
				continue;
			}
			
			OneParse = 	(*Onewordparsecollection)[1]; 
			if (! OneParse ->IsAnalysed() )
			{
				m_AnalysedOrNoAnalysedWords.insert(OneWord, 1);
				 
				if (OneWord.length() > m_LenOfLongestAnalysedWord)
				{
					m_LenOfLongestAnalysedWord = OneWord.length();
				}
				
				m_NumberOfAnalysedOrNoAnalysedWords++;
			}
		}	
	
		return; 
	}

} 

void	WordCollection::DuplicateWord(QTable* Table)
{
	if ( ( m_Deletestrings.size() != 0) || (m_Affectedstrings.size() !=0) || (m_DeleteDuplicatestrings.size() != 0))		
	{
		QMessageBox::information( NULL, "Attention", "Please commit your deletion before saving","OK" );
		return; 
	}	
	
	int							NumberOfSelections =0; 
	QTableSelection				OneSelection; 
	int							toprow,bottomrow;  
	int							realrow; 
	int							CurrentDisplayType = m_CurrentDisplayType; 						
	

	NumberOfSelections = Table ->numSelections(); 
	
	if ( NumberOfSelections > 1) 
	{
		QMessageBox::information( NULL, "Attention","Please only select one word to make a copy.","OK" );
		return; 
	}
	
	
	
	OneSelection = Table ->selection(0); 
	toprow = OneSelection.topRow();
	bottomrow = OneSelection.bottomRow();
	realrow = toprow + m_CurrentPage * m_EntryPerPage; 
	
	if ( toprow != bottomrow) 
	{
		QMessageBox::information( NULL, "Attention","Please only select one word to make a copy.","OK" );
		return; 
	}
	
	if ( toprow < 0) 
	{
		//QMessageBox::information( NULL, QString("%1").arg(toprow),"OK" );
		return; 
	}
	
	QString				OneWord; 
	int					Index;
	int					TotalCopies;  
	int					AddIndex; 
	int					StartAffectRow, CurrentTotalRows, NewTotalRows, CurrentTotalCols; 
	int					RealStartAffectRow, DisplayTotalRows;
	ParseCollection*	parsecollection;
	Parse*				Oneparse; 
	int					i, j; 
	MyTableItem*		MyOneItem;
	QChar				OneLetter; 
	int					Displaycolortype;
	int					type; 
	QHeader*			Vheader; 
	int					CurrentStartloc; 
	int					LenOfOneString; 
	bool				LeftToRight;
	int					realj;  
	
	LeftToRight = m_Myalchemist ->m_leftToRight->isOn(); 	
	
	
	Vheader = Table -> verticalHeader();
	
	
	
	OneWord  = m_TableDisplayRowString[realrow];
	Index = m_TableDisplayRowStringIndex[realrow]; 
	TotalCopies = m_Words[OneWord]; 
	AddIndex = TotalCopies + 1;
	StartAffectRow = toprow + (TotalCopies - Index) + 1; 
	RealStartAffectRow = realrow + (TotalCopies - Index) + 1; 
	CurrentTotalRows = m_DisplayedAllnumber;
	CurrentTotalCols = Table ->numCols(); 
	NewTotalRows = CurrentTotalRows + 1;
	DisplayTotalRows = Table ->numRows(); 
	CurrentStartloc =  m_TableDisplayRowStartLoc[realrow];
	Table ->setNumRows(DisplayTotalRows + 1); 
	
	// update m_words and m_wordparses
	m_Words[OneWord] = AddIndex;
	parsecollection = m_WordParses[OneWord];
	Oneparse = new Parse(this, OneWord); 
	parsecollection ->insert(AddIndex, Oneparse); 
	m_NumberOfWords ++; 
	m_DisplayedAllnumber ++; 
	
	if ( CurrentDisplayType >= 4)
	{
		m_NumberOfFilteredWords ++; 
	}
	
	//update the m_Tabledisplayrow...
	m_TableDisplayRowString.insert(NewTotalRows-1, QString("")); 
	for ( i= CurrentTotalRows-1; i>= RealStartAffectRow; i--)
	{
		m_TableDisplayRowString[i+1] = m_TableDisplayRowString[i];
	}
	m_TableDisplayRowString[RealStartAffectRow] = OneWord; 
	
	
	m_TableDisplayRowStringIndex.insert(NewTotalRows-1, 1); 
	for ( i= CurrentTotalRows-1; i>= RealStartAffectRow; i--)
	{
		m_TableDisplayRowStringIndex[i+1] = m_TableDisplayRowStringIndex[i];
	}
	m_TableDisplayRowStringIndex[RealStartAffectRow]= AddIndex;
	
	
	m_TableDisplayRowStartLoc.insert(NewTotalRows-1, 1); 
	for ( i= CurrentTotalRows-1; i>= RealStartAffectRow; i--)
	{
		m_TableDisplayRowStartLoc[i+1] = m_TableDisplayRowStartLoc[i];
	}
	m_TableDisplayRowStartLoc[RealStartAffectRow]= CurrentStartloc;
	 
	
	
	if ( StartAffectRow > m_EntryPerPage -1 )
	{
		Table ->setNumRows(DisplayTotalRows); 
		//QMessageBox::information( NULL, "debug","touch boundary","OK" );
		return; 
	}
	
	//update table show
	Vheader ->setLabel(DisplayTotalRows, QString("%1").arg(DisplayTotalRows)); 
	MyOneItem = new MyTableItem( Table, QTableItem::Never, OneWord);
	MyOneItem->setFont( m_Myalchemist->getTableFont() );
	Table ->setItem (DisplayTotalRows, 0, MyOneItem );
	Table ->setColumnWidth(0,10*m_Myalchemist->getTableFont().pointSize());
	Table ->setRowHeight(DisplayTotalRows,2*m_Myalchemist->getTableFont().pointSize());
	
	LenOfOneString = OneWord.length(); 
	
	for ( j=1; j<CurrentStartloc; j++)
	{
		MyOneItem = new MyTableItem(Table, QTableItem::Never, QString("") ); 
		MyOneItem ->setColor( getColor( -1 ) );
		MyOneItem->setFont( m_Myalchemist->getTableFont() );		
		MyOneItem->setBold( FALSE );
		MyOneItem->setItalic( FALSE );
		Table ->setItem(DisplayTotalRows,j,MyOneItem);
		Table ->setColumnWidth(j,2*m_Myalchemist->getTableFont().pointSize()); 
	}
	
	
	for ( j=CurrentStartloc; j<CurrentStartloc + LenOfOneString; j++)
	{
		if ( LeftToRight)
		{
			OneLetter = OneWord[j - CurrentStartloc];
			realj = j - CurrentStartloc;
		}
		else
		{
			OneLetter = OneWord[LenOfOneString -j + CurrentStartloc -1];
			realj = LenOfOneString -j + CurrentStartloc -1;	
		}			
		
		Displaycolortype = -1;
		type = 0; 
		
		MyOneItem = new MyTableItem(Table, QTableItem::Never, QString("%1").arg(OneLetter) ); 
		MyOneItem ->setColor( getColor( Displaycolortype ) );
		MyOneItem->setFont( m_Myalchemist->getTableFont() );
		if( type == 0 )
		{			
			MyOneItem->setBold( FALSE );
			MyOneItem->setItalic( FALSE );
		}
		else if( type == 1 ) MyOneItem->setBold( TRUE );
		else if( type == 2 ) MyOneItem->setItalic( TRUE );
		Table ->setItem(DisplayTotalRows,j,MyOneItem);
		Table ->setColumnWidth(j,2*m_Myalchemist->getTableFont().pointSize()); 
	}
	
	for ( j= CurrentStartloc + LenOfOneString; j< CurrentTotalCols; j++)
	{
		MyOneItem = new MyTableItem(Table, QTableItem::Never, QString("") ); 
		MyOneItem ->setColor( getColor( -1 ) );
		MyOneItem->setFont( m_Myalchemist->getTableFont() );		
		MyOneItem->setBold( FALSE );
		MyOneItem->setItalic( FALSE );
		Table ->setItem(DisplayTotalRows,j,MyOneItem);
		Table ->setColumnWidth(j,2*m_Myalchemist->getTableFont().pointSize()); 
	
	}
	
	
	for ( i = DisplayTotalRows -1; i >= StartAffectRow; i--)
	{
		Table ->swapRows(i, i+1); 
	}
	
	if ( DisplayTotalRows >= m_EntryPerPage)
	{
		Table ->removeRow(DisplayTotalRows);
		Table ->setNumRows(DisplayTotalRows);  
	}
	
	
	
} 


void  WordCollection::AdjustColsBecauseOfDisplayOrder(int row,int* ptrleftcol, int* ptrrightcol )
{
	int							leftcol, rightcol;
	int							newleftcol, newrightcol;
	int							startlocinrow, endlocinrow;
	QString						OneWord; 
	int							LenOfOneWord; 
	int							Leftcolinword, Rightcolinword; 
	
	
	OneWord = m_TableDisplayRowString[row];
	LenOfOneWord = OneWord.length(); 
	startlocinrow = m_TableDisplayRowStartLoc[row];
	endlocinrow = startlocinrow + LenOfOneWord -1; 
	
	leftcol = *ptrleftcol;
	rightcol = *ptrrightcol; 
	
	
	
	if ( ( leftcol < startlocinrow ) && ( endlocinrow < rightcol ))
	{
		return; 
	}
	
	if ( rightcol < startlocinrow)
	{
		return; 
	}
	
	if ( leftcol > endlocinrow)
	{
		return; 
	}
	
	if ( leftcol < startlocinrow) 
	{
		leftcol = startlocinrow;
	}
	
	if ( rightcol > endlocinrow)
	{
		rightcol = endlocinrow;
	}
	
	Leftcolinword = LenOfOneWord - (leftcol - startlocinrow) -1; 
	Rightcolinword = LenOfOneWord - (rightcol - startlocinrow) -1;
	
	newleftcol = startlocinrow + Rightcolinword;
	newrightcol = startlocinrow + Leftcolinword;
	
	*ptrleftcol = newleftcol;
	*ptrrightcol = newrightcol; 

	return; 
}  

int	 WordCollection::GetCount() 
{ 
		
	if ( m_CurrentDisplayType == -1)
	{
		return 0; 
	}

	
	if (  m_CurrentDisplayType < 4)
	{
		return m_NumberOfWords; 
	}
	
	if (  m_CurrentDisplayType < 6)
	{
		return m_NumberOfFilteredWords; 
	}

	return 0; 

}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MyTableItem::MyTableItem(QTable * table, EditType et, const QString & text) : QTableItem(table,et,text)
{
	m_Color = "white"; 
	m_Bold = FALSE;
	m_Italic = FALSE;
	// Font starts as system default...
}


void	MyTableItem::paint(QPainter* p, const QColorGroup& cg, const QRect& cr, bool selected)
{
	QColorGroup	newcg(cg);
	
	QFont font = m_Font;
	font.setBold( m_Bold );
	font.setItalic( m_Italic );	
	p->setFont( font );
	
	newcg.setColor( QColorGroup::Base, m_Color );
	QTableItem::paint( p , newcg , cr , selected );
} 



