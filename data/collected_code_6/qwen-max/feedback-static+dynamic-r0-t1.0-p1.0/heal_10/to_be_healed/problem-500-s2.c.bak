#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected '  Part of the journey is end', got Partofthejourneyisend
  *  test case 1 failed: expected '  Hi there How are you', got HithereHowareyou
  *  test case 0 failed: expected '  hello there have a rocky day', got hellotherehavearockyday
  */

char* concatenate_elements(char **list, int length) {
    if (length <= 0) return NULL;

    size_t total_length = 1;
    for (int i = 0; i < length; ++i) {
        total_length += strlen(list[i]);
    }
    char *result = malloc(total_length);
    if (result == NULL) return NULL;
    result[0] = '\0';

    for (int i = 0; i < length; ++i) {
        strcat(result, list[i]);
    }

    return result;
}

int main() {
    char *elements[] = {"hello", " ", "there", " ", "have", " ", "a", " ", "rocky", " ", "day"};
    int num_elements = 11;

    char *concatenated = concatenate_elements(elements, num_elements);
    if (concatenated != NULL) {
        printf("  %s\n", concatenated);
        free(concatenated);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }

    elements[0] = "Hi";
    elements[1] = " ";
    elements[2] = "there";
    elements[3] = " ";
    elements[4] = "How";
    elements[5] = " ";
    elements[6] = "are";
    elements[7] = " ";
    elements[8] = "you";
    num_elements = 9;

    concatenated = concatenate_elements(elements, num_elements);
    if (concatenated != NULL) {
        printf("  %s\n", concatenated);
        free(concatenated);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }

    elements[0] = "Part";
    elements[1] = " ";
    elements[2] = "of";
    elements[3] = " ";
    elements[4] = "the";
    elements[5] = " ";
    elements[6] = "journey";
    elements[7] = " ";
    elements[8] = "is";
    elements[9] = " ";
    elements[10] = "end";
    num_elements = 11;

    concatenated = concatenate_elements(elements, num_elements);
    if (concatenated != NULL) {
        printf("  %s\n", concatenated);
        free(concatenated);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }

    return 0;
}