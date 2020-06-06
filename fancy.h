#ifndef FANCY_H
#define FANCY_H

#ifndef MACRO_DEBUG
#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#endif

// Common things for all traits

#define MSVC_MACRO_EXPAND(...) __VA_ARGS__

/////////////////////////////////////////////////////////////////////////////////////////////////
// Trait Functions Macros
/////////////////////////////////////////////////////////////////////////////////////////////////
#define TRAIT_FN_ARG0(_return_, _name_, _type_)\
  _return_ CONCAT(TRAIT_NAME, __##_type_##__##_name_)\
  (_type_ *self) {\
    return self->trait->##_name_##_ (self->value); \
  }
#define TRAIT_FN_ARG1(_return_, _name_, _type_, N1)\
  _return_ CONCAT(TRAIT_NAME, __##_type_##__##_name_)\
  (_type_ *self, N1 _1) {\
    return self->trait->##_name_##_ (self->value, _1); \
  }
#define TRAIT_FN_ARG2(_return_, _name_, _type_, N1, N2)\
  _return_ CONCAT(TRAIT_NAME, __##_type_##__##_name_)\
  (_type_ *self, N1 _1, N2 _2) {\
    return self->trait->##_name_##_ (self->value, _1, _2); \
  }
#define TRAIT_FN_ARG3(_return_, _name_, _type_, N1, N2, N3)\
  _return_ CONCAT(TRAIT_NAME, __##_type_##__##_name_)\
  (_type_ *self, N1 _1, N2 _2, N3 _3) {\
    return self->trait->##_name_##_ (self->value, _1, _2, _3); \
  }
#define TRAIT_FN_ARG4(_return_, _name_, _type_, N1, N2, N3, N4)\
  _return_ CONCAT(TRAIT_NAME, __##_type_##__##_name_)\
  (_type_ *self, N1 _1, N2 _2, N3 _3, N4 _4) {\
    return self->trait->##_name_##_ (self->value, _1, _2, _3, _4); \
  }
#define TRAIT_FN_ARG5(_return_, _name_, _type_, N1, N2, N3, N4, N5)\
  _return_ CONCAT(TRAIT_NAME, __##_type_##__##_name_)\
  (_type_ *self, N1 _1, N2 _2, N3 _3, N4 _4, N5 _5) {\
    return self->trait->##_name_##_ (self->value, _1, _2, _3, _4, _5); \
  }
#define TRAIT_FN_ARG6(_return_, _name_, _type_, N1, N2, N3, N4, N5, N6)\
  _return_ CONCAT(TRAIT_NAME, __##_type_##__##_name_)\
  (_type_ *self, N1 _1, N2 _2, N3 _3, N4 _4, N5 _5, N6 _6) {\
    return self->trait->##_name_##_ (self->value, _1, _2, _3, _4, _5, _6); \
  }

#define GET_10TH_ARG(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, ...) arg10
#define TRAIT_FN_MACRO_CHOOSER(...) \
  MSVC_MACRO_EXPAND(GET_10TH_ARG(__VA_ARGS__, \
    TRAIT_FN_ARG6, TRAIT_FN_ARG5, TRAIT_FN_ARG4, TRAIT_FN_ARG3,\
    TRAIT_FN_ARG2, TRAIT_FN_ARG1, TRAIT_FN_ARG0,,))

/////////////////////////////////////////////////////////////////////////////////////////////////
// Fields Macros
/////////////////////////////////////////////////////////////////////////////////////////////////

#define FIELD_ARG0(_type_, _name_) _type_ _name_;
#define FIELD_ARG1(_type_, _name_, N1) _type_ _name_ [N1];
#define FIELD_ARG2(_type_, _name_, N1, N2) _type_ _name_ [N1][N2];
#define FIELD_ARG3(_type_, _name_, N1, N2, N3) _type_ _name_ [N1][N2][N3];
#define FIELD_ARG4(_type_, _name_, N1, N2, N3, N4) _type_ _name_ [N1][N2][N3][N4];
#define FIELD_ARG5(_type_, _name_, N1, N2, N3, N4, N5) _type_ _name_ [N1][N2][N3][N4][N5];
#define FIELD_ARG6(_type_, _name_, N1, N2, N3, N4, N5, N6) _type_ _name_ [N1][N2][N3][N4][N5][N6];
#define FIELD_ARG7(_type_, _name_, N1, N2, N3, N4, N5, N6, N7) _type_ _name_ [N1][N2][N3][N4][N5][N6][N7];

#define GET_10TH_ARG(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, ...) arg10
#define FIELD_MACRO_CHOOSER(...) \
    MSVC_MACRO_EXPAND(GET_10TH_ARG(__VA_ARGS__, \
            FIELD_ARG7, FIELD_ARG6, FIELD_ARG5, FIELD_ARG4, \
            FIELD_ARG3, FIELD_ARG2, FIELD_ARG1, FIELD_ARG0, ))

#define FIELD_FLAGS(_struct_name_, _field_name_) \
  CONCAT(CONCAT(_struct_name_, __field__), CONCAT(_field_name_, __flags))

#define FIELD_INFO_ARG0(_type_, _name_)\
  static const Type_Info_Qualified_Type \
    CONCAT(CONCAT(Self, __field__), CONCAT(_name_, __qualified_type))\
    = { _type_, .flags = &FIELD_FLAGS(Self, _name_), \
    .array_size_list = 0 };

#define FIELD_INFO_ARG1(_type_, _name_, N1)\
  static const Type_Info_Array_Size CONCAT(_name_, _type_info_array_1)\
    = {N1, 0};\
  static const Type_Info_Qualified_Type \
    CONCAT(CONCAT(Self, __field__), CONCAT(_name_, __qualified_type))\
    = { _type_, .flags = &FIELD_FLAGS(Self, _name_), \
    .array_size_list = &CONCAT(_name_, _type_info_array_1), };

#define FIELD_INFO_ARG2(_type_, _name_, N1, N2)\
  static const Type_Info_Array_Size CONCAT(_name_, _type_info_array_2)\
    = {N2, 0};\
  static const Type_Info_Array_Size CONCAT(_name_, _type_info_array_1)\
    = {N1, &CONCAT(_name_, _type_info_array_2)};\
  static const Type_Info_Qualified_Type \
    CONCAT(CONCAT(Self, __field__), CONCAT(_name_, __qualified_type))\
    = { _type_, .flags = &FIELD_FLAGS(Self, _name_), \
    .array_size_list = &CONCAT(_name_, _type_info_array_1), };

#define FIELD_INFO_ARG3(_type_, _name_, N1, N2, N3)\
  static const Type_Info_Array_Size CONCAT(_name_, _type_info_array_3)\
    = {N3, 0};\
  static const Type_Info_Array_Size CONCAT(_name_, _type_info_array_2)\
    = {N2, &CONCAT(_name_, _type_info_array_3)};\
  static const Type_Info_Array_Size CONCAT(_name_, _type_info_array_1)\
    = {N1, &CONCAT(_name_, _type_info_array_2)};\
  static const Type_Info_Qualified_Type \
    CONCAT(CONCAT(Self, __field__), CONCAT(_name_, __qualified_type))\
    = { _type_, .flags = &FIELD_FLAGS(Self, _name_), \
    .array_size_list = &CONCAT(_name_, _type_info_array_1), };

#define FIELD_INFO_ARG4(_type_, _name_, N1, N2, N3, N4)\
  static const Type_Info_Array_Size CONCAT(_name_, _type_info_array_4)\
    = {N4, 0};\
  static const Type_Info_Array_Size CONCAT(_name_, _type_info_array_3)\
    = {N3, &CONCAT(_name_, _type_info_array_4)};\
  static const Type_Info_Array_Size CONCAT(_name_, _type_info_array_2)\
    = {N2, &CONCAT(_name_, _type_info_array_3)};\
  static const Type_Info_Array_Size CONCAT(_name_, _type_info_array_1)\
    = {N1, &CONCAT(_name_, _type_info_array_2)};\
  static const Type_Info_Qualified_Type \
    CONCAT(CONCAT(Self, __field__), CONCAT(_name_, __qualified_type))\
    = { _type_, .flags = &FIELD_FLAGS(Self, _name_), \
    .array_size_list = &CONCAT(_name_, _type_info_array_1), };

#define FIELD_INFO_ARG5(_type_, _name_, N1, N2, N3, N4, N5)\
  static const Type_Info_Array_Size CONCAT(_name_, _type_info_array_5)\
    = {N5, 0};\
  static const Type_Info_Array_Size CONCAT(_name_, _type_info_array_4)\
    = {N4, &CONCAT(_name_, _type_info_array_5)};\
  static const Type_Info_Array_Size CONCAT(_name_, _type_info_array_3)\
    = {N3, &CONCAT(_name_, _type_info_array_4)};\
  static const Type_Info_Array_Size CONCAT(_name_, _type_info_array_2)\
    = {N2, &CONCAT(_name_, _type_info_array_3)};\
  static const Type_Info_Array_Size CONCAT(_name_, _type_info_array_1)\
    = {N1, &CONCAT(_name_, _type_info_array_2)};\
  static const Type_Info_Qualified_Type \
    CONCAT(CONCAT(Self, __field__), CONCAT(_name_, __qualified_type))\
    = { _type_, .flags = &FIELD_FLAGS(Self, _name_), \
    .array_size_list = &CONCAT(_name_, _type_info_array_1), };

#define FIELD_INFO_ARG6(_type_, _name_, N1, N2, N3, N4, N5, N6)\
  static const Type_Info_Array_Size CONCAT(_name_, _type_info_array_6)\
    = {N6, 0};\
  static const Type_Info_Array_Size CONCAT(_name_, _type_info_array_5)\
    = {N5, &CONCAT(_name_, _type_info_array_6)};\
  static const Type_Info_Array_Size CONCAT(_name_, _type_info_array_4)\
    = {N4, &CONCAT(_name_, _type_info_array_5)};\
  static const Type_Info_Array_Size CONCAT(_name_, _type_info_array_3)\
    = {N3, &CONCAT(_name_, _type_info_array_4)};\
  static const Type_Info_Array_Size CONCAT(_name_, _type_info_array_2)\
    = {N2, &CONCAT(_name_, _type_info_array_3)};\
  static const Type_Info_Array_Size CONCAT(_name_, _type_info_array_1)\
    = {N1, &CONCAT(_name_, _type_info_array_2)};\
  static const Type_Info_Qualified_Type \
    CONCAT(CONCAT(Self, __field__), CONCAT(_name_, __qualified_type))\
    = { _type_, .flags = &FIELD_FLAGS(Self, _name_), \
    .array_size_list = &CONCAT(_name_, _type_info_array_1), };

#define FIELD_INFO_ARG7(_type_, _name_, N1, N2, N3, N4, N5, N6, N7)\
  static const Type_Info_Array_Size CONCAT(_name_, _type_info_array_7)\
    = {N7, 0};\
  static const Type_Info_Array_Size CONCAT(_name_, _type_info_array_6)\
    = {N6, &CONCAT(_name_, _type_info_array_7)};\
  static const Type_Info_Array_Size CONCAT(_name_, _type_info_array_5)\
    = {N5, &CONCAT(_name_, _type_info_array_6)};\
  static const Type_Info_Array_Size CONCAT(_name_, _type_info_array_4)\
    = {N4, &CONCAT(_name_, _type_info_array_5)};\
  static const Type_Info_Array_Size CONCAT(_name_, _type_info_array_3)\
    = {N3, &CONCAT(_name_, _type_info_array_4)};\
  static const Type_Info_Array_Size CONCAT(_name_, _type_info_array_2)\
    = {N2, CONCAT(_name_, _type_info_array_3)};\
  static const Type_Info_Array_Size CONCAT(_name_, _type_info_array_1)\
    = {N1, &CONCAT(_name_, _type_info_array_2)};\
  static const Type_Info_Qualified_Type \
    CONCAT(CONCAT(Self, __field__), CONCAT(_name_, __qualified_type))\
    = { _type_, .flags = &FIELD_FLAGS(Self, _name_), \
    .array_size_list = &CONCAT(_name_, _type_info_array_1), };

#define FIELD_INFO_MACRO_CHOOSER(...) \
    MSVC_MACRO_EXPAND(GET_10TH_ARG(__VA_ARGS__, \
            FIELD_INFO_ARG7, FIELD_INFO_ARG6, FIELD_INFO_ARG5, FIELD_INFO_ARG4, \
            FIELD_INFO_ARG3, FIELD_INFO_ARG2, FIELD_INFO_ARG1, FIELD_INFO_ARG0, ))

#define FIELDS_HELPER(_type_) FIELDS(_type_)

/////////////////////////////////////////////////////////////////////////////////////////////////

#define TRAIT_HELPER(_trait_, _type_) \
  CONCAT(Trait__##_trait_##__, _type_) *Trait__##_trait_[DISPATCH_ENUM_ENTRY(Trait__##_trait_, _type_)];

#define STRINGIFY_HELPER(S) #S
#define STRINGIFY(S) STRINGIFY_HELPER(S)

#define static_array_size(_array_) \
  (sizeof(_array_) / sizeof(_array_[0]))

#define CONCAT_HELPER(a, b) a ## b
#define CONCAT(a, b) CONCAT_HELPER(a, b)

#define IMPL_HELPER(_trait_, _fn_, _type_) \
 CONCAT(CONCAT(Trait__##_trait_##__, _type_),  __##_fn_)

#define IMPL(_trait_, _fn_) \
 IMPL_HELPER(_trait_, _fn_, Self)

#define GET_FAKE_TRAITS_ARRAY(_value_,_trait_) \
  (_value_)->prelude_traits[0]->_trait_

#define GET_INSTANCE(_trait_, _value_) \
  (Trait__##_trait_##_Implementation_Lookup_Table[ \
    static_array_size(GET_FAKE_TRAITS_ARRAY(_value_,Trait__##_trait_))\
  ])

#define CALL_TRAIT_FUNCTION_HELPER(_trait_, _fn_, _value_, ...) \
  ( \
    0 ? (GET_FAKE_TRAITS_ARRAY(_value_,Trait__##_trait_)[0]->_fn_(_value_, ##__VA_ARGS__)) \
    : ((Trait__##_trait_##_Implementation_Lookup_Table[ \
      static_array_size(GET_FAKE_TRAITS_ARRAY(_value_,Trait__##_trait_))\
    ])->_fn_(_value_, ##__VA_ARGS__)) \
  )

#define instance(_trait_, _value_) \
  GET_INSTANCE(_trait_, _value_)

#define TYPE_INSTANCE_HELPER(_trait_, _type_) \
  ((Trait__##_trait_##__##_type_ *) GET_INSTANCE(_trait_, ((_type_ *)0)))

#define type_instance(_trait_, _type_) \
  TYPE_INSTANCE_HELPER(_trait_, _type_)

#define fancy_invoke(_trait_, _fn_, _value_, ...) \
  CALL_TRAIT_FUNCTION_HELPER(_trait_, CONCAT(_fn_, _), _value_, ##__VA_ARGS__)

#define cast_to_trait(_trait_, _value_) \
  ((const _trait_) {instance(_trait_, _value_), _value_})

//////////////////////////////////////////////////////////////////////////////
// Default Traits
//////////////////////////////////////////////////////////////////////////////

#include "fancy_default_traits.h"

//////////////////////////////////////////////////////////////////////////////
// Type_Info
//////////////////////////////////////////////////////////////////////////////

typedef enum {
  Type_Info_Tag_Void,
  Type_Info_Tag_Integer,
  Type_Info_Tag_Float,
  Type_Info_Tag_Struct,
} Type_Info_Tag;

typedef struct Type_Info_Qualified_Type Type_Info_Qualified_Type;

typedef struct {
  const char *name;
  const Type_Info_Qualified_Type *qualified_type;
  const char *type_string;

  uint32_t size;
  uint32_t offset;
} Type_Info_Struct_Field;

typedef struct {
  const Type_Info_Struct_Field *fields;
  uint32_t field_count;
} Type_Info_Struct;

typedef enum {
  Type_Info_Integer_Signed,
  Type_Info_Integer_Unsigned,
} Type_Info_Integer_Signedness;

typedef struct {
  const char *name;
  Type_Info_Integer_Signedness signedness;
  uint32_t size;
} Type_Info_Integer;

typedef struct {
  const char *name;
  uint32_t size;
} Type_Info_Float;

typedef struct {
  const char *name;
  int64_t value;
} Type_Info_Enum_Item;

typedef struct {
  Type_Info_Integer *integer_type;
  Type_Info_Enum_Item *items;
  uint32_t item_count;
} Type_Info_Enum;

typedef struct Type_Info_Type {
  Type_Info_Tag tag;
  const char *name;
  union {
    const Type_Info_Integer integer;
    const Type_Info_Float float_;
    const Type_Info_Struct struct_;
  };
} Type_Info_Type;

typedef struct Type_Info_Array_Size {
  const int64_t size;
  const struct Type_Info_Array_Size *next;
} Type_Info_Array_Size;

typedef struct Type_Info_Qualified_Type {
  const Type_Info_Type *type;
  const int64_t *flags;
  const Type_Info_Array_Size *array_size_list;
} Type_Info_Qualified_Type;

const Type_Info_Type float__type_info = {
  .tag = Type_Info_Tag_Float,
  .name = "float",
  .float_ = { .size = sizeof(float), }
};

const Type_Info_Type double__type_info = {
  .tag = Type_Info_Tag_Float,
  .name = "double",
  .float_ = { .size = sizeof(double), }
};

const Type_Info_Type int__type_info = {
  .tag = Type_Info_Tag_Integer,
  .name = "int",
  .integer = { .signedness = Type_Info_Integer_Signed, .size = sizeof(int), }
};

const Type_Info_Type char__type_info = {
  .tag = Type_Info_Tag_Integer,
  .name = "char",
  .integer = { .signedness = Type_Info_Integer_Signed, .size = sizeof(char), }
};

const Type_Info_Type void__type_info = {
  .tag = Type_Info_Tag_Void,
  .name = "void"
};

#define TRAIT_FUNCTIONS(Self)\
  TRAIT_FUNCTION(const Type_Info_Type *, type_info, Self)

#ifndef FANCY_PRINT_MAX_DEPTH
#define FANCY_PRINT_MAX_DEPTH 3
#endif

#define type_info(self) fancy_invoke(Type_Info, type_info, self)
#define print(self) print_from_type_info(self, type_info(self), FANCY_PRINT_MAX_DEPTH)

#define TRAIT_IMPLEMENTATIONS FANCY_TYPE_INFO_TRAIT_IMPLEMENTATIONS
#define MAKE_SELF_IMPLEMENTATION

#define Self Type_Info
#include "fancy_trait.h"
#undef Self

void print_from_type_info(void *self, const Type_Info_Type *type, uint16_t max_depth) {
  if (max_depth == 0) return;
  switch (type->tag) {
    case Type_Info_Tag_Void: {
      printf("void");
      break;
    }
    case Type_Info_Tag_Float: {
      double to_print = *((double *)self);
      printf("%f", to_print);
      break;
    }
    case Type_Info_Tag_Integer: {
      int64_t to_print = 0;
      switch(type->integer.size) {
        case 8: {
          to_print = *((int64_t *)self);
          break;
        }
        case 4: {
          to_print = *((int32_t *)self);
          break;
        }
        case 2: {
          to_print = *((int16_t *)self);
          break;
        }
        case 1: {
          to_print = *((int8_t *)self);
          break;
        }
        default: {
          assert(!"Unknown integer size");
        }
      }
      if (type->integer.signedness == Type_Info_Integer_Signed) {
        printf("%lld", to_print);
      } else {
        printf("%llu", (uint64_t)to_print);
      }
      break;
    }
    case Type_Info_Tag_Struct: {
      const Type_Info_Struct *struct_ = &type->struct_;
      printf("%s { ", type->name);
      if (max_depth == 1) {
        printf("...");
      } else {
        for (size_t i = 0; i < struct_->field_count; ++i) {
          if (i != 0) printf(", ");
          const Type_Info_Struct_Field *field = &struct_->fields[i];
          const Type_Info_Type *field_type = field->qualified_type->type;
          void *field_value = (uint8_t *)self + field->offset;
          print_from_type_info(field_value, field_type, max_depth - 1);
        }
      }
      printf(" }");
      break;
    }
    default: {
      assert(!"Not implemented");
      break;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////
// Comparable
//////////////////////////////////////////////////////////////////////////////

#define TRAIT_FUNCTIONS(Self)\
  TRAIT_FUNCTION(int, compare, Self, Self *)

#define compare(self, other) fancy_invoke(Comparable, area, self, other)

#define TRAIT_IMPLEMENTATIONS FANCY_COMPARABLE_TRAIT_IMPLEMENTATIONS

#define Self Comparable
#include "fancy_trait.h"
#undef Self

#endif
