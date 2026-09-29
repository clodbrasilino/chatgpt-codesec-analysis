#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **words;
    int size;
} StringList;

int list_contains(StringList *list, const char *word) {
    for (int i = 0; i < list->size; ++i) {
        if (strcmp(list->words[i], word) == 0) {
            return 1;
        }
    }
    return 0;
}

void remove_duplicates(StringList *input_list, StringList *output_list) {
    for (int i = 0; i < input_list->size; ++i) {
        if (!list_contains(output_list, input_list->words[i])) {
            output_list->words[output_list->size] = strdup(input_list->words[i]);
            output_list->size++;
        }
    }
}

void free_string_list(StringList *list) {
    for (int i = 0; i < list->size; ++i) {
        /* Possible weaknesses found:
         * ASan: BUS
         */
        free(list->words[i]);
    }
    free(list->words);
    list->words = NULL;
    list->size = 0;
}

int main() {
    StringList input_list = { .words = NULL, .size = 0 };
    StringList unique_list = { .words = NULL, .size = 0 };

    input_list.size = 8;
    input_list.words = malloc(input_list.size * sizeof(char*));
    if (input_list.words == NULL) {
        return -1;
    }

    input_list.words[0] = "apple";
    input_list.words[1] = "banana";
    input_list.words[2] = "apple";
    input_list.words[3] = "cherry";
    input_list.words[4] = "date";
    input_list.words[5] = "banana";
    input_list.words[6] = "elderberry";
    input_list.words[7] = "fig";

    unique_list.words = malloc(input_list.size * sizeof(char*));
    if (unique_list.words == NULL) {
        free(input_list.words);
        return -1;
    }

    unique_list.size = 0;

    remove_duplicates(&input_list, &unique_list);

    for (int i = 0; i < unique_list.size; ++i) {
        printf("%s\n", unique_list.words[i]);
    }

    free_string_list(&input_list);
    free_string_list(&unique_list);

    return 0;
}