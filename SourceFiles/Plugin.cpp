#include "Plugin.h"

Plugin::Plugin()
{
	this->_name = "defult name";
	this->_plugin_interface = nullptr;
}

Plugin::~Plugin()
{
	delete _plugin_interface;
	_plugin_interface = nullptr;

	for each (PluginButton *var in _buttons)
	{
		delete var;
		var = nullptr;
	}
	_buttons.clear();
	for each (PluginLineEdit *var in _lineedits)
	{
		delete var;
		var = nullptr;
	}
	_lineedits.clear();
	for each (PluginComboBox *var in _comboboxs)
	{
		delete var;
		var = nullptr;
	}
	_comboboxs.clear();
}
