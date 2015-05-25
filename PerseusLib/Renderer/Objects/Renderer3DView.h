#pragma once

#include "..\..\Others\PerseusLibDefines.h"

#include "..\..\Utils\ImageUtils.h"

#include "..\..\Renderer\Primitives\Camera3D.h"
#include "..\..\Renderer\Transforms\CameraCoordinateTransform.h"

using namespace PerseusLib::Primitives;
using namespace PerseusLib::Utils;

using namespace Renderer::Transforms;
using namespace Renderer::Primitives;

namespace Renderer
{
	namespace Objects
	{
		class Renderer3DView
		{
		public:
			Camera3D* camera3D;
			CameraCoordinateTransform* cameraCoordinateTransform;
			CameraCoordinateTransform::ProjectionParams projectionParams;

			int viewId;
			int view[4];
			int roiGenerated[6];
			
			VFLOAT invP[16];

			void SetViewPort(int x, int y, int width, int height) { view[0] = x; view[1] = y; view[2] = width; view[3] = height; }

			Renderer3DView(int width, int height, Camera3D* camera, VFLOAT zNear, VFLOAT zFar, int viewId)
			{
				this->camera3D = camera;
				cameraCoordinateTransform = new CameraCoordinateTransform();
				cameraCoordinateTransform->SetProjectionMatrix(camera, zNear, zFar);

				this->viewId = viewId;

				this->SetViewPort(0, 0, width, height);
			}

			Renderer3DView(int width, int height, char* cameraCalibrationFile, VFLOAT zNear, VFLOAT zFar, int viewId)
			{
				camera3D = new Camera3D(cameraCalibrationFile);

				cameraCoordinateTransform = new CameraCoordinateTransform();
				cameraCoordinateTransform->SetProjectionMatrix(cameraCalibrationFile, zNear, zFar);
				cameraCoordinateTransform->GetProjectionParameters(&projectionParams);

				//setup invP matrix (inverse of projection matrix ... needed in energy function)
				cameraCoordinateTransform->GetInvPMatrix(invP);

				this->viewId = viewId;

				this->SetViewPort(0, 0, width, height);
			}

			~Renderer3DView(void) {
				delete cameraCoordinateTransform;
			}
		};
	}
}