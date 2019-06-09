/*
By Yao Taihang	2015-11-19

This Object is used to write the mark line on the picture
by the mouse move event.
It must get the vtklineObject
*/
#ifndef VTKMYMARKCALLBACK_H
#define VTKMYMARKCALLBACK_H
#include "vtkCommand.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkPolygonalLineData.h"
#include "qdebug.h"

#include "vtkPolyDataMapper2D.h"
#include "vtkActor2D.h"
#include "vtkProperty2D.h"

#define MARKFLAGFALSE 0
#define MARKFLAGTRUE 1


class vtkMyMarkCallback :public vtkCommand
{
public:
	static vtkMyMarkCallback* New()
	{
		return new vtkMyMarkCallback;
	}
	////YY////
	Ui::ServerClass currentui;

	void SetAllPolygonalColor(vector<int> Color)
	{
		allPolygonalColor = Color;
	}
	void SetAllPolygonalWidth(vector<int> Width)
	{
		allPolygonalWidth = Width;
	}
	vector<int> GetAllPolygonalColor()
	{
		return allPolygonalColor;
	}

	vector<int> GetAllPolygonalWidth()
	{
		return allPolygonalWidth;
	}
	void SetColor(int n)
	{
		color = n;
	}

	void SetWidth(int n)
	{
		width = n;
	}
	////2016.12.23////


	vtkMyMarkCallback()
	{
		//Init LineProperty for different mark
		
		for (int i = 0; i < 4; i++)
		{
			this->allLineProperty[i] = vtkSmartPointer<vtkProperty2D>::New();
			this->allLineProperty[i]->SetLineWidth(3);
			//this->allLineProperty[i]->SetColor(1, 0, 0);
			switch (i)
			{
			case 0:this->allLineProperty[i]->SetColor(1, 0, 0); break;
			case 1:this->allLineProperty[i]->SetColor(0, 1, 0); break;
			case 2:this->allLineProperty[i]->SetColor(0, 0, 1); break;
			case 3:this->allLineProperty[i]->SetColor(1, 0, 0); break;
			default:break;
			}
		}
		
		/*
		this->allLineProperty[0] = vtkSmartPointer<vtkProperty2D>::New();
		this->allLineProperty[0]->SetLineWidth(3);
		this->allLineProperty[0]->SetColor(1, 0, 0);
		this->allLineProperty[1] = vtkSmartPointer<vtkProperty2D>::New();
		this->allLineProperty[1]->SetLineWidth(3);
		this->allLineProperty[1] = vtkSmartPointer<vtkProperty2D>::New();
		this->allLineProperty[2]->SetLineWidth(3);
		this->allLineProperty[2]->SetColor(1, 0, 0);
		this->allLineProperty[2] = vtkSmartPointer<vtkProperty2D>::New();
		this->allLineProperty[3]->SetLineWidth(3);
		this->allLineProperty[3]->SetColor(1, 0, 0);
		this->allLineProperty[3]->SetColor(1, 0, 0);
		*/
	}


	void SetInteractor(vtkRenderWindowInteractor *interactor)
	{
		this->Interactor = interactor;
	}

	vtkRenderWindowInteractor * GetInteractor()
	{
		return this->Interactor;
	}

	void SetAllPolygonalLines(vector<vtkSmartPointer<vtkPolygonalLineData>> allPolygonalLines)
	{
		this->allPolygonalLines = allPolygonalLines;
	}

	vector<vtkSmartPointer<vtkPolygonalLineData>> GetAllPolygonalLines()
	{
		return this->allPolygonalLines;
	}

	void SetRenderer(vtkRenderer * renderer)
	{
		this->renderer = renderer;
	}

	vtkRenderer * GetRenderer()
	{
		return this->renderer;
	}

	void SetCurrentWidget(QVTKWidget * qvtkWidget)
	{
		this->currentWidget = qvtkWidget;
	}

	//Reset the color for the mark line
	void ResetLineColor(int index, double r, double g, double b)
	{
		this->allLineProperty[index]->SetColor(r, g, b);
	}
	//Reset the width for the mark line
	void ResetLineWidth(int index, int size)
	{
		this->allLineProperty[index]->SetLineWidth(size);
	}
	//Reset the flag for the mark line
	void ResetFlagForMarkLine()
	{
		this->MarkFlagState = this->MarkFlagState == 0 ? 1 : 0;
	}
	//Reset the MarkLineStyleIndex for the mark line
	void ResetMarkLineStyleIndex(int n)
	{
		this->MarkLineStyleIndex = n;
	}
	//Clear all lines
	void ClearAllLines()
	{
		int LinesSizeNow = this->allPolygonalLines.size();

		for (int i = this->allPolygonalLines.size() - 1; i >= 0; i--)
		{
			//Remove actor
			this->GetRenderer()->RemoveActor2D(allActors[i + NumberForActor]);
			//Remove line
			this->allPolygonalLines[i]->Delete();
			this->allPolygonalLines.pop_back();
		}
		NumberForActor += LinesSizeNow;
		////YY////
		allPolygonalColor.swap(vector<int>());
		allPolygonalWidth.swap(vector<int>());
		////2016.12.23////

		this->currentWidget->update();
	}
	//Set the mark line flag
	void SetMarkFlag(int Flag)
	{
		this->MarkFlag = Flag;
	}

