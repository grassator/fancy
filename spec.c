#include "bdd-for-c.h"
#include "prelude.h"

spec("prelude") {
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
    check(invoke(Shape, area, &circle) == 314);
    check(invoke(Shape, perimeter, &circle) == 62);
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

  it("should stringified Type_Info") {
    Rect rect = {42, 10};
    //printf("%s", type_info_to_c_string(type_info(&rect)));
    const char *type_info_string = type_info_to_c_string(type_info(&rect));
    check(strcmp(type_info_string, "Rect { int width; int height; }") == 0);
  }
}
