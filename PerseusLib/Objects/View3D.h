#pragma once

#include "..\Others\PerseusLibDefines.h"

#include "..\Renderer\Transforms\CoordinateTransform.h"
#include "..\Renderer\Objects\Renderer3DView.h"

#include "..\Primitives\Vector3D.h"
#include "..\Primitives\Vector4D.h"

#include "..\Objects\Pose3D.h"
#include "..\Objects\View3DParams.h"
#include "..\Objects\ImageRender.h"

#include "..\Utils\ImageUtils.h"

using namespace PerseusLib::Objects;

using namespace Renderer::Primitives;
using namespace Renderer::Transforms;
using namespace Renderer::Objects;

using namespace PerseusLib::Utils;

namespace PerseusLib
{
	namespace Objects
	{
		class View3D
		{
		public:
			int viewId;

			float zBufferOffset;

			VUINT roiGeneratedAll[6];

			Renderer3DView* renderView;

			ImageRender *imageRenderAll;

			ImageRender *imageHistogramMaskAll;
			ImageUChar *imageWireframeAll;

			ImageUChar *imagePosteriors;
			ImageUChar4 *imageRegistered;
			ImageUChar4 *imageRegisteredPrev;
			ImageUChar4 *imageProximity;

			ImageUChar *videoMask;

			View3D(int viewIdx, char* cameraCalibFileName, int width, int height, View3DParams* params = NULL) {
				if (params == NULL) { View3DParams params_c = View3DParams(); params = &params_c; }
				
				this->viewId = viewIdx;
				this->zBufferOffset = params->zBufferOffset;

				renderView = new Renderer3DView(width, height, cameraCalibFileName, params->zNear, params->zFar, viewIdx);

				imageRenderAll = new ImageRender(width, height, true);

				imageHistogramMaskAll = new ImageRender(width, height, false);
				imageWireframeAll = new ImageUChar(width, height, false);

				imagePosteriors = new ImageUChar(width, height, false);

				imageRegistered = new ImageUChar4(width, height, true);
				imageRegisteredPrev = new ImageUChar4(width, height, false);
				imageProximity = new ImageUChar4(width, height, false);

				videoMask = new ImageUChar(width, height, false);
			}

			~View3D() {
				delete imageRenderAll;
				
				delete imageHistogramMaskAll;
				delete imageWireframeAll;

				delete imagePosteriors;

				delete imageRegistered;
				delete imageRegisteredPrev;
				delete imageProximity;

				delete videoMask;

				delete renderView;
			}
		};
	}
}