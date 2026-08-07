
#ifndef MultiArrayModel_hpp
	#define MultiArrayModel_hpp

	#include "MemoryAllocator.hpp"
	#include "ArrayPointer.hpp"

	namespace pankey{

		namespace DataStructure{

			namespace Array{

				template<class Policy>
				struct MultiArrayModel{
					using ALLOCATOR_TYPE = ::pankey::Memory::Allocator::MemoryAllocator;
					using VALUE_TYPE = ArrayPointer<Policy>;
					using SIZE_TYPE = int;
				};

			}

		}

	}

#endif



