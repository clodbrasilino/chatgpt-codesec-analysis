#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    ELEMENT_UNINITIALIZED,
    ELEMENT_INTEGER,
    ELEMENT_STRING,
    ELEMENT_TUPLE
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

static char *duplicate_string(const char *source, size_t source_size,
                              size_t length)
{
    char *copy;

    if (source == NULL || length > source_size ||
        length > SIZE_MAX - 1U) {
        return NULL;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return NULL;
    }

    if (length != 0U) {
        memcpy(copy, source, length);
    }

    copy[length] = '\0';
    return copy;
}

static int initialize_tuple(Tuple *tuple, size_t size)
{
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

    tuple->size = size;
    return 0;
}

static void destroy_tuple(Tuple *tuple)
{
    size_t index;

    if (tuple == NULL) {
        return;
    }

    if (tuple->elements == NULL) {
        tuple->size = 0U;
        return;
    }

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

    free(tuple->elements);
    tuple->elements = NULL;
    tuple->size = 0U;
}

static int element_is_uninitialized(const Tuple *tuple, size_t index)
{
    return tuple != NULL &&
           tuple->elements != NULL &&
           index < tuple->size &&
           tuple->elements[index].type == ELEMENT_UNINITIALIZED;
}

static int set_integer(Tuple *tuple, size_t index, long value)
{
    if (!element_is_uninitialized(tuple, index)) {
        return -1;
    }

    tuple->elements[index].value.integer = value;
    tuple->elements[index].type = ELEMENT_INTEGER;
    return 0;
}

static int set_string(Tuple *tuple, size_t index, const char *value,
                      size_t value_size, size_t length)
{
    char *copy;

    if (!element_is_uninitialized(tuple, index) ||
        value == NULL ||
        length > value_size ||
        length > SIZE_MAX - 1U) {
        return -1;
    }

    copy = duplicate_string(value, value_size, length);
    if (copy == NULL) {
        return -1;
    }

    tuple->elements[index].value.string = copy;
    tuple->elements[index].type = ELEMENT_STRING;
    return 0;
}

static int set_nested_tuple(Tuple *tuple, size_t index, Tuple *nested)
{
    if (!element_is_uninitialized(tuple, index) ||
        nested == NULL ||
        nested == tuple) {
        return -1;
    }

    tuple->elements[index].value.tuple = nested;
    tuple->elements[index].type = ELEMENT_TUPLE;
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
        return frequency->value.string != NULL &&
               element->value.string != NULL &&
               strcmp(frequency->value.string,
                      element->value.string) == 0;

    default:
        return 0;
    }
}

static int grow_frequency_table(FrequencyTable *table)
{
    size_t new_capacity;
    Frequency *new_items;

    if (table == NULL ||
        table->size > table->capacity ||
        (table->capacity != 0U && table->items == NULL)) {
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
    Frequency *frequency;

    if (table == NULL ||
        element == NULL ||
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

    frequency = &table->items[table->size];
    frequency->type = element->type;
    frequency->count = 1U;

    if (element->type == ELEMENT_INTEGER) {
        frequency->value.integer = element->value.integer;
    } else {
        frequency->value.string = element->value.string;
    }

    ++table->size;
    return 0;
}

static int tuple_is_ancestor(const Tuple *tuple,
                             const Tuple *const *ancestors,
                             size_t ancestor_count)
{
    size_t index;

    if (tuple == NULL || ancestors == NULL) {
        return 0;
    }

    for (index = 0U; index < ancestor_count; ++index) {
        if (ancestors[index] == tuple) {
            return 1;
        }
    }

    return 0;
}

static int count_element_frequencies_recursive(
    const Tuple *tuple, FrequencyTable *table, const Tuple **ancestors,
    size_t depth, size_t ancestor_capacity)
{
    size_t index;

    if (tuple == NULL ||
        table == NULL ||
        ancestors == NULL ||
        depth >= ancestor_capacity ||
        (tuple->size != 0U && tuple->elements == NULL) ||
        tuple_is_ancestor(tuple, ancestors, depth)) {
        return -1;
    }

    ancestors[depth] = tuple;

    for (index = 0U; index < tuple->size; ++index) {
        const Element *element = &tuple->elements[index];

        switch (element->type) {
        case ELEMENT_INTEGER:
        case ELEMENT_STRING:
            if (add_frequency(table, element) != 0) {
                ancestors[depth] = NULL;
                return -1;
            }
            break;

        case ELEMENT_TUPLE:
            if (element->value.tuple == NULL ||
                count_element_frequencies_recursive(
                    element->value.tuple, table, ancestors, depth + 1U,
                    ancestor_capacity) != 0) {
                ancestors[depth] = NULL;
                return -1;
            }
            break;

        default:
            ancestors[depth] = NULL;
            return -1;
        }
    }

    ancestors[depth] = NULL;
    return 0;
}

static int count_element_frequencies(const Tuple *tuple,
                                     FrequencyTable *table)
{
    const size_t capacity = 64U;
    const Tuple **ancestors;
    int result;

    if (tuple == NULL || table == NULL) {
        return -1;
    }

    if (capacity > SIZE_MAX / sizeof(*ancestors)) {
        return -1;
    }

    ancestors = calloc(capacity, sizeof(*ancestors));
    if (ancestors == NULL) {
        return -1;
    }

    result = count_element_frequencies_recursive(
        tuple, table, ancestors, 0U, capacity);

    free(ancestors);
    return result;
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

    if (table == NULL ||
        table->size > table->capacity ||
        (table->size != 0U && table->items == NULL)) {
        return -1;
    }

    for (index = 0U; index < table->size; ++index) {
        const Frequency *frequency = &table->items[index];
        int result;

        if (frequency->type == ELEMENT_INTEGER) {
            result = printf("%ld: %zu\n",
                            frequency->value.integer,
                            frequency->count);
        } else if (frequency->type == ELEMENT_STRING &&
                   frequency->value.string != NULL) {
            result = printf("\"%s\": %zu\n",
                            frequency->value.string,
                            frequency->count);
        } else {
            return -1;
        }

        if (result < 0) {
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

    nested = calloc(1U, sizeof(*nested));
    if (nested == NULL) {
        goto cleanup;
    }

    deeper = calloc(1U, sizeof(*deeper));
    if (deeper == NULL) {
        goto cleanup;
    }

    if (initialize_tuple(nested, 4U) != 0 ||
        initialize_tuple(deeper, 3U) != 0 ||
        set_integer(&root, 0U, 42L) != 0 ||
        set_string(&root, 1U, "apple", sizeof("apple") - 1U,
                   sizeof("apple") - 1U) != 0 ||
        set_integer(nested, 0U, 42L) != 0 ||
        set_string(nested, 1U, "banana", sizeof("banana") - 1U,
                   sizeof("banana") - 1U) != 0 ||
        set_integer(nested, 2U, 7L) != 0 ||
        set_string(deeper, 0U, "apple", sizeof("apple") - 1U,
                   sizeof("apple") - 1U) != 0 ||
        set_integer(deeper, 1U, 42L) != 0 ||
        set_string(deeper, 2U, "banana", sizeof("banana") - 1U,
                   sizeof("banana") - 1U) != 0 ||
        set_nested_tuple(nested, 3U, deeper) != 0) {
        goto cleanup;
    }

    deeper = NULL;

    if (set_nested_tuple(&root, 2U, nested) != 0) {
        goto cleanup;
    }

    nested = NULL;

    if (set_string(&root, 3U, "apple", sizeof("apple") - 1U,
                   sizeof("apple") - 1U) != 0 ||
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