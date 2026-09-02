#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strcmp'
  */

typedef struct {
    char *key;
    int value;
} Entry;

typedef struct {
    Entry *entries;
    int size;
    int capacity;
} Dictionary;

Dictionary *create_dictionary(int capacity) {
    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    if (!dict) return NULL;
    dict->entries = (Entry *)malloc(capacity * sizeof(Entry));
    if (!dict->entries) {
        free(dict);
        return NULL;
    }
    dict->size = 0;
    dict->capacity = capacity;
    return dict;
}

int dictionary_insert(Dictionary *dict, const char *key, int value) {
    for (int i = 0; i < dict->size; i++) {
        /* Possible weaknesses found:
         *  include the header <string.h> or explicitly provide a declaration for 'strcmp'
         *  call to undeclared library function 'strcmp' with type 'int (const char *, const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  implicit declaration of function 'strcmp' [-Wimplicit-function-declaration]
         */
        if (strcmp(dict->entries[i].key, key) == 0) {
            dict->entries[i].value = value;
            return 1;
        }
    }
    if (dict->size >= dict->capacity) return 0;
    /* Possible weaknesses found:
     *  include the header <string.h> or explicitly provide a declaration for 'strdup'
     *  call to undeclared library function 'strdup' with type 'char *(const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'strdup' [-Wimplicit-function-declaration]
     */
    dict->entries[dict->size].key = strdup(key);
    dict->entries[dict->size].value = value;
    dict->size++;
    return 1;
}

int dictionary_merge(Dictionary *target, Dictionary *source1, Dictionary *source2, Dictionary *source3) {
    for (int i = 0; i < source1->size; i++)
        dictionary_insert(target, source1->entries[i].key, source1->entries[i].value);
    for (int i = 0; i < source2->size; i++)
        dictionary_insert(target, source2->entries[i].key, source2->entries[i].value);
    for (int i = 0; i < source3->size; i++)
        dictionary_insert(target, source3->entries[i].key, source3->entries[i].value);
    return target->size;
}

void free_dictionary(Dictionary *dict) {
    for (int i = 0; i < dict->size; i++) {
        free(dict->entries[i].key);
    }
    free(dict->entries);
    free(dict);
}

int main() {
    Dictionary *dict1 = create_dictionary(3);
    Dictionary *dict2 = create_dictionary(3);
    Dictionary *dict3 = create_dictionary(3);
    Dictionary *merged_dict = create_dictionary(9);

    dictionary_insert(dict1, "apple", 1);
    dictionary_insert(dict1, "banana", 2);
    dictionary_insert(dict1, "cherry", 3);

    dictionary_insert(dict2, "date", 4);
    dictionary_insert(dict2, "elderberry", 5);
    dictionary_insert(dict2, "fig", 6);

    dictionary_insert(dict3, "grape", 7);
    dictionary_insert(dict3, "honeydew", 8);
    dictionary_insert(dict3, "iceberg", 9);

    dictionary_merge(merged_dict, dict1, dict2, dict3);

    for (int i = 0; i < merged_dict->size; i++) {
        printf("%s: %d\n", merged_dict->entries[i].key, merged_dict->entries[i].value);
    }

    free_dictionary(dict1);
    free_dictionary(dict2);
    free_dictionary(dict3);
    free_dictionary(merged_dict);

    return 0;
}