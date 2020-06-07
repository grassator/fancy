#include "bdd-for-c.h"
#include "fancy.h"
#include "examples/shape.h"
#include "examples/enum.h"
#include "examples/struct_type_modifiers.h"

spec("fancy") {
  it("should support dynamicly growing arrays") {
    fancy_array(int) test = fancy_array_alloc(int, 4);
    check(fancy_array_count(test) == 0);
    check(fancy_array_capacity(test) == 4);
    for (int i = 0; i < 5; ++i) {
      fancy_array_push(test, i);
    }
    check(test.at(0) == 0);
    check(test.at(4) == 4);
    check(fancy_array_count(test) == 5);
  }

  it("should be possible to sort arrays of int") {
    fancy_array(int) test = fancy_array_alloc(int, 10);
    fancy_array_push(test, 9);
    fancy_array_push(test, 2);
    fancy_array_push(test, 6);
    fancy_array_sort(test);
    check(test.at(0) == 2);
    check(test.at(1) == 6);
    check(test.at(2) == 9);
  }

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
