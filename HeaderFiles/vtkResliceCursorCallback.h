#pragma once
#include "vtkCommand.h"
#include <vtkImagePlaneWidget.h>
#include <vtkResliceCursorWidget.h>
#include <vtkResliceCursorLineRepresentation.h>
#include <vtkRenderer.h>
#include <vtkResliceCursorActor.h>
#include <vtkResliceCursorPolyDataAlgorithm.h>
#include <vtkResliceCursor.h>
#include <vtkPlaneSource.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
class vtkResliceCursorCallback :
	public vtkCommand
{
public:
	vtkResliceCursorCallback();
	~vtkResliceCursorCallback();

	static vtkResliceCursorCallback *New();
	void Execute(vtkObject *caller, unsigned long eventId, void *callData);

	vtkImagePlaneWidget* IPW[3];
	vtkResliceCursorWidget* RCW[3];
};

