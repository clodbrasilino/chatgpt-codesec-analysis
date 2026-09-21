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

    char** temp = realloc(list, new_count * sizeof(char*));
    if (temp) {
        list = temp;
    }

    return list;
}

char** create_list(const char* items[], int size) {
    char** list = malloc(size * sizeof(char*));
    if (!list) {
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        size_t len = strlen(items[i]);
        list[i] = malloc(len + 1);
        if (!list[i]) {
            for (int j = 0; j < i; j++) {
                free(list[j]);
            }
            free(list);
            return NULL;
        }
        memcpy(list[i], items[i], len + 1);
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
    const char* test0[] = {"red", "banana", "green", "blue", "banana", "black"};
    int count0 = 6;
    char** list0 = create_list(test0, count0);
    list0 = remove_words(list0, &count0, "banana");
    for (int i = 0; i < count0; i++) {
        printf("%s\n", list0[i]);
    }
    free_list(list0, count0);

    const char* test1[] = {"red", "green", "blue", "white"};
    int count1 = 4;
    char** list1 = create_list(test1, count1);
    list1 = remove_words(list1, &count1, "yellow");
    for (int i = 0; i < count1; i++) {
        printf("%s\n", list1[i]);
    }
    free_list(list1, count1);

    const char* test2[] = {"red", "green", "black", "orange"};
    int count2 = 4;
    char** list2 = create_list(test2, count2);
    list2 = remove_words(list2, &count2, "purple");
    for (int i = 0; i < count2; i++) {
        printf("%s\n", list2[i]);
    }
    free_list(list2, count2);

    return 0;
}