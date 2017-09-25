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

#include "alchemist.h"
#include "general.h"



Alchemist::Alchemist( QWidget* parent, const char* name, WFlags f )
		:AlchemistBase( parent, name, f )
{
	// YuHu Added Begin
	m_WordCollection = NULL;
	m_Score = 0; 
	// YuHu Added End
	
	// SETTINGS
//	m_Settings.setPath( "UChicago", "Alchemist" );
		
	m_TotalNumberOfDistinctWords = m_Settings.readNumEntry( "/UChicago/Alchemist/Preferences/NumberDistinctWords", 500 );

	QString family = m_Settings.readEntry( "/UChicago/Alchemist/Preferences/FontFamily" );
	int pointSize = m_Settings.readNumEntry( "/UChicago/Alchemist/Preferences/FontSize", 16 );
	m_TableFont = QFont( family, pointSize );
	
	bool b1, b2, b3, b4;
	setMinimumSize( 800, 600 );
	QSize mysize( m_Settings.readNumEntry( "/UChicago/Alchemist/Geometry/Width", 800, &b1 ), \
		m_Settings.readNumEntry( "/UChicago/Alchemist/Geometry/Height", 600, &b2 ) );
	QPoint mypoint( m_Settings.readNumEntry( "/UChicago/Alchemist/Geometry/X_Pos", 0, &b3 ), \
		m_Settings.readNumEntry( "/UChicago/Alchemist/Geometry/Y_Pos", 0, &b4 ) );
	if( b1 && b2 && b3 && b4 )
	{
		resize( mysize );
		move( mypoint );
	}
	else resize( sizeHint() );


	// HACK: setNormal() wasn't working when overloaded, so this is a hack that makes it so that if
	// you close the window maximized, the next time you open it it will be maximized and when
	// normalized will go back to the previous (recorded) normal position
	mysize = QSize( m_Settings.readNumEntry( "/UChicago/Alchemist/Geometry/Width_Old", 800, &b1 ), \
		m_Settings.readNumEntry( "/UChicago/Alchemist/Geometry/Height_Old", 600, &b2 ) );
	mypoint = QPoint( m_Settings.readNumEntry( "/UChicago/Alchemist/Geometry/X_Pos_Old", 0, &b3 ), \
		m_Settings.readNumEntry( "/UChicago/Alchemist/Geometry/Y_Pos_Old", 0, &b4 ) );

	if ( QApplication::desktop()->width() <= width() + 10 ||
		 QApplication::desktop()->height() <= height() + 30 )
	{
		if( b1 && b2 && b3 && b4 )
		{
			resize( mysize );
			move( mypoint );
		}

		showMaximized();
	}
	
	// STATUS BAR
	QStatusBar* sb = statusBar();
	m_StatusBar1 = new QLabel(this, "status bar 1");
	m_StatusBar1->setMaximumWidth( 250 );
	sb->addWidget( m_StatusBar1, 33, true );

	m_ProgressBar = new QProgressBar();
	sb->addWidget( m_ProgressBar, 33, true );
	m_ProgressBar->setMaximumWidth( 250 );

	m_StatusBar2 = new QLabel(this, "status bar 2");
	sb->addWidget( m_StatusBar2, 33, true );
	m_StatusBar2->setMaximumWidth( 250 );
	
	m_WordFilterType = 0;	
	m_projectDirty = 0;
	
	m_EntriesPerPage = m_Settings.readNumEntry( "/UChicago/Alchemist/Preferences/EntriesPerPage", 200 );
	m_PageNumber = 0;
	m_pageComboBox->clear();
	m_previousPageButton->setEnabled( FALSE );
	m_nextPageButton->setEnabled( FALSE );
	
	// CONNECTIONS
	connect( this, SIGNAL( changeScore(int) ), this, SLOT( setScoring(int) ) );
	
	resetCountDown();
}


Alchemist::~Alchemist()
{
	if( m_WordCollection ) delete m_WordCollection;	
	if( m_ProgressBar ) delete m_ProgressBar;
	if( m_StatusBar1 ) delete m_StatusBar1;
	if( m_StatusBar2 ) delete m_StatusBar2;
}



void Alchemist::allomorphyChanged( const QString& allomorph )
{
}



void Alchemist::clearCuts()
{
	if( m_WordCollection == NULL )
	{
		QMessageBox::information( NULL, "Error", "Please read in a file first.", "OK" );
		return;
	}

	m_WordCollection->ClearCuts( m_tableDisplay ); 

}
 

