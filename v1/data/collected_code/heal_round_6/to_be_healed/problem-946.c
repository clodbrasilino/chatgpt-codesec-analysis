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
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    size_t length = strlen(text);
    int max_count = 0;
    int num_unique_elements = 0;

    for (i = 0; i < length; i++) {

        /* Possible weaknesses found:
         *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
         */
        char current_element[MAX_TEXT_LENGTH] = {0};

        if (text[i] != ' ' && text[i] != '\t' && text[i] != '\n') {

            for (j = i; j < i + sizeof(current_element) && text[j] != ' ' && text[j] != '\t' && text[j] != '\n'; j++) {
                /* Possible weaknesses found:
                 *   Easily used incorrectly (e.g., incorrectly computing the correct maximum  size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf,  or automatically resizing strings.
                 */
                strncat(current_element, &text[j], 1);
            }

            int element_found = 0;

            for (k = 0; k < num_unique_elements; k++) {
                /* Possible weaknesses found:
                 *  use of possibly-NULL '*elements_92 + _25.element' where non-null expected [CWE-690] [-Wanalyzer-possible-null-argument]
                 */
                if (strcmp(elements[k].element, current_element) == 0) {
                    elements[k].count++;
                    element_found = 1;
                    break;
                }
            }

            if (!element_found && num_unique_elements < MAX_UNIQUE_ELEMENTS) {
                /* Possible weaknesses found:
                 *  dereference of possibly-NULL 'elements' [CWE-690] [-Wanalyzer-possible-null-dereference]
                 */
                elements[num_unique_elements].element = strdup(current_element);
                elements[num_unique_elements].count = 1;
                num_unique_elements++;
            }
            i = j;
        }
    }

    *num_elements = num_unique_elements;

    for (i = 0; i < num_unique_elements; i++) {
        if (elements[i].count > max_count) {
            max_count = elements[i].count;
        }
    }

    for (i = 0, j = 0; i < num_unique_elements; i++) {
        if (elements[i].count == max_count) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'result' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            result[j].element = strdup(elements[i].element);
            result[j++].count = max_count;
        }
        free(elements[i].element);
    }
    /* Possible weaknesses found:
     *  leak of '<unknown>' [CWE-401] [-Wanalyzer-malloc-leak]
     */
    free(elements);
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char text[MAX_TEXT_LENGTH] = {0};
    Element *result = calloc(MAX_UNIQUE_ELEMENTS, sizeof(Element));
    int num_elements = 0;

    printf("Enter the text:\n");
    fgets(text, sizeof(text), stdin);

    find_most_common_elements(text, result, &num_elements);
 /* Possible weaknesses found:
  *  argument 1 of 'strcmp' must be non-null
  */

    printf("Most common elements and their counts:\n");
    for (int i = 0; i < num_elements; i++) {
        printf("%s: %d\n", result[i].element, result[i].count);
        free(result[i].element);
    }

    free(result);
    return 0;
}