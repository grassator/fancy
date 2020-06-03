#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// Common things for all traits

#define MSVC_MACRO_EXPAND(...) __VA_ARGS__

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

#define FIELD_INFO_ARG0(_type_, _name_)\
  static const Type_Info_Qualified_Type CONCAT(_name_, _type_info)\
    = { _type_, .flags = &CONCAT(_name_, _flags) };

#define FIELD_INFO_ARG1(_type_, _name_, N1)\
  static const Type_Info_Array_Size CONCAT(_name_, _type_info_array_1)\
    = {N1, 0};\
  static const Type_Info_Qualified_Type CONCAT(_name_, _type_info)\
    = { _type_, .flags = &CONCAT(_name_, _flags), \
    .array_size_list = &CONCAT(_name_, _type_info_array_1), };

#define FIELD_INFO_ARG2(_type_, _name_, N1, N2)\
  static const Type_Info_Array_Size CONCAT(_name_, _type_info_array_2)\
    = {N2, 0};\
  static const Type_Info_Array_Size CONCAT(_name_, _type_info_array_1)\
    = {N1, &CONCAT(_name_, _type_info_array_2)};\
  static const Type_Info_Qualified_Type CONCAT(_name_, _type_info)\
    = { _type_, .flags = &CONCAT(_name_, _flags), \
    .array_size_list = &CONCAT(_name_, _type_info_array_1), };

