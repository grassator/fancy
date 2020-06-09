# fancy

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

`fancy` is an experiment in supporting reflection and traits (Go-style interfaces) in pure C. For example we would want a `print` function that would have type signature similar to this:

```C
void print(To_String something);
```

Of course you could write something like this manually in C:

```C
typedef const char *(*to_string_fn)(void *);
typedef struct {
    void *object;
    to_string_fn to_string;
} To_String;

typedef struct {
    const char *foo;
} Foo;

const char *Foo__to_string(Foo *foo) { return foo; }

int main(void) {
    Foo foo = {"Hello, World!"};
    To_String sts = {&foo, Foo__to_string};
    print(sts);
}
```

It works, but requires you to remember and type every time the mapping between `Foo` type and `Foo__to_string` function, in which case just calling `Foo__to_string` is more convenient.

The main contribution of `fancy` is to provide this mapping from an instance of a type to some arbitrary function associated with a struct at compile time and no inflating the size of the original struct (with a couple of exceptions).

To achieve this `fancy` completely changes the syntax for header files through macros, so code above would look something like this:

```C
#define Self Foo ////////////////////////////////////////

#define FIELDS(Self)\
    FIELD(TYPE(C_String), foo)

#define TRAITS\
    TRAIT(To_String)

#include "fancy_struct.h"

C_String IMPL(To_String, to_string)(const Self *self) {
  return self->name;
}

#undef Self ///////////////////////////////////////////

int main(void) {
    Foo foo = {"Hello, World!"};
    print(&foo);
}
```

The definition of a struct looks quite alien and verbose at first, but in its minimal form without the traits it only requires `FIELDS` definition and still provides a significant benefit of giving compile-time reflection:

```C
int main(void) {
    Foo foo = {"Hello, World!"};
    print(type_info(&foo)->name); // prints "Foo"
}
```

## Requirements

Currently the code has been tested only with MSVC compiler in C mode, but the target is to also suport GCC and Clang.

Technically code requires C11, but both advanced features (anonymous structs and `__VA_ARGS__` macro) are available in many compilers for a long time. It is also possible to make a version of the code that will use neither of the features, but would be more awkward to use.

## How Does It Work?



## License

The MIT License (MIT)

Copyright (c) 2020 Dmitriy Kubyshkin

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

