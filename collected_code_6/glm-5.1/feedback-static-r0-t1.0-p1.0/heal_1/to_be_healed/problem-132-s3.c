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

    size_t len = snprintf(NULL, 0, "(%d, %f, %s)", t->i, t->d, t->s);
    /* Possible weaknesses found:
     *  Checking if unsigned expression 'len' is less than zero. [unsignedLessThanZero]
     */
    if (len < 0) {
        return NULL;
    }

    char *str = malloc(len + 1);
    if (str == NULL) {
        return NULL;
    }

    int written = snprintf(str, len + 1, "(%d, %f, %s)", t->i, t->d, t->s);
    if (written < 0) {
        free(str);
        return NULL;
    }

    return str;
}

int main(void) {
    Tuple t = {42, 3.14, "hello"};
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
     *  Condition 'str==NULL' is always true
     *  Condition 'str==NULL' is always true [knownConditionTrueFalse]
     */
    if (str == NULL) {
        printf("Handled NULL input safely.\n");
    }

    return 0;
}