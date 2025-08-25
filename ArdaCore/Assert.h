#pragma once

#ifdef __LINUX__
#define BREAKPOINT
#endif
#ifdef _WIN32
#define BREAKPOINT __debugbreak()
#endif

#define Assert(condition)																\
	do                                                                                  \
	{                                                                                   \
		if (!(condition)) [[unlikely]]													\
			BREAKPOINT;                                                                 \
	} while (0);