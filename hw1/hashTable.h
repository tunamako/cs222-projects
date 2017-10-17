#ifndef csHashTable_H_
#define csHashTable_H_
#include "adt.h"

// Declare csHashTable instance.
typedef struct csHashTable {
	struct csHashTableMethods *methods;
	uint32_t hash;
	int size; //number of slots in the table
	int count; //current number of elements in the table
	csAdtRef  *table;
} csHashTable, *csHashTableRef;

// Declare types of methods.
typedef char * (*pfn_cstr_hashTableRef)(csHashTableRef);
typedef int (*pfn_int_hashTableRef)(csHashTableRef);
typedef bool (*pfn_bool_hashTableRefAdtRef)(csHashTableRef, csAdtRef);
typedef csAdtRef (*pfn_adtRef_hashTableRefAdtRef)(csHashTableRef, csAdtRef);

// Declare csHashTable interface.
typedef struct csHashTableMethods {
	pfn_uint32_adtRef hash;
	pfn_bool_adtRefAdtRef equals;
	pfn_cstr_hashTableRef description;
	pfn_int_hashTableRef size;
	pfn_bool_hashTableRefAdtRef includes;
	pfn_bool_hashTableRefAdtRef add;
	pfn_adtRef_hashTableRefAdtRef remove;
} csHashTableMethods, *csHashTableMethodsRef;

#ifdef __cplusplus
extern "C" {
#endif

csHashTableRef newCsHashTable(int);

#ifdef __cplusplus
}
#endif

#endif
