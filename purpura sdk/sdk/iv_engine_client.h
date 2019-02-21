#pragma once

#include "../utilities/utilities.h"

class iv_engine_client {

public:

	void screen_size ( int& width, int& height ) {

		typedef int(__thiscall *o_fn)(void*, int&, int&);
		global_utils::v_function<o_fn>( this, 5 )( this, width, height );

	}

	int get_localplayer ( ) {

		typedef int(__thiscall *o_fn)(void*);
		return global_utils::v_function<o_fn>(this, 12)(this);

	}
	/*
	*

	VMatrix& w2s_matrix ( ) {

		typedef VMatrix&(__thiscall *OrigFn)(void*);
		return Aniware::Utilities::VirtualFunction <OrigFn>(this, 37)(this);

	}

	*
	*/

	float last_timestamp ( ) {

		typedef float(__thiscall *o_fn)(void*);
		return global_utils::v_function<o_fn>(this, 14)(this);

	}

	int get_max_clients ( ) {

		typedef int(__thiscall *o_fn)(void*);
		return global_utils::v_function<o_fn>(this, 20)(this);

	}

	bool in_game ( ) {

		typedef int(__thiscall *o_fn)(void*);
		return global_utils::v_function<o_fn>(this, 26)(this);

	}

	bool connected ( ) {

		typedef int(__thiscall *o_fn)(void*);
		return global_utils::v_function<o_fn>(this, 27)(this);

	}

	bool game_and_connect ( ) {

		if ( this->connected( ) && this->in_game( ) )
			return true; //big brain
		return false;

	}

	void client_cmd ( const char* szCmdString ) {

		typedef void(__thiscall *o_fn)(void*, const char *);
		return global_utils::v_function<o_fn>(this, 108)(this, szCmdString);

	}

	void unrestricted_client_cmd ( const char* szCmdString ) {

		typedef void(__thiscall* o_fn)(void*, const char*, char);
		return global_utils::v_function<o_fn>(this, 114)(this, szCmdString, 1);

	}

};