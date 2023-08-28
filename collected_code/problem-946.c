#include <stdio.h>
#include <string.h>

#define MAX_TEXT_LENGTH 100
#define MAX_UNIQUE_ELEMENTS 100

typedef struct {
    char element[MAX_TEXT_LENGTH];
    int count;
} Element;

void find_most_common_elements(char *text, Element *result, int *num_elements) {
    Element elements[MAX_UNIQUE_ELEMENTS];

    int i, j, k;
    int length = strlen(text);
    int max_count = 0;
    int num_unique_elements = 0;

    for (i = 0; i < length; i++) {
        char current_element[MAX_TEXT_LENGTH] = "";
        int current_count = 0;

        if (text[i] == ' ' || text[i] == '\t' || text[i] == '\n') {
            continue;
        }

        for (j = i; j < length; j++) {
            if (text[j] == ' ' || text[j] == '\t' || text[j] == '\n') {
                break;
            }
            strncat(current_element, &text[j], 1);
            current_count++;
        }

        if (current_count > 0) {
            int element_found = 0;

            for (k = 0; k < num_unique_elements; k++) {
                if (strcmp(elements[k].element, current_element) == 0) {
                    elements[k].count++;
                    element_found = 1;
                    break;
                }
            }

            if (!element_found) {
                strcpy(elements[num_unique_elements].element, current_element);
                elements[num_unique_elements].count = 1;
                num_unique_elements++;
            }
        }
        i = j;
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
            strcpy(result[index].element, elements[i].element);
            result[index].count = max_count;
            index++;
        }
    }
}

int main() {
    char text[MAX_TEXT_LENGTH];
    Element result[MAX_UNIQUE_ELEMENTS];
    int num_elements = 0;
    
    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);

    find_most_common_elements(text, result, &num_elements);

    printf("Most common elements and their counts: \n");
    for (int i = 0; i < num_elements; i++) {
        printf("%s: %d\n", result[i].element, result[i].count);
    }

    return 0;
}