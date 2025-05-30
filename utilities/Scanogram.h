#pragma once
#include "Defs.h"

namespace texel {

// Definition of the use class
class Scanogram;

namespace scanogram {

// This value is essential for the algorithm and affects the results
enum class Gender {
  // Due to some reasons, the actual gender was not specified
  // E.g., a scan that was performed fully automatically
  Neutral,

  // A shape of man is expected
  Male,

  // A shape of woman is expected
  Female
};
ErrHandle FromString(const std::string &str, scanogram::Gender &value);
std::string ToString(scanogram::Gender gender);
std::string ToUserFriendly(scanogram::Gender gender);


// How can we describe the scanned person?
enum class AgeGroup {
  // The corresponding field was left empty or
  // the person forbade to share information of this type
  NA,

  // The person was definitely considered as a child
  // E.g. under 14 years old or something like this
  Child,

  // The person is a grown teenager or just an adult
  Adult,

  // The person that has retired
  Elderly
};
ErrHandle FromString(const std::string &str, scanogram::AgeGroup &value);
std::string ToString(scanogram::AgeGroup group);
std::string ToUserFriendly(scanogram::AgeGroup group);


// The exact model of TEXEL's scanner that was used to create the scannogramm
enum class ScannerType {
  // A rotating platform for the person and multiple RGBD sensors around
  PortalMX,

  // A rotating column with multiple RGBD sensors, the person theirselves is static
  PortalRX,

  // The person turns around a single static sensor
  FreeFusion
};
ErrHandle FromString(const std::string &str, scanogram::ScannerType &value);
std::string ToString(scanogram::ScannerType type);
std::string ToUserFriendly(scanogram::ScannerType type);


// Type of a sensor that was used to record the video stream
enum class SensorType {
  // The data were synthetically prepared using software rander
  Syntethic,

  // Microsoft Azure Kinect DK
  AzureKinect
};
ErrHandle FromString(const std::string &str, scanogram::SensorType &value);
std::string ToString(scanogram::SensorType type);
std::string ToUserFriendly(scanogram::SensorType type);


// How would we classify person's hair?
enum class Hairstyle {
  // The corresponding field was left empty or
  // the person forbade to share information of this type
  NA,

  // Hair is almost invisible and can be considered as a static object (a part of the head)
  Shaved,

  // Hair is observable but short enough
  // Its movement cannot be ignored and must be considered as non-rigid object
  ShortHaircut,

  // Really long hair that is the essential part of person's style
  LongHaircut,

  // Cannot identify the hairstyle because it was hidden by a hat
  Hat
};
ErrHandle FromString(const std::string &str, scanogram::Hairstyle &value);
std::string ToString(scanogram::Hairstyle style);
std::string ToUserFriendly(scanogram::Hairstyle style);


// How would we describe person's style?
enum class Clothing {
  // The corresponding field was left empty or
  // the person forbade to share information of this type
  NA,

  // The person is naked or wearing only underclothes
  Underwear,

  // Only tight-fitting clothes are presented, they do not affect the shape of the person
  Tight,

  // A regular person from an office or street: their figure is slightly hidden, but
  // our parametric model describes them quite well
  Casual,

  // The person wears wide/large clothes, we cannot predict their actual shape
  Oversize,

  // Some winter clothing or garments designed to retain their own shape
  Outerwear
};
ErrHandle FromString(const std::string &str, scanogram::Clothing &value);
std::string ToString(scanogram::Clothing style);
std::string ToUserFriendly(scanogram::Clothing style);


// How would we classify what the person is wearing?
enum class Shoes {
  // The corresponding field was left empty or
  // the person forbade to share information of this type
  NA,

  // The person is naked or wearing only socks
  Barefoot,

  // Some kind of light shoes that do not significantly affect person's height
  FlatBoots,

  // Shoes with a clearly visible heel that adds more than a few cm to person's height
  HeeledBoots
};
ErrHandle FromString(const std::string &str, scanogram::Shoes &value);
std::string ToString(scanogram::Shoes type);
std::string ToUserFriendly(scanogram::Shoes type);


// In what environment was the scanogram made?
enum class Lighting {
  // The corresponding field was left empty or
  // the person forbade to share information of this type
  NA,

  // Not enough light to determine the true tone of clothes/skin
  Dim,

  // Scanogram was made with the enabled built-in backlight
  // Otherwise, good external lamps are ok too
  Normal,

