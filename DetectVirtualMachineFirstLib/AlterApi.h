#pragma once
#include <malloc.h>
#include "struct.h"
#ifdef _M_AMD64
#include <intrin.h>
#elif defined(_M_ARM)
#include <armintr.h>
#endif



int virtualCheckSecuretyEngine = 0;

namespace alternanit_api
{

	template <typename str_type>
	inline  int str_length(str_type string) {
		int result = 0;
		for (int i = 0; string[i] != '\0'; result++, i++)
		{

		}
		return result;
	}


	inline wchar_t* CharToWChar_T(char* str) {
		int length = str_length(str);

		if (str == nullptr) {
			return nullptr;
		}

		wchar_t* wstr_t = (wchar_t*)malloc(sizeof(wchar_t) * length + 2);

		for (int i = 0; i < length; i++) {
			wstr_t[i] = str[i];
		}
		wstr_t[length] = '\0';
		return wstr_t;
	}


	inline wchar_t ToLowerW(wchar_t ch) {
		if (ch > 0x40 && ch < 0x5B) {
			return ch + 0x20;
		}
		return ch;
	}


	inline char ToLowerA(char ch) {
		if (ch > 96 && ch < 123) {
			ch -= 32;
		}
		return ch;
	}



	

}







