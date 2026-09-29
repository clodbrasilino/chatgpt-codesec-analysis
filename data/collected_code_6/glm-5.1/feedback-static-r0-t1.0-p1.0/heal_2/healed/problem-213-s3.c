#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *first;
    char *second;
} StringTuple;

StringTuple concatenate_tuples(const StringTuple *a, const StringTuple *b) {
    StringTuple result;
    result.first = NULL;
    result.second = NULL;

    if (a == NULL || b == NULL) {
        return result;
    }

    size_t len_a1 = (a->first != NULL) ? strlen(a->first) : 0;
    size_t len_a2 = (a->second != NULL) ? strlen(a->second) : 0;
    size_t len_b1 = (b->first != NULL) ? strlen(b->first) : 0;
    size_t len_b2 = (b->second != NULL) ? strlen(b->second) : 0;

    result.first = (char *)malloc(len_a1 + len_b1 + 1);
    if (result.first != NULL) {
        if (len_a1 > 0) {
            memcpy(result.first, a->first, len_a1);
        }
        if (len_b1 > 0) {
            memcpy(result.first + len_a1, b->first, len_b1);
        }
        result.first[len_a1 + len_b1] = '\0';
    }

    result.second = (char *)malloc(len_a2 + len_b2 + 1);
    if (result.second != NULL) {
        if (len_a2 > 0) {
            memcpy(result.second, a->second, len_a2);
        }
        if (len_b2 > 0) {
            memcpy(result.second + len_a2, b->second, len_b2);
        }
        result.second[len_a2 + len_b2] = '\0';
    }

    if (result.first == NULL || result.second == NULL) {
        free(result.first);
        free(result.second);
        result.first = NULL;
        result.second = NULL;
    }

    return result;
}

int main(void) {
    StringTuple t1 = {"Hello, ", "C "};
    StringTuple t2 = {"World!", "Developer"};

    StringTuple res = concatenate_tuples(&t1, &t2);

    if (res.first != NULL && res.second != NULL) {
        printf("First: %s\n", res.first);
        printf("Second: %s\n", res.second);
    } else {
        printf("Allocation failed\n");
        return 1;
    }

    free(res.first);
    free(res.second);

    return 0;
}