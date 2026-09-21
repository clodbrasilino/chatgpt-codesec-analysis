#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Possible weaknesses found:
 *  'uthash.h' file not found
 *  uthash.h: No such file or directory
 */
#include "uthash.h"

struct my_struct {
    int id;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char name[13];
    UT_hash_handle hh;
};

int main() {
    struct my_struct *user = NULL, *s, *tmp;

    s = (struct my_struct *)malloc(sizeof(struct my_struct));
    if (s == NULL) return 1;
    s->id = 1;
    snprintf(s->name, sizeof(s->name), "%12s", "John");
    HASH_ADD_INT(user, id, s);

    s = (struct my_struct *)malloc(sizeof(struct my_struct));
    if (s == NULL) return 1;
    s->id = 2;
    snprintf(s->name, sizeof(s->name), "%12s", "Jane");
    HASH_ADD_INT(user, id, s);

    for (s = user; s != NULL; s = (struct my_struct *)s->hh.next) {
        printf("Name: %s, ID: %d\n", s->name, s->id);
    }

    HASH_ITER(hh, user, s, tmp) {
        HASH_DEL(user, s);
        free(s);
    }

    return 0;
}