#define FIELD_INFO_ARG3(_type_, _name_, N1, N2, N3)\
  static const Type_Info_Array_Size CONCAT(_name_, _type_info_array_3)\
    = {N3, 0};\
  static const Type_Info_Array_Size CONCAT(_name_, _type_info_array_2)\
    = {N2, &CONCAT(_name_, _type_info_array_3)};\
  static const Type_Info_Array_Size CONCAT(_name_, _type_info_array_1)\
    = {N1, &CONCAT(_name_, _type_info_array_2)};\
  static const Type_Info_Qualified_Type CONCAT(_name_, _type_info)\
    = { _type_, .flags = &CONCAT(_name_, _flags), \
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
  static const Type_Info_Qualified_Type CONCAT(_name_, _type_info)\
    = { _type_, .flags = &CONCAT(_name_, _flags), \
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
  static const Type_Info_Qualified_Type CONCAT(_name_, _type_info)\
    = { _type_, .flags = &CONCAT(_name_, _flags), \
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
  static const Type_Info_Qualified_Type CONCAT(_name_, _type_info)\
    = { _type_, .flags = &CONCAT(_name_, _flags), \
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
  static const Type_Info_Qualified_Type CONCAT(_name_, _type_info)\
    = { _type_, .flags = &CONCAT(_name_, _flags), \
    .array_size_list = &CONCAT(_name_, _type_info_array_1), };

#define FIELD_INFO_MACRO_CHOOSER(...) \
    MSVC_MACRO_EXPAND(GET_10TH_ARG(__VA_ARGS__, \
            FIELD_INFO_ARG7, FIELD_INFO_ARG6, FIELD_INFO_ARG5, FIELD_INFO_ARG4, \
            FIELD_INFO_ARG3, FIELD_INFO_ARG2, FIELD_INFO_ARG1, FIELD_INFO_ARG0, ))



#define FIELDS_HELPER(_type_) FIELDS(_type_)

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

#define invoke(_trait_, _fn_, _value_, ...) \
  CALL_TRAIT_FUNCTION_HELPER(_trait_, CONCAT(_fn_, _), _value_, ##__VA_ARGS__)

#define cast_to_trait(_trait_, _value_) \
  (const _trait_) {instance(_trait_, _value_), _value_};


//////////////////////////////////////////////////////////////////////////////
// Type_Info
//////////////////////////////////////////////////////////////////////////////

typedef enum {
  Type_Info_Type_Tag_Void,
  Type_Info_Type_Tag_Integer,
  Type_Info_Type_Tag_Struct,
  Type_Info_Type_Tag_Pointer,
  Type_Info_Type_Tag_Array,
  Type_Info_Type_Tag_Enum,
} Type_Info_Type_Tag;

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
  int64_t value;
} Type_Info_Enum_Item;

typedef struct {
  Type_Info_Integer *integer_type;
  Type_Info_Enum_Item *items;
  uint32_t item_count;
} Type_Info_Enum;

typedef struct Type_Info_Type {
  Type_Info_Type_Tag tag;
  const char *name;
  union {
    const Type_Info_Integer integer;
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

const Type_Info_Type int_type_info = {
  .tag = Type_Info_Type_Tag_Integer,
  .name = "int",
  .integer = {
    .signedness = Type_Info_Integer_Signed,
    .size = sizeof(int),
  }
};


#define TRAIT_FUNCTIONS(Self)\
  TRAIT_FUNCTION(const Type_Info_Type *, type_info, Self)

#define type_info(self) invoke(Type_Info, type_info, self)


// Users need to register here
#define TRAIT_IMPLEMENTATIONS\
  REGISTER_IMPLEMENTATION(Type_Info)\
  REGISTER_IMPLEMENTATION(Rect)\
  //REGISTER_IMPLEMENTATION(Circle)

#define Self Type_Info
#include "trait.h"
#undef Self

const char *type_info_to_c_string(const Type_Info_Type *type) {
  const size_t size = 4000;

  char number_buffer[64] = {0};
  char *buffer = malloc(size);

  buffer[0] = 0;
  strcat_s(buffer, size, type->name);
  const Type_Info_Struct *struct_ = &type->struct_;
  strcat_s(buffer, size, " { ");
  for (size_t i = 0; i < struct_->field_count; ++i) {
    int64_t flags = *struct_->fields[i].qualified_type->flags;
    if (flags < 0) {
      strcat_s(buffer, size, "const ");
      flags = -flags;
    }
    strcat_s(buffer, size, struct_->fields[i].qualified_type->type->name);
    strcat_s(buffer, size, " ");
    for (; flags; --flags) {
      strcat_s(buffer, size, "*");
    }
    strcat_s(buffer, size, struct_->fields[i].name);
    const Type_Info_Array_Size *array_size = struct_->fields[i].qualified_type->array_size_list;
    while (array_size) {
      strcat_s(buffer, size, "[");
      sprintf_s(number_buffer, static_array_size(number_buffer), "%lld", array_size->size);
      strcat_s(buffer, size, number_buffer);
      strcat_s(buffer, size, "]");
      array_size = array_size->next;
    }
    strcat_s(buffer, size, "; ");
  }
  strcat_s(buffer, size, "}");
  return buffer;
}

//////////////////////////////////////////////////////////////////////////////
// Shape
//////////////////////////////////////////////////////////////////////////////


#define TRAIT_FUNCTIONS(Self)\
  TRAIT_FUNCTION(int, area,      Self)\
  TRAIT_FUNCTION(int, perimeter, Self)

#define area(self)      invoke(Shape, area,      self)
#define perimeter(self) invoke(Shape, perimeter, self)

// Users need to register here
#define TRAIT_IMPLEMENTATIONS\
  REGISTER_IMPLEMENTATION(Shape)\
  REGISTER_IMPLEMENTATION(Rect)\
  REGISTER_IMPLEMENTATION(Circle)

#define Self Shape
#include "trait.h"
#undef Self


//////////////////////////////////////////////////////////////////////////////
// Rect
//////////////////////////////////////////////////////////////////////////////

#define Self Rect

#define FIELDS(Self)\
  FIELD(TYPE(int), width)\
  FIELD(TYPE(int), height)\
  FIELD(CONST(PTR(PTR(TYPE(int)))), dummy, 10, 21)

#define TRAITS\
  TRAIT(Shape)\
  TRAIT(Type_Info)

#include "struct.h"

inline int IMPL(Shape, area)(Self *self) {
  return self->width * self->height;
}

inline int IMPL(Shape, perimeter)(Self *self) {
  return self->width * 2 + self->height * 2;
}
#undef Self

//////////////////////////////////////////////////////////////////////////////
// Circle
//////////////////////////////////////////////////////////////////////////////

#define Self Circle

#define FIELDS(Self)\
  FIELD(TYPE(int), radius)

#define TRAITS\
  TRAIT(Shape)

#include "struct.h"

inline int IMPL(Shape, area) (Self *self) {
  return (int)(3.14 * self->radius * self->radius);
}

inline int IMPL(Shape, perimeter)(Self *self) {
  return (int)(2.0 * 3.14 * self->radius);
}
#undef Self
