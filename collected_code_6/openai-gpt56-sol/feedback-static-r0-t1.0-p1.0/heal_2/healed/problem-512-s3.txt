#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    ELEMENT_INTEGER,
    ELEMENT_STRING,
    ELEMENT_TUPLE,
    ELEMENT_UNINITIALIZED
} ElementType;

typedef struct Tuple Tuple;

typedef struct {
    ElementType type;
    union {
        long integer;
        char *string;
        Tuple *tuple;
    } value;
} Element;

struct Tuple {
    Element *elements;
    size_t size;
};

typedef struct {
    ElementType type;
    union {
        long integer;
        const char *string;
    } value;
    size_t count;
} Frequency;

typedef struct {
    Frequency *items;
    size_t size;
    size_t capacity;
} FrequencyTable;

static int duplicate_string(const char *source, size_t source_size,
                            char **destination)
{
    const char *terminator;
    size_t length;
    char *copy;

    if (source == NULL || destination == NULL || source_size == 0U) {
        return -1;
    }

    *destination = NULL;
    terminator = memchr(source, '\0', source_size);
    if (terminator == NULL) {
        return -1;
    }

    length = (size_t)(terminator - source);
    if (length == SIZE_MAX) {
        return -1;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return -1;
    }

    if (length != 0U) {
        memcpy(copy, source, length);
    }
    copy[length] = '\0';

    *destination = copy;
    return 0;
}

static int initialize_tuple(Tuple *tuple, size_t size)
{
    size_t index;

    if (tuple == NULL) {
        return -1;
    }

    tuple->elements = NULL;
    tuple->size = 0U;

    if (size == 0U) {
        return 0;
    }

    if (size > SIZE_MAX / sizeof(*tuple->elements)) {
        return -1;
    }

    tuple->elements = calloc(size, sizeof(*tuple->elements));
    if (tuple->elements == NULL) {
        return -1;
    }

    for (index = 0U; index < size; ++index) {
        tuple->elements[index].type = ELEMENT_UNINITIALIZED;
    }

    tuple->size = size;
    return 0;
}

static void destroy_tuple(Tuple *tuple)
{
    size_t index;

    if (tuple == NULL) {
        return;
    }

    if (tuple->elements != NULL) {
        for (index = 0U; index < tuple->size; ++index) {
            Element *element = &tuple->elements[index];

            if (element->type == ELEMENT_STRING) {
                free(element->value.string);
            } else if (element->type == ELEMENT_TUPLE &&
                       element->value.tuple != NULL) {
                destroy_tuple(element->value.tuple);
                free(element->value.tuple);
            }

            element->type = ELEMENT_UNINITIALIZED;
            element->value.string = NULL;
        }
    }

    free(tuple->elements);
    tuple->elements = NULL;
    tuple->size = 0U;
}

static int element_is_initialized(const Element *element)
{
    return element != NULL && element->type != ELEMENT_UNINITIALIZED;
}

static int set_integer(Tuple *tuple, size_t index, long value)
{
    Element *element;

    if (tuple == NULL || tuple->elements == NULL ||
        index >= tuple->size) {
        return -1;
    }

    element = &tuple->elements[index];
    if (element_is_initialized(element)) {
        return -1;
    }

    element->value.integer = value;
    element->type = ELEMENT_INTEGER;
    return 0;
}

static int set_string(Tuple *tuple, size_t index, const char *value,
                      size_t value_size)
{
    Element *element;
    char *copy = NULL;

    if (tuple == NULL || tuple->elements == NULL || value == NULL ||
        value_size == 0U || index >= tuple->size) {
        return -1;
    }

    element = &tuple->elements[index];
    if (element_is_initialized(element)) {
        return -1;
    }

    if (duplicate_string(value, value_size, &copy) != 0) {
        return -1;
    }

    element->value.string = copy;
    element->type = ELEMENT_STRING;
    return 0;
}

static int tuple_contains(const Tuple *tuple, const Tuple *target)
{
    size_t index;

    if (tuple == NULL || target == NULL) {
        return 0;
    }

    if (tuple == target) {
        return 1;
    }

    if (tuple->size != 0U && tuple->elements == NULL) {
        return 0;
    }

    for (index = 0U; index < tuple->size; ++index) {
        const Element *element = &tuple->elements[index];

        if (element->type == ELEMENT_TUPLE &&
            element->value.tuple != NULL &&
            tuple_contains(element->value.tuple, target)) {
            return 1;
        }
    }

    return 0;
}

static int set_nested_tuple(Tuple *tuple, size_t index, Tuple *nested)
{
    Element *element;

    if (tuple == NULL || tuple->elements == NULL || nested == NULL ||
        index >= tuple->size || tuple_contains(nested, tuple)) {
        return -1;
    }

    element = &tuple->elements[index];
    if (element_is_initialized(element)) {
        return -1;
    }

    element->value.tuple = nested;
    element->type = ELEMENT_TUPLE;
    return 0;
}

static int frequencies_equal(const Frequency *frequency,
                             const Element *element)
{
    if (frequency == NULL || element == NULL ||
        frequency->type != element->type) {
        return 0;
    }

    switch (element->type) {
    case ELEMENT_INTEGER:
        return frequency->value.integer == element->value.integer;

    case ELEMENT_STRING:
        if (frequency->value.string == NULL ||
            element->value.string == NULL) {
            return 0;
        }
        return strcmp(frequency->value.string,
                      element->value.string) == 0;

    default:
        return 0;
    }
}

