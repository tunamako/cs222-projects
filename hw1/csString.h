#ifndef csString_H_
#define csString_H_
#include "adt.h"

// Declare csString instance.
typedef struct csString {
	struct csStringMethods *methods;
	int size;
	char * contents;
} csString, *csStringRef;

// Declare types of methods.
typedef uint32_t (*pfn_uint32_csStringRef)(csStringRef);
typedef bool (*pfn_bool_csStringRefAdtRef)(csStringRef, csAdtRef);
typedef char * (*pfn_cstr_csStringRef)(csStringRef);
typedef int (*pfn_int_csStringRef)(csStringRef);

// Declare csString interface.
typedef struct csStringMethods {
	pfn_uint32_csStringRef hash;
	pfn_bool_csStringRefAdtRef equals;
	pfn_cstr_csStringRef description;
	pfn_int_csStringRef size;
	pfn_cstr_csStringRef cStr;
} csStringMethods, *csStringMethodsRef;

#ifdef __cplusplus
extern "C" {
#endif

csStringRef newCSString(char *);

#ifdef __cplusplus
}
#endif

#endif
