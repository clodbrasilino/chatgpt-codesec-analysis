#include <stdio.h>
#include <stdlib.h>

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
    char name[10];
    UT_hash_handle hh;
};

int main() {
    struct my_struct *user = NULL, *s;

    s = (struct my_struct *)malloc(sizeof(struct my_struct));
    s->id = 1;
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). Risk is low because the source is a constant string. (risk 2, buffer)
     */
    strcpy(s->name, "John");
    HASH_ADD_INT(user, id, s);

    s = (struct my_struct *)malloc(sizeof(struct my_struct));
    s->id = 2;
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). Risk is low because the source is a constant string. (risk 2, buffer)
     */
    strcpy(s->name, "Jane");
    HASH_ADD_INT(user, id, s);

    for (s = user; s != NULL; s = (struct my_struct *)s->hh.next) {
        printf("Name: %s, ID: %d\n", s->name, s->id);
    }

    HASH_CLEAR(hh, user);

    return 0;
}