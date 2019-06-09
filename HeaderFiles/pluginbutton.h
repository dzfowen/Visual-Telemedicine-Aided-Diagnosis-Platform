#ifndef PLUGINBUTTON_H
#define PLUGINBUTTON_H

#include <QPushButton>

#include "PluginInterface.h"

class PluginButton : public QPushButton
{
	Q_OBJECT

public:
	void SetButton(Button *button, bool auto_connect = true);

	//use to get function of the button, if you want deal with the function's return value, use this way
	Button_Function GetFunction();
	bool auto_connect;
	int _widget_group;

private:
	Button_Function _button_function;

private slots:
	//auto call button function when clicked, but can not use return value
	void OnThisClicked();
};

#endif // PLUGINBUTTON_H
