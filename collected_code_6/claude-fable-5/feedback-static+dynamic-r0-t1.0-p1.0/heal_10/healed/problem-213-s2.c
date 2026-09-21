#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define TUPLE_SIZE 3
#define MAX_ITEM_LEN 4096

typedef struct {
    char *items[TUPLE_SIZE];
} StringTuple;

static size_t bounded_strlen(const char *s, size_t max_len)
{
    size_t len = 0U;

    while (len < max_len && s[len] != '\0') {
        len++;
    }

    return len;
}

static char *concat_strings(const char *a, const char *b)
{
    if (a == NULL || b == NULL) {
        return NULL;
    }

    size_t len_a = bounded_strlen(a, MAX_ITEM_LEN);
    size_t len_b = bounded_strlen(b, MAX_ITEM_LEN);

    if (len_a >= MAX_ITEM_LEN || len_b >= MAX_ITEM_LEN) {
        return NULL;
    }

    if (len_a > SIZE_MAX - 1U - len_b) {
        return NULL;
    }

    size_t total = len_a + len_b + 1U;

    char *result = malloc(total);
    if (result == NULL) {
        return NULL;
    }

    if (len_a > 0U) {
        memcpy(result, a, len_a);
    }
    if (len_b > 0U) {
        memcpy(result + len_a, b, len_b);
    }
    result[len_a + len_b] = '\0';

    return result;
}

static int concat_tuples(const StringTuple *t1, const StringTuple *t2, StringTuple *out)
{
    if (t1 == NULL || t2 == NULL || out == NULL) {
        return -1;
    }

    for (size_t i = 0; i < TUPLE_SIZE; i++) {
        out->items[i] = NULL;
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

    if (fputs("[", stdout) == EOF) {
        return -1;
    }

    for (size_t i = 0; i < TUPLE_SIZE; i++) {
        if (t->items[i] == NULL) {
            return -1;
        }
        if (printf("'%s'", t->items[i]) < 0) {
            return -1;
        }
        if (i + 1U < TUPLE_SIZE) {
            if (fputs(", ", stdout) == EOF) {
                return -1;
            }
        }
    }

    if (fputs("]\n", stdout) == EOF) {
        return -1;
    }

    if (fflush(stdout) != 0) {
        return -1;
    }

    return 0;
}

static int run_case(const char *a0, const char *a1, const char *a2,
                    const char *b0, const char *b1, const char *b2)
{
    StringTuple t1;
    StringTuple t2;
    StringTuple result;

    t1.items[0] = (char *)a0;
    t1.items[1] = (char *)a1;
    t1.items[2] = (char *)a2;

    t2.items[0] = (char *)b0;
    t2.items[1] = (char *)b1;
    t2.items[2] = (char *)b2;

    if (concat_tuples(&t1, &t2, &result) != 0) {
        fprintf(stderr, "Tuple concatenation failed\n");
        return -1;
    }

    int status = print_tuple(&result);
    free_tuple(&result);

    return status;
}

int main(void)
{
    if (run_case("Manjeet", "Nikhil", "Akshat",
                 " Singh", " Meherwal", " Garg") != 0) {
        return EXIT_FAILURE;
    }

    if (run_case("Shaik", "Ayesha", "Sanya",
                 " Dawood", " Begum", " Singh") != 0) {
        return EXIT_FAILURE;
    }

    if (run_case("Harpreet", "Priyanka", "Muskan",
                 "Kour", " Agarwal", "Sethi") != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}