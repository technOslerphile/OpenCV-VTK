#include <iostream>

#include <opencv2\highgui\highgui.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <vtkSmartPointer.h>
#include <vtkWindowToImageFilter.h>
#include <vtkSphereSource.h>
#include <vtkConeSource.h>
#include <vtkRenderer.h>
#include <vtkMapper.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCamera.h>
#include <vtkImageData.h>

using namespace std;
using namespace cv;

int main()
{
	vtkSmartPointer<vtkSphereSource> sphere = vtkSmartPointer<vtkSphereSource>::New();
	vtkSmartPointer<vtkConeSource> cone1 = vtkSmartPointer<vtkConeSource>::New();
	vtkSmartPointer<vtkConeSource> cone2 = vtkSmartPointer<vtkConeSource>::New();
	vtkSmartPointer<vtkConeSource> cone3 = vtkSmartPointer<vtkConeSource>::New();
	vtkSmartPointer<vtkPolyDataMapper> mapper1 = vtkSmartPointer<vtkPolyDataMapper>::New();
	vtkSmartPointer<vtkPolyDataMapper> mapper2 = vtkSmartPointer<vtkPolyDataMapper>::New();
	vtkSmartPointer<vtkPolyDataMapper> mapper3 = vtkSmartPointer<vtkPolyDataMapper>::New();
	vtkSmartPointer<vtkActor> actor1 = vtkSmartPointer<vtkActor>::New();
	vtkSmartPointer<vtkActor> actor2 = vtkSmartPointer<vtkActor>::New();
	vtkSmartPointer<vtkActor> actor3 = vtkSmartPointer<vtkActor>::New();
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
	vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	vtkSmartPointer<vtkWindowToImageFilter> imageFilter = vtkSmartPointer<vtkWindowToImageFilter>::New();

	//Create a Sphere
	sphere->SetCenter(0,0,0);
	sphere->SetRadius(2);

	//Create Cones
	cone1->SetDirection(1,0,0); cone1->SetRadius(0.3); cone1->SetCenter(cone1->GetHeight()/2,0,0);
	cone2->SetDirection(0,1,0); cone2->SetRadius(0.3); cone2->SetCenter(0, cone2->GetHeight()/2, 0);
	cone2->SetDirection(0,0,0.7); cone2->SetRadius(0.3); cone2->SetCenter(0, 0, cone2->GetHeight()/2);

	//Mappers and Actors
	mapper1->SetInputConnection(cone1->GetOutputPort()); actor1->SetMapper(mapper1); actor1->GetProperty()->SetColor(1,0,0);
	mapper2->SetInputConnection(cone2->GetOutputPort()); actor2->SetMapper(mapper2); actor2->GetProperty()->SetColor(0,1,0);
	mapper3->SetInputConnection(cone3->GetOutputPort()); actor3->SetMapper(mapper3); actor3->GetProperty()->SetColor(0,0,1);

	//Rendering
	renderer->AddActor(actor1); renderer->AddActor(actor2); renderer->AddActor(actor3);
	renderer->SetBackground(0.7, 0.5, 0.8);
	renderWindow->AddRenderer(renderer);
	renderWindow->SetSize(640,360);
	interactor->SetRenderWindow(renderWindow);

	//Start Visualising
	renderWindow->Render();
	interactor->Start();

	//Window to Image Filtering
	int windowSize[2];
	renderWindow->GetInteractor()->GetSize(windowSize);
	cv::Mat image(windowSize[1], windowSize[0], CV_8UC3);
	renderer->TexturedBackgroundOff();
	imageFilter->SetInput(renderWindow);
	vtkImageData *imageData = imageFilter->GetOutput();
	imageFilter->Update();
	image.data = (unsigned char*)imageData->GetScalarPointer();
	//cv::flip(image,image,0);
	//cv::cvtColor(image, image, CV_RGB2BGR);
	cvNamedWindow("ScreenShot", CV_WINDOW_AUTOSIZE);
	imshow("ScreenShot", image);
	imwrite("image.jpg", image);
    
	cvWaitKey(0);
	return EXIT_SUCCESS;
}