static int grow_frequency_table(FrequencyTable *table)
{
    size_t new_capacity;
    Frequency *new_items;

    if (table == NULL || table->size > table->capacity) {
        return -1;
    }

    if (table->capacity == 0U) {
        new_capacity = 8U;
    } else {
        if (table->capacity > SIZE_MAX / 2U) {
            return -1;
        }
        new_capacity = table->capacity * 2U;
    }

    if (new_capacity > SIZE_MAX / sizeof(*table->items)) {
        return -1;
    }

    new_items = realloc(table->items,
                        new_capacity * sizeof(*table->items));
    if (new_items == NULL) {
        return -1;
    }

    table->items = new_items;
    table->capacity = new_capacity;
    return 0;
}

static int add_frequency(FrequencyTable *table, const Element *element)
{
    size_t index;

    if (table == NULL || element == NULL ||
        table->size > table->capacity ||
        (table->capacity != 0U && table->items == NULL)) {
        return -1;
    }

    if (element->type != ELEMENT_INTEGER &&
        element->type != ELEMENT_STRING) {
        return -1;
    }

    if (element->type == ELEMENT_STRING &&
        element->value.string == NULL) {
        return -1;
    }

    for (index = 0U; index < table->size; ++index) {
        if (frequencies_equal(&table->items[index], element)) {
            if (table->items[index].count == SIZE_MAX) {
                return -1;
            }
            ++table->items[index].count;
            return 0;
        }
    }

    if (table->size == table->capacity &&
        grow_frequency_table(table) != 0) {
        return -1;
    }

    table->items[table->size].type = element->type;
    table->items[table->size].count = 1U;

    if (element->type == ELEMENT_INTEGER) {
        table->items[table->size].value.integer =
            element->value.integer;
    } else {
        table->items[table->size].value.string =
            element->value.string;
    }

    ++table->size;
    return 0;
}

static int count_element_frequencies(const Tuple *tuple,
                                     FrequencyTable *table)
{
    size_t index;

    if (tuple == NULL || table == NULL ||
        (tuple->size != 0U && tuple->elements == NULL)) {
        return -1;
    }

    for (index = 0U; index < tuple->size; ++index) {
        const Element *element = &tuple->elements[index];

        switch (element->type) {
        case ELEMENT_INTEGER:
        case ELEMENT_STRING:
            if (add_frequency(table, element) != 0) {
                return -1;
            }
            break;

        case ELEMENT_TUPLE:
            if (element->value.tuple == NULL ||
                count_element_frequencies(element->value.tuple,
                                          table) != 0) {
                return -1;
            }
            break;

        default:
            return -1;
        }
    }

    return 0;
}

static void destroy_frequency_table(FrequencyTable *table)
{
    if (table == NULL) {
        return;
    }

    free(table->items);
    table->items = NULL;
    table->size = 0U;
    table->capacity = 0U;
}

static int print_frequencies(const FrequencyTable *table)
{
    size_t index;

    if (table == NULL || table->size > table->capacity ||
        (table->size != 0U && table->items == NULL)) {
        return -1;
    }

    for (index = 0U; index < table->size; ++index) {
        const Frequency *frequency = &table->items[index];

        if (frequency->type == ELEMENT_INTEGER) {
            if (printf("%ld: %zu\n",
                       frequency->value.integer,
                       frequency->count) < 0) {
                return -1;
            }
        } else if (frequency->type == ELEMENT_STRING &&
                   frequency->value.string != NULL) {
            if (printf("\"%s\": %zu\n",
                       frequency->value.string,
                       frequency->count) < 0) {
                return -1;
            }
        } else {
            return -1;
        }
    }

    return 0;
}

int main(void)
{
    Tuple root = {NULL, 0U};
    Tuple *nested = NULL;
    Tuple *deeper = NULL;
    FrequencyTable table = {NULL, 0U, 0U};
    int status = EXIT_FAILURE;

    if (initialize_tuple(&root, 5U) != 0) {
        goto cleanup;
    }

    nested = malloc(sizeof(*nested));
    if (nested == NULL) {
        goto cleanup;
    }
    nested->elements = NULL;
    nested->size = 0U;

    deeper = malloc(sizeof(*deeper));
    if (deeper == NULL) {
        goto cleanup;
    }
    deeper->elements = NULL;
    deeper->size = 0U;

    if (initialize_tuple(nested, 4U) != 0 ||
        initialize_tuple(deeper, 3U) != 0 ||
        set_integer(&root, 0U, 42L) != 0 ||
        set_string(&root, 1U, "apple", sizeof("apple")) != 0 ||
        set_integer(nested, 0U, 42L) != 0 ||
        set_string(nested, 1U, "banana", sizeof("banana")) != 0 ||
        set_integer(nested, 2U, 7L) != 0 ||
        set_string(deeper, 0U, "apple", sizeof("apple")) != 0 ||
        set_integer(deeper, 1U, 42L) != 0 ||
        set_string(deeper, 2U, "banana", sizeof("banana")) != 0 ||
        set_nested_tuple(nested, 3U, deeper) != 0) {
        goto cleanup;
    }
    deeper = NULL;

    if (set_nested_tuple(&root, 2U, nested) != 0) {
        goto cleanup;
    }
    nested = NULL;

    if (set_string(&root, 3U, "apple", sizeof("apple")) != 0 ||
        set_integer(&root, 4U, 7L) != 0 ||
        count_element_frequencies(&root, &table) != 0 ||
        print_frequencies(&table) != 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    destroy_frequency_table(&table);

    if (deeper != NULL) {
        destroy_tuple(deeper);
        free(deeper);
    }

    if (nested != NULL) {
        destroy_tuple(nested);
        free(nested);
    }

    destroy_tuple(&root);

    if (status != EXIT_SUCCESS) {
        fputs("Operation failed\n", stderr);
    }

    return status;
}