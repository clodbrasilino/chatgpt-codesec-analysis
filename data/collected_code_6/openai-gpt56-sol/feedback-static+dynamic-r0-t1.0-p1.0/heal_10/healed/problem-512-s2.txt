#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    ELEMENT_INTEGER,
    ELEMENT_STRING,
    ELEMENT_TUPLE
} ElementType;

typedef struct Tuple Tuple;

typedef struct {
    const char *data;
    size_t length;
} StringView;

typedef struct {
    ElementType type;
    union {
        long integer;
        StringView string;
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
        struct {
            char *data;
            size_t length;
        } string;
    } value;
    size_t frequency;
} Frequency;

typedef struct {
    Frequency *items;
    size_t size;
    size_t capacity;
} FrequencyTable;

static int duplicate_string(const char *source, size_t length,
                            char **destination)
{
    char *copy;

    if (destination == NULL || (source == NULL && length != 0U)) {
        return -1;
    }

    *destination = NULL;

    if (length > SIZE_MAX - 1U) {
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

static int frequencies_equal(const Frequency *frequency,
                             const Element *element)
{
    size_t length;

    if (frequency == NULL || element == NULL ||
        frequency->type != element->type) {
        return 0;
    }

    switch (element->type) {
        case ELEMENT_INTEGER:
            return frequency->value.integer == element->value.integer;

        case ELEMENT_STRING:
            length = element->value.string.length;

            if (frequency->value.string.length != length) {
                return 0;
            }

            if (length == 0U) {
                return 1;
            }

            if (frequency->value.string.data == NULL ||
                element->value.string.data == NULL) {
                return 0;
            }

            return memcmp(frequency->value.string.data,
                          element->value.string.data,
                          length) == 0;

        case ELEMENT_TUPLE:
        default:
            return 0;
    }
}

static int reserve_frequencies(FrequencyTable *table, size_t required)
{
    Frequency *resized;
    size_t new_capacity;

    if (table == NULL ||
        table->size > table->capacity ||
        (table->capacity != 0U && table->items == NULL)) {
        return -1;
    }

    if (required <= table->capacity) {
        return 0;
    }

    if (required > SIZE_MAX / sizeof(*table->items)) {
        return -1;
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

    resized = realloc(table->items,
                      new_capacity * sizeof(*table->items));
    if (resized == NULL) {
        return -1;
    }

    table->items = resized;
    table->capacity = new_capacity;
    return 0;
}

static int add_frequency(FrequencyTable *table, const Element *element)
{
    Frequency *frequency;
    size_t i;

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
        element->value.string.length != 0U &&
        element->value.string.data == NULL) {
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
    memset(frequency, 0, sizeof(*frequency));
    frequency->type = element->type;
    frequency->frequency = 1U;

    if (element->type == ELEMENT_INTEGER) {
        frequency->value.integer = element->value.integer;
    } else {
        if (duplicate_string(element->value.string.data,
                             element->value.string.length,
                             &frequency->value.string.data) != 0) {
            memset(frequency, 0, sizeof(*frequency));
            return -1;
        }

        frequency->value.string.length = element->value.string.length;
    }

    ++table->size;
    return 0;
}

static int count_element_frequency(const Tuple *tuple,
                                   FrequencyTable *table)
{
    size_t i;

    if (tuple == NULL ||
        table == NULL ||
        (tuple->size != 0U && tuple->elements == NULL)) {
        return -1;
    }

    for (i = 0U; i < tuple->size; ++i) {
        const Element *element = &tuple->elements[i];

        switch (element->type) {
            case ELEMENT_INTEGER:
            case ELEMENT_STRING:
                if (add_frequency(table, element) != 0) {
                    return -1;
                }
                break;

            case ELEMENT_TUPLE:
                if (element->value.tuple == NULL ||
                    count_element_frequency(element->value.tuple,
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

static void free_frequency_table(FrequencyTable *table)
{
    size_t i;

    if (table == NULL) {
        return;
    }

    if (table->items != NULL) {
        for (i = 0U; i < table->size; ++i) {
            if (table->items[i].type == ELEMENT_STRING) {
                free(table->items[i].value.string.data);
            }
        }
    }

    free(table->items);
    table->items = NULL;
    table->size = 0U;
    table->capacity = 0U;
}

static int print_string(const char *data, size_t length)
{
    if (length != 0U && data == NULL) {
        return -1;
    }

    if (fputc('"', stdout) == EOF) {
        return -1;
    }

    if (length != 0U && fwrite(data, 1U, length, stdout) != length) {
        return -1;
    }

    return fputc('"', stdout) == EOF ? -1 : 0;
}

static int print_frequency_table(const FrequencyTable *table)
{
    size_t i;

    if (table == NULL ||
        table->size > table->capacity ||
        (table->size != 0U && table->items == NULL)) {
        return -1;
    }

    for (i = 0U; i < table->size; ++i) {
        switch (table->items[i].type) {
            case ELEMENT_INTEGER:
                if (printf("%ld: %zu\n",
                           table->items[i].value.integer,
                           table->items[i].frequency) < 0) {
                    return -1;
                }
                break;

            case ELEMENT_STRING:
                if (print_string(table->items[i].value.string.data,
                                 table->items[i].value.string.length) != 0 ||
                    printf(": %zu\n", table->items[i].frequency) < 0) {
                    return -1;
                }
                break;

            case ELEMENT_TUPLE:
            default:
                return -1;
        }
    }

    return 0;
}

int main(void)
{
    Element inner_elements[] = {
        {
            .type = ELEMENT_INTEGER,
            .value.integer = 2
        },
        {
            .type = ELEMENT_STRING,
            .value.string = {
                .data = "apple",
                .length = sizeof("apple") - 1U
            }
        },
        {
            .type = ELEMENT_INTEGER,
            .value.integer = 1
        }
    };

    Tuple inner_tuple = {
        .elements = inner_elements,
        .size = sizeof(inner_elements) / sizeof(inner_elements[0])
    };

    Element deeper_elements[] = {
        {
            .type = ELEMENT_STRING,
            .value.string = {
                .data = "banana",
                .length = sizeof("banana") - 1U
            }
        },
        {
            .type = ELEMENT_INTEGER,
            .value.integer = 2
        }
    };

    Tuple deeper_tuple = {
        .elements = deeper_elements,
        .size = sizeof(deeper_elements) / sizeof(deeper_elements[0])
    };

    Element outer_elements[] = {
        {
            .type = ELEMENT_INTEGER,
            .value.integer = 1
        },
        {
            .type = ELEMENT_STRING,
            .value.string = {
                .data = "apple",
                .length = sizeof("apple") - 1U
            }
        },
        {
            .type = ELEMENT_TUPLE,
            .value.tuple = &inner_tuple
        },
        {
            .type = ELEMENT_TUPLE,
            .value.tuple = &deeper_tuple
        },
        {
            .type = ELEMENT_STRING,
            .value.string = {
                .data = "banana",
                .length = sizeof("banana") - 1U
            }
        }
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

    if (count_element_frequency(&outer_tuple, &table) != 0) {
        fputs("Failed to count element frequencies\n", stderr);
        status = EXIT_FAILURE;
    } else if (print_frequency_table(&table) != 0) {
        fputs("Failed to print element frequencies\n", stderr);
        status = EXIT_FAILURE;
    }

    free_frequency_table(&table);
    return status;
}