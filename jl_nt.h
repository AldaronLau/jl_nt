#include "include/ntcore.h"
#include <dlfcn.h>
#include "jl.h"

typedef struct{
	jl_t* jlc;
	void* nt;
}jl_nt_t;

jl_nt_t* jl_nt_init(jl_t* jlc, str_t hostname);
void jl_nt_push_num(jl_nt_t* jl_nt, str_t name, f32_t value);
void jl_nt_push_bool(jl_nt_t* jl_nt, str_t name, u8_t value);
void jl_nt_push_data(jl_nt_t* jl_nt, str_t name, void* data,
	u32_t datasize);
f64_t jl_nt_pull_num(jl_nt_t* jl_nt, str_t name, f64_t set);
u8_t jl_nt_pull_bool(jl_nt_t* jl_nt, str_t name, u8_t set);
