#include "hooks.h"
#include "../utilities/globals.h"

std::unique_ptr <vmt>   client_mode_hook;

void hooks::init() {

	global_utils::console_log("initialising hooks...");

	client_mode_hook = std::make_unique<vmt>(interfaces::client_mode);

	global_utils::console_log("hooks initialised, have fun!");

	client_mode_hook->hook(hooks::indexes::create_move, hooks::create_move_hook);
	client_mode_hook->hook(hooks::indexes::viewmodel_fov, hooks::viewmodel_fov_hook);

	interfaces::engine_client->unrestricted_client_cmd("clear");
	interfaces::engine_client->unrestricted_client_cmd("echo purpura sdk.");

}

void hooks::restore() {

	client_mode_hook->unhook(hooks::indexes::create_move);
	client_mode_hook->unhook(hooks::indexes::viewmodel_fov);

}

bool __fastcall hooks::create_move_hook(i_client_mode* thisptr, void* edx, float sample_frametime, c_usercmd* cmd) {

	static auto o_create_move = client_mode_hook->get_original<create_move_t>(hooks::indexes::create_move);
	o_create_move(thisptr, edx, sample_frametime, cmd);

	if( !interfaces::engine_client->in_game ( ) || !cmd || !cmd->command_number )
		return o_create_move;

	global_variables::global_cmd = cmd;

	global_utils::set_clantag ( "purpura", "purpura sdk" );

	return false;

}

float __stdcall hooks::viewmodel_fov_hook() {

	return 90.f;

}