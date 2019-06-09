#include <vtkSmartPointer.h>
#include <vtkRendererCollection.h>
#include <vtkPointPicker.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <QDebug>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkActor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkObjectFactory.h>
#include "mhdReader.h"
#include "fstream"
#include "cstdio"




class MouseInteractorStylePP2 : public vtkInteractorStyleTrackballCamera
{
public:
	static MouseInteractorStylePP2* New();
	vtkTypeMacro(MouseInteractorStylePP2, vtkInteractorStyleTrackballCamera);

	//int picked[3];
	virtual void OnLeftButtonDown()
	{
		//std::cout << "Picking pixel: " << this->Interactor->GetEventPosition()[0] << " " << this->Interactor->GetEventPosition()[1] << std::endl;
		this->Interactor->GetPicker()->Pick(this->Interactor->GetEventPosition()[0],
			this->Interactor->GetEventPosition()[1],
			0,  // always zero.
			this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer());

		//qDebug("--%d--%d--%d", this->Interactor->GetEventPosition()[0], this->Interactor->GetEventPosition()[1], this->Interactor->GetEventPosition()[2]);
		qDebug("--%d--%d--", this->Interactor->GetEventPosition()[0], this->Interactor->GetEventPosition()[1]);

		double picked[3];
		this->Interactor->GetPicker()->GetPickPosition(picked);


		//this->Interactor->GetPicker()->GetPickPosition(picked);
		//std::cout << "Picked value: " << picked[0] << " " << picked[1] << " " << picked[2] << std::endl;
		/*picked[0] = (this->Interactor->GetEventPosition()[0] - 50) * 512 / 189;
		picked[1] = (this->Interactor->GetEventPosition()[1] - 50) * 512 / 189;
		picked[2] = (this->Interactor->GetEventPosition()[2] - 50) * 512 / 189;*/
		/*picked[0] = this->Interactor->GetEventPosition()[0] ;
		picked[1] = this->Interactor->GetEventPosition()[1] ;
		picked[2] = this->Interactor->GetEventPosition()[2] ;*/
		qDebug("Pick new position: **%f**%f**%f", picked[0], picked[1], picked[2]);
		ofstream outfile("C:\\workspace\\server_now\\Server\\Server\\modifyData\\newPoints.txt");
		/*for (int i = 0; i<3 ; i++)
		{

		outfile << picked[i];
		outfile.close();

		}*/
		char buffer[20];
		sprintf_s(buffer, "%f", picked[0]);
		string s0 = buffer;
		char buffer1[20];
		sprintf_s(buffer1, "%f", picked[1]);
		string s1 = buffer1;
		char buffer2[20];
		sprintf_s(buffer2, "%f", picked[2]);
		string s2 = buffer2;
		string s = s0 + "\n" + s1 + "\n" + s2;
		outfile << s;
		outfile.close();


		vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
		sphereSource->SetRadius(2);
		sphereSource->SetThetaResolution(4);
		sphereSource->SetPhiResolution(8);
		sphereSource->SetCenter(picked[0], picked[1], picked[2]);
		//sphereSource->Update();

		vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
		mapper->SetInputConnection(sphereSource->GetOutputPort());

		vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
		actor->SetMapper(mapper);

		//actor->SetPosition(picked);
		//actor->SetScale(0.05);
		actor->GetProperty()->SetColor(0.0, 1.0, 1.0);
		//vtkRenderer* ren = this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer();
		//vtkActor* ACTOR = ren->GetActors()->GetLastActor();
		//double* bounds = ACTOR->GetBounds();
		////double *bounds = this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->GetActors()->GetLastActor()->GetBounds();
		//int axis = 2;
		//picked[axis] = bounds[2 * axis];
		//qDebug("Pick position: --%f--%f--%f", picked[0], picked[1], picked[2]);
		this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(actor);
		this->Interactor->GetRenderWindow()->Render();

		//setPoint(picked,3);
		// Forward events
		vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
	}
	/*int setPoint(int arg[], int n)
	{
	int point[3];
	for (int i = 0; i < 3; i++)
	{
	point[i] = arg[i];
	}
	return point[3];
	}*/

};


vtkStandardNewMacro(MouseInteractorStylePP2);