// Called before closing the main window
void Alchemist::closeEvent(QCloseEvent* close)
{
  bool verify = TRUE;

  // Verify information saved

  if( verify && m_projectDirty )
  {
    QString message = "Would you like to save your changes before closing?";
    VerifyDialog *saveCheckDlg = new VerifyDialog(message);
    saveCheckDlg->setCaption( saveCheckDlg->caption() + "Save Project?" );

    switch( saveCheckDlg->exec() )
    {
    case RESULT_YES:
      // User clicked 'Yes', save changes and close
      fileSave();
      if( m_projectDirty ) close->ignore();
      else close->accept();
      break;
    case RESULT_NO:
      // User clicked 'No', close without saving
      close->accept();
      break;
    case RESULT_CANCEL:
    default:
      // User clicked 'Cancel', do not close
      close->ignore();
      break;
    }
  }

  // Allow the window to close
  else close->accept();
}


void Alchemist::commitInfo()
{
	if( m_WordCollection == NULL )
	{
		QMessageBox::information( NULL, "Error", "Please read in a file first.", "OK" );
		return;
	}

	QString allormorph, comment;
	
	allormorph = m_allomorphyLineEdit ->text();
	comment = m_remarksTextEdit ->text();
	
	if ( allormorph == NULL)
	{
		allormorph = QString("");
	}
	
	if (comment == NULL)
	{
		comment = QString("");
	}
		
	m_WordCollection ->CommitDespriptionInfo( m_tableDisplay, m_Score, allormorph, comment);
	
	m_commitInfoButton->setEnabled( FALSE );
	
	
	 m_projectDirty = TRUE;
}

void Alchemist::countDownOnProgressBar( int i, int total, int stepsize )
{
  if( !stepsize ) stepsize = total/100;
  if( stepsize < 1 ) stepsize = 1;
  
  if( i < 0  || i > total )    // Reset if less than 0 or greater than total
  {
    m_ProgressBar->reset();
  }
  else
  {
    // Update on multiples of stepsize
    if( i % stepsize == 0 )
    {
      m_ProgressBar->setProgress( i, total );
    }
  }
}


void Alchemist::duplicateWord()
{
	if( m_WordCollection == NULL )
	{
		QMessageBox::information( NULL, "Error", "Please read in a file first.", "OK" );
		return;
	}
	
	 m_WordCollection->DuplicateWord( m_tableDisplay );
	 
	 m_projectDirty = TRUE; 


}




void Alchemist::editChangeFont()
{
	bool ok;
	QFont font = QFontDialog::getFont( &ok, m_TableFont, this, "font dialog" );
	
	if( ok ) m_TableFont = font;
	
	m_WordCollection->DisplayOnTable( m_tableDisplay, m_SortType ); 
}


void Alchemist::editDelete()
{
	if( m_WordCollection == NULL )
	{
		QMessageBox::information( NULL, "Error", "Please read in a file first.", "OK" );
		return;
	}
	
	 m_WordCollection->EditDelete( m_tableDisplay );
	 
	 
	 m_projectDirty = TRUE; 
}


void Alchemist::editDocInfo()
{
	DocInfoDialog getDocInfo( m_DocInfo, this, "getDocInfo", TRUE );
	
	if( getDocInfo.exec() == QDialog::Accepted )
	{
		m_DocInfo = QDomDocument();
		
		QDomElement doc = m_DocInfo.createElement( "documentinfo" );
		
		QDomElement creators = m_DocInfo.createElement( "creators" );
		QDomText creatorsText = m_DocInfo.createTextNode( getDocInfo.getCreators() );
		creators.appendChild( creatorsText );		
		doc.appendChild( creators );
		
		QDomElement affiliation = m_DocInfo.createElement( "affiliation" );
		QDomText affiliationText = m_DocInfo.createTextNode( getDocInfo.getAffiliation() );
		affiliation.appendChild( affiliationText );
		doc.appendChild( affiliation );
		
		QDomElement language = m_DocInfo.createElement( "language" );
		QDomText languageText = m_DocInfo.createTextNode( getDocInfo.getLanguage() );
		language.appendChild( languageText );
		doc.appendChild( language );
		
		QDomElement remarks = m_DocInfo.createElement( "remarks" );
		QDomText remarksText = m_DocInfo.createTextNode( getDocInfo.getRemarks() );
		remarks.appendChild( remarksText );
		doc.appendChild( remarks );
		
		m_DocInfo.appendChild( doc );

		m_projectDirty = TRUE;
	}	
}


void Alchemist::editRedo()
{}


void Alchemist::editRefresh()
{
	if( m_WordCollection == NULL )
	{
		QMessageBox::information( NULL, "Error", "Please read in a file first.", "OK" );
		return;
	}
	
	m_WordCollection->AcceptDelete(m_tableDisplay); 
}


