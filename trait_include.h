#define TRAIT_FUNCTION(_type_, _return_, _name_, ...) _return_ (*_name_) __VA_ARGS__;
typedef struct {
  TRAIT_FUNCTIONS(void)
} TRAIT;
#undef TRAIT_FUNCTION

#define DISPATCH_ENUM_ENTRY_HELPER(_trait_, _struct_name_) Dispatch_##_trait_##__##_struct_name_
#define DISPATCH_ENUM_ENTRY(_trait_, _struct_name_) DISPATCH_ENUM_ENTRY_HELPER(_trait_, _struct_name_)

#define REGISTER_IMPLEMENTATION(_trait_, _struct_name_)\
  DISPATCH_ENUM_ENTRY(_trait_, _struct_name_),
enum {
  CONCAT(Dispatch_, TRAIT),
  TRAIT_IMPLEMENTATIONS(TRAIT)
};
#undef REGISTER_IMPLEMENTATION

#define REGISTER_IMPLEMENTATION(_trait_, _struct_name_) typedef struct _struct_name_ _struct_name_;
TRAIT_IMPLEMENTATIONS(TRAIT)
#undef REGISTER_IMPLEMENTATION

#define TRAIT_FUNCTION(_type_, _return_, _name_, ...) _return_ (*_name_) __VA_ARGS__;
#define REGISTER_IMPLEMENTATION(_trait_, _struct_name_)\
  typedef struct { \
    TRAIT_FUNCTIONS(_struct_name_)\
  } _trait_##__##_struct_name_;
TRAIT_IMPLEMENTATIONS(TRAIT)
#undef REGISTER_IMPLEMENTATION
#undef TRAIT_FUNCTION

// Declare actual implementation functions
#define TRAIT_FUNCTION(_type_, _return_, _name_, ...) \
  _return_ CONCAT(TRAIT, __##_type_##__##_name_) __VA_ARGS__;
#define REGISTER_IMPLEMENTATION(_trait_, _struct_name_) \
  TRAIT_FUNCTIONS(_struct_name_)
TRAIT_IMPLEMENTATIONS(TRAIT)
#undef REGISTER_IMPLEMENTATION
#undef TRAIT_FUNCTION

#define TRAIT_FUNCTION(_type_, _return_, _name_, ...) CONCAT(TRAIT, __##_type_##__##_name_),
#define REGISTER_IMPLEMENTATION(_trait_, _struct_name_) \
  const _trait_##__##_struct_name_  _trait_##__Implementation__##_struct_name_ = {\
    TRAIT_FUNCTIONS(_struct_name_)\
  };
TRAIT_IMPLEMENTATIONS(TRAIT)
#undef REGISTER_IMPLEMENTATION
#undef TRAIT_FUNCTION

#define REGISTER_IMPLEMENTATION(_trait_, _struct_name_)\
  [DISPATCH_ENUM_ENTRY(_trait_, _struct_name_)] = \
    (_trait_ *)&(_trait_##__Implementation__##_struct_name_),
static const TRAIT *CONCAT(TRAIT, _Implementation_Lookup_Table)[] = {
  0, // default implementation maybe can go here?
TRAIT_IMPLEMENTATIONS(TRAIT)
};
#undef REGISTER_IMPLEMENTATION


