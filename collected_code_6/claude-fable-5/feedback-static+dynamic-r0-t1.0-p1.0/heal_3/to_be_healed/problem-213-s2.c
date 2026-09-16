#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TUPLE_SIZE 3

typedef struct {
    char *items[TUPLE_SIZE];
} StringTuple;
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['HarpreetKour', 'Priyanka Agarwal', 'MuskanSethi'], got <no output>
  *  test case 1 failed: expected ['Shaik Dawood', 'Ayesha Begum', 'Sanya Singh'], got <no output>
  *  test case 0 failed: expected ['Manjeet Singh', 'Nikhil Meherwal', 'Akshat Garg'], got <no output>
  */

static char *concat_strings(const char *a, const char *b)
{
    size_t len_a;
    size_t len_b;
    char *result;

    if (a == NULL || b == NULL) {
        return NULL;
    }

    len_a = strlen(a);
    len_b = strlen(b);

    result = malloc(len_a + len_b + 1U);
    if (result == NULL) {
        return NULL;
    }

    memcpy(result, a, len_a);
    memcpy(result + len_a, b, len_b + 1U);

    return result;
}

static void free_tuple(StringTuple *t)
{
    int i;

    if (t == NULL) {
        return;
    }

    for (i = 0; i < TUPLE_SIZE; i++) {
        free(t->items[i]);
        t->items[i] = NULL;
    }
}

static int concat_tuples(const StringTuple *t1, const StringTuple *t2, StringTuple *out)
{
    int i;

    if (t1 == NULL || t2 == NULL || out == NULL) {
        return -1;
    }

    for (i = 0; i < TUPLE_SIZE; i++) {
        out->items[i] = NULL;
    }

    for (i = 0; i < TUPLE_SIZE; i++) {
        out->items[i] = concat_strings(t1->items[i], t2->items[i]);
        if (out->items[i] == NULL) {
            free_tuple(out);
            return -1;
        }
    }

    return 0;
}

static int print_tuple(const StringTuple *t)
{
    int i;

    if (t == NULL) {
        return -1;
    }

    if (printf("[") < 0) {
        return -1;
    }

    for (i = 0; i < TUPLE_SIZE; i++) {
        if (t->items[i] == NULL) {
            return -1;
        }
        if (printf("'%s'", t->items[i]) < 0) {
            return -1;
        }
        if (i < TUPLE_SIZE - 1) {
            if (printf(", ") < 0) {
                return -1;
            }
        }
    }

    if (printf("]\n") < 0) {
        return -1;
    }

    if (fflush(stdout) != 0) {
        return -1;
    }

    return 0;
}

static int run_test(const char *first[TUPLE_SIZE], const char *second[TUPLE_SIZE])
{
    StringTuple t1;
    StringTuple t2;
    StringTuple result;
    int i;

    if (first == NULL || second == NULL) {
        return -1;
    }

    for (i = 0; i < TUPLE_SIZE; i++) {
        if (first[i] == NULL || second[i] == NULL) {
            return -1;
        }
        t1.items[i] = (char *)first[i];
        t2.items[i] = (char *)second[i];
    }

    if (concat_tuples(&t1, &t2, &result) != 0) {
        fprintf(stderr, "Tuple concatenation failed\n");
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
    const char *test0_a[TUPLE_SIZE] = { "Manjeet", "Nikhil", "Akshat" };
    const char *test0_b[TUPLE_SIZE] = { " Singh", " Meherwal", " Garg" };

    const char *test1_a[TUPLE_SIZE] = { "Shaik", "Ayesha", "Sanya" };
    const char *test1_b[TUPLE_SIZE] = { " Dawood", " Begum", " Singh" };

    const char *test2_a[TUPLE_SIZE] = { "Harpreet", "Priyanka", "Muskan" };
    const char *test2_b[TUPLE_SIZE] = { "Kour", " Agarwal", "Sethi" };

    setvbuf(stdout, NULL, _IONBF, 0);

    if (run_test(test0_a, test0_b) != 0) {
        return EXIT_FAILURE;
    }

    if (run_test(test1_a, test1_b) != 0) {
        return EXIT_FAILURE;
    }

    if (run_test(test2_a, test2_b) != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}