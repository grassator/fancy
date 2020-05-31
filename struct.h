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

#undef TRAIT_HELPER
#undef FIELDS_HELPER
#undef FIELDS
#undef TRAITS