#include "utilities.h"

typedef void* ( *create_interface_fn ) ( const char *name, int *return_code );

void* global_utils::find_interface ( const char* module, const char* interface_name ) {

	void* interf = nullptr;
	auto create_interface = reinterpret_cast<create_interface_fn>(GetProcAddress(GetModuleHandleA(module), "CreateInterface"));

	char possible_interface_name[1024];
	for ( int i = 1; i < 100; i ++ )
	{
		sprintf(possible_interface_name, "%s0%i", interface_name, i);
		interf = create_interface(possible_interface_name, 0);
		if (interf)
			break;

		sprintf(possible_interface_name, "%s00%i", interface_name, i);
		interf = create_interface(possible_interface_name, 0);
		if (interf)
			break;
	}

	return interf;

}