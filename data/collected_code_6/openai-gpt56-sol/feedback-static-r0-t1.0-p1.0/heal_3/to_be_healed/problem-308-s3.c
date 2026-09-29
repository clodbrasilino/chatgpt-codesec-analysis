#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int64_t value;
    size_t row;
    size_t column;
} HeapNode;

static int compare_int64_desc(const void *lhs, const void *rhs)
{
    const int64_t a = *(const int64_t *)lhs;
    const int64_t b = *(const int64_t *)rhs;

    return (a < b) - (a > b);
}

static int64_t multiply_saturating(int64_t a, int64_t b)
{
    if (a == 0 || b == 0) {
        return 0;
    }

    if (a > 0) {
        if (b > 0 && a > INT64_MAX / b) {
            return INT64_MAX;
        }
        if (b < 0 && b < INT64_MIN / a) {
            return INT64_MIN;
        }
    } else {
        if (b > 0 && a < INT64_MIN / b) {
            return INT64_MIN;
        }
        if (b < 0 && a < INT64_MAX / b) {
            return INT64_MAX;
        }
    }

    return a * b;
}

static int heap_node_greater(const HeapNode *lhs, const HeapNode *rhs)
{
    if (lhs->value != rhs->value) {
        return lhs->value > rhs->value;
    }
    if (lhs->row != rhs->row) {
        return lhs->row < rhs->row;
    }
    return lhs->column < rhs->column;
}

static void heap_push(HeapNode *heap, size_t *size, HeapNode node)
{
    size_t index = *size;

    heap[index] = node;
    ++*size;

    while (index > 0) {
        size_t parent = (index - 1U) / 2U;

        if (!heap_node_greater(&heap[index], &heap[parent])) {
            break;
        }

        HeapNode temporary = heap[index];
        heap[index] = heap[parent];
        heap[parent] = temporary;
        index = parent;
    }
}

static HeapNode heap_pop(HeapNode *heap, size_t *size)
{
    HeapNode result = heap[0];

    --*size;
    if (*size == 0) {
        return result;
    }

    heap[0] = heap[*size];

    for (size_t index = 0;;) {
        size_t left;
        size_t right;
        size_t largest = index;

        if (index > (SIZE_MAX - 1U) / 2U) {
            break;
        }

        left = index * 2U + 1U;
        /* Possible weaknesses found:
         *  right is assigned 'left+1U' here.
         */
        right = left + 1U;

        if (left < *size &&
            heap_node_greater(&heap[left], &heap[largest])) {
            largest = left;
        }

        /* Possible weaknesses found:
         *  Condition 'right>left' is always true
         *  Condition 'right>left' is always true [knownConditionTrueFalse]
         */
        if (right > left && right < *size &&
            heap_node_greater(&heap[right], &heap[largest])) {
            largest = right;
        }

        if (largest == index) {
            break;
        }

        HeapNode temporary = heap[index];
        heap[index] = heap[largest];
        heap[largest] = temporary;
        index = largest;
    }

    return result;
}

