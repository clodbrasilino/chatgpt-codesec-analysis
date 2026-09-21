#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    char *key;
    char *value;
} DictItem;

typedef struct {
    DictItem *items;
    size_t size;
    size_t capacity;
} Dictionary;

Dictionary *dict_create(size_t initial_capacity) {
    Dictionary *dict = malloc(sizeof(Dictionary));
    if (dict == NULL) {
        return NULL;
    }
    if (initial_capacity == 0) {
        initial_capacity = 1;
    }
    dict->items = malloc(initial_capacity * sizeof(DictItem));
    if (dict->items == NULL) {
        free(dict);
        return NULL;
    }
    dict->size = 0;
    dict->capacity = initial_capacity;
    return dict;
}

int dict_add(Dictionary *dict, const char *key, size_t key_len, const char *value, size_t value_len) {
    if (dict == NULL || key == NULL) {
        return -1;
    }
    if (key_len == SIZE_MAX) {
        return -1;
    }
    if (value != NULL && value_len == SIZE_MAX) {
        return -1;
    }
    if (dict->size >= dict->capacity) {
        size_t new_capacity = dict->capacity * 2;
        if (new_capacity < dict->capacity) {
            return -1;
        }
        DictItem *new_items = realloc(dict->items, new_capacity * sizeof(DictItem));
        if (new_items == NULL) {
            return -1;
        }
        dict->items = new_items;
        dict->capacity = new_capacity;
    }
    size_t key_alloc = key_len + 1;
    dict->items[dict->size].key = malloc(key_alloc);
    if (dict->items[dict->size].key == NULL) {
        return -1;
    }
    if (key_len > 0) {
        if (strnlen(key, key_len) < key_len) {
            free(dict->items[dict->size].key);
            return -1;
        }
        memcpy(dict->items[dict->size].key, key, key_len);
    }
    dict->items[dict->size].key[key_len] = '\0';
    if (value != NULL) {
        size_t value_alloc = value_len + 1;
        dict->items[dict->size].value = malloc(value_alloc);
        if (dict->items[dict->size].value == NULL) {
            free(dict->items[dict->size].key);
            return -1;
        }
        if (value_len > 0) {
            if (strnlen(value, value_len) < value_len) {
                free(dict->items[dict->size].value);
                free(dict->items[dict->size].key);
                return -1;
            }
            memcpy(dict->items[dict->size].value, value, value_len);
        }
        dict->items[dict->size].value[value_len] = '\0';
    } else {
        dict->items[dict->size].value = malloc(1);
        if (dict->items[dict->size].value == NULL) {
            free(dict->items[dict->size].key);
            return -1;
        }
        dict->items[dict->size].value[0] = '\0';
    }
    dict->size++;
    return 0;
}

void dict_drop_empty(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }
    size_t write_index = 0;
    for (size_t i = 0; i < dict->size; i++) {
        if (dict->items[i].value != NULL && dict->items[i].value[0] != '\0') {
            if (write_index != i) {
                dict->items[write_index] = dict->items[i];
            }
            write_index++;
        } else {
            free(dict->items[i].key);
            free(dict->items[i].value);
        }
    }
    dict->size = write_index;
}

void dict_free(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }
    for (size_t i = 0; i < dict->size; i++) {
        free(dict->items[i].key);
        free(dict->items[i].value);
    }
    free(dict->items);
    free(dict);
}

void dict_print(const Dictionary *dict) {
    if (dict == NULL) {
        return;
    }
    printf("{");
    for (size_t i = 0; i < dict->size; i++) {
        printf("\"%s\": \"%s\"", dict->items[i].key, dict->items[i].value);
        if (i < dict->size - 1) {
            printf(", ");
        }
    }
    printf("}\n");
}

int main(void) {
    Dictionary *dict = dict_create(4);
    if (dict == NULL) {
        fprintf(stderr, "Failed to create dictionary\n");
        return EXIT_FAILURE;
    }

    const char *name_key = "name";
    const char *name_value = "John";
    const char *email_key = "email";
    const char *email_value = "";
    const char *city_key = "city";
    const char *city_value = "New York";
    const char *phone_key = "phone";
    const char *phone_value = "";
    const char *country_key = "country";
    const char *country_value = "USA";

    if (dict_add(dict, name_key, strlen(name_key), name_value, strlen(name_value)) != 0 ||
        dict_add(dict, email_key, strlen(email_key), email_value, 0) != 0 ||
        dict_add(dict, city_key, strlen(city_key), city_value, strlen(city_value)) != 0 ||
        dict_add(dict, phone_key, strlen(phone_key), phone_value, 0) != 0 ||
        dict_add(dict, country_key, strlen(country_key), country_value, strlen(country_value)) != 0) {
        fprintf(stderr, "Failed to add items\n");
        dict_free(dict);
        return EXIT_FAILURE;
    }

    printf("Before: ");
    dict_print(dict);

    dict_drop_empty(dict);

    printf("After: ");
    dict_print(dict);

    dict_free(dict);
    return EXIT_SUCCESS;
}