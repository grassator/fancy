#include "bdd-for-c.h"
#include "fancy.h"
#include "examples/shape.h"
#include "examples/enum.h"
#include "examples/struct_type_modifiers.h"

spec("fancy") {
  it("should compute area of the rectangle") {
    Rect rect = {42, 10};
    check(area(&rect) == 420);
    check(perimeter(&rect) == 104);
  }

  it("should compute area of the circle") {
    Circle circle = {10};
    check(area(&circle) == 314);
    check(perimeter(&circle) == 62);
  }

  it("should support generic invoke_ calls") {
    Circle circle = {10};
    check(fancy_invoke(Shape, area, &circle) == 314);
    check(fancy_invoke(Shape, perimeter, &circle) == 62);
  }

  it("should support calls through explicit (unsafe) instance") {
    Circle circle = {10};
    check(instance(Shape, &circle)->area_(&circle) == 314);
    check(instance(Shape, &circle)->perimeter_(&circle) == 62);
  }

  it("should support calls through explicit typed instance") {
    Circle circle = {10};
    check(type_instance(Shape, Circle)->area_(&circle) == 314);
    check(type_instance(Shape, Circle)->perimeter_(&circle) == 62);
  }

  it("should support virtual calls through the trait type") {
    Circle circle = {10};
    Shape shape = cast_to_trait(Shape, &circle);
    check(area(&shape) == 314);
    check(perimeter(&shape) == 62);
  }

  it("should be able to print a value") {
    Rect rect = {{42, 10}};
    print(&rect);
    printf("\n");
    Circle circle = {10};
    print(&circle);
    printf("\n");
  }

  it("should be able to print struct with an enum field") {
    Using_Enum_Field test = {.enum_field = Example_Enum_One};
    print(&test);
    printf("\n");
  }
}
