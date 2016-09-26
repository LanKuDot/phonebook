#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#define MAX_LAST_NAME_SIZE 16
#define HASH_TABLE_SIZE 4096

#define OPT 1

typedef struct __PERSONAL_DETAIL {
    char firstName[16];
    char email[16];
    char phone[10];
    char cell[10];
    char addr1[16];
    char addr2[16];
    char city[16];
    char state[2];
    char zip[5];
} personal_detail;

typedef struct __PHONE_BOOK_ENTRY {
    char lastName[MAX_LAST_NAME_SIZE];
    personal_detail *detail;
    struct __PHONE_BOOK_ENTRY *pNext;
} entry;

entry *findName(char lastName[], entry **pHashTable);
entry *append(char lastName[], entry **pHashTable);

#endif
