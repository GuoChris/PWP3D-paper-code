#pragma once

#include "..\Objects\Pose3D.h"

namespace PerseusLib
{
	namespace Objects
	{
		class Object3DParams
		{
		public:
			int numberOfOptimizedVariables;
			int noVarBinHistograms; // max 8
			int noVarBinHistogramBins[4];

			Object3DParams() {
				noVarBinHistogramBins[0] = 8;
				noVarBinHistogramBins[1] = 16;
				noVarBinHistogramBins[2] = 32;
				noVarBinHistogramBins[3] = 64;
				noVarBinHistograms = 4;
				numberOfOptimizedVariables = 7;
			}
			~Object3DParams(void) 
			{ 

			}
		};
	}
}