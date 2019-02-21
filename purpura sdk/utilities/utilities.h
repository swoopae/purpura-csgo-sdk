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

		PDWORD pVTable = *(PDWORD*)pClass;
		DWORD dwAddress = pVTable[iIndex];

		return (T)(dwAddress);

	}

	static bool w2s(const vec3_t &origin, vec2_t &screen)
	{
		// stolen from antario i think? i dont remember
		const auto screenTransform = [&origin, &screen]() -> bool
		{
			static std::uintptr_t pViewMatrix;
			if (!pViewMatrix)
			{
				pViewMatrix = static_cast<std::uintptr_t>(global_utils::get_signature("client_panorama.dll", "0F 10 05 ? ? ? ? 8D 85 ? ? ? ? B9"));
				pViewMatrix += 3;
				pViewMatrix = *reinterpret_cast<std::uintptr_t*>(pViewMatrix);
				pViewMatrix += 176;
			}

			const VMatrix& w2sMatrix = *reinterpret_cast<VMatrix*>(pViewMatrix);
			screen.x = w2sMatrix.m[0][0] * origin.x + w2sMatrix.m[0][1] * origin.y + w2sMatrix.m[0][2] * origin.z + w2sMatrix.m[0][3];
			screen.y = w2sMatrix.m[1][0] * origin.x + w2sMatrix.m[1][1] * origin.y + w2sMatrix.m[1][2] * origin.z + w2sMatrix.m[1][3];

			float w = w2sMatrix.m[3][0] * origin.x + w2sMatrix.m[3][1] * origin.y + w2sMatrix.m[3][2] * origin.z + w2sMatrix.m[3][3];

			if (w < 0.001f)
			{
				screen.x *= 100000;
				screen.y *= 100000;
				return true;
			}

			float invw = 1.f / w;
			screen.x *= invw;
			screen.y *= invw;

			return false;
		};

		if (!screenTransform())
		{
			int s_width, s_height;
			interfaces::engine_client->screen_size(s_width, s_height);

			screen.x = (s_width * 0.5f) + (screen.x * s_width) * 0.5f;
			screen.y = (s_height * 0.5f) - (screen.y * s_height) * 0.5f;

			return true;
		}
		return false;
	}

	/// - High priority -
	/// TODO: Write a netvar manager.
}