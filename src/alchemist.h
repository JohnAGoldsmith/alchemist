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

#ifndef ALCHEMIST_H
#define ALCHEMIST_H

#include <qtable.h>
#include <qsettings.h>
#include <qprogressbar.h>
#include <qlabel.h>
#include <qdom.h>
#include <qcombobox.h>

#include "alchemistbase.h"



class WordCollection;

class Alchemist : public AlchemistBase
{
	Q_OBJECT
  
private:
	WordCollection*	m_WordCollection; 
	int				m_SortType; 
	int				m_WordFilterType;  // {0=All, 1=Analyzed, 2=Unanalyzed}

	QString			m_SaveFileName ;
	QSettings		m_Settings;
	int				m_TotalNumberOfDistinctWords;
	
	bool 			m_projectDirty;
	
	QProgressBar*	m_ProgressBar;
	QLabel*			m_StatusBar1,
		  *			m_StatusBar2;
		  
	int				m_ColorIndex;
					
	QFont			m_TableFont;
	
	// Paging
	int				m_EntriesPerPage;
	int				m_PageNumber;
	QDomDocument	m_DocInfo;
	
	
public:
		
	int				m_Score;
  
public:
	Alchemist( QWidget* parent = 0, const char* name = 0, WFlags f = WType_TopLevel );
	~Alchemist();
	
	QString			getStatusBar1() const { return m_StatusBar1->text(); }
	QString			getStatusBar2() const { return m_StatusBar2->text(); }

	void			setStatusBar1( QString text );
	void			setStatusBar2( QString text );

	void			resetCountDown();
	void			countDownOnProgressBar( int, int, int step=100 );
	
	int				getNextColorIndex();
	QFont			getTableFont() const { return m_TableFont; }
	
	QDomDocument	getDocInfo();
	void			setDocInfo( QDomDocument doc ) { m_DocInfo = doc; }
	
	
	void 			pageChange();
	int	 			getPageNumber(){ return m_PageNumber; }
	int	 			getEntryPerPage() { return m_EntriesPerPage; }
	
	

public slots:
	// File menu
	void fileClose();
	void fileExit();
	void fileNew();
	void fileOpen(); 
	void filePreferences();
	void fileSave();
	void fileSaveAs();
	
	// Edit menu
	void editChangeFont();
	void editDelete();
	void editDocInfo();
	void editRedo();
	void editUndo();
	void editRefresh();
	void editSetDirectionality();
	
	// Help menu
	void helpAbout();
	
	// User input widgets
	void allomorphyChanged( const QString& );
	void enableMorphemeInfo();
	void remarksChanged();
	void setScoring( int );
	void setSorting( int );
	void sort(); 
	void showFiltered();
	void tableSelectionChanged();
	void setWordFilter( int );
	void enableInfoCommit();
	void commitInfo(); 
	void tableContextMenu();
	
	// Morphology menu
	void newRoot();
	void newAffix(); 
	void clearCuts();
	void duplicateWord(); 
	// Others
	int	 getfiltertype() {return m_WordFilterType;};
	void filterSelected();
	
	// Scoring
	void scoreNot() { m_scoringComboBox->setCurrentItem(0); commitInfo(); }
	void scoreCertain() { m_scoringComboBox->setCurrentItem(1); commitInfo(); }
	void scoreSomewhat() { m_scoringComboBox->setCurrentItem(2); commitInfo(); }
	void scoreUn() { m_scoringComboBox->setCurrentItem(3); commitInfo(); }
	
	// Paging
	void nextPage() { m_PageNumber++; m_pageComboBox->setCurrentItem( m_PageNumber ); pageChange(); }
	void prevPage() { m_PageNumber--; m_pageComboBox->setCurrentItem( m_PageNumber ); pageChange(); }
	void pageSelected(int i) { m_PageNumber = i; pageChange(); }
	
signals:

	void changeScore( int );
	
protected:
  virtual void closeEvent( QCloseEvent * );
  virtual void resizeEvent( QResizeEvent * );
  virtual void moveEvent( QMoveEvent * );
	 
};

#endif // #ifndef ALCHEMIST_H
