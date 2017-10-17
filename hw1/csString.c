#include "csString.h"
#include <string.h>
#include <stdlib.h>

// forward declaration of method implementations
uint32_t stringHash(csStringRef self);
bool stringEquals(csStringRef self, csAdtRef other);
int stringSize(csStringRef self);
char * stringCStr(csStringRef self);
// declare the method structure for csString
csStringMethods strMethods = {
	stringHash,
	stringEquals,
	stringCStr,
	stringSize,
	stringCStr,
};

// declare csString constructor function
csStringRef newCSString(char *cStr){
	csStringRef aString = (csStringRef)malloc(sizeof(csString));
	if(aString == (csStringRef)NULL){
		return (csStringRef)NULL;
	}
	aString->methods = &strMethods;
	aString->size = strlen(cStr);
	aString->contents = cStr;
	return aString;
}

// stringHash()
// 32 bit fnv-1a hash
// assumes that the string like object
//	has the char * in a field called contents
//	has the string length in a field called count

#define HASH_SEED 2166136261U
#define HASH_PRIME 16777619U
uint32_t stringHash(csStringRef self)
{
    uint32_t result = HASH_SEED;
    int i;

    for (i = 0; i < self->size; ++i) {
        result = result ^ self->contents[i];
        result = result * HASH_PRIME;
    }
    return result;
}

bool stringEquals(csStringRef self, csAdtRef other){
		csStringRef strRef;
		if((csAdtMethodsRef)self->methods != other->methods){
			return false;
		}
		strRef = (csStringRef)other;
		if(self->size != strRef->size){
			return false;
		}
		return strcmp(self->contents,strRef->contents)==0;
}

int stringSize(csStringRef self){
	return self->size;
}

char * stringCStr(csStringRef self){
	return self->contents;
}
