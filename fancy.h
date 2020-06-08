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
  const CONCAT(Trait__##_trait_##__, _type_)\
    *Trait__##_trait_[DISPATCH_ENUM_ENTRY(Trait__##_trait_, _type_)];

#define STRINGIFY_HELPER(S) #S
#define STRINGIFY(S) STRINGIFY_HELPER(S)

#define static_array_size(_array_) \
  (sizeof(_array_) / sizeof(_array_[0]))

#define CONCAT_HELPER(a, b) a ## b
#define CONCAT(a, b) CONCAT_HELPER(a, b)

#define IMPL_TYPE(_trait_, _fn_, _type_) \
 CONCAT(CONCAT(Trait__##_trait_##__, _type_),  CONCAT(__, _fn_))

#define IMPL(_trait_, _fn_) \
 IMPL_TYPE(_trait_, _fn_, Self)

#define GET_FAKE_TRAITS_ARRAY(_value_,_trait_) \
  ((_value_)->fancy_traits->_trait_)

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

#define fancy_cast_pointer_value(_ptr_, _to_)\
  ((_to_) + ((int64_t)(_ptr_) - (int64_t)(_to_)) / sizeof(_to_))

//////////////////////////////////////////////////////////////////////////////
// Default Traits
//////////////////////////////////////////////////////////////////////////////

#include "fancy_default_traits.h"

//////////////////////////////////////////////////////////////////////////////
// Comparable
//////////////////////////////////////////////////////////////////////////////

#define TRAIT_FUNCTIONS(Self)\
  TRAIT_FUNCTION(int, compare, Self, const Self *, const Self *)

#define compare(self, other) fancy_invoke(Comparable, area, self, other)

typedef long long long_long;
typedef unsigned char unsigned_char;
typedef unsigned int unsigned_int;
typedef unsigned long unsigned_long;
typedef unsigned long long unsigned_long_long;

// TODO Maybe IMPLEMENTATION_PRIMITIVE would be a better option
#define TRAIT_IMPLEMENTATIONS\
  IMPLEMENTATION_PRIMITIVE(float)\
  IMPLEMENTATION_PRIMITIVE(double)\
  IMPLEMENTATION_PRIMITIVE(char)\
  IMPLEMENTATION_PRIMITIVE(int)\
  IMPLEMENTATION_PRIMITIVE(long)\
  IMPLEMENTATION_PRIMITIVE(long_long)\
  IMPLEMENTATION_PRIMITIVE(unsigned_char)\
  IMPLEMENTATION_PRIMITIVE(unsigned_int)\
  IMPLEMENTATION_PRIMITIVE(unsigned_long)\
  IMPLEMENTATION_PRIMITIVE(unsigned_long_long)\
  FANCY_COMPARABLE_TRAIT_IMPLEMENTATIONS

inline int IMPL_TYPE(Comparable, compare, float)(
  const float *a,
  const float *b
) {
  return (*a > *b) - (*a < *b);
}

inline int IMPL_TYPE(Comparable, compare, double)(
  const double *a,
  const double *b
) {
  return (*a > *b) - (*a < *b);
}

inline int IMPL_TYPE(Comparable, compare, char)(
  const char *a,
  const char *b
) {
  return *a - *b;
}

inline int IMPL_TYPE(Comparable, compare, int)(
  const int *a,
  const int *b
) {
  return *a - *b;
}

inline int IMPL_TYPE(Comparable, compare, long)(
  const long *a,
  const long *b
) {
  return (*a > *b) - (*a < *b);
}

inline int IMPL_TYPE(Comparable, compare, long_long)(
  const long long *a,
  const long long *b
) {
  return (*a > *b) - (*a < *b);
}

inline int IMPL_TYPE(Comparable, compare, unsigned_char)(
  const unsigned char *a,
  const unsigned char *b
) {
  return (*a > *b) - (*a < *b);
}

inline int IMPL_TYPE(Comparable, compare, unsigned_int)(
  const unsigned int *a,
  const unsigned int *b
) {
  return (*a > *b) - (*a < *b);
}

inline int IMPL_TYPE(Comparable, compare, unsigned_long)(
  const unsigned long *a,
  const unsigned long *b
) {
  return (*a > *b) - (*a < *b);
}

inline int IMPL_TYPE(Comparable, compare, unsigned_long_long)(
  const unsigned long long *a,
  const unsigned long long *b
) {
  return (*a > *b) - (*a < *b);
}

#define Self Comparable
#include "fancy_trait.h"
#undef Self

//////////////////////////////////////////////////////////////////////////////
// Primitive types
//////////////////////////////////////////////////////////////////////////////

#define fancy_primitive_type_vtable_typedef(_type_)\
  typedef struct {\
    const CONCAT(Trait__Comparable__, _type_) *Trait__Comparable;\
  } CONCAT(VTable__, _type_);\
  const CONCAT(VTable__, _type_) CONCAT(VTable__Implementation__, _type_) = {\
    .Trait__Comparable = &CONCAT(CONCAT(Trait__Comparable, __Implementation__), _type_),\
  };

fancy_primitive_type_vtable_typedef(float);
fancy_primitive_type_vtable_typedef(double);
fancy_primitive_type_vtable_typedef(char);
fancy_primitive_type_vtable_typedef(int);
fancy_primitive_type_vtable_typedef(long);
fancy_primitive_type_vtable_typedef(long_long);
fancy_primitive_type_vtable_typedef(unsigned_char);
fancy_primitive_type_vtable_typedef(unsigned_int);
fancy_primitive_type_vtable_typedef(unsigned_long);
fancy_primitive_type_vtable_typedef(unsigned_long_long);

//////////////////////////////////////////////////////////////////////////////
// Array
//////////////////////////////////////////////////////////////////////////////

typedef struct {
  const void *vtable;
  char *next_free;
  char *after_last;
  char items[];
} Fancy_Array_Internal;

#define fancy_array_typedef(_type_)\
  typedef union {\
    Fancy_Array_Internal *internal;\
    struct CONCAT(Fancy_Array_Internal__, _type_) {\
      const CONCAT(VTable__, _type_) *vtable;\
      _type_ *next_free;\
      _type_ *after_last;\
      _type_ items[];\
    } *array;\
  } CONCAT(Fancy_Array__, _type_)

fancy_array_typedef(float);
fancy_array_typedef(double);
fancy_array_typedef(char);
fancy_array_typedef(int);
fancy_array_typedef(long);
fancy_array_typedef(long_long);
fancy_array_typedef(unsigned_char);
fancy_array_typedef(unsigned_int);
fancy_array_typedef(unsigned_long);
fancy_array_typedef(unsigned_long_long);

Fancy_Array_Internal *
fancy_array_realloc_internal(
  const void *vtable,
  Fancy_Array_Internal *internal,
  size_t item_size,
  size_t item_count
) {
  size_t new_allocation_size = sizeof(Fancy_Array_Internal) + item_count * item_size;
  Fancy_Array_Internal *result = realloc(internal, new_allocation_size);
  if (result) {
    result->vtable = vtable;
    result->next_free = result->items;
    result->after_last = result->items + item_count * item_size;
  } else {
    free(internal);
  }
  return result;
}

void
fancy_array_increase_capacity(
  Fancy_Array_Internal **internal,
  size_t item_size
) {
  size_t current_capacity = ((*internal)->after_last - (*internal)->items) / item_size;
  size_t new_capacity = current_capacity + current_capacity / 2;
  size_t next_free_offset = (*internal)->next_free - (*internal)->items;
  *internal = fancy_array_realloc_internal((*internal)->vtable, *internal, item_size, new_capacity);
  if (*internal) {
    (*internal)->next_free += next_free_offset;
  }
}

inline void
fancy_array_ensure_capacity(
  Fancy_Array_Internal **internal,
  size_t item_size,
  size_t extra_item_count
) {
  while (((*internal)->next_free + extra_item_count * item_size) > (*internal)->after_last) {
    fancy_array_increase_capacity(internal, item_size);
  }
}

#define fancy_array(_type_) CONCAT(Fancy_Array__, _type_)
#define fancy_array_alloc(_type_, _count_)\
  ((CONCAT(Fancy_Array__, _type_)) {\
    .internal = fancy_array_realloc_internal(\
      &CONCAT(VTable__Implementation__, _type_), 0, sizeof(_type_), _count_\
    ),\
  })
#define fancy_array_push(_array_, ...)\
  do {\
    fancy_array_ensure_capacity(&((_array_).internal), sizeof((_array_).array->items[0]), 1);\
    (*(_array_).array->next_free++ = (##__VA_ARGS__));\
  } while(0)

#define fancy_array_capacity(_array_)\
  (((_array_).internal->after_last - (_array_).internal->items) / sizeof((_array_).array->items[0]))

#define fancy_array_count(_array_)\
  (((_array_).array->next_free - (_array_).array->items))


#define fancy_array_sort(_array_)\
  qsort(\
    (_array_).array->items,\
    fancy_array_count(test),\
    sizeof((_array_).array->items[0]),\
    (_array_).array->vtable->Trait__Comparable[0].compare_\
  );

#define fancy_array_get(_array_, _index_)\
  (&(_array_).array->items[_index_])

#define at(_index_) array->items[_index_]

//////////////////////////////////////////////////////////////////////////////
// Type_Info
//////////////////////////////////////////////////////////////////////////////

typedef enum {
  Type_Info_Tag_Void,
  Type_Info_Tag_Integer,
  Type_Info_Tag_Float,
  Type_Info_Tag_Struct,
  Type_Info_Tag_Enum,
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
  uint32_t byte_size;
} Type_Info_Integer;

typedef struct {
  const char *name;
  uint32_t byte_size;
} Type_Info_Float;

typedef struct {
  const char *name;
  int64_t value;
} Type_Info_Enum_Item;

typedef struct {
  const Type_Info_Enum_Item *items;
  uint32_t item_count;
  uint32_t byte_size;
} Type_Info_Enum;

typedef struct Type_Info_Type {
  Type_Info_Tag tag;
  const char *name;
  union {
    const Type_Info_Integer integer;
    const Type_Info_Float float_;
    const Type_Info_Struct struct_;
    const Type_Info_Enum enum_;
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
  .float_ = { .byte_size = sizeof(float), }
};

const Type_Info_Type double__type_info = {
  .tag = Type_Info_Tag_Float,
  .name = "double",
  .float_ = { .byte_size = sizeof(double), }
};

const Type_Info_Type int__type_info = {
  .tag = Type_Info_Tag_Integer,
  .name = "int",
  .integer = { .signedness = Type_Info_Integer_Signed, .byte_size = sizeof(int), }
};

const Type_Info_Type unsigned_int__type_info = {
  .tag = Type_Info_Tag_Integer,
  .name = "unsigned int",
  .integer = { .signedness = Type_Info_Integer_Unsigned, .byte_size = sizeof(unsigned int), }
};

const Type_Info_Type long__type_info = {
  .tag = Type_Info_Tag_Integer,
  .name = "long",
  .integer = { .signedness = Type_Info_Integer_Signed, .byte_size = sizeof(long), }
};

const Type_Info_Type unsigned_long__type_info = {
  .tag = Type_Info_Tag_Integer,
  .name = "unsigned long",
  .integer = { .signedness = Type_Info_Integer_Unsigned, .byte_size = sizeof(unsigned long), }
};

const Type_Info_Type char__type_info = {
  .tag = Type_Info_Tag_Integer,
  .name = "char",
  .integer = { .signedness = Type_Info_Integer_Signed, .byte_size = sizeof(char), }
};

const Type_Info_Type unsigned_char__type_info = {
  .tag = Type_Info_Tag_Integer,
  .name = "unsigned char",
  .integer = { .signedness = Type_Info_Integer_Unsigned, .byte_size = sizeof(unsigned char), }
};

const Type_Info_Type void__type_info = {
  .tag = Type_Info_Tag_Void,
  .name = "void"
};

#define TRAIT_FUNCTIONS(Self)\
  TRAIT_FUNCTION(const Type_Info_Type *, type_info, Self, Self *)

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
    case Type_Info_Tag_Enum: {
      int64_t to_print = 0;
      switch(type->enum_.byte_size) {
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
      assert(to_print < type->enum_.item_count);
      printf("%s", type->enum_.items[to_print].name);
      break;
    }
    case Type_Info_Tag_Integer: {
      int64_t to_print = 0;
      switch(type->integer.byte_size) {
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
          printf(".%s = ", field->name);
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

#endif