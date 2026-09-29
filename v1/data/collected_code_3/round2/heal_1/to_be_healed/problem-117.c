#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

float toFloat(char *str) {
    return strtof(str, NULL);
}

void convertListToFloat(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%f\n", toFloat(current->data));
        current = current->next;
    }
}

int main() {
    Node *head = malloc(sizeof(Node));
    Node *second = malloc(sizeof(Node));
    Node *third = malloc(sizeof(Node));

    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'head' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    head->data = "3.14";
    head->next = second;

    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'second' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    second->data = "2.71";
    second->next = third;

    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'third' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    third->data = "1.41";
    third->next = NULL;

    convertListToFloat(head);

    free(head);
    free(second);
    free(third);

    return 0;
}