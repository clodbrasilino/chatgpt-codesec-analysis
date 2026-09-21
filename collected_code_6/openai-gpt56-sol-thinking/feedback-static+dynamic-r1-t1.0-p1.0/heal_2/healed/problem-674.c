#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct WordNode {
    char *word;
    size_t length;
    size_t hash;
    struct WordNode *next;
} WordNode;

typedef struct {
    WordNode **buckets;
    size_t bucket_count;
    size_t size;
} WordCollection;

typedef enum {
    COLLECTION_ERROR = -1,
    COLLECTION_EXISTS = 0,
    COLLECTION_INSERTED = 1
} CollectionResult;

static int string_length(const char *string, size_t *length)
{
    size_t position = 0U;

    if (string == NULL || length == NULL) {
        return 0;
    }

    while (string[position] != '\0') {
        if (position == SIZE_MAX) {
            return 0;
        }

        ++position;
    }

    *length = position;
    return 1;
}

static void copy_bytes(char *destination, const char *source, size_t length)
{
    for (size_t position = 0U; position < length; ++position) {
        destination[position] = source[position];
    }
}

static size_t hash_word(const char *word, size_t length)
{
    size_t hash = 5381U;

    for (size_t position = 0U; position < length; ++position) {
        hash = ((hash << 5U) + hash) ^ (unsigned char)word[position];
    }

    return hash;
}

static int collection_init(WordCollection *collection)
{
    const size_t initial_bucket_count = 64U;

    if (collection == NULL) {
        return 0;
    }

    collection->buckets = NULL;
    collection->bucket_count = 0U;
    collection->size = 0U;

    if (initial_bucket_count >
        SIZE_MAX / sizeof(*collection->buckets)) {
        return 0;
    }

    collection->buckets = calloc(initial_bucket_count,
                                 sizeof(*collection->buckets));
    if (collection->buckets == NULL) {
        return 0;
    }

    collection->bucket_count = initial_bucket_count;
    return 1;
}

static void collection_destroy(WordCollection *collection)
{
    if (collection == NULL) {
        return;
    }

    if (collection->buckets != NULL) {
        for (size_t bucket = 0U;
             bucket < collection->bucket_count;
             ++bucket) {
            WordNode *node = collection->buckets[bucket];

            while (node != NULL) {
                WordNode *next = node->next;

                free(node->word);
                free(node);
                node = next;
            }
        }

        free(collection->buckets);
    }

    collection->buckets = NULL;
    collection->bucket_count = 0U;
    collection->size = 0U;
}

static int collection_resize(WordCollection *collection)
{
    WordNode **new_buckets;
    size_t new_bucket_count;

    if (collection == NULL ||
        collection->buckets == NULL ||
        collection->bucket_count == 0U ||
        collection->bucket_count > SIZE_MAX / 2U) {
        return 0;
    }

    new_bucket_count = collection->bucket_count * 2U;

    if (new_bucket_count > SIZE_MAX / sizeof(*new_buckets)) {
        return 0;
    }

    new_buckets = calloc(new_bucket_count, sizeof(*new_buckets));
    if (new_buckets == NULL) {
        return 0;
    }

    for (size_t bucket = 0U;
         bucket < collection->bucket_count;
         ++bucket) {
        WordNode *node = collection->buckets[bucket];

        while (node != NULL) {
            WordNode *next = node->next;
            size_t index = node->hash % new_bucket_count;

            node->next = new_buckets[index];
            new_buckets[index] = node;
            node = next;
        }
    }

    free(collection->buckets);
    collection->buckets = new_buckets;
    collection->bucket_count = new_bucket_count;

    return 1;
}

static int words_equal(const char *left, const char *right, size_t length)
{
    for (size_t position = 0U; position < length; ++position) {
        if (left[position] != right[position]) {
            return 0;
        }
    }

    return 1;
}

static CollectionResult collection_insert(WordCollection *collection,
                                          const char *word,
                                          size_t length)
{
    size_t hash;
    size_t index;
    char *copy;
    WordNode *new_node;

    if (collection == NULL ||
        collection->buckets == NULL ||
        collection->bucket_count == 0U ||
        word == NULL ||
        length == SIZE_MAX) {
        return COLLECTION_ERROR;
    }

    hash = hash_word(word, length);
    index = hash % collection->bucket_count;

    for (WordNode *node = collection->buckets[index];
         node != NULL;
         node = node->next) {
        if (node->hash == hash &&
            node->length == length &&
            words_equal(node->word, word, length)) {
            return COLLECTION_EXISTS;
        }
    }

    if (collection->size >=
        collection->bucket_count - collection->bucket_count / 4U) {
        if (!collection_resize(collection)) {
            return COLLECTION_ERROR;
        }

        index = hash % collection->bucket_count;
    }

    if (collection->size == SIZE_MAX) {
        return COLLECTION_ERROR;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return COLLECTION_ERROR;
    }

    copy_bytes(copy, word, length);
    copy[length] = '\0';

    new_node = malloc(sizeof(*new_node));
    if (new_node == NULL) {
        free(copy);
        return COLLECTION_ERROR;
    }

    new_node->word = copy;
    new_node->length = length;
    new_node->hash = hash;
    new_node->next = collection->buckets[index];

    collection->buckets[index] = new_node;
    ++collection->size;

    return COLLECTION_INSERTED;
}

char *remove_duplicate_words(const char *input)
{
    WordCollection collection = {NULL, 0U, 0U};
    char *output;
    size_t input_length;
    size_t input_position = 0U;
    size_t output_position = 0U;
    int first_word = 1;

    if (!string_length(input, &input_length) ||
        input_length == SIZE_MAX) {
        return NULL;
    }

    output = malloc(input_length + 1U);
    if (output == NULL) {
        return NULL;
    }

    if (!collection_init(&collection)) {
        free(output);
        return NULL;
    }

    while (input_position < input_length) {
        size_t word_start;
        size_t word_length;
        CollectionResult result;

        while (input_position < input_length &&
               isspace((unsigned char)input[input_position]) != 0) {
            ++input_position;
        }

        if (input_position == input_length) {
            break;
        }

        word_start = input_position;

        while (input_position < input_length &&
               isspace((unsigned char)input[input_position]) == 0) {
            ++input_position;
        }

        word_length = input_position - word_start;
        result = collection_insert(&collection,
                                   input + word_start,
                                   word_length);

        if (result == COLLECTION_ERROR) {
            collection_destroy(&collection);
            free(output);
            return NULL;
        }

        if (result == COLLECTION_INSERTED) {
            if (!first_word) {
                if (output_position >= input_length) {
                    collection_destroy(&collection);
                    free(output);
                    return NULL;
                }

                output[output_position++] = ' ';
            }

            if (word_length > input_length - output_position) {
                collection_destroy(&collection);
                free(output);
                return NULL;
            }

            copy_bytes(output + output_position,
                       input + word_start,
                       word_length);
            output_position += word_length;
            first_word = 0;
        }
    }

    output[output_position] = '\0';
    collection_destroy(&collection);

    return output;
}

int main(int argc, char *argv[])
{
    const char *input;
    char *result;
    int status = EXIT_SUCCESS;

    if (argc != 2) {
        const char *program_name =
            argc > 0 && argv != NULL && argv[0] != NULL
                ? argv[0]
                : "program";

        fprintf(stderr, "Usage: %s \"string\"\n", program_name);
        return EXIT_FAILURE;
    }

    input = argv[1];
    result = remove_duplicate_words(input);

    if (result == NULL) {
        fputs("Unable to process the string.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        status = EXIT_FAILURE;
    }

    free(result);
    return status;
}