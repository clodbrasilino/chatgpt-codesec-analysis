#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Dictionary Dictionary;

typedef enum {
    VALUE_SCALAR,
    VALUE_DICTIONARY
} ValueType;

typedef struct {
    ValueType type;
    union {
        const char *scalar;
        const Dictionary *dictionary;
    } data;
} Value;

typedef struct {
    const char *key;
    Value value;
} DictionaryEntry;

struct Dictionary {
    size_t count;
    const DictionaryEntry *entries;
};

typedef struct {
    const Dictionary *dictionary;
    size_t next_entry;
} TraversalFrame;

static int reserve_frames(TraversalFrame **frames, size_t *capacity,
                          size_t required)
{
    TraversalFrame *new_frames;
    size_t new_capacity;

    if (required <= *capacity) {
        return 0;
    }

    new_capacity = *capacity == 0U ? 8U : *capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2U) {
            new_capacity = required;
            break;
        }
        new_capacity *= 2U;
    }

    if (new_capacity > SIZE_MAX / sizeof(**frames)) {
        return EOVERFLOW;
    }

    new_frames = realloc(*frames, new_capacity * sizeof(*new_frames));
    if (new_frames == NULL) {
        return ENOMEM;
    }

    *frames = new_frames;
    *capacity = new_capacity;
    return 0;
}

int dictionary_depth(const Dictionary *dictionary, size_t *depth)
{
    TraversalFrame *frames = NULL;
    size_t frame_count = 0U;
    size_t frame_capacity = 0U;
    size_t maximum_depth = 0U;
    int status;

    if (dictionary == NULL || depth == NULL) {
        return EINVAL;
    }

    *depth = 0U;

    if (dictionary->count != 0U && dictionary->entries == NULL) {
        return EINVAL;
    }

    status = reserve_frames(&frames, &frame_capacity, 1U);
    if (status != 0) {
        return status;
    }

    frames[0].dictionary = dictionary;
    frames[0].next_entry = 0U;
    frame_count = 1U;
    maximum_depth = 1U;

    while (frame_count != 0U) {
        TraversalFrame *frame = &frames[frame_count - 1U];
        const DictionaryEntry *entry;
        const Dictionary *nested;
        size_t i;

        if (frame->next_entry >= frame->dictionary->count) {
            --frame_count;
            continue;
        }

        entry = &frame->dictionary->entries[frame->next_entry++];

        if (entry->key == NULL) {
            status = EINVAL;
            goto cleanup;
        }

        if (entry->value.type == VALUE_SCALAR) {
            continue;
        }

        if (entry->value.type != VALUE_DICTIONARY) {
            status = EINVAL;
            goto cleanup;
        }

        nested = entry->value.data.dictionary;

        if (nested == NULL ||
            (nested->count != 0U && nested->entries == NULL)) {
            status = EINVAL;
            goto cleanup;
        }

        for (i = 0U; i < frame_count; ++i) {
            if (frames[i].dictionary == nested) {
                status = ELOOP;
                goto cleanup;
            }
        }

        if (frame_count == SIZE_MAX) {
            status = EOVERFLOW;
            goto cleanup;
        }

        status = reserve_frames(&frames, &frame_capacity, frame_count + 1U);
        if (status != 0) {
            goto cleanup;
        }

        frames[frame_count].dictionary = nested;
        frames[frame_count].next_entry = 0U;
        ++frame_count;

        if (frame_count > maximum_depth) {
            maximum_depth = frame_count;
        }
    }

    *depth = maximum_depth;
    status = 0;

cleanup:
    free(frames);
    return status;
}

int main(void)
{
    const Dictionary leaf = {0U, NULL};

    const DictionaryEntry middle_entries[] = {
        {"leaf", {VALUE_DICTIONARY, {.dictionary = &leaf}}}
    };
    const Dictionary middle = {
        sizeof(middle_entries) / sizeof(middle_entries[0]),
        middle_entries
    };

    const DictionaryEntry root_entries[] = {
        {"name", {VALUE_SCALAR, {.scalar = "example"}}},
        {"nested", {VALUE_DICTIONARY, {.dictionary = &middle}}}
    };
    const Dictionary root = {
        sizeof(root_entries) / sizeof(root_entries[0]),
        root_entries
    };

    size_t depth;
    int status = dictionary_depth(&root, &depth);

    if (status != 0) {
        fprintf(stderr, "Unable to determine dictionary depth: %d\n", status);
        return EXIT_FAILURE;
    }

    printf("%zu\n", depth);
    return EXIT_SUCCESS;
}