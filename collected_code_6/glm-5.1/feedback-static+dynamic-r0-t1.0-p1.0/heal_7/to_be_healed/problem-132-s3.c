#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int i;
    double d;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char s[32];
} Tuple;

char *tuple_to_string(const Tuple *t) {
    if (t == NULL) {
        return NULL;
    }

    int len = snprintf(NULL, 0, "(%d, %f, %.31s)", t->i, t->d, t->s);
    if (len < 0) {
        return NULL;
    }

    char *str = malloc(len + 1);
    if (str == NULL) {
        return NULL;
    }

    int written = snprintf(str, len + 1, "(%d, %f, %.31s)", t->i, t->d, t->s);
    if (written < 0 || written >= len + 1) {
        free(str);
        return NULL;
    }

    return str;
}

int main(void) {
    Tuple t = {42, 3.14, "hello"};
    t.s[strnlen(t.s, sizeof(t.s))] = '\0';

    char *str = tuple_to_string(&t);

    if (str != NULL) {
        printf("%s\n", str);
        free(str);
    }

    str = tuple_to_string(&t);
    if (str != NULL) {
        printf("%s\n", str);
        free(str);
    }

    return EXIT_SUCCESS;
}