#pragma once
#include "Defs.h"
#include "Scanogram.h"

namespace texel {

namespace scan_finder {

// A helper to avoid awful tuples
struct ScanInfo {
  Scanogram scan;
  std::string name;
  scanogram::AgeGroup group;
  scanogram::Gender gender;
  std::string id;

  ScanInfo()
    : name("NA"),
      group(scanogram::AgeGroup::NA),
      gender(scanogram::Gender::Neutral) {
  }
  ScanInfo(Scanogram &scan_,
           const std::string &name_,
           scanogram::AgeGroup group_,
           scanogram::Gender gender_,
           const std::string &id_) noexcept
    : scan(std::move(scan_)), name(name_), group(group_),
      gender(gender_), id(id_) {
  }
  ScanInfo(ScanInfo &) = delete;
  ScanInfo(ScanInfo &&) noexcept = default;
  ScanInfo &operator =(const ScanInfo &) = delete;
  ScanInfo &operator =(ScanInfo &&) noexcept = default;
};

} // namespace scan_finder


// Searches for scans located somewhere on disk
class ScanogramFinder {
  public:
    ScanogramFinder() : cur_scan_(-1) { }
    ScanogramFinder(const ScanogramFinder &) = delete;
    ScanogramFinder &operator =(const ScanogramFinder &) = delete;

    // Binds this instance to a new file with scanograms (*.scan.xml)
    // Encapsulates all its scanograms into the finder
    ErrHandle BindFile(const std::string &filename);

    // Scans the directory and its subdirectories,
    // enumerates all the scans (*.scan.xml) they contain
    ErrHandle BindDirectory(const std::string &dir);

    // Resets the built-in enumerator
    void Reset() { cur_scan_ = -1; }

    // Sets local fields to the next scan and returns the 'true' value
    // If no scans left, returns 'false'
    bool FindNext();

    // Returns the current scannogram provided by 'FindNext()'
    const scan_finder::ScanInfo &Current() const;

  private:
    std::vector<scan_finder::ScanInfo> scans_;
    int cur_scan_;
    scan_finder::ScanInfo empty_scan_;
};

} // namespace texel
