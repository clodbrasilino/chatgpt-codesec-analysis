# Problem-level channel contribution across all LLMs

Unit: BCT problem (974 tasks). A problem counts for a set if ANY
model, ANY of its 3 samples, on ANY version within rounds 0-5
produced >=1 injectable finding. Main cells, non-thinking.

Problems total: 974

## Channel-level (Venn 1): static / tests / dynamic(excl. tests)
static any: 961
tests: 248
dynamic (oracle+fuzzer): 226

  none                                          10
  Static                                        583
  Tests                                         2
  Static+Tests                                  153
  Dynamic                                       1
  Static+Dynamic                                132
  Tests+Dynamic                                 0
  Static+Tests+Dynamic                          93

## Static tools (Venn 2)
  none                                          13
  gcc                                           0
  clang                                         0
  gcc+clang                                     2
  cppcheck                                      151
  gcc+cppcheck                                  0
  clang+cppcheck                                12
  gcc+clang+cppcheck                            82
  flawfinder                                    6
  gcc+flawfinder                                0
  clang+flawfinder                              0
  gcc+clang+flawfinder                          2
  cppcheck+flawfinder                           197
  gcc+cppcheck+flawfinder                       8
  clang+cppcheck+flawfinder                     56
  gcc+clang+cppcheck+flawfinder                 445

## Dynamic tools (Venn 3): ASan / UBSan / AFL++
  none                                          748
  ASan                                          5
  UBSan                                         8
  ASan+UBSan                                    1
  AFL++                                         198
  ASan+AFL++                                    1
  UBSan+AFL++                                   13
  ASan+UBSan+AFL++                              0
