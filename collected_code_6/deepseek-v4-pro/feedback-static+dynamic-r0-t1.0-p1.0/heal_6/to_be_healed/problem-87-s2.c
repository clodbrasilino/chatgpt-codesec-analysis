#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define INITIAL_CAPACITY 16
#define MAX_KEY_LENGTH 64
#define MAX_VALUE_LENGTH 256
#define FNV_OFFSET 14695981039346656037ULL
#define FNV_PRIME 1099511628211ULL

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char key[MAX_KEY_LENGTH];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char value[MAX_VALUE_LENGTH];
} Entry;

typedef struct {
    Entry *entries;
    size_t size;
    size_t capacity;
} Dictionary;

static size_t hash_string(const char *str) {
    size_t hash = 5381;
    unsigned char c;
    
    while ((c = (unsigned char)*str++) != '\0') {
        hash = ((hash << 5) + hash) + (size_t)c;
    }
    
    return hash;
}

static Dictionary *create_dictionary(void) {
    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    if (!dict) {
        return NULL;
    }
    
    dict->entries = (Entry *)calloc(INITIAL_CAPACITY, sizeof(Entry));
    if (!dict->entries) {
        free(dict);
        return NULL;
    }
    
    dict->size = 0;
    dict->capacity = INITIAL_CAPACITY;
    
    return dict;
}

static int resize_dictionary(Dictionary *dict, size_t new_capacity) {
    if (!dict || new_capacity <= dict->capacity) {
        return -1;
    }
    
    Entry *new_entries = (Entry *)calloc(new_capacity, sizeof(Entry));
    if (!new_entries) {
        return -1;
    }
    
    for (size_t i = 0; i < dict->capacity; i++) {
        if (dict->entries[i].key[0] != '\0') {
            size_t hash = hash_string(dict->entries[i].key);
            size_t index = hash % new_capacity;
            
            while (new_entries[index].key[0] != '\0') {
                index = (index + 1) % new_capacity;
            }
            
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(new_entries[index].key, dict->entries[i].key, MAX_KEY_LENGTH - 1);
            new_entries[index].key[MAX_KEY_LENGTH - 1] = '\0';
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(new_entries[index].value, dict->entries[i].value, MAX_VALUE_LENGTH - 1);
            new_entries[index].value[MAX_VALUE_LENGTH - 1] = '\0';
        }
    }
    
    free(dict->entries);
    dict->entries = new_entries;
    dict->capacity = new_capacity;
    
    return 0;
}

static int insert_entry(Dictionary *dict, const char *key, const char *value) {
    if (!dict || !key || !value) {
        return -1;
    }
    
    size_t key_len = strnlen(key, MAX_KEY_LENGTH);
    size_t value_len = strnlen(value, MAX_VALUE_LENGTH);
    
    if (key_len >= MAX_KEY_LENGTH || value_len >= MAX_VALUE_LENGTH) {
        return -1;
    }
    
    if (dict->size >= dict->capacity / 2) {
        if (resize_dictionary(dict, dict->capacity * 2) != 0) {
            return -1;
        }
    }
    
    size_t hash = hash_string(key);
    size_t index = hash % dict->capacity;
    
    while (dict->entries[index].key[0] != '\0') {
        if (strcmp(dict->entries[index].key, key) == 0) {
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(dict->entries[index].value, value, MAX_VALUE_LENGTH - 1);
            dict->entries[index].value[MAX_VALUE_LENGTH - 1] = '\0';
            return 0;
        }
        index = (index + 1) % dict->capacity;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(dict->entries[index].key, key, MAX_KEY_LENGTH - 1);
    dict->entries[index].key[MAX_KEY_LENGTH - 1] = '\0';
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(dict->entries[index].value, value, MAX_VALUE_LENGTH - 1);
    dict->entries[index].value[MAX_VALUE_LENGTH - 1] = '\0';
    dict->size++;
    
    return 0;
}

static Dictionary *merge_dictionaries(Dictionary *dict1, Dictionary *dict2, Dictionary *dict3) {
    if (!dict1 || !dict2 || !dict3) {
        return NULL;
    }
    
    Dictionary *merged = create_dictionary();
    if (!merged) {
        return NULL;
    }
    
    Dictionary *dicts[3] = {dict1, dict2, dict3};
    
    for (int d = 0; d < 3; d++) {
        for (size_t i = 0; i < dicts[d]->capacity; i++) {
            if (dicts[d]->entries[i].key[0] != '\0') {
                if (insert_entry(merged, dicts[d]->entries[i].key, dicts[d]->entries[i].value) != 0) {
                    free(merged->entries);
                    free(merged);
                    return NULL;
                }
            }
        }
    }
    
    return merged;
}

static void destroy_dictionary(Dictionary *dict) {
    if (dict) {
        free(dict->entries);
        free(dict);
    }
}

static void print_dictionary(Dictionary *dict) {
    if (!dict) {
        printf("Invalid dictionary\n");
        return;
    }
    
    for (size_t i = 0; i < dict->capacity; i++) {
        if (dict->entries[i].key[0] != '\0') {
            printf("%s: %s\n", dict->entries[i].key, dict->entries[i].value);
        }
    }
}

static int initialize_test_dictionary(Dictionary *dict, const char **keys, const char **values, size_t count) {
    if (!dict || !keys || !values) {
        return -1;
    }
    
    for (size_t i = 0; i < count; i++) {
        if (insert_entry(dict, keys[i], values[i]) != 0) {
            return -1;
        }
    }
    
    return 0;
}

int main(void) {
    Dictionary *dict1 = create_dictionary();
    Dictionary *dict2 = create_dictionary();
    Dictionary *dict3 = create_dictionary();
    
    if (!dict1 || !dict2 || !dict3) {
        destroy_dictionary(dict1);
        destroy_dictionary(dict2);
        destroy_dictionary(dict3);
        return EXIT_FAILURE;
    }
    
    const char *keys1[] = {"name", "age", "city"};
    const char *values1[] = {"Alice", "25", "New York"};
    
    const char *keys2[] = {"country", "language", "city"};
    const char *values2[] = {"USA", "English", "Boston"};
    
    const char *keys3[] = {"age", "hobby", "profession"};
    const char *values3[] = {"30", "Reading", "Engineer"};
    
    if (initialize_test_dictionary(dict1, keys1, values1, 3) != 0 ||
        initialize_test_dictionary(dict2, keys2, values2, 3) != 0 ||
        initialize_test_dictionary(dict3, keys3, values3, 3) != 0) {
        destroy_dictionary(dict1);
        destroy_dictionary(dict2);
        destroy_dictionary(dict3);
        return EXIT_FAILURE;
    }
    
    Dictionary *merged = merge_dictionaries(dict1, dict2, dict3);
    if (!merged) {
        destroy_dictionary(dict1);
        destroy_dictionary(dict2);
        destroy_dictionary(dict3);
        return EXIT_FAILURE;
    }
    
    print_dictionary(merged);
    
    destroy_dictionary(dict1);
    destroy_dictionary(dict2);
    destroy_dictionary(dict3);
    destroy_dictionary(merged);
    
    return EXIT_SUCCESS;
}