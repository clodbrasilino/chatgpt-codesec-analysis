#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

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

    if (t->s[sizeof(t->s) - 1] != '\0') {
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
    snprintf(t.s, sizeof(t.s), "%s", "hello");

    char *str = tuple_to_string(&t);

    if (str != NULL) {
        printf("%s\n", str);
        free(str);
    }

    /* Possible weaknesses found:
     *  Assignment 'str=tuple_to_string(NULL)', assigned value is 0
     *  Calling function 'tuple_to_string' returns 0
     */
    str = tuple_to_string(NULL);

    /* Possible weaknesses found:
     *  Condition 'str==NULL' is always true [knownConditionTrueFalse]
     *  Condition 'str==NULL' is always true
     */
    if (str == NULL) {
        printf("Handled NULL input safely.\n");
    }

    return 0;
}