collected_code/heal_round_6/healed/problem-595.c: In function 'minSwaps':
collected_code/heal_round_6/healed/problem-595.c:19:30: error: 'INT_MAX' undeclared (first use in this function)
   19 |     int len1 = strnlen(str1, INT_MAX);
      |                              ^~~~~~~
collected_code/heal_round_6/healed/problem-595.c:4:1: note: 'INT_MAX' is defined in header '<limits.h>'; did you forget to '#include <limits.h>'?
    3 | #include <stdbool.h>
  +++ |+#include <limits.h>
    4 | 
collected_code/heal_round_6/healed/problem-595.c:19:30: note: each undeclared identifier is reported only once for each function it appears in
   19 |     int len1 = strnlen(str1, INT_MAX);
      |                              ^~~~~~~
