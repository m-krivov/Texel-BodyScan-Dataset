#include "ScanogramFinder.h"

namespace texel {

namespace {

bool HasScanXmlExtension(const std::string &filename) {
  std::string scan_xml(".scan.xml");
  return filename.size() >= scan_xml.size() &&
         filename.substr(filename.size() - scan_xml.size(), scan_xml.size()) == scan_xml;
}

std::string PathToIdentifier(const std::filesystem::path &params) {
  std::stringstream id;
  bool need_separator = false;
  for (const auto &token : params) {
    auto str = token.string();

    // Skip uninformative elements from the path
    if (str == "/" || str == "\\" || str == "." || str == ".." ||
        str == "Scans") {
      continue;
    }

    // Check for Windows' absolute path
    if (str.find(":") != std::string::npos) {
      str.erase(str.find(":"), 1);
    }

    // Skip the default filename
    if (str == "person.scan.xml" ||
        str == "Person.scan.xml") {
      continue;
    }

    // Remove our default extension
    if (HasScanXmlExtension(str)) {
      str = str.substr(0, str.size() - std::string(".scan.xml").size());
    }

    // Combine tokens into some identifier
    if (need_separator) {
      id << "_";
    }
    need_separator = true;
    id << str;
  }

  auto string_id = id.str();
  return string_id.empty() ? "scan" : string_id;
}

ErrHandle PopulateScans(const std::string &filename,
                        std::vector<scan_finder::ScanInfo> &scans) {
  std::string name;
  scanogram::Gender gender = scanogram::Gender::Neutral;
  scanogram::AgeGroup group = scanogram::AgeGroup::NA;
  std::vector<Scanogram> new_scans;
  auto err = Scanogram::Load(filename, gender, name, group, new_scans);
  if (err.Failed()) {
    std::ostringstream oss;
    oss << "failed to open pre-recorded scanograms from a file '" << filename << "'";
    return ErrHandle(TEXEL_WHERE, oss.str(), err);
  }

  auto id_prefix = PathToIdentifier(filename);
  for (size_t i = 0; i < new_scans.size(); i++) {
    std::ostringstream oss;
    oss << id_prefix;
    if (new_scans.size() > 1) {
      oss << "_" << i;
    }

    scans.emplace_back(scan_finder::ScanInfo(new_scans[i], name, group, gender, oss.str()));
  }
  return ErrHandle();
}

} // unnamed namespace

//-------------------
//--- ScansFinder ---
//-------------------

ErrHandle ScanogramFinder::BindFile(const std::string &filename) {
  cur_scan_ = -1;
  scans_.clear();

  std::filesystem::path path(filename);
  if (!std::filesystem::is_regular_file(filename) ||
      !HasScanXmlExtension(filename)) {
    std::ostringstream oss;
    oss << "'" << filename << "' is not a file with pre-recorded scanograms";
    return ErrHandle(TEXEL_WHERE, oss.str());
  }

  auto err = PopulateScans(filename, scans_);
  if (err.Failed()) {
    return ErrHandle(TEXEL_WHERE, "trace holder", err);
  }
  return ErrHandle();
}

ErrHandle ScanogramFinder::BindDirectory(const std::string &dir) {
  cur_scan_ = -1;
  scans_.clear();

  std::filesystem::path path(dir);
  if (!std::filesystem::is_directory(path)) {
    return ErrHandle(TEXEL_WHERE, "'path' must refer to a directory");
  }
  
  for (const auto &iter : std::filesystem::recursive_directory_iterator(path)) {
    if (std::filesystem::is_regular_file(iter.path()) &&
        HasScanXmlExtension(iter.path().string())) {
      auto err = PopulateScans(iter.path().string(), scans_);
      if (err.Failed()) {
        return ErrHandle(TEXEL_WHERE, "trace holder", err);
      }
    }
  }

  return ErrHandle();
}

bool ScanogramFinder::FindNext() {
  if (cur_scan_ + 1 >= (int)scans_.size()) {
    return false;
  }
  else {
    cur_scan_ += 1;
    return true;
  }
}

const scan_finder::ScanInfo &ScanogramFinder::Current() const {
  if (cur_scan_ < 0) {
    return empty_scan_;
  }
  else {
    return scans_[(size_t)cur_scan_];
  }
}

} // namespace texel
