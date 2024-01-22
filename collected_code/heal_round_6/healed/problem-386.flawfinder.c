Flawfinder version 2.0.19, (C) 2001-2019 David A. Wheeler.
Number of rules (primarily dangerous function names) in C/C++ ruleset: 222
Examining collected_code/heal_round_6/healed/problem-386.c

FINAL RESULTS:

collected_code/heal_round_6/healed/problem-386.c:43:  [2] (buffer) char:
  Statically-sized arrays can be improperly restricted, leading to potential
  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use
  functions that limit length, or ensure that the size is larger than the
  maximum possible length.

ANALYSIS SUMMARY:

Hits = 1
Lines analyzed = 61 in approximately 0.00 seconds (15828 lines/second)
Physical Source Lines of Code (SLOC) = 48
Hits@level = [0]   3 [1]   0 [2]   1 [3]   0 [4]   0 [5]   0
Hits@level+ = [0+]   4 [1+]   1 [2+]   1 [3+]   0 [4+]   0 [5+]   0
Hits/KSLOC@level+ = [0+] 83.3333 [1+] 20.8333 [2+] 20.8333 [3+]   0 [4+]   0 [5+]   0
Minimum risk level = 1

Not every hit is necessarily a security vulnerability.
You can inhibit a report by adding a comment in this form:
// flawfinder: ignore
Make *sure* it's a false positive!
You can use the option --neverignore to show these.

There may be other security vulnerabilities; review your code!
See 'Secure Programming HOWTO'
(https://dwheeler.com/secure-programs) for more information.
