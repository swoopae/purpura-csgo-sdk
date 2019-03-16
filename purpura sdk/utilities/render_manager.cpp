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


void render_manager::text ( const char* text, int x, int y, int font, color color ) {

	char buffer[1024] = { '\0' };
	va_list arguments;

	va_start ( arguments, text );
	vsprintf_s ( buffer, text, arguments );
	va_end ( arguments );

	size_t size_nigga = strlen ( buffer ) + 1;

	wchar_t* wide_buffer = new wchar_t [ size_nigga ];
	mbstowcs_s ( 0, wide_buffer, size_nigga, buffer, size_nigga - 1 );

	interfaces::surface->draw_set_text_color ( color.r, color.g, color.b, color.a );
	interfaces::surface->draw_set_text_font ( font );
	interfaces::surface->draw_set_text_pos ( x, y );
	interfaces::surface->draw_print_text ( wide_buffer, size_nigga, FONT_DRAW_DEFAULT );

}