static int find_largest_products(const int64_t *first,
                                 size_t first_count,
                                 const int64_t *second,
                                 size_t second_count,
                                 size_t requested_count,
                                 int64_t **products,
                                 size_t *product_count)
{
    int64_t *sorted_first = NULL;
    int64_t *sorted_second = NULL;
    HeapNode *heap = NULL;
    int64_t *result = NULL;
    const int64_t *rows;
    const int64_t *columns;
    size_t row_count;
    size_t column_count;
    size_t total_count;
    size_t output_count;
    size_t heap_size = 0;

    if (products == NULL || product_count == NULL) {
        return EINVAL;
    }

    *products = NULL;
    *product_count = 0;

    if ((first == NULL && first_count != 0) ||
        (second == NULL && second_count != 0)) {
        return EINVAL;
    }

    if (requested_count == 0 || first_count == 0 || second_count == 0) {
        return 0;
    }

    if (first_count > SIZE_MAX / second_count) {
        total_count = SIZE_MAX;
    } else {
        total_count = first_count * second_count;
    }

    output_count = requested_count < total_count
                       ? requested_count
                       : total_count;

    if (first_count <= second_count) {
        row_count = first_count;
        column_count = second_count;
    } else {
        row_count = second_count;
        column_count = first_count;
    }

    if (first_count > SIZE_MAX / sizeof(*sorted_first) ||
        second_count > SIZE_MAX / sizeof(*sorted_second) ||
        row_count > SIZE_MAX / sizeof(*heap) ||
        output_count > SIZE_MAX / sizeof(*result)) {
        return EOVERFLOW;
    }

    sorted_first = malloc(first_count * sizeof(*sorted_first));
    sorted_second = malloc(second_count * sizeof(*sorted_second));
    heap = malloc(row_count * sizeof(*heap));
    result = malloc(output_count * sizeof(*result));

    if (sorted_first == NULL || sorted_second == NULL ||
        heap == NULL || result == NULL) {
        free(result);
        free(heap);
        free(sorted_second);
        free(sorted_first);
        return ENOMEM;
    }

    for (size_t i = 0; i < first_count; ++i) {
        sorted_first[i] = first[i];
    }

    for (size_t i = 0; i < second_count; ++i) {
        sorted_second[i] = second[i];
    }

    qsort(sorted_first,
          first_count,
          sizeof(*sorted_first),
          compare_int64_desc);
    qsort(sorted_second,
          second_count,
          sizeof(*sorted_second),
          compare_int64_desc);

    rows = first_count <= second_count ? sorted_first : sorted_second;
    columns = first_count <= second_count ? sorted_second : sorted_first;

    for (size_t row = 0; row < row_count; ++row) {
        size_t column = rows[row] >= 0 ? 0 : column_count - 1U;
        HeapNode node = {
            multiply_saturating(rows[row], columns[column]),
            row,
            column
        };

        heap_push(heap, &heap_size, node);
    }

    for (size_t i = 0; i < output_count; ++i) {
        HeapNode node;

        if (heap_size == 0) {
            free(result);
            free(heap);
            free(sorted_second);
            free(sorted_first);
            return EINVAL;
        }

        node = heap_pop(heap, &heap_size);
        result[i] = node.value;

        if (rows[node.row] >= 0) {
            if (node.column < column_count - 1U) {
                ++node.column;
                node.value = multiply_saturating(
                    rows[node.row], columns[node.column]);
                heap_push(heap, &heap_size, node);
            }
        } else if (node.column > 0) {
            --node.column;
            node.value = multiply_saturating(
                rows[node.row], columns[node.column]);
            heap_push(heap, &heap_size, node);
        }
    }

    free(heap);
    free(sorted_second);
    free(sorted_first);

    *products = result;
    *product_count = output_count;
    return 0;
}

static int grow_token_buffer(char **buffer, size_t *capacity, size_t needed)
{
    size_t new_capacity;
    char *new_buffer;

    if (buffer == NULL || capacity == NULL) {
        return EINVAL;
    }

    if (*capacity >= needed) {
        return 0;
    }

    new_capacity = *capacity == 0 ? 32U : *capacity;

    while (new_capacity < needed) {
        if (new_capacity > SIZE_MAX / 2U) {
            new_capacity = SIZE_MAX;
        } else {
            new_capacity *= 2U;
        }

        if (new_capacity < needed && new_capacity == SIZE_MAX) {
            return EOVERFLOW;
        }
    }

    new_buffer = realloc(*buffer, new_capacity);
    if (new_buffer == NULL) {
        return ENOMEM;
    }

    *buffer = new_buffer;
    *capacity = new_capacity;
    return 0;
}

static int read_token(char **token)
{
    char *buffer = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int character;
    /* Possible weaknesses found:
     *  The scope of the variable 'status' can be reduced. [variableScope]
     */
    int status;

    if (token == NULL) {
        return EINVAL;
    }

    *token = NULL;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);
        if (character == EOF) {
            return ferror(stdin) ? EIO : EINVAL;
        }
        if (!isspace((unsigned char)character)) {
            break;
        }
    }

    for (;;) {
        if (length == SIZE_MAX - 1U) {
            free(buffer);
            return EOVERFLOW;
        }

        status = grow_token_buffer(&buffer, &capacity, length + 2U);
        if (status != 0) {
            free(buffer);
            return status;
        }

        buffer[length++] = (char)character;

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);
        if (character == EOF) {
            if (ferror(stdin)) {
                free(buffer);
                return EIO;
            }
            break;
        }

        if (isspace((unsigned char)character)) {
            break;
        }
    }

    buffer[length] = '\0';
    *token = buffer;
    return 0;
}

static int parse_uintmax_token(const char *token, uintmax_t *value)
{
    char *end = NULL;
    uintmax_t parsed;

    if (token == NULL || value == NULL || token[0] == '\0' ||
        token[0] == '-' || token[0] == '+') {
        return EINVAL;
    }

    errno = 0;
    parsed = strtoumax(token, &end, 10);

    if (errno == ERANGE) {
        return EOVERFLOW;
    }

    if (end == token || *end != '\0') {
        return EINVAL;
    }

    *value = parsed;
    return 0;
}

