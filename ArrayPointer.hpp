#pragma once

#include "ArrayIterator.hpp"
#include "move.hpp"
#include "MemoryAllocator.hpp"

#if defined(pankey_Log) && (defined(ArrayPointer_Log) || defined(pankey_Global_Log) || defined(pankey_DataStructure_Array_Log))
	#include "Logger_status.hpp"
	#define ArrayPointerLog(status,method,mns) pankey_Log(status,"ArrayPointer",method,mns)
#else
	#define ArrayPointerLog(status,method,mns)
#endif

namespace pankey{

	namespace DataStructure{

		namespace Array{

			template<typename Policy>
			class ArrayPointer{
				public:
					using ALLOCATOR_TYPE = typename Policy::ALLOCATOR_TYPE;
					using VALUE_TYPE = typename Policy::VALUE_TYPE;
					using SIZE_TYPE = typename Policy::SIZE_TYPE;

					ArrayPointer(){
						ArrayPointerLog(pankey_Log_StartMethod, "Constructor", "");
						ArrayPointerLog(pankey_Log_Statement, "Constructor", "Default Constructor");
						ArrayPointerLog(pankey_Log_EndMethod, "Constructor", "");
					}

					ArrayPointer(ALLOCATOR_TYPE* a_allocator){
						ArrayPointerLog(pankey_Log_StartMethod, "Constructor", "");
						ArrayPointerLog(pankey_Log_Statement, "Constructor", "MemoryAllocator*");
						this->m_allocator = setMemoryAllocator(a_allocator);
						ArrayPointerLog(pankey_Log_EndMethod, "Constructor", "");
					}

					ArrayPointer(const ArrayPointer<Policy>& a_values){
						ArrayPointerLog(pankey_Log_StartMethod, "Copy Constructor", "");
						ArrayPointerLog(pankey_Log_Statement, "Copy Constructor", "const ArrayPointer&");
						this->m_allocator = setMemoryAllocator(a_values.m_allocator);
						if(a_values.isEmpty()){
							ArrayPointerLog(pankey_Log_EndMethod, "Copy Constructor", "a_values.isEmpty()");
							return;
						}
						this->createArray(a_values.m_last_index);
						this->copy(a_values.m_t_value, a_values.m_last_index);
						ArrayPointerLog(pankey_Log_EndMethod, "Copy Constructor", "");
					}

					ArrayPointer(ArrayPointer<Policy>&& a_values){
						ArrayPointerLog(pankey_Log_StartMethod, "Constructor", "start");
						ArrayPointerLog(pankey_Log_Statement, "Constructor", "ArrayPointer&&");
						this->m_last_index = a_values.m_last_index;
						this->m_size = a_values.m_size;
						this->m_t_value = a_values.m_t_value;
						this->m_allocator = a_values.m_allocator;
						a_values.m_allocator = nullptr;
						a_values.m_t_value = nullptr;
						a_values.m_last_index = 0;
						a_values.m_size = 0;
						ArrayPointerLog(pankey_Log_EndMethod, "Constructor", "");
					}

					~ArrayPointer(){
						ArrayPointerLog(pankey_Log_StartMethod, "Destructor", "");
						ArrayPointerLog(pankey_Log_Statement, "Destructor", "~ArrayPointer");
						pankey::Memory::Allocator::deallocateArray<VALUE_TYPE>(this->m_allocator, this->m_size, this->m_t_value);
						pankey::Memory::Allocator::destroyMemoryAllocator(this->m_allocator);
						ArrayPointerLog(pankey_Log_EndMethod, "Destructor", "");
					}

				protected:

					void copy(VALUE_TYPE* a_array, SIZE_TYPE a_size){
						ArrayPointerLog(pankey_Log_StartMethod, "copy", "");
						if(this->m_t_value == nullptr || a_array == nullptr){
							ArrayPointerLog(pankey_Log_StartMethod, "copy", "this->m_t_value == nullptr || a_array == nullptr");
							return;
						}
						if(a_size > this->m_size){
							ArrayPointerLog(pankey_Log_EndMethod, "copy", "a_size > this->m_size");
							return;
						}
						for(SIZE_TYPE x = 0; x < a_size; x++){
							this->m_t_value[x] = a_array[x];
						}
						this->m_last_index = a_size;
						ArrayPointerLog(pankey_Log_EndMethod, "copy", "");
					}

					void copyFast(VALUE_TYPE* a_array, SIZE_TYPE a_size){
						ArrayPointerLog(pankey_Log_StartMethod, "copyFast", "");
						for(SIZE_TYPE x = 0; x < a_size; x++){
							this->m_t_value[x] = a_array[x];
						}
						ArrayPointerLog(pankey_Log_EndMethod, "copyFast", "");
					}

