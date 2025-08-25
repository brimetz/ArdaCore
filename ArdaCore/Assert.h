#pragma once

#ifdef _WIN32
#define BREAKPOINT __debugbreak()
#else
#define BREAKPOINT
#endif

#define Assert(condition)																\
	do                                                                                  \
	{                                                                                   \
		if (!(condition)) [[unlikely]]													\
			BREAKPOINT;                                                                 \
	} while (0);