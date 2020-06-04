#define TRAIT_NAME CONCAT(Trait__, Self)

#ifdef MAKE_SELF_IMPLEMENTATION
  #define TRAIT_IMPLEMENTATIONS_HELPER\
    IMPLEMENTATION(Self)\
    TRAIT_IMPLEMENTATIONS
#else
  #define TRAIT_IMPLEMENTATIONS_HELPER\
    TRAIT_IMPLEMENTATIONS
#endif

#define TRAIT_FUNCTION(_return_, _name_, _type_, ...) \
  _return_ (*_name_##_) (_type_ *self, __VA_ARGS__);
typedef struct {
  TRAIT_FUNCTIONS(void)
} TRAIT_NAME;
#undef TRAIT_FUNCTION

#define DISPATCH_ENUM_ENTRY_HELPER(_trait_, _struct_name_) Dispatch_##_trait_##__##_struct_name_
#define DISPATCH_ENUM_ENTRY(_trait_, _struct_name_) DISPATCH_ENUM_ENTRY_HELPER(_trait_, _struct_name_)

#define IMPLEMENTATION(_struct_name_) DISPATCH_ENUM_ENTRY(TRAIT_NAME, _struct_name_),
enum {
  CONCAT(Dispatch_, TRAIT_NAME),
  TRAIT_IMPLEMENTATIONS_HELPER
};
#undef IMPLEMENTATION

#define IMPLEMENTATION(_struct_name_) typedef struct _struct_name_ _struct_name_;
TRAIT_IMPLEMENTATIONS_HELPER
#undef IMPLEMENTATION

#define TRAIT_FUNCTION(_return_, _name_, _type_, ...)\
  _return_ (*_name_##_) (_type_ *self, __VA_ARGS__);
#define IMPLEMENTATION(_struct_name_)\
  typedef struct { \
    TRAIT_FUNCTIONS(_struct_name_)\
  } CONCAT(TRAIT_NAME, CONCAT(__, _struct_name_));
TRAIT_IMPLEMENTATIONS_HELPER
#undef IMPLEMENTATION
#undef TRAIT_FUNCTION

// Declare actual implementation functions
#define TRAIT_FUNCTION(_return_, _name_, _type_, ...) \
  _return_ CONCAT(TRAIT_NAME, __##_type_##__##_name_) (_type_ *self, __VA_ARGS__);
#define IMPLEMENTATION(_struct_name_) \
  TRAIT_FUNCTIONS(_struct_name_)
TRAIT_IMPLEMENTATIONS_HELPER
#undef IMPLEMENTATION
#undef TRAIT_FUNCTION

#define TRAIT_FUNCTION(_return_, _name_, _type_, ...)\
  CONCAT(TRAIT_NAME, CONCAT(CONCAT(CONCAT(__, _type_), __), _name_)),
#define IMPLEMENTATION(_struct_name_) \
  const CONCAT(TRAIT_NAME, CONCAT(__, _struct_name_)) CONCAT(TRAIT_NAME, __Implementation__##_struct_name_) = {\
    TRAIT_FUNCTIONS(_struct_name_)\
  };
TRAIT_IMPLEMENTATIONS_HELPER
#undef IMPLEMENTATION
#undef TRAIT_FUNCTION

#define IMPLEMENTATION(_struct_name_)\
  [DISPATCH_ENUM_ENTRY(TRAIT_NAME, _struct_name_)] = \
    (TRAIT_NAME *)&(CONCAT(TRAIT_NAME, __Implementation__##_struct_name_)),
static const TRAIT_NAME *CONCAT(TRAIT_NAME, _Implementation_Lookup_Table)[] = {
  0, // default implementation maybe can go here?
TRAIT_IMPLEMENTATIONS_HELPER
};
#undef IMPLEMENTATION

#ifdef MAKE_SELF_IMPLEMENTATION
  #define FIELDS(Self)\
    FIELD(CONST(PTR(TYPE(TRAIT_NAME))), trait)\
    FIELD(PTR(TYPE(void)), value)

  #define TRAITS\
    TRAIT(Self)

  #include "struct.h"

  #define TRAIT_FUNCTION(...) MSVC_MACRO_EXPAND(TRAIT_FN_MACRO_CHOOSER(__VA_ARGS__)(__VA_ARGS__))
  TRAIT_FUNCTIONS(Self)
  #undef TRAIT_FUNCTION
#endif

#undef TRAIT_IMPLEMENTATIONS
#undef TRAIT_FUNCTIONS
#undef TRAIT_NAME
#undef MAKE_SELF_IMPLEMENTATION
#undef TRAIT_IMPLEMENTATIONS_HELPER

