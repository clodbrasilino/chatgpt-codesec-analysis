Flawfinder version 2.0.19, (C) 2001-2019 David A. Wheeler.
Number of rules (primarily dangerous function names) in C/C++ ruleset: 222
Examining collected_code/heal_round_7/healed/problem-812.c

FINAL RESULTS:

collected_code/heal_round_7/healed/problem-812.c:11:  [2] (buffer) char:
  Statically-sized arrays can be improperly restricted, leading to potential
  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use
  functions that limit length, or ensure that the size is larger than the
  maximum possible length.
collected_code/heal_round_7/healed/problem-812.c:12:  [2] (buffer) memcpy:
  Does not check for buffer overflows when copying to destination (CWE-120).
  Make sure destination can always hold the source data.
collected_code/heal_round_7/healed/problem-812.c:22:  [2] (buffer) memcpy:
  Does not check for buffer overflows when copying to destination (CWE-120).
  Make sure destination can always hold the source data.

ANALYSIS SUMMARY:

Hits = 3
Lines analyzed = 43 in approximately 0.00 seconds (11367 lines/second)
Physical Source Lines of Code (SLOC) = 34
Hits@level = [0]   3 [1]   0 [2]   3 [3]   0 [4]   0 [5]   0
Hits@level+ = [0+]   6 [1+]   3 [2+]   3 [3+]   0 [4+]   0 [5+]   0
Hits/KSLOC@level+ = [0+] 176.471 [1+] 88.2353 [2+] 88.2353 [3+]   0 [4+]   0 [5+]   0
Minimum risk level = 1

Not every hit is necessarily a security vulnerability.
You can inhibit a report by adding a comment in this form:
// flawfinder: ignore
Make *sure* it's a false positive!
You can use the option --neverignore to show these.

There may be other security vulnerabilities; review your code!
See 'Secure Programming HOWTO'
(https://dwheeler.com/secure-programs) for more information.
