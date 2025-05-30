#include "Scanogram.h"

namespace texel {

//---------------
//--- Parsers ---
//---------------

namespace scanogram {

namespace {

template <class T>
class Correspondence {
  public:
    Correspondence() = delete;
    Correspondence(const std::string type_name,
                   const std::vector<std::tuple<T, std::string, std::string>> &values)
      : type_name_(type_name) {
      for (const auto &value : values) {
        to_name_[std::get<0>(value)] = std::make_pair(std::get<1>(value), std::get<2>(value));
        to_value_[std::get<1>(value)] = std::get<0>(value);
      }
    }
    Correspondence(const Correspondence &) = delete;
    Correspondence &operator =(const Correspondence &) = delete;

    ErrHandle FromString(const std::string &str, T &value) {
      auto iter = to_value_.find(str);
      if (iter != to_value_.end()) {
        value = iter->second;
        return ErrHandle();
      }
      else {
        std::ostringstream oss;
        oss << "failed to cast '" << str << "' value to the type of '" << type_name_ << "'";
        return ErrHandle(TEXEL_WHERE, oss.str());
      }
    }

    std::string ToString(T value) {
      auto it = to_name_.find(value);
      if (it != to_name_.end()) {
        return it->second.first;
      }
      else {
        return "unknown";
      }
    }

    std::string ToUserFriendly(T value) {
      auto it = to_name_.find(value);
      if (it != to_name_.end()) {
        return it->second.second;
      }
      else {
        std::ostringstream oss;
        oss << "Unknown value ('" << type_name_ << "')";
        return oss.str();
      }
    }

