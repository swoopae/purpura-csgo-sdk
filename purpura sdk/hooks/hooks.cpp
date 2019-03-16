#include "hooks.h"
#include "../utilities/globals.h"
#include "../utilities/render_manager.h"

std::unique_ptr <vmt>   client_mode_hook;
std::unique_ptr <vmt>   panel_hook;

void hooks::init() {

	global_utils::console_log("initialising hooks...");

	client_mode_hook = std::make_unique<vmt>( interfaces::client_mode );
	panel_hook = std::make_unique<vmt>( interfaces::panel );

	global_utils::console_log("hooks initialised, have fun!");

	client_mode_hook->hook ( hooks::indexes::create_move, hooks::create_move_hook );
	client_mode_hook->hook ( hooks::indexes::viewmodel_fov, hooks::viewmodel_fov_hook );
	panel_hook->hook ( hooks::indexes::paint_traverse, hooks::paint_traverse_hook );

	interfaces::engine_client->unrestricted_client_cmd ( "clear" );
	interfaces::engine_client->unrestricted_client_cmd ( "echo purpura sdk." );

}

void hooks::restore() {

	client_mode_hook->unhook ( hooks::indexes::create_move );
	client_mode_hook->unhook ( hooks::indexes::viewmodel_fov );

	panel_hook->unhook ( hooks::indexes::paint_traverse );

}

bool __fastcall hooks::create_move_hook ( i_client_mode* thisptr, void* edx, float sample_frametime, c_usercmd* cmd ) {

	static auto o_create_move = client_mode_hook->get_original<create_move_t>(hooks::indexes::create_move);

	o_create_move ( thisptr, edx, sample_frametime, cmd );
	
	if( !interfaces::engine_client->game_and_connect ( ) || !cmd || !cmd->command_number )
		return o_create_move;

	global_variables::global_cmd = cmd;

	cmd->buttons |= IN_BULLRUSH;

	global_utils::set_clantag ( "purpura", "purpura sdk" );

	return false;

}

float __stdcall hooks::viewmodel_fov_hook ( ) {

	return 120.f;

}

void __fastcall hooks::paint_traverse_hook ( PVOID p_panel, int edx, unsigned int vgui_panel, bool force_repaint, bool allow_force ) {

	static auto o_paint_traverse = panel_hook->get_original<paint_traverse_t>(hooks::indexes::paint_traverse);

	static unsigned int panel_hud_id, panel_id;

	if (!panel_hud_id)

		if (!strcmp("HudZoom", interfaces::panel->get_name(vgui_panel)))

			panel_hud_id = vgui_panel;

	o_paint_traverse ( p_panel, vgui_panel, force_repaint, allow_force );

	if (!panel_id)

		if (!strcmp("MatSystemTopPanel", interfaces::panel->get_name(vgui_panel)))

			panel_id = vgui_panel;

	if (panel_id == vgui_panel)
	{
		// draw shit here lmao
		render_manager::text ( "purpura sdk. // for sex having gamers" , 15, 15, render_manager::fonts::main_font, color ( 255,255,255,255 ) );
	}

}
