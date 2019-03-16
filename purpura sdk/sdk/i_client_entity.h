#pragma once

class i_base_client_dll {

};

class i_client_entity {

public:
	int entity_index() {

		void *nigga_toilet = (void*)(this + 0x8);

		typedef int(__thiscall *o_fn)(void*);
		return global_utils::v_function<o_fn>(nigga_toilet, 10)(nigga_toilet); // yeah i was bored

	}
};