					void move(VALUE_TYPE* a_array, SIZE_TYPE a_size){
						ArrayPointerLog(pankey_Log_StartMethod, "move", "");
						if(a_size > this->m_last_index || this->m_t_value == nullptr || a_array == nullptr){
							return;
						}
						for(SIZE_TYPE x = 0; x < a_size; x++){
							this->m_t_value[x] = pankey::Utility::Base::move(a_array[x]);
						}
						ArrayPointerLog(pankey_Log_EndMethod, "move", "");
					}

					void moveFast(VALUE_TYPE* a_array, SIZE_TYPE a_size){
						ArrayPointerLog(pankey_Log_StartMethod, "moveFast", "");
						for(SIZE_TYPE x = 0; x < a_size; x++){
							this->m_t_value[x] = pankey::Utility::Base::move(a_array[x]);
						}
						ArrayPointerLog(pankey_Log_EndMethod, "moveFast", "");
					}
				
				public:

					VALUE_TYPE* getArrayPointer() const{
						ArrayPointerLog(pankey_Log_StartMethod, "getArrayPointer", "");
						ArrayPointerLog(pankey_Log_EndMethod, "getArrayPointer", "");
						return this->m_t_value;
					}

					void createArray(SIZE_TYPE a_size){
						ArrayPointerLog(pankey_Log_StartMethod, "createArray", "");
						ArrayPointerLog(pankey_Log_Statement, "createArray", "size:");
						ArrayPointerLog(pankey_Log_Statement, "createArray", a_size);
						pankey::Memory::Allocator::deallocateArray<VALUE_TYPE>(this->m_allocator, this->m_size, this->m_t_value);
						this->m_t_value = pankey::Memory::Allocator::allocateArray<VALUE_TYPE>(this->m_allocator, a_size);
						ArrayPointerLog(pankey_Log_Statement, "createArray", "is new Array is null:");
						ArrayPointerLog(pankey_Log_Statement, "createArray", this->m_t_value == nullptr);
						this->m_last_index = 0;
						this->m_size = a_size;
						ArrayPointerLog(pankey_Log_EndMethod, "createArray", "");
					}

					void createArrayFast(SIZE_TYPE a_size){
						ArrayPointerLog(pankey_Log_StartMethod, "createArrayFast", "");
						this->m_t_value = pankey::Memory::Allocator::allocateArray<VALUE_TYPE>(m_allocator, a_size);
						this->m_last_index = 0;
						this->m_size = a_size;
						ArrayPointerLog(pankey_Log_EndMethod, "createArrayFast", "");
					}

					void expand(SIZE_TYPE a_size){
						ArrayPointerLog(pankey_Log_StartMethod, "expand", "");
						SIZE_TYPE i_size = this->m_size + a_size;
						ArrayPointerLog(pankey_Log_Statement, "expand", "initial size:");
						ArrayPointerLog(pankey_Log_Statement, "expand", this->m_size);
						ArrayPointerLog(pankey_Log_Statement, "expand", "requested extra size:");
						ArrayPointerLog(pankey_Log_Statement, "expand", a_size);
						ArrayPointerLog(pankey_Log_Statement, "expand", "applied new size:");
						ArrayPointerLog(pankey_Log_Statement, "expand", i_size);
						ArrayPointerLog(pankey_Log_Statement, "expand", "last index:");
						ArrayPointerLog(pankey_Log_Statement, "expand", this->m_last_index);
						VALUE_TYPE *nT = pankey::Memory::Allocator::allocateArray<VALUE_TYPE>(this->m_allocator, i_size);
						for(SIZE_TYPE x = 0; x < this->m_last_index; x++){
							nT[x] = pankey::Utility::Base::move(this->m_t_value[x]);
						}
						if(this->m_t_value != nullptr){
							ArrayPointerLog(pankey_Log_Statement, "expand", "this->m_t_value != nullptr");
							pankey::Memory::Allocator::deallocateArray<VALUE_TYPE>(this->m_allocator, this->m_size, this->m_t_value);
						}
						this->m_t_value = nT;
						this->m_size = i_size;
						ArrayPointerLog(pankey_Log_EndMethod, "expand", "");
					}

