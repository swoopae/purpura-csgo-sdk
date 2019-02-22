#pragma once

// fix this

typedef void * (*o_interface_t) (const char *pName, int *pReturnCode);

class i_app_system {
public:
	virtual bool Connect(o_interface_t factory) = 0;                                // 0
	virtual void Disconnect() = 0;                                                      // 1
	virtual void* QueryInterface(const char* pInterfaceName) = 0;                       // 2
	virtual int /*InitReturnVal_t*/ Init() = 0;                                         // 3
	virtual void Shutdown() = 0;                                                        // 4
	virtual const void* /*AppSystemInfo_t*/ GetDependencies() = 0;                      // 5
	virtual int /*AppSystemTier_t*/ GetTier() = 0;                                      // 6
	virtual void Reconnect(o_interface_t factory, const char* pInterfaceName) = 0;  // 7
	virtual void UnkFunc() = 0;                                                         // 8
};