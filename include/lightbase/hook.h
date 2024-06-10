#pragma once

#ifdef __cplusplus
extern "C" {
#endif

void *lb_ahook_install(void **in_target_addr, void *in_hook_addr, void **out_handle);
void *lb_shook_install(const char *in_sym, void *in_hook_addr, void **out_handle);
void lb_hook_uninstall(const char *in_sym, void *in_handle);

#ifdef __cplusplus
}
#endif

#define SHOOK(name, ret_type, sym, ...)                             \
	void lb_hook_##name##_install();                                \
	void lb_hook_##name##_uninstall();                              \
	void lb_hook_##name##_destory();                                \
	ret_type lb_hook_##name##_hook(__VA_ARGS__);                    \
                                                                    \
	struct lb_hook_##name {                                         \
		void *handle;                                               \
		void (*install)();                                          \
		void (*uninstall)();                                        \
		ret_type (*call)(__VA_ARGS__);                              \
		ret_type (*hook)(__VA_ARGS__);                              \
	} name = { NULL,                                                \
			   lb_hook_##name##_install,                            \
			   lb_hook_##name##_uninstall,                          \
			   NULL,                                                \
			   lb_hook_##name##_hook };                             \
                                                                    \
	void lb_hook_##name##_install()                                 \
	{                                                               \
		name.call = lb_shook_install(sym, name.hook, &name.handle); \
	}                                                               \
	void lb_hook_##name##_uninstall()                               \
	{                                                               \
		lb_hook_uninstall(sym, name.handle);                        \
	}                                                               \
	ret_type lb_hook_##name##_hook(__VA_ARGS__)

#define AHOOK(name, ret_type, addr, ...)                                     \
	void lb_hook_##name##_install();                                         \
	void lb_hook_##name##_uninstall();                                       \
	void lb_hook_##name##_destory();                                         \
	ret_type lb_hook_##name##_hook(__VA_ARGS__);                             \
                                                                             \
	struct lb_hook_##name {                                                  \
		void *handle;                                                        \
		void (*install)();                                                   \
		void (*uninstall)();                                                 \
		ret_type (*call)(__VA_ARGS__);                                       \
		ret_type (*hook)(__VA_ARGS__);                                       \
	} name = { NULL,                                                         \
			   lb_hook_##name##_install,                                     \
			   lb_hook_##name##_uninstall,                                   \
			   NULL,                                                         \
			   lb_hook_##name##_hook };                                      \
	void lb_hook_##name##_install()                                          \
                                                                             \
	{                                                                        \
		name.call = lb_ahook_install((void *)addr, name.hook, &name.handle); \
	}                                                                        \
	void lb_hook_##name##_uninstall()                                        \
	{                                                                        \
		lb_hook_uninstall(#addr, name.handle);                               \
	}                                                                        \
	ret_type lb_hook_##name##_hook(__VA_ARGS__)
