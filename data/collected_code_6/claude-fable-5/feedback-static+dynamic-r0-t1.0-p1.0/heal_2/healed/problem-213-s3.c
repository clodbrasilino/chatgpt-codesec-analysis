#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define TUPLE_SIZE 3
#define MAX_STRING_LEN 4096

typedef struct {
    char *items[TUPLE_SIZE];
} StringTuple;

static char *concat_strings(const char *a, const char *b)
{
    if (a == NULL || b == NULL) {
        return NULL;
    }

    size_t len_a = strnlen(a, MAX_STRING_LEN);
    size_t len_b = strnlen(b, MAX_STRING_LEN);

    if (len_a >= MAX_STRING_LEN || len_b >= MAX_STRING_LEN) {
        return NULL;
    }

    if (len_a > SIZE_MAX - len_b - 1u) {
        return NULL;
    }

    size_t total = len_a + len_b + 1u;
    char *result = malloc(total);
    if (result == NULL) {
        return NULL;
    }

    memcpy(result, a, len_a);
    memcpy(result + len_a, b, len_b);
    result[len_a + len_b] = '\0';

    return result;
}

static int concat_tuples(const StringTuple *t1, const StringTuple *t2, StringTuple *out)
{
    if (t1 == NULL || t2 == NULL || out == NULL) {
        return -1;
    }

    for (size_t i = 0; i < TUPLE_SIZE; i++) {
        out->items[i] = concat_strings(t1->items[i], t2->items[i]);
        if (out->items[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(out->items[j]);
                out->items[j] = NULL;
            }
            return -1;
        }
    }

    return 0;
}

static void free_tuple(StringTuple *t)
{
    if (t != NULL) {
        for (size_t i = 0; i < TUPLE_SIZE; i++) {
            free(t->items[i]);
            t->items[i] = NULL;
        }
    }
}

static int print_tuple(const StringTuple *t)
{
    if (t == NULL) {
        return -1;
    }

    if (printf("[") < 0) {
        return -1;
    }

    for (size_t i = 0; i < TUPLE_SIZE; i++) {
        if (t->items[i] == NULL) {
            return -1;
        }
        if (printf("'%s'", t->items[i]) < 0) {
            return -1;
        }
        if (i < TUPLE_SIZE - 1u) {
            if (printf(", ") < 0) {
                return -1;
            }
        }
    }

    if (printf("]\n") < 0) {
        return -1;
    }

    return 0;
}

static int run_test_case(const StringTuple *a, const StringTuple *b)
{
    StringTuple result;

    for (size_t i = 0; i < TUPLE_SIZE; i++) {
        result.items[i] = NULL;
    }

    if (concat_tuples(a, b, &result) != 0) {
        fprintf(stderr, "Error: tuple concatenation failed\n");
        return -1;
    }

    if (print_tuple(&result) != 0) {
        free_tuple(&result);
        return -1;
    }

    free_tuple(&result);
    return 0;
}

int main(void)
{
    StringTuple a0 = { { "Manjeet", "Nikhil", "Akshat" } };
    StringTuple b0 = { { " Singh", " Meherwal", " Garg" } };

    StringTuple a1 = { { "Shaik", "Ayesha", "Sanya" } };
    StringTuple b1 = { { " Dawood", " Begum", " Singh" } };

    StringTuple a2 = { { "Harpreet", "Priyanka", "Muskan" } };
    StringTuple b2 = { { "Kour", " Agarwal", "Sethi" } };

    if (run_test_case(&a0, &b0) != 0) {
        return EXIT_FAILURE;
    }

    if (run_test_case(&a1, &b1) != 0) {
        return EXIT_FAILURE;
    }

    if (run_test_case(&a2, &b2) != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}