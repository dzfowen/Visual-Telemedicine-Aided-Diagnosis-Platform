#include "plugincombobox.h"

#include <qdebug.h>

void PluginComboBox::SetComboBox(ComboBox *combobox, bool auto_connect)
{
	this->_combobox_function = combobox->combobox_function;
	this->setObjectName(combobox->combobox_name);
	this->addItem(combobox->combobox_select->combobox_select_text);
	ComboBox_Select *combobox_select_ptr = combobox->combobox_select;
	while (nullptr != combobox_select_ptr->next_select)
	{
		combobox_select_ptr = combobox_select_ptr->next_select;
		this->addItem(combobox_select_ptr->combobox_select_text);
	}
	this->setStyleSheet(
		"PluginComboBox{color: rgb(255, 255, 255);"
		"background - color: rgb(20, 20, 20);"
		"border - radius:5px;"
		"border:1px solid grey;"
		"padding: 3px;"
		"font - size: 9px;"
		"text - align: center;}"
		"PluginComboBox:hover{background - color: rgb(50, 50, 50);}"
		"PluginComboBox:pressed, PluginButton : checked{background - color: rgb(0, 0, 0);}"
		);
	this->auto_connect = auto_connect;
	this->_widget_group = combobox->widget_group;
	if (auto_connect = true)
		connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(OnThisSelectChanged()));
}

//auto call combobox function when select changed, but can not use return value
void PluginComboBox::OnThisSelectChanged()
{
	if (auto_connect = false) return;
	int index = this->currentIndex();
	int result = this->_combobox_function(index);
	qDebug() << objectName() << " changed to " << index;
	qDebug() << objectName() << " in plugin dll changed to " << result;
}