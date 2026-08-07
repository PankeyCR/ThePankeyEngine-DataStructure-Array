#pragma once

#if defined(pankey_Log) && (defined(ArrayIterator_Log) || defined(pankey_Global_Log) || defined(pankey_Base_Log))
	#include "Logger_status.hpp"
	#define ArrayIteratorLog(status,method,mns) pankey_Log(status,"ArrayIterator",method,mns)
#else
	#define ArrayIteratorLog(status,method,mns) 
#endif

namespace pankey{

	namespace DataStructure{

		namespace Array{

			template<class T>
			class ArrayIterator{
				public:
				
					ArrayIterator(T* i_array, int i_pos){
						ArrayIteratorLog(pankey_Log_StartMethod, "Constructor", "");
						m_array = i_array;
						m_pos = i_pos;
						ArrayIteratorLog(pankey_Log_EndMethod, "Constructor", "");
					}
				
					ArrayIterator(const ArrayIterator& i_iterator){
						ArrayIteratorLog(pankey_Log_StartMethod, "Constructor", "");
						m_array = i_iterator.m_array;
						m_pos = i_iterator.m_pos;
						ArrayIteratorLog(pankey_Log_EndMethod, "Constructor", "");
					}
					virtual ~ArrayIterator(){
						ArrayIteratorLog(pankey_Log_StartMethod, "Destructor", "");
						ArrayIteratorLog(pankey_Log_EndMethod, "Destructor", "");
					}
					
					virtual T& operator *(){
						ArrayIteratorLog(pankey_Log_StartMethod, "operator *", "");
						ArrayIteratorLog(pankey_Log_EndMethod, "operator *", "");
						return m_array[m_pos];
					}
				
					void operator ++(){
						ArrayIteratorLog(pankey_Log_StartMethod, "operator ++", "");
						if(m_array == nullptr){
							return;
						}
						m_pos++;
						ArrayIteratorLog(pankey_Log_EndMethod, "operator ++", "");
					}
					
					bool operator ==(ArrayIterator i){
						ArrayIteratorLog(pankey_Log_StartMethod, "operator ==", "");
						if(m_array == nullptr){
							return false;
						}
						ArrayIteratorLog(pankey_Log_EndMethod, "operator ==", "");
						return m_pos == i.m_pos;
					}
					
					bool operator !=(ArrayIterator i){
						ArrayIteratorLog(pankey_Log_StartMethod, "operator !=", "");
						if(m_array == nullptr){
							return false;
						}
						ArrayIteratorLog(pankey_Log_EndMethod, "operator !=", "");
						return m_pos != i.m_pos;
					}
					virtual ArrayIterator& operator =(const ArrayIterator& i){
						ArrayIteratorLog(pankey_Log_StartMethod, "operator =", "");
						m_array = i.m_array;
						m_pos = i.m_pos;
						ArrayIteratorLog(pankey_Log_EndMethod, "operator =", "");
						return *this;
					}
				protected:
					T* m_array = nullptr;
					int m_pos = 0;
			};

		}
	}
}