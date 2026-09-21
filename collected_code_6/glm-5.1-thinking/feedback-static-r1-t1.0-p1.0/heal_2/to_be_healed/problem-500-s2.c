#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char *data;
    struct Node *next;
};

char *concatenate_list(struct Node *head) {
    size_t total_len = 1;
    struct Node *curr = head;
    
    while (curr != NULL) {
        if (curr->data != NULL) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            total_len += strlen(curr->data);
        }
        curr = curr->next;
    }
    
    char *result = malloc(total_len);
    if (result == NULL) {
        return NULL;
    }
    
    size_t pos = 0;
    curr = head;
    while (curr != NULL) {
        if (curr->data != NULL) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len = strlen(curr->data);
            if (pos + len < total_len) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + pos, curr->data, len);
                pos += len;
            }
        }
        curr = curr->next;
    }
    
    result[pos] = '\0';
    return result;
}

int main(void) {
    struct Node n3 = {"!", NULL};
    struct Node n2 = {"world", &n3};
    struct Node n1 = {"Hello, ", &n2};
    
    char *result = concatenate_list(&n1);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }
    
    return 0;
}