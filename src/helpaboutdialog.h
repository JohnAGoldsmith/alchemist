#ifndef HELPABOUTDIALOG_H
#define HELPABOUTDIALOG_H

#include "helpaboutdialogbase.h"

class HelpAboutDialog : public HelpAboutDialogBase
{
    Q_OBJECT

public:
    HelpAboutDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
};

#endif // HELPABOUTDIALOG_H
