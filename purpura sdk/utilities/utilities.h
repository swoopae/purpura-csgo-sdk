#pragma once

#include <Windows.h>
#include <iostream>
#include <string>
#include <cmath>
#include <Psapi.h>
#include <iomanip>
#include <ctime>
#include <chrono>

#include "vmatrix.h"

#define in_range(x,a,b)   (x >= a && x <= b)

#define get_bits( x )    (in_range((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (in_range(x,'0','9') ? x - '0' : 0))
#define get_byte( x )    (get_bits(x[0]) << 4 | get_bits(x[1]))

namespace global_utils {

	template <typename T>
	static T* get_interface(char* szModule, char* szInterface) {

		typedef void * (*o_interface_t)(char*, int);
		o_interface_t original = (o_interface_t)GetProcAddress(GetModuleHandleA(szModule), "CreateInterface");

		return (T*)original(szInterface, 0);

	}

	static uintptr_t get_signature(const char* szModule, const char* szSignature) 
	{
		const char* pat = szSignature;
		DWORD firstMatch = 0;
		DWORD rangeStart = (DWORD)GetModuleHandleA(szModule);
		MODULEINFO miModInfo;
		GetModuleInformation(GetCurrentProcess(), (HMODULE)rangeStart, &miModInfo, sizeof(MODULEINFO));
		DWORD rangeEnd = rangeStart + miModInfo.SizeOfImage;
		for (DWORD pCur = rangeStart; pCur < rangeEnd; pCur++)
		{
			if (!*pat)
				return firstMatch;

			if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == get_byte(pat))
			{
				if (!firstMatch)
					firstMatch = pCur;

				if (!pat[2])
					return firstMatch;

				if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
					pat += 3;

				else
					pat += 2;
			}
			else
			{
				pat = szSignature;
				firstMatch = 0;
			}
		}
		return NULL;

	}

	static void console_log(const std::string& szOutput) {

		std::cout << "[log:] " << szOutput << "\n";

	}

	static void console_warn(const std::string& szOutput) {

		std::cout << "[warning:] " << szOutput << "\n";

	}

	static void console_error(const std::string& szOutput) {

		std::cout << "[ERROR:] " << szOutput << "\n";

	}

	template <typename T>
	static T v_function(void* pClass, int iIndex) {

		PDWORD p_vtable = *(PDWORD*)pClass;
		DWORD dw_address = p_vtable[iIndex];

		return (T)(dw_address);

	}

	static void set_clantag(const char* tag, const char* name) {

		static auto p_set_clantag = reinterpret_cast<void(__fastcall*)(const char*, const char*)>((DWORD)(global_utils::get_signature("engine.dll", "53 56 57 8B DA 8B F9 FF 15")));
		p_set_clantag(tag, name);

	}
	/// - High priority -
	/// TODO: Write a netvar manager.
}