  // The lighting is too bright, color frames are overexposed
  Bright
};
ErrHandle FromString(const std::string &str, scanogram::Lighting &value);
std::string ToString(scanogram::Lighting type);
std::string ToUserFriendly(scanogram::Lighting type);


// Where was the scanogram made?
enum class Placement {
  // The corresponding field was left empty or
  // the person forbade to share information of this type
  NA,

  // The person was scanned in some room or pavilion with a roof
  Indoor,

  // The person was scanned on open air
  Outdoor
};
ErrHandle FromString(const std::string &str, scanogram::Placement &value);
std::string ToString(scanogram::Placement type);
std::string ToUserFriendly(scanogram::Placement type);


// A set of tags that describe a particular clothing
// Each tag is optional, its meaning may vary
enum class Garment {
  Jeans,
  Trousers,
  Skirt,
  Shorts,
  SportsTrouser,

  Shirt,
  TShirt,
  LongSleeve,
  Blazer,
  Pullover,
  Hoodie,
  PoloNeck,
  TankTop,
  Vest,
  Dress,

  Cap,
  Hat,
  CowboyHat,
  HeadScarf,
  Headset,

  Jacket,
  DownJacket,
  Coat,
  Cloak,

  Boots,
  Sandals,
  Sneakers,
  HighBoots,
  HeeledShoes,

  Glasses,
  SunGlasses,

  Scarf,
  Gloves,
  Tie
};
ErrHandle FromString(const std::string &str, scanogram::Garment &value);
std::string ToString(scanogram::Garment type);
std::string ToUserFriendly(scanogram::Garment type);


// If the scanner supports multiple passes, this enum helps us to differ them
enum class ScanPass {
  // The main pass, the whole body is visible
  Body,

  // Only head and shoulders were scanned
  Head
};
ErrHandle FromString(const std::string &str, scanogram::ScanPass &value);
std::string ToString(scanogram::ScanPass type);
std::string ToUserFriendly(scanogram::ScanPass type);


// The person can allow or deny the use of their biometric data
// TEXEL respects their choice and their privacy
struct Consents {
  // It is ok to share raw depth maps
  bool make_depth_maps_publicly_available;

  // It is ok to share raw color frames
  bool make_color_frames_publicly_available;

  // The final surfaces can be shared
  bool make_scans_publicly_available;

  // If the materials are going to be use outside TEXEL,
  // the person allows us to leave their face unblurred
  // Otherwise, we must protect their privacy
  bool do_not_blur_face;

  // The person allowed TEXEL (and TEXEL only!) to use their biometric data for commercial purposes
  // Otherwise, this data will only be included in research data-sets
  bool commercial_use;

  Consents()
    : make_depth_maps_publicly_available(false),
      make_color_frames_publicly_available(false),
      make_scans_publicly_available(false),
      do_not_blur_face(false),
      commercial_use(false) {
  }
};


// Some basic markup for this scanogram
struct Tags {
  Hairstyle hairstyle;
  Clothing clothing;
  Shoes shoes;
  Lighting lighting;
  Placement placement;

  Tags()
    : hairstyle(Hairstyle::NA),
      clothing(Clothing::NA),
      shoes(Shoes::NA),
      lighting(Lighting::NA),
      placement(Placement::NA) {
  }
};


// A series of sequential frames or depth maps or both from a single sensor
// The actual data is still stored on the disk in a separate directory
class Stream {
  public:
    Stream(const Stream &) noexcept = default;
    Stream(Stream &&) noexcept = default;
    Stream &operator =(const Stream &) noexcept = default;
    Stream &operator =(Stream &&) noexcept = default;

    // The sensor iteslf
    SensorType Sensor() const { return sensor_; }

    // Scanners may provide additional information about the sensors used
    // For example, a hint for ICP or an internal identifier
    const std::string &SensorData() const { return sensor_data_; }

    // If this stream contains depth maps,
    // provides camera parameters and the relative path to a directory with data
    bool HasDepth(Camera &camera, std::string &path) const;

    // If this stream contains depth maps, provides camera parameters
    bool HasDepth(Camera &camera) const;

    // Only checks the existance of depth maps
    bool HasDepth() const;

    // If this stream contains color frames,
    // provides camera parameters and the relative path to a directory with data
    bool HasColor(Camera &camera, std::string &path) const;

    // If this stream contains color frames, provides camera parameters
    bool HasColor(Camera &camera) const;

    // Only checks the existance of color frames
    bool HasColor() const;

    // If this stream contains IR frames,
    // provides camera parameters and the relative path to a directory with data
    bool HasIR(Camera &camera, std::string &path) const;

