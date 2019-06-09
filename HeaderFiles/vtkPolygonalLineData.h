/*
By Yao Taihang	2015-11-20

This object is used to build a polygonal line with single points and lines
It can update when the new point add in.
It can be used to draw some not structed lines, for an excemple,you can use it
to build a mark line.
*/
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkLine.h>
#include <vtkCellArray.h>
#include <qdebug.h>


class vtkPolygonalLineData :public vtkPolyData
{
public:
	static vtkPolygonalLineData* New()
	{
		return new vtkPolygonalLineData();
	}

	vtkPolygonalLineData()
	{
		//Create the var to save the points and lines which can combine the polygonal line
		this->points = vtkSmartPointer<vtkPoints>::New();
		this->lines = vtkSmartPointer<vtkCellArray>::New();
		this->SetPoints(points);
		this->SetLines(lines);

	}

	vtkCellArray * GetLines()
	{
		return this->lines;
	}

	vtkPoints * GetPoints()
	{
		return this->points;
	}

	void InsertNewPointIntoPolygonallLine(double x, double y, double z)
	{
		
		//Insert the new point into array
		this->points->InsertNextPoint(x, y, z);
		//Build the new single ,and insert into line array
		if (this->points->GetNumberOfPoints() > 1)
		{
			vtkSmartPointer<vtkLine> singleLine = vtkSmartPointer<vtkLine>::New();
			singleLine->GetPointIds()->SetId(0, this->points->GetNumberOfPoints() - 2);
			singleLine->GetPointIds()->SetId(1, this->points->GetNumberOfPoints() - 1);
			this->lines->InsertNextCell(singleLine);
		}
	}


	~vtkPolygonalLineData()
	{
		this->points->Delete();
		this->lines->Delete();
		this->Delete();
	}

private:
	vtkSmartPointer<vtkPoints> points;
	vtkSmartPointer<vtkCellArray> lines;

};