#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char *abbreviate_road(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t len = strlen(input);
    char *result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t i = 0, j = 0;
    while (i < len) {
        if (i + 3 < len && 
            tolower(input[i]) == 'r' && 
            tolower(input[i+1]) == 'o' && 
            tolower(input[i+2]) == 'a' && 
            tolower(input[i+3]) == 'd') {
            result[j++] = 'r';
            result[j++] = 'd';
            result[j++] = '.';
            i += 4;
        } else {
            result[j++] = input[i++];
        }
    }
    result[j] = '\0';
    return result;
}

int main(void) {
    /* Possible weaknesses found:
     *  Assignment 'test1="123 Main Road"', assigned value is "123 Main Road"
     */
    const char *test1 = "123 Main Road";
    /* Possible weaknesses found:
     *  Assignment 'test2="Road to nowhere"', assigned value is "Road to nowhere"
     */
    const char *test2 = "Road to nowhere";
    /* Possible weaknesses found:
     *  Assignment 'test3="Broadway"', assigned value is "Broadway"
     */
    const char *test3 = "Broadway";
    /* Possible weaknesses found:
     *  Assignment 'test4="road"', assigned value is "road"
     */
    const char *test4 = "road";
    /* Possible weaknesses found:
     *  Assignment 'test5="ROAD"', assigned value is "ROAD"
     */
    const char *test5 = "ROAD";
    /* Possible weaknesses found:
     *  Assignment 'test6="Rd."', assigned value is "Rd."
     */
    const char *test6 = "Rd.";
    /* Possible weaknesses found:
     *  Assignment 'test7=NULL', assigned value is 0
     */
    const char *test7 = NULL;

    char *result1 = abbreviate_road(test1);
    char *result2 = abbreviate_road(test2);
    char *result3 = abbreviate_road(test3);
    char *result4 = abbreviate_road(test4);
    char *result5 = abbreviate_road(test5);
    char *result6 = abbreviate_road(test6);
    /* Possible weaknesses found:
     *  Calling function 'abbreviate_road' returns 0
     *  Assignment 'result7=abbreviate_road(test7)', assigned value is 0
     */
    char *result7 = abbreviate_road(test7);

    /* Possible weaknesses found:
     *  Condition 'test1!=NULL' is always true [knownConditionTrueFalse]
     *  Condition 'test1!=NULL' is always true
     */
    if (test1 != NULL) {
        printf("%s -> %s\n", test1, result1 ? result1 : "(null)");
    } else {
        printf("(null) -> %s\n", result1 ? result1 : "(null)");
    }
    /* Possible weaknesses found:
     *  Condition 'test2!=NULL' is always true
     *  Condition 'test2!=NULL' is always true [knownConditionTrueFalse]
     */
    if (test2 != NULL) {
        printf("%s -> %s\n", test2, result2 ? result2 : "(null)");
    } else {
        printf("(null) -> %s\n", result2 ? result2 : "(null)");
    }
    /* Possible weaknesses found:
     *  Condition 'test3!=NULL' is always true [knownConditionTrueFalse]
     *  Condition 'test3!=NULL' is always true
     */
    if (test3 != NULL) {
        printf("%s -> %s\n", test3, result3 ? result3 : "(null)");
    } else {
        printf("(null) -> %s\n", result3 ? result3 : "(null)");
    }
    /* Possible weaknesses found:
     *  Condition 'test4!=NULL' is always true
     *  Condition 'test4!=NULL' is always true [knownConditionTrueFalse]
     */
    if (test4 != NULL) {
        printf("%s -> %s\n", test4, result4 ? result4 : "(null)");
    } else {
        printf("(null) -> %s\n", result4 ? result4 : "(null)");
    }
    /* Possible weaknesses found:
     *  Condition 'test5!=NULL' is always true
     *  Condition 'test5!=NULL' is always true [knownConditionTrueFalse]
     */
    if (test5 != NULL) {
        printf("%s -> %s\n", test5, result5 ? result5 : "(null)");
    } else {
        printf("(null) -> %s\n", result5 ? result5 : "(null)");
    }
    /* Possible weaknesses found:
     *  Condition 'test6!=NULL' is always true [knownConditionTrueFalse]
     *  Condition 'test6!=NULL' is always true
     */
    if (test6 != NULL) {
        printf("%s -> %s\n", test6, result6 ? result6 : "(null)");
    } else {
        printf("(null) -> %s\n", result6 ? result6 : "(null)");
    }
    /* Possible weaknesses found:
     *  Condition 'test7!=NULL' is always false
     *  Condition 'test7!=NULL' is always false [knownConditionTrueFalse]
     */
    if (test7 != NULL) {
        printf("%s -> %s\n", test7, result7 ? result7 : "(null)");
    } else {
        /* Possible weaknesses found:
         *  Condition 'result7' is always false [knownConditionTrueFalse]
         *  Condition 'result7' is always false
         */
        printf("(null) -> %s\n", result7 ? result7 : "(null)");
    }

    free(result1);
    free(result2);
    free(result3);
    free(result4);
    free(result5);
    free(result6);
    free(result7);

    return 0;
}