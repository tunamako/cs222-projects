#ifndef adt_H_
#define adt_H_
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

// Send message macros
#define SEND(receiver, wutdo)\
	receiver->methods->wutdo(receiver)

#define SEND1(receiver,wutdo,arg)\
	receiver->methods->wutdo(receiver,arg)

// Declare csAdt instance.
typedef struct csAdt {
	struct csAdtMethods *methods;
	uint32_t hash;
} csAdt, *csAdtRef;

// Declare types of methods.
typedef uint32_t (*pfn_uint32_adtRef)(csAdtRef);
typedef bool (*pfn_bool_adtRefAdtRef)(csAdtRef, csAdtRef);
typedef char * (*pfn_cstr_adtRef)(csAdtRef);

// Declare csAdt interface.
typedef struct csAdtMethods {
	pfn_uint32_adtRef hash;
	pfn_bool_adtRefAdtRef equals;
	pfn_cstr_adtRef description;
} csAdtMethods, *csAdtMethodsRef;

#ifdef __cplusplus
extern "C" {
#endif

csAdtRef newCsAdt(void);

#ifdef __cplusplus
}
#endif

#endif