	virtual void Execute(vtkObject* caller, unsigned long event, void* callData)
	{
		if (this->MarkFlagState == 1)
		{
			vtkRenderWindowInteractor *interactor = this->GetInteractor();
			int currPos[2];
			interactor->GetEventPosition(currPos);
			if (event == vtkCommand::LeftButtonPressEvent)
			{
				//When first click happend, create a new polygonalLine
				if (this->MarkFlag == 0)
				{
					this->singlePolygonalLine = vtkSmartPointer<vtkPolygonalLineData>::New();
					this->singlePolygonalLine->InsertNewPointIntoPolygonallLine(currPos[0], currPos[1], 0);

					vtkSmartPointer<vtkPolyDataMapper2D> polyDataMapper = vtkSmartPointer<vtkPolyDataMapper2D>::New();
					polyDataMapper->SetInputData(singlePolygonalLine);

					vtkSmartPointer<vtkActor2D> polyDataActor = vtkSmartPointer<vtkActor2D>::New();
					polyDataActor->SetMapper(polyDataMapper);
					polyDataActor->SetProperty(this->allLineProperty[MarkLineStyleIndex]);
					this->GetRenderer()->AddActor2D(polyDataActor);
					this->allActors.push_back(polyDataActor);
				}
				//When second click happend, pushback the line to the line array
				else
				{
					this->allPolygonalLines.push_back(this->singlePolygonalLine);
					////YY////
					allPolygonalColor.push_back(color);
					allPolygonalWidth.push_back(width);
					////2016.12.23////
				}
				//Change the mark flag between the begin and end
				this->MarkFlag = this->MarkFlag == 0 ? 1 : 0;
				//This sentences is very important for refresh Ui!!!!!!!!!!!!!
				this->currentWidget->update();
			}
			else if (event == vtkCommand::MouseMoveEvent)
			{
				//When the mark flag is 1 , begin to write line
				if (this->MarkFlag == 1)
				{
					countFlag++;
					if (countFlag == 6)
					{
						this->singlePolygonalLine->InsertNewPointIntoPolygonallLine(currPos[0], currPos[1], 0);
						this->currentWidget->update();
						countFlag = 0;
					}

				}
			}
			else
			{
				qDebug("Some thing eles happend");
			}
		}
	}

	//When server be controled ,set mark line use x,y envent message
	void SetMarkLineUserEventMessage(int X, int Y, int event,int colorType)
	{
		if (this->MarkFlagState == 1)
		{
			int currPos[2];
			currPos[0] = X;
			currPos[1] = Y;
			int colornum = colorType;
			qDebug() << "colorNumber is" << colornum;
			if (event == vtkCommand::LeftButtonPressEvent)
			{
				//When first click happend, create a new polygonalLine
				this->singlePolygonalLine = vtkSmartPointer<vtkPolygonalLineData>::New();
				this->singlePolygonalLine->InsertNewPointIntoPolygonallLine(currPos[0], currPos[1], 0);

				vtkSmartPointer<vtkPolyDataMapper2D> polyDataMapper = vtkSmartPointer<vtkPolyDataMapper2D>::New();
				polyDataMapper->SetInputData(singlePolygonalLine);

				vtkSmartPointer<vtkActor2D> polyDataActor = vtkSmartPointer<vtkActor2D>::New();
				polyDataActor->SetMapper(polyDataMapper);
				polyDataActor->SetProperty(this->allLineProperty[colornum]);
				this->GetRenderer()->AddActor2D(polyDataActor);
				this->allActors.push_back(polyDataActor);

				//Change the mark flag between the begin and end
				this->MarkFlag = 1;
				//This sentences is very important for refresh Ui!!!!!!!!!!!!!
				this->currentWidget->update();
			}
			else if (event == vtkCommand::MouseMoveEvent)
			{
				//When the mark flag is 1 , begin to write line
				if (this->MarkFlag == 1)
				{
					countFlag++;
					if (countFlag == 6)
					{
						this->singlePolygonalLine->InsertNewPointIntoPolygonallLine(currPos[0], currPos[1], 0);
						this->currentWidget->update();
						countFlag = 0;
					}
				}
			}
			else if (event == vtkCommand::LeftButtonReleaseEvent)
			{
				this->MarkFlag = 0;
				this->allPolygonalLines.push_back(this->singlePolygonalLine);
				////YY////
				allPolygonalColor.push_back(color);
				allPolygonalWidth.push_back(width);
				////2016.12.23////
			}
		}
	}

private:
	////YY////
	int color = 0;
	int width = 3;
	vector <int> allPolygonalColor;
	vector <int> allPolygonalWidth;
	////2016.12.23////
	int countFlag = 0;
	int MarkFlag = 0;
	int MarkFlagState = 0;
	int MarkLineStyleIndex = 0;
	//For solving the problem of clear,this number is used to remember the total count of actors for line
	int NumberForActor = 0;
	vector<vtkSmartPointer<vtkPolygonalLineData>> allPolygonalLines;
	vector<vtkSmartPointer<vtkActor2D>> allActors;
	vtkSmartPointer<vtkPolygonalLineData> singlePolygonalLine;
	vtkRenderWindowInteractor *Interactor;
	vtkRenderer * renderer;
	QVTKWidget * currentWidget;
	vtkSmartPointer<vtkProperty2D> allLineProperty[4];
};
#endif
