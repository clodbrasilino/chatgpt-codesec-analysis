#include <ctype.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    ELEMENT_STRING,
    ELEMENT_FLOAT
} ElementType;

typedef struct ListNode {
    ElementType type;
    union {
        char *string_value;
        float float_value;
    } value;
    struct ListNode *next;
} ListNode;

typedef struct {
    ListNode *head;
    ListNode *tail;
} List;

static void list_initialize(List *list)
{
    if (list != NULL) {
        list->head = NULL;
        list->tail = NULL;
    }
}

static char *duplicate_string(const char *source)
{
    size_t length = 0U;
    size_t index;
    char *copy;

    if (source == NULL) {
        return NULL;
    }

    while (source[length] != '\0') {
        if (length == SIZE_MAX - 1U) {
            return NULL;
        }
        ++length;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return NULL;
    }

    for (index = 0U; index < length; ++index) {
        copy[index] = source[index];
    }

    copy[length] = '\0';
    return copy;
}

static int list_append_string(List *list, const char *text)
{
    ListNode *node;
    char *copy;

    if (list == NULL || text == NULL) {
        return 0;
    }

    copy = duplicate_string(text);
    if (copy == NULL) {
        return 0;
    }

    node = malloc(sizeof(*node));
    if (node == NULL) {
        free(copy);
        return 0;
    }

    node->type = ELEMENT_STRING;
    node->value.string_value = copy;
    node->next = NULL;

    if (list->tail == NULL) {
        list->head = node;
        list->tail = node;
    } else {
        list->tail->next = node;
        list->tail = node;
    }

    return 1;
}

static int parse_float(const char *text, float *result)
{
    char *end;
    float value;

    if (text == NULL || result == NULL) {
        return 0;
    }

    errno = 0;
    value = strtof(text, &end);

    if (end == text || errno == ERANGE) {
        return 0;
    }

    while (*end != '\0') {
        if (!isspace((unsigned char)*end)) {
            return 0;
        }
        ++end;
    }

    *result = value;
    return 1;
}

static size_t convert_all_possible_to_float(List *list)
{
    ListNode *node;
    size_t converted_count = 0U;

    if (list == NULL) {
        return 0U;
    }

    for (node = list->head; node != NULL; node = node->next) {
        float converted_value;

        if (node->type == ELEMENT_STRING &&
            node->value.string_value != NULL &&
            parse_float(node->value.string_value, &converted_value)) {
            free(node->value.string_value);
            node->value.float_value = converted_value;
            node->type = ELEMENT_FLOAT;
            ++converted_count;
        }
    }

    return converted_count;
}

static int list_print(const List *list)
{
    const ListNode *node;

    if (list == NULL) {
        return 0;
    }

    for (node = list->head; node != NULL; node = node->next) {
        int result;

        switch (node->type) {
        case ELEMENT_STRING:
            if (node->value.string_value == NULL) {
                return 0;
            }

            result = printf("%s\n", node->value.string_value);
            break;

        case ELEMENT_FLOAT:
            result = printf("%.9g\n", (double)node->value.float_value);
            break;

        default:
            return 0;
        }

        if (result < 0) {
            return 0;
        }
    }

    return fflush(stdout) == 0;
}

static void list_destroy(List *list)
{
    ListNode *node;

    if (list == NULL) {
        return;
    }

    node = list->head;

    while (node != NULL) {
        ListNode *next = node->next;

        if (node->type == ELEMENT_STRING) {
            free(node->value.string_value);
        }

        free(node);
        node = next;
    }

    list->head = NULL;
    list->tail = NULL;
}

int main(int argc, char *argv[const])
{
    List list;
    int index;
    int exit_status = EXIT_SUCCESS;

    list_initialize(&list);

    for (index = 1; index < argc; ++index) {
        const char *const argument = argv[index];

        if (!list_append_string(&list, argument)) {
            fprintf(stderr, "Failed to add list element.\n");
            exit_status = EXIT_FAILURE;
            goto cleanup;
        }
    }

    (void)convert_all_possible_to_float(&list);

    if (!list_print(&list)) {
        fprintf(stderr, "Failed to write output.\n");
        exit_status = EXIT_FAILURE;
    }

cleanup:
    list_destroy(&list);
    return exit_status;
}