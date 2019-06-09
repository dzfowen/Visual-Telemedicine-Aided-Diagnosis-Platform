#ifndef PLUGINLINEEDIT_H
#define PLUGINLINEEDIT_H

#include <QLineEdit>

#include "PluginInterface.h"

class PluginLineEdit : public QLineEdit
{
	Q_OBJECT

public:
	void SetLineEdit(LineEdit *lineedit, bool auto_connect = true);

	LineEdit_Function GetFunction();
	bool auto_connect;
	int _widget_group;

private:
	LineEdit_Function _lineedit_function;

private slots:
	void OnThisTextChanged();
	
};

#endif // PLUGINLINEEDIT_H
