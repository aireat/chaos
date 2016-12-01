
#ifndef __TYPE_H__
#define __TYPE_H__

#ifdef __cplusplus
    extern "C" {
#endif

//////////////////////////////////////  < BEGIN >  ///////////////////////////////////////


/*======================================================================================*/
/*
    Specific macro definition that depend on compiler
*/
/*======================================================================================*/

#if   defined (WIN32)               /* Windows */
    #define __CO_FUNC__             ""
    #define __CO_LINE__             __LINE__
    #define __CO_FILE__             __FILE__
    #define WEAK                    
    #define __ASM__                 
    #define __INLINE__              
    #define __STATIC_INLINE__       

    typedef int                     BOOL;

#elif defined (__CC_ARM)            /* Keil uVision */
    #define __CO_FUNC__             __func__
    #define __CO_LINE__             __LINE__
    #define __CO_FILE__             __FILE__
    #define WEAK                    __attribute__ ((weak))
    #define __ASM__                 __asm
    #define __INLINE__              __inline
    #define __STATIC_INLINE__       static __inline

    typedef int                     BOOL;

#elif defined (COMPILER_ROWLEY)
    #define __CO_FUNC__            ""
    #define __CO_LINE__             __LINE__
    #define __CO_FILE__             __FILE__
    #define WEAK                    
    #define __ASM__                 __asm
    #define __INLINE__              inline
    #define __STATIC_INLINE__       static inline

    typedef unsigned char           BOOL;

#elif defined (__ICCARM__)          /* IAR EWARM */
    #define __CO_FUNC__             __func__
    #define __CO_LINE__             __LINE__
    #define __CO_FILE__             __FILE__
    #define WEAK                    __weak
    #define __ASM__                 __asm
    #define __INLINE__              inline
    #define __STATIC_INLINE__       static inline

    typedef unsigned int            BOOL;

#elif defined (__GNUC__)            /* GNU Compiler */
    #define __CO_FUNC__             __func__
    #define __CO_LINE__             __LINE__
    #define __CO_FILE__             __FILE__
    #define WEAK                    
    #define __ASM__                 __asm
    #define __INLINE__              inline
    #define __STATIC_INLINE__       static inline

    typedef unsigned int            BOOL;

#else
    #error "__ must define Compiler Type __"

#endif

/*======================================================================================*/
/*
    Constant type definition
*/
/*======================================================================================*/
#ifndef CONST
    #define CONST               const
#endif

#ifndef VOID
    #define VOID                void
#endif

// type for null
#ifndef NULL
#define NULL                    0
#endif

// type for false
#ifndef FALSE
#define FALSE                   0
#endif

// type for true
#ifndef TRUE
#define TRUE                    !FALSE
#endif

#ifndef DO_NOTHING
#define DO_NOTHING              do{ }while(0)
#endif

/*======================================================================================*/
/*
    Basic data type definition
*/
/*======================================================================================*/

// type for byte
typedef          char           BYTE;

// type for character type
typedef          char           CHAR;

// type for word integer value
typedef unsigned int            UINT;
typedef          int            INT;

// type for 8 bit integer value
typedef unsigned char           UINT8;
typedef   signed char           INT8;

// type for 16 bit integer value
typedef unsigned short          UINT16;
typedef          short          INT16;

// type for 32 bit integer value
typedef unsigned long           UINT32;
typedef          long           INT32;


//////////////////////////////////////  <  END  >  ///////////////////////////////////////

#ifdef __cplusplus
    } /* extern "C" */
#endif

#endif //__TYPE_H__

