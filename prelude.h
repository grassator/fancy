#include <stdint.h>
#include <stdbool.h>

// Common things for all traits

#define CONCAT(a, b) CONCAT_HELPER(a, b)
#define CONCAT_HELPER(a, b) a ## b

#define BEGIN_TRAITS struct {
#define HAS_TRAIT(_trait_)\
  CONCAT(_trait_##__, Self) *_trait_[DISPATCH_ENUM_ENTRY(_trait_, Self)]
#define END_TRAITS } *prelude_traits[];

#define IMPL(_trait_, _fn_) \
 CONCAT(CONCAT(_trait_##__, Self),  __##_fn_)

#define GET_FAKE_TRAITS_ARRAY(_value_,_trait_) \
  (_value_)->prelude_traits[0]->_trait_

#define CALL_TRAIT_FUNCTION_HELPER(_trait_, _fn_, _value_, ...) \
  (_trait_##_Implementation_Lookup_Table[ \
    sizeof(GET_FAKE_TRAITS_ARRAY(_value_,_trait_)[0]->_fn_(_value_, ##__VA_ARGS__)) * 0 + \
    sizeof(GET_FAKE_TRAITS_ARRAY(_value_,_trait_)) / sizeof(GET_FAKE_TRAITS_ARRAY(_value_,_trait_)[0]) \
  ])->_fn_(_value_, ##__VA_ARGS__)

#define CALL_TRAIT_FUNCTION(_trait_, _fn_, _value_, ...) \
  CALL_TRAIT_FUNCTION_HELPER(_trait_, _fn_, _value_, ##__VA_ARGS__)

//////////////////////////////////////////

#define TRAIT Trait_Shape

#define TRAIT_FUNCTIONS(T)\
  TRAIT_FUNCTION(T, int, area,      (T *))\
  TRAIT_FUNCTION(T, int, perimeter, (T *))

#define area(x)      CALL_TRAIT_FUNCTION(Trait_Shape, area,      x)
#define perimeter(x) CALL_TRAIT_FUNCTION(Trait_Shape, perimeter, x)

// Users need to register here
#define TRAIT_IMPLEMENTATIONS\
  REGISTER_IMPLEMENTATION(Rect)\
  REGISTER_IMPLEMENTATION(Circle)

#include "trait_include.h"
#undef TRAIT

/////////////////////////////

#define Self Rect
typedef struct Self {
    int width;
    int height;

    BEGIN_TRAITS
      HAS_TRAIT(Trait_Shape);
    END_TRAITS
} Self;

inline int IMPL(Trait_Shape, area) (Self *rect) {
  return rect->width * rect->height;
}

inline int IMPL(Trait_Shape, perimeter)(Self *rect) {
  return rect->width * 2 + rect->height * 2;
}
#undef Self

#define Self Circle
typedef struct Self {
    int radius;

    BEGIN_TRAITS
      HAS_TRAIT(Trait_Shape);
    END_TRAITS
} Self;

inline int IMPL(Trait_Shape, area) (Self *self) {
  return (int)(3.14 * self->radius * self->radius);
}

inline int IMPL(Trait_Shape, perimeter)(Self *self) {
  return (int)(2.0 * 3.14 * self->radius);
}
#undef Self

