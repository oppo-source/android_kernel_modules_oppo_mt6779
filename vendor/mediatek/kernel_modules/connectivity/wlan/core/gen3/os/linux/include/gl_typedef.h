/*
* Copyright (C) 2016 MediaTek Inc.
*
* This program is free software: you can redistribute it and/or modify it under the terms of the
* GNU General Public License version 2 as published by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
* without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
* See the GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License along with this program.
* If not, see <http://www.gnu.org/licenses/>.
*/

/*
** Id: //Department/DaVinci/BRANCHES/MT6620_WIFI_DRIVER_V2_3/os/linux/include/gl_typedef.h#1
*/

/*
 * ! \file   gl_typedef.h
 *  \brief  Definition of basic data type(os dependent).
 *
 *  In this file we define the basic data type.
 */

#ifndef _GL_TYPEDEF_H
#define _GL_TYPEDEF_H


#include "config.h"

#if CFG_ENABLE_EARLY_SUSPEND
#include <linux/earlysuspend.h>
#endif

/*******************************************************************************
*                         C O M P I L E R   F L A G S
********************************************************************************
*/

/*******************************************************************************
*                    E X T E R N A L   R E F E R E N C E S
********************************************************************************
*/

/*******************************************************************************
*                              C O N S T A N T S
********************************************************************************
*/
/* Define HZ of timer tick for function kalGetTimeTick() */
#define KAL_HZ                  (1000)

/* Miscellaneous Equates */
#ifndef FALSE
#define FALSE               ((BOOL) 0)
#define TRUE                ((BOOL) 1)
#endif /* FALSE */

#ifndef NULL
#if defined(__cplusplus)
#define NULL            0
#else
#define NULL            ((void *) 0)
#endif
#endif

#if CFG_ENABLE_EARLY_SUSPEND
typedef void (*early_suspend_callback) (struct early_suspend *h);
typedef void (*late_resume_callback) (struct early_suspend *h);
#endif

/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/
/* Type definition for void */
typedef void VOID, *PVOID, **PPVOID;

/* Type definition for Boolean */
typedef unsigned char BOOL, *PBOOL, BOOLEAN, *PBOOLEAN;

/* Type definition for signed integers */
typedef signed char CHAR, *PCHAR, **PPCHAR;
typedef signed char INT_8, *PINT_8, **PPINT_8;
typedef signed short INT_16, *PINT_16, **PPINT_16;
typedef signed int INT_32, *PINT_32, **PPINT_32;
typedef unsigned int UINT32, *PUINT32, **PPUINT32;
typedef signed long LONG, *PLONG, **PPLONG;
typedef signed long long INT_64, *PINT_64, **PPINT_64;

/* Type definition for unsigned integers */
typedef unsigned char UCHAR, *PUCHAR, **PPUCHAR;
typedef unsigned char UINT_8, *PUINT_8, **PPUINT_8, *P_UINT_8;
typedef unsigned short UINT_16, *PUINT_16, **PPUINT_16;
typedef unsigned int UINT_32, *PUINT_32, **PPUINT_32;
typedef unsigned long ULONG, *PULONG, **PPULONG;
typedef unsigned long long UINT_64, *PUINT_64, **PPUINT_64;

typedef unsigned int OS_SYSTIME, *POS_SYSTIME, **PPOS_SYSTIME;

/* Type definition of large integer (64bits) union to be comptaible with
 * Windows definition, so we won't apply our own coding style to these data types.
 * NOTE: LARGE_INTEGER must NOT be floating variable.
 * <TODO>: Check for big-endian compatibility.
 */
typedef union _LARGE_INTEGER {
	struct {
		UINT_32 LowPart;
		INT_32 HighPart;
	} u;
	INT_64 QuadPart;
} LARGE_INTEGER, *PLARGE_INTEGER;

