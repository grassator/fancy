
#define ENUMERATE(_name_) CONCAT(CONCAT(Self, _), _name_),
typedef enum Self {
  FANCY_ENUM
} Self;
#undef ENUMERATE

static const Type_Info_Enum_Item CONCAT(Self, __items)[] = {
#define ENUMERATE(_name_)\
  { .name = STRINGIFY(CONCAT(CONCAT(Self, _), _name_)), .value = CONCAT(CONCAT(Self, _), _name_), },
FANCY_ENUM
#undef ENUMERATE
};

static const Type_Info_Type CONCAT(Self, __type_info) = {
  .tag = Type_Info_Tag_Enum,
  .name = STRINGIFY(Self),
  .enum_ = {
    .items = CONCAT(Self, __items),
    .item_count = static_array_size(CONCAT(Self, __items)),
    .byte_size = sizeof(Self),
  },
};