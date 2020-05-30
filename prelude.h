#include <stdint.h>

typedef int (*stuff_t)(void *);
#define stuff_method(_struct_name_) \
  int (*stuff[Stuff_Dispatch_Offset_##_struct_name_])(struct _struct_name_ *)

#define STUFF_IMPLS\
  IMPL(Foo)

#define IMPL(_struct_name_) Stuff_Dispatch_Offset_##_struct_name_,
typedef enum {
  Stuff_Dispatch_Offset_,
  STUFF_IMPLS
} Stuff_Dispatch_Offset;
#undef IMPL

#define IMPL(_struct_name_) struct _struct_name_;
STUFF_IMPLS
#undef IMPL

#define IMPL(_struct_name_) inline int _struct_name_##__stuff(struct _struct_name_ *arg);
STUFF_IMPLS
#undef IMPL

#define IMPL(_struct_name_) [Stuff_Dispatch_Offset_##_struct_name_] = (stuff_t)_struct_name_##__stuff,
static const stuff_t stuff_impl_array[] = {
  0,
STUFF_IMPLS
};
#undef IMPL

typedef struct Foo {
    int i;
    struct {
        stuff_method(Foo);
    } methods[];
} Foo;

inline int Foo__stuff(struct Foo *arg) {
  return arg->i;
}

#define call_method(_arg_, _method_) \
  ((_method_##_impl_array[\
    sizeof((_arg_)->methods[0]._method_[0](_arg_)) * 0 +\
    sizeof((_arg_)->methods[0]._method_) / sizeof((_arg_)->methods[0]._method_[0])\
  ]))(_arg_)

#define stuff(_arg_) call_method(_arg_, stuff)

