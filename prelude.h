#include <stdint.h>
#include <stdbool.h>

// Common things for all traits

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
    sizeof(GET_FAKE_TRAITS_ARRAY(_value_,Trait__##_trait_)) / \
    sizeof(GET_FAKE_TRAITS_ARRAY(_value_,Trait__##_trait_)[0]) \
  ])

#define CALL_TRAIT_FUNCTION_HELPER(_trait_, _fn_, _value_, ...) \
  (Trait__##_trait_##_Implementation_Lookup_Table[ \
    sizeof(GET_FAKE_TRAITS_ARRAY(_value_,Trait__##_trait_)[0]->_fn_(_value_, ##__VA_ARGS__)) * 0 + \
    sizeof(GET_FAKE_TRAITS_ARRAY(_value_,Trait__##_trait_)) / \
      sizeof(GET_FAKE_TRAITS_ARRAY(_value_,Trait__##_trait_)[0]) \
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

//////////////////////////////////////////

#define Self Shape

#define TRAIT_FUNCTIONS(T)\
  TRAIT_FUNCTION(T, int, area,      (T *))\
  TRAIT_FUNCTION(T, int, perimeter, (T *))

#define area(x)      invoke(Shape, area,      x)
#define perimeter(x) invoke(Shape, perimeter, x)

// Users need to register here
#define TRAIT_IMPLEMENTATIONS\
  REGISTER_IMPLEMENTATION(Shape)\
  REGISTER_IMPLEMENTATION(Rect)\
  REGISTER_IMPLEMENTATION(Circle)

#include "trait.h"

#define FIELDS(Self)\
  FIELD(const Trait__##Self *, trait)\
  FIELD(void *, value)

#define TRAITS\
  TRAIT(Self)

#include "struct.h"

inline int IMPL(Self, area) (Self *self) {
  return self->trait->area_(self->value);
}

inline int IMPL(Self, perimeter)(Self *self) {
  return self->trait->perimeter_(self->value);
}
#undef Self


//////////////////////////////////////////////////////////////////////////////
// Rect
//////////////////////////////////////////////////////////////////////////////

#define Self Rect

#define FIELDS(Self)\
  FIELD(int, width)\
  FIELD(int, height)

#define TRAITS\
  TRAIT(Shape)

#include "struct.h"

inline int IMPL(Shape, area)(Self *rect) {
  return rect->width * rect->height;
}

inline int IMPL(Shape, perimeter)(Self *rect) {
  return rect->width * 2 + rect->height * 2;
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

