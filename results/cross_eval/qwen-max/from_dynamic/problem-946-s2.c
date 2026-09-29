#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char element[256];
    int count;
} ElementCount;

int compare(const void *a, const void *b) {
    return strcmp(((ElementCount *)a)->element, ((ElementCount *)b)->element);
}

int main() {
    char text[] = "example text to find the most common elements and their counts in a specified text";
    int text_length = strlen(text);
    ElementCount *elements = (ElementCount *)malloc(sizeof(ElementCount) * 100);
    int elements_count = 0;

    for (int i = 0; i < text_length; ++i) {
        if (isalpha(text[i])) {
            int found = 0;
            for (int j = 0; j < elements_count; ++j) {
                if (tolower(text[i]) == tolower(elements[j].element[0])) {
                    elements[j].count++;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                elements[elements_count].element[0] = tolower(text[i]);
                elements[elements_count].element[1] = '\0';
                elements[elements_count].count = 1;
                elements_count++;
            }
        }
    }

    qsort(elements, elements_count, sizeof(ElementCount), compare);

    for (int i = 0; i < elements_count; ++i) {
        printf("%s: %d\n", elements[i].element, elements[i].count);
    }

    free(elements);
    return 0;
}