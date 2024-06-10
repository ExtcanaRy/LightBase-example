#pragma once

enum lb_log_level {
	LEVEL_ERROR,
	LEVEL_WARN,
	LEVEL_INFO,
	LEVEL_DEBUG,
	LEVEL_TRACE
};

#define LOADER_NAME "LightBase"
#define PLUGIN_DIR "plugins/"

int lb_preinit_logger(int in_level, const char *in_fmt, ...);