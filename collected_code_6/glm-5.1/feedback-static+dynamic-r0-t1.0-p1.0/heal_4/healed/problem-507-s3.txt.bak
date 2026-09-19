#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** remove_words(char** list, int* count, const char* word) {
    if (!list || !count || !word) {
        return list;
    }

    int new_count = 0;
    for (int i = 0; i < *count; i++) {
        if (strcmp(list[i], word) == 0) {
            free(list[i]);
            list[i] = NULL;
        } else {
            list[new_count++] = list[i];
        }
    }

    for (int i = new_count; i < *count; i++) {
        list[i] = NULL;
    }

    *count = new_count;

    if (new_count == 0) {
        free(list);
        return NULL;
    }

    return list;
}

char** create_list(const char* items[], int size) {
    char** list = malloc(size * sizeof(char*));
    if (!list) {
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        list[i] = malloc(strlen(items[i]) + 1);
        if (!list[i]) {
            for (int j = 0; j < i; j++) {
                free(list[j]);
            }
            free(list);
            return NULL;
        }
        strcpy(list[i], items[i]);
    }
    return list;
}

void free_list(char** list, int count) {
    if (!list) {
        return;
    }
    for (int i = 0; i < count; i++) {
        free(list[i]);
    }
    free(list);
}

int main(void) {
    const char* items0[] = {"red", "green", "blue", "black", "blue"};
    int count0 = 5;
    char** list0 = create_list(items0, count0);
    if (list0) {
        list0 = remove_words(list0, &count0, "blue");
        if (list0) {
            for (int i = 0; i < count0; i++) {
                printf("%s\n", list0[i]);
            }
        }
        free_list(list0, count0);
    }

    const char* items1[] = {"red", "green", "blue", "white", "white"};
    int count1 = 5;
    char** list1 = create_list(items1, count1);
    if (list1) {
        list1 = remove_words(list1, &count1, "white");
        if (list1) {
            for (int i = 0; i < count1; i++) {
                printf("%s\n", list1[i]);
            }
        }
        free_list(list1, count1);
    }

    const char* items2[] = {"red", "green", "black", "orange", "orange"};
    int count2 = 5;
    char** list2 = create_list(items2, count2);
    if (list2) {
        list2 = remove_words(list2, &count2, "orange");
        if (list2) {
            for (int i = 0; i < count2; i++) {
                printf("%s\n", list2[i]);
            }
        }
        free_list(list2, count2);
    }

    return 0;
}