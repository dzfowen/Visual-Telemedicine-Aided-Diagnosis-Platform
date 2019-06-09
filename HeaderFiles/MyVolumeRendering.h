#include <vtkSmartPointer.h>
#include <vtkMetaImageReader.h>
#include <vtkImageCast.h>
#include <vtkVolumeRayCastCompositeFunction.h>
#include <vtkVolumeProperty.h>
#include <vtkPiecewiseFunction.h>
#include <vtkColorTransferFunction.h>
#include <vtkVolume.h>
#include <vtkRenderer.h>
#include <vtkFixedPointVolumeRayCastMapper.h>
#include <vtkFixedPointVolumeRayCastCompositeHelper.h>
#include <qdebug.h>


class MyVolumeRendering
{
public:
	MyVolumeRendering();
	~MyVolumeRendering();

	void SetVtkMetaImageReader(vtkSmartPointer<vtkMetaImageReader> reader)
	{
		this->reader = reader;
	};

	vtkSmartPointer<vtkMetaImageReader> GetVtkMetaImageReader()
	{
		return this->reader;
	};

	vtkSmartPointer<vtkRenderer> GetVolumeRenderer()
	{
		return this->pRen;
	};

	vtkSmartPointer<vtkRenderer> StartVolumRenderingAndReturnRenderer()
	{
		vtkSmartPointer<vtkImageCast> cast = vtkSmartPointer<vtkImageCast>::New();
		cast->SetInputConnection(this->reader->GetOutputPort());
		cast->SetOutputScalarTypeToUnsignedShort();
		cast->Update();

		//vtkSmartPointer<vtkSMPTools> vtkSmptool = vtkSmartPointer<vtkSMPTools>::New();

		//vtkSmartPointer<vtkFixedPointVolumeRayCastCompositeHelper> rayCastFun_CastComposite = vtkSmartPointer<vtkVolumeRayCastCompositeFunction>::New();

		vtkSmartPointer<vtkFixedPointVolumeRayCastMapper> volumeMapper = vtkSmartPointer<vtkFixedPointVolumeRayCastMapper>::New();
		volumeMapper->SetInputConnection(cast->GetOutputPort());
		volumeMapper->SetSampleDistance(0.5f);

		vtkSmartPointer<vtkVolumeProperty> volumeProperty = vtkSmartPointer<vtkVolumeProperty>::New();
		volumeProperty->SetInterpolationTypeToLinear();
		volumeProperty->ShadeOn();
		//volumeProperty->SetAmbient(0.4);
		//volumeProperty->SetDiffuse(0.6);
		//volumeProperty->SetSpecular(0.2);
		volumeProperty->SetAmbient(.5);
		volumeProperty->SetDiffuse(1.0);
		volumeProperty->SetSpecular(.5);
		volumeProperty->SetSpecularPower(25);
		volumeProperty->SetInterpolationTypeToLinear();

		vtkSmartPointer<vtkPiecewiseFunction> compositeOpacity = vtkSmartPointer<vtkPiecewiseFunction>::New();
		//compositeOpacity->AddPoint(0, 1);
		//compositeOpacity->AddPoint(260, 1);
		//compositeOpacity->SetClamping(0);
		compositeOpacity->AddPoint(-3024, 0, 0.5, 0.0);
		compositeOpacity->AddPoint(-220, 0, .49, .61);
		compositeOpacity->AddPoint(625, .71, .5, 0.0);
		compositeOpacity->AddPoint(3071, 0.0, 0.5, 0.0);

		volumeProperty->SetScalarOpacity(compositeOpacity);

		vtkSmartPointer<vtkColorTransferFunction> color = vtkSmartPointer<vtkColorTransferFunction>::New();
		//color->AddRGBPoint(0, 1, 0.7, 0.6); //灰度值及RGB颜色值
		//color->AddRGBPoint(20, 1, 0.7, 0.6);
		//color->AddRGBPoint(40, 1, 1, 0);
		//color->AddRGBPoint(60, 0.8, 0.8, 0.8);
		//color->AddRGBPoint(70, 0.9, 0, 0);
		//color->AddRGBPoint(160, 1, 1, 1);
		//color->AddRGBPoint(260, 1, 1, 1);
		//color->SetClamping(0);
		color->AddRGBPoint(-3024, 0, 0, 0, 0.5, 0.0);
		color->AddRGBPoint(-200, 0.73, 0.25, 0.30, 0.49, .61);
		color->AddRGBPoint(641, .90, .82, .56, .5, 0.0);
		color->AddRGBPoint(3071, 1, 1, 1, .5, 0.0);

		volumeProperty->SetColor(color);

		vtkSmartPointer<vtkPiecewiseFunction> volumeGradientOpacity =
			vtkSmartPointer<vtkPiecewiseFunction>::New();
		volumeGradientOpacity->AddPoint(0, 2.0);
		volumeGradientOpacity->AddPoint(500, 2.0);
		volumeGradientOpacity->AddSegment(600, 0.73, 900, 0.9);
		volumeGradientOpacity->AddPoint(1300, 0.1);
		volumeProperty->SetGradientOpacity(volumeGradientOpacity);


		vtkSmartPointer<vtkVolume>volume = vtkSmartPointer<vtkVolume>::New();
		volume->SetMapper(volumeMapper);
		volume->SetProperty(volumeProperty);


		this->pRen = vtkSmartPointer<vtkRenderer>::New();
		this->pRen->AddVolume(volume);

		return this->pRen;
	};

private:
	vtkSmartPointer<vtkMetaImageReader> reader;
	vtkSmartPointer<vtkRenderer> pRen;

};

MyVolumeRendering::MyVolumeRendering()
{
}

MyVolumeRendering::~MyVolumeRendering()
{
}