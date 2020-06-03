
typedef struct Self {
#undef CONST
#define TYPE(_type_) _type_
#define CONST(_type_) const _type_
#define PTR(_type_)_type_*
#define FIELD(...) MSVC_MACRO_EXPAND(FIELD_MACRO_CHOOSER(__VA_ARGS__)(__VA_ARGS__))
FIELDS_HELPER(Self)
#undef FIELD
#undef CONST
#undef PTR
#undef TYPE
  struct {
#define TRAIT(_trait_)\
  TRAIT_HELPER(_trait_, Self)
TRAITS
#undef TRAIT
  } *prelude_traits[];
} Self;

#ifndef TRAIT_NAME

inline const Type_Info_Type * IMPL(Type_Info, type_info)(Self *self) {
  #define TYPE(_type_) 0
  #define CONST(_type_) (_type_) * (-1)
  #define PTR(_type_) _type_ + 1
  #define FIELD(_type_, _name_, ...) \
    static const int64_t CONCAT(_name_, _flags) = _type_;
  FIELDS_HELPER(Self)
  #undef FIELD
  #undef CONST
  #undef PTR
  #undef TYPE

  #define TYPE(_type_) CONCAT(_type_, _type_info)
  #define int &int
  #define CONST(_type_) _type_
  #define PTR(_type_) _type_
  #define FIELD(...) MSVC_MACRO_EXPAND(FIELD_INFO_MACRO_CHOOSER(__VA_ARGS__)(__VA_ARGS__))
  FIELDS_HELPER(Self)
  #undef FIELD
  #undef CONST
  #undef PTR
  #undef int
  #undef TYPE

  // TODO the ##__VA_ARGS__ here is not C99 compatible,
  //      need to create a separate FIELD_ * macro set to fix!
  static const Type_Info_Struct_Field fields[] = {
    #define CONST(_type_) const _type_
    #define TYPE(_type_) _type_
    #define PTR(_type_) _type_*
    #define FIELD(_type_, _name_, ...) { \
      .name = STRINGIFY(_name_), \
      .qualified_type = &CONCAT(_name_, _type_info),\
      .type_string = STRINGIFY(MSVC_MACRO_EXPAND(FIELD_MACRO_CHOOSER(_type_, _name_, ##__VA_ARGS__)(_type_, _name_, ##__VA_ARGS__))), \
      .size = sizeof(_type_), \
      .offset = offsetof(Self, _name_), \
    },
    FIELDS_HELPER(Self)
    #undef FIELD
    #undef CONST
    #undef PTR
    #undef TYPE
  };

  static const Type_Info_Type type = {
    .name = STRINGIFY(Self),
    .struct_ = {
      .fields = fields,
      .field_count = static_array_size(fields),
    }
  };
  return &type;
}
#endif

#undef FIELDS
#undef TRAITS