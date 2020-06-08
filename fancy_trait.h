#define TRAIT_NAME CONCAT(Trait__, Self)

#define TRAIT_IMPLEMENTATIONS_HELPER TRAIT_IMPLEMENTATIONS

#define TRAIT_FUNCTION(_return_, _name_, _type_, ...) \
  _return_ (*_name_##_) (__VA_ARGS__);
typedef struct {
  TRAIT_FUNCTIONS(void)
} TRAIT_NAME;
#undef TRAIT_FUNCTION

#define DISPATCH_ENUM_ENTRY_HELPER(_trait_, _struct_name_) Dispatch_##_trait_##__##_struct_name_
#define DISPATCH_ENUM_ENTRY(_trait_, _struct_name_) DISPATCH_ENUM_ENTRY_HELPER(_trait_, _struct_name_)

#define IMPLEMENTATION(_struct_name_) DISPATCH_ENUM_ENTRY(TRAIT_NAME, _struct_name_),
#define IMPLEMENTATION_PRIMITIVE(_type_) IMPLEMENTATION(_type_)
enum {
  CONCAT(Dispatch_, TRAIT_NAME),
  TRAIT_IMPLEMENTATIONS_HELPER
};
#undef IMPLEMENTATION_PRIMITIVE
#undef IMPLEMENTATION

#define IMPLEMENTATION(_struct_name_) typedef struct _struct_name_ _struct_name_;
#define IMPLEMENTATION_PRIMITIVE(_type_)
TRAIT_IMPLEMENTATIONS_HELPER
#undef IMPLEMENTATION_PRIMITIVE
#undef IMPLEMENTATION

#define TRAIT_FUNCTION(_return_, _name_, _type_, ...)\
  _return_ (*_name_##_) (__VA_ARGS__);
#define IMPLEMENTATION(_struct_name_)\
  typedef struct { \
    TRAIT_FUNCTIONS(_struct_name_)\
  } CONCAT(TRAIT_NAME, CONCAT(__, _struct_name_));
#define IMPLEMENTATION_PRIMITIVE(_type_) IMPLEMENTATION(_type_)
TRAIT_IMPLEMENTATIONS_HELPER
#undef IMPLEMENTATION_PRIMITIVE
#undef IMPLEMENTATION
#undef TRAIT_FUNCTION

// Declare actual implementation functions
#define TRAIT_FUNCTION(_return_, _name_, _type_, ...) \
  _return_ CONCAT(TRAIT_NAME, __##_type_##__##_name_) (__VA_ARGS__);
#define IMPLEMENTATION(_struct_name_) TRAIT_FUNCTIONS(_struct_name_)
#define IMPLEMENTATION_PRIMITIVE(_type_) IMPLEMENTATION(_type_)
TRAIT_IMPLEMENTATIONS_HELPER
#undef IMPLEMENTATION_PRIMITIVE
#undef IMPLEMENTATION
#undef TRAIT_FUNCTION

#define TRAIT_FUNCTION(_return_, _name_, _type_, ...)\
  CONCAT(TRAIT_NAME, CONCAT(CONCAT(CONCAT(__, _type_), __), _name_)),
#define IMPLEMENTATION(_struct_name_) \
  const CONCAT(TRAIT_NAME, CONCAT(__, _struct_name_))\
    CONCAT(CONCAT(TRAIT_NAME, __Implementation__), _struct_name_)\
    = { TRAIT_FUNCTIONS(_struct_name_) };
#define IMPLEMENTATION_PRIMITIVE(_type_) IMPLEMENTATION(_type_)
TRAIT_IMPLEMENTATIONS_HELPER
#undef IMPLEMENTATION_PRIMITIVE
#undef IMPLEMENTATION
#undef TRAIT_FUNCTION

#define IMPLEMENTATION(_struct_name_)\
  [DISPATCH_ENUM_ENTRY(TRAIT_NAME, _struct_name_)] = \
    (TRAIT_NAME *)&(CONCAT(CONCAT(TRAIT_NAME, __Implementation__), _struct_name_)),
#define IMPLEMENTATION_PRIMITIVE(_type_) IMPLEMENTATION(_type_)
static const TRAIT_NAME *CONCAT(TRAIT_NAME, _Implementation_Lookup_Table)[] = {
  0, // default implementation maybe can go here?
TRAIT_IMPLEMENTATIONS_HELPER
};
#undef IMPLEMENTATION_PRIMITIVE
#undef IMPLEMENTATION

#undef TRAIT_IMPLEMENTATIONS
#undef TRAIT_FUNCTIONS
#undef TRAIT_NAME
#undef MAKE_SELF_IMPLEMENTATION
#undef TRAIT_IMPLEMENTATIONS_HELPER

