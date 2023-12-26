#include <stdio.h>
#include <string.h>

#define MAX_TEXT_LENGTH 100
#define MAX_UNIQUE_ELEMENTS 100

typedef struct {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char element[MAX_TEXT_LENGTH];
    int count;
} Element;

void find_most_common_elements(char *text, Element *result, int *num_elements) {
    Element elements[MAX_UNIQUE_ELEMENTS];

    int i, j, k;
    /* Possible weaknesses found:
     *  Cannot determine that 'text[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int length = strlen(text);
    int max_count = 0;
    int num_unique_elements = 0;

    for (i = 0; i < length; i++) {
        /* Possible weaknesses found:
         *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
         */
        char current_element[MAX_TEXT_LENGTH] = "";
        int current_count = 0;

        if (text[i] == ' ' || text[i] == '\t' || text[i] == '\n') {
            continue;
        }

        for (j = i; j < length; j++) {
            if (text[j] == ' ' || text[j] == '\t' || text[j] == '\n') {
                break;
            }
            /* Possible weaknesses found:
             *   Easily used incorrectly (e.g., incorrectly computing the correct maximum  size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf,  or automatically resizing strings.
             */
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
                /* Possible weaknesses found:
                 *   Does not check for buffer overflows when copying to destination [MS-banned]  (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy  easily misused).
                 */
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
            /* Possible weaknesses found:
             *   Does not check for buffer overflows when copying to destination [MS-banned]  (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy  easily misused).
             */
            strcpy(result[index].element, elements[i].element);
            result[index].count = max_count;
            index++;
        }
    }
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char text[MAX_TEXT_LENGTH];
    Element result[MAX_UNIQUE_ELEMENTS];
    int num_elements = 0;
    
    printf("Enter the text: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'text[0]' is initialized [premium-bughuntingUninit]
     */
    fgets(text, sizeof(text), stdin);

    find_most_common_elements(text, result, &num_elements);

    printf("Most common elements and their counts: \n");
    for (int i = 0; i < num_elements; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'result[i] members' is initialized [premium-bughuntingUninit]
         */
        printf("%s: %d\n", result[i].element, result[i].count);
    }

    return 0;
}