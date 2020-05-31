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
}
