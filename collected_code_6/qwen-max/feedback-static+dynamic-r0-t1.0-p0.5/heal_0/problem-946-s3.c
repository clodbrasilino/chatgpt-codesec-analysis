#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char *element;
    int count;
} ElementCount;

int compare(const void *a, const void *b) {
    return strcmp(((ElementCount *)a)->element, ((ElementCount *)b)->element);
}

ElementCount* findMostCommonElements(char *text, int *count) {
    if (text == NULL || count == NULL) return NULL;

    int n = strlen(text);
    ElementCount *elements = (ElementCount *)malloc(n * sizeof(ElementCount));
    if (elements == NULL) return NULL;

    int elements_count = 0;
    for (int i = 0; i < n; i++) {
        if (isalpha(text[i])) {
            int found = 0;
            for (int j = 0; j < elements_count; j++) {
                if (tolower(text[i]) == tolower(elements[j].element[0])) {
                    elements[j].count++;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                elements[elements_count].element = (char *)malloc(2 * sizeof(char));
                elements[elements_count].element[0] = tolower(text[i]);
                elements[elements_count].element[1] = '\0';
                elements[elements_count].count = 1;
                elements_count++;
            }
        }
    }

    qsort(elements, elements_count, sizeof(ElementCount), compare);

    int max_count = 0;
    for (int i = 0; i < elements_count; i++) {
        if (elements[i].count > max_count) {
            max_count = elements[i].count;
        }
    }

    int most_common_count = 0;
    for (int i = 0; i < elements_count; i++) {
        if (elements[i].count == max_count) {
            most_common_count++;
        }
    }

    ElementCount *most_common_elements = (ElementCount *)malloc(most_common_count * sizeof(ElementCount));
    if (most_common_elements == NULL) {
        for (int i = 0; i < elements_count; i++) {
            free(elements[i].element);
        }
        free(elements);
        return NULL;
    }

    int index = 0;
    for (int i = 0; i < elements_count; i++) {
        if (elements[i].count == max_count) {
            most_common_elements[index] = elements[i];
            index++;
        }
    }

    for (int i = 0; i < elements_count; i++) {
        free(elements[i].element);
    }
    free(elements);

    *count = most_common_count;
    return most_common_elements;
}

int main() {
    char text[] = "Hello World! Hello C!";
    int count;
    ElementCount *most_common_elements = findMostCommonElements(text, &count);

    if (most_common_elements != NULL) {
        for (int i = 0; i < count; i++) {
            printf("Element: %s, Count: %d\n", most_common_elements[i].element, most_common_elements[i].count);
            free(most_common_elements[i].element);
        }
        free(most_common_elements);
    }

    return 0;
}