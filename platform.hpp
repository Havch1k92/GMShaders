#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#if defined(_MSC_VER)
#	define MSVC 1
#elif defined(__GNUC__)
#	define GCC 1
#elif defined(__clang__)
#	define CLANG 1
#else
#	error Unknown compiler, not supported by this project.
#endif

#if defined(_M_IX86) or defined(__i386__) or defined (__i386)
#	define ARCH_X86 1
#elif defined(_M_X64) or defined(__amd64__) or defined(__amd64)
#	define ARCH_X64 1
#endif

#if defined(_WIN32)
#	define SYS_WINDOWS	1
#elif defined (__linux)
#	define SYS_LINUX	1
#	define SYS_POSIX	1
#elif defined (__APPLE__)
#	define SYS_MACOSX	1
#	define SYS_POSIX	1
#else
#	error Unknown OS, not supported by this project.
#endif

#if MSVC
#	define CPP_VERSION _MSVC_LANG
#else
#	define CPP_VERSION __cplusplus
#endif

// NOTE: use _ATTR_PORTABLE with stuff that is present in all of three compilers
#if GCC
#	define _DECLSPEC(...)
#	define _ATTRIBUTE(...)		__attribute__((__VA_ARGS__))
#	define _ATTR_PORTABLE(...) 	_ATTRIBUTE(__VA_ARGS__)

#	define __CALLCONV(x) _ATTRIBUTE(x)
#elif CLANG
#	define _DECLSPEC(...)		__declspec(__VA_ARGS__)
#	define _ATTRIBUTE(...)		__attribute__((__VA_ARGS__))
#	define _ATTR_PORTABLE(...) 	_ATTRIBUTE(__VA_ARGS__)

#	define __CALLCONV(x)		_ATTRIBUTE(x)
#else
#	if _MSC_EXTENSIONS
#		define _DECLSPEC(...)	__declspec(__VA_ARGS__)
#	else
#		define _DECLSPEC(...)
#	endif
#	define _ATTRIBUTE(...)
#	define _ATTR_PORTABLE(...) 	_DECLSPEC(__VA_ARGS__)

#	define __CALLCONV(x) __##x
#endif

#define _CDECL		__CALLCONV(cdecl)
#define _FASTCALL	__CALLCONV(fastcall)
#define _THISCALL	__CALLCONV(thiscall)
#define _STDCALL	__CALLCONV(stdcall)

class _DECLSPEC(novtable) Platform final
{
public:
	constexpr static bool IsX86()
	{
#if ARCH_X86
		return true;
#else
		return false;
#endif
	}
	constexpr static bool IsX64() { return !IsX86(); }

	constexpr static bool IsWindows()
	{
#if SYS_WINDOWS
		return true;
#else
		return false;
#endif
	}
	constexpr static bool IsPOSIX()
	{
#if SYS_POSIX
		return true;
#else
		return false;
#endif
	}
	constexpr static bool IsLinux()
	{
#if SYS_LINUX
		return true;
#else
		return false;
#endif
	}
	constexpr static bool IsOSX()
	{
#if SYS_MACOSX
		return true;
#else
		return false;
#endif
	}
};

#endif // PLATFORM_HPP
