#include "hashTable.h"

int primeList[] = {
	7, 13, 29, 61, 137, 293, 557, 1097, 2213, 
	3823, 6659, 11587, 20173, 35129, 70241, 
	140521, 244589, 489179, 851723, 1482919, 
	581907, 296584, 0,
};

uint32_t adtHash(csAdtRef self);
bool adtEquals(csAdtRef self, csAdtRef other);
char * adtDescription(csHashTableRef self);
int csHashTableSize(csHashTableRef self);
bool csHashTableIncludes(csHashTableRef self, csAdtRef item);
bool csHashTableAdd(csHashTableRef self, csAdtRef item);
csAdtRef csHashTableRemove(csHashTableRef self, csAdtRef item);
int csHashTableScanFor(csHashTableRef self, csAdtRef item);
bool csHashTableGrow(csHashTableRef self);
bool checkTableLoad(csHashTableRef self);
int findNextPrime(int capacity);
void copyOldTable(csHashTableRef self, csAdtRef * oldTable);

csHashTableMethods tableMethods = {
	adtHash,
	adtEquals,
	adtDescription,
	csHashTableSize,
	csHashTableIncludes,
	csHashTableAdd,
	csHashTableRemove,
};

csHashTableRef newCsHashTable(int capacity){
	csHashTableRef aHashTable = (csHashTableRef)malloc(sizeof(csHashTable));
	if(aHashTable == NULL){
		return NULL;
	}
	aHashTable->methods = &tableMethods;
	aHashTable->hash = lfsrHash();
	aHashTable->size = findNextPrime(capacity);
	aHashTable->count = 0;
	aHashTable->table = (csAdtRef*)calloc(aHashTable->size, sizeof(csAdt));
	if(aHashTable->table == NULL){
		return NULL;
	}
	return aHashTable;
}

int csHashTableSize(csHashTableRef self){
	return self->count;
}

int csHashTableScanFor(csHashTableRef self, csAdtRef item){
	unsigned int index = SEND(item, hash) % self->size;
	while(self->table[index] != NULL && !self->methods->equals(self->table[index], item)){
		index++;
	}
	return index;
}

bool csHashTableAdd(csHashTableRef self, csAdtRef item){
	int index = csHashTableScanFor(self, item);
	while(self->table[index] != NULL){
		if(SEND1(item, equals, self->table[index])){
			return false;
		}
		else if(index + 1 == self->size){
			index = 0;
		}
		index++;
	}
	self->table[index] = item;
	self->count++;
	return checkTableLoad(self);
}

bool csHashTableIncludes(csHashTableRef self, csAdtRef item){
	int index = csHashTableScanFor(self, item);
	return self->methods->equals(self->table[index], item);
}

bool csHashTableGrow(csHashTableRef self){
	csAdtRef * oldTable = self->table;
	self->size = findNextPrime(self->size);
	self->count = 0;
	self->table = (csAdtRef*)calloc(self->size, sizeof(csAdt));
	if(self->table == NULL){
		return NULL;
	}
	copyOldTable(self, oldTable);
	free(oldTable);
	return true;
}

csAdtRef csHashTableRemove(csHashTableRef self, csAdtRef item){
	if(!csHashTableIncludes(self, item)){
		return NULL;
	}
	int index = csHashTableScanFor(self, item);
	csAdtRef * oldTable = self->table;
	oldTable[index] = NULL;
	self->count = 0;
	self->table = (csAdtRef*)calloc(self->size, sizeof(csAdt));
	if(self->table == NULL){
		return NULL;
	}
	copyOldTable(self, oldTable);
	free(oldTable);
	return item;
}

bool checkTableLoad(csHashTableRef self){
	double loadRatio = (double)self->count / (double)self->size;
	if(loadRatio >= 0.7){
		return csHashTableGrow(self);
	}
	return true;
}

int findNextPrime(int capacity){
	int i = 0;
	double targetSize = 1.4 * capacity;
	while(targetSize >= primeList[i]){
		if(primeList[i] == 0){
			return NULL;
		}
		i++;
	}
	return primeList[i];
}

void copyOldTable(csHashTableRef self, csAdtRef *oldTable){
	for(int j = 0; j < self->size; j++){
		if(oldTable[j] != NULL){
			SEND1(self, add, oldTable[j]);
		}
	}
}