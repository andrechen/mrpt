/* +------------------------------------------------------------------------+
   |                     Mobile Robot Programming Toolkit (MRPT)            |
   |                          http://www.mrpt.org/                          |
   |                                                                        |
   | Copyright (c) 2005-2018, Individual contributors, see AUTHORS file     |
   | See: http://www.mrpt.org/Authors - All rights reserved.                |
   | Released under BSD License. See details in http://www.mrpt.org/License |
   +------------------------------------------------------------------------+ */
#pragma once

#include <cstring>

namespace mrpt
{
namespace system
{
/** \addtogroup mrpt_memory Memory utilities (#include <mrpt/system/memory.h>)
 * \ingroup mrpt_system_grp
 *  @{ */

/** Returns the memory occupied by this process, in bytes */
unsigned long getMemoryUsage();

/** In platforms and compilers with support to "alloca", allocate a memory block
 * on the stack; if alloca is not supported, it is emulated as a normal "malloc"
 * - NOTICE: Since in some platforms alloca will be emulated with malloc,
 * alloca_free MUST BE ALWAYS CALLED to avoid memory leaks.
 *   This method MUST BE a macro rather than a function in order to operate on
 * the caller's stack.
 *  \sa mrpt_alloca_free
 */
#if defined(_MSC_VER) && (_MSC_VER >= 1400)
// Visual Studio 2005, 2008
#define mrpt_alloca(nBytes) _malloca(nBytes)
#elif defined(HAVE_ALLOCA)
// GCC
#define mrpt_alloca(nBytes) ::alloca(nBytes)
#else
// Default: Emulate with memory in the heap:
#define mrpt_alloca(nBytes) ::malloc(nBytes)
#endif

/** This method must be called to "free" each memory block allocated with
 * "system::alloca": If the block was really allocated in the stack, no
 * operation is actually performed, otherwise it will be freed from the heap.
 *   This method MUST BE a macro rather than a function in order to operate on
 * the caller's stack.
 * \sa mrpt_alloca
 */
#if defined(_MSC_VER) && (_MSC_VER >= 1400)
// Visual Studio 2005, 2008
#define mrpt_alloca_free(mem_block) _freea(mem_block)
#elif defined(HAVE_ALLOCA)
// GCC
#define mrpt_alloca_free(mem_block)
#else
// Default: Emulate with memory in the heap:
#define mrpt_alloca_free(mem_block) free(mem_block)
#endif

/** @} */

/** \addtogroup mrpt_memory Memory utilities
 *  @{ */
// The following templates are taken from libcvd (LGPL). See
// http://mi.eng.cam.ac.uk/~er258/cvd/
// Check if the pointer is aligned to the specified byte granularity
template <int bytes>
bool is_aligned(const void* ptr);
template <>
inline bool is_aligned<8>(const void* ptr)
{
	return ((reinterpret_cast<size_t>(ptr)) & 0x7) == 0;
}
template <>
inline bool is_aligned<16>(const void* ptr)
{
	return ((reinterpret_cast<size_t>(ptr)) & 0xF) == 0;
}
/** @} */

}  // namespace system
}  // namespace mrpt
