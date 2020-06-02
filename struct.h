#define FIELDS_HELPER(_type_) FIELDS(_type_)

#define TRAIT_HELPER(_trait_, _type_) \
  CONCAT(Trait__##_trait_##__, _type_) *Trait__##_trait_[DISPATCH_ENUM_ENTRY(Trait__##_trait_, _type_)];

typedef struct Self {
#undef CONST
#define CONST(_type_) const _type_
#define PTR(_type_) _type_*
#define FIELD(_type_, _name_)  _type_ _name_;
FIELDS_HELPER(Self)
#undef FIELD
#undef CONST
#undef PTR
  struct {
#define TRAIT(_trait_)\
  TRAIT_HELPER(_trait_, Self)
TRAITS
#undef TRAIT
  } *prelude_traits[];
} Self;

#ifndef TRAIT_NAME
inline const Type_Info_Type * IMPL(Type_Info, type_info)(Self *self) {
  // CONST(PTR(int))
  #define PTR(_type_) _type_, 1
  #define CONST(_type_) _type_, .is_const = true
  #define int &type_info_int
  #define FIELD(_type_, _name_)\
    static const Type_Info_Qualified_Type CONCAT(_name_, _type_info) = {\
      _type_\
    };
  FIELDS_HELPER(Self)
  #undef FIELD
  #undef int
  #undef CONST
  #undef PTR

  static const Type_Info_Struct_Field fields[] = {
    #define PTR(_type_) _type_*
    #define CONST(_type_) const _type_
    #define FIELD(_type_, _name_) { \
      .name = STRINGIFY(_name_), \
      .qualified_type = &CONCAT(_name_, _type_info),\
      .type_string = STRINGIFY(_type_), \
      .size = sizeof(_type_), \
      .offset = offsetof(Self, _name_), \
    },
    FIELDS_HELPER(Self)
    #undef FIELD
    #undef CONST
    #undef PTR
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

#undef TRAIT_HELPER
#undef FIELDS_HELPER
#undef FIELDS
#undef TRAITS