#pragma once

#include "../sdk/i_surface.h"
#include "../sdk/i_panel.h"
#include "../sdk/iv_engine_client.h"
#include "../sdk/i_client_mode.h"
#include "../sdk/i_client_entity.h"
#include "../sdk/c_global_vars.h"

namespace interfaces {
	extern iv_engine_client* engine_client;
	extern i_surface* surface;
	extern i_panel* panel;
	extern i_base_client_dll* client;
	extern i_client_mode* client_mode;
	extern c_global_vars* global_vars;

	void init ( );
}