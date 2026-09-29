#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STR_LEN 4096U
#define TUPLE_COUNT 3U

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
    size_t len_a;
    size_t len_b;
    size_t total;
    char *result;

    if (a == NULL || b == NULL) {
        return NULL;
    }

    len_a = bounded_strlen(a, MAX_STR_LEN);
    len_b = bounded_strlen(b, MAX_STR_LEN);

    if (len_a >= MAX_STR_LEN || len_b >= MAX_STR_LEN) {
        return NULL;
    }

    if (len_a > SIZE_MAX - len_b) {
        return NULL;
    }

    if ((len_a + len_b) > SIZE_MAX - 1U) {
        return NULL;
    }

    total = len_a + len_b + 1U;

    result = (char *)malloc(total);
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

static int concat_tuple_arrays(const char *const *t1, const char *const *t2,
                               char **out, size_t count)
{
    size_t i;
    size_t j;

    if (t1 == NULL || t2 == NULL || out == NULL || count == 0U) {
        return -1;
    }

    for (i = 0U; i < count; i++) {
        out[i] = NULL;
    }

    for (i = 0U; i < count; i++) {
        out[i] = concat_strings(t1[i], t2[i]);
        if (out[i] == NULL) {
            for (j = 0U; j < i; j++) {
                free(out[j]);
                out[j] = NULL;
            }
            return -1;
        }
    }

    return 0;
}

static void free_tuple_array(char **out, size_t count)
{
    size_t i;

    if (out == NULL) {
        return;
    }

    for (i = 0U; i < count; i++) {
        free(out[i]);
        out[i] = NULL;
    }
}

static int print_tuple_array(char **out, size_t count)
{
    size_t i;

    if (out == NULL || count == 0U) {
        return -1;
    }

    if (fputs("[", stdout) == EOF) {
        return -1;
    }

    for (i = 0U; i < count; i++) {
        if (out[i] == NULL) {
            return -1;
        }
        if (printf("'%s'", out[i]) < 0) {
            return -1;
        }
        if (i + 1U < count) {
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

static int run_test(const char *const *a, const char *const *b,
                    char **result, size_t count)
{
    int status;

    if (a == NULL || b == NULL || result == NULL || count == 0U) {
        return -1;
    }

    if (concat_tuple_arrays(a, b, result, count) != 0) {
        if (fprintf(stderr, "Error: tuple concatenation failed\n") < 0) {
            return -1;
        }
        return -1;
    }

    status = print_tuple_array(result, count);
    free_tuple_array(result, count);

    if (status != 0) {
        return -1;
    }

    return 0;
}

int main(void)
{
    const char *const test1_a[TUPLE_COUNT] = { "Manjeet ", "Nikhil ", "Akshat " };
    const char *const test1_b[TUPLE_COUNT] = { "Singh", "Meherwal", "Garg" };
    const char *const test2_a[TUPLE_COUNT] = { "Shaik ", "Ayesha ", "Sanya " };
    const char *const test2_b[TUPLE_COUNT] = { "Dawood", "Begum", "Singh" };
    const char *const test3_a[TUPLE_COUNT] = { "Harpreet", "Priyanka ", "Muskan" };
    const char *const test3_b[TUPLE_COUNT] = { "Kour", "Agarwal", "Sethi" };
    char *result[TUPLE_COUNT] = { NULL, NULL, NULL };
    size_t count = sizeof(result) / sizeof(result[0]);

    if (run_test(test1_a, test1_b, result, count) != 0) {
        return EXIT_FAILURE;
    }
    if (run_test(test2_a, test2_b, result, count) != 0) {
        return EXIT_FAILURE;
    }
    if (run_test(test3_a, test3_b, result, count) != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}