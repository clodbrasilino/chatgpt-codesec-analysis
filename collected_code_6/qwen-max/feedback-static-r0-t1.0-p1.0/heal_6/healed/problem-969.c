#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[51];
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
    size_t dest_len = strnlen(dest, 50);
    size_t src_len = strnlen(src, 50);
    if (dest_len + src_len + 2 >= 50) {
        dest[50] = '\0';
        return;
    }
    snprintf(dest + dest_len, 50 - dest_len, ", %s", src);
}

Tuple* join_tuples(Tuple *a, Tuple *b) {
    if (a == NULL || b == NULL) {
        return NULL;
    }
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