typedef union _ULARGE_INTEGER {
	struct {
		UINT_32 LowPart;
		UINT_32 HighPart;
	} u;
	UINT_64 QuadPart;
} ULARGE_INTEGER, *PULARGE_INTEGER;

typedef INT_32(*probe_card) (PVOID pvData);
typedef VOID(*remove_card) (VOID);

/*******************************************************************************
*                            P U B L I C   D A T A
********************************************************************************
*/

/*******************************************************************************
*                           P R I V A T E   D A T A
********************************************************************************
*/

/*******************************************************************************
*                                 M A C R O S
********************************************************************************
*/
#define IN			/* volatile */
#define OUT			/* volatile */

#define __KAL_INLINE__                  inline
#define __KAL_ATTRIB_PACKED__           __attribute__((__packed__))
#define __KAL_ATTRIB_ALIGN_4__          __aligned(4)

#ifndef BIT
#define BIT(n)                          (1UL << (n))
#endif /* BIT */

#ifndef BITS
/* bits range: for example BITS(16,23) = 0xFF0000
 *   ==>  (BIT(m)-1)   = 0x0000FFFF     ~(BIT(m)-1)   => 0xFFFF0000
 *   ==>  (BIT(n+1)-1) = 0x00FFFFFF
 */
#define BITS(m, n)                       (~(BIT(m)-1) & ((BIT(n) - 1) | BIT(n)))
#endif /* BIT */

/*
 * This macro returns the byte offset of a named field in a known structure
 * type.
 * _type - structure name,
 *  _field - field name of the structure
 */
#ifndef OFFSET_OF
#define OFFSET_OF(_type, _field)         offsetof(_type, _field)
#endif /* OFFSET_OF */

/*
 * This macro returns the base address of an instance of a structure
 * given the type of the structure and the address of a field within the
 * containing structure.
 * _addrOfField - address of current field of the structure,
 * _type - structure name,
 * _field - field name of the structure
 */
#ifndef ENTRY_OF
#define ENTRY_OF(_addrOfField, _type, _field) \
	((_type *)((PINT_8)(_addrOfField) - (PINT_8)OFFSET_OF(_type, _field)))
#endif /* ENTRY_OF */

/* This macro align the input value to the DW boundary.
 * _value - value need to check
 */
#ifndef ALIGN_4
#define ALIGN_4(_value)             (((_value) + 3) & ~3u)
#endif /* ALIGN_4 */

/* This macro check the DW alignment of the input value.
 * _value - value of address need to check
 */
#ifndef IS_ALIGN_4
#define IS_ALIGN_4(_value)          (((_value) & 0x3) ? FALSE : TRUE)
#endif /* IS_ALIGN_4 */

#ifndef IS_NOT_ALIGN_4
#define IS_NOT_ALIGN_4(_value)      (((_value) & 0x3) ? TRUE : FALSE)
#endif /* IS_NOT_ALIGN_4 */

/* This macro evaluate the input length in unit of Double Word(4 Bytes).
 * _value - value in unit of Byte, output will round up to DW boundary.
 */
#ifndef BYTE_TO_DWORD
#define BYTE_TO_DWORD(_value)       ((_value + 3) >> 2)
#endif /* BYTE_TO_DWORD */

/* This macro evaluate the input length in unit of Byte.
 * _value - value in unit of DW, output is in unit of Byte.
 */
#ifndef DWORD_TO_BYTE
#define DWORD_TO_BYTE(_value)       ((_value) << 2)
#endif /* DWORD_TO_BYTE */

#if 1				/* Little-Endian */
#define NTOHS(_x)           ntohs(_x)

#define HTONS(_x)           htons(_x)

#define NTOHL(_x)           ntohl(_x)

#define HTONL(_x)           htonl(_x)

#else /* Big-Endian */

#define CONST_NTOHS(_x)

#define CONST_HTONS(_x)

#define NTOHS(_x)

#define HTONS(_x)

#endif

/*******************************************************************************
*                  F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/

/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/

#endif /* _GL_TYPEDEF_H */