					void shrink(SIZE_TYPE a_size){
						ArrayPointerLog(pankey_Log_StartMethod, "shrink", "");
						SIZE_TYPE i_size = this->m_size - a_size;
						VALUE_TYPE *nT = pankey::Memory::Allocator::allocateArray<VALUE_TYPE>(m_allocator, i_size);
						for(SIZE_TYPE x = 0; x < this->m_last_index && x < i_size; x++){
							nT[x] = pankey::Utility::Base::move(this->m_t_value[x]);
						}
						if(this->m_t_value != nullptr){
							ArrayPointerLog(pankey_Log_Statement, "shrink", "this->m_t_value != nullptr");
							pankey::Memory::Allocator::deallocateArray<VALUE_TYPE>(this->m_allocator, this->m_size, this->m_t_value);
						}
						this->m_t_value = nT;
						this->m_size = i_size;
						if(this->m_last_index > i_size){
							this->m_last_index = i_size;
						}
						ArrayPointerLog(pankey_Log_EndMethod, "shrink", "");
					}

					void clear(){
						ArrayPointerLog(pankey_Log_StartMethod, "clear", "");
						if(this->m_t_value == nullptr){
							this->m_last_index = 0;
							this->m_size = 0;
							ArrayPointerLog(pankey_Log_EndMethod, "clear", "this->m_t_value == nullptr");
							return;
						}
						pankey::Memory::Allocator::deallocateArray<VALUE_TYPE>(this->m_allocator, this->m_size, this->m_t_value);
						this->m_t_value = nullptr;
						this->m_last_index = 0;
						this->m_size = 0;
						ArrayPointerLog(pankey_Log_EndMethod, "clear", "");
					}

					void reseVALUE_TYPE(){
						ArrayPointerLog(pankey_Log_StartMethod, "reset", "");
						this->m_last_index = 0;
						ArrayPointerLog(pankey_Log_EndMethod, "reset", "");
					}

					bool isEmpty() const{
						ArrayPointerLog(pankey_Log_StartMethod, "isEmpty", "");
						ArrayPointerLog(pankey_Log_Statement, "isEmpty", "this->m_last_index == 0");
						ArrayPointerLog(pankey_Log_Statement, "isEmpty", this->m_last_index == 0);
						ArrayPointerLog(pankey_Log_Statement, "isEmpty", "this->m_t_value == nullptr");
						ArrayPointerLog(pankey_Log_Statement, "isEmpty", this->m_t_value == nullptr);
						ArrayPointerLog(pankey_Log_EndMethod, "isEmpty", "");
						return this->m_last_index == 0 || this->m_t_value == nullptr;
					}

					SIZE_TYPE getSize() const{
						ArrayPointerLog(pankey_Log_StartMethod, "getSize", "");
						ArrayPointerLog(pankey_Log_EndMethod, "getSize", "");
						return this->m_size;
					}

					void setLastIndex(SIZE_TYPE a_index){
						ArrayPointerLog(pankey_Log_StartMethod, "setLastIndex", "");
						this->m_last_index = a_index;
						ArrayPointerLog(pankey_Log_EndMethod, "setLastIndex", "");
					}

					SIZE_TYPE getLastIndex() const{
						ArrayPointerLog(pankey_Log_StartMethod, "getLastIndex", "");
						ArrayPointerLog(pankey_Log_EndMethod, "getLastIndex", "");
						return this->m_last_index;
					}

					void setLength(SIZE_TYPE a_index){
						ArrayPointerLog(pankey_Log_StartMethod, "setLength", "");
						this->m_last_index = a_index;
						ArrayPointerLog(pankey_Log_EndMethod, "setLength", "");
					}

					SIZE_TYPE length() const{
						ArrayPointerLog(pankey_Log_StartMethod, "length", "");
						ArrayPointerLog(pankey_Log_EndMethod, "length", "");
						return this->m_last_index;
					}

					SIZE_TYPE getAvailableSpace() const{
						ArrayPointerLog(pankey_Log_StartMethod, "length", "");
						ArrayPointerLog(pankey_Log_EndMethod, "length", "");
						return this->m_size - this->m_last_index;
					}

					bool add(const VALUE_TYPE& a_value){
						ArrayPointerLog(pankey_Log_StartMethod, "add", "const VALUE_TYPE&");
						if(this->m_last_index >= this->m_size || this->m_t_value == nullptr){
							ArrayPointerLog(pankey_Log_Statement, "add", "expanding");
							this->expand(this->m_expandSize);
						}
						if(this->m_last_index >= this->m_size || this->m_t_value == nullptr){
							ArrayPointerLog(pankey_Log_EndMethod, "add", "no more space");
							return false;
						}
						this->m_t_value[this->m_last_index] = a_value;
						this->m_last_index++;
						ArrayPointerLog(pankey_Log_EndMethod, "add", "");
						return true;
					}