void Alchemist::editSetDirectionality()
{
	m_WordCollection->DisplayOnTable( m_tableDisplay, m_SortType ); 
}


void Alchemist::editUndo()
{}


void Alchemist::enableInfoCommit()
{
	m_commitInfoButton->setEnabled( TRUE );
}


void Alchemist::enableMorphemeInfo()
{
	QTableSelection selection;
	int i;
	bool enable = FALSE;
	bool wordenable = TRUE;
	
	for( i = 0; i < m_tableDisplay->numSelections(); i++ )
	{
		selection = m_tableDisplay->selection(i);
		
		if( selection.isActive() &&
			( selection.leftCol() != 0 || selection.rightCol() != 0  ) )
		{
			enable = TRUE;
			wordenable = FALSE;
		}
	}
	
	m_infoGroupBox->setEnabled( enable );
	
	m_scoringComboBox->setEnabled( enable );
	m_scoreTextLabel->setEnabled( enable );
	
	m_allomorphyLineEdit->setEnabled( enable );
	m_allomorphyTextLabel->setEnabled( enable );
	
	m_remarksTextEdit->setEnabled( enable );
	m_remarksTextLabel->setEnabled( enable );
	
	if (!enable)
	{ 
		m_infoGroupBox->setEnabled( wordenable );
		m_remarksTextEdit->setEnabled( wordenable );	
		m_remarksTextLabel->setEnabled( wordenable );
	}
	
	if ( m_WordCollection == NULL) return; 
	
	m_WordCollection ->DisplayDespriptionInfo(m_tableDisplay); 
	
	// This is enabled and disabled for other reasons, always should
	// be false when these are first enabled
	m_commitInfoButton->setEnabled( FALSE );
	
}


void Alchemist::fileClose()
{
  bool verify = TRUE;

  // Verify information saved

  if( verify && m_projectDirty )
  {
    QString message = "Would you like to save your changes before closing?";
    VerifyDialog *saveCheckDlg = new VerifyDialog(message);
    saveCheckDlg->setCaption( saveCheckDlg->caption() + "Save Project?" );

    switch( saveCheckDlg->exec() )
    {
    case RESULT_YES:
      // User clicked 'Yes', save changes and close
      fileSave();
      if( m_projectDirty ) return;
      break;
    case RESULT_NO:
      // User clicked 'No', close without saving
	  m_projectDirty = FALSE;
      break;
    case RESULT_CANCEL:
    default:
      // User clicked 'Cancel', do not close
      return;
      break;
    }
  }
  
	m_SaveFileName = "";
	m_pageComboBox->clear();

	if( m_WordCollection )
	{
  		m_WordCollection ->ClearMe(); 
		int					Currentrows;
		int					Currentcols;  
		int					cleari, clearj; 

		Currentrows = m_tableDisplay ->numRows();
		Currentcols = m_tableDisplay ->numCols(); 
	
	
		for (cleari = 0; cleari < Currentrows; cleari++)		
		{
			for (clearj = 0; clearj < Currentcols ; clearj++)
			{
				m_tableDisplay ->clearCell(cleari, clearj);
			}
		
		}
	
		delete m_WordCollection; 
		m_WordCollection = NULL;
	}
}


void Alchemist::fileExit()
{
	this->close();
}


