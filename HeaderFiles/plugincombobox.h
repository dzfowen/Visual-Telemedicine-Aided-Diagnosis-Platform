#ifndef PLUGINCOMBOBOX_H
#define PLUGINCOMBOBOX_H

#include <QComboBox>

#include "PluginInterface.h"

class PluginComboBox : public QComboBox
{
	Q_OBJECT

public:
	void SetComboBox(ComboBox *combobox, bool auto_connect = true);
	
	//use to get function of the combobox, if you want deal with the function's return value, use this way
	ComboBox_Function GetFunction();
	bool auto_connect;
	int _widget_group;

private:
	ComboBox_Function _combobox_function;
	
private slots:
	//auto call combobox function when select changed, but can not use return value
	void OnThisSelectChanged();
};

#endif // PLUGINCOMBOBOX_H
