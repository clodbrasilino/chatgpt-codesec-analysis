#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>

#define MAX_DICT_SIZE 100
#define MAX_KEY_LEN 50
#define MAX_VALUE_LEN 50

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char key[MAX_KEY_LEN];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char value[MAX_VALUE_LEN];
} DictionaryEntry;

static bool is_unique(const char values[][MAX_VALUE_LEN], size_t count, const char *value) {
    if (values == NULL || value == NULL) {
        return false;
    }
    
    for (size_t i = 0; i < count; i++) {
        if (strncmp(values[i], value, MAX_VALUE_LEN) == 0) {
            return false;
        }
    }
    return true;
}

static bool safe_copy_string(char *dest, size_t dest_size, const char *src) {
    if (dest == NULL || src == NULL || dest_size == 0) {
        return false;
    }
    
    size_t src_len = strnlen(src, dest_size - 1);
    if (src_len >= dest_size) {
        return false;
    }
    
    if (src_len + 1 > dest_size) {
        return false;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dest, src, src_len);
    dest[src_len] = '\0';
    return true;
}

int extract_unique_values(const DictionaryEntry *dict, size_t dict_size, 
                         char unique_values[][MAX_VALUE_LEN], size_t max_unique) {
    if (dict == NULL || unique_values == NULL || dict_size == 0 || max_unique == 0) {
        return -1;
    }
    
    if (dict_size > SIZE_MAX / sizeof(DictionaryEntry)) {
        return -1;
    }
    
    size_t unique_count = 0;
    
    for (size_t i = 0; i < dict_size && unique_count < max_unique; i++) {
        if (strnlen(dict[i].value, MAX_VALUE_LEN) == 0) {
            continue;
        }
        
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        if (is_unique((const char (*)[MAX_VALUE_LEN])unique_values, unique_count, dict[i].value)) {
            if (!safe_copy_string(unique_values[unique_count], MAX_VALUE_LEN, dict[i].value)) {
                return -1;
            }
            unique_count++;
        }
    }
    
    if (unique_count > INT_MAX) {
        return -1;
    }
    
    return (int)unique_count;
}

int main(void) {
    DictionaryEntry dict[] = {
        {"key1", "value1"},
        {"key2", "value2"},
        {"key3", "value1"},
        {"key4", "value3"},
        {"key5", "value2"}
    };
    
    size_t dict_size = sizeof(dict) / sizeof(dict[0]);
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char unique_values[MAX_DICT_SIZE][MAX_VALUE_LEN] = {0};
    
    if (dict_size > MAX_DICT_SIZE) {
        fprintf(stderr, "Dictionary size exceeds maximum allowed\n");
        return EXIT_FAILURE;
    }
    
    int unique_count = extract_unique_values(dict, dict_size, unique_values, MAX_DICT_SIZE);
    
    if (unique_count < 0) {
        fprintf(stderr, "Error extracting unique values\n");
        return EXIT_FAILURE;
    }
    
    printf("Unique values:\n");
    for (int i = 0; i < unique_count; i++) {
        if (printf("%s\n", unique_values[i]) < 0) {
            fprintf(stderr, "Error printing output\n");
            return EXIT_FAILURE;
        }
    }
    
    return EXIT_SUCCESS;
}