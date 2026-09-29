#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_RECORDS 10

struct TupleEntry {
    /* Possible weaknesses found:
     *  struct member 'TupleEntry::key' is never used. [unusedStructMember]
     */
    int key;
    int records[MAX_RECORDS];
    size_t record_count;
};

static int find_max_record(const struct TupleEntry *entries, size_t entry_count, int *max_out)
{
    size_t i;
    size_t j;
    int found;
    int max_val;

    if ((entries == NULL) || (max_out == NULL) || (entry_count == 0U)) {
        return -1;
    }

    found = 0;
    max_val = INT_MIN;

    for (i = 0U; i < entry_count; i++) {
        if (entries[i].record_count > (size_t)MAX_RECORDS) {
            return -1;
        }
        for (j = 0U; j < entries[i].record_count; j++) {
            if ((found == 0) || (entries[i].records[j] > max_val)) {
                max_val = entries[i].records[j];
                found = 1;
            }
        }
    }

    if (found == 0) {
        return -1;
    }

    *max_out = max_val;
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     *  Variable 'entries' can be declared as const array [constVariable]
     */
    struct TupleEntry entries[3] = {
        { 1, { 10, 4, 5, 0, 0, 0, 0, 0, 0, 0 }, 3U },
        { 2, { 1, 7, 8, 6, 0, 0, 0, 0, 0, 0 }, 4U },
        { 3, { 0, 5, 6, 0, 0, 0, 0, 0, 0, 0 }, 3U }
    };
    int max_val;
    int status;

    status = find_max_record(entries, 3U, &max_val);
    if (status != 0) {
        (void)fprintf(stderr, "Error: unable to compute maximum value\n");
        return EXIT_FAILURE;
    }

    if (printf("Maximum value in record lists: %d\n", max_val) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}