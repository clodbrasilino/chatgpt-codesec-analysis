#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *duplicate_string(const char *src) {
    if (src == NULL) {
        return NULL;
    }
    
    size_t len = 0;
    while (src[len] != '\0' && len < 4096) {
        len++;
    }
    
    char *dest = malloc(len + 1);
    
    if (dest != NULL) {
        snprintf(dest, len + 1, "%s", src);
    }
    
    return dest;
}

int remove_words(char **list, size_t *list_len, const char **targets, size_t targets_len) {
    if (list == NULL || list_len == NULL || targets == NULL) {
        return -1;
    }

    size_t write_idx = 0;
    size_t original_len = *list_len;

    for (size_t i = 0; i < original_len; i++) {
        if (list[i] == NULL) {
            continue;
        }

        int should_remove = 0;
        for (size_t j = 0; j < targets_len; j++) {
            if (targets[j] != NULL && strcmp(list[i], targets[j]) == 0) {
                should_remove = 1;
                break;
            }
        }

        if (should_remove) {
            free(list[i]);
        } else {
            list[write_idx] = list[i];
            write_idx++;
        }
    }

    for (size_t i = write_idx; i < original_len; i++) {
        list[i] = NULL;
    }

    *list_len = write_idx;
    return 0;
}

int main(void) {
    size_t list_len = 5;
    char **my_list = malloc(list_len * sizeof(char *));
    
    if (my_list == NULL) {
        return 1;
    }

    my_list[0] = duplicate_string("apple");
    my_list[1] = duplicate_string("banana");
    my_list[2] = duplicate_string("cherry");
    my_list[3] = duplicate_string("date");
    my_list[4] = duplicate_string("banana");

    for (size_t i = 0; i < list_len; i++) {
        if (my_list[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(my_list[j]);
            }
            free(my_list);
            return 1;
        }
    }

    const char *targets[] = {"banana", "date"};
    size_t targets_len = sizeof(targets) / sizeof(targets[0]);

    if (remove_words(my_list, &list_len, targets, targets_len) != 0) {
        for (size_t i = 0; i < list_len; i++) {
            free(my_list[i]);
        }
        free(my_list);
        return 1;
    }

    for (size_t i = 0; i < list_len; i++) {
        if (my_list[i] != NULL) {
            printf("%s\n", my_list[i]);
            free(my_list[i]);
        }
    }
    
    free(my_list);

    return 0;
}