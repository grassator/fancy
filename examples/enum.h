#ifndef EXAMPLE_ENUM_H
#define EXAMPLE_ENUM_H
#include "fancy.h"

#define Self Example_Enum
  #define FANCY_ENUM\
    ENUMERATE(One)\
    ENUMERATE(Two)\
    ENUMERATE(Three)

  #include "fancy_enum.h"
#undef Self

//////////////////////////////////////////////////////////////////////////////

#define Self Using_Enum_Field

#define FIELDS(Self)\
  FIELD(TYPE(Example_Enum), enum_field)

#define TRAITS\
  TRAIT(Type_Info)

#include "fancy_struct.h"
#undef Self

#endif