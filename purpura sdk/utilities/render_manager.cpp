#include "render_manager.h"

namespace render_manager {

	namespace fonts {

		DWORD main_font;

	}

}

void render_manager::init ( ) {

	global_utils::console_log ( "initialising draw manager..." );

	fonts::main_font = interfaces::surface->create_font ( );
	interfaces::surface->set_font_glyph_set ( fonts::main_font, "Calibri", 14, 500, 0, 0, FONTFLAG_ANTIALIAS | FONTFLAG_OUTLINE );

	global_utils::console_log ( "draw manager initialised..." );

}

void render_manager::rect ( int x, int y, int w, int h, color color ) {

	interfaces::surface->draw_set_color ( color.r , color.g , color.b , color.a );
	interfaces::surface->draw_outline ( x, y, x + w, y + h );

}

void render_manager::filled_rect ( int x, int y, int w, int h, color color ) {

	interfaces::surface->draw_set_color ( color.r, color.g, color.b, color.a );
	interfaces::surface->draw_filled_rect ( x, y, x + w, y + h );

}

void render_manager::text(const char* text, int x, int y, int font, color color) {

	std::string text_normal = text;
	std::wstring text_wide = std::wstring(text_normal.begin(), text_normal.end());

	interfaces::surface->draw_set_text_color(color.r, color.g, color.b, color.a);
	interfaces::surface->draw_set_text_font(font);
	interfaces::surface->draw_set_text_pos(x, y);
	interfaces::surface->draw_print_text(text_wide.c_str(), text_wide.length(), FONT_DRAW_DEFAULT);

}

