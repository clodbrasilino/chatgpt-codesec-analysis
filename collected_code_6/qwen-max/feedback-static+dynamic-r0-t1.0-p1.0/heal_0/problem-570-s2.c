#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct List {
    char **strings;
    int count;
} List;

void free_list(List *list) {
    for (int i = 0; i < list->count; i++) {
        free(list->strings[i]);
    }
    free(list->strings);
}

List *create_list(int size) {
    List *list = (List *)malloc(sizeof(List));
    if (list == NULL) return NULL;
    list->strings = (char **)calloc(size, sizeof(char *));
    if (list->strings == NULL) {
        free(list);
        return NULL;
    }
    list->count = 0;
    return list;
}

void add_string(List *list, const char *str) {
    list->strings[list->count] = strdup(str);
    if (list->strings[list->count] != NULL) {
        list->count++;
    }
}

int contains_substring(const char *haystack, const char *needle) {
    return strstr(haystack, needle) != NULL;
}

List *filter_strings(List *original, const char *to_remove) {
    List *filtered = create_list(original->count);
    if (filtered == NULL) return NULL;

    for (int i = 0; i < original->count; i++) {
        if (!contains_substring(original->strings[i], to_remove)) {
            add_string(filtered, original->strings[i]);
        }
    }

    return filtered;
}

void print_list(const List *list) {
    for (int i = 0; i < list->count; i++) {
        printf("%s\n", list->strings[i]);
    }
}

int main() {
    List *list = create_list(10);
    if (list == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    add_string(list, "apple");
    add_string(list, "banana");
    add_string(list, "grape");
    add_string(list, "blueberry");

    printf("Original List:\n");
    print_list(list);

    const char *to_remove = "blue";
    List *filtered = filter_strings(list, to_remove);
    if (filtered == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free_list(list);
        return 1;
    }

    printf("\nFiltered List:\n");
    print_list(filtered);

    free_list(list);
    free_list(filtered);

    return 0;
}