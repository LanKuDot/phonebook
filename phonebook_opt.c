#include <stdlib.h>
#include <stdint.h>

#include "phonebook_opt.h"

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
