In file included from /usr/local/Cellar/gcc/13.1.0/lib/gcc/current/gcc/x86_64-apple-darwin22/13/include-fixed/stdio.h:440,
                 from collected_code/heal_round_6/healed/problem-500.c:1:
collected_code/heal_round_6/healed/problem-500.c: In function 'concatenateList':
collected_code/heal_round_6/healed/problem-500.c:47:27: warning: implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
   47 |         snprintf(result + strlen(result), length, "%d", current->data);
      |                           ^~~~~~
collected_code/heal_round_6/healed/problem-500.c:3:1: note: include '<string.h>' or provide a declaration of 'strlen'
    2 | #include <stdlib.h>
  +++ |+#include <string.h>
    3 | 
collected_code/heal_round_6/healed/problem-500.c:47:27: warning: incompatible implicit declaration of built-in function 'strlen' [-Wbuiltin-declaration-mismatch]
   47 |         snprintf(result + strlen(result), length, "%d", current->data);
      |                           ^~~~~~
collected_code/heal_round_6/healed/problem-500.c:47:27: note: include '<string.h>' or provide a declaration of 'strlen'
-macosx_version_min has been renamed to -macos_version_min
