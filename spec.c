#include "bdd-for-c.h"
#include "prelude.h"

spec("prelude") {
  before() {

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
}
