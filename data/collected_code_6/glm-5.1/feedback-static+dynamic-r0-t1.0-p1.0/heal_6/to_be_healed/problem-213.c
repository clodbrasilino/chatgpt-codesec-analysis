#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *first;
    char *second;
} StringTuple;

StringTuple concatenate_tuples(const StringTuple *t1, const StringTuple *t2) {
    StringTuple result = {NULL, NULL};

    if (t1 == NULL || t2 == NULL || t1->first == NULL || t1->second == NULL || t2->first == NULL || t2->second == NULL) {
        return result;
    }

    size_t len1_first = strnlen(t1->first, SIZE_MAX);
    size_t len1_second = strnlen(t1->second, SIZE_MAX);
    size_t len2_first = strnlen(t2->first, SIZE_MAX);
    size_t len2_second = strnlen(t2->second, SIZE_MAX);

    result.first = (char *)malloc(len1_first + len2_first + 1);
    if (result.first == NULL) {
        return result;
    }

    result.second = (char *)malloc(len1_second + len2_second + 1);
    if (result.second == NULL) {
        free(result.first);
        result.first = NULL;
        return result;
    }

    /* Possible weaknesses found:
     *  implicit declaration of function 'memcpy_s'; did you mean 'memcpy'? [-Wimplicit-function-declaration]
     *  call to undeclared function 'memcpy_s'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  did you mean 'memcpy'?
     */
    memcpy_s(result.first, len1_first + len2_first + 1, t1->first, len1_first);
    memcpy_s(result.first + len1_first, len2_first + 1, t2->first, len2_first);
    result.first[len1_first + len2_first] = '\0';

    memcpy_s(result.second, len1_second + len2_second + 1, t1->second, len1_second);
    memcpy_s(result.second + len1_second, len2_second + 1, t2->second, len2_second);
    result.second[len1_second + len2_second] = '\0';

    return result;
}

int main(void) {
    StringTuple t1 = {"Hello, ", "Good "};
    StringTuple t2 = {"World!", "Morning!"};

    StringTuple res = concatenate_tuples(&t1, &t2);

    if (res.first != NULL && res.second != NULL) {
        printf("First: %s\n", res.first);
        printf("Second: %s\n", res.second);
        free(res.first);
        free(res.second);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
        free(res.first);
        free(res.second);
    }

    return 0;
}