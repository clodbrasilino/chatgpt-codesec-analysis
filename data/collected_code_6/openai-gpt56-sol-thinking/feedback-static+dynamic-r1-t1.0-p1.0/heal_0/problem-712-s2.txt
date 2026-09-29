#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct IntNode {
    int value;
    struct IntNode *next;
} IntNode;

typedef struct ListNode {
    IntNode *values;
    struct ListNode *next;
} ListNode;

typedef struct {
    ListNode *head;
    ListNode *tail;
    size_t size;
} ListOfLists;

static void initialize_list_of_lists(ListOfLists *lists)
{
    if (lists != NULL) {
        lists->head = NULL;
        lists->tail = NULL;
        lists->size = 0U;
    }
}

static void free_int_list(IntNode *head)
{
    while (head != NULL) {
        IntNode *next = head->next;
        free(head);
        head = next;
    }
}

static void free_list_of_lists(ListOfLists *lists)
{
    if (lists == NULL) {
        return;
    }

    ListNode *current = lists->head;

    while (current != NULL) {
        ListNode *next = current->next;
        free_int_list(current->values);
        free(current);
        current = next;
    }

    initialize_list_of_lists(lists);
}

static IntNode *copy_values(const int *values, size_t count, bool *success)
{
    IntNode *head = NULL;
    IntNode *tail = NULL;

    if (success == NULL) {
        return NULL;
    }

    *success = false;

    if (count > 0U && values == NULL) {
        return NULL;
    }

    for (size_t i = 0U; i < count; ++i) {
        IntNode *node = malloc(sizeof(*node));

        if (node == NULL) {
            free_int_list(head);
            return NULL;
        }

        node->value = values[i];
        node->next = NULL;

        if (tail == NULL) {
            head = node;
        } else {
            tail->next = node;
        }

        tail = node;
    }

    *success = true;
    return head;
}

static bool append_list(ListOfLists *lists, const int *values, size_t count)
{
    bool success = false;
    IntNode *copied_values;
    ListNode *node;

    if (lists == NULL) {
        return false;
    }

    copied_values = copy_values(values, count, &success);

    if (!success) {
        return false;
    }

    node = malloc(sizeof(*node));

    if (node == NULL) {
        free_int_list(copied_values);
        return false;
    }

    node->values = copied_values;
    node->next = NULL;

    if (lists->tail == NULL) {
        lists->head = node;
    } else {
        lists->tail->next = node;
    }

    lists->tail = node;
    ++lists->size;

    return true;
}

static bool lists_are_equal(const IntNode *left, const IntNode *right)
{
    while (left != NULL && right != NULL) {
        if (left->value != right->value) {
            return false;
        }

        left = left->next;
        right = right->next;
    }

    return left == NULL && right == NULL;
}

void remove_duplicates(ListOfLists *lists)
{
    if (lists == NULL) {
        return;
    }

    for (ListNode *current = lists->head;
         current != NULL;
         current = current->next) {
        ListNode *previous = current;
        ListNode *candidate = current->next;

        while (candidate != NULL) {
            if (lists_are_equal(current->values, candidate->values)) {
                ListNode *duplicate = candidate;
                candidate = candidate->next;
                previous->next = candidate;

                if (lists->tail == duplicate) {
                    lists->tail = previous;
                }

                free_int_list(duplicate->values);
                free(duplicate);
                --lists->size;
            } else {
                previous = candidate;
                candidate = candidate->next;
            }
        }
    }
}

static bool print_list_of_lists(const ListOfLists *lists)
{
    if (lists == NULL || fputs("[\n", stdout) == EOF) {
        return false;
    }

    for (const ListNode *list = lists->head;
         list != NULL;
         list = list->next) {
        if (fputs("  [", stdout) == EOF) {
            return false;
        }

        for (const IntNode *value = list->values;
             value != NULL;
             value = value->next) {
            if (printf("%d", value->value) < 0) {
                return false;
            }

            if (value->next != NULL && fputs(", ", stdout) == EOF) {
                return false;
            }
        }

        if (fputs(list->next == NULL ? "]\n" : "],\n", stdout) == EOF) {
            return false;
        }
    }

    return fputs("]\n", stdout) != EOF;
}

int main(void)
{
    const int first[] = {1, 2, 3};
    const int second[] = {1, 2, 3};
    const int third[] = {3, 2, 1};
    const int fourth[] = {4, 5};
    ListOfLists lists;

    initialize_list_of_lists(&lists);

    if (!append_list(&lists, first, sizeof(first) / sizeof(first[0])) ||
        !append_list(&lists, second, sizeof(second) / sizeof(second[0])) ||
        !append_list(&lists, third, sizeof(third) / sizeof(third[0])) ||
        !append_list(&lists, NULL, 0U) ||
        !append_list(&lists, NULL, 0U) ||
        !append_list(&lists, fourth, sizeof(fourth) / sizeof(fourth[0]))) {
        free_list_of_lists(&lists);
        return EXIT_FAILURE;
    }

    remove_duplicates(&lists);

    if (!print_list_of_lists(&lists)) {
        free_list_of_lists(&lists);
        return EXIT_FAILURE;
    }

    free_list_of_lists(&lists);
    return EXIT_SUCCESS;
}