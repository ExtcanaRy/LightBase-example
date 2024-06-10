#include <stdio.h>
#include <stdarg.h>

#include <lightbase/hook.h>
#include <lightbase/symbol.h>

#ifdef _WIN32
#include <Windows.h>
#endif

#ifdef __linux__
__attribute__((constructor)) void load();
#endif

#ifdef __linux__
#define hook_respawn "_ZN6Player7respawnEv"
#define call_logger "_ZN10BedrockLog6log_vaENS_11LogCategoryENSt3__16bitsetILm3EEENS_7LogRuleE9LogAreaIDjPKciS7_P13__va_list_tag"
#endif

#ifdef _WIN32
#define hook_respawn "?respawn@Player@@UEAAXXZ"
#define call_logger "?log_va@BedrockLog@@YAXW4LogCategory@1@V?$bitset@$02@std@@W4LogRule@1@W4LogAreaID@@IPEBDH4PEAD@Z"
#endif

enum log_level {
	LOG_LEVEL_TRACE = 6u,
	LOG_LEVEL_INFO = 2u,
	LOG_LEVEL_WARN = 4u,
	LOG_LEVEL_ERR = 8u
};

void server_logger(enum log_level level, const char *msg, ...)
{
	va_list va;
	va_start(va, msg);

	// symbol call
	SCALL(call_logger,
		  char (*)(unsigned int category, char set, int rule, int area, unsigned int level, const char *tag, int tid, const char *format, va_list args),
		  0, 1, 0x0d00, 0, level, "私のオナニーを見てください！", 0x0721, msg, va);

	va_end(va);
}

SHOOK(on_player_spawn, void *, hook_respawn, void *p)
{
	void *ret = on_player_spawn.call(p); // call origin func

	printf("-------- HOOK START --------\n");
	printf("Player Respawn!!!!!!!!!!!!!!!!!! @ 1.20.81.01!\n");
	printf("Server Version @ 1.20.81.01!\n");
	printf("Server Version @ 1.20.81.01!!\n");
	printf("Server Version @ 1.20.81.01!!!\n");
	printf("Server Version @ 1.20.81.01!!!!\n");
	printf("Server Version @ 1.20.81.01!!!!!\n");
	printf("-------- HOOK END --------\n");

	server_logger(LOG_LEVEL_INFO, "CALL TEST\n");
	server_logger(LOG_LEVEL_INFO, "CALL TEST\n");
	server_logger(LOG_LEVEL_INFO, "CALL TEST\n");
	server_logger(LOG_LEVEL_INFO, "CALL TEST\n");
	server_logger(LOG_LEVEL_INFO, "CALL TEST\n");
	server_logger(LOG_LEVEL_INFO, "CALL TEST\n");
	server_logger(LOG_LEVEL_INFO, "CALL TEST\n");
	server_logger(LOG_LEVEL_INFO, "CALL TEST\n");
	server_logger(LOG_LEVEL_INFO, "CALL TEST\n");
	server_logger(LOG_LEVEL_INFO, "CALL TEST\n");
	server_logger(LOG_LEVEL_INFO, "CALL TEST\n");

	on_player_spawn.uninstall(); // uninstall hook

	return ret;
}

void load()
{
	on_player_spawn.install();
}

#ifdef _WIN32
BOOL APIENTRY DllMain(HMODULE hModule,
					  DWORD ul_reason_for_call,
					  LPVOID lpReserved)
{
	switch (ul_reason_for_call) {
		case DLL_PROCESS_ATTACH:
			load();
			break;
		case DLL_THREAD_ATTACH:
			break;
		case DLL_THREAD_DETACH:
			break;
		case DLL_PROCESS_DETACH:
			break;
	}
	return TRUE;
}
#endif
