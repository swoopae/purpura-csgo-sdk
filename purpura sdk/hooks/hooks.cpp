#include "hooks.h"

std::unique_ptr <vmt>   client_mode_hook;

void hooks::init() {

	global_utils::console_log("initialising hooks...");

	client_mode_hook = std::make_unique<vmt>(interfaces::client_mode);

	global_utils::console_log("hooks initialised, have fun!");

	client_mode_hook->hook(hooks::indexes::create_move, hooks::create_move_hook);
	client_mode_hook->hook(hooks::indexes::viewmodel_fov, hooks::viewmodel_fov_hook);

	interfaces::engine_client->unrestricted_client_cmd("clear");
	interfaces::engine_client->unrestricted_client_cmd("echo purpura sdk.");\
}

static void set_clantag(const char* tag, const char* name) {
	static auto p_set_clantag = reinterpret_cast<void(__fastcall*)(const char*, const char*)>((DWORD)(global_utils::get_signature("engine.dll", "53 56 57 8B DA 8B F9 FF 15")));
	p_set_clantag(tag, name);
}

void hooks::restore() {
	client_mode_hook->unhook(hooks::indexes::create_move);
	client_mode_hook->unhook(hooks::indexes::viewmodel_fov);
}

bool __fastcall hooks::create_move_hook(i_client_mode* thisptr, void* edx, float sample_frametime, c_usercmd* cmd) {
	static auto o_create_move = client_mode_hook->get_original<create_move_t>(hooks::indexes::create_move);
	o_create_move(thisptr, edx, sample_frametime, cmd);

	set_clantag("tag", "name");

	return false;
}

float __stdcall hooks::viewmodel_fov_hook() {
	return 90.f;
}