static int parse_int64_token(const char *token, int64_t *value)
{
    char *end = NULL;
    intmax_t parsed;

    if (token == NULL || value == NULL || token[0] == '\0') {
        return EINVAL;
    }

    errno = 0;
    parsed = strtoimax(token, &end, 10);

    if (errno == ERANGE || parsed < INT64_MIN || parsed > INT64_MAX) {
        return EOVERFLOW;
    }

    if (end == token || *end != '\0') {
        return EINVAL;
    }

    *value = (int64_t)parsed;
    return 0;
}

static int read_size(const char *name, size_t *value)
{
    char *token = NULL;
    uintmax_t input;
    int status;

    if (name == NULL || value == NULL) {
        return EINVAL;
    }

    status = read_token(&token);
    if (status != 0) {
        fprintf(stderr, "Failed to read %s.\n", name);
        return status;
    }

    status = parse_uintmax_token(token, &input);
    free(token);

    if (status != 0) {
        if (status == EOVERFLOW) {
            fprintf(stderr, "%s is too large.\n", name);
        } else {
            fprintf(stderr, "Invalid %s.\n", name);
        }
        return status;
    }

    if (input > SIZE_MAX) {
        fprintf(stderr, "%s is too large.\n", name);
        return EOVERFLOW;
    }

    *value = (size_t)input;
    return 0;
}

static int read_list(int64_t *list, size_t count, const char *name)
{
    if ((list == NULL && count != 0) || name == NULL) {
        return EINVAL;
    }

    for (size_t i = 0; i < count; ++i) {
        char *token = NULL;
        int status = read_token(&token);

        if (status == 0) {
            status = parse_int64_token(token, &list[i]);
        }

        free(token);

        if (status != 0) {
            fprintf(stderr,
                    "Failed to read %s element %zu.\n",
                    name,
                    i);
            return status;
        }
    }

    return 0;
}

int main(void)
{
    size_t first_count;
    size_t second_count;
    size_t requested_count;
    size_t product_count;
    int64_t *first = NULL;
    int64_t *second = NULL;
    int64_t *products = NULL;
    int status;

    status = read_size("first list size", &first_count);
    if (status != 0) {
        return EXIT_FAILURE;
    }

    status = read_size("second list size", &second_count);
    if (status != 0) {
        return EXIT_FAILURE;
    }

    status = read_size("number of products", &requested_count);
    if (status != 0) {
        return EXIT_FAILURE;
    }

    if (first_count > SIZE_MAX / sizeof(*first) ||
        second_count > SIZE_MAX / sizeof(*second)) {
        fprintf(stderr, "List size is too large.\n");
        return EXIT_FAILURE;
    }

    if (first_count != 0) {
        first = malloc(first_count * sizeof(*first));
        if (first == NULL) {
            fprintf(stderr, "Unable to allocate the first list.\n");
            return EXIT_FAILURE;
        }
    }

    if (second_count != 0) {
        second = malloc(second_count * sizeof(*second));
        if (second == NULL) {
            fprintf(stderr, "Unable to allocate the second list.\n");
            free(first);
            return EXIT_FAILURE;
        }
    }

    status = read_list(first, first_count, "first list");

    if (status == 0) {
        status = read_list(second, second_count, "second list");
    }

    if (status == 0) {
        status = find_largest_products(first,
                                       first_count,
                                       second,
                                       second_count,
                                       requested_count,
                                       &products,
                                       &product_count);
    }

    if (status != 0) {
        if (status == ENOMEM) {
            fprintf(stderr, "Unable to allocate working memory.\n");
        } else if (status == EOVERFLOW) {
            fprintf(stderr, "Input dimensions or values are too large.\n");
        } else if (status != EINVAL) {
            fprintf(stderr, "Unable to find the largest products.\n");
        }

        free(products);
        free(second);
        free(first);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < product_count; ++i) {
        if (printf("%" PRId64 "%c",
                   products[i],
                   i + 1U == product_count ? '\n' : ' ') < 0) {
            fprintf(stderr, "Failed to write output.\n");
            free(products);
            free(second);
            free(first);
            return EXIT_FAILURE;
        }
    }

    free(products);
    free(second);
    free(first);
    return EXIT_SUCCESS;
}