#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char* data;
    struct Node* next;
};

char* concatenate_list(struct Node* head) {
    if (head == NULL) {
        char* empty_str = malloc(1);
        if (empty_str != NULL) {
            empty_str[0] = '\0';
        }
        return empty_str;
    }

    size_t total_length = 0;
    struct Node* current = head;
    while (current != NULL) {
        if (current->data != NULL) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            total_length += strlen(current->data);
        }
        current = current->next;
    }

    char* result = malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }
    result[0] = '\0';

    current = head;
    while (current != NULL) {
        if (current->data != NULL) {
            /* Possible weaknesses found:
             * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
             */
            strcat(result, current->data);
        }
        current = current->next;
    }

    return result;
}

int main(void) {
    struct Node node3 = {"World!", NULL};
    struct Node node2 = {" ", &node3};
    struct Node node1 = {"Hello", &node2};

    char* concatenated_string = concatenate_list(&node1);

    if (concatenated_string != NULL) {
        printf("%s\n", concatenated_string);
        free(concatenated_string);
    } else {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    return 0;
}