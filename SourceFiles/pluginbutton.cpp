#include "pluginbutton.h"

#include <qdebug.h>

void PluginButton::SetButton(Button* button, bool auto_connect)
{
	this->_button_function = button->button_function;
	this->setObjectName(button->button_name);
	this->setText(button->button_text);
	this->auto_connect = auto_connect;
	this->_widget_group = button->widget_group;
	this->setStyleSheet(
		"PluginButton{color: rgb(255, 255, 255);"
		"background - color: rgb(20, 20, 20);"
		"border - radius:5px;"
		"border:1px solid grey;"
		"padding: 3px;"
		"font - size: 9px;"
		"text - align: center;}"
		"PluginButton:hover{background - color: rgb(50, 50, 50);}"
		"PluginButton:pressed, PluginButton : checked{background - color: rgb(0, 0, 0);}"
		);
	if (auto_connect == true)
		connect(this, SIGNAL(clicked()), this, SLOT(OnThisClicked()));
}

Button_Function PluginButton::GetFunction()
{
	return this->_button_function;
}

void PluginButton::OnThisClicked()
{
	if (auto_connect == false) return;
	qDebug() << "clicked";
	if (this->_button_function != nullptr)
	{
		qDebug()<<this->_button_function();
	}
}
