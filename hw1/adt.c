#include "adt.h"

// This implements a base abstract data type.
// Think of this as class Object.

// forward declaration of method implementations
uint32_t lfsrHash(void);
uint32_t adtHash(csAdtRef self);
bool adtEquals(csAdtRef self, csAdtRef other);
char * adtDescription(csAdtRef self);

// declare the method structure for csAdtMethods
csAdtMethods adtMethods = {
	adtHash,
	adtEquals,
	adtDescription,
};

// declare csAdt constructor function
csAdtRef newCsAdt(){
	csAdtRef anAdtRef = (csAdtRef)malloc(sizeof(csAdt));
	if(anAdtRef == (csAdtRef)NULL){
		return (csAdtRef)NULL;
	}
	anAdtRef->methods = &adtMethods;
	anAdtRef->hash = lfsrHash();
	return anAdtRef;
}

// nextHash()
//  Generate 32 bit hash using a linear feedback shift register.
//      feedback polynomial: x^32 + x^31 + x^29 + x + 1
//      taps: 32 31 29 1
uint32_t lfsrHash(void){
	static uint32_t lfsr = 1;
	lfsr = (lfsr >> 1) ^ (-(lfsr & 1u) & 0xD0000001u);
	return lfsr;
}
uint32_t adtHash(csAdtRef self){
	return self->hash;
}

bool adtEquals(csAdtRef self, csAdtRef other){
	return self == other;
}

char * adtDescription(csAdtRef self){
	return "an ADT";
}
