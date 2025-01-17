///
// Fundamental Types
///

#include <stdint.h>

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int32_t i32;
typedef int64_t i64;

typedef float  r32;
typedef double r64;

typedef char    c8;
typedef wchar_t c16;


///
// Helpful Macros & Templates
///

#define Kilobyte 1024LL
#define Megabyte 1024LL * Kilobyte
#define Gigabyte 1024LL * Megabyte

#define Assert(condition) if (!(condition)) { *((u8 *) 0) = 0; }
#define InvalidCodePath Assert(!"Invalid code path")
#define InvalidDefaultCase default: InvalidCodePath; break

//TODO: Confirm the loop is optimized away
#define IF(expression, check, action) \
do {                                  \
	if ( check(expression) )          \
	{                                 \
		action;                       \
	}                                 \
} while ( 0 )                         

#define IGNORE
#define IS_TRUE
#define IS_FALSE !

template<typename T, size_t S>
inline size_t ArrayCount(const T (&arr)[S])
{
	return S;
}

template<typename T, size_t S>
inline size_t ArraySize(const T (&arr)[S])
{
	return S * sizeof(T);
}


///
// Global Functionality
///

//TODO: Disable exceptions?
//#define _HAS_EXCEPTIONS 0

#include "Logging.h"
using namespace Logging;

#include <memory>
#include "FileIO.hpp"


///
// Math
///

i32
Clamp(i32 value, i32 min, i32 max)
{
	if (value < min) value = min;
	if (value > max) value = max;

	return value;
}

i64
Clamp(i64 value, i64 min, i64 max)
{
	if (value < min) value = min;
	if (value > max) value = max;

	return value;
}

struct V2i
{
	i32 x;
	i32 y;
};

//Operators
inline bool
operator== (V2i lhs, V2i rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

inline bool
operator!= (V2i lhs, V2i rhs)
{
	return !(lhs.x == rhs.x && lhs.y == rhs.y);
}

inline V2i
operator+ (V2i lhs, V2i rhs)
{
	return {lhs.x + rhs.x, lhs.y + rhs.y};
}

inline V2i
operator- (V2i lhs, V2i rhs)
{
	return {lhs.x - rhs.x, lhs.y - rhs.y};
}

inline V2i
operator* (V2i v, i32 multiplier)
{
	return {multiplier * v.x, multiplier * v.y};
}

inline V2i
operator/ (V2i v, i32 dividend)
{
	return {v.x / dividend, v.y / dividend};
}

inline void
Clamp(V2i v, V2i maxSize)
{
	if (v.x > maxSize.x) v.x = maxSize.x;
	if (v.y > maxSize.y) v.y = maxSize.y;
}


///
// Input
///

struct ButtonState
{
	bool isDown;
	u8   transitionCount;
};

struct InputState
{
	r64 t;
	r64 dt;

	V2i mouse;

	union
	{
		ButtonState buttons[5];
		struct
		{
			ButtonState mouseLeft;
			ButtonState mouseRight;
			ButtonState mouseMiddle;
			ButtonState mouseWheelUp;
			ButtonState mouseWheelDown;
		};
	};
};


///
// Memory
///

struct SimMemory
{
	//NOTE: bytes are expected to be initialized to zeros.
	void* bytes;
	u32   size;

	InputState input;
};

struct SimState
{
	//r32  gameTime, gamedt;
	//r32  realTime, realdt;
	bool isPaused;
};

void
InitializeSimulation(SimMemory *simMemory, V2i* windowSize)
{
	SimState* simState = (SimState*) simMemory->bytes;

	*windowSize = {800, 600};
}

void
UpdateSimulation(SimMemory *simMemory)
{
	SimState* simState = (SimState*) simMemory->bytes;
}