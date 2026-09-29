#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char *name;
    double value;
} Tuple;

typedef struct TupleNode {
    Tuple data;
    struct TupleNode *next;
} TupleNode;

int tuple_init(Tuple *tuple, int id, const char *name, double value) {
    if (tuple == NULL) return 0;
    tuple->id = id;
    tuple->value = value;
    if (name != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        tuple->name = malloc(strlen(name) + 1);
        if (tuple->name == NULL) return 0;
        /* Possible weaknesses found:
         * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
         */
        strcpy(tuple->name, name);
    } else {
        tuple->name = malloc(1);
        if (tuple->name == NULL) return 0;
        tuple->name[0] = '\0';
    }
    return 1;
}

void tuple_free_contents(Tuple *tuple) {
    if (tuple != NULL && tuple->name != NULL) {
        free(tuple->name);
        tuple->name = NULL;
    }
}

TupleNode *tuple_node_create(int id, const char *name, double value) {
    TupleNode *node = malloc(sizeof(*node));
    if (node == NULL) return NULL;
    if (!tuple_init(&node->data, id, name, value)) {
        free(node);
        return NULL;
    }
    node->next = NULL;
    return node;
}

int tuple_list_append(TupleNode **head, int id, const char *name, double value) {
    if (head == NULL) return 0;
    TupleNode *node = tuple_node_create(id, name, value);
    if (node == NULL) return 0;
    if (*head == NULL) {
        *head = node;
        return 1;
    }
    TupleNode *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = node;
    return 1;
}

int extract_rear(TupleNode **head, Tuple *result) {
    if (head == NULL || *head == NULL || result == NULL) return 0;
    TupleNode *previous = NULL;
    TupleNode *current = *head;
    while (current->next != NULL) {
        previous = current;
        current = current->next;
    }
    result->id = current->data.id;
    result->value = current->data.value;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    result->name = malloc(strlen(current->data.name) + 1);
    if (result->name == NULL) return 0;
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(result->name, current->data.name);
    tuple_free_contents(&current->data);
    if (previous == NULL) {
        *head = NULL;
    } else {
        previous->next = NULL;
    }
    free(current);
    return 1;
}

void tuple_list_free(TupleNode **head) {
    if (head == NULL) return;
    TupleNode *current = *head;
    while (current != NULL) {
        TupleNode *next = current->next;
        tuple_free_contents(&current->data);
        free(current);
        current = next;
    }
    *head = NULL;
}

int main(void) {
    TupleNode *head = NULL;
    Tuple extracted;
    extracted.name = NULL;
    int ok;

    if (!tuple_list_append(&head, 1, "alpha", 1.5)) {
        tuple_list_free(&head);
        return 1;
    }
    if (!tuple_list_append(&head, 2, "beta", 2.5)) {
        tuple_list_free(&head);
        return 1;
    }
    if (!tuple_list_append(&head, 3, "gamma", 3.5)) {
        tuple_list_free(&head);
        return 1;
    }

    ok = extract_rear(&head, &extracted);
    if (ok) {
        printf("%d %s %.1f\n", extracted.id, extracted.name, extracted.value);
        tuple_free_contents(&extracted);
    } else {
        printf("empty\n");
    }

    ok = extract_rear(&head, &extracted);
    if (ok) {
        printf("%d %s %.1f\n", extracted.id, extracted.name, extracted.value);
        tuple_free_contents(&extracted);
    } else {
        printf("empty\n");
    }

    ok = extract_rear(&head, &extracted);
    if (ok) {
        printf("%d %s %.1f\n", extracted.id, extracted.name, extracted.value);
        tuple_free_contents(&extracted);
    } else {
        printf("empty\n");
    }

    ok = extract_rear(&head, &extracted);
    if (ok) {
        printf("%d %s %.1f\n", extracted.id, extracted.name, extracted.value);
        tuple_free_contents(&extracted);
    } else {
        printf("empty\n");
    }

    tuple_list_free(&head);
    return 0;
}