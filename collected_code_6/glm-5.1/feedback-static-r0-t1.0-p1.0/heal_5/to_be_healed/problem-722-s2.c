#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char name[50];
    double height;
    double width;
} Student;

typedef struct {
    Student* items;
    size_t size;
    size_t capacity;
} Dictionary;

Dictionary dictionary_init(size_t capacity) {
    Dictionary dict;
    dict.items = (Student*)malloc(capacity * sizeof(Student));
    if (dict.items == NULL) {
        exit(EXIT_FAILURE);
    }
    dict.size = 0;
    dict.capacity = capacity;
    return dict;
}

void dictionary_free(Dictionary* dict) {
    if (dict != NULL) {
        free(dict->items);
        dict->items = NULL;
        dict->size = 0;
        dict->capacity = 0;
    }
}

int dictionary_insert(Dictionary* dict, const char* name, double height, double width) {
    if (dict == NULL || dict->size >= dict->capacity) {
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (strlen(name) >= sizeof(dict->items[dict->size].name)) {
        return -1;
    }
    snprintf(dict->items[dict->size].name, sizeof(dict->items[dict->size].name), "%s", name);
    dict->items[dict->size].height = height;
    dict->items[dict->size].width = width;
    dict->size++;
    return 0;
}

Dictionary filter_students(const Dictionary* dict, double min_height, double max_height, double min_width, double max_width) {
    if (dict == NULL) {
        Dictionary empty = {NULL, 0, 0};
        return empty;
    }

    Dictionary result = dictionary_init(dict->size);

    for (size_t i = 0; i < dict->size; i++) {
        if (dict->items[i].height >= min_height && dict->items[i].height <= max_height &&
            dict->items[i].width >= min_width && dict->items[i].width <= max_width) {
            result.items[result.size] = dict->items[i];
            result.size++;
        }
    }

    return result;
}

int main(void) {
    Dictionary students = dictionary_init(10);

    dictionary_insert(&students, "Alice", 165.0, 55.0);
    dictionary_insert(&students, "Bob", 180.0, 75.0);
    dictionary_insert(&students, "Charlie", 170.0, 65.0);
    dictionary_insert(&students, "Diana", 155.0, 50.0);

    Dictionary filtered = filter_students(&students, 160.0, 175.0, 60.0, 70.0);

    for (size_t i = 0; i < filtered.size; i++) {
        printf("Name: %s, Height: %.1f, Width: %.1f\n", filtered.items[i].name, filtered.items[i].height, filtered.items[i].width);
    }

    dictionary_free(&filtered);
    dictionary_free(&students);

    return EXIT_SUCCESS;
}