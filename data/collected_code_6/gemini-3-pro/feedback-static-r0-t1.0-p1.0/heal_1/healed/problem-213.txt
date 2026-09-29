#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 8192

typedef struct {
    char *first;
    char *second;
} StringTuple;

StringTuple* concat_tuples(const StringTuple *t1, const StringTuple *t2) {
    if (!t1 || !t2 || !t1->first || !t1->second || !t2->first || !t2->second) {
        return NULL;
    }

    StringTuple *result = (StringTuple *)malloc(sizeof(StringTuple));
    if (!result) {
        return NULL;
    }

    size_t f1_len = strnlen(t1->first, MAX_STR_LEN);
    size_t f2_len = strnlen(t2->first, MAX_STR_LEN);
    size_t len1 = f1_len + f2_len + 1;
    
    result->first = (char *)malloc(len1);
    if (!result->first) {
        free(result);
        return NULL;
    }

    size_t s1_len = strnlen(t1->second, MAX_STR_LEN);
    size_t s2_len = strnlen(t2->second, MAX_STR_LEN);
    size_t len2 = s1_len + s2_len + 1;
    
    result->second = (char *)malloc(len2);
    if (!result->second) {
        free(result->first);
        free(result);
        return NULL;
    }

    snprintf(result->first, len1, "%s%s", t1->first, t2->first);
    snprintf(result->second, len2, "%s%s", t1->second, t2->second);

    return result;
}

void free_tuple(StringTuple *t) {
    if (t) {
        free(t->first);
        free(t->second);
        free(t);
    }
}

int main(void) {
    StringTuple t1 = {"Hello, ", "Open"};
    StringTuple t2 = {"World!", "AI"};

    StringTuple *result = concat_tuples(&t1, &t2);
    if (result) {
        printf("First: %s\n", result->first);
        printf("Second: %s\n", result->second);
        free_tuple(result);
    } else {
        printf("Concatenation failed.\n");
    }

    return 0;
}