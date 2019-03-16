#pragma once

#include "i_client_entity.h"

class i_client_mode {

public:
	bool should_draw_entity(i_client_entity *p_entity) {

		typedef bool(__thiscall *o_fn)(void*, i_client_entity*);
		return global_utils::v_function<o_fn>(this, 14)(this, p_entity);

	}
};