void Alchemist::fileNew()
{
	fileClose();

	// YuHu Added Begin
	int NumberOfDistinctWords = 0;
	bool ok;
	m_TotalNumberOfDistinctWords = QInputDialog::getInteger( "Alchemist : Number of Words", 
															 "How many distinct words would you like in the gold standard collection?",
															 m_TotalNumberOfDistinctWords,
															 MIN_NUMBER_OF_DISTINCT_WORDS,
															 MAX_NUMBER_OF_DISTINCT_WORDS,
															 NUMBER_OF_DISTINCT_WORDS_STEP,
															 &ok,
															 this,
															 "get word count dialog" );
	
	if( !ok ) return;
	
	m_Settings.writeEntry( "/UChicago/Alchemist/Preferences/NumberWordsPerPage", m_TotalNumberOfDistinctWords ); 

	// Get the last file name used
	QString openFileName = m_Settings.readEntry( "/UChicago/Alchemist/File/New", QString::null );

	openFileName = QFileDialog::getOpenFileName( openFileName,
												 "Text Files (*.txt);;Rich Text Files (*.rtf);;All Files (*)",
												 this,
												 "open file dialog",
												 "Choose a file to open" );
												 
	if( !openFileName.isEmpty() )
	{ 
		m_Settings.writeEntry( "/UChicago/Alchemist/File/New", openFileName );
		
		//QMessageBox::information( NULL, "Attention",	"Start To Load File","OK" );
		// TODO: give message of unsaved data when necessary so we don't clobber something already done
		if( m_WordCollection ) delete m_WordCollection;
		m_WordCollection = new WordCollection(this);
	
		QFile File( openFileName );
		if ( File.open( IO_ReadOnly ) )
		{
        	QTextStream    stream( &File );
    		QString      word, temp, localcasedword;

		 	stream.setEncoding( QTextStream::Locale );

			setStatusBar1( "Reading words from file..." );
			resetCountDown();
			
		    while( (!stream.atEnd())&&(NumberOfDistinctWords < m_TotalNumberOfDistinctWords) )
    		{				
      			stream >> word;

 		        if( word.endsWith("-") )
			    {
        			stream >> temp;
        			word = word.left( word.length()-1 ) + temp;
      			}

			    if (word.length()  == 0)
      			{
        			continue;
      			}
				
				localcasedword = word.lower(); 
				NumberOfDistinctWords = m_WordCollection ->InsertOneWord(localcasedword); 
				// QMessageBox::information( NULL, "Data",	word,"OK" );
				
				countDownOnProgressBar( NumberOfDistinctWords, 
										m_TotalNumberOfDistinctWords, 
										m_TotalNumberOfDistinctWords/100 );
			}
    		File.close();
			
			setStatusBar1( "" );
			resetCountDown();
			//QMessageBox::information( NULL, "NumberOfDistinctWords",QString("Have read %1 distinct words.").arg(NumberOfDistinctWords),"OK" );
			
			// By default, we will display these words alphabatically
			m_PageNumber = 0; 
			m_WordCollection ->DisplayOnTable(m_tableDisplay, 0);
			
			m_pageComboBox ->clear(); 
			for( int pages = 0; pages < ceil( (double)m_WordCollection->GetCount()/(double)m_EntriesPerPage ); pages++ )
			{
				m_pageComboBox->insertItem( QString("%1").arg( pages ) );
			}
			m_pageComboBox ->setCurrentItem(m_PageNumber);
			if( ceil( (double)m_WordCollection->GetCount()/(double)m_EntriesPerPage ) ) m_nextPageButton->setEnabled( TRUE );
		}
		else
		{
			QMessageBox::information( NULL, "Attention", "Unable to open " + openFileName + " .", "OK" );
		} 
	}	
		
	// YuHu Added End
}

