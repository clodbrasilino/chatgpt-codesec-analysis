#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected '  hello there have a rocky day', got <no output>
  *  test case 1 failed: expected '  Hi there How are you', got <no output>
  *  test case 2 failed: expected '  Part of the journey is end', got <no output>
  */

char* concatenate_elements(char **list, int length) {
    if (length <= 0) return NULL;

    char *result = malloc(1);
    if (result == NULL) return NULL;
    result[0] = '\0';

    for (int i = 0; i < length; ++i) {
        size_t len_result = strlen(result);
        size_t len_next = strlen(list[i]);
        size_t new_len = len_result + len_next + 2; 
        char *new_result = realloc(result, new_len);
        if (new_result == NULL) {
            free(result);
            return NULL;
        }
        result = new_result;
        if (len_result > 0 && i > 0) { 
            result[len_result] = ' ';
            strcat(result + len_result + 1, list[i]);
        } else {
            strcat(result, list[i]);
        }
    }

    return result;
}

int main() {
    char *elements[] = {"  hello", "there", "have", "a", "rocky", "day"};
    int num_elements = 6;
    char *concatenated = concatenate_elements(elements, num_elements);
    if (concatenated != NULL) {
        printf("%s\n", concatenated);
        free(concatenated);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }

    elements[0] = "  Hi"; elements[1] = "there"; elements[2] = "How"; elements[3] = "are"; elements[4] = "you";
    num_elements = 5;
    concatenated = concatenate_elements(elements, num_elements);
    if (concatenated != NULL) {
        printf("%s\n", concatenated);
        free(concatenated);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }

    elements[0] = "  Part"; elements[1] = "of"; elements[2] = "the"; elements[3] = "journey"; elements[4] = "is"; elements[5] = "end";
    num_elements = 6;
    concatenated = concatenate_elements(elements, num_elements);
    if (concatenated != NULL) {
        printf("%s\n", concatenated);
        free(concatenated);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }

    return 0;
}