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

#ifndef sw_VertexProcessor_hpp
#define sw_VertexProcessor_hpp

#include "Matrix.hpp"
#include "Context.hpp"
#include "RoutineCache.hpp"
#include "Vertex.hpp"
#include "Pipeline/SpirvShader.hpp"

namespace sw
{
	struct DrawData;

	// Basic direct mapped vertex cache.
	struct VertexCache
	{
		static constexpr uint32_t SIZE = 64;  // TODO: Variable size?
		static constexpr uint32_t TAG_MASK = SIZE - 1;  // Size must be power of 2.

		void clear();

		Vertex vertex[SIZE];
		uint32_t tag[SIZE];

		int drawCall;
	};

	struct VertexTask
	{
		unsigned int vertexCount;
		unsigned int primitiveStart;
		VertexCache vertexCache;
	};

	class VertexProcessor
	{
	public:
		struct States : Memset<States>
		{
			States() : Memset(this, 0) {}

			uint32_t computeHash();

			uint64_t shaderID;

			struct Input
			{
				operator bool() const   // Returns true if stream contains data
				{
					return count != 0;
				}

				StreamType type    : BITS(STREAMTYPE_LAST);
				unsigned int count : 3;
				bool normalized    : 1;
				unsigned int attribType : BITS(SpirvShader::ATTRIBTYPE_LAST);
			};

			Input input[MAX_VERTEX_INPUTS];
		};

		struct State : States
		{
			bool operator==(const State &state) const;

			uint32_t hash;
		};

		typedef void (*RoutinePointer)(Vertex *output, unsigned int *batch, VertexTask *vertexTask, DrawData *draw);

		VertexProcessor();

		virtual ~VertexProcessor();

	protected:
		const State update(const sw::Context* context);
		Routine *routine(const State &state, vk::PipelineLayout const *pipelineLayout,
		                 SpirvShader const *vertexShader, const vk::DescriptorSet::Bindings &descriptorSets);

		void setRoutineCacheSize(int cacheSize);

	private:
		RoutineCache<State> *routineCache;
	};
}

#endif   // sw_VertexProcessor_hpp
