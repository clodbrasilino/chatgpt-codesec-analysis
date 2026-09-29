#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char *data;
    struct Node *next;
};

void insertStringAtBeginning(struct Node *head, const char *prefix) {
    if (head == NULL || prefix == NULL) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t prefix_len = strlen(prefix);
    struct Node *current = head;

    while (current != NULL) {
        if (current->data != NULL) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t data_len = strlen(current->data);
            char *new_data = malloc(prefix_len + data_len + 1);

            if (new_data != NULL) {
                /* Possible weaknesses found:
                 * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
                 */
                strcpy(new_data, prefix);
                /* Possible weaknesses found:
                 * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
                 */
                strcat(new_data, current->data);

                free(current->data);
                current->data = new_data;
            }
        }
        current = current->next;
    }
}

int main() {
    struct Node *head = malloc(sizeof(struct Node));
    if (head == NULL) return 1;
    head->data = strdup("world");
    if (head->data == NULL) {
        free(head);
        return 1;
    }

    struct Node *second = malloc(sizeof(struct Node));
    if (second == NULL) {
        free(head->data);
        free(head);
        return 1;
    }
    second->data = strdup("people");
    if (second->data == NULL) {
        free(second);
        free(head->data);
        free(head);
        return 1;
    }
    
    head->next = second;
    second->next = NULL;

    insertStringAtBeginning(head, "Hello ");

    struct Node *current = head;
    while (current != NULL) {
        printf("%s\n", current->data);
        current = current->next;
    }

    current = head;
    while (current != NULL) {
        struct Node *temp = current;
        current = current->next;
        free(temp->data);
        free(temp);
    }

    return 0;
}