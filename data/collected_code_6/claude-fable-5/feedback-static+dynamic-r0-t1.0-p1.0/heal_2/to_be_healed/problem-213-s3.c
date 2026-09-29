#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define TUPLE_SIZE 3

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char *items[TUPLE_SIZE];
} StringTuple;
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

    if (len_a > SIZE_MAX - len_b - 1u) {
        return NULL;
    }

    result = malloc(len_a + len_b + 1u);
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
    memcpy(result + len_a, b, len_b + 1u);

    return result;
}

static int concat_tuples(const StringTuple *t1, const StringTuple *t2, StringTuple *out)
{
    size_t i;
    size_t j;

    if (t1 == NULL || t2 == NULL || out == NULL) {
        return -1;
    }

    for (i = 0; i < TUPLE_SIZE; i++) {
        out->items[i] = concat_strings(t1->items[i], t2->items[i]);
        if (out->items[i] == NULL) {
            for (j = 0; j < i; j++) {
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
    /* Possible weaknesses found:
     *  The scope of the variable 'i' can be reduced. [variableScope]
     */
    size_t i;

    if (t != NULL) {
        for (i = 0; i < TUPLE_SIZE; i++) {
            free(t->items[i]);
            t->items[i] = NULL;
        }
    }
}

static int print_tuple(const StringTuple *t)
{
    size_t i;

    if (t == NULL) {
        return -1;
    }

    if (printf("[") < 0) {
        return -1;
    }

    for (i = 0; i < TUPLE_SIZE; i++) {
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

int main(void)
{
    StringTuple a;
    StringTuple b;
    StringTuple result;
    size_t i;

    a.items[0] = "Manjeet";
    a.items[1] = "Nikhil";
    a.items[2] = "Akshat";

    b.items[0] = " Singh";
    b.items[1] = " Meherwal";
    b.items[2] = " Garg";

    for (i = 0; i < TUPLE_SIZE; i++) {
        result.items[i] = NULL;
    }

    if (concat_tuples(&a, &b, &result) != 0) {
        fprintf(stderr, "Error: tuple concatenation failed\n");
        return EXIT_FAILURE;
    }

    if (print_tuple(&result) != 0) {
        free_tuple(&result);
        return EXIT_FAILURE;
    }

    free_tuple(&result);

    return EXIT_SUCCESS;
}