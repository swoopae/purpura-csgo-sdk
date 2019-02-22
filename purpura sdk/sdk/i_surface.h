#pragma once

#include "../utilities/utilities.h"

enum font_feature {

	FONT_FEATURE_ANTIALIASED_FONTS = 1, FONT_FEATURE_DROPSHADOW_FONTS = 2, FONT_FEATURE_OUTLINE_FONTS = 6

};

enum font_draw_type {

	FONT_DRAW_DEFAULT = 0, FONT_DRAW_NONADDITIVE, FONT_DRAW_ADDITIVE, FONT_DRAW_TYPE_COUNT = 2

};

enum font_flags {

	FONTFLAG_NONE,
	FONTFLAG_ITALIC = 0x001,
	FONTFLAG_UNDERLINE = 0x002,
	FONTFLAG_STRIKEOUT = 0x004,
	FONTFLAG_SYMBOL = 0x008,
	FONTFLAG_ANTIALIAS = 0x010,
	FONTFLAG_GAUSSIANBLUR = 0x020,
	FONTFLAG_ROTARY = 0x040,
	FONTFLAG_DROPSHADOW = 0x080,
	FONTFLAG_ADDITIVE = 0x100,
	FONTFLAG_OUTLINE = 0x200,
	FONTFLAG_CUSTOM = 0x400,
	FONTFLAG_BITMAP = 0x800

};

class color {

public:

	float r, g, b, a;

	color(float red, float green, float blue, float alpha) {

		r = red, g = green, b = blue, a = alpha;

	}

	color(float red, float green, float blue) {

		r = red, g = green, b = blue, a = 255.f;

	}
};

class i_surface {

public:

	void draw_set_color(color col) {

		typedef void(__thiscall *o_fn)(void*, color);
		return global_utils::v_function<o_fn>(this, 14)(this, col);

	}

	void draw_filled_rect(int x0, int y0, int x1, int y1) {

		typedef void(__thiscall *o_fn)(void*, int, int, int, int);
		return global_utils::v_function<o_fn>(this, 16)(this, x0, y0, x1, y1);

	}

	void draw_fancy_rect(int x0, int y0, int x1, int y1) { // outlined rect, that is

		typedef void(__thiscall *o_fn)(void*, int, int, int, int);
		return global_utils::v_function<o_fn>(this, 18)(this, x0, y0, x1, y1);

	}
};