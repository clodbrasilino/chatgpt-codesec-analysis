#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strncpy'
  */

typedef struct {
    int id;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char name[50];
} Tuple;

Tuple* create_tuple(int id, const char *name) {
    Tuple *t = (Tuple *)malloc(sizeof(Tuple));
    if (t == NULL) {
        exit(EXIT_FAILURE);
    }
    t->id = id;
    /* Possible weaknesses found:
     *  implicit declaration of function 'strncpy' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'strncpy' with type 'char *(char *, const char *, unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     *  include the header <string.h> or explicitly provide a declaration for 'strncpy'
     */
    strncpy(t->name, name, 49);
    t->name[49] = '\0';
    return t;
}

void append_name(char *dest, const char *src) {
    /* Possible weaknesses found:
     *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'strlen' with type 'unsigned long (const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     *  include '<string.h>' or provide a declaration of 'strlen'
     *  include the header <string.h> or explicitly provide a declaration for 'strlen'
     */
    size_t dest_len = strlen(dest);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (dest_len + strlen(src) + 2 > 49) {
        dest[49] = '\0';
        return;
    }
    /* Possible weaknesses found:
     * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). Risk is low because the source is a constant string. (risk 2, buffer)
     *  implicit declaration of function 'strcat' [-Wimplicit-function-declaration]
     *  include '<string.h>' or provide a declaration of 'strcat'
     *  call to undeclared library function 'strcat' with type 'char *(char *, const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <string.h> or explicitly provide a declaration for 'strcat'
     */
    strcat(dest, ", ");
    /* Possible weaknesses found:
     * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
     */
    strcat(dest, src);
}

Tuple* join_tuples(Tuple *a, Tuple *b) {
    if (a->id != b->id) {
        return NULL;
    }
    append_name(a->name, b->name);
    free(b);
    return a;
}

int main() {
    Tuple *t1 = create_tuple(1, "Alice");
    Tuple *t2 = create_tuple(1, "Bob");
    Tuple *t3 = create_tuple(2, "Carol");

    Tuple *result = join_tuples(t1, t2);
    if (result != NULL) {
        printf("Joined: %d - %s\n", result->id, result->name);
        free(result);
    } else {
        printf("Did not join.\n");
    }

    if (t3 != NULL) {
        free(t3);
    }

    return 0;
}