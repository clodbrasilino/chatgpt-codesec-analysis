#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char** insert_string(char** list, size_t size, const char* prefix) {
    if (list == NULL || prefix == NULL) {
        return NULL;
    }

    size_t prefix_len = strlen(prefix);

    for (size_t i = 0; i < size; i++) {
        if (list[i] == NULL) {
            continue;
        }

        size_t item_len = strlen(list[i]);

        if (item_len > SIZE_MAX - prefix_len) {
            free(list[i]);
            list[i] = NULL;
            continue;
        }

        size_t new_len = prefix_len + item_len;
        char* new_item = (char*)malloc(new_len + 1);
        if (new_item == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(list[j]);
                list[j] = NULL;
            }
            return NULL;
        }

        memcpy(new_item, prefix, prefix_len);
        memcpy(new_item + prefix_len, list[i], item_len);
        new_item[new_len] = '\0';

        free(list[i]);
        list[i] = new_item;
    }

    return list;
}

int main() {
    char* items[] = {
        (char*)malloc(6),
        (char*)malloc(6),
        (char*)malloc(7)
    };

    if (items[0] == NULL || items[1] == NULL || items[2] == NULL) {
        free(items[0]);
        free(items[1]);
        free(items[2]);
        return 1;
    }

    snprintf(items[0], 6, "apple");
    snprintf(items[1], 6, "banana");
    snprintf(items[2], 7, "cherry");

    size_t count = sizeof(items) / sizeof(items[0]);

    char** result = insert_string(items, count, "my_");

    if (result != NULL) {
        for (size_t i = 0; i < count; i++) {
            if (items[i] != NULL) {
                printf("%s\n", items[i]);
            }
        }
    }

    for (size_t i = 0; i < count; i++) {
        free(items[i]);
    }

    return 0;
}