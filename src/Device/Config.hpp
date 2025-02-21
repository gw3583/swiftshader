// Copyright 2016 The SwiftShader Authors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef sw_Config_hpp
#define sw_Config_hpp

#include "System/Types.hpp"

namespace sw
{
	enum
	{
		PERF_PIXEL,
		PERF_PIPE,
		PERF_INTERP,
		PERF_SHADER,
		PERF_TEX,
		PERF_ROP,

		PERF_TIMERS
	};

	struct Profiler
	{
		Profiler();

		void reset();
		void nextFrame();

		int framesSec;
		int framesTotal;
		double FPS;
	};

	extern Profiler profiler;

	enum
	{
		OUTLINE_RESOLUTION = 8192,   // Maximum vertical resolution of the render target
		MIPMAP_LEVELS = 14,
		FRAGMENT_UNIFORM_VECTORS = 264,
		VERTEX_UNIFORM_VECTORS = 259,
		MAX_VERTEX_INPUTS = 32,
		MAX_VERTEX_OUTPUTS = 34,
		MAX_FRAGMENT_INPUTS = 32,
		MAX_FRAGMENT_UNIFORM_BLOCKS = 12,
		MAX_VERTEX_UNIFORM_BLOCKS = 12,
		MAX_UNIFORM_BUFFER_BINDINGS = MAX_FRAGMENT_UNIFORM_BLOCKS + MAX_VERTEX_UNIFORM_BLOCKS,   // Limited to 127 by SourceParameter.bufferIndex in Shader.hpp
		MAX_UNIFORM_BLOCK_SIZE = 16384,
		MAX_CLIP_PLANES = 6,
		MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS = 64,
		MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS = 64,
		MIN_PROGRAM_TEXEL_OFFSET = -8,
		MAX_PROGRAM_TEXEL_OFFSET = 7,
		MAX_TEXTURE_LOD = MIPMAP_LEVELS - 2,   // Trilinear accesses lod+1
		RENDERTARGETS = 8,
		NUM_TEMPORARY_REGISTERS = 4096,
		MAX_INTERFACE_COMPONENTS = 32 * 4,  // Must be multiple of 4 for 16-byte alignment.
	};
}

#endif   // sw_Config_hpp
