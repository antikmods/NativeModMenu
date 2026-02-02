#ifndef ANDROID_MOD_MENU_MACROS_H
#define ANDROID_MOD_MENU_MACROS_H

#include <dlfcn.h>
#include <map>
#include <string>
#include <cstdint>


#include "Logger.h"


void hook(void *offset, void *ptr, void **orig) {
#if defined(__aarch64__)
    A64HookFunction(offset, ptr, orig);
#else
    MSHookFunction(offset, ptr, orig);
#endif
}


#if defined(__aarch64__)

#include <And64InlineHook/And64InlineHook.hpp>

#define HOOK(offset, ptr, orig) \
A64HookFunction((void*)getAbsoluteAddress(targetLibName, string2Offset(OBFUSCATE(offset))), \
                (void*)ptr, (void**)&orig)

#define HOOK_LIB(lib, offset, ptr, orig) \
A64HookFunction((void*)getAbsoluteAddress(OBFUSCATE(lib), string2Offset(OBFUSCATE(offset))), \
                (void*)ptr, (void**)&orig)

#define HOOK_NO_ORIG(offset, ptr) \
A64HookFunction((void*)getAbsoluteAddress(targetLibName, string2Offset(OBFUSCATE(offset))), \
                (void*)ptr, nullptr)

#define HOOKSYM(sym, ptr, orig) \
A64HookFunction(dlsym(dlopen(targetLibName, RTLD_NOW), OBFUSCATE(sym)), \
                (void*)ptr, (void**)&orig)

#define HOOKSYM_NO_ORIG(sym, ptr) \
A64HookFunction(dlsym(dlopen(targetLibName, RTLD_NOW), OBFUSCATE(sym)), \
                (void*)ptr, nullptr)

#else
#include <Substrate/SubstrateHook.h>
#include <Substrate/CydiaSubstrate.h>

#define HOOK(offset, ptr, orig) \
MSHookFunction((void*)getAbsoluteAddress(targetLibName, string2Offset(OBFUSCATE(offset))), \
               (void*)ptr, (void**)&orig)

#define HOOK_LIB(lib, offset, ptr, orig) \
MSHookFunction((void*)getAbsoluteAddress(OBFUSCATE(lib), string2Offset(OBFUSCATE(offset))), \
               (void*)ptr, (void**)&orig)

#define HOOK_NO_ORIG(offset, ptr) \
MSHookFunction((void*)getAbsoluteAddress(targetLibName, string2Offset(OBFUSCATE(offset))), \
               (void*)ptr, nullptr)

#define HOOKSYM(sym, ptr, orig) \
MSHookFunction(dlsym(dlopen(targetLibName, RTLD_NOW), OBFUSCATE(sym)), \
               (void*)ptr, (void**)&orig)

#define HOOKSYM_NO_ORIG(sym, ptr) \
MSHookFunction(dlsym(dlopen(targetLibName, RTLD_NOW), OBFUSCATE(sym)), \
               (void*)ptr, nullptr)

#endif


#define OBFUSCATEOFFSET(str) string2Offset(OBFUSCATE(str))


inline void patchOffset(const char *lib, uint64_t offset, const std::string &hex) {
    MemoryPatch patch = MemoryPatch::createWithHex(lib, offset, hex);
    if (!patch.isValid()) {
        LOGE("Invalid patch offset: 0x%llX", offset);
        return;
    }
    patch.Modify();
}

inline void patchOffset(uint64_t offset, const std::string &hex) {
    patchOffset(targetLibName, offset, hex);
}

#define PATCHOFFSET(offset, hex) \
patchOffset(string2Offset(OBFUSCATE(offset)), OBFUSCATE(hex))

#define PATCHOFFSET_LIB(lib, offset, hex) \
patchOffset(OBFUSCATE(lib), string2Offset(OBFUSCATE(offset)), OBFUSCATE(hex))


inline void patchOffsetSym(uintptr_t addr,
                           const std::string &hex,
                           bool enable) {
    static std::map<uintptr_t, MemoryPatch> patchMap;

    if (!addr) {
        LOGE("patchOffsetSym: NULL address");
        return;
    }

    if (!patchMap.count(addr)) {
        patchMap[addr] = MemoryPatch::createWithHex(addr, hex);
    }

    MemoryPatch &patch = patchMap[addr];

    if (!patch.isValid()) {
        LOGE("patchOffsetSym: invalid patch at %p", (void*)addr);
        return;
    }

    if (enable) {
        patch.Modify();
    } else {
        patch.Restore();
    }
}


#define PATCH_SYM_SWITCH(sym, hex, state) \
patchOffsetSym((uintptr_t)dlsym(dlopen(targetLibName, RTLD_NOW), OBFUSCATE(sym)), \
               OBFUSCATE(hex), state)

#define PATCH_LIB_SYM_SWITCH(lib, sym, hex, state) \
patchOffsetSym((uintptr_t)dlsym(dlopen(OBFUSCATE(lib), RTLD_NOW), OBFUSCATE(sym)), \
               OBFUSCATE(hex), state)

#endif // ANDROID_MOD_MENU_MACROS_H
