#include <stdio.h>
#include <stdlib.h>

typedef enum { TYPE_NONE, TYPE_INT, TYPE_TUPLE } ElementType;

typedef struct Element {
    ElementType type;
    int int_val;
    struct Element *tuple_val;
    struct Element *next;
} Element;

Element *element_create_int(int val) {
    Element *e = (Element *)malloc(sizeof(Element));
    if (e == NULL) return NULL;
    e->type = TYPE_INT;
    e->int_val = val;
    e->tuple_val = NULL;
    e->next = NULL;
    return e;
}

Element *element_create_tuple(Element *children) {
    Element *e = (Element *)malloc(sizeof(Element));
    if (e == NULL) {
        while (children != NULL) {
            Element *tmp = children;
            children = children->next;
            free(tmp);
        }
        return NULL;
    }
    e->type = TYPE_TUPLE;
    e->int_val = 0;
    e->tuple_val = children;
    e->next = NULL;
    return e;
}

void element_free(Element *e) {
    while (e != NULL) {
        Element *next = e->next;
        if (e->type == TYPE_TUPLE) {
            element_free(e->tuple_val);
        }
        free(e);
        e = next;
    }
}

Element *result_append(Element **head, Element **tail, int val) {
    Element *e = element_create_int(val);
    if (e == NULL) return NULL;
    if (*head == NULL) {
        *head = e;
    } else {
        (*tail)->next = e;
    }
    *tail = e;
    return e;
}

Element *extract_even(Element *tuple) {
    Element *result = NULL;
    Element *result_tail = NULL;
    Element *current = tuple;

    while (current != NULL) {
        if (current->type == TYPE_INT) {
            if (current->int_val % 2 == 0) {
                if (result_append(&result, &result_tail, current->int_val) == NULL) {
                    element_free(result);
                    return NULL;
                }
            }
        } else if (current->type == TYPE_TUPLE) {
            Element *sub_result = extract_even(current->tuple_val);
            if (sub_result == NULL && current->tuple_val != NULL) {
                element_free(result);
                return NULL;
            }
            if (sub_result != NULL) {
                if (result == NULL) {
                    result = sub_result;
                    result_tail = sub_result;
                    while (result_tail->next != NULL) {
                        result_tail = result_tail->next;
                    }
                } else {
                    result_tail->next = sub_result;
                    while (result_tail->next != NULL) {
                        result_tail = result_tail->next;
                    }
                }
            }
        }
        current = current->next;
    }
    return result;
}

void print_result(Element *e) {
    printf("( ");
    while (e != NULL) {
        if (e->type == TYPE_INT) {
            printf("%d ", e->int_val);
        }
        e = e->next;
    }
    printf(")\n");
}

int main(void) {
    Element *inner_tuple = element_create_tuple(
        element_create_int(3,
            element_create_int(4,
                element_create_int(5, NULL)
            )
        )
    );
    if (inner_tuple == NULL) return 1;

    Element *outer_tuple = element_create_tuple(
        element_create_int(1,
            element_create_tuple(inner_tuple,
                element_create_int(6,
                    element_create_int(7, NULL)
                )
            )
        )
    );
    if (outer_tuple == NULL) {
        element_free(inner_tuple);
        return 1;
    }

    Element *evens = extract_even(outer_tuple);
    if (evens != NULL) {
        print_result(evens);
        element_free(evens);
    }

    element_free(outer_tuple);
    return 0;
}