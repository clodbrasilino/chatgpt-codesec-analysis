#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *concatenate_list(size_t count, const char * const *list) {
    if (count > 0 && list == NULL) {
        return NULL;
    }

    size_t total_length = 0;
    for (size_t i = 0; i < count; i++) {
        if (list[i] != NULL) {
            size_t len = strlen(list[i]);
            if (len > SIZE_MAX - total_length) {
                return NULL;
            }
            total_length += len;
        }
    }

    /* Possible weaknesses found:
     *  alloc_size is assigned 'total_length+1' here.
     */
    size_t alloc_size = total_length + 1;
    /* Possible weaknesses found:
     *  Condition 'alloc_size<total_length' is always false [knownConditionTrueFalse]
     *  Condition 'alloc_size<total_length' is always false
     */
    if (alloc_size < total_length) {
        return NULL;
    }

    char *result = malloc(alloc_size);
    if (result == NULL) {
        return NULL;
    }

    size_t offset = 0;
    for (size_t i = 0; i < count; i++) {
        if (list[i] != NULL) {
            size_t len = strlen(list[i]);
            memcpy(result + offset, list[i], len);
            offset += len;
        }
    }
    result[offset] = '\0';

    return result;
}

int main(void) {
    const char *list[] = {"Hello", ", ", "world", "!"};
    size_t count = sizeof(list) / sizeof(list[0]);

    char *concatenated = concatenate_list(count, list);
    if (concatenated != NULL) {
        printf("%s\n", concatenated);
        free(concatenated);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}