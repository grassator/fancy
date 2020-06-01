#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// Common things for all traits

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
  (Trait__##_trait_##_Implementation_Lookup_Table[ \
    sizeof(GET_FAKE_TRAITS_ARRAY(_value_,Trait__##_trait_)[0]->_fn_(_value_, ##__VA_ARGS__)) * 0 + \
    static_array_size(GET_FAKE_TRAITS_ARRAY(_value_,Trait__##_trait_))\
  ])->_fn_(_value_, ##__VA_ARGS__)

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

typedef struct {
  const char *name;
  const char *type;
  size_t size;
  size_t offset;
} Type_Info_Struct_Field;

typedef struct {
  const char *name;
  const Type_Info_Struct_Field *fields;
  size_t field_count;
} Type_Info_Struct;

#define TRAIT_FUNCTIONS(Self)\
  TRAIT_FUNCTION(const Type_Info_Struct *, type_info, Self)

#define type_info(self) invoke(Type_Info, type_info, self)


// Users need to register here
#define TRAIT_IMPLEMENTATIONS\
  REGISTER_IMPLEMENTATION(Type_Info)\
  REGISTER_IMPLEMENTATION(Rect)\
  //REGISTER_IMPLEMENTATION(Circle)

#define Self Type_Info
#include "trait.h"
#undef Self

const char *type_info_to_c_string(const Type_Info_Struct *struct_) {
  const size_t size = 4000;
  char *buffer = malloc(size);

  buffer[0] = 0;
  strcat_s(buffer, size, struct_->name);
  strcat_s(buffer, size, " { ");
  for (size_t i = 0; i < struct_->field_count; ++i) {
    strcat_s(buffer, size, struct_->fields[i].type);
    strcat_s(buffer, size, " ");
    strcat_s(buffer, size, struct_->fields[i].name);
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
  FIELD(int, width)\
  FIELD(int, height)

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
  FIELD(int, radius)

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

