#define FIELDS_HELPER(_type_) FIELDS(_type_)

#define TRAIT_HELPER(_trait_, _type_) \
  CONCAT(Trait__##_trait_##__, _type_) *Trait__##_trait_[DISPATCH_ENUM_ENTRY(Trait__##_trait_, _type_)];

typedef struct Self {
#define FIELD(_type_, _name_)  _type_ _name_;
FIELDS_HELPER(Self)
#undef FIELD
  struct {
#define TRAIT(_trait_)\
  TRAIT_HELPER(_trait_, Self)
TRAITS
#undef TRAIT
  } *prelude_traits[];
} Self;

#ifndef TRAIT_NAME
inline const Type_Info_Struct * IMPL(Type_Info, type_info)(Self *self) {
  static const Type_Info_Struct_Field fields[] = {
    #define FIELD(_type_, _name_) { \
      .name = STRINGIFY(_name_), \
      .type = STRINGIFY(_type_), \
      .size = sizeof(_type_), \
      .offset = offsetof(Self, _name_), \
    },
    FIELDS(Self)
    #undef FIELD
  };

  static const Type_Info_Struct struct_ = {
    .name = STRINGIFY(Self),
    .fields = fields,
    .field_count = static_array_size(fields),
  };
  return &struct_;
}
#endif

#undef TRAIT_HELPER
#undef FIELDS_HELPER
#undef FIELDS
#undef TRAITS