#pragma once

#include "../utilities/vmt.h"
#include "../interfaces/interfaces.h"

#include "../sdk/c_input.h"

namespace hooks {
	enum indexes {
		create_move = 24,
		viewmodel_fov = 35,
	};

	void init();
	void restore();

	// hooked functions
	static bool     __fastcall  create_move_hook(i_client_mode*, void*, float, c_usercmd*);
	static float    __stdcall   viewmodel_fov_hook();

	// hook prototypes
	typedef bool(__fastcall* create_move_t) (i_client_mode*, void*, float, c_usercmd*);
}