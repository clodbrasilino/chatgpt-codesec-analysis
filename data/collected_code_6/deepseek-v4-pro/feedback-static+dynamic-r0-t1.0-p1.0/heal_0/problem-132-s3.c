#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int a;
    int b;
} tuple_t;

char *tuple_to_string(tuple_t t) {
    int len = snprintf(NULL, 0, "(%d, %d)", t.a, t.b);
    if (len < 0) return NULL;
    char *str = (char *)malloc(len + 1);
    if (str == NULL) return NULL;
    snprintf(str, len + 1, "(%d, %d)", t.a, t.b);
    return str;
}

int main(void) {
    tuple_t t = {3, 4};
    char *result = tuple_to_string(t);
    if (result == NULL) {
        return 1;
    }
    printf("%s\n", result);
    free(result);
    return 0;
}