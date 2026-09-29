#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int i;
    double d;
    char s[32];
} Tuple;

char *tuple_to_string(const Tuple *t) {
    if (t == NULL) {
        return strdup("");
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

    str = tuple_to_string(NULL);
    
    if (str != NULL) {
        printf("Handled NULL input safely: %s\n", str);
        free(str);
    }

    return 0;
}