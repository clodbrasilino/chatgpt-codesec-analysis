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
    snprintf(t->name, sizeof(t->name), "%s", name);
    return t;
}

void append_name(char *dest, const char *src) {
    size_t dest_len = strnlen(dest, sizeof(dest));
    size_t src_len = strnlen(src, sizeof(src));
    if (dest_len + 2 + src_len < sizeof(dest)) {
        /* Possible weaknesses found:
         * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. Risk is low because the source is a constant string. (risk 1, buffer)
         *  Size of pointer 'dest' used instead of size of its data. [pointerSize]
         */
        strncat(dest, ", ", sizeof(dest) - dest_len - 1);
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
         *  Size of pointer 'dest' used instead of size of its data. [pointerSize]
         */
        strncat(dest, src, sizeof(dest) - strlen(dest) - 1);
    } else {
        dest[sizeof(dest) - 1] = '\0';
    }
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