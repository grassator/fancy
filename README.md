# fancy

> WARNING: The library is currently in the proof of concept stage and is not ready for public use.

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

`fancy` is an experiment in supporting reflection and traits (Go-style interfaces) in pure C. For example we would want a `print` function that would have type signature similar to this:

```C
void print(Printable something);
```

Of course you could write something like this manually in C:

```C
typedef void(*print_fn)(void *);
typedef struct {
    void *object;
    print_fn to_string;
} Printable;

typedef struct {
    const char *foo;
} Foo;

const char *Foo__print(Foo *foo) { return foo; }

int main(void) {
    Foo foo = {"Hello, World!"};
    Printable sts = {&foo, Foo__print};
    print(sts);
}
```

It works, but requires you to remember and type every time the mapping between `Foo` type and `Foo__print` function, in which case just calling `Foo__print` is more convenient.

The main contribution of `fancy` is to provide this mapping from an instance of a type to some arbitrary function associated with a struct at compile time and no inflating the size of the original struct (with a couple of exceptions).

To achieve this `fancy` completely changes the syntax for header files through macros, so code above would look something like this:

```C
#define TRAIT_FUNCTIONS(Self)\
  TRAIT_FUNCTION(void, print, Self, const Self *)

#define print(self) fancy_invoke(Printable, print, self)

// Trait needs to have a list of all implementations
#define TRAIT_IMPLEMENTATIONS\
  IMPLEMENTATION(Foo)

#define Self Printable
#include "fancy_trait.h"
#undef Self

// struct Foo
#define Self Foo

#define FIELDS(Self)\
    FIELD(CONST(PTR(TYPE(char))), foo)

// Struct needs to list all the traits it implements
#define TRAITS\
    TRAIT(Printable)

#include "fancy_struct.h"

void IMPL(Printable, print)(const Self *self) {
  printf("%s", self->foo);
}

int main(void) {
    Foo foo = {"Hello, World!"};
    print(&foo);
}
```

The definition of a struct looks quite alien and verbose at first, but in its minimal form without the traits it only requires `FIELDS` definition and still provides a significant benefit of giving compile-time reflection:

```C
int main(void) {
    Foo foo = {"Hello, World!"};
    printf("%s", type_info(&foo)->name); // prints "Foo"
}
```

## Requirements

Currently the code has been tested only with MSVC compiler in C mode, but the target is to also suport GCC and Clang.

Technically code requires C11, but both advanced features (anonymous structs and `__VA_ARGS__` macro) are available in many compilers for a long time. It is also possible to make a version of the code that will use neither of the features, but would be more awkward to use.

## How Does It Work?

To make such static overloaded dispatch to work in any language / system one needs to have several ingredients:

* Statically known *id* associated with every type
* Ability to resolve from an *instance* to that *id*
* Have a statically defined *dispatch table* from an *id* to the right function implementation.

To generate the *id* `fancy` uses an enum that lists all the types that should implement a given trait using a well known technique of [X macro](https://www.drdobbs.com/the-new-c-x-macros/184401387).

The static *dispatch table* is also pretty straighforward to implement as a global const array of function pointers with indexes corresponding to the enum described above.

The tricky part and the one that supposed to be impossible in C without runtime overhead is to somehow get the *id* of the type from an instance. There is however one operator in C that can accept and dynamic expression and provide a static value - `sizeof`.

To make use of `sizeof` on a struct, the struct itself is changed into a union of an anonymous struct with the original field and an extra struct with fields that are pointers to the array of size corresponding to the `id` that is accessible through the enum. Once that is in place another known `countof()` macro trick can be used to turn the array size (which is `id`) into a compile time integer that we can use to index the `dispatch table`.

Here's the minimal code:

```C
#include <stdint.h>
#include <stdio.h>

// Commonly used macro to get the size of the static array
#define countof(_array_)\
  (sizeof(_array_) / sizeof(_array_[0]))

typedef void(*print_fn)(const void *);

enum {
    Print__Dispatcher_DUMMY,
    Print__Dispatcher__Foo,
    Print__Dispatcher__Bar,
};

typedef union {
    struct { const char *foo_field; };
    struct {
        print_fn print[Print__Dispatcher__Foo];
    } *dispatcher;
} Foo;
inline void Foo__print(const Foo *foo) { puts(foo->foo_field); }

typedef union {
    struct { const char *bar_field; };
    struct {
        print_fn print[Print__Dispatcher__Bar];
    } *dispatcher;
} Bar;
inline void Bar__print(const Bar *bar) { puts(bar->bar_field); }

const print_fn print__dispatcher[] = {
    0, // DUMMY
    [Print__Dispatcher__Foo] = (print_fn) Foo__print,
    [Print__Dispatcher__Bar] = (print_fn) Bar__print,
};

int main(void) {
    Foo foo = {"foo_field_value"};
    print__dispatcher[
        countof((&foo)->dispatcher->print)
    ](&foo);
    
    Bar bar = {"bar_field_value"};
    print__dispatcher[
        countof((&foo)->dispatcher->print)
    ](&bar);
}
```

> One important side effect of this approach is that any struct that uses this approach is inflated to be at least the size of the pointer (`void *`) on your target platform.


## Performance

Full performance evaluation is still to be done, however cursory look at the generated assembly from optimized builds is the same as with any other non-inlined function call. GCC and CLang are also able to inline overloaded functions if they are explicitly marked as such.

## License

The MIT License (MIT)

Copyright (c) 2020 Dmitriy Kubyshkin

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

