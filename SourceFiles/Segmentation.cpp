#include "Segmentation.h"
#include <QDebug>



#include "vtkAVIWriter.h"
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyDataReader.h> 
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkOutlineFilter.h>
#include <vtkCamera.h>
#include <vtkProperty.h>
#include <vtkPolyDataNormals.h>
#include <vtkContourFilter.h>
#include <vtkSmartPointer.h>
#include <vtkMetaImageReader.h>
#include <vtkDecimatePro.h>
#include <vtkSmoothPolyDataFilter.h> 
#include <vtkTriangleFilter.h> 
#include <vtkImageGaussianSmooth.h> 
#include <vtkPolyDataWriter.h>
#include <vtkImageFlip.h>
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkBoxWidget.h"
#include "vtkCommand.h"
#include "vtkTransform.h"
#include <vtkTextProperty.h>
#include <vtkTextActor.h>
#include <vtkTextSource.h>
#include <vtkExtractVOI.h>
#include <vtkAssembly.h>
#include <vtkVectorText.h>
#include <vtkLinearExtrusionFilter.h>
#include <vtkWindowToImageFilter.h>


#include <vtkVolumeRayCastCompositeFunction.h>
#include <vtkVolume.h>
#include <vtkVolumeProperty.h>
#include <vtkColorTransferFunction.h>	
#include <vtkVolumeRayCastMapper.h>
#include <vtkStripper.h>
#include <vtkLODActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkPointLocator.h>
#include <vtkTriangleFilter.h> 
#include <vtkQuadricClustering.h> 
#include <vtkDataSetWriter.h>

#include "graph.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <sstream>
#include <direct.h>
#include <io.h>
#include <string>   // for strings
#include <iomanip>  // for controlling float print precision
#include <stdio.h>


Segmentation::Segmentation()
{
}

Segmentation::~Segmentation()
{
}


