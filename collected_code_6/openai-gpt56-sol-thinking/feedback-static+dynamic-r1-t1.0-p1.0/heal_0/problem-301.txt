#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Dictionary Dictionary;

typedef enum {
    VALUE_INTEGER,
    VALUE_DICTIONARY
} ValueType;

typedef struct {
    const char *key;
    ValueType type;
    union {
        long integer;
        const Dictionary *dictionary;
    } value;
} DictionaryEntry;

struct Dictionary {
    const DictionaryEntry *entries;
    size_t count;
};

typedef enum {
    DICTIONARY_DEPTH_OK,
    DICTIONARY_DEPTH_INVALID,
    DICTIONARY_DEPTH_CYCLE,
    DICTIONARY_DEPTH_NO_MEMORY,
    DICTIONARY_DEPTH_OVERFLOW
} DictionaryDepthStatus;

typedef struct {
    const Dictionary *dictionary;
    size_t next_entry;
    size_t depth;
} DepthFrame;

DictionaryDepthStatus dictionary_depth(const Dictionary *root, size_t *depth)
{
    DepthFrame *frames;
    size_t frame_count = 1;
    size_t capacity = 8;
    size_t maximum_depth = 1;

    if (root == NULL || depth == NULL ||
        (root->count != 0 && root->entries == NULL)) {
        return DICTIONARY_DEPTH_INVALID;
    }

    frames = malloc(capacity * sizeof(*frames));
    if (frames == NULL) {
        return DICTIONARY_DEPTH_NO_MEMORY;
    }

    frames[0] = (DepthFrame){root, 0, 1};

    while (frame_count != 0) {
        DepthFrame *current = &frames[frame_count - 1];

        if (current->next_entry >= current->dictionary->count) {
            --frame_count;
            continue;
        }

        const DictionaryEntry *entry =
            &current->dictionary->entries[current->next_entry++];

        if (entry->key == NULL) {
            free(frames);
            return DICTIONARY_DEPTH_INVALID;
        }

        if (entry->type == VALUE_INTEGER) {
            continue;
        }

        if (entry->type != VALUE_DICTIONARY ||
            entry->value.dictionary == NULL ||
            (entry->value.dictionary->count != 0 &&
             entry->value.dictionary->entries == NULL)) {
            free(frames);
            return DICTIONARY_DEPTH_INVALID;
        }

        for (size_t i = 0; i < frame_count; ++i) {
            if (frames[i].dictionary == entry->value.dictionary) {
                free(frames);
                return DICTIONARY_DEPTH_CYCLE;
            }
        }

        if (current->depth == SIZE_MAX) {
            free(frames);
            return DICTIONARY_DEPTH_OVERFLOW;
        }

        if (frame_count == capacity) {
            if (capacity > SIZE_MAX / 2 ||
                capacity * 2 > SIZE_MAX / sizeof(*frames)) {
                free(frames);
                return DICTIONARY_DEPTH_OVERFLOW;
            }

            size_t new_capacity = capacity * 2;
            DepthFrame *resized =
                realloc(frames, new_capacity * sizeof(*frames));

            if (resized == NULL) {
                free(frames);
                return DICTIONARY_DEPTH_NO_MEMORY;
            }

            frames = resized;
            capacity = new_capacity;
        }

        size_t child_depth = current->depth + 1;
        frames[frame_count++] =
            (DepthFrame){entry->value.dictionary, 0, child_depth};

        if (child_depth > maximum_depth) {
            maximum_depth = child_depth;
        }
    }

    free(frames);
    *depth = maximum_depth;
    return DICTIONARY_DEPTH_OK;
}

int main(void)
{
    const DictionaryEntry third_level_entries[] = {
        {"value", VALUE_INTEGER, {.integer = 42}}
    };
    const Dictionary third_level = {
        third_level_entries,
        sizeof(third_level_entries) / sizeof(third_level_entries[0])
    };

    const DictionaryEntry second_level_entries[] = {
        {"nested", VALUE_DICTIONARY, {.dictionary = &third_level}}
    };
    const Dictionary second_level = {
        second_level_entries,
        sizeof(second_level_entries) / sizeof(second_level_entries[0])
    };

    const DictionaryEntry root_entries[] = {
        {"number", VALUE_INTEGER, {.integer = 7}},
        {"dictionary", VALUE_DICTIONARY, {.dictionary = &second_level}}
    };
    const Dictionary root = {
        root_entries,
        sizeof(root_entries) / sizeof(root_entries[0])
    };

    size_t depth;
    DictionaryDepthStatus status = dictionary_depth(&root, &depth);

    if (status != DICTIONARY_DEPTH_OK) {
        if (fprintf(stderr, "Unable to determine dictionary depth: %d\n",
                    (int)status) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", depth) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}