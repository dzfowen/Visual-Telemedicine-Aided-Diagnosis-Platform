#pragma once

using namespace std;
#include <string>
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkDICOMImageReader.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkCamera.h"
#include "vtkProperty.h"
#include "vtkPolyDataNormals.h"
#include "vtkContourFilter.h"
#include "server.h"
#include "vtkImagePlaneWidget.h"
#include <vtkResliceCursorWidget.h>
#include "vtkResliceCursor.h"
#include "vtkResliceCursorThickLineRepresentation.h"
#include <vtkImageData.h>
#include <vtkDataSetReader.h>
#include <vtkDataSetMapper.h>
#include <vtkInteractorStyleRubberBandPick.h>
class VtkReader
{
public:
	VtkReader();
	~VtkReader();

	void Read_Display(QStringList vtkFileNameList, Ui::ServerClass ui);
};

