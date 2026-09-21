#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *concatenate_list(const char *const list[], size_t count) {
    size_t total_length = 0;
    size_t *lengths = NULL;
    
    if (count == 0) {
        char *result = (char *)malloc(1);
        if (result != NULL) {
            result[0] = '\0';
        }
        return result;
    }
    
    lengths = (size_t *)malloc(count * sizeof(size_t));
    if (lengths == NULL) {
        return NULL;
    }
    
    for (size_t i = 0; i < count; i++) {
        if (list[i] != NULL) {
            size_t len = strnlen(list[i], SIZE_MAX);
            if (len > SIZE_MAX - total_length) {
                free(lengths);
                return NULL;
            }
            total_length += len;
            lengths[i] = len;
        } else {
            lengths[i] = 0;
        }
    }
    
    if (total_length == SIZE_MAX) {
        free(lengths);
        return NULL;
    }
    
    char *result = (char *)malloc(total_length + 1);
    if (result == NULL) {
        free(lengths);
        return NULL;
    }
    
    size_t offset = 0;
    for (size_t i = 0; i < count; i++) {
        if (list[i] != NULL && lengths[i] > 0) {
            if (offset + lengths[i] > total_length) {
                free(lengths);
                free(result);
                return NULL;
            }
            if (lengths[i] <= total_length - offset) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + offset, list[i], lengths[i]);
                offset += lengths[i];
            } else {
                free(lengths);
                free(result);
                return NULL;
            }
        }
    }
    result[offset] = '\0';
    
    free(lengths);
    return result;
}

int main(void) {
    const char *words[] = {"Hello", " ", "World", "!"};
    size_t count = sizeof(words) / sizeof(words[0]);
    
    char *result = concatenate_list(words, count);
    if (result != NULL) {
        free(result);
    }
    
    return 0;
}