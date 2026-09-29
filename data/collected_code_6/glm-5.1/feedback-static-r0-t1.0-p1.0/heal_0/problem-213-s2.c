#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *first;
    char *second;
} StringTuple;

StringTuple concatenate_tuples(const StringTuple *t1, const StringTuple *t2) {
    StringTuple result = {NULL, NULL};

    if (t1 == NULL || t2 == NULL) {
        return result;
    }

    size_t len1_first = (t1->first != NULL) ? strlen(t1->first) : 0;
    size_t len2_first = (t2->first != NULL) ? strlen(t2->first) : 0;
    size_t len1_second = (t1->second != NULL) ? strlen(t1->second) : 0;
    size_t len2_second = (t2->second != NULL) ? strlen(t2->second) : 0;

    result.first = (char *)malloc(len1_first + len2_first + 1);
    result.second = (char *)malloc(len1_second + len2_second + 1);

    if (result.first == NULL || result.second == NULL) {
        free(result.first);
        free(result.second);
        result.first = NULL;
        result.second = NULL;
        return result;
    }

    if (t1->first != NULL) {
        memcpy(result.first, t1->first, len1_first);
    }
    if (t2->first != NULL) {
        memcpy(result.first + len1_first, t2->first, len2_first);
    }
    result.first[len1_first + len2_first] = '\0';

    if (t1->second != NULL) {
        memcpy(result.second, t1->second, len1_second);
    }
    if (t2->second != NULL) {
        memcpy(result.second + len1_second, t2->second, len2_second);
    }
    result.second[len1_second + len2_second] = '\0';

    return result;
}

int main(void) {
    StringTuple t1 = {"hello, ", "world, "};
    StringTuple t2 = {"C ", "developer"};
    StringTuple t3 = {NULL, "only second"};
    StringTuple t4 = {"only first", NULL};
    StringTuple t5 = {NULL, NULL};

    StringTuple r1 = concatenate_tuples(&t1, &t2);
    StringTuple r2 = concatenate_tuples(&t3, &t4);
    StringTuple r3 = concatenate_tuples(&t5, &t5);
    StringTuple r4 = concatenate_tuples(NULL, &t1);

    if (r1.first != NULL && r1.second != NULL) {
        printf("%s | %s\n", r1.first, r1.second);
        free(r1.first);
        free(r1.second);
    }

    if (r2.first != NULL && r2.second != NULL) {
        printf("%s | %s\n", r2.first, r2.second);
        free(r2.first);
        free(r2.second);
    }

    if (r3.first != NULL && r3.second != NULL) {
        printf("%s | %s\n", r3.first, r3.second);
        free(r3.first);
        free(r3.second);
    }

    if (r4.first == NULL && r4.second == NULL) {
        printf("NULL input handled correctly.\n");
    }

    return 0;
}