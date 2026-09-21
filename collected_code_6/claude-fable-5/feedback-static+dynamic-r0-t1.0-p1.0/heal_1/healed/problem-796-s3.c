#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEY_LEN 32

typedef struct {
    char key[MAX_KEY_LEN];
    int value;
} DictItem;

typedef struct {
    DictItem *items;
    size_t size;
    size_t capacity;
} Dict;

int dict_init(Dict *dict, size_t capacity)
{
    if (dict == NULL || capacity == 0) {
        return -1;
    }
    if (capacity > SIZE_MAX / sizeof(DictItem)) {
        return -1;
    }
    dict->items = calloc(capacity, sizeof(DictItem));
    if (dict->items == NULL) {
        return -1;
    }
    dict->size = 0;
    dict->capacity = capacity;
    return 0;
}

int dict_add(Dict *dict, const char *key, int value)
{
    if (dict == NULL || key == NULL) {
        return -1;
    }
    if (dict->size >= dict->capacity) {
        return -1;
    }
    size_t key_len = strnlen(key, MAX_KEY_LEN);
    if (key_len >= MAX_KEY_LEN) {
        return -1;
    }
    memcpy(dict->items[dict->size].key, key, key_len);
    dict->items[dict->size].key[key_len] = '\0';
    dict->items[dict->size].value = value;
    dict->size++;
    return 0;
}

int dict_sum(const Dict *dict, long *result)
{
    if (dict == NULL || result == NULL || dict->items == NULL) {
        return -1;
    }
    long sum = 0;
    for (size_t i = 0; i < dict->size; i++) {
        sum += (long)dict->items[i].value;
    }
    *result = sum;
    return 0;
}

void dict_free(Dict *dict)
{
    if (dict != NULL) {
        free(dict->items);
        dict->items = NULL;
        dict->size = 0;
        dict->capacity = 0;
    }
}

int main(void)
{
    Dict dict;
    long sum = 0;

    if (dict_init(&dict, 10) != 0) {
        fprintf(stderr, "Failed to initialize dictionary\n");
        return EXIT_FAILURE;
    }

    if (dict_add(&dict, "apple", 100) != 0 ||
        dict_add(&dict, "banana", 200) != 0 ||
        dict_add(&dict, "cherry", 300) != 0) {
        fprintf(stderr, "Failed to add items\n");
        dict_free(&dict);
        return EXIT_FAILURE;
    }

    if (dict_sum(&dict, &sum) != 0) {
        fprintf(stderr, "Failed to compute sum\n");
        dict_free(&dict);
        return EXIT_FAILURE;
    }

    printf("Sum of all items: %ld\n", sum);

    dict_free(&dict);
    return EXIT_SUCCESS;
}