#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TEXT_LENGTH 101
#define MAX_UNIQUE_ELEMENTS 100

typedef struct {
    char *element;
    int count;
} Element;

void find_most_common_elements(char *text, Element *result, int *num_elements) {
    Element *elements = calloc(MAX_UNIQUE_ELEMENTS, sizeof(Element));
    int i, j, k;
    size_t length = strnlen(text, MAX_TEXT_LENGTH);
    int max_count = 0;
    int num_unique_elements = 0;

    for (i = 0; i < length; i++) {

        char* current_element = calloc(MAX_TEXT_LENGTH, sizeof(char));

        if (text[i] == ' ' || text[i] == '\t' || text[i] == '\n') {
            continue;
        }

        for (j = i; j < length; j++) {

            if (text[j] == ' ' || text[j] == '\t' || text[j] == '\n') {
                break;
            }

            strncat(current_element, &text[j], 1);
        }

        int element_found = 0;

        for (k = 0; k < num_unique_elements; k++) {
            if (strcmp(elements[k].element, current_element) == 0) {
                elements[k].count++;
                element_found = 1;
                break;
            }
        }

        if (!element_found && num_unique_elements < MAX_UNIQUE_ELEMENTS) {
            elements[num_unique_elements].element = calloc(strlen(current_element) + 1, sizeof(char));
            strncpy(elements[num_unique_elements].element, current_element, strlen(current_element));
            elements[num_unique_elements].count = 1;
            num_unique_elements++;
        }
        i = j;
        free(current_element);
    }

    *num_elements = num_unique_elements;

    for (i = 0; i < num_unique_elements; i++) {
        if (elements[i].count > max_count) {
            max_count = elements[i].count;
        }
    }

    int index = 0;

    for (i = 0; i < num_unique_elements; i++) {
        if (elements[i].count == max_count) {
            result[index].element = calloc(strlen(elements[i].element) + 1, sizeof(char));
            strncpy(result[index].element, elements[i].element, strlen(elements[i].element));
            result[index++].count = max_count;
        }
        free(elements[i].element);
    }
    free(elements);
}

int main() {
    char text[MAX_TEXT_LENGTH] = {0};
    Element *result = calloc(MAX_UNIQUE_ELEMENTS, sizeof(Element));
    int num_elements = 0;

    printf("Enter the text:\n");
    fgets(text, sizeof(text), stdin);

    find_most_common_elements(text, result, &num_elements);

    printf("Most common elements and their counts:\n");
    for (int i = 0; i < num_elements; i++) {
        printf("%s: %d\n", result[i].element, result[i].count);
        free(result[i].element);
    }

    free(result);
    return 0;
}