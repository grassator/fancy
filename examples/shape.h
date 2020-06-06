#ifndef SHAPE_H
#define SHAPE_H

#include "fancy.h"
#include <math.h>

//////////////////////////////////////////////////////////////////////////////
// Shape
//////////////////////////////////////////////////////////////////////////////

#define TRAIT_FUNCTIONS(Self)\
  TRAIT_FUNCTION(int, area,      Self)\
  TRAIT_FUNCTION(int, perimeter, Self)

#define area(self)      fancy_invoke(Shape, area,      self)
#define perimeter(self) fancy_invoke(Shape, perimeter, self)

// Users need to register here
#define TRAIT_IMPLEMENTATIONS\
  IMPLEMENTATION(Rect)\
  IMPLEMENTATION(Circle)

#define MAKE_SELF_IMPLEMENTATION
#define Self Shape
#include "fancy_trait.h"
#undef Self


//////////////////////////////////////////////////////////////////////////////
#define Self Geometry_Size
//////////////////////////////////////////////////////////////////////////////

#define FIELDS(Self)\
  FIELD(TYPE(int), width)\
  FIELD(TYPE(int), height)

#define TRAITS\
  TRAIT(Type_Info)

#include "fancy_struct.h"

inline int IMPL(Comparable, compare)(Self *self, Self *other) {
  return self->width * self->height - other->width * other->height;
}

#undef Self

//////////////////////////////////////////////////////////////////////////////
#define Self Rect
//////////////////////////////////////////////////////////////////////////////

#define FIELDS(Self)\
  FIELD(TYPE(Geometry_Size), size)

#define TRAITS\
  TRAIT(Shape)\
  TRAIT(Type_Info)

#include "fancy_struct.h"

inline int IMPL(Shape, area)(Self *self) {
  return self->size.width * self->size.height;
}

inline int IMPL(Shape, perimeter)(Self *self) {
  return self->size.width * 2 + self->size.height * 2;
}

#undef Self

//////////////////////////////////////////////////////////////////////////////
// Circle
//////////////////////////////////////////////////////////////////////////////

#define Self Circle

#define FIELDS(Self)\
  FIELD(TYPE(int), radius)

#define TRAITS\
  TRAIT(Shape)\
  TRAIT(Type_Info)

#include "fancy_struct.h"

#define CIRCLE_PI 3.14159265358979323846

inline int IMPL(Shape, area) (Self *self) {
  return (int)(CIRCLE_PI * self->radius * self->radius);
}

inline int IMPL(Shape, perimeter)(Self *self) {
  return (int)(2.0 * CIRCLE_PI * self->radius);
}
#undef Self

#endif