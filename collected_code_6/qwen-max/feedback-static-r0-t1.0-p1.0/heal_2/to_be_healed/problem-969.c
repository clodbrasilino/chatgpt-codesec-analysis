#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(t->name, name, 49);
    t->name[49] = '\0';
    return t;
}

void append_name(char *dest, const char *src) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t dest_len = strlen(dest);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t src_len = strlen(src);
    if (dest_len + src_len + 2 > 49) {
        dest[49] = '\0';
        return;
    }
    /* Possible weaknesses found:
     * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. Risk is low because the source is a constant string. (risk 1, buffer)
     */
    strncat(dest, ", ", 49 - dest_len);
    /* Possible weaknesses found:
     * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
     */
    strncat(dest, src, 49 - (dest_len + 2));
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