//Useful prime number table sizes.
7 
13 
29 
61 
137 
293 
557 
1097 
2213 
3823 
6659 
11587 
20173 
35129 
70241 
140521 
244589 
489179 
851723 
1482919 
2581907 
2965847

// nextHash()
//  Generate 32 bit hash using a linear feedback shift register.
//      feedback polynomial: x^32 + x^31 + x^29 + x + 1 
//      taps: 32 31 29 1
uint32_t defaultHash(adtRef self)
{
	static uint32_t lfsr = 1;
    return (lfsr >> 1) ^ (-(lfsr & 1u) & 0xD0000001u);
}

// stringHash()
// 32 bit fnv-1a hash
// assumes that the string like object 
//	has the char * in a field called contents
//	has the string length in a field called count

#define HASH_SEED 2166136261U
#define HASH_PRIME 16777619U
uint32_t stringHash(stringAdtRef self)
{
    uint32_t result = HASH_SEED;
    int i;

    for (i = 0; i < self->count; ++i) {
        result = result ^ self->contents[i];
        result = result * HASH_PRIME;
    }
    return result;
}

