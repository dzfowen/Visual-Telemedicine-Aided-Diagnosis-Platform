#pragma once
#include "vtkCommand.h"
#include <vtkTransform.h>
#include <vtkBoxWidget.h>
#include <vtkProp3D.h>

class vtkMyCallback :
	public vtkCommand
{
public:
	vtkMyCallback();
	~vtkMyCallback();
	static vtkMyCallback *New()
	{
		return new vtkMyCallback;
	}

	virtual void Execute(vtkObject *caller, unsigned long, void*)
	{
		vtkTransform *t = vtkTransform::New();
		vtkBoxWidget *widget = reinterpret_cast<vtkBoxWidget*>(caller);
		widget->GetTransform(t);
		widget->GetProp3D()->SetUserTransform(t);
		t->Delete();
	}
};

