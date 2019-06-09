#ifndef PLUGIN_H
#define PLUGIN_H

#include "PluginInterface.h"
#include "pluginbutton.h"
#include "plugincombobox.h"
#include "pluginlineedit.h"
#include <QString>

class Plugin
{
public:
	Plugin();
	~Plugin();

	QString _name;
	PluginInterface *_plugin_interface;
	QVector<PluginButton*> _buttons;
	QVector<PluginLineEdit*> _lineedits;
	QVector<PluginComboBox*> _comboboxs;
};

#endif // PLUGIN_H
