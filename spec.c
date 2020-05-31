#include "bdd-for-c.h"
#include "prelude.h"

spec("prelude") {
  before() {

  }

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
}
