#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef enum {
    ELEM_INT,
    ELEM_STR,
    ELEM_TUPLE
} ElemType;

struct Tuple;

typedef struct Element {
    ElemType type;
    union {
        int ival;
        const char *sval;
        const struct Tuple *tval;
    } value;
} Element;

typedef struct Tuple {
    const Element *items;
    size_t count;
} Tuple;

typedef struct FreqEntry {
    ElemType type;
    int ival;
    const char *sval;
    size_t count;
} FreqEntry;

typedef struct FreqTable {
    FreqEntry *entries;
    size_t size;
    size_t capacity;
} FreqTable;

static void freq_table_init(FreqTable *table)
{
    table->entries = NULL;
    table->size = 0;
    table->capacity = 0;
}

static void freq_table_free(FreqTable *table)
{
    if (table != NULL) {
        free(table->entries);
        table->entries = NULL;
        table->size = 0;
        table->capacity = 0;
    }
}

static int freq_table_add(FreqTable *table, ElemType type, int ival, const char *sval)
{
    size_t i;
    for (i = 0; i < table->size; i++) {
        FreqEntry *entry = &table->entries[i];
        if (entry->type != type) {
            continue;
        }
        if (type == ELEM_INT && entry->ival == ival) {
            if (entry->count == SIZE_MAX) {
                return -1;
            }
            entry->count++;
            return 0;
        }
        if (type == ELEM_STR && strcmp(entry->sval, sval) == 0) {
            if (entry->count == SIZE_MAX) {
                return -1;
            }
            entry->count++;
            return 0;
        }
    }
    if (table->size == table->capacity) {
        size_t new_capacity = (table->capacity == 0) ? 8 : table->capacity * 2;
        FreqEntry *tmp;
        if (new_capacity <= table->capacity) {
            return -1;
        }
        if (new_capacity > SIZE_MAX / sizeof(FreqEntry)) {
            return -1;
        }
        tmp = realloc(table->entries, new_capacity * sizeof(FreqEntry));
        if (tmp == NULL) {
            return -1;
        }
        table->entries = tmp;
        table->capacity = new_capacity;
    }
    table->entries[table->size].type = type;
    table->entries[table->size].ival = ival;
    table->entries[table->size].sval = sval;
    table->entries[table->size].count = 1;
    table->size++;
    return 0;
}

static int count_frequency(const Tuple *tuple, FreqTable *table)
{
    size_t i;
    if (tuple == NULL || table == NULL) {
        return -1;
    }
    if (tuple->count > 0 && tuple->items == NULL) {
        return -1;
    }
    for (i = 0; i < tuple->count; i++) {
        const Element *elem = &tuple->items[i];
        switch (elem->type) {
        case ELEM_INT:
            if (freq_table_add(table, ELEM_INT, elem->value.ival, NULL) != 0) {
                return -1;
            }
            break;
        case ELEM_STR:
            if (elem->value.sval == NULL) {
                return -1;
            }
            if (freq_table_add(table, ELEM_STR, 0, elem->value.sval) != 0) {
                return -1;
            }
            break;
        case ELEM_TUPLE:
            if (elem->value.tval == NULL) {
                return -1;
            }
            if (count_frequency(elem->value.tval, table) != 0) {
                return -1;
            }
            break;
        default:
            return -1;
        }
    }
    return 0;
}

static void print_frequency(const FreqTable *table)
{
    size_t i;
    for (i = 0; i < table->size; i++) {
        const FreqEntry *entry = &table->entries[i];
        if (entry->type == ELEM_INT) {
            printf("%d : %zu\n", entry->ival, entry->count);
        } else {
            printf("%s : %zu\n", entry->sval, entry->count);
        }
    }
}

int main(void)
{
    static const Element inner_items[] = {
        { ELEM_INT, { .ival = 5 } },
        { ELEM_STR, { .sval = "green" } },
        { ELEM_INT, { .ival = 5 } }
    };
    static const Tuple inner = { inner_items, 3 };

    static const Element middle_items[] = {
        { ELEM_STR, { .sval = "orange" } },
        { ELEM_TUPLE, { .tval = &inner } },
        { ELEM_INT, { .ival = 7 } }
    };
    static const Tuple middle = { middle_items, 3 };

    static const Element outer_items[] = {
        { ELEM_INT, { .ival = 5 } },
        { ELEM_STR, { .sval = "green" } },
        { ELEM_TUPLE, { .tval = &middle } },
        { ELEM_STR, { .sval = "orange" } },
        { ELEM_INT, { .ival = 7 } },
        { ELEM_INT, { .ival = 9 } }
    };
    static const Tuple outer = { outer_items, 6 };

    FreqTable table;
    freq_table_init(&table);

    if (count_frequency(&outer, &table) != 0) {
        fprintf(stderr, "Failed to count element frequency\n");
        freq_table_free(&table);
        return EXIT_FAILURE;
    }

    print_frequency(&table);
    freq_table_free(&table);
    return EXIT_SUCCESS;
}