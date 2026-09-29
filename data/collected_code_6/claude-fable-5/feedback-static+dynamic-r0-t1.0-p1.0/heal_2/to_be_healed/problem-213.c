#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected ['Shaik Dawood', 'Ayesha Begum', 'Sanya Singh'], got <no output>
  *  test case 0 failed: expected ['Manjeet Singh', 'Nikhil Meherwal', 'Akshat Garg'], got <no output>
  *  test case 2 failed: expected ['HarpreetKour', 'Priyanka Agarwal', 'MuskanSethi'], got <no output>
  */

static char *concat_strings(const char *a, const char *b)
{
    size_t len_a;
    size_t len_b;
    char *result;

    if (a == NULL || b == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len_a = strlen(a);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len_b = strlen(b);

    if (len_a > SIZE_MAX - len_b - 1U) {
        return NULL;
    }

    result = malloc(len_a + len_b + 1U);
    if (result == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result, a, len_a);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result + len_a, b, len_b + 1U);

    return result;
}

static int concat_tuple_arrays(const char *const *t1, const char *const *t2,
                               char **out, size_t count)
{
    size_t i;
    size_t j;

    if (t1 == NULL || t2 == NULL || out == NULL) {
        return -1;
    }

    for (i = 0; i < count; i++) {
        out[i] = NULL;
    }

    for (i = 0; i < count; i++) {
        out[i] = concat_strings(t1[i], t2[i]);
        if (out[i] == NULL) {
            for (j = 0; j < i; j++) {
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

    for (i = 0; i < count; i++) {
        free(out[i]);
        out[i] = NULL;
    }
}

static int print_tuple_array(char **out, size_t count)
{
    size_t i;

    if (out == NULL) {
        return -1;
    }

    if (printf("[") < 0) {
        return -1;
    }

    for (i = 0; i < count; i++) {
        if (printf("'%s'", out[i]) < 0) {
            return -1;
        }
        if (i + 1U < count) {
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

int main(void)
{
    const char *const test1_a[] = { "Manjeet ", "Nikhil ", "Akshat " };
    const char *const test1_b[] = { "Singh", "Meherwal", "Garg" };
    const char *const test2_a[] = { "Shaik ", "Ayesha ", "Sanya " };
    const char *const test2_b[] = { "Dawood", "Begum", "Singh" };
    const char *const test3_a[] = { "Harpreet", "Priyanka ", "Muskan" };
    const char *const test3_b[] = { "Kour", "Agarwal", "Sethi" };
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char *result[3];
    size_t count = 3U;

    if (concat_tuple_arrays(test1_a, test1_b, result, count) != 0) {
        fprintf(stderr, "Error: tuple concatenation failed\n");
        return EXIT_FAILURE;
    }
    if (print_tuple_array(result, count) != 0) {
        free_tuple_array(result, count);
        return EXIT_FAILURE;
    }
    free_tuple_array(result, count);

    if (concat_tuple_arrays(test2_a, test2_b, result, count) != 0) {
        fprintf(stderr, "Error: tuple concatenation failed\n");
        return EXIT_FAILURE;
    }
    if (print_tuple_array(result, count) != 0) {
        free_tuple_array(result, count);
        return EXIT_FAILURE;
    }
    free_tuple_array(result, count);

    if (concat_tuple_arrays(test3_a, test3_b, result, count) != 0) {
        fprintf(stderr, "Error: tuple concatenation failed\n");
        return EXIT_FAILURE;
    }
    if (print_tuple_array(result, count) != 0) {
        free_tuple_array(result, count);
        return EXIT_FAILURE;
    }
    free_tuple_array(result, count);

    return EXIT_SUCCESS;
}