#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef enum {
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
        char *string;
    } value;
    size_t frequency;
} Frequency;

typedef struct {
    Frequency *items;
    size_t size;
    size_t capacity;
} FrequencyTable;

static char *duplicate_string(const char *source)
{
    char *copy;
    size_t length;

    if (source == NULL) {
        return NULL;
    }

    length = strlen(source);
    if (length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, source, length + 1U);
    return copy;
}

static int frequencies_equal(const Frequency *frequency, const Element *element)
{
    if (frequency == NULL || element == NULL || frequency->type != element->type) {
        return 0;
    }

    if (element->type == ELEMENT_INTEGER) {
        return frequency->value.integer == element->value.integer;
    }

    if (element->type == ELEMENT_STRING) {
        return frequency->value.string != NULL &&
               element->value.string != NULL &&
               strcmp(frequency->value.string, element->value.string) == 0;
    }

    return 0;
}

static int reserve_frequencies(FrequencyTable *table, size_t required)
{
    Frequency *resized;
    size_t new_capacity;

    if (table == NULL) {
        return -1;
    }

    if (required <= table->capacity) {
        return 0;
    }

    new_capacity = table->capacity == 0U ? 8U : table->capacity;
    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2U) {
            new_capacity = required;
            break;
        }
        new_capacity *= 2U;
    }

    if (new_capacity > SIZE_MAX / sizeof(*table->items)) {
        return -1;
    }

    resized = realloc(table->items, new_capacity * sizeof(*table->items));
    if (resized == NULL) {
        return -1;
    }

    table->items = resized;
    table->capacity = new_capacity;
    return 0;
}

static int add_frequency(FrequencyTable *table, const Element *element)
{
    size_t i;
    Frequency *frequency;

    if (table == NULL || element == NULL) {
        return -1;
    }

    if (element->type != ELEMENT_INTEGER && element->type != ELEMENT_STRING) {
        return -1;
    }

    if (element->type == ELEMENT_STRING && element->value.string == NULL) {
        return -1;
    }

    for (i = 0U; i < table->size; ++i) {
        if (frequencies_equal(&table->items[i], element)) {
            if (table->items[i].frequency == SIZE_MAX) {
                return -1;
            }
            ++table->items[i].frequency;
            return 0;
        }
    }

    if (table->size == SIZE_MAX ||
        reserve_frequencies(table, table->size + 1U) != 0) {
        return -1;
    }

    frequency = &table->items[table->size];
    frequency->type = element->type;
    frequency->frequency = 1U;

    if (element->type == ELEMENT_INTEGER) {
        frequency->value.integer = element->value.integer;
    } else {
        frequency->value.string = duplicate_string(element->value.string);
        if (frequency->value.string == NULL) {
            return -1;
        }
    }

    ++table->size;
    return 0;
}

static int count_element_frequency(const Tuple *tuple, FrequencyTable *table)
{
    size_t i;
    /* Possible weaknesses found:
     *  The scope of the variable 'element' can be reduced. [variableScope]
     */
    const Element *element;

    if (tuple == NULL || table == NULL) {
        return -1;
    }

    if (tuple->size != 0U && tuple->elements == NULL) {
        return -1;
    }

    for (i = 0U; i < tuple->size; ++i) {
        element = &tuple->elements[i];

        switch (element->type) {
            case ELEMENT_INTEGER:
            case ELEMENT_STRING:
                if (add_frequency(table, element) != 0) {
                    return -1;
                }
                break;
            case ELEMENT_TUPLE:
                if (element->value.tuple == NULL ||
                    count_element_frequency(element->value.tuple, table) != 0) {
                    return -1;
                }
                break;
            default:
                return -1;
        }
    }

    return 0;
}

static void free_frequency_table(FrequencyTable *table)
{
    size_t i;

    if (table == NULL) {
        return;
    }

    for (i = 0U; i < table->size; ++i) {
        if (table->items[i].type == ELEMENT_STRING) {
            free(table->items[i].value.string);
            table->items[i].value.string = NULL;
        }
    }

    free(table->items);
    table->items = NULL;
    table->size = 0U;
    table->capacity = 0U;
}

static int print_frequency_table(const FrequencyTable *table)
{
    size_t i;

    if (table == NULL) {
        return -1;
    }

    for (i = 0U; i < table->size; ++i) {
        int result;

        if (table->items[i].type == ELEMENT_INTEGER) {
            result = printf("%ld: %zu\n",
                            table->items[i].value.integer,
                            table->items[i].frequency);
        } else if (table->items[i].type == ELEMENT_STRING) {
            result = printf("\"%s\": %zu\n",
                            table->items[i].value.string,
                            table->items[i].frequency);
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
    Element inner_elements[] = {
        { .type = ELEMENT_INTEGER, .value.integer = 2 },
        { .type = ELEMENT_STRING, .value.string = "apple" },
        { .type = ELEMENT_INTEGER, .value.integer = 1 }
    };
    Tuple inner_tuple = {
        .elements = inner_elements,
        .size = sizeof(inner_elements) / sizeof(inner_elements[0])
    };

    Element deeper_elements[] = {
        { .type = ELEMENT_STRING, .value.string = "banana" },
        { .type = ELEMENT_INTEGER, .value.integer = 2 }
    };
    Tuple deeper_tuple = {
        .elements = deeper_elements,
        .size = sizeof(deeper_elements) / sizeof(deeper_elements[0])
    };

    Element outer_elements[] = {
        { .type = ELEMENT_INTEGER, .value.integer = 1 },
        { .type = ELEMENT_STRING, .value.string = "apple" },
        { .type = ELEMENT_TUPLE, .value.tuple = &inner_tuple },
        { .type = ELEMENT_TUPLE, .value.tuple = &deeper_tuple },
        { .type = ELEMENT_STRING, .value.string = "banana" }
    };
    Tuple outer_tuple = {
        .elements = outer_elements,
        .size = sizeof(outer_elements) / sizeof(outer_elements[0])
    };

    FrequencyTable table = {
        .items = NULL,
        .size = 0U,
        .capacity = 0U
    };
    int status = EXIT_SUCCESS;

    errno = 0;

    if (count_element_frequency(&outer_tuple, &table) != 0) {
        fprintf(stderr, "Failed to count element frequencies\n");
        status = EXIT_FAILURE;
    } else if (print_frequency_table(&table) != 0) {
        fprintf(stderr, "Failed to print element frequencies\n");
        status = EXIT_FAILURE;
    }

    free_frequency_table(&table);
    return status;
}