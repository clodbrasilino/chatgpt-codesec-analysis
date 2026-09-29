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

    size_t len1_first = strlen(t1->first);
    size_t len1_second = strlen(t1->second);
    size_t len2_first = strlen(t2->first);
    size_t len2_second = strlen(t2->second);

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

    memcpy(result.first, t1->first, len1_first);
    memcpy(result.first + len1_first, t2->first, len2_first);
    result.first[len1_first + len2_first] = '\0';

    memcpy(result.second, t1->second, len1_second);
    memcpy(result.second + len1_second, t2->second, len2_second);
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
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }

    free(res.first);
    free(res.second);

    return 0;
}