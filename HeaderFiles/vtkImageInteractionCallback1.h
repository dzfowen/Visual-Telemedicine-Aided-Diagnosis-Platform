#include <vtkVersion.h>
#include <vtkAssemblyPath.h>
#include <vtkCell.h>
#include <vtkCommand.h>
#include <vtkCornerAnnotation.h>
#include <vtkDataArray.h>
#include <vtkImageActor.h>
#include <vtkImageData.h>
#include <vtkImageViewer2.h>
#include <vtkInteractorStyleImage.h>
#include <vtkJPEGReader.h>
#include <vtkPointData.h>
#include <vtkPropPicker.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkTextProperty.h>

// The mouse motion callback, to pick the image and recover pixel values
class vtkImageInteractionCallback1 : public vtkCommand
{
public:

	static vtkImageInteractionCallback1 *New()
	{
		return new vtkImageInteractionCallback1;
	}

	vtkImageInteractionCallback1()
	{
		this->Viewer = 0;
		this->Picker = 0;
		//this->Annotation = 0;
		this->PointData = vtkPointData::New();
	}

	~vtkImageInteractionCallback1()
	{
		this->Viewer = 0;
		this->Picker = 0;
		//this->Annotation = 0;
		this->PointData->Delete();
	}

	void SetPicker(vtkPropPicker *picker)
	{
		this->Picker = picker;
	}

	//void SetAnnotation(vtkCornerAnnotation *annotation)
	//{
	//	this->Annotation = annotation;
	//}

	void SetViewer(vtkImageViewer2 *viewer)
	{
		this->Viewer = viewer;
	}

	virtual void Execute(vtkObject *, unsigned long vtkNotUsed(event), void *)
	{
		//this->Viewer;
		vtkRenderWindowInteractor *interactor = this->Viewer->GetRenderWindow()->GetInteractor();
		vtkRenderer* renderer = this->Viewer->GetRenderer();
		vtkImageActor* actor = this->Viewer->GetImageActor();
		vtkImageData* image = this->Viewer->GetInput();
		vtkInteractorStyle *style = vtkInteractorStyle::SafeDownCast(
			 interactor->GetInteractorStyle());

#if VTK_MAJOR_VERSION <= 5
		image->Update();
#endif

		// Pick at the mouse location provided by the interactor
		this->Picker->Pick(interactor->GetEventPosition()[0],
			interactor->GetEventPosition()[1],
			0.0, interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer());

		// There could be other props assigned to this picker, so 
		// make sure we picked the image actor
		vtkAssemblyPath* path = this->Picker->GetPath();
		bool validPick = false;

		if (path)
		{
			vtkCollectionSimpleIterator sit;
			path->InitTraversal(sit);
			vtkAssemblyNode *node;
			for (int i = 0; i < path->GetNumberOfItems() && !validPick; ++i)
			{
				node = path->GetNextNode(sit);
				if (actor == vtkImageActor::SafeDownCast(node->GetViewProp()))
				{
					validPick = true;
				}
			}
		}

		if (!validPick)
		{
			this->Annotation->SetText(0, "Off Image");
			interactor->Render();
			// Pass the event further on
			style->OnMouseMove();
			return;
		}

		// Get the world coordinates of the pick
		double pos[3];
		this->Picker->GetPickPosition(pos);
		// Fixes some numerical problems with the picking
		double *bounds = actor->GetDisplayBounds();
		int axis = this->Viewer->GetSliceOrientation();
		pos[axis] = bounds[2 * axis];

		vtkPointData* pd = image->GetPointData();
		if (!pd)
		{
			return;
		}

		this->PointData->InterpolateAllocate(pd, 1, 1);

		// Use tolerance as a function of size of source data
		double tol2 = image->GetLength();
		tol2 = tol2 ? tol2*tol2 / 1000.0 : 0.001;

		// Find the cell that contains pos
		int subId;
		double pcoords[3], weights[8];
		vtkCell* cell = image->FindAndGetCell(
			pos, NULL, -1, tol2, subId, pcoords, weights);
		if (cell)
		{
			// Interpolate the point data
			this->PointData->InterpolatePoint(pd, 0, cell->PointIds, weights);
			int components =
				this->PointData->GetScalars()->GetNumberOfComponents();
			double* tuple = this->PointData->GetScalars()->GetTuple(0);
			
			double* origin = image->GetOrigin();
			double* spacing = image->GetSpacing();

			int idx0 = int((pos[0]-origin[0])/spacing[0]);
			int idx1 = int((pos[1] - origin[1]) / spacing[1]);
			int idx2 = int((pos[2] - origin[2]) / spacing[2]);

			//std::string message = "Location: ( ";
			//message += vtkVariant(idx0).ToString();
			//message += ", ";
			//message += vtkVariant(idx1).ToString();
			//message += ", ";
			//message += vtkVariant(idx2).ToString();
			//message += " )\nValue: ( ";

			//for (int c = 0; c < components; ++c)
			//{
			//	message += vtkVariant(tuple[c]).ToString();
			//	if (c != components - 1)
			//	{
			//		message += ", ";
			//	}
			//}
			//message += " )";
			//this->Annotation->SetText(0, message.c_str());
			interactor->Render();
			style->OnMouseMove();
		}
	}

private:

	// Pointer to the viewer
	vtkImageViewer2 *Viewer;

	// Pointer to the picker
	vtkPropPicker *Picker;

	// Pointer to the annotation
	vtkCornerAnnotation *Annotation;

	// Interpolator
	vtkPointData* PointData;
};

