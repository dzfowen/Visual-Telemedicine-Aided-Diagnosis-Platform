#include "VtkReader.h"
#include "Service.h"
#include "QVTKWidget.h"



extern Service* current_service;

VtkReader::VtkReader()
{
}


VtkReader::~VtkReader()
{
}

void VtkReader::Read_Display(QStringList vtkFileNameList, Ui::ServerClass ui)
{


	vector<vtkActor*> vtkActors;

	for (int i = 0; i < vtkFileNameList.size(); i++)
	{
		/*
		Upadte by WangYi	2015-12-03
		different colors for images
		*/

		vtkDataSetReader* vtkReader = vtkDataSetReader::New();
		vtkReader->SetFileName(vtkFileNameList[i].toStdString().c_str());
		vtkReader->Update();
		vtkDataSetMapper* vtkMapper = vtkDataSetMapper::New();
		vtkMapper->SetInputConnection(vtkReader->GetOutputPort());
		vtkMapper->ScalarVisibilityOff();	//For change color

		double* doubles = vtkReader->GetOutput()->GetScalarRange();
		vtkMapper->SetScalarRange(doubles[0], doubles[1]);

		vtkActor* actor = vtkActor::New();
		actor->SetMapper(vtkMapper);
		

		switch (i % 5){
		case 0:
			actor->GetProperty()->SetColor(1, 0, 0);
			actor->GetProperty()->SetOpacity(0.3);
			break;
		case 1:
			actor->GetProperty()->SetColor(1, 0, 1);
			actor->GetProperty()->SetOpacity(1);
			break;
		case 2:
			actor->GetProperty()->SetColor(1, 1, 0);
			actor->GetProperty()->SetOpacity(0.3);
			break;
		case 3:
			actor->GetProperty()->SetColor(0.5, 0.5, 1);
			actor->GetProperty()->SetOpacity(0.7);
			break;
		case 4:
			actor->GetProperty()->SetColor(0, 1, 0);
			break;
		}

		vtkActors.push_back(actor);
	}

	/*
	2016/11/21 3d display
	*/
	vtkSmartPointer<vtkRenderer> aRenderer = vtkRenderer::New();
	for (int i = 0; i < vtkActors.size(); i++)
	{
		aRenderer->AddActor(vtkActors[i]);
	}

	/*vtkSmartPointer<vtkRenderer> bRenderer = vtkRenderer::New();
	for (int i = 0; i < vtkActors.size(); i++)
	{
		bRenderer->AddActor(vtkActors[i]);
	}*/

	QVTKWidget* widget = current_service->Widget();
	vtkRenderWindow* renderWindow = widget->GetRenderWindow();


	/*vtkSmartPointer<vtkCamera> aCamera = vtkSmartPointer<vtkCamera>::New();
	aCamera->ComputeViewPlaneNormal();
	aCamera->Azimuth(0.0);
	aCamera->Elevation(0.0);
	aRenderer->SetActiveCamera(aCamera);
	aRenderer->ResetCamera();
	aRenderer->SetViewport(0.0, 0.5, 1.0, 1.0);
	aRenderer->ResetCameraClippingRange();
	renderWindow->AddRenderer(aRenderer);

	vtkSmartPointer<vtkCamera> bCamera = vtkSmartPointer<vtkCamera>::New();
	bCamera = aCamera;
	double* position = aCamera->GetPosition();
	bCamera->SetPosition(position[0], position[1], position[2] - 2);

	bRenderer->SetActiveCamera(bCamera);
	bRenderer->ResetCamera();
	bRenderer->SetViewport(0.0, 0.0, 1.0, 0.5);
	bRenderer->ResetCameraClippingRange();
	renderWindow->AddRenderer(bRenderer);*/





	//vtkSmartPointer<vtkRenderWindow> renderWindow3D = vtkSmartPointer<vtkRenderWindow>::New();
	////renderWindow3D->AddRenderer(renderer);


	//renderWindow3D->StereoRenderOn();
	////renderWindow3D->StereoCapableWindowOn();
	//renderWindow3D->SetStereoTypeToRedBlue();
	////renderWindow3D->SetStereoTypeToInterlaced();
	//renderWindow3D->StereoUpdate();


	//renderWindow3D->AddRenderer(renderer);

	renderWindow->AddRenderer(aRenderer);
	widget->SetRenderWindow(renderWindow);
	//widget->SetRenderWindow(renderWindow3D);
	widget->update();

}

