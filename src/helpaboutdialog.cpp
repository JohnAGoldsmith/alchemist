#include "helpaboutdialog.h"
#include "general.h"



HelpAboutDialog::HelpAboutDialog( QWidget* parent, const char* name, bool modal, WFlags fl )
    : HelpAboutDialogBase( parent, name, modal, fl )
{
	m_versionTextLabel->setText( "<h1><font face=\"Arial\">Alchemist " + QString(AU_VERSION) + "</font></h1>" ); 
	setCaption( "About Alchemist " + QString(AU_VERSION) );
}