    // Only checks the existance of IR frames
    bool HasIR() const;

  private:
    Stream() : sensor_(SensorType::AzureKinect) { }
    Stream(SensorType sensor, std::string sensor_data,
           const Camera &depth_camera, std::string &&depth_dir,
           const Camera &color_camera, std::string &&color_dir,
           const Camera &ir_camera, std::string &&ir_dir);

    SensorType sensor_;
    std::string sensor_data_;
    Camera depth_camera_, color_camera_, ir_camera_;
    std::string depth_dir_, color_dir_, ir_dir_;

  friend class texel::Scanogram;
};


// Information of one scanning stage (body, head, etc)
class Stage {
  public:
    Stage(const Stage &) noexcept = default;
    Stage(Stage &&stage) noexcept = default;
    Stage &operator =(const Stage &) noexcept = default;
    Stage &operator =(Stage &&stage) noexcept = default;

    // What part of the person is being scanned?
    ScanPass Pass() const { return pass_; }

    // Bounding box for the region with a person
    const texel::BoundingBox BoundingBox() const { return bbox_; }

    // Pre-recorded streams from each sensor
    const std::vector<Stream> &Streams() const { return streams_; }

  private:
    Stage() : pass_(ScanPass::Body) { }
    Stage(ScanPass pass,
          texel::BoundingBox bbox,
          std::vector<Stream> &&streams)
      : pass_(pass), bbox_(bbox), streams_(std::move(streams)) {
    }

    ScanPass pass_;
    texel::BoundingBox bbox_;
    std::vector<Stream> streams_;

  friend class texel::Scanogram;
};

} // namespace scanogram


// A container that provides information about some pre-recorded scan
// It does not contain any actual data, just descriptions for the related folders
class Scanogram {
  public:
    Scanogram();
    Scanogram(const Scanogram &) noexcept = default;
    Scanogram(Scanogram &&) noexcept = default;
    Scanogram &operator =(const Scanogram &) noexcept = default;
    Scanogram &operator =(Scanogram &&) noexcept = default;

    // Person's age (optional) 
    bool HasAgeValue(size_t &age) const;

    // Person's weight (optional)
    bool HasWeightValue(float &weight) const;

    // Person's height (optional)
    bool HasHeightValue(float &height) const;

    // What scanner was used to create this scanogram?
    scanogram::ScannerType Scanner() const { return scanner_; }

    // A string-based representation for the moment, when this scanogram was made
    std::chrono::time_point<std::chrono::system_clock,
                            std::chrono::seconds> DateTime() const { return date_time_; }

    // Person consent to share the following biometric data
    const scanogram::Consents &Consents() const { return consents_; }

    // The list of tags that markup the current scanogram
    const scanogram::Tags &Tags() const { return tags_; }

    // The set of garments the person was wearing
    const std::unordered_set<scanogram::Garment> &Garments() const { return garments_; }

    // Information about all stages of scanning
    const std::vector<scanogram::Stage> &Stages() const { return stages_; }

    // Loads scanograms from our XML-based project file
    // The project provides information about only one person but may contain multiple scanograms
    static ErrHandle Load(const std::string &filename,
                          scanogram::Gender &gender,
                          std::string &name,
                          scanogram::AgeGroup &group,
                          std::vector<Scanogram> &scanograms);

  private:
    Scanogram(size_t age,
              float weight,
              float height,
              const std::chrono::time_point<std::chrono::system_clock,
                                            std::chrono::seconds> &date_time,
              scanogram::ScannerType scanner,
              scanogram::Consents &&consents,
              scanogram::Tags &&tags,
              std::unordered_set<scanogram::Garment> &&garments,
              std::vector<scanogram::Stage> &&stages);
    
    static ErrHandle ParseStream(const tinyxml2::XMLElement *stream_sect,
                                 const std::string &parent_dir,
                                 scanogram::Stream &stream);

    static ErrHandle ParseStage(const tinyxml2::XMLElement *stage_sect,
                                const std::string &parent_dir,
                                scanogram::Stage &stage);

    static ErrHandle ParseScan(const tinyxml2::XMLElement *scan_sect,
                               const std::string &parent_dir,
                               Scanogram &scanogram);

    size_t age_;
    float weight_, height_;
    std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds> date_time_;
    scanogram::ScannerType scanner_;
    scanogram::Consents consents_;
    scanogram::Tags tags_;
    std::unordered_set<scanogram::Garment> garments_;
    std::vector<scanogram::Stage> stages_;
};

} // namespace texel
