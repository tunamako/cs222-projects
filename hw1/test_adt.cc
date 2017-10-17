#include "gtest/gtest.h"
#include "adt.h"
#include "csString.h"
#include "hashTable.h"
#include <string.h>

TEST(AdtTest, testHash){
	csAdtRef thing1 = newCsAdt();
	csAdtRef thing2 = newCsAdt();
	uint32_t hash1 = SEND(thing1,hash);
	uint32_t hash2 = SEND(thing2,hash);
	EXPECT_EQ(hash1, SEND(thing1,hash));
	EXPECT_EQ(hash2, SEND(thing2,hash));
	EXPECT_NE(hash1,hash2);
}

TEST(AdtTest, testEquals){
	csAdtRef thing1 = newCsAdt();
	csAdtRef thing2 = newCsAdt();
	EXPECT_TRUE(SEND1(thing1,equals,thing1));
	EXPECT_TRUE(SEND1(thing2,equals,thing2));
	EXPECT_FALSE(SEND1(thing1,equals,thing2));
}

TEST(csStringTest, testHash){
	csStringRef thing1 = newCSString((char *)"testString1");
	csStringRef thing2 = newCSString((char *)"testString2");
	uint32_t hash1 = SEND(thing1,hash);
	uint32_t hash2 = SEND(thing2,hash);
	EXPECT_EQ(hash1, SEND(thing1,hash));
	EXPECT_EQ(hash2, SEND(thing2,hash));
	EXPECT_NE(hash1,hash2);
}

TEST(csStringTest, testEquals){
	csStringRef string1 = newCSString((char *)"testString");
	csStringRef string2 = newCSString((char *)"testString");
	csStringRef string3 = newCSString((char *)"testString");
	csStringRef string4 = newCSString((char *)"notLikeTheOthers");
	EXPECT_TRUE(SEND1(string1, equals, (csAdtRef)string2));
	EXPECT_TRUE(SEND1(string2, equals, (csAdtRef)string3));
	EXPECT_TRUE(SEND1(string1, equals, (csAdtRef)string3));
	EXPECT_FALSE(SEND1(string1, equals, (csAdtRef)string4));
}

TEST(HashTableTest, testConstructor){
	csHashTableRef hashTableRef = newCsHashTable(6);
	EXPECT_EQ(hashTableRef->size, 13); 
	EXPECT_EQ(hashTableRef->count, 0);
}

TEST(HashTableTest, testAddAndIncludesNoGrow){
	csHashTableRef hashTable = newCsHashTable(6);
	csAdtRef item1 = newCsAdt();
	csStringRef item2 = newCSString((char *)"testString1");
	EXPECT_FALSE(SEND1(hashTable, includes, item1));
	EXPECT_FALSE(SEND1(hashTable, includes, (csAdtRef)item2));
	EXPECT_EQ(SEND(hashTable, size), 0);
	SEND1(hashTable, add, item1);
	EXPECT_TRUE(SEND1(hashTable, includes, item1));
	EXPECT_FALSE(SEND1(hashTable, includes, (csAdtRef)item2));
	EXPECT_EQ(SEND(hashTable, size), 1);
	SEND1(hashTable, add, (csAdtRef)item2);
	EXPECT_TRUE(SEND1(hashTable, includes, item1));
	EXPECT_TRUE(SEND1(hashTable, includes, (csAdtRef)item2));
	EXPECT_EQ(SEND(hashTable, size), 2);
	SEND1(hashTable, add, (csAdtRef)item2);
	EXPECT_TRUE(SEND1(hashTable, includes, item1));
	EXPECT_TRUE(SEND1(hashTable, includes, (csAdtRef)item2));
	EXPECT_EQ(SEND(hashTable, size), 2);
}

TEST(HashTableTest, testGrow){
	csHashTableRef hashTable = newCsHashTable(1);
	csAdtRef item1 = newCsAdt();
	csAdtRef item2 = newCsAdt();
	csAdtRef item3 = newCsAdt();
	csAdtRef item4 = newCsAdt();
	csAdtRef item5 = newCsAdt();
	csAdtRef item6 = newCsAdt();
	csAdtRef item7 = newCsAdt();

	EXPECT_EQ(hashTable->size, 7);
	EXPECT_EQ(SEND(hashTable, size), 0);
	SEND1(hashTable, add, item1);
	SEND1(hashTable, add, item2);
	SEND1(hashTable, add, item3);
	SEND1(hashTable, add, item4);
	EXPECT_EQ(hashTable->size, 7);
	EXPECT_EQ(SEND(hashTable,size), 4);
	SEND1(hashTable, add, item5);
	EXPECT_EQ(hashTable->size, 13);
	EXPECT_EQ(SEND(hashTable,size), 5);
	SEND1(hashTable, add, item6);
	SEND1(hashTable, add, item7);
	EXPECT_EQ(hashTable->size, 13);
	EXPECT_EQ(SEND(hashTable,size), 7);
}

TEST(HashTableTest, testRemove){
	csHashTableRef hashTable = newCsHashTable(1);
	csAdtRef item1 = newCsAdt();
	csAdtRef item2 = newCsAdt();
	csAdtRef item3 = newCsAdt();
	csAdtRef item4 = newCsAdt();
	//Modify default hashes so we get hash collisions.
	item2->hash = item1->hash;
	item3->hash = item1->hash;
	item4->hash = item1->hash;
	SEND1(hashTable, add, item1);
	SEND1(hashTable, add, item2);
	SEND1(hashTable, add, item3);
	SEND1(hashTable, add, item4);
	EXPECT_EQ(hashTable->size, 7);
	EXPECT_EQ(SEND(hashTable, size), 4);
	EXPECT_EQ(SEND1(hashTable, remove, item1), (csAdtRef)item1);
	EXPECT_EQ(SEND(hashTable, size), 3);
	EXPECT_EQ(SEND1(hashTable, remove, item2), (csAdtRef)item2);
	EXPECT_EQ(SEND(hashTable, size), 2);
}
