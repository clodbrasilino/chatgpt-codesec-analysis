#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char name[51];
} Tuple;

Tuple* create_tuple(int id, const char *name) {
    Tuple *t = (Tuple *)malloc(sizeof(Tuple));
    if (t == NULL) {
        exit(EXIT_FAILURE);
    }
    t->id = id;
    snprintf(t->name, sizeof(t->name) - 1, "%s", name);
    t->name[sizeof(t->name) - 1] = '\0';
    return t;
}

void append_name(char *dest, const char *src) {
    size_t dest_len = strnlen(dest, sizeof(dest) - 1);
    size_t src_len = strnlen(src, sizeof(src) - 1);
    if (dest_len + src_len + 2 >= sizeof(dest) - 1) {
        dest[sizeof(dest) - 1] = '\0';
        return;
    }
    snprintf(dest + dest_len, sizeof(dest) - dest_len - 1, ", %s", src);
}

Tuple* join_tuples(Tuple *a, Tuple *b) {
    /* Possible weaknesses found:
     *  Null pointer dereference
     *  Assuming that condition 'b==NULL' is not redundant
     *  Either the condition 'a==NULL' is redundant or there is possible null pointer dereference: a. [nullPointerRedundantCheck]
     *  Either the condition 'b==NULL' is redundant or there is possible null pointer dereference: b. [nullPointerRedundantCheck]
     *  Assuming that condition 'a==NULL' is not redundant
     */
    if (a->id != b->id || a == NULL || b == NULL) {
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