void Alchemist::fileOpen()
{

	fileClose();

	//	m_TotalNumberOfDistinctWords 
	
	// Get the last file name used
	QString openFileName = m_Settings.readEntry( "/UChicago/Alchemist/File/Open", QString::null );
	
	openFileName = QFileDialog::getOpenFileName( openFileName,
												 "XML Files (*.xml)",
												 this,
												 "open file dialog",
												 "Choose a file to open" );
												 
	if( !openFileName.isEmpty() )
	{ 
		
		if( m_WordCollection ) delete m_WordCollection;
		m_WordCollection = new WordCollection(this);
		
		m_SaveFileName = openFileName;
	
		QFile File( openFileName );
		if ( File.open( IO_ReadOnly ) )
		{
			QDomDocument doc( "Goldstandard" );
				
			 if( !doc.setContent(&File) )
			 {
  				File.close();
  				return;
			 }
			
			QDomElement root = doc.documentElement();
  		
			QString		debugstring; 
			
			debugstring = root.tagName();
			
			if( root.tagName() != "GDS")
			{
				QMessageBox::information( NULL, "Error", "Sorry, we can't read this xml tag: " +debugstring , "OK" );
				File.close();
				return; 
			}
			
			// Read the header
			 QDomNode header = root.firstChild();

			 QDomElement direction = header.nextSibling().toElement();
			 if( direction.hasAttribute( "left2right" ) )
			 {
			 	if( direction.attributeNode( "left2right" ).value() == "false" )
					m_leftToRight->setOn( FALSE );
			 } 
			
			// Filling into the docinfo
			 // Read the content
			 QDomNode contentnode = direction.nextSibling();
			 QDomElement content = contentnode.toElement();

			 if( content.tagName() != "content" )
    		 {
			 	QMessageBox::information( NULL, "Error", "Sorry, the xml file format is not supported", "OK" );
				File.close();
				return;
			 }

			 
			 // Get document information from header
			 
			 m_DocInfo = QDomDocument();
			 m_DocInfo.appendChild( header );
			 
			 
			 
			 QString				value; 
			 int					supposedtotalnumberofwords; 
			 QString				key;
			 QString				wordcomment; 
			 int					numberofpieces;  
			 int					start; 
			 int					type;
			 int					color; 
			 int					score;
			 QString				allormorph, comment; 
			 int					Index; 
			 
			 value = content.attribute("number", "100"); 
			 supposedtotalnumberofwords = value.toInt(); 
			 
			 setStatusBar1( "Reading words from file..." );
			 resetCountDown();
			 
			 QDomNode onewordnode = content.firstChild();
			 
			 while (!onewordnode.isNull())
			 {
			 	QDomElement oneword = onewordnode.toElement();
			 	if( !oneword.isNull() )
  				{
					if( oneword.tagName() == "word" )
    				{
						key = oneword.attribute( "key", "" );
						if (key == "")
						{
							onewordnode = onewordnode.nextSibling();
							continue; 
						}
						
						value = oneword.attribute("morphemes", "0"); 
						numberofpieces = value.toInt();
						
						if (numberofpieces == 0)
						{
							onewordnode = onewordnode.nextSibling();
							continue;
						}
						
						wordcomment = oneword.attribute("comment", "");
						
						
						m_TotalNumberOfDistinctWords = m_WordCollection ->InsertOneWord2(key, &Index); 
						
						QDomNode onepiecenode = oneword.firstChild();		
						
						while (!onepiecenode.isNull())
			 			{
							QDomElement onepiece = onepiecenode.toElement();
			 				if( !onepiece.isNull() )
  							{
								if( onepiece.tagName() == "morpheme" )
    							{
									value = onepiece.attribute("start", "-1");
									start = value.toInt();
									value =onepiece.attribute("type", "-1"); 
									type = value.toInt();
									value = onepiece.attribute("color", "-2");
									color = value.toInt();
									value = onepiece.attribute("score", "0");
									score = value.toInt();
									allormorph = onepiece.attribute("allomorph", "");
									comment = onepiece.attribute("comment", "");
									
									if ( ( start == -1) || (type == -1) || (color == -2)) 
 									{
										onepiecenode = onepiecenode.nextSibling();
										continue; 
									}
									
									
									
									m_WordCollection ->ParseOneWord(key, start, type, color, true, score, allormorph, comment, Index, wordcomment);
									 
									
								}
							}	
						
							onepiecenode = onepiecenode.nextSibling();
						}			
						
						countDownOnProgressBar( m_TotalNumberOfDistinctWords, supposedtotalnumberofwords, supposedtotalnumberofwords/100 );
						
					}
				}
					
				onewordnode = onewordnode.nextSibling();
			 }
			 
			 if ( m_TotalNumberOfDistinctWords != supposedtotalnumberofwords ) 
			 {
			 	//QMessageBox::information( NULL, "Attention", "The number attribute in the content tag is not correct!", "OK" );
			 }
			 
		}
		else
		{
			QMessageBox::information( NULL, "Attention", "Unable to open " + openFileName + " .", "OK" );
			return; 
		}
    	
		File.close();
			
		setStatusBar1( "" );
		resetCountDown();
		m_PageNumber = 0; 
		m_WordCollection ->DisplayOnTable(m_tableDisplay, 0);
		
		m_pageComboBox ->clear(); 
		for( int pages = 0; pages < ceil( (double)m_WordCollection->GetCount()/(double)m_EntriesPerPage ); pages++ )
		{
			m_pageComboBox->insertItem( QString("%1").arg( pages ) );
		}
		m_pageComboBox ->setCurrentItem(m_PageNumber);
		if( ceil( (double)m_WordCollection->GetCount()/(double)m_EntriesPerPage ) ) m_nextPageButton->setEnabled( TRUE );
	}
	else
	{
		return;
	} 
}	


void Alchemist::filePreferences()
{
	PreferencesDialog *prefDlg = new PreferencesDialog( m_EntriesPerPage, this );
	if( prefDlg->exec() == QDialog::Accepted )
	{
		// Get the settings from dialog
		m_EntriesPerPage = prefDlg->getNumberOfWordsPerPage();

//		QMessageBox::information( NULL, "debug", QString("%1").arg( m_EntriesPerPage ), "OK" );	
		
		// Write out to settings
		m_Settings.writeEntry( "/UChicago/Alchemist/Preferences/EntriesPerPage", m_EntriesPerPage );

	
		m_PageNumber = 0;
		if( m_WordCollection ) m_WordCollection->DisplayOnTable( m_tableDisplay, m_SortType );

		m_pageComboBox ->clear(); 
		for( int pages = 0; pages < ceil( (double)m_WordCollection->GetCount()/(double)m_EntriesPerPage ); pages++ )
		{
				m_pageComboBox->insertItem( QString("%1").arg( pages ) );
		}
		m_pageComboBox ->setCurrentItem(m_PageNumber);
		if( ceil( (double)m_WordCollection->GetCount()/(double)m_EntriesPerPage ) ) m_nextPageButton->setEnabled( TRUE );

	}
}



