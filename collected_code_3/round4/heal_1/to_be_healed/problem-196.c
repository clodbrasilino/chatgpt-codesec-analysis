#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tuple {
    char *str;
    struct Tuple *next;
} Tuple;

Tuple* removeKLengthTuples(Tuple *head, int k) {
    Tuple *current = head;
    Tuple *prev = NULL;

    while (current != NULL) {
        /* Possible weaknesses found:
         *  use of possibly-NULL '*current.str' where non-null expected [CWE-690] [-Wanalyzer-possible-null-argument]
         */
        if (strlen(current->str) == k) {
            if (prev == NULL) {
                head = current->next;
            } else {
                prev->next = current->next;
            }
            Tuple *temp = current;
            current = current->next;
            free(temp->str);
            free(temp);
        } else {
            prev = current;
            current = current->next;
        }
    }
    return head;
}

int main() {
    Tuple *head = malloc(sizeof(Tuple));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'head' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    head->str = strdup("hello");
    head->next = malloc(sizeof(Tuple));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL '*head.next' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    head->next->str = strdup("world");
    head->next->next = NULL;

    head = removeKLengthTuples(head, 5);

    Tuple *current = head;
    while (current != NULL) {
        printf("%s\n", current->str);
        current = current->next;
    }

    while (head != NULL) {
        Tuple *temp = head;
        head = head->next;
        free(temp->str);
        free(temp);
    }

    return 0;
}