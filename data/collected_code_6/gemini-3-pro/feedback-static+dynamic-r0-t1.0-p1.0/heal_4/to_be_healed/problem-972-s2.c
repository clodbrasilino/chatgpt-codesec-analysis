#if defined(__linux__) || defined(__APPLE__) || defined(__unix__)
#define _POSIX_C_SOURCE 200809L
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 1024

typedef struct {
    int id;
    char *name;
} Tuple;

typedef struct {
    Tuple tuple1;
    Tuple tuple2;
} NestedTuple;

NestedTuple* concatenate_tuples(const Tuple* t1, const Tuple* t2) {
    if (t1 == NULL || t2 == NULL || t1->name == NULL || t2->name == NULL) {
        return NULL;
    }

    NestedTuple* nested = (NestedTuple*)malloc(sizeof(NestedTuple));
    if (nested == NULL) {
        return NULL;
    }

    nested->tuple1.name = NULL;
    nested->tuple2.name = NULL;

    nested->tuple1.id = t1->id;
    size_t len1 = strnlen(t1->name, MAX_NAME_LEN);
    nested->tuple1.name = (char*)malloc(len1 + 1);
    if (nested->tuple1.name != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(nested->tuple1.name, t1->name, len1);
        nested->tuple1.name[len1] = '\0';
    }

    nested->tuple2.id = t2->id;
    size_t len2 = strnlen(t2->name, MAX_NAME_LEN);
    nested->tuple2.name = (char*)malloc(len2 + 1);
    if (nested->tuple2.name != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(nested->tuple2.name, t2->name, len2);
        nested->tuple2.name[len2] = '\0';
    }

    if (nested->tuple1.name == NULL || nested->tuple2.name == NULL) {
        free(nested->tuple1.name);
        free(nested->tuple2.name);
        free(nested);
        return NULL;
    }

    return nested;
}

int main(void) {
    Tuple t1 = {1, "First"};
    Tuple t2 = {2, "Second"};

    NestedTuple* result = concatenate_tuples(&t1, &t2);
    if (result != NULL) {
        printf("NestedTuple: { { %d, %s }, { %d, %s } }\n",
               result->tuple1.id, result->tuple1.name,
               result->tuple2.id, result->tuple2.name);
        
        free(result->tuple1.name);
        free(result->tuple2.name);
        free(result);
    } else {
        fprintf(stderr, "Failed to concatenate tuples.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}