  private:
    std::string type_name_;
    std::unordered_map<T, std::pair<std::string, std::string> > to_name_;
    std::unordered_map<std::string, T> to_value_;
};

template <class T>
std::string ToString(T value, const std::unordered_map<T, std::string> &correspondence) {
  auto it = correspondence.find(value);
  if (it != correspondence.end()) {
    return it->second;
  }
  else {
    return "unknown";
  }
}

} // unnamed namespace

//--------------
//--- Gender ---
//--------------

static Correspondence<scanogram::Gender> genders{ "scanogram::Gender",
  {
    { scanogram::Gender::Neutral, "neutral", "neutral gender" },
    { scanogram::Gender::Male,    "male",    "male" },
    { scanogram::Gender::Female,  "female",  "female" }
  }
};

ErrHandle FromString(const std::string &str, scanogram::Gender &value) {
  return genders.FromString(str, value);
}

std::string ToString(scanogram::Gender gender) {
  return genders.ToString(gender);
}

std::string ToUserFriendly(scanogram::Gender gender) {
  return genders.ToUserFriendly(gender);
}

//----------------
//--- AgeGroup ---
//----------------

static Correspondence<scanogram::AgeGroup> age_groups{ "scanogram::AgeGroup",
  {
    { scanogram::AgeGroup::NA,      "not_available", "unknown age group" },
    { scanogram::AgeGroup::Child,   "child",         "a child" },
    { scanogram::AgeGroup::Adult,   "adult",         "adult person" },
    { scanogram::AgeGroup::Elderly, "elderly",       "elderly person" }
  }
};

ErrHandle FromString(const std::string &str, scanogram::AgeGroup &value) {
  return age_groups.FromString(str, value);
}

std::string ToString(scanogram::AgeGroup group) {
  return age_groups.ToString(group);
}

std::string ToUserFriendly(scanogram::AgeGroup group) {
  return age_groups.ToUserFriendly(group);
}

//-------------------
//--- ScannerType ---
//-------------------

static Correspondence<scanogram::ScannerType> scanner_types{ "scanogram::ScannerType",
  {
    { scanogram::ScannerType::PortalMX,   "portal_mx",   "Portal MX" },
    { scanogram::ScannerType::PortalRX,   "portal_rx",   "Portal RX" },
    { scanogram::ScannerType::FreeFusion, "free_fusion", "Free Fusion" }
  }
};

ErrHandle FromString(const std::string &str, scanogram::ScannerType &value) {
  return scanner_types.FromString(str, value);
}
std::string ToString(scanogram::ScannerType type) {
  return scanner_types.ToString(type);
}

std::string ToUserFriendly(scanogram::ScannerType type) {
  return scanner_types.ToUserFriendly(type);
}

//------------------
//--- SensorType ---
//------------------

static Correspondence<scanogram::SensorType> sensor_types{ "scanogram::SensorType",
  {
    { scanogram::SensorType::Syntethic,   "syntethic",    "software render" },
    { scanogram::SensorType::AzureKinect, "azure_kinect", "Azure Kinect DK" }
  }
};

ErrHandle FromString(const std::string &str, scanogram::SensorType &value) {
  return sensor_types.FromString(str, value);
}

std::string ToString(scanogram::SensorType type) {
  return sensor_types.ToString(type);
}

std::string ToUserFriendly(scanogram::SensorType type) {
  return sensor_types.ToUserFriendly(type);
}

//-----------------
//--- Hairstyle ---
//-----------------

static Correspondence<scanogram::Hairstyle> hairstyles{ "scanogram::Hairstyle",
  {
    { scanogram::Hairstyle::NA,            "not_available",    "unknown hairstyle" },
    { scanogram::Hairstyle::Shaved,        "shaved",           "shaved" },
    { scanogram::Hairstyle::ShortHaircut,  "short_haircut",    "short haircut" },
    { scanogram::Hairstyle::LongHaircut,   "long_haircut",     "long haircut" },
    { scanogram::Hairstyle::Hat,           "hat",              "with hat" }
  }
};

ErrHandle FromString(const std::string &str, scanogram::Hairstyle &value) {
  return hairstyles.FromString(str, value);
}

std::string ToString(scanogram::Hairstyle style) {
  return hairstyles.ToString(style);
}

std::string ToUserFriendly(scanogram::Hairstyle style) {
  return hairstyles.ToUserFriendly(style);
}

//----------------
//--- Clothing ---
//----------------

static Correspondence<scanogram::Clothing> clothings{ "scanogram::Clothing",
  {
    { scanogram::Clothing::NA,         "not_available",  "unknown clothes" },
    { scanogram::Clothing::Underwear,  "underwear",      "almost naked" },
    { scanogram::Clothing::Tight,      "tight",          "tight clothing" },
    { scanogram::Clothing::Casual,     "casual",         "casual clothing" },
    { scanogram::Clothing::Oversize,   "oversize",       "oversize clothing" },
    { scanogram::Clothing::Outerwear,  "outerwear",      "outerwear" }
  }
};

ErrHandle FromString(const std::string &str, scanogram::Clothing &value) {
  return clothings.FromString(str, value);
}

std::string ToString(scanogram::Clothing style) {
  return clothings.ToString(style);
}

std::string ToUserFriendly(scanogram::Clothing style) {
  return clothings.ToUserFriendly(style);
}

//-------------
//--- Shoes ---
//-------------

static Correspondence<scanogram::Shoes> shoes{ "scanogram::Shoes",
  {
    { scanogram::Shoes::NA,           "not_available",  "unknown shoes" },
    { scanogram::Shoes::Barefoot,     "barefoot",       "barefoot or in socks" },
    { scanogram::Shoes::FlatBoots,    "flat_boots",     "flat boots" },
    { scanogram::Shoes::HeeledBoots,  "heeled_boots",   "boots with heels" }
  }
};

ErrHandle FromString(const std::string &str, scanogram::Shoes &value) {
  return shoes.FromString(str, value);
}

std::string ToString(scanogram::Shoes type) {
  return shoes.ToString(type);
}

std::string ToUserFriendly(scanogram::Shoes type) {
  return shoes.ToUserFriendly(type);
}

//----------------
//--- Lighting ---
//----------------

static Correspondence<scanogram::Lighting> lighting_types{ "scanogram::Lighting",
  {
    { scanogram::Lighting::NA,      "not_available",  "unknown lighting" },
    { scanogram::Lighting::Dim,     "dim",            "dim lighting" },
    { scanogram::Lighting::Normal,  "normal",         "normal lighting" },
    { scanogram::Lighting::Bright,  "bright",         "bright lighting" }
  }
};

ErrHandle FromString(const std::string &str, scanogram::Lighting &value) {
  return lighting_types.FromString(str, value);
}

std::string ToString(scanogram::Lighting type) {
  return lighting_types.ToString(type);
}

std::string ToUserFriendly(scanogram::Lighting type) {
  return lighting_types.ToUserFriendly(type);
}

//-----------------
//--- Placement ---
//-----------------

static Correspondence<scanogram::Placement> placements{ "scanogram::Placement",
  {
    { scanogram::Placement::NA,       "not_available",  "unknown place" },
    { scanogram::Placement::Indoor,   "indoor",         "indoor" },
    { scanogram::Placement::Outdoor,  "outdoor",        "outdoor" }
  }
};

ErrHandle FromString(const std::string &str, scanogram::Placement &value) {
  return placements.FromString(str, value);
}

std::string ToString(scanogram::Placement type) {
  return placements.ToString(type);
}

std::string ToUserFriendly(scanogram::Placement type) {
  return placements.ToUserFriendly(type);
}

//---------------
//--- Garment ---
//---------------

static Correspondence<scanogram::Garment> garments{ "scanogram::Garment",
  {
    { scanogram::Garment::Jeans,          "jeans",           "jeans" },
    { scanogram::Garment::Trousers,       "trousers",        "trousers" },
    { scanogram::Garment::Skirt,          "skirt",           "skirt" },
    { scanogram::Garment::Shorts,         "shorts",          "shorts" },
    { scanogram::Garment::SportsTrouser,  "sports_trouser",  "sports trouser" },

    { scanogram::Garment::Shirt,       "shirt",        "shirt" },
    { scanogram::Garment::TShirt,      "t_shirt",      "t-shirt" },
    { scanogram::Garment::LongSleeve,  "long_sleeve",  "long sleeve" },
    { scanogram::Garment::Blazer,      "blazer",       "blazer" },
    { scanogram::Garment::Pullover,    "pullover",     "pullover" },
    { scanogram::Garment::Hoodie,      "hoodie",       "hoodie" },
    { scanogram::Garment::PoloNeck,    "polo_neck",    "polo neck" },
    { scanogram::Garment::TankTop,     "tank_top",     "tank top" },
    { scanogram::Garment::Vest,        "vest",         "vest" },
    { scanogram::Garment::Dress,       "dress",        "dress" },

    { scanogram::Garment::Cap,        "cap",         "cap" },
    { scanogram::Garment::Hat,        "hat",         "hat" },
    { scanogram::Garment::CowboyHat,  "cowboy_hat",  "cowboy hat" },
    { scanogram::Garment::HeadScarf,  "head_scarf",  "head scarf" },
    { scanogram::Garment::Headset,    "headset",     "headset" },

    { scanogram::Garment::Jacket,      "jacket",       "jacket" },
    { scanogram::Garment::DownJacket,  "down_jacket",  "down jacket" },
    { scanogram::Garment::Coat,        "coat",         "coat" },
    { scanogram::Garment::Cloak,       "cloak",        "cloak" },

    { scanogram::Garment::Boots,        "boots",         "boots" },
    { scanogram::Garment::Sandals,      "sandals",       "sandals" },
    { scanogram::Garment::Sneakers,     "sneakers",      "sneakers" },
    { scanogram::Garment::HighBoots,    "high_boots",    "high boots" },
    { scanogram::Garment::HeeledShoes,  "heeled_shoes",  "heeled shoes" },

    { scanogram::Garment::Glasses,     "glasses",      "glasses" },
    { scanogram::Garment::SunGlasses,  "sun_glasses",  "sun glasses" },

    { scanogram::Garment::Scarf,   "scarf",   "scarf" },
    { scanogram::Garment::Gloves,  "gloves",  "gloves" },
    { scanogram::Garment::Tie,     "tie",     "tie" }
  }
};

ErrHandle FromString(const std::string &str, scanogram::Garment &value) {
  return garments.FromString(str, value);
}

std::string ToString(scanogram::Garment type) {
  return garments.ToString(type);
}

std::string ToUserFriendly(scanogram::Garment type) {
  return garments.ToUserFriendly(type);
}

//----------------
//--- ScanPass ---
//----------------

static Correspondence<scanogram::ScanPass> scan_passes{ "scanogram::ScanPass",
  {
    { scanogram::ScanPass::Body,  "body",  "indoor" },
    { scanogram::ScanPass::Head,  "head",  "outdoor" }
  }
};

ErrHandle FromString(const std::string &str, scanogram::ScanPass &value) {
  return scan_passes.FromString(str, value);
}

std::string ToString(scanogram::ScanPass type) {
  return scan_passes.ToString(type);
}

std::string ToUserFriendly(scanogram::ScanPass type) {
  return scan_passes.ToUserFriendly(type);
}

} // namespace scanogram

//--------------
//--- Stream ---
//--------------

namespace {

ErrHandle FromString(const std::string &str, size_t &value) {
  std::istringstream iss(str);
  if (!(iss >> value) || iss.bad()) {
    std::ostringstream oss;
    oss << "failed to parse the '" << str << "' (expected to be uint)";
    return ErrHandle(TEXEL_WHERE, oss.str());
  }
  return ErrHandle();
}

ErrHandle FromString(const std::string &str, float &value) {
  std::istringstream iss(str);
  if (!(iss >> value) || iss.bad()) {
    std::ostringstream oss;
    oss << "failed to parse the '" << str << "' (expected to be float)";
    return ErrHandle(TEXEL_WHERE, oss.str());
  }
  return ErrHandle();
}

ErrHandle FromString(const std::string &str, std::string &value) {
  value = str;
  return ErrHandle();
}

} // unnamed namespace

namespace scanogram {

Stream::Stream(SensorType sensor, std::string sensor_data,
               const Camera &depth_camera, std::string &&depth_dir,
               const Camera &color_camera, std::string &&color_dir,
               const Camera &ir_camera, std::string &&ir_dir)
  : sensor_(sensor),
    sensor_data_(sensor_data),
    depth_camera_(depth_camera),
    color_camera_(color_camera),
    ir_camera_(ir_camera),
    depth_dir_(std::move(depth_dir)),
    color_dir_(std::move(color_dir)),
    ir_dir_(std::move(ir_dir)) {
  // nothing
}

bool Stream::HasDepth(Camera &camera, std::string &path) const {
  if (!depth_dir_.empty()) {
    camera = depth_camera_;
    path   = depth_dir_;
    return true;
  }
  else {
    return false;
  }
}

bool Stream::HasDepth(Camera &camera) const {
  std::string path;
  return HasDepth(camera, path);
}

bool Stream::HasDepth() const {
  Camera camera;
  return HasDepth(camera);
}

bool Stream::HasColor(Camera &camera, std::string &path) const {
  if (!color_dir_.empty()) {
    camera = color_camera_;
    path   = color_dir_;
    return true;
  }
  else {
    return false;
  }
}

bool Stream::HasColor(Camera &camera) const {
  std::string path;
  return HasColor(camera, path);
}

bool Stream::HasColor() const {
  Camera camera;
  return HasColor(camera);
}

bool Stream::HasIR(Camera &camera, std::string &path) const {
  if (!ir_dir_.empty()) {
    camera = ir_camera_;
    path   = ir_dir_;
    return true;
  }
  else {
    return false;
  }
}

bool Stream::HasIR() const {
  Camera camera;
  std::string path;
  return HasIR(camera, path);
}

} // namespace scanogram

//-----------------
//--- Scanogram ---
//-----------------

Scanogram::Scanogram()
 : age_(0), weight_(0), height_(0),
   scanner_(scanogram::ScannerType::FreeFusion) {
  // nothing
}

Scanogram::Scanogram(size_t age,
                     float weight,
                     float height,
                     const std::chrono::time_point<std::chrono::system_clock,
                                                   std::chrono::seconds> &date_time,
                     scanogram::ScannerType scanner,
                     scanogram::Consents &&consents,
                     scanogram::Tags &&tags,
                     std::unordered_set<scanogram::Garment> &&garments,
                     std::vector<scanogram::Stage> &&stages)
  : age_(age), weight_(weight), height_(height),
    date_time_(date_time),
    scanner_(scanner),
    consents_(consents),
    tags_(tags),
    garments_(std::move(garments)),
    stages_(std::move(stages)) {
  // nothing
}

bool Scanogram::HasAgeValue(size_t &age) const {
  if (age_ > 0) {
    age = age_;
    return true;
  }
  else {
    return false;
  }
}

bool Scanogram::HasWeightValue(float &weight) const {
  if (weight_ > 0.0f) {
    weight = weight_;
return true;
  }
  else {
  return false;
  }
}

bool Scanogram::HasHeightValue(float &height) const {
  if (height_ > 0.0f) {
    height = height_;
    return true;
  }
  else {
    return false;
  }
}

namespace {

ErrHandle WrongOrMissedSection(const std::string &where,
                               const tinyxml2::XMLElement *actual,
                               const std::string &expected) {
    std::ostringstream oss;
    if (actual == nullptr) {
      oss << "section named as '" << expected << "' is missing";
    }
    else {
      oss << "wrong name of the section ('" << actual->Name()
          << "' instead of '" << expected << "')";
    }
    return ErrHandle(where, oss.str());
}

ErrHandle WrongSectionContent(const std::string &where,
                              const tinyxml2::XMLElement *sect,
                              const ErrHandle &inner_error) {
  std::ostringstream oss;
  if (sect != nullptr) {
    oss << "section named as '" << sect->Name() << "' has invalid content";
  }
  else {
    oss << "internal error";
  }
  return ErrHandle(where, oss.str(), inner_error);
}

// A helper that extracts and parses optional values
template <class T>
ErrHandle ExtractValue(const std::unordered_map<std::string, std::string> &values,
                       const std::string &name,
                       bool &has_value, T &value_itself) {
  using namespace scanogram;
  ErrHandle err;

  auto iter = values.find(name);
  if (iter != values.end()) {
    if ((err = FromString(iter->second, value_itself)).Failed()) {
      std::ostringstream oss;
      oss << "failed to get value from the '" << name << "' section";
      return ErrHandle(TEXEL_WHERE, oss.str(), err);
    }
    has_value = true;
  }
  else {
    has_value = false;
  }

  return ErrHandle();
}

template <class T>
ErrHandle ExtractOptionalValue(const std::unordered_map<std::string, std::string> &values,
                               const std::string &name, T &value) {
  bool stub = false;
  auto err = ExtractValue(values, name, stub, value);
  if (err.Failed()) {
    err = ErrHandle(TEXEL_WHERE, "trace holder", err);
  }
  return err;
}

// Ensures that all requested attributes are presented and no unknown parameters are specified
ErrHandle CheckAttributes(const tinyxml2::XMLElement *sect,
                          const std::vector<std::string> &required_names,
                          std::unordered_map<std::string, std::string> &values) {
  using namespace tinyxml2;

  values.clear();
  std::unordered_map<std::string, size_t> refs;
  for (const auto &name : required_names) {
    refs[name] = 0;
  }

  const XMLAttribute *attr = sect->FirstAttribute();
  while (attr != nullptr) {
    auto iter = refs.find(attr->Name());
    if (iter == refs.end()) {
      std::ostringstream oss;
      oss << "met an unknown attribute ('" << attr->Name() << "')";
      return ErrHandle(TEXEL_WHERE, oss.str());
    }
    iter->second += 1;

    std::string attr_value;
    if (attr->Value() != nullptr) {
      attr_value = attr->Value();
    }
    values[attr->Name()] = attr_value;
    attr = attr->Next();
  }

  for (const auto &ref : refs) {
    if (ref.second != 1) {
      std::ostringstream oss;
      oss << "value for the required attribute is not provided ('" << ref.first << "')";
      return ErrHandle(TEXEL_WHERE, oss.str());
    }
  }

  return ErrHandle();
}

// Like 'CheckAttributes()', but checks sections and extracts values from the selected ones
// The 'bool' flag defines single/multiple occurrence
ErrHandle CheckSections(const tinyxml2::XMLElement *sect,
                        const std::unordered_map<std::string, bool> &allowed_names,
                        std::unordered_map<std::string, std::vector<std::string>> &values) {
  // Extract values
  const tinyxml2::XMLElement *child = sect->FirstChildElement();
  while (child != nullptr) {
    auto iter = allowed_names.find(child->Name());
    if (iter == allowed_names.end()) {
      std::ostringstream oss;
      oss << "section with the name '" << child->Name() << "' is not allowed here";
      auto err = ErrHandle(TEXEL_WHERE, oss.str());
      return WrongSectionContent(TEXEL_WHERE, sect, err);
    }
    std::string text;
    if (child->GetText() != nullptr) {
      text = child->GetText();
    }
    values[child->Name()].emplace_back(text);
    child = child->NextSiblingElement();
  }

  // Check that multiple occurrences do not violate the requirements
  for (const auto &value : values) {
    const auto iter = allowed_names.find(value.first);
    if (iter != allowed_names.cend() &&
        !iter->second &&
        value.second.size() > 1) {
      std::ostringstream oss;
      oss << "value with the name '" << value.first << "' cannot be declared multiple times";
      auto err = ErrHandle(TEXEL_WHERE, oss.str());
      return WrongSectionContent(TEXEL_WHERE, sect, err);
    }
  }
  return ErrHandle();
}

// A version that returns single value with such name instead of multiple ones
ErrHandle CheckSections(const tinyxml2::XMLElement *sect,
                        const std::unordered_map<std::string, bool> &allowed_names,
                        std::unordered_map<std::string, std::string> &values) {
  std::unordered_map<std::string, std::vector<std::string>> multiple_values;
  auto err = CheckSections(sect, allowed_names, multiple_values);
  if (err.Failed()) {
    return ErrHandle(TEXEL_WHERE, "trace holder", err);
  }

  for (const auto &rec : multiple_values) {
    if (!rec.second.empty()) {
      values.emplace(std::make_pair(rec.first, rec.second[0]));
    }
  }
  return ErrHandle();
}

// A version that ignores values but checks sections
ErrHandle CheckSections(const tinyxml2::XMLElement *sect,
                        const std::unordered_map<std::string, bool> &allowed_names) {
  std::unordered_map<std::string, std::vector<std::string>> tmp;
  auto err = CheckSections(sect, allowed_names, tmp);
  if (err.Failed()) {
    return ErrHandle(TEXEL_WHERE, "trace holder", err);
  }
  return ErrHandle();
}

ErrHandle ParseInvariantPersonInfo(const tinyxml2::XMLElement *sect,
                                   scanogram::Gender &gender,
                                   bool &has_name, std::string &name,
                                   bool &has_group, scanogram::AgeGroup &group) {
  using namespace tinyxml2;
  ErrHandle err;
  if (sect == nullptr || std::string("person") != sect->Name()) {
    return WrongOrMissedSection(TEXEL_WHERE, sect, "person");
  }

  // 'gender' is the required parameter
  std::unordered_map<std::string, std::string> attrs;
  if ((err = CheckAttributes(sect, { "gender" }, attrs)).Failed()) {
    return WrongSectionContent(TEXEL_WHERE, sect, err);
  }
  if ((err = FromString(attrs["gender"], gender)).Failed()) {
    return ErrHandle(TEXEL_WHERE, "failed to get person's gender", err);
  }

  // 'name' and 'group' are optional
  std::unordered_map<std::string, std::string> values;
  if ((err = CheckSections(sect,
                           { { "name", false }, { "group", false } },
                           values)).Failed()) {
    return WrongSectionContent(TEXEL_WHERE, sect, err);
  }
  
  if ((err = ExtractValue(values, "name", has_name, name)).Failed() ||
      (err = ExtractValue(values, "group", has_group, group)).Failed()) {
    return WrongSectionContent(TEXEL_WHERE, sect, err);
  }

  return ErrHandle();
}

ErrHandle ParseChangeablePersonInfo(const tinyxml2::XMLElement *sect,
                                    size_t &age, float &weight, float &height) {
  if (sect == nullptr || std::string(sect->Name()) != "person") {
    return WrongOrMissedSection(TEXEL_WHERE, sect, "person");
  }

  ErrHandle err;
  std::unordered_map<std::string, std::string> values;
  if ((err = CheckSections(sect,
                           { { "age", false }, { "weight", false }, { "height", false } },
                           values)).Failed()) {
    return WrongSectionContent(TEXEL_WHERE, sect, err);
  }

  if ((err = ExtractOptionalValue(values, "age", age)).Failed() ||
      (err = ExtractOptionalValue(values, "weight", weight)).Failed() ||
      (err = ExtractOptionalValue(values, "height", height)).Failed()) {
    return WrongSectionContent(TEXEL_WHERE, sect, err);
  }

  return ErrHandle();
}

ErrHandle ParseConsents(const tinyxml2::XMLElement *sect,
                        scanogram::Consents &consents) {
  if (sect == nullptr || (std::string(sect->Name())) != "consents") {
    return WrongOrMissedSection(TEXEL_WHERE, sect, "consents");
  }

  ErrHandle err;
  std::unordered_map<std::string, std::string> values;
  if ((err = CheckSections(sect, {
                             { "make_depth_maps_publicly_available", false },
                             { "make_color_frames_publicly_available", false },
                             { "make_scans_publicly_available", false },
                             { "do_not_blur_face", false },
                             { "commercial_use", false }
                           },
                           values)).Failed()) {
    return WrongSectionContent(TEXEL_WHERE, sect, err);
  }

  auto yes_or_no = [&values](std::string &&name, bool &value) -> ErrHandle {
    bool has_value = false;
    std::string str_value;
    ErrHandle err = ExtractValue(values, name, has_value, str_value);
    if (err.Failed()) {
      std::ostringstream oss;
      oss << "failed to find value '" << name << "'";
      return ErrHandle(TEXEL_WHERE, oss.str(), err);
    }
    if (has_value) {
      if (str_value == "yes") {
        value = true;
      }
      else if (str_value == "no") {
        value = false;
      }
      else {
        std::ostringstream oss;
        oss << "wrong value '" << str_value << "', only 'yes' and 'no' are supported";
        return ErrHandle(TEXEL_WHERE, oss.str());
      }
    }
    return ErrHandle();
  };

  if ((err = yes_or_no("make_depth_maps_publicly_available",
                       consents.make_depth_maps_publicly_available)).Failed() ||
      (err = yes_or_no("make_color_frames_publicly_available",
                       consents.make_color_frames_publicly_available)).Failed() ||
      (err = yes_or_no("make_scans_publicly_available",
                       consents.make_scans_publicly_available)).Failed() ||
      (err = yes_or_no("do_not_blur_face",
                       consents.do_not_blur_face)).Failed() ||
      (err = yes_or_no("commercial_use",
                       consents.commercial_use)).Failed()) {
    return WrongSectionContent(TEXEL_WHERE, sect, err);
  }

  return ErrHandle();
}

ErrHandle ParseTags(const tinyxml2::XMLElement *sect,
                    scanogram::Tags &tags) {
  if (sect == nullptr || std::string(sect->Name()) != "tags") {
    return WrongOrMissedSection(TEXEL_WHERE, sect, "tags");
  }

  ErrHandle err;
  std::unordered_map<std::string, std::string> values;
  if ((err = CheckSections(sect, {
                             { "hairstyle", false },
                             { "clothing", false },
                             { "shoes", false },
                             { "lighting", false },
                             { "placement", false }
                           },
                           values)).Failed()) {
    return WrongSectionContent(TEXEL_WHERE, sect, err);
  }

  if ((err = ExtractOptionalValue(values, "hairstyle", tags.hairstyle)).Failed() ||
      (err = ExtractOptionalValue(values, "clothing", tags.clothing)).Failed() ||
      (err = ExtractOptionalValue(values, "shoes", tags.shoes)).Failed() ||
      (err = ExtractOptionalValue(values, "lighting", tags.lighting)).Failed() ||
      (err = ExtractOptionalValue(values, "placement", tags.placement)).Failed()) {
    return WrongSectionContent(TEXEL_WHERE, sect, err);
  }

  return ErrHandle();
}

ErrHandle ParseGarments(const tinyxml2::XMLElement *sect,
                        std::unordered_set<scanogram::Garment> &garments) {
  if (sect == nullptr || std::string(sect->Name()) != "garments") {
    return WrongOrMissedSection(TEXEL_WHERE, sect, "garments");
  }

  ErrHandle err;
  std::unordered_map<std::string, std::vector<std::string> > values;
  if ((err = CheckSections(sect, { { "item", true } },
                           values)).Failed()) {
    return WrongSectionContent(TEXEL_WHERE, sect, err);
  }

  std::vector<std::string> items = values["item"];
  for (const auto &item : items) {
    ErrHandle err;
    scanogram::Garment garment;
    if ((err = FromString(item, garment)).Failed()) {
      return WrongSectionContent(TEXEL_WHERE, sect, err);
    }
    garments.emplace(garment);
  }
  return ErrHandle();
}

ErrHandle ParseCamera(const tinyxml2::XMLElement *sect,
                      Camera &camera, std::string &path) {
  if (sect == nullptr ||
      (std::string("depth") != sect->Name() &&
       std::string("color") != sect->Name() &&
       std::string("ir") != sect->Name())) {
    return WrongOrMissedSection(TEXEL_WHERE, sect, "depth|color|ir");
  }

  // Common parameters: directory with frames, their width and height
  ErrHandle err;
  std::unordered_map<std::string, std::string> values;
  size_t width = 0, height = 0;
  if ((err = CheckAttributes(sect, { "path", "width", "height" }, values)).Failed() ||
      (err = FromString(values["width"], width)).Failed() ||
      (err = FromString(values["height"], height)).Failed()) {
    return WrongSectionContent(TEXEL_WHERE, sect, err);
  }
  path = values["path"];

  if ((err = CheckSections(sect, {
                             { "intrinsics", false },
                             { "extrinsics", false }
                           })).Failed()) {
    return WrongSectionContent(TEXEL_WHERE, sect, err);
  }

  // Section with intrinsics
  auto intrinsics = sect->FirstChildElement("intrinsics");
  if (intrinsics == nullptr) {
    err = ErrHandle(TEXEL_WHERE, "section with camera's intrinsics is missed");
    return WrongSectionContent(TEXEL_WHERE, sect, err);
  }
  
  values.clear();
  float cx = 0.0f, cy = 0.0f, fx = 0.0f, fy = 0.0f;
  if ((err = CheckAttributes(intrinsics, { "cx", "cy", "fx", "fy" }, values)).Failed() ||
      (err = FromString(values["cx"], cx)).Failed(),
      (err = FromString(values["cy"], cy)).Failed(),
      (err = FromString(values["fx"], fx)).Failed(),
      (err = FromString(values["fy"], fy)).Failed()) {
    return WrongSectionContent(TEXEL_WHERE, intrinsics, err);
  }
  
  // Section with extrinsics
  auto extrinsics = sect->FirstChildElement("extrinsics");
  if (extrinsics == nullptr) {
    err = ErrHandle(TEXEL_WHERE, "section with camera's extrinsics is missed");
    return WrongSectionContent(TEXEL_WHERE, sect, err);
  }
  values.clear();

  glm::vec3 offset{};
  glm::mat3x3 rotation{};
  if ((err = CheckAttributes(extrinsics, {
                               "rot11", "rot12", "rot13",
                               "rot21", "rot22", "rot23", 
                               "rot31", "rot32", "rot33",
                               "trans1", "trans2", "trans3"
                             }, values)).Failed() ||
      (err = FromString(values["rot11"], rotation[0].x)).Failed() ||
      (err = FromString(values["rot12"], rotation[0].y)).Failed() || 
      (err = FromString(values["rot13"], rotation[0].z)).Failed() ||
      (err = FromString(values["rot21"], rotation[1].x)).Failed() ||
      (err = FromString(values["rot22"], rotation[1].y)).Failed() ||
      (err = FromString(values["rot23"], rotation[1].z)).Failed() || 
      (err = FromString(values["rot31"], rotation[2].x)).Failed() ||
      (err = FromString(values["rot32"], rotation[2].y)).Failed() ||
      (err = FromString(values["rot33"], rotation[2].z)).Failed() ||
      (err = FromString(values["trans1"], offset.x)).Failed() ||
      (err = FromString(values["trans2"], offset.y)).Failed() || 
      (err = FromString(values["trans3"], offset.z)).Failed()) {
    return WrongSectionContent(TEXEL_WHERE, extrinsics, err);
  }

  camera = Camera(width, height, cx, cy, fx, fy, offset, rotation);
  return ErrHandle();
}

} // unnamed namespace

ErrHandle Scanogram::ParseStream(const tinyxml2::XMLElement *stream_sect,
                                 const std::string &parent_dir,
                                 scanogram::Stream &stream) {
  ErrHandle err;

  // Check name and child sections, extract information about the sensor
  if (stream_sect == nullptr || std::string("stream") != stream_sect->Name()) {
    return WrongOrMissedSection(TEXEL_WHERE, stream_sect, "stream");
  }
  if ((err = CheckSections(stream_sect, {
                             { "depth", false },
                             { "color", false },
                             { "intensity", false }
                           })).Failed()) {
    return WrongSectionContent(TEXEL_WHERE, stream_sect, err);
  }

  std::unordered_map<std::string, std::string> values;
  if ((err = CheckAttributes(stream_sect, { "sensor", "sensor_data" }, values)).Failed()) {
    return WrongSectionContent(TEXEL_WHERE, stream_sect, err);
  }

  scanogram::SensorType sensor(scanogram::SensorType::Syntethic);
  std::string sensor_data = values["sensor_data"];
  if ((err = FromString(values["sensor"], sensor)).Failed()) {
    return WrongSectionContent(TEXEL_WHERE, stream_sect, err);
  }

  // Read information about each camera
  auto extend_path = [&parent_dir](const std::string &path) -> auto {
    return std::filesystem::absolute(std::filesystem::path(parent_dir) / path).string();
  };

  Camera depth_camera, color_camera, ir_camera;
  std::string depth_path, color_path, ir_path;
  {
    auto depth_sect = stream_sect->FirstChildElement("depth");
    if (depth_sect != nullptr) {
      if ((err = ParseCamera(depth_sect, depth_camera, depth_path)).Failed()) {
        return WrongSectionContent(TEXEL_WHERE, depth_sect, err);
      }
      depth_path = extend_path(depth_path);
    }

    auto color_sect = stream_sect->FirstChildElement("color");
    if (color_sect != nullptr) {
      if ((err = ParseCamera(color_sect, color_camera, color_path)).Failed()) {
        return WrongSectionContent(TEXEL_WHERE, color_sect, err);
      }
      color_path = extend_path(color_path);
    }

    auto ir_sect = stream_sect->FirstChildElement("ir");
    if (ir_sect != nullptr) {
      if ((err = ParseCamera(ir_sect, ir_camera, ir_path)).Failed()) {
        return WrongSectionContent(TEXEL_WHERE, ir_sect, err);
      }
      ir_path = extend_path(ir_path);
    }

    if (depth_sect == nullptr && color_sect == nullptr && ir_sect == nullptr) {
      err = ErrHandle(TEXEL_WHERE, "at least one section with camera parameters must be provided");
      return WrongSectionContent(TEXEL_WHERE, stream_sect, err);
    }
  }

  stream = std::move(scanogram::Stream(sensor, sensor_data,
                                       depth_camera, std::move(depth_path),
                                       color_camera, std::move(color_path),
                                       ir_camera, std::move(ir_path)));
  return ErrHandle();
}

ErrHandle Scanogram::ParseStage(const tinyxml2::XMLElement *stage_sect,
                                const std::string &parent_dir,
                                scanogram::Stage &stage) {
  ErrHandle err;
  using namespace scanogram;

  // Check name, extract the type of the current pass and verify sections
  if (stage_sect == nullptr || std::string("stage") != stage_sect->Name()) {
    return WrongOrMissedSection(TEXEL_WHERE, stage_sect, "stage");
  }

  std::unordered_map<std::string, std::string> values;
  if ((err = CheckAttributes(stage_sect, { "pass" }, values)).Failed()) {
    return WrongSectionContent(TEXEL_WHERE, stage_sect, err);
  }
  
  ScanPass pass = ScanPass::Body;
  if ((err = FromString(values["pass"], pass)).Failed()) {
    return WrongSectionContent(TEXEL_WHERE, stage_sect, err);
  }

  if ((err = CheckSections(stage_sect, {
                             { "bounding_box", false },
                             { "stream", true }
                           })).Failed()) {
    return WrongSectionContent(TEXEL_WHERE, stage_sect, err);
  }

  // The bounding box is the necessary information
  auto bbox_sect = stage_sect->FirstChildElement("bounding_box");
  if (bbox_sect == nullptr) {
    return WrongOrMissedSection(TEXEL_WHERE, bbox_sect, "bounding_box");
  }
  values.clear();
  if ((err = CheckAttributes(bbox_sect, {
                               "min_x", "min_y", "min_z",
                               "max_x", "max_y", "max_z"
                             }, values)).Failed()) {
    return WrongSectionContent(TEXEL_WHERE, stage_sect, err);
  }

  glm::vec3 offset{}, size{};
  if ((err = FromString(values["min_x"], offset.x)).Failed() ||
      (err = FromString(values["min_y"], offset.y)).Failed() ||
      (err = FromString(values["min_z"], offset.z)).Failed() ||
      (err = FromString(values["max_x"], size.x)).Failed() ||
      (err = FromString(values["max_y"], size.y)).Failed() ||
      (err = FromString(values["max_z"], size.z)).Failed()) {
    return WrongSectionContent(TEXEL_WHERE, stage_sect, err);
  }
  BoundingBox bbox(offset, size - offset);

  // Get information about each video stream
  std::vector<Stream> streams;
  {
    auto stream_sect = stage_sect->FirstChildElement("stream");
    if (stream_sect == nullptr) {
      return WrongOrMissedSection(TEXEL_WHERE, stream_sect, "stream");
    }

    while (stream_sect != nullptr) {
      Stream stream;
      if ((err = ParseStream(stream_sect, parent_dir, stream)).Failed()) {
        return WrongSectionContent(TEXEL_WHERE, stage_sect, err);
      }
      streams.emplace_back(std::move(stream));
      stream_sect = stream_sect->NextSiblingElement("stream");
    }
  }

  stage = std::move(Stage(pass, bbox, std::move(streams)));
  return ErrHandle();
}

ErrHandle Scanogram::ParseScan(const tinyxml2::XMLElement *scan_sect,
                               const std::string &parent_dir,
                               Scanogram &scanogram) {
  ErrHandle err;

  // Check the section header and extract the required values ('scanner', 'date')
  if (scan_sect == nullptr || std::string("scan") != scan_sect->Name()) {
    return WrongOrMissedSection(TEXEL_WHERE, scan_sect, "scan");
  }

  std::unordered_map<std::string, std::string> values;
  if ((err = CheckAttributes(scan_sect, { "scanner", "date" }, values)).Failed()) {
    return WrongSectionContent(TEXEL_WHERE, scan_sect, err);
  }

  scanogram::ScannerType scanner;
  if ((err = FromString(values["scanner"], scanner)).Failed()) {
    return ErrHandle(TEXEL_WHERE, "failed to get the scanner version");
  }
  std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds> date_time;
  {
    std::istringstream iss(values["date"]);
    if (!(iss >> date::parse("%FT%TZ", date_time))) {
      std::ostringstream oss;
      oss << "the 'date' library failed to parse time ('" << values["date"] << "'), "
          << "the ISO-8601 format is expected";
      err = ErrHandle(TEXEL_WHERE, oss.str());
      return WrongSectionContent(TEXEL_WHERE, scan_sect, err);
    }
  }

  // Read additional information about the person and their consents
  std::unordered_map<std::string, std::string> stub;
  if ((err = CheckSections(scan_sect,
                          { { "person", false }, { "consents", false },
                            { "tags", false }, { "garments", false }, { "stage", true } },
                            stub)).Failed()) {
    return WrongSectionContent(TEXEL_WHERE, scan_sect, err);
  }

  // Some variable information about the person
  size_t age = 0;
  float weight = 0.0f, height = 0.0f;
  {
    auto person_sect = scan_sect->FirstChildElement("person");
    if (person_sect != nullptr) {
      if ((err = ParseChangeablePersonInfo(person_sect, age,
                                           weight, height)).Failed()) {
        return WrongSectionContent(TEXEL_WHERE, scan_sect, err);
      }
    }
  }

  // Information about consents
  scanogram::Consents consents;
  {
    auto consents_sect = scan_sect->FirstChildElement("consents");
    if (consents_sect != nullptr) {
      if ((err = ParseConsents(consents_sect, consents)).Failed()) {
        return WrongSectionContent(TEXEL_WHERE, scan_sect, err);
      }
    }
  }

  // Extract optional tags
  scanogram::Tags tags;
  {
    auto tags_sect = scan_sect->FirstChildElement("tags");
    if (tags_sect != nullptr) {
      if ((err = ParseTags(tags_sect, tags)).Failed()) {
        return WrongSectionContent(TEXEL_WHERE, scan_sect, err);
      }
    }
  }

  // Extract the list of markup'ed garments
  std::unordered_set<scanogram::Garment> garments;
  {
    auto garments_sect = scan_sect->FirstChildElement("garments");
    if (garments_sect != nullptr) {
      if ((err = ParseGarments(garments_sect, garments)).Failed()) {
        return WrongSectionContent(TEXEL_WHERE, scan_sect, err);
      }
    }
  }

  // Finally, load information about each scanning stage
  std::vector<scanogram::Stage> stages;
  {
    auto stage_sect = scan_sect->FirstChildElement("stage");
    if (stage_sect == nullptr) {
      return WrongOrMissedSection(TEXEL_WHERE, scan_sect, "stage");
    }
    while (stage_sect != nullptr) {
      scanogram::Stage stage;
      if ((err = ParseStage(stage_sect, parent_dir, stage)).Failed()) {
        return WrongSectionContent(TEXEL_WHERE, scan_sect, err);
      }
      stages.emplace_back(std::move(stage));
      stage_sect = stage_sect->NextSiblingElement("stage");
    }
  }
  
  scanogram = std::move(Scanogram(age, weight, height, date_time, scanner,
                                  std::move(consents), std::move(tags),
                                  std::move(garments), std::move(stages)));

  return ErrHandle();
}

ErrHandle Scanogram::Load(const std::string &filename,
                          scanogram::Gender &gender,
                          std::string &name,
                          scanogram::AgeGroup &group,
                          std::vector<Scanogram> &scanograms) {
  using namespace tinyxml2;
  ErrHandle err;
  auto append_filename = [&filename](const std::string &where,
                                     const ErrHandle &inner) -> ErrHandle {
    std::stringstream ss;
    ss << "some errors were found when parsing a file ('" << filename << "')";
    return ErrHandle(where, ss.str(), inner);
  };

  // Parse and locate the root element
  std::ifstream xml_stream(filename);
  if (!xml_stream.good()) {
    err = ErrHandle(TEXEL_WHERE, "failed to open a file with scanograms");
    return append_filename(TEXEL_WHERE, err);
  }

  std::string xml;
  {
    std::ostringstream oss;
    oss << xml_stream.rdbuf();
    xml = oss.str();
  }

  XMLDocument doc;
  XMLElement *root = nullptr;
  {
    if (doc.Parse(xml.c_str()) != XML_SUCCESS ||
        (root = doc.RootElement()) == nullptr) {
      err = ErrHandle(TEXEL_WHERE, "failed to recognize XML-based project format");
      return append_filename(TEXEL_WHERE, err);
    }
    if (std::string("texel") != root->Name()) {
      err = WrongOrMissedSection(TEXEL_WHERE, root, "texel");
      return append_filename(TEXEL_WHERE, err);
    }
  }
  std::unordered_map<std::string, std::string> stub;
  if ((err = CheckSections(root, { { "person", false }, { "scan", true } }, stub)).Failed()) {
    err = WrongSectionContent(TEXEL_WHERE, root, err);
    return append_filename(TEXEL_WHERE, err);
  }

  // Read details about the person
  auto person = root->FirstChildElement("person");
  bool has_name = false, has_group = false;
  if (person != nullptr) {
    if ((err = ParseInvariantPersonInfo(person, gender,
                                        has_name, name,
                                        has_group, group)).Failed()) {
      err = WrongSectionContent(TEXEL_WHERE, person, err);
      return append_filename(TEXEL_WHERE, err);
    }
  }
  if (!has_name) {
    name = "NA";
  }
  if (!has_group) {
    group = scanogram::AgeGroup::NA;
  }

  // Process each pre-recorded scanogram
  auto parent_scan = std::filesystem::path(filename).parent_path().string();
  auto scan = root->FirstChildElement("scan");
  while (scan != nullptr) {
    Scanogram scanogram;
    if ((err = ParseScan(scan, parent_scan, scanogram)).Failed()) {
      err = WrongSectionContent(TEXEL_WHERE, root, err);
      return append_filename(TEXEL_WHERE, err);
    }
    scanograms.emplace_back(std::move(scanogram));    
    scan = scan->NextSiblingElement("scan");
  };
  if (scanograms.empty()) {
    err = ErrHandle(TEXEL_WHERE, "at least one scanogram must be provided");
    return append_filename(TEXEL_WHERE, err);
  }
  
  return ErrHandle();
}

} // namespace texel
