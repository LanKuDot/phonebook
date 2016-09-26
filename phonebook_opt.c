#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "phonebook_opt.h"

#define HASH_MODULO(x) ((x) & 0xFFF)
static uint32_t jenkins(char *key, size_t len);

/* FILL YOUR OWN IMPLEMENTATION HERE! */
entry *findName(char lastname[], entry *pHead)
{
    /* TODO: implement */
    return NULL;
}

entry *append(char lastName[], entry *e)
{
    return NULL;
}

/**
 * @brief Append an element to the hash table
 * @param lastName The last name
 * @param pHashTable The pointer to the hash table
 * @return The pointer to new entry element
 */
entry *append(char lastName[], entry **pHashTable)
{
    uint32_t hashValue;
    // Initialize the entry
    entry *newEntry = (entry *) malloc(sizeof(entry));
    strcpy(newEntry->lastName, lastName);
    newEntry->detail = NULL;
    newEntry->pNext = NULL;

    // Calculate the hash index
    hashValue = HASH_MODULO(jenkins(lastName, strlen(lastName)));
    // Insert the new elemnt to the head of the linked list
    // of the specified entry.
    if (pHashTable[hashValue] == NULL)
        pHashTable[hashValue] = newEntry;
    else {
        entry *secondEntry = pHashTable[hashValue];
        pHashTable[hashValue] = newEntry;
        pHashTable[hashValue]->pNext = secondEntry;
    }

    return newEntry;
}

/* Jenkins's one-at-a-time hash function.
 */
static uint32_t jenkins(char *key, size_t len)
{
    uint32_t hash = 0;
    for (int i = 0; i < len; ++i) {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash >> 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}