void Alchemist::fileSave()
{
	if( m_SaveFileName.length() > 0 )
	{
		// Write all the canvas items to XML and save to file
		QFile saveFile( m_SaveFileName );
		if ( saveFile.open( IO_WriteOnly ) ) 
		{
			QTextStream outStream( &saveFile );
			outStream.setEncoding( QTextStream::Unicode );
		
			this ->m_WordCollection ->Save(outStream); 
			
			m_projectDirty = FALSE;
			
			saveFile.close();
		}
	}
	else fileSaveAs();
	
}


void Alchemist::fileSaveAs()
{
	if( m_WordCollection == NULL )
	{
		QMessageBox::information( NULL, "Error", "Please read in a file first.", "OK" );
		return;
	}

	// Get the save file name
	QString saveFileName = m_Settings.readEntry( "/UChicago/Alchemist/File/SaveAs", QString::null );
	saveFileName = QFileDialog::getSaveFileName( saveFileName,
												 "XML Files (*.xml)",
												 this,
												 "save file dialog",
												 "Choose a filename to save under" );
  
	if( !saveFileName.isEmpty() ) 
	{
		m_Settings.writeEntry( "/UChicago/Alchemist/File/SaveAs", saveFileName );
		m_SaveFileName = saveFileName;
	
		int dot = m_SaveFileName.findRev('.');
		QString type = m_SaveFileName.right( m_SaveFileName.length() - dot - 1 );
	
		if( dot < 0 ) m_SaveFileName += ".xml";
		else if( type.lower() != "xml" ) m_SaveFileName = m_SaveFileName.replace( dot+1, type.length(), "xml" );
	
		fileSave();
	}
}


void Alchemist::filterSelected()
{
	QString include = "";
	
	if( m_tableDisplay->numSelections() != 1 )
	{
		QMessageBox::information( NULL, "Error", "Only one word or one part of one word can be filtered.", "OK" );
		return;
	}
	
	QTableSelection selection = m_tableDisplay->selection( 0 );
	if( !selection.isActive() || selection.topRow() != selection.bottomRow() )
	{
		QMessageBox::information( NULL, "Error", "Only one word or one part of one word can be filtered.", "OK" );
		return;
	}
	for( int i = selection.leftCol(); i <= selection.rightCol(); i++ )
	{
		if( m_leftToRight->isOn() )
			include.append( m_tableDisplay->text( selection.topRow() , i ) );
		else
			include.prepend( m_tableDisplay->text( selection.topRow(), i ) );
	} 
	
	m_includeLineEdit->setText( include );
	m_excludeLineEdit->setText( "" );
	
	showFiltered();
}


QDomDocument Alchemist::getDocInfo()
{
	if( !m_DocInfo.hasChildNodes() )
	{
		m_DocInfo = QDomDocument();
		
		QDomElement doc = m_DocInfo.createElement( "documentinfo" );
		
		QDomElement creators = m_DocInfo.createElement( "creators" );
		doc.appendChild( creators );
		
		QDomElement affiliation = m_DocInfo.createElement( "affiliation" );
		doc.appendChild( affiliation );
		
		QDomElement language = m_DocInfo.createElement( "language" );
		doc.appendChild( language );
		
		QDomElement remarks = m_DocInfo.createElement( "remarks" );
		doc.appendChild( remarks );
		
		m_DocInfo.appendChild( doc );
	}
	
	return m_DocInfo;
}


int Alchemist::getNextColorIndex()
{
	int index = m_ColorIndex++;
	if( m_ColorIndex >= NUMBER_COLOR_SETS ) m_ColorIndex = 0;
	
	return index;
}


void Alchemist::helpAbout()
{
  HelpAboutDialog *helpDlg = new HelpAboutDialog( this );
  if( helpDlg->exec() == QDialog::Accepted )
  {
    // Do nothing
  }
  else
  {
    // Do nothing
  }
  delete helpDlg;
}


