#pragma once

#define BREAKPOINT __debugbreak()

#define Assert(condition)																\
	do                                                                                  \
	{                                                                                   \
		if (!(condition)) [[unlikely]]													\
			BREAKPOINT;                                                                 \
	} while (0);