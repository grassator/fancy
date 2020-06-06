#ifndef STRUCT_TYPE_MODIFIERS_H
#define STRUCT_TYPE_MODIFIERS_H

#include "fancy.h"

#define Self Crazy_Field_Type_Modifiers
#define FIELDS(Self)\
  FIELD(CONST(PTR(PTR(TYPE(UNSIGNED(int))))), test)

#define TRAITS\
  TRAIT(Type_Info)

#include "fancy_struct.h"

#undef Self

#endif