// Called whenever the window is moved, includes maximizing,
// normalizing, opening and closing the window
void Alchemist::moveEvent( QMoveEvent *move )
{
  int x, y;
  int x_max = QApplication::desktop()->width() - ( width() + 10 );
  int y_max = QApplication::desktop()->height() - ( height() + 30 );
  x = move->pos().x();
  if( x < 10 ) x = 10;
  if( x > x_max ) x = x_max;
  y = move->pos().y();
  if( y < 30 ) y = 30;
  if( y > y_max ) y = y_max;

  m_Settings.writeEntry( "/UChicago/Alchemist/Geometry/X_Pos", x );
  m_Settings.writeEntry( "/UChicago/Alchemist/Geometry/Y_Pos", y );

  // If old position and new position are different, update old position.
  if( move->pos().x() != move->oldPos().x() || move->pos().y() != move->oldPos().y() )
  {
    x = move->oldPos().x();
    if( x < 10 ) x = 10;
    if( x > x_max ) x = x_max;
    y = move->oldPos().y();
    if( y < 30 ) y = 30;
    if( y > y_max ) y = y_max;

    m_Settings.writeEntry( "/UChicago/Alchemist/Geometry/X_Pos_Old", x );
    m_Settings.writeEntry( "/UChicago/Alchemist/Geometry/Y_Pos_Old", y );
  }
}


void Alchemist::newAffix()
{

	if( m_WordCollection == NULL )
	{
		QMessageBox::information( NULL, "Error", "Please read in a file first.", "OK" );
		return;
	}
	
	 m_WordCollection ->NewAffix(m_tableDisplay);
	 
	 m_projectDirty = TRUE; 

}


void Alchemist::newRoot()
{

	if( m_WordCollection == NULL )
	{
		QMessageBox::information( NULL, "Error", "Please read in a file first.", "OK" );
		return;
	}
	
	 m_WordCollection ->NewRoot(m_tableDisplay); 
	 
	 m_projectDirty = TRUE;

}


void Alchemist::pageChange()
{
	m_previousPageButton->setEnabled( TRUE );
	m_nextPageButton->setEnabled( TRUE );
	if( m_PageNumber <= 0 )
	{
		m_PageNumber = 0;
		m_previousPageButton->setEnabled( FALSE );
	}
	if( m_PageNumber >= m_WordCollection->GetCount()/m_EntriesPerPage )
	{
		m_PageNumber = m_WordCollection->GetCount()/m_EntriesPerPage;
		m_nextPageButton->setEnabled( FALSE );
	}
	
	m_WordCollection->DisplayOnTable( m_tableDisplay, m_WordCollection ->GetCurrentDisplayType() ); 
}


void Alchemist::remarksChanged()
{}


void Alchemist::resetCountDown()
{
  m_ProgressBar->reset();
}


// Called whenever the window is resized, includes maximizing,
// normalizing, opening and closing the window
void Alchemist::resizeEvent( QResizeEvent *resize )
{
  m_Settings.writeEntry( "/UChicago/Alchemist/Geometry/Width", resize->size().width() );
  m_Settings.writeEntry( "/UChicago/Alchemist/Geometry/Height", resize->size().height() );

  // If old size and new size are different, update old size
  if( resize->size().width() != resize->oldSize().width() )
    m_Settings.writeEntry( "/UChicago/Alchemist/Geometry/Width_Old", resize->oldSize().width() );
  if( resize->size().width() != resize->oldSize().width() )
    m_Settings.writeEntry( "/UChicago/Alchemist/Geometry/Height_Old", resize->oldSize().height() );
}


void Alchemist::setScoring( int Score )
{
	//QMessageBox::information( NULL, "Number",	QString("%1").arg(Score),"OK" );
	m_Score = Score; 
}


void Alchemist::setSorting( int SortType)
{
// YuHu Added Begin
	
	//QMessageBox::information( NULL, "Number",	QString("%1").arg(SortType),"OK" );
	m_SortType = SortType; 
// YuHu Added End
}


void Alchemist::setStatusBar1(QString string)
{
  if( getStatusBar1() == string ) return;
  else
  {
    m_StatusBar1->setText(string);
    m_StatusBar1->repaint();
  }
}


void Alchemist::setStatusBar2(QString string)
{
  if( getStatusBar2() == string ) return;
  else
  {
    m_StatusBar2->setText(string);
    m_StatusBar2->repaint();
  }
}


void Alchemist::setWordFilter( int FilterType )
{
	m_WordFilterType = FilterType;
}


