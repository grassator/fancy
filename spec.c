#include "bdd-for-c.h"
#include "prelude.h"

spec("prelude") {
  it("should compute area of the rectangle") {
    Rect rect = {42, 10};
    check(area_(&rect) == 420);
    check(perimeter_(&rect) == 104);
  }

  it("should compute area of the circle") {
    Circle circle = {10};
    check(area_(&circle) == 314);
    check(perimeter_(&circle) == 62);
  }

  it("should support generic invoke_ calls") {
    Circle circle = {10};
    check(invoke_(Shape, area, &circle) == 314);
    check(invoke_(Shape, perimeter, &circle) == 62);
  }

  it("should support calls through explicit (unsafe) instance") {
    Circle circle = {10};
    check(instance_(Shape, &circle)->area(&circle) == 314);
    check(instance_(Shape, &circle)->perimeter(&circle) == 62);
  }

  it("should support calls through explicit typed instance") {
    Circle circle = {10};
    check(type_instance_(Shape, Circle)->area(&circle) == 314);
    check(type_instance_(Shape, Circle)->perimeter(&circle) == 62);
  }
}
