#pragma once

#include "CharPointer.hpp"
#include "MemorySize.hpp"
#include "MemoryAllocator.hpp"
#include "AllocatorFactory.hpp"
#include "strlen.hpp"

#if defined(pankey_Log) && (defined(Note_Log) || defined(pankey_Global_Log) || defined(pankey_DataStructure_Array_Log))
	#include "Logger_status.hpp"
	#define NoteLog(status,method,mns) pankey_Log(status,"Note",method,mns)
#else
	#define NoteLog(status,method,mns)
#endif

namespace pankey{

	namespace DataStructure{

		namespace Array{

			class Note : public pankey::Utility::Test::CharPointer{
				// public:
				// 	Note() {
				// 		NoteLog(pankey_Log_StartMethod, "Contructor", "const char*");
				// 		m_allocator = pankey::Memory::Allocator::setMemoryAllocator(AllocatorFactory(char));
				// 		NoteLog(pankey_Log_EndMethod, "Contructor", "");
				// 	}
				// 	Note(const char* a_pointer){
				// 		NoteLog(pankey_Log_StartMethod, "Contructor", "const char*");
				// 		m_allocator = pankey::Memory::Allocator::setMemoryAllocator(AllocatorFactory(char));
				// 		int i_length = pankey::Utility::Test::strlen(a_pointer);
				// 		this->create(a_pointer, i_length);
				// 		NoteLog(pankey_Log_EndMethod, "Contructor", "");
				// 	}

				// 	Note(const char* a_pointer, pankey::Memory::Allocator::MemoryAllocator* a_allocator){
				// 		NoteLog(pankey_Log_StartMethod, "Contructor", "const char*,MemoryAllocator");
				// 		m_allocator = pankey::Memory::Allocator::setMemoryAllocator(a_allocator);
				// 		int i_length = pankey::Utility::Test::strlen(a_pointer);
				// 		this->create(a_pointer, i_length);
				// 		NoteLog(pankey_Log_EndMethod, "Contructor", "");
				// 	}

				// 	Note(const char* a_pointer, int a_length){
				// 		NoteLog(pankey_Log_StartMethod, "Contructor", "const char*,int");
				// 		m_allocator = pankey::Memory::Allocator::setMemoryAllocator(AllocatorFactory(char));
				// 		this->create(a_pointer, a_length);
				// 		NoteLog(pankey_Log_EndMethod, "Contructor", "");
				// 	}

				// 	Note(const char* a_pointer, int a_length, pankey::Memory::Allocator::MemoryAllocator* a_allocator) : Note(){
				// 		NoteLog(pankey_Log_StartMethod, "Contructor", "const char*,pankey::Memory::Allocator::memory_size,MemoryAllocator");
				// 		m_allocator = pankey::Memory::Allocator::setMemoryAllocator(a_allocator);
				// 		this->create(a_pointer, a_length);
				// 		NoteLog(pankey_Log_EndMethod, "Contructor", "");
				// 	}

				// 	Note(const Note& a_charpointer){
				// 		NoteLog(pankey_Log_StartMethod, "Contructor", "const Note&");
				// 		m_allocator = pankey::Memory::Allocator::setMemoryAllocator(a_charpointer.m_allocator);
				// 		this->create(a_charpointer.m_pointer, a_charpointer.m_length);
				// 		NoteLog(pankey_Log_EndMethod, "Contructor", "");
				// 	}

				// 	Note(Note&& a_charpointer){
				// 		NoteLog(pankey_Log_StartMethod, "Contructor", "Note&&");
				// 		m_pointer = a_charpointer.m_pointer;
				// 		m_length = a_charpointer.m_length;
				// 		m_allocator = pankey::Memory::Allocator::setMemoryAllocator(a_charpointer.m_allocator);
				// 		a_charpointer.m_pointer = nullptr;
				// 		a_charpointer.m_length = 0;
				// 		pankey::Memory::Allocator::destroyMemoryAllocator(a_charpointer.m_allocator);
				// 		NoteLog(pankey_Log_EndMethod, "Contructor", "");
				// 	}

				// 	virtual ~Note(){
				// 		NoteLog(pankey_Log_StartMethod, "Destructor", "");
				// 		clear();
				// 		pankey::Memory::Allocator::destroyMemoryAllocator(m_allocator);
				// 		NoteLog(pankey_Log_EndMethod, "Destructor", "");
				// 	}

				// 	virtual void clear() override{
				// 		NoteLog(pankey_Log_StartMethod, "clear", "");
				// 		if(m_pointer == nullptr){
				// 			return;
				// 		}
				// 		pankey::Memory::Allocator::deallocateArray<char>(m_allocator, m_length + 1, m_pointer);
				// 		m_pointer = nullptr;
				// 		m_length = 0;
				// 		NoteLog(pankey_Log_EndMethod, "clear", "");
				// 	}

				// 	virtual void create(int a_length) override{
				// 		NoteLog(pankey_Log_StartMethod, "create", "");
				// 		clear();
				// 		m_pointer = pankey::Memory::Allocator::allocateArray<char>(m_allocator, a_length + 1);
				// 		if(m_pointer == nullptr){
				// 			NoteLog(pankey_Log_Error, "create", "m_pointer == nullptr");
				// 			NoteLog(pankey_Log_EndMethod, "create", "");
				// 			return;
				// 		}
				// 		m_length = a_length;
				// 		m_pointer[a_length] = '\0';
				// 		NoteLog(pankey_Log_EndMethod, "create", "");
				// 	}
					
				// protected:
				// 	pankey::Memory::Allocator::MemoryAllocator* m_allocator = nullptr;
			};

		}

	}

}