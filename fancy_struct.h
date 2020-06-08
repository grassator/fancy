typedef struct CONCAT(VTable__, Self) {
  #define TRAIT(_trait_) TRAIT_HELPER(_trait_, Self)
  TRAITS
  #undef TRAIT
  // @VTableFiller
  // This is required if type has no traits leading
  // to a zero-sized struct that is not allowed in C
  void *fancy_vtable_filler;
} CONCAT(VTable__, Self);

const CONCAT(VTable__, Self) CONCAT(VTable__Implementation__, Self) = {
  #define TRAIT(_trait_)\
    .CONCAT(Trait__,_trait_) =\
      &CONCAT(CONCAT(CONCAT(Trait__,_trait_), __Implementation__), _type_),
  #undef TRAIT
  .fancy_vtable_filler = 0, // @VTableFiller
};

// Anonymous unions and structs in declaration is only compatible with C11,
// but it is also a known GNU extension and is supported in a bunch of
// compilers that otherwise do not support C11.
typedef struct Self {
  union {
    struct {
  #undef CONST
  #define UNSIGNED(_type_) unsigned _type_
  #define TYPE(_type_) _type_
  #define CONST(_type_) const _type_
  #define PTR(_type_)_type_*
  #define FIELD(...) MSVC_MACRO_EXPAND(FIELD_MACRO_CHOOSER(__VA_ARGS__)(__VA_ARGS__))
  FIELDS_HELPER(Self)
  #undef FIELD
  #undef CONST
  #undef PTR
  #undef TYPE
  #undef UNSIGNED
    };
    CONCAT(VTable__, Self) *fancy_traits;
  };
} Self;

#ifndef TRAIT_NAME

#define UNSIGNED(_type_) _type_
#define TYPE(_type_) 0
#define CONST(_type_) (_type_) * (-1)
#define PTR(_type_) _type_ + 1
#define FIELD(_type_, _field_name_, ...) \
  static const int64_t FIELD_FLAGS(Self, _field_name_) = _type_;
FIELDS_HELPER(Self)
#undef FIELD
#undef CONST
#undef PTR
#undef TYPE
#undef UNSIGNED

// Define field flags constants
#define UNSIGNED(_type_) CONCAT(unsigned_, _type_)
#define TYPE(_type_) &CONCAT(_type_, __type_info)
#define CONST(_type_) _type_
#define PTR(_type_) _type_
#define FIELD(...) MSVC_MACRO_EXPAND(FIELD_INFO_MACRO_CHOOSER(__VA_ARGS__)(__VA_ARGS__))
FIELDS_HELPER(Self)
#undef FIELD
#undef CONST
#undef PTR
#undef TYPE
#undef UNSIGNED

// TODO the ##__VA_ARGS__ here is not C99 compatible,
//      need to create a separate FIELD_ * macro set to fix!
static const Type_Info_Struct_Field CONCAT(Self, __fields)[] = {
  #define UNSIGNED(_type_) unsigned _type_
  #define CONST(_type_) const _type_
  #define TYPE(_type_) _type_
  #define PTR(_type_) _type_*
  #define FIELD(_type_, _name_, ...) { \
    .name = STRINGIFY(_name_), \
    .qualified_type = &CONCAT(CONCAT(Self, __field__), CONCAT(_name_, __qualified_type)),\
    .type_string = STRINGIFY(MSVC_MACRO_EXPAND(FIELD_MACRO_CHOOSER(_type_, _name_, ##__VA_ARGS__)(_type_, _name_, ##__VA_ARGS__))), \
    .size = sizeof(_type_), \
    .offset = offsetof(Self, _name_), \
  },
  FIELDS_HELPER(Self)
  #undef FIELD
  #undef CONST
  #undef PTR
  #undef TYPE
  #undef UNSIGNED
};

static const Type_Info_Type CONCAT(Self, __type_info) = {
  .tag = Type_Info_Tag_Struct,
  .name = STRINGIFY(Self),
  .struct_ = {
    .fields = CONCAT(Self, __fields),
    .field_count = static_array_size(CONCAT(Self, __fields)),
  }
};

inline const Type_Info_Type * IMPL(Type_Info, type_info)(Self *self) {
  return &CONCAT(Self, __type_info);
}
#endif

#undef FIELDS
#undef TRAITS