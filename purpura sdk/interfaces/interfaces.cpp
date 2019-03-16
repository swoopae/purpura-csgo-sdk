#include "interfaces.h"
#include "../utilities/utilities.h"

namespace interfaces {

	iv_engine_client*     engine_client    = nullptr;
	i_surface*            surface          = nullptr;
	i_base_client_dll*    client           = nullptr;
	i_client_mode*        client_mode      = nullptr;
	i_panel*              panel            = nullptr; 
	c_global_vars*        global_vars      = nullptr;

	void interfaces::init ( ) {

		global_utils::console_log("trying to get interfaces...");

		engine_client   = global_utils::get_interface <iv_engine_client> ( ( char* ) "engine.dll", ( char* ) "VEngineClient014" );
		surface         = global_utils::get_interface <i_surface> ( ( char* ) "vguimatsurface.dll", ( char* ) "VGUI_Surface031" ); 
		client          = global_utils::get_interface <i_base_client_dll> ( ( char* ) "client_panorama.dll", ( char* ) "VClient018" );
		panel			= reinterpret_cast < i_panel* > ( global_utils::find_interface ( "vgui2.dll", "VGUI_Panel" ) );

		client_mode     = **(i_client_mode***)((*(DWORD**)client)[10] + 0x5);
		global_vars     = **reinterpret_cast<c_global_vars***>((*reinterpret_cast<uintptr_t**>(client))[0] + 0x1Bu);

		global_utils::console_log("got all interfaces...");

	}
}