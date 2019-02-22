#include <Windows.h>
#include <iostream>
#include <thread>

#include "utilities/utilities.h"
#include "interfaces/interfaces.h"
#include "hooks/hooks.h"

VOID WINAPI setup_debug_console ( ) {

	AllocConsole();
	
	freopen_s((FILE**)stdin, "CONIN$", "r", stdin);
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
	
	SetConsoleTitleA( "[purpura sdk] console: " );

}

VOID WINAPI dll_setup ( HINSTANCE module_handle ) {

	DisableThreadLibraryCalls ( module_handle );
	setup_debug_console ( );

	global_utils::console_log ( "purpura console loaded." );
	
	interfaces::init ( );
	hooks::init ( );

	while ( true ) {

		using namespace std::literals::chrono_literals;
		std::this_thread::sleep_for(1s);

		/// - Low priority -
		/// TODO: Make key customizable like properly, for now this will do though.

		if ( GetAsyncKeyState ( VK_DELETE ) ) {

			fclose( ( FILE* ) stdin );
			fclose( ( FILE* ) stdout );
			
			HWND hw_ConsoleHwnd = GetConsoleWindow();
			
			FreeConsole( );
			PostMessageW( hw_ConsoleHwnd, WM_CLOSE, 0, 0 );
			
			hooks::restore ( );
			
			FreeLibraryAndExitThread( module_handle, 1 );

		}
	}
}

BOOL APIENTRY DllMain( HMODULE module, DWORD  reason_for_call, LPVOID reserved ) {

    switch ( reason_for_call ) {

    case DLL_PROCESS_ATTACH:

		dll_setup ( module );
		break;

    }

    return TRUE;

}