void Alchemist::showFiltered()
{
	if( m_WordCollection == NULL )
	{
		QMessageBox::information( NULL, "Error", "Please read in a file first.", "OK" );
		return;
	}
	
	QString IncludeString, ExcludeString;
	
	IncludeString = m_includeLineEdit->text();
	ExcludeString = m_excludeLineEdit->text();
	
	
	
	m_WordCollection ->FindAnalysedOrUnAnalysedWords(m_WordFilterType); 
		
	
	
	if( (IncludeString.length() == 0) && (ExcludeString.length() ==0 ))
	{
		m_PageNumber = 0; 
		m_WordCollection->FilterWords( m_tableDisplay, IncludeString, ExcludeString, true, 0 );
		m_pageComboBox ->clear();
	    //QMessageBox::information( NULL, "debug", QString("%1").arg(m_WordCollection->GetCount()), "OK" );
		for( int pages = 0; pages < ceil( (double)m_WordCollection->GetCount()/(double)m_EntriesPerPage ); pages++ )
		{
			m_pageComboBox->insertItem( QString("%1").arg( pages ) );
		}
		m_pageComboBox ->setCurrentItem(m_PageNumber);
		return;
		
	}
	
	// QMessageBox::information( NULL, "Include/Exclude, ExcludeString, "OK" );
	
	if( IncludeString.length() == 0 )
	{
		QMessageBox::information( NULL, "Attention", "Please enter an string to be included.", "OK" );
		return;
	}
	
	m_PageNumber = 0; 
	m_WordCollection->FilterWords( m_tableDisplay, IncludeString, ExcludeString, true, 1 );
	
	m_pageComboBox ->clear(); 
	for( int pages = 0; pages < ceil( (double)m_WordCollection->GetCount()/(double)m_EntriesPerPage ); pages++ )
	{
 		m_pageComboBox->insertItem( QString("%1").arg( pages ) );
	}
	m_pageComboBox ->setCurrentItem(m_PageNumber);
	
}


void Alchemist::sort()
{	
	if( m_WordCollection == NULL )
	{
		QMessageBox::information( NULL, "Error", "Please read in a file first.", "OK" );
		return;
	}
	m_PageNumber = 0; 
	m_WordCollection->DisplayOnTable( m_tableDisplay, m_SortType ); 
	
	m_pageComboBox ->clear(); 
	for( int pages = 0; pages < ceil( (double)m_WordCollection->GetCount()/(double)m_EntriesPerPage ); pages++ )
	{
		m_pageComboBox->insertItem( QString("%1").arg( pages ) );
	}
	m_pageComboBox ->setCurrentItem(m_PageNumber);
}


void Alchemist::tableContextMenu()
{	
	bool single = FALSE;
	if( m_tableDisplay->numSelections() == 1 && 
	    m_tableDisplay->selection(0).topRow() == m_tableDisplay->selection(0).bottomRow() )
	{
		single = TRUE;
	}
	
	QPopupMenu* ContextMenu = new QPopupMenu( this, "table context menu" ); 

	ContextMenu->insertItem( "New Root\tCtrl+R", this, SLOT( newRoot() ), 0, 0 );
	ContextMenu->insertItem( "New Affix\tCtrl+A", this, SLOT( newAffix() ), 0, 1 );
	ContextMenu->insertItem( "Clear Cuts\tCtrl+C", this, SLOT( clearCuts() ), 0, 2 );
	if( single )
	{
		ContextMenu->insertItem( "Duplicate Word", this, SLOT( duplicateWord() ), 0, 4 );
		ContextMenu->insertSeparator();
		ContextMenu->insertItem( "Filter Selected", this, SLOT( filterSelected() ), 0, 5 );
	}
	ContextMenu->insertSeparator();
	ContextMenu->insertItem( "Refresh\tF5", this, SLOT( editRefresh() ), 0, 6 );
	ContextMenu->insertItem( "Delete\tDel", this, SLOT( editDelete() ), 0, 7 );
	
	QPopupMenu* score = new QPopupMenu( ContextMenu, "score menu" );
	score->insertItem( "Not scored", this, SLOT( scoreNot() ), 0, 0 );
	score->insertItem( "Certain", this, SLOT( scoreCertain() ), 0, 1 );
	score->insertItem( "Somewhat certain", this, SLOT( scoreSomewhat() ), 0, 2 );
	score->insertItem( "Uncertain", this, SLOT( scoreUn() ), 0, 3 );
	
	score->setItemChecked( m_scoringComboBox->currentItem(), TRUE );
	
	ContextMenu->insertSeparator();
	ContextMenu->insertItem( "Set score...", score, 8 );
	
	ContextMenu->exec( QCursor::pos() );
	
	score->clear();
	delete score;
	
	ContextMenu->clear();
}


void Alchemist::tableSelectionChanged()
{}


 

