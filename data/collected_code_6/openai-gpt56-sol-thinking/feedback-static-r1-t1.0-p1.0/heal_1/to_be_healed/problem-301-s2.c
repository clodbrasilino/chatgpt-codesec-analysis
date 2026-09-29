#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct Dictionary Dictionary;

typedef enum {
    VALUE_INTEGER,
    VALUE_STRING,
    VALUE_DICTIONARY
} ValueType;

typedef struct {
    ValueType type;
    union {
        long integer;
        const char *string;
        const Dictionary *dictionary;
    } data;
} DictionaryValue;

typedef struct {
    const char *key;
    DictionaryValue value;
} DictionaryEntry;

struct Dictionary {
    const DictionaryEntry *entries;
    size_t count;
};

typedef struct {
    const Dictionary *dictionary;
    size_t next_entry;
} TraversalFrame;

static bool push_frame(
    TraversalFrame **frames,
    size_t *length,
    size_t *capacity,
    const Dictionary *dictionary
) {
    TraversalFrame *new_frames;
    /* Possible weaknesses found:
     *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
     */
    size_t new_capacity;

    if (dictionary == NULL ||
        (dictionary->count > 0 && dictionary->entries == NULL)) {
        errno = EINVAL;
        return false;
    }

    if (*length == *capacity) {
        if (*capacity == 0) {
            new_capacity = 8;
        } else {
            if (*capacity > SIZE_MAX / 2) {
                errno = ENOMEM;
                return false;
            }
            new_capacity = *capacity * 2;
        }

        if (new_capacity > SIZE_MAX / sizeof(**frames)) {
            errno = ENOMEM;
            return false;
        }

        new_frames = realloc(*frames, new_capacity * sizeof(**frames));
        if (new_frames == NULL) {
            errno = ENOMEM;
            return false;
        }

        *frames = new_frames;
        *capacity = new_capacity;
    }

    (*frames)[*length].dictionary = dictionary;
    (*frames)[*length].next_entry = 0;
    ++(*length);

    return true;
}

bool find_dictionary_depth(
    const Dictionary *dictionary,
    size_t *result
) {
    TraversalFrame *frames = NULL;
    size_t length = 0;
    size_t capacity = 0;
    size_t maximum_depth = 0;
    bool success = false;

    if (dictionary == NULL || result == NULL) {
        errno = EINVAL;
        return false;
    }

    if (!push_frame(&frames, &length, &capacity, dictionary)) {
        goto cleanup;
    }

    maximum_depth = 1;

    while (length > 0) {
        TraversalFrame *frame = &frames[length - 1];
        const DictionaryEntry *entry;
        const Dictionary *child;
        size_t index;

        if (frame->next_entry == frame->dictionary->count) {
            --length;
            continue;
        }

        entry = &frame->dictionary->entries[frame->next_entry++];

        if (entry->key == NULL) {
            errno = EINVAL;
            goto cleanup;
        }

        switch (entry->value.type) {
            case VALUE_INTEGER:
                break;

            case VALUE_STRING:
                if (entry->value.data.string == NULL) {
                    errno = EINVAL;
                    goto cleanup;
                }
                break;

            case VALUE_DICTIONARY:
                child = entry->value.data.dictionary;

                if (child == NULL) {
                    errno = EINVAL;
                    goto cleanup;
                }

                for (index = 0; index < length; ++index) {
                    if (frames[index].dictionary == child) {
                        errno = EINVAL;
                        goto cleanup;
                    }
                }

                if (!push_frame(&frames, &length, &capacity, child)) {
                    goto cleanup;
                }

                if (length > maximum_depth) {
                    maximum_depth = length;
                }
                break;

            default:
                errno = EINVAL;
                goto cleanup;
        }
    }

    *result = maximum_depth;
    success = true;

cleanup:
    free(frames);
    return success;
}

int main(void) {
    const Dictionary deepest = {
        .entries = NULL,
        .count = 0
    };

    const DictionaryEntry middle_entries[] = {
        {
            .key = "deepest",
            .value = {
                .type = VALUE_DICTIONARY,
                .data.dictionary = &deepest
            }
        }
    };

    const Dictionary middle = {
        .entries = middle_entries,
        .count = sizeof(middle_entries) / sizeof(middle_entries[0])
    };

    const DictionaryEntry root_entries[] = {
        {
            .key = "name",
            .value = {
                .type = VALUE_STRING,
                .data.string = "example"
            }
        },
        {
            .key = "value",
            .value = {
                .type = VALUE_INTEGER,
                .data.integer = 42
            }
        },
        {
            .key = "middle",
            .value = {
                .type = VALUE_DICTIONARY,
                .data.dictionary = &middle
            }
        }
    };

    const Dictionary root = {
        .entries = root_entries,
        .count = sizeof(root_entries) / sizeof(root_entries[0])
    };

    size_t depth;

    if (!find_dictionary_depth(&root, &depth)) {
        perror("find_dictionary_depth");
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", depth) < 0 || fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}