
#ifndef ArrayPointerHelper_hpp
	#define ArrayPointerHelper_hpp

	#include "ArrayPointer.hpp"
	#include "MultiArrayModel.hpp"

	#if defined(pankey_Log) && (defined(ArrayPointerHelper_Log) || defined(pankey_Global_Log) || defined(pankey_Base_Log))
		#include "Logger_status.hpp"
		#define ArrayPointerHelperLog(status,method,mns) pankey_Log(status,"ArrayPointerHelper",method,mns)
	#else
		#define ArrayPointerHelperLog(status,method,mns)
	#endif

	namespace pankey{

		namespace DataStructure{

			namespace Array{

				template<class Policy, class... Args>
				int isEqual(const ArrayPointer<Policy>& a_array, Args... a_args){
					// ArrayPointerHelperLog(pankey_Log_StartMethod, "getLengthUntil", "");
					// for(int x = 0; x < a_array.length(); x++){
					// 	T f_value = a_array.getFast(x);
					// 	if(f_value == a_end){
					// 		return x;
					// 	}
					// }
					// ArrayPointerHelperLog(pankey_Log_EndMethod, "getLengthUntil", "");
					return -1;
				}

				template<class Policy>
				int getLengthUntil(const ArrayPointer<Policy>& a_array, typename Policy::VALUE_TYPE a_end){
					ArrayPointerHelperLog(pankey_Log_StartMethod, "getLengthUntil", "");
					for(int x = 0; x < a_array.length(); x++){
						typename Policy::VALUE_TYPE f_value = a_array.getFast(x);
						if(f_value == a_end){
							return x;
						}
					}
					ArrayPointerHelperLog(pankey_Log_EndMethod, "getLengthUntil", "");
					return -1;
				}

				template<class Policy>
				ArrayPointer<MultiArrayModel<Policy>> split(const ArrayPointer<Policy>& a_array, typename Policy::VALUE_TYPE a_split){
					ArrayPointerHelperLog(pankey_Log_StartMethod, "split", "");
					ArrayPointer<MultiArrayModel<Policy>> i_parts;
					if(a_array.isEmpty()){
						ArrayPointerHelperLog(pankey_Log_EndMethod, "split", "");
						return i_parts;
					}
					ArrayPointer<Policy> i_capture;
					for(int x = 0; x < a_array.length(); x++){
						typename Policy::VALUE_TYPE f_value = a_array.getFast(x);
						if(f_value == a_split){
							i_parts.add(i_capture);
							i_capture.clear();
							continue;
						}
						i_capture.add(f_value);
					}
					if(!i_capture.isEmpty()){
						i_parts.add(i_capture);
					}
					ArrayPointerHelperLog(pankey_Log_EndMethod, "split", "");
					return i_parts;
				}

			}
		}
	}

#endif