					bool add(VALUE_TYPE&& a_value){
						ArrayPointerLog(pankey_Log_StartMethod, "add", "VALUE_TYPE&&");
						if(this->m_last_index >= this->m_size || this->m_t_value == nullptr){
							ArrayPointerLog(pankey_Log_Statement, "add", "expanding");
							this->expand(this->m_expandSize);
						}
						if(this->m_last_index >= this->m_size || this->m_t_value == nullptr){
							ArrayPointerLog(pankey_Log_EndMethod, "add", "no more space");
							return false;
						}
						this->m_t_value[this->m_last_index] = pankey::Utility::Base::move(a_value);
						this->m_last_index++;
						ArrayPointerLog(pankey_Log_EndMethod, "add", "");
						return true;
					}

					bool add(const ArrayPointer<Policy>& a_array){
						ArrayPointerLog(pankey_Log_StartMethod, "add", "const VALUE_TYPE&");
						if(a_array.isEmpty()){
							ArrayPointerLog(pankey_Log_EndMethod, "add", "a_array.isEmpty()");
							return false;
						}
						if(this->getAvailableSpace() < a_array.length() || this->m_t_value == nullptr){
							ArrayPointerLog(pankey_Log_Statement, "add", "expanding");
							this->expand(a_array.length());
						}
						if(this->getAvailableSpace() < a_array.length() || this->m_t_value == nullptr){
							ArrayPointerLog(pankey_Log_EndMethod, "add", "no more space");
							return false;
						}
						for(SIZE_TYPE x = 0; x < a_array.length(); x++){
							this->m_t_value[this->m_last_index] = a_array.get(x);
							this->m_last_index++;
						}
						ArrayPointerLog(pankey_Log_EndMethod, "add", "");
						return true;
					}

					void addFast(const VALUE_TYPE& a_value){
						ArrayPointerLog(pankey_Log_StartMethod, "addFast", "");
						this->m_t_value[this->m_last_index] = a_value;
						this->m_last_index++;
						ArrayPointerLog(pankey_Log_EndMethod, "addFast", "");
					}

					void addFast(VALUE_TYPE&& a_value){
						ArrayPointerLog(pankey_Log_StartMethod, "addFast", "");
						this->m_t_value[this->m_last_index] = pankey::Utility::Base::move(a_value);
						this->m_last_index++;
						ArrayPointerLog(pankey_Log_EndMethod, "addFast", "");
					}

					bool set(SIZE_TYPE a_index, const VALUE_TYPE& a_value){
						ArrayPointerLog(pankey_Log_StartMethod, "set", "");
						if(a_index < 0 || a_index >= this->m_size || this->m_t_value == nullptr){
							return false;
						}
						this->m_t_value[a_index] = a_value;
						if(a_index == this->m_last_index){
							this->m_last_index++;
						}
						ArrayPointerLog(pankey_Log_EndMethod, "set", "");
						return true;
					}

					bool set(SIZE_TYPE a_index, VALUE_TYPE&& a_value){
						ArrayPointerLog(pankey_Log_StartMethod, "set", "");
						if(a_index < 0 || a_index >= this->m_size || this->m_t_value == nullptr){
							return false;
						}
						this->m_t_value[a_index] = pankey::Utility::Base::move(a_value);
						if(a_index == this->m_last_index){
							this->m_last_index++;
						}
						ArrayPointerLog(pankey_Log_EndMethod, "set", "");
						return true;
					}

					void setFast(SIZE_TYPE a_index, const VALUE_TYPE& a_value){
						ArrayPointerLog(pankey_Log_StartMethod, "setFast", "");
						this->m_t_value[a_index] = a_value;
						ArrayPointerLog(pankey_Log_EndMethod, "setFast", "");
					}

					void setFast(SIZE_TYPE a_index, VALUE_TYPE&& a_value){
						ArrayPointerLog(pankey_Log_StartMethod, "setFast", "");
						this->m_t_value[a_index] = pankey::Utility::Base::move(a_value);
						ArrayPointerLog(pankey_Log_EndMethod, "setFast", "");
					}

					bool insert(SIZE_TYPE a_index, const VALUE_TYPE& a_value){
						ArrayPointerLog(pankey_Log_StartMethod, "insert", "");
						ArrayPointerLog(pankey_Log_Statement, "insert", "insert index:");
						ArrayPointerLog(pankey_Log_Statement, "insert", a_index);
						ArrayPointerLog(pankey_Log_Statement, "insert", "last index:");
						ArrayPointerLog(pankey_Log_Statement, "insert", this->m_last_index);
						ArrayPointerLog(pankey_Log_Statement, "insert", "size:");
						ArrayPointerLog(pankey_Log_Statement, "insert", this->m_size);
						if(a_index < 0){
							ArrayPointerLog(pankey_Log_EndMethod, "insert", "a_index < 0");
							return false;
						}
						if(a_index >= this->m_size || this->m_last_index >= this->m_size || this->m_t_value == nullptr){
							ArrayPointerLog(pankey_Log_Statement, "insert", "expanding");
							if(a_index >= this->m_size){
								ArrayPointerLog(pankey_Log_Statement, "insert", "a_index >= this->m_size");
								this->expand(this->m_expandSize + (this->m_size - a_index));
							}
							if(this->m_last_index >= this->m_size){
								ArrayPointerLog(pankey_Log_Statement, "insert", "this->m_last_index >= this->m_size");
								this->expand(this->m_expandSize);
							}
						}
						if(a_index >= this->m_size || this->m_last_index >= this->m_size || this->m_t_value == nullptr){
							ArrayPointerLog(pankey_Log_EndMethod, "insert", "no more space");
							return false;
						}
						if(a_index == this->m_last_index){
							this->m_t_value[this->m_last_index] = a_value;
							this->m_last_index++;
							ArrayPointerLog(pankey_Log_EndMethod, "insert", "a_index == this->m_last_index");
							return true;
						}
						if(a_index > this->m_last_index){
							this->m_t_value[a_index] = a_value;
							ArrayPointerLog(pankey_Log_EndMethod, "insert", "a_index > this->m_last_index");
							return true;
						}
						VALUE_TYPE i_retain = a_value;
						for(SIZE_TYPE x = a_index; x < this->m_last_index; x++){
							// ArrayPointerLog(pankey_Log_Statement, "insert", "interation:");
							// ArrayPointerLog(pankey_Log_Statement, "insert", x);
							VALUE_TYPE f_retain = pankey::Utility::Base::move(this->m_t_value[x]);
							// ArrayPointerLog(pankey_Log_Statement, "insert", "f_retain:");
							// ArrayPointerLog(pankey_Log_Statement, "insert", f_retain);
							this->m_t_value[x] = pankey::Utility::Base::move(i_retain);
							// ArrayPointerLog(pankey_Log_Statement, "insert", "this->m_t_value[x]:");
							// ArrayPointerLog(pankey_Log_Statement, "insert", this->m_t_value[x]);
							i_retain = pankey::Utility::Base::move(f_retain);
							// ArrayPointerLog(pankey_Log_Statement, "insert", "i_retain:");
							// ArrayPointerLog(pankey_Log_Statement, "insert", i_retain);
						}
						this->m_t_value[this->m_last_index] = pankey::Utility::Base::move(i_retain);
						this->m_last_index++;
						ArrayPointerLog(pankey_Log_EndMethod, "insert", "insert done");
						return true;
					}

					bool insert(SIZE_TYPE a_index, VALUE_TYPE&& a_value){
						ArrayPointerLog(pankey_Log_StartMethod, "insert", "");
						ArrayPointerLog(pankey_Log_Statement, "insert", "insert index:");
						ArrayPointerLog(pankey_Log_Statement, "insert", a_index);
						ArrayPointerLog(pankey_Log_Statement, "insert", "last index:");
						ArrayPointerLog(pankey_Log_Statement, "insert", this->m_last_index);
						ArrayPointerLog(pankey_Log_Statement, "insert", "size:");
						ArrayPointerLog(pankey_Log_Statement, "insert", this->m_size);
						if(a_index < 0){
							ArrayPointerLog(pankey_Log_EndMethod, "insert", "a_index < 0");
							return false;
						}
						if(a_index >= this->m_size || this->m_last_index >= this->m_size || this->m_t_value == nullptr){
							ArrayPointerLog(pankey_Log_Statement, "insert", "expanding");
							if(a_index >= this->m_size){
								ArrayPointerLog(pankey_Log_Statement, "insert", "a_index >= this->m_size");
								this->expand(this->m_expandSize + (this->m_size - a_index));
							}
							if(this->m_last_index >= this->m_size){
								ArrayPointerLog(pankey_Log_Statement, "insert", "this->m_last_index >= this->m_size");
								this->expand(this->m_expandSize);
							}
						}
						if(a_index >= this->m_size || this->m_last_index >= this->m_size || this->m_t_value == nullptr){
							ArrayPointerLog(pankey_Log_EndMethod, "insert", "no more space");
							return false;
						}
						if(a_index == this->m_last_index){
							this->m_t_value[this->m_last_index] = a_value;
							this->m_last_index++;
							ArrayPointerLog(pankey_Log_EndMethod, "insert", "a_index == this->m_last_index");
							return true;
						}
						if(a_index > this->m_last_index){
							this->m_t_value[a_index] = a_value;
							ArrayPointerLog(pankey_Log_EndMethod, "insert", "a_index > this->m_last_index");
							return true;
						}
						VALUE_TYPE i_retain = pankey::Utility::Base::move(a_value);
						for(SIZE_TYPE x = a_index; x < this->m_last_index; x++){
							VALUE_TYPE f_retain = pankey::Utility::Base::move(this->m_t_value[x]);
							this->m_t_value[x] = pankey::Utility::Base::move(i_retain);
							i_retain = pankey::Utility::Base::move(f_retain);
						}
						this->m_t_value[this->m_last_index] = pankey::Utility::Base::move(i_retain);
						this->m_last_index++;
						ArrayPointerLog(pankey_Log_EndMethod, "insert", "insert done");
						return true;
					}

					void insertFast(SIZE_TYPE a_index, const VALUE_TYPE& a_value){
						ArrayPointerLog(pankey_Log_StartMethod, "insertFast", "");
						if(a_index == this->m_last_index){
							this->m_t_value[this->m_last_index] = a_value;
							this->m_last_index++;
							ArrayPointerLog(pankey_Log_EndMethod, "insertFast", "a_index == this->m_last_index");
							return;
						}
						if(a_index > this->m_last_index){
							this->m_t_value[a_index] = a_value;
							ArrayPointerLog(pankey_Log_EndMethod, "insertFast", "a_index > this->m_last_index");
							return;
						}
						VALUE_TYPE i_retain = a_value;
						for(SIZE_TYPE x = a_index; x < this->m_last_index; x++){
							VALUE_TYPE f_retain = pankey::Utility::Base::move(this->m_t_value[x]);
							this->m_t_value[x] = pankey::Utility::Base::move(i_retain);
							i_retain = pankey::Utility::Base::move(f_retain);
						}
						this->m_t_value[this->m_last_index] = pankey::Utility::Base::move(i_retain);
						this->m_last_index++;
						ArrayPointerLog(pankey_Log_EndMethod, "insertFast", "");
					}

					void insertFast(SIZE_TYPE a_index, VALUE_TYPE&& a_value){
						ArrayPointerLog(pankey_Log_StartMethod, "insertFast", "");
						if(a_index == this->m_last_index){
							this->m_t_value[this->m_last_index] = a_value;
							this->m_last_index++;
							ArrayPointerLog(pankey_Log_EndMethod, "insertFast", "a_index == this->m_last_index");
							return;
						}
						if(a_index > this->m_last_index){
							this->m_t_value[a_index] = a_value;
							ArrayPointerLog(pankey_Log_EndMethod, "insertFast", "a_index > this->m_last_index");
							return;
						}
						VALUE_TYPE i_retain = pankey::Utility::Base::move(a_value);
						for(SIZE_TYPE x = a_index; x < this->m_last_index; x++){
							VALUE_TYPE f_retain = pankey::Utility::Base::move(this->m_t_value[x]);
							this->m_t_value[x] = pankey::Utility::Base::move(i_retain);
							i_retain = pankey::Utility::Base::move(f_retain);
						}
						this->m_t_value[this->m_last_index] = pankey::Utility::Base::move(i_retain);
						this->m_last_index++;
						ArrayPointerLog(pankey_Log_EndMethod, "insertFast", "");
					}

					VALUE_TYPE get(SIZE_TYPE x) const{
						ArrayPointerLog(pankey_Log_StartMethod, "get", "");
						if(this->m_t_value == nullptr){
							ArrayPointerLog(pankey_Log_EndMethod, "get", "");
							return VALUE_TYPE();
						}
						if(x < this->m_last_index){
							ArrayPointerLog(pankey_Log_EndMethod, "get", "");
							return this->m_t_value[x];
						}
						ArrayPointerLog(pankey_Log_EndMethod, "get", "");
						return VALUE_TYPE();
					}

					VALUE_TYPE getFast(SIZE_TYPE x) const{
						ArrayPointerLog(pankey_Log_StartMethod, "getFast", "");
						ArrayPointerLog(pankey_Log_EndMethod, "getFast", "");
						return this->m_t_value[x];
					}

					VALUE_TYPE&& getMove(SIZE_TYPE x) const{
						ArrayPointerLog(pankey_Log_StartMethod, "getMove", "");
						ArrayPointerLog(pankey_Log_EndMethod, "getMove", "");
						return pankey::Utility::Base::move(this->m_t_value[x]);
					}

					VALUE_TYPE remove(SIZE_TYPE a_index){
						ArrayPointerLog(pankey_Log_StartMethod, "remove", "");
						if(this->isEmpty() || a_index >= this->length()){
							return VALUE_TYPE();
						}
						VALUE_TYPE i_value = this->m_t_value[a_index];
						int i_iteration = this->length();
						this->m_last_index--;
						for(int x = a_index + 1; x < i_iteration; x++){
							this->m_t_value[x - 1] = this->m_t_value[x];
						}
						ArrayPointerLog(pankey_Log_EndMethod, "remove", "");
						return i_value;
					}

					VALUE_TYPE removeFast(SIZE_TYPE a_index){
						ArrayPointerLog(pankey_Log_StartMethod, "removeFast", "");
						
						ArrayPointerLog(pankey_Log_EndMethod, "removeFast", "");
						return remove(a_index);
					}

					ArrayPointer<Policy>& operator=(const ArrayPointer<Policy>& a_values){
						ArrayPointerLog(pankey_Log_StartMethod, "operator=", "");
						ArrayPointerLog(pankey_Log_Statement, "operator=", "const ArrayPointer&");
						this->m_allocator = setMemoryAllocator(this->m_allocator, a_values.m_allocator);
						this->clear();
						if(a_values.isEmpty()){
							ArrayPointerLog(pankey_Log_EndMethod, "operator=", "a_values.isEmpty()");
							return *this;
						}
						this->createArray(a_values.m_last_index);
						this->copy(a_values.m_t_value, a_values.m_last_index);
						ArrayPointerLog(pankey_Log_EndMethod, "operator=", "");
						return *this;
					}

					bool operator==(const ArrayPointer<Policy>& a_values)const{
						ArrayPointerLog(pankey_Log_StartMethod, "operator==", "");
						if(this->isEmpty() && a_values.isEmpty()){
							ArrayPointerLog(pankey_Log_Statement, "operator==", "this->isEmpty() == a_values.isEmpty()");
							ArrayPointerLog(pankey_Log_EndMethod, "operator==", "");
							return true;
						}
						if(this->length() != a_values.length()){
							ArrayPointerLog(pankey_Log_Statement, "operator==", "this->length() != a_values.length()");
							ArrayPointerLog(pankey_Log_EndMethod, "operator==", "");
							return false;
						}
						for(SIZE_TYPE x = 0; x < this->length(); x++){
							VALUE_TYPE f_value_1 = m_t_value[x];
							VALUE_TYPE f_value_2 = a_values.m_t_value[x];
							if(f_value_1 != f_value_2){
								ArrayPointerLog(pankey_Log_Statement, "operator==", "f_value_1 != f_value_2");
								ArrayPointerLog(pankey_Log_Statement, "operator==", "iteration:");
								ArrayPointerLog(pankey_Log_Statement, "operator==", x);
								ArrayPointerLog(pankey_Log_EndMethod, "operator==", "");
								return false;
							}
						}
						ArrayPointerLog(pankey_Log_EndMethod, "operator==", "");
						return true;
					}

					bool operator!=(const ArrayPointer<Policy>& a_values)const{
						ArrayPointerLog(pankey_Log_StartMethod, "operator!=", "");
						if(this->isEmpty() && a_values.isEmpty()){
							ArrayPointerLog(pankey_Log_Statement, "operator!=", "this->isEmpty() == a_values.isEmpty()");
							ArrayPointerLog(pankey_Log_EndMethod, "operator!=", "");
							return false;
						}
						if(this->length() != a_values.length()){
							ArrayPointerLog(pankey_Log_Statement, "operator!=", "this->length() != a_values.length()");
							ArrayPointerLog(pankey_Log_EndMethod, "operator!=", "");
							return true;
						}
						for(SIZE_TYPE x = 0; x < this->length(); x++){
							VALUE_TYPE f_value_1 = m_t_value[x];
							VALUE_TYPE f_value_2 = a_values.m_t_value[x];
							if(f_value_1 != f_value_2){
								ArrayPointerLog(pankey_Log_Statement, "operator!=", "f_value_1 != f_value_2");
								ArrayPointerLog(pankey_Log_Statement, "operator!=", "iteration:");
								ArrayPointerLog(pankey_Log_Statement, "operator!=", x);
								ArrayPointerLog(pankey_Log_EndMethod, "operator!=", "");
								return true;
							}
						}
						ArrayPointerLog(pankey_Log_EndMethod, "operator!=", "");
						return false;
					}

					ArrayPointer<Policy> operator+(const ArrayPointer<Policy>& a_values)const{
						ArrayPointerLog(pankey_Log_StartMethod, "operator!=", "");
						if(this->isEmpty() && a_values.isEmpty()){
							ArrayPointerLog(pankey_Log_Statement, "operator!=", "this->isEmpty() == a_values.isEmpty()");
							ArrayPointerLog(pankey_Log_EndMethod, "operator!=", "");
							return ArrayPointer<Policy>();
						}
						if(this->isEmpty()){
							ArrayPointerLog(pankey_Log_Statement, "operator!=", "this->isEmpty() == a_values.isEmpty()");
							ArrayPointerLog(pankey_Log_EndMethod, "operator!=", "");
							return *this;
						}
						if(a_values.isEmpty()){
							ArrayPointerLog(pankey_Log_Statement, "operator!=", "this->isEmpty() == a_values.isEmpty()");
							ArrayPointerLog(pankey_Log_EndMethod, "operator!=", "");
							return ArrayPointer<Policy>(a_values);
						}
						ArrayPointer<Policy> i_sum;
						i_sum.createArrayFast(this->length() + a_values.length());
						for(SIZE_TYPE x = 0; x < this->length(); x++){
							i_sum.addFast(this->getFast(x));
						}
						for(SIZE_TYPE x = 0; x < a_values.length(); x++){
							i_sum.addFast(a_values.getFast(x));
						}
						ArrayPointerLog(pankey_Log_EndMethod, "operator!=", "");
						return i_sum;
					}

					ArrayPointer<Policy> operator+=(const ArrayPointer<Policy>& a_values){
						ArrayPointerLog(pankey_Log_StartMethod, "operator+=", "");
						if(this->isEmpty() && a_values.isEmpty()){
							ArrayPointerLog(pankey_Log_Statement, "operator+=", "this->isEmpty() == a_values.isEmpty()");
							ArrayPointerLog(pankey_Log_EndMethod, "operator+=", "");
							return ArrayPointer<Policy>();
						}
						if(this->isEmpty()){
							ArrayPointerLog(pankey_Log_Statement, "operator+=", "this->isEmpty() == a_values.isEmpty()");
							ArrayPointerLog(pankey_Log_EndMethod, "operator+=", "");
							return *this;
						}
						if(a_values.isEmpty()){
							ArrayPointerLog(pankey_Log_Statement, "operator+=", "this->isEmpty() == a_values.isEmpty()");
							ArrayPointerLog(pankey_Log_EndMethod, "operator+=", "");
							return ArrayPointer<Policy>(a_values);
						}
						ArrayPointer<Policy> i_array = *this;
						this->operator=(i_array + a_values);
						ArrayPointerLog(pankey_Log_EndMethod, "operator+=", "");
						return *this;
					}

					VALUE_TYPE operator[](SIZE_TYPE a_index)const{
						ArrayPointerLog(pankey_Log_StartMethod, "operator[]", "VALUE_TYPE");
						if(this->m_t_value == nullptr || a_index < 0 || a_index >= this->m_size){
							ArrayPointerLog(pankey_Log_EndMethod, "operator[]", "this->m_t_value == nullptr || a_index < 0 || a_index >= this->m_size");
							return VALUE_TYPE();
						}
						ArrayPointerLog(pankey_Log_EndMethod, "operator[]", "");
						return this->m_t_value[a_index];
					}

				protected:
					ALLOCATOR_TYPE* m_allocator = nullptr;
					VALUE_TYPE* m_t_value = nullptr;
					SIZE_TYPE m_last_index = 0;
					SIZE_TYPE m_size = 0;
					SIZE_TYPE m_expandSize = 5;
			};

			template<class Policy, class... Args>
			ArrayPointer<Policy> createArrayPointer(Args... a_args){
				using VALUE_TYPE = typename Policy::VALUE_TYPE;
				VALUE_TYPE i_values[] = { static_cast<VALUE_TYPE>(a_args)... };
				ArrayPointer<Policy> i_array;
				for(const auto& f_value : i_values){
					i_array.add(f_value);
				}
				return i_array;
			}

			template<class Policy_1, class Policy_2>
			ArrayPointer<Policy_1> toArrayPointer(const ArrayPointer<Policy_2>& a_array){
				using VALUE_TYPE = typename Policy_1::VALUE_TYPE;
				ArrayPointer<Policy_1> i_array;
				for(int x = 0; x < a_array.length(); x++){
					VALUE_TYPE f_value = (VALUE_TYPE)a_array.get(x);
					i_array.add(f_value);
				}
				return i_array;
			}

		}

	}
	
}



