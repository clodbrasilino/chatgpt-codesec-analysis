#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[32];
    int height;
    int width;
} Student;

typedef struct {
    Student *items;
    size_t count;
    size_t capacity;
} StudentDictionary;

/* Possible weaknesses found:
 *  'dictionary_create' declared here
 */
StudentDictionary *dictionary_create(size_t initial_capacity) {
    StudentDictionary *dict = (StudentDictionary *)malloc(sizeof(StudentDictionary));
    if (!dict) {
        return NULL;
    }
    dict->items = (Student *)malloc(initial_capacity * sizeof(Student));
    if (!dict->items) {
        free(dict);
        return NULL;
    }
    dict->count = 0;
    dict->capacity = initial_capacity;
    return dict;
}

int dictionary_insert(StudentDictionary *dict, const char *name, int height, int width) {
    if (!dict || !name) {
        return -1;
    }
    if (dict->count >= dict->capacity) {
        size_t new_capacity = dict->capacity * 2;
        Student *new_items = (Student *)realloc(dict->items, new_capacity * sizeof(Student));
        if (!new_items) {
            return -1;
        }
        dict->items = new_items;
        dict->capacity = new_capacity;
    }
    strncpy(dict->items[dict->count].name, name, sizeof(dict->items[dict->count].name) - 1);
    dict->items[dict->count].name[sizeof(dict->items[dict->count].name) - 1] = '\0';
    dict->items[dict->count].height = height;
    dict->items[dict->count].width = width;
    dict->count++;
    return 0;
}

StudentDictionary *dictionary_filter(StudentDictionary *dict, int min_height, int max_height, int min_width, int max_width) {
    if (!dict) {
        return NULL;
    }
    StudentDictionary *filtered = dictionary_create(dict->capacity);
    if (!filtered) {
        return NULL;
    }
    for (size_t i = 0; i < dict->count; i++) {
        int h = dict->items[i].height;
        int w = dict->items[i].width;
        if (h >= min_height && h <= max_height && w >= min_width && w <= max_width) {
            if (dictionary_insert(filtered, dict->items[i].name, h, w) != 0) {
                /* Possible weaknesses found:
                 *  did you mean 'dictionary_create'?
                 *  implicit declaration of function 'dictionary_free'; did you mean 'dictionary_create'? [-Wimplicit-function-declaration]
                 *  call to undeclared function 'dictionary_free'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
                 *  previous implicit declaration is here
                 */
                dictionary_free(filtered);
                return NULL;
            }
        }
    }
    return filtered;
}

/* Possible weaknesses found:
 *  conflicting types for 'dictionary_free'
 */
void dictionary_free(StudentDictionary *dict) {
    if (dict) {
        free(dict->items);
        free(dict);
    }
}

void dictionary_print(const StudentDictionary *dict) {
    if (!dict) {
        return;
    }
    for (size_t i = 0; i < dict->count; i++) {
        printf("Name: %s, Height: %d, Width: %d\n", dict->items[i].name, dict->items[i].height, dict->items[i].width);
    }
}

int main(void) {
    StudentDictionary *dict = dictionary_create(8);
    if (!dict) {
        return EXIT_FAILURE;
    }

    dictionary_insert(dict, "Alice", 165, 55);
    dictionary_insert(dict, "Bob", 180, 75);
    dictionary_insert(dict, "Charlie", 155, 50);
    dictionary_insert(dict, "Diana", 172, 60);

    StudentDictionary *filtered = dictionary_filter(dict, 160, 185, 50, 70);
    if (!filtered) {
        dictionary_free(dict);
        return EXIT_FAILURE;
    }

    dictionary_print(filtered);

    dictionary_free(filtered);
    dictionary_free(dict);

    return EXIT_SUCCESS;
}