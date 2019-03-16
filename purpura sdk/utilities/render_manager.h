#pragma once

#include "vector.h" // i don't know why i include "vector.h" but i'm not going to remove it this commit, i really don't want it to break some shit

#include "../interfaces/interfaces.h"

namespace render_manager {

	namespace fonts {

		extern DWORD main_font;

	}

	void init ( );
	void rect ( int x, int y, int w, int h, color color );
	void filled_rect ( int x, int y, int w, int h, color color );
	void text ( const char *text, int x, int y, int font, color color );

}