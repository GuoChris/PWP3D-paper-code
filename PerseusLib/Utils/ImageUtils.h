#pragma once

#include "..\Others\PerseusLibDefines.h"

#include "..\Primitives\ImagePerseus.h"
#include "..\Primitives\PixelUCHAR4.h"

using namespace PerseusLib::Primitives;

namespace PerseusLib
{
	namespace Utils
	{
		class ImageUtils
		{
		private:
			static ImageUtils* instance;
		public:
			static ImageUtils* Instance(void) {
				if (instance == NULL) instance = new ImageUtils();
				return instance;
			}

			void ScaleToGray(ImageFloat *source, ImageUChar4* dest);
			void Overlay(ImageUChar* srcGrey, ImageUChar4 *destRGB, int destR = 255, int destG = 0, int destB = 0);
			
			void FlipColours(ImageUChar4 *image);

			void SaveImageToFile(ImageUChar4* image, char* fileName);
			void LoadImageFromFile(ImageUChar4* image, char* fileName);
			void LoadImageFromFile(ImageUChar* image, char* fileName, int fixedValue = -1);

			void Copy(ImageUChar4 *src, ImageUChar4* dst);
			void Copy(ImageUChar *src, ImageUChar* dst);
			void Copy(ImageUChar *src, ImageUChar4* dst);
			void Copy(ImageUChar4 *src, ImageUChar* dst, int fixedValue = -1);

			ImageUtils(void);
			~ImageUtils(void);
		};
	}
}