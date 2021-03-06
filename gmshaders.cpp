#include <cstddef>
#include <Windows.h>

#include <color.h>
#include <icvar.h> // need this to print all kinds of stuff to the console because ConMsg from dbg.h doesnt work bruh
#include <interface.h> // Sys_LoadInterface etc
#include <materialsystem\IShader.h>

#include "detours\detours.h"
#include "SymbolFinder\symbolfinder.hpp"
#include "Shaders\lensflare.hpp"

#include "platform.hpp"

#if GCC
#	define _DllExport extern "C" _DECLSPEC(dllexport)
#else
#	define _DllExport extern "C" _ATTRIBUTE(visibility("default"))
#endif

class IShaderDLLInternal
{
public:
	virtual bool Connect(CreateInterfaceFn factory, bool bIsMaterialSystem = false) = 0;
	virtual void Disconnect(bool bIsMaterialSystem = false) = 0;
};
IShaderDLLInternal* GetShaderDLLInternal();

constexpr SymbolSig g_FindShaderSig = { "\x55\x8B\xEC\x51\x8B\xC1\x53\x56\x57\x8B\x70\x14", "xxxxxxxxxxxx" };

using FindShaderFn = IShader* (_THISCALL*)(void*, const char*);
FindShaderFn FindShader;
IShader* _FASTCALL FindShaderHook(void* inst, [[maybe_unused]] void* edx, const char* name)
{
	if (strcmp(name, "LensFlare") == 0)
		return &LensFlare::s_ShaderInstance;

	return FindShader(inst, name);
}

void PrintMessage(const char* msg)
{
	cvar->ConsolePrintf("[");
	cvar->ConsoleColorPrintf(Color(86, 214, 156, 255), "GMShaders");
	cvar->ConsolePrintf("] %s\n", msg);
}

int PrintError(const char* err)
{
	PrintMessage(err);
	cvar->ConsolePrintf("If you get this error please open an issue on GMShaders github page: ");
	cvar->ConsoleColorPrintf(Color(106, 176, 234, 255), "https://github.com/Havch1k92/GMShaders\n");

	return 0;
}

// Not using gmod-modules-base repo because devs don't feel like finishing it
_DllExport int gmod13_open([[maybe_unused]] void* L)
{
	IShaderDLLInternal* shaderDll = GetShaderDLLInternal();
	CreateInterfaceFn materialsystem = Sys_GetFactory("materialsystem");
	if (!shaderDll->Connect(materialsystem)) // Initializes stuff like shaderlib, cvars etc
		return PrintError("Could not initialize 'shaderlib'!");

	SymbolFinder scanner;

	FindShader = (FindShaderFn)scanner.FindPattern("materialsystem", g_FindShaderSig);
	if (!FindShader)
		return PrintError("'CShaderSystem::FindShader' signature is outdated.");

	FindShader = (FindShaderFn)DetourFunction((uint8_t*)FindShader, (uint8_t*)&FindShaderHook);

	PrintMessage("Module loaded successfully!");

	return 0;
}

_DllExport int gmod13_close([[maybe_unused]] void* L)
{
	IShaderDLLInternal* shaderDll = GetShaderDLLInternal();
	shaderDll->Disconnect();

	if (FindShader)
		; // TODO: unhook it

	PrintMessage("Module unloaded successfully!");

	return 0;
}
