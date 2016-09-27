#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "phonebook_opt.h"

#define HASH_MODULO(x) ((x) & 0xFFF)
static uint32_t jenkins(char *key, int len);
static uint32_t djb2(char *key, int len);

static entry *findEntry(const char value[], entry * const pHead);
/**
 * @brief Find the entry containing the specified last name
 * in the hash table
 * @param lastName The last name to search
 * @param pHashTable The pointer to the hash table
 * @return The pointer to the matched entry
 * @retval NULL There is no entry matched
 */
entry *findName(char lastName[], entry **pHashTable)
{
    uint32_t hashValue = HASH_MODULO(jenkins(lastName, strlen(lastName)));
    return findEntry(lastName, pHashTable[hashValue]);
}

/**
 * @brief Find the entry containing the specified value in the
 * linked list.
 * @param value The value to search
 * @param pHead The head of the linked list
 * @return The pointer to the matched entry
 * @retval NULL There is no entry matched
 */
static entry *findEntry(const char value[], entry * const pHead)
{
    entry *current = pHead;
    while (current != NULL) {
        if (strcasecmp(current->lastName, value) == 0)
            return current;
        current = current->pNext;
    }

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
static uint32_t jenkins(char *key, int len)
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

static uint32_t djb2(char *key, int len)
{
    unsigned long hash = 5381;
    for (int i = 0; i < len; ++i)
        hash = ((hash << 5) + hash) + key[i];

    return (uint32_t)(hash & 0xFFFFFFFF);
}

static void clearList(entry *list);
/**
 * @brief Free the allocated memory for the hash table.
 * @param pHashTable The pointer to the hash table
 * @param numOfIndex The number of the indexes in the hash table
 */
void clearTable(entry **pHashTable, int numOfIndex)
{
    for (int i = 0; i < numOfIndex; ++i) {
        clearList(pHashTable[i]);
        pHashTable[i] = NULL;
    }
}

/**
 * @brief Free all the element in the linked list _list_.
 */
static void clearList(entry *list)
{
    entry *next;
    while (list != NULL) {
        next = list->pNext;
        free(list);
        list = next;
    }
}

static int countListLen(entry *pHead);
/**
 * @brief Count the length of the linked list in each index of hashTable
 * @param pHashTable The pointer to the hash table
 * @param pResult [out] The pointer to the array of integer to
 *        store the result. Must have enough length.
 */
void getListLen(entry **pHashTable, int *pResult)
{
    for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
        pResult[i] = countListLen(pHashTable[i]);
    }
}

/**
 * @brief Count the length of the specified linked list
 * @param pHead The pointer to the head of the linked list
 * @return The length of the linked list
 */
static int countListLen(entry *pHead)
{
    int count = 0;
    entry *current = pHead;
    while (current != NULL) {
        ++count;
        current = current->pNext;
    }
    return count;
}
