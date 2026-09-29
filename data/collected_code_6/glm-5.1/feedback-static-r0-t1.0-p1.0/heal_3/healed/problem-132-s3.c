#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

typedef struct {
    int i;
    double d;
    char *s;
} Tuple;

char *tuple_to_string(const Tuple *t) {
    if (t == NULL) {
        return NULL;
    }

    if (t->s == NULL) {
        return NULL;
    }

    int len = snprintf(NULL, 0, "(%d, %f, %s)", t->i, t->d, t->s);
    if (len < 0) {
        return NULL;
    }

    char *str = malloc((size_t)len + 1);
    if (str == NULL) {
        return NULL;
    }

    int written = snprintf(str, (size_t)len + 1, "(%d, %f, %s)", t->i, t->d, t->s);
    if (written < 0 || written != len) {
        free(str);
        return NULL;
    }

    return str;
}

int main(void) {
    Tuple t;
    t.i = 42;
    t.d = 3.14;
    t.s = strdup("hello");
    if (t.s == NULL) {
        return 1;
    }

    char *str = tuple_to_string(&t);

    if (str != NULL) {
        printf("%s\n", str);
        free(str);
    }

    str = tuple_to_string(NULL);

    if (str == NULL) {
        printf("Handled NULL input safely.\n");
    }

    free(t.s);

    return 0;
}