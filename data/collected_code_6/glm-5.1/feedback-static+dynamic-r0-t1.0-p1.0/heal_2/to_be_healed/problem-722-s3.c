#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char name[50];
    float height;
    float width;
} Student;

typedef struct {
    Student *items;
    size_t count;
    size_t capacity;
} StudentDictionary;

StudentDictionary dictionary_create(size_t capacity) {
    StudentDictionary dict;
    if (capacity == 0) {
        capacity = 1;
    }
    dict.items = (Student *)malloc(capacity * sizeof(Student));
    if (dict.items == NULL) {
        exit(EXIT_FAILURE);
    }
    dict.count = 0;
    dict.capacity = capacity;
    return dict;
}

void dictionary_insert(StudentDictionary *dict, const char *name, float height, float width) {
    if (dict->count >= dict->capacity) {
        size_t new_capacity = dict->capacity * 2;
        Student *new_items = (Student *)realloc(dict->items, new_capacity * sizeof(Student));
        if (new_items == NULL) {
            exit(EXIT_FAILURE);
        }
        dict->items = new_items;
        dict->capacity = new_capacity;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t name_len = strlen(name);
    size_t buffer_size = sizeof(dict->items[dict->count].name);
    if (name_len >= buffer_size) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dict->items[dict->count].name, name, buffer_size - 1);
        dict->items[dict->count].name[buffer_size - 1] = '\0';
    } else {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dict->items[dict->count].name, name, name_len + 1);
    }
    dict->items[dict->count].height = height;
    dict->items[dict->count].width = width;
    dict->count++;
}

StudentDictionary filter_students(const StudentDictionary *dict, float min_height, float max_height, float min_width, float max_width) {
    StudentDictionary result = dictionary_create(dict->count);
    for (size_t i = 0; i < dict->count; i++) {
        if (dict->items[i].height >= min_height && dict->items[i].height <= max_height &&
            dict->items[i].width >= min_width && dict->items[i].width <= max_width) {
            dictionary_insert(&result, dict->items[i].name, dict->items[i].height, dict->items[i].width);
        }
    }
    return result;
}

void dictionary_free(StudentDictionary *dict) {
    if (dict->items != NULL) {
        free(dict->items);
        dict->items = NULL;
    }
    dict->count = 0;
    dict->capacity = 0;
}

int main(void) {
    StudentDictionary dict = dictionary_create(4);
    
    dictionary_insert(&dict, "Alice", 165.5, 55.0);
    dictionary_insert(&dict, "Bob", 180.0, 75.5);
    dictionary_insert(&dict, "Charlie", 172.0, 68.2);
    dictionary_insert(&dict, "Diana", 158.0, 50.5);
    
    float min_h = 160.0;
    float max_h = 175.0;
    float min_w = 55.0;
    float max_w = 70.0;
    
    StudentDictionary filtered = filter_students(&dict, min_h, max_h, min_w, max_w);
    
    for (size_t i = 0; i < filtered.count; i++) {
        printf("%s: Height=%.1f, Width=%.1f\n", filtered.items[i].name, filtered.items[i].height, filtered.items[i].width);
    }
    
    dictionary_free(&filtered);
    dictionary_free(&dict);
    
    return 0;
}