#include "pluginlineedit.h"

#include <qdebug.h>

void PluginLineEdit::SetLineEdit(LineEdit *lineedit, bool auto_connect)
{
	this->setObjectName(lineedit->lineedit_name);
	this->_lineedit_function = lineedit->lineedit_function;
	this->setPlaceholderText(lineedit->lineedit_name);
	this->auto_connect = auto_connect;
	this->_widget_group = lineedit->widget_group;
	this->setStyleSheet(
		"PluginLineEdit{color: rgb(255, 255, 255);"
		"background - color: rgb(20, 20, 20);"
		"border - radius:5px;"
		"border:1px solid grey;"
		"padding: 3px;"
		"font - size: 9px;"
		"text - align: center;}"
		"PluginLineEdit:hover{background - color: rgb(50, 50, 50);}"
		"PluginLineEdit:pressed, PluginButton : checked{background - color: rgb(0, 0, 0);}"
		);
	if (auto_connect)
		connect(this, SIGNAL(textEdited(QString)), this, SLOT(OnThisTextChanged()));
}

LineEdit_Function PluginLineEdit::GetFunction()
{
	return this->_lineedit_function;
}

void PluginLineEdit::OnThisTextChanged()
{
	qDebug()<<this->_lineedit_function((char*)this->text().toStdString().c_str());
}