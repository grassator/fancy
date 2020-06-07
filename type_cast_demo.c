#include "fancy.h"
#include <stdint.h>
#include <stdio.h>

inline int *foo(void) {
    static int result = 2;
    return &result;
}
inline int *bar(void) {
    static int result = 4;
    return &result;
}

struct Foo { int *(*fn)(void); };
struct Bar  { int *(*fn)(void); };

const struct Foo foo_wrap = {foo};
const struct Bar bar_wrap = {bar};

int main(void) {
  printf("pointer: %llx\n", (uint64_t) (&bar_wrap));
  printf("reified: %llx\n", (uint64_t) fancy_cast_pointer_value(&bar_wrap, &foo_wrap));
  int *result = fancy_cast_pointer_value(&bar_wrap, &foo_wrap)->fn();
  printf("expected 4, got %d", result);
  return o;
}
