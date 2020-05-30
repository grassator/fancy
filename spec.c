#include "bdd-for-c.h"
#include "prelude.h"

spec("prelude") {
  before() {

  }

  it("should do stuff") {
    Foo foo = {42};
    check(stuff(&foo) == 42);
  }
}
