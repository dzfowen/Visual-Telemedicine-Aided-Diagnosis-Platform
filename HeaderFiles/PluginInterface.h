#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H

#include <Pluma\Pluma.hpp>

#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkImage.h"


#include <vector>
#include <string>

#define MAX_BUTTON_COUNT 10 //do not support over 10 buttons in one plugin
#define MAX_COMBOBOX_COUNT 10 //do not support over 10 comboboxs in one plugin
#define MAX_COMBOBOX_SELECT_COUNT 10 //do not support over 10 selects in one combobox
#define MAX_LINEEDIT_COUNT 10 //do not support over 10 selects in one combobox

typedef int(*Button_Function)();
typedef int(*ComboBox_Function)(int);
typedef int(*LineEdit_Function)(char*);
typedef int(*Custom_Function)();

typedef std::string(*GetNowOpenFile_Function)();
typedef std::string(*GetNowLabelFile_Function)();
typedef void(*SendNewOpenFileAndDisplay_Function)(std::string);

typedef struct FileAPI_struct
{
	GetNowOpenFile_Function GetNowOpenFile = nullptr;
	GetNowLabelFile_Function GetNowLabelFile = nullptr;
	SendNewOpenFileAndDisplay_Function SendNewOpenFileAndDisplay = nullptr;
} FileAPI;

typedef struct Button_struct
{
	char *button_name = "defult name";
	char *button_text = "defult text";
	Button_Function button_function = nullptr;
	Button_struct *next_button = nullptr;
	int widget_group = 0;
} Button;

typedef struct ComboBox_Select_struct
{
	char *combobox_select_text = "defult select";
	int combobox_select_index = 0;
	ComboBox_Select_struct *next_select = nullptr;
} ComboBox_Select;

typedef struct ComboBox_struct
{
	char *combobox_name = "defult name";
	ComboBox_Select_struct *combobox_select = nullptr;
	ComboBox_Function combobox_function = nullptr;
	ComboBox_struct *next_combobox = nullptr;
	int widget_group = 0;
} ComboBox;

typedef struct LineEdit_struct
{
	char *lineedit_name = "defult name";
	LineEdit_Function lineedit_function = nullptr;
	LineEdit_struct *next_lineedit = nullptr;
	int widget_group = 0;
} LineEdit;

class PluginInterface
{
public:
	virtual int GetButtons(Button *button) = 0;
	virtual int GetComboBoxs(ComboBox *combobox) = 0;
	virtual int GetLineEdits(LineEdit *lineedit) = 0;

	//not all plugin use imagedata exchange with server, if you do use it, overwrite these two function
	virtual int SendFileAPI(FileAPI *fileAPI);
};

PLUMA_PROVIDER_HEADER(PluginInterface);

#endif // PLUGININTERFACE_H
