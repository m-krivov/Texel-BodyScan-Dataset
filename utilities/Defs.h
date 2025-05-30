#pragma once

// Disable annoying and stupid warnings from VC++ 2019
#if _MSC_VER >= 1920
#pragma warning(disable: 26812)
#pragma warning(disable: 26451)
#endif

// This file is supposed to be a precompiled header (if they are enabled)
// Place here any standard and 3rd-party headers that will not be modified
#include <algorithm>
#include <array>
#include <atomic>
#include <cstring>
#include <cstdio>
#include <chrono>
#include <cmath>
#include <filesystem>
#include <functional>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <set>
#include <stdexcept>
#include <string>
#include <sstream>
#include <stdint.h>
#include <thread>
#include <type_traits>


// A few 3rd-party libraries
#include <tinyxml2.h>
#include <date/date.h>
#include <glm/glm.hpp>


namespace texel {

// Our personal error class with the enhanced message and trace
// Some handmade analogue of std::exception, but it is more robust
class ErrHandle {
  public:
    explicit ErrHandle() noexcept = default;
    explicit ErrHandle(const std::string& location, const std::string& reason) noexcept {
      trace_.emplace_back(std::make_pair(location, reason));
    }
    explicit ErrHandle(const std::string &location, const std::string &reason,
                       const ErrHandle &inner) noexcept {
      trace_.insert(trace_.begin(), inner.trace_.begin(), inner.trace_.end());
      trace_.emplace_back(std::make_pair(location, reason));
    }
    ErrHandle(const ErrHandle &) = default;
    ErrHandle &operator =(const ErrHandle &) = default;
    
    bool Succeeded() const { return trace_.empty(); }
    bool Failed() const { return !Succeeded(); }
    std::string Message() const {
      std::stringstream ss;
      if (trace_.empty()) {
        ss << "No errors are detected";
      }
      else {
        for (int i = (int)trace_.size() - 1; i >= 0; i--) {
          ss << trace_[i].first << ": " << trace_[i].second << std::endl;
        }
      }
      return ss.str();
    }
    
  private:
    std::vector<std::pair<std::string, std::string> > trace_;
};

namespace err_handle {

static inline std::string Where(const char* file, int line) {
  std::stringstream ss;
  ss << file << ":" << line;
  return ss.str();
}
static inline ErrHandle ToError(ErrHandle err, const char* file, int line) {
  if (err.Failed()) {
    err = ErrHandle(Where(file, line), "trace holder", err);
  }
  return err;
}

} // namespace err_handle


// Specifies a rectangular region in 3D space that bounds some value information
// In the project, we use bounding boxes to separate the scanned object from background
class BoundingBox {
public:
  BoundingBox() : offset_(0.0f), size_(0.0f) {}
  BoundingBox(const glm::vec3& offset,
    const glm::vec3& size)
    : offset_(offset), size_(size) {
  }
  BoundingBox(const BoundingBox&) = default;
  BoundingBox& operator =(const BoundingBox&) = default;

  // Offset from the origin of the coordinate system
  const glm::vec3 Offset() const { return offset_; }

  // Size of the bounding box, expected to be positive
  const glm::vec3 Size() const { return size_; }

private:
  glm::vec3 offset_, size_;
};


// Container with parameters of our sensor (depth or color)
class Camera {
public:
  Camera()
    : width_(0), height_(0),
    cx_(0), cy_(0), fx_(0), fy_(0),
    offset_(0.0f), rotation_(0.0f) {
  }
  Camera(const Camera&) = default;
  Camera(Camera&&) noexcept = default;
  Camera(size_t width, size_t height,
    float cx, float cy, float fx, float fy,
    const glm::vec3& offset,
    const glm::mat3x3& rotation)
    : width_(width), height_(height),
    cx_(cx), cy_(cy), fx_(fx), fy_(fy),
    offset_(offset), rotation_(rotation) {
  }
  Camera& operator =(const Camera&) = default;
  Camera& operator =(Camera&&) noexcept = default;

  // Returns width of the frame, in pixels
  size_t Width() const { return width_; }

  // Returns height of the frame, in pixels
  size_t Height() const { return height_; }

  // A coefficient for projection matrix
  float Cx() const { return cx_; }

  // A coefficient for projection matrix
  float Cy() const { return cy_; }

  // A coefficient for projection matrix
  float Fx() const { return fx_; }

  // A coefficient for projection matrix
  float Fy() const { return fy_; }

  // Returns offset from the viewer position, in meters
  const glm::vec3& Offset() const { return offset_; }

  // Returns rotations (as row-based matrix) from viewer's line of sight
  const glm::mat3x3& Rotation() const { return rotation_; }

private:
  size_t width_, height_;
  float cx_, cy_, fx_, fy_;
  glm::vec3 offset_;
  glm::mat3x3 rotation_;
};

} // namespace texel


// Macro that references the current source file and line
#define TEXEL_WHERE texel::err_handle::Where(__FILE__, __LINE__)

// Macro to reduce the number of code lines
#define TEXEL_CHECK(err)                                        \
do {                                                            \
  auto _err = err_handle::ToError((err), __FILE__, __LINE__);   \
  if (_err.Failed()) {                                          \
    return _err;                                                \
  }                                                             \
} while (false)
