#include <iostream>
#include "Scanogram.h"
#include "ScanogramFinder.h"

using namespace texel;

// Each RGB-D frame is presented as .png + .jpg files
// We just need to count the files to get the total number of frames
size_t CountFiles(const std::filesystem::path &dir, const std::string &extension) {
  size_t count{};
  for (const auto &entry : std::filesystem::directory_iterator(dir)) {
    if (entry.path().extension() == extension) {
      count += 1;
    }
  }
  return count;
};

// Instead of real processing, print all available information about the scan
void ProcessScan(const scan_finder::ScanInfo &info) {

  // First line: the almost unique identifier
  std::cout << std::endl;
  std::cout << "'" << info.id << "': " << std::endl;
        
  // Second line: some basic information about the person (gender, age, etc)
  std::cout << "  ";
  if (info.name != "NA") {
    std::cout << info.name << " (" << ToUserFriendly(info.gender) << ")";
  }
  else {
    std::cout << ToUserFriendly(info.gender);
  }
  std::cout << ": " << ToUserFriendly(info.group);
  size_t age = 0;
  if (info.scan.HasAgeValue(age)) {
    std::cout << ", " << age << " years old";
  }
  float height = 0.0f, weight = 0.0f;
  if (info.scan.HasHeightValue(height)) {
    std::cout << ", " << height << " cm";
  }
  if (info.scan.HasWeightValue(weight)) {
    std::cout << ", " << weight << " kg";
  }
  std::cout << std::endl;

  // Third line: what does the person look like
  decltype(auto) tags = info.scan.Tags();
  std::cout << "  Appearance: "
            << ToUserFriendly(tags.hairstyle) << ", "
            << ToUserFriendly(tags.clothing) << ", "
            << ToUserFriendly(tags.shoes);
  std::cout << std::endl;

  // Fourth line: basic information about the scanner
  std::cout << "  " << ToUserFriendly(info.scan.Scanner());
  if (info.scan.Stages().size() == 1 &&
      info.scan.Stages()[0].Streams().size() == 1) {
    decltype(auto) stream = info.scan.Stages()[0].Streams()[0];
    std::cout << " (" << ToUserFriendly(stream.Sensor()) << "): ";

    Camera camera;
    std::string frame_dir;
    if (stream.HasDepth(camera, frame_dir)) {
      std::cout << "depth " << camera.Width() << "x" << camera.Height()
                << " (" << CountFiles(frame_dir, ".png") << " frames)";
    }
    else {
      std::cout << "no depth maps";
    }

    if (stream.HasColor(camera, frame_dir)) {
      std::cout << ", color " << camera.Width() << "x" << camera.Height()
                << " (" << CountFiles(frame_dir, ".jpg") << " frames)";
    }
    else {
      std::cout << ", no color frames";
    }
    if (tags.placement != scanogram::Placement::NA) {
      std::cout << ", " << ToUserFriendly(tags.placement);
    }
  }

  std::cout << std::endl << std::endl;
  std::cout.flush();
}

ErrHandle IterateScans(const std::filesystem::path &dir,
                       size_t &n_men, size_t &n_women) {
  // Search for all files with the '.scan.xml' extension
  // Store their paths somewhere in memory
  ScanogramFinder finder;
  TEXEL_CHECK(finder.BindDirectory(dir.string()));

  // For each such scan, parse its XML-based annotations and process somehow
  while (finder.FindNext()) {
    decltype(auto) info = finder.Current();
    ProcessScan(info);

    switch (info.gender) {
      case scanogram::Gender::Male:
        n_men += 1;
        break;

      case scanogram::Gender::Female:
        n_women += 1;
        break;

      case scanogram::Gender::Neutral:
      default:
        // Sorry! In my country, only two genders exist
        break;
    }
  }

  return ErrHandle();
}

int main(int argc, char **argv) {
  if (argc > 2) {
    std::cerr << "Wrong arguments, use as './IterateScans <path_to_directory_with_scans>'" << std::endl;
    return 0;
  }
  auto dir = argc == 2 ? argv[1] : std::filesystem::current_path();

  size_t n_men{}, n_women{};
  auto err = IterateScans(dir, n_men, n_women);
  if (err.Failed()) {
    std::cerr << "Failed to iterate scans from the '" << dir.string() << "' directory:" << std::endl;
    std::cerr << err.Message();
  }
  std::cout << "Found information about " << n_men + n_women
            << " scans (" << n_men << " men, " << n_women << " women)" << std::endl;
  return 0;
}
