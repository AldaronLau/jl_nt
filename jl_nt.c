#include "jl_nt.h"

/*static inline void jl_nt_loadnt(jl_nt_t* jl_nt) {
	if(!(jl_nt->nt = dlopen("libnt.so", RTLD_NOW | RTLD_GLOBAL))) {
		jl_io_print(jl_nt->jlc, "failed to load .so");
		jl_io_print(jl_nt->jlc, "%s", dlerror());
		jl_sg_exit(jl_nt->jlc);
	}
}*/

jl_nt_t* jl_nt_init(jl_t* jlc, str_t hostname) {
	jl_nt_t* jl_nt = jl_memi(jlc, sizeof(jl_nt_t));
	jl_nt->jlc = jlc;
	// Load the library
	// jl_nt_loadnt(jl_nt);
	// Start client
	NT_StartClient(hostname, 1735);
	return jl_nt;
}

void jl_nt_push_num(jl_nt_t* jl_nt, str_t name, f32_t value) {
	NT_SetEntryDouble(name, strlen(name), value, 1);
}

void jl_nt_push_bool(jl_nt_t* jl_nt, str_t name, u8_t value) {
	NT_SetEntryBoolean(name, strlen(name), value, 1);
}

void jl_nt_push_data(jl_nt_t* jl_nt, str_t name, void* data,
	u32_t datasize)
{
	NT_SetEntryRaw(name, strlen(name), data, datasize, 1);
}

f64_t jl_nt_get_num(jl_nt_t* jl_nt, str_t name) {
	double rtn = 0.;
	unsigned long long last_change; // How defined in network tables.
	if(NT_GetEntryDouble(name, strlen(name), &last_change, &rtn)) {
		return rtn;
	}else{
		return rtn;
	}
}

f64_t jl_nt_pull_num(jl_nt_t* jl_nt, str_t name, f64_t set) {
	double rtn;
	unsigned long long last_change; // How defined in network tables.
	if(NT_GetEntryDouble(name, strlen(name), &last_change, &rtn)) {
		return rtn;
	}else{
		jl_nt_push_num(jl_nt, name, set);
		return set;
	}
}

u8_t jl_nt_pull_bool(jl_nt_t* jl_nt, str_t name, u8_t set) {
	int rtn;
	unsigned long long last_change; // How defined in network tables.
	if(NT_GetEntryBoolean(name, strlen(name), &last_change, &rtn)) {
		return rtn;
	}else{
		jl_nt_push_bool(jl_nt, name, set);
		return set;
	}
}

void jl_nt_kill(jl_nt_t* jl_nt) {
	NT_StopClient();
//	dlclose(jl_nt->nt);
}
