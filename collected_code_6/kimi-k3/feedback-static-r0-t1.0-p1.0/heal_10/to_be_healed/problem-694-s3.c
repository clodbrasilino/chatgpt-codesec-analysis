#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *value;
} KeyValuePair;

typedef struct {
    KeyValuePair *pairs;
    size_t count;
} Dictionary;

char **get_unique_values(const Dictionary *dict, size_t *unique_count) {
    if (dict == NULL || dict->pairs == NULL || unique_count == NULL) {
        return NULL;
    }
    
    *unique_count = 0;
    
    if (dict->count == 0) {
        return NULL;
    }
    
    char **unique_values = malloc(dict->count * sizeof(char *));
    if (unique_values == NULL) {
        return NULL;
    }
    
    size_t found = 0;
    
    for (size_t i = 0; i < dict->count; i++) {
        if (dict->pairs[i].value == NULL) {
            continue;
        }
        
        int is_duplicate = 0;
        
        for (size_t j = 0; j < found; j++) {
            if (strcmp(unique_values[j], dict->pairs[i].value) == 0) {
                is_duplicate = 1;
                break;
            }
        }
        
        if (!is_duplicate) {
            size_t len = strnlen(dict->pairs[i].value, 4096);
            unique_values[found] = malloc(len + 1);
            if (unique_values[found] == NULL) {
                for (size_t k = 0; k < found; k++) {
                    free(unique_values[k]);
                }
                free(unique_values);
                return NULL;
            }
            if (len > 0) {
                if (len < 4096) {
                    /* Possible weaknesses found:
                     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
                     */
                    if (len <= strlen(dict->pairs[i].value)) {
                        /* Possible weaknesses found:
                         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                         */
                        memcpy(unique_values[found], dict->pairs[i].value, len);
                        unique_values[found][len] = '\0';
                    } else {
                        for (size_t k = 0; k < found; k++) {
                            free(unique_values[k]);
                        }
                        free(unique_values[found]);
                        free(unique_values);
                        return NULL;
                    }
                } else {
                    /* Possible weaknesses found:
                     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
                     */
                    if (len <= strlen(dict->pairs[i].value)) {
                        /* Possible weaknesses found:
                         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                         */
                        memcpy(unique_values[found], dict->pairs[i].value, len);
                        unique_values[found][len] = '\0';
                    } else {
                        for (size_t k = 0; k < found; k++) {
                            free(unique_values[k]);
                        }
                        free(unique_values[found]);
                        free(unique_values);
                        return NULL;
                    }
                }
            } else {
                unique_values[found][0] = '\0';
            }
            found++;
        }
    }
    
    *unique_count = found;
    return unique_values;
}

void free_unique_values(char **values, size_t count) {
    if (values == NULL) {
        return;
    }
    
    for (size_t i = 0; i < count; i++) {
        free(values[i]);
    }
    free(values);
}

int main(void) {
    KeyValuePair pairs[] = {
        {"apple"},
        {"banana"},
        {"apple"},
        {"cherry"},
        {"banana"},
        {"date"}
    };
    
    Dictionary dict = {pairs, 6};
    size_t unique_count = 0;
    
    char **unique = get_unique_values(&dict, &unique_count);
    
    if (unique == NULL && unique_count == 0) {
        fprintf(stderr, "Error: Failed to extract unique values\n");
        return 1;
    }
    
    printf("Unique values (%zu):\n", unique_count);
    for (size_t i = 0; i < unique_count; i++) {
        printf("%s\n", unique[i]);
    }
    
    free_unique_values(unique, unique_count);
    
    return 0;
}