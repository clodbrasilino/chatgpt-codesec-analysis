#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char element[2];
    int count;
} ElementCount;

int compare(const void *a, const void *b) {
    return strcmp(((ElementCount *)a)->element, ((ElementCount *)b)->element);
}

int main() {
    char text[] = "example text to find the most common elements and their counts in a specified text";
    size_t text_length = sizeof(text) / sizeof(text[0]) - 1;
    ElementCount *elements = (ElementCount *)malloc(sizeof(ElementCount) * 100);
    if (!elements) {
        return 1;
    }
    int elements_count = 0;

    for (size_t i = 0; i < text_length; ++i) {
        if (isalpha(text[i])) {
            int found = 0;
            for (int j = 0; j < elements_count; ++j) {
                if (tolower(text[i]) == tolower(elements[j].element[0])) {
                    elements[j].count++;
                    found = 1;
                    break;
                }
            }
            if (!found && elements_count < 100) {
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