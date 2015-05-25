#pragma once

#include "..\..\Utils\ImageUtils.h"

#include "..\..\Objects\Pose3D.h"

#include "..\..\Renderer\Model\Model.h"
#include "..\..\Renderer\Model\ModelH.h"

#include "..\..\Renderer\Engine\DrawingPrimitives.h"

#include "..\..\Renderer\Transforms\CoordinateTransform.h"

#include "..\..\Renderer\Primitives\Quaternion.h"

#include "..\..\Renderer\Objects\Renderer3DObject.h"
#include "..\..\Renderer\Objects\Renderer3DView.h"

#include "..\..\CUDA\CUDAEngine.h"

using namespace PerseusLib::Primitives;
using namespace PerseusLib::Objects;
using namespace PerseusLib::Utils;

using namespace Renderer::Model3D;
using namespace Renderer::Primitives;
using namespace Renderer::Objects;
using namespace Renderer::Transforms;

#include <string>

namespace Renderer
{
	namespace Engine
	{
		class DrawingEngine
		{
		private:
			VECTOR3DA f;
			VFLOAT projectionMatrix[16], modelViewMatrix[16], pmMatrix[16], buffer[4];

			void applyCoordinateTransform(Renderer3DView* view, Renderer3DObject* object, float *pmMatrix);

			void drawFaceEdges(ImageUChar *imageRender, ModelFace* currentFace, ModelH* drawingModel, VBYTE color, int* roiGenerated);
			void drawFaceFilled(ImageUChar *imageRender, ModelFace* currentFace, ModelH* drawingModel, int objectId, VBYTE color, VINT meshId);
			void drawFaceFilled(ImageRender *imageRender, ModelFace* currentFace, ModelH* drawingModel, int objectId, VBYTE color, int meshId);

			void drawWireframe(ImageUChar* imageWireframe, ModelH* drawingModel, int* roiGenerated);
			void drawFilled(ImageRender* imageFill, ModelH* drawingModel, int objectId);
			void drawFilled(ImageUChar* imageFill, ModelH* drawingModel, int objectId);

			static DrawingEngine* instance;
		public:
			enum RenderingType {RENDERING_FILL, RENDERING_WIREFRAME};

			static DrawingEngine* Instance(void) {
				if (instance == NULL) instance = new DrawingEngine();
				return instance;
			}

			void DrawAllInView(Object3D** objects, int objectCount, View3D* view, bool useCUDA, bool getBackData);

			void Draw(Object3D* object, View3D *view, bool useCUDA, bool getBackData);
			void Draw(Object3D* object, View3D* view, Pose3D *pose, ImageUChar *image, RenderingType renderingType, bool clearImage = true);
			void Draw(Object3D* object, View3D* view, Pose3D *pose, ImageRender *imageRender, bool clearImage = true);

			void ChangeROIWithBand(Object3D* object, View3D *view, int bandSize, int width, int height);
			void ChangeROIWithBand(View3D* view, int bandSize, int width, int height);

			void GetPMMatrices(Object3D *object, View3D *view, Pose3D* pose, float *projectionMatrix, float *modelViewMatrix, float *pmMatrix);
			void ComputeAndSetPMMatrices(Object3D* object, View3D* view, Pose3D* pose = NULL);

			DrawingEngine(void);
			~DrawingEngine(void);
		};
	}
}