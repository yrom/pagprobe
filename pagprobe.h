#ifndef PAGPROBE_H
#define PAGPROBE_H

#include <array>
#include <fifo_map.hpp>
#include <nlohmann/json.hpp>
#include <pag/file.h>
#include <pag/types.h>
namespace pagprobe {

// https://github.com/nlohmann/json/issues/485#issuecomment-333652309
template <class K, class V, class Dummy, class A>
using _workaround_fifo_map =
    nlohmann::fifo_map<K, V, nlohmann::fifo_map_compare<K>, A>;
using json = nlohmann::basic_json<_workaround_fifo_map>;
static const json kNull = json();

json Dump(pag::File *file);

json Dump(pag::FileAttributes *fileAttributes);

json DumpLayer(pag::Layer *layer);
json DumpComposition(pag::Composition *c, bool isref = false);

json DumpShape(pag::ShapeElement *shape);

inline const char *CompositionTypeName(pag::CompositionType type) {

  switch (type) {
  case pag ::CompositionType ::Vector:
    return "Vector";
  case pag ::CompositionType ::Bitmap:
    return "Bitmap";
  case pag ::CompositionType ::Video:
    return "Video";
  case pag ::CompositionType ::Unknown:
  default:
    return "Unknown";
  }
}

#define LAYER_TYPE(type)                                                       \
  { ::pag::LayerType::type, #type }
static const std::unordered_map<pag::LayerType, std::string> kLayerTypeNames = {
    LAYER_TYPE(Unknown),    LAYER_TYPE(Null),   LAYER_TYPE(Solid),
    LAYER_TYPE(Text),       LAYER_TYPE(Shape),  LAYER_TYPE(Image),
    LAYER_TYPE(PreCompose), LAYER_TYPE(Camera),
};
#undef LAYER_TYPE

#define SHAPE_TYPE(type)                                                       \
  { ::pag::ShapeType::type, #type }
static const std::unordered_map<pag::ShapeType, std::string> kShapeTypeNames = {
  SHAPE_TYPE(Unknown),
  SHAPE_TYPE(ShapeGroup),
  SHAPE_TYPE(Rectangle),
  SHAPE_TYPE(Ellipse),
  SHAPE_TYPE(PolyStar),
  SHAPE_TYPE(ShapePath),
  SHAPE_TYPE(Fill),
  SHAPE_TYPE(Stroke),
  SHAPE_TYPE(GradientFill),
  SHAPE_TYPE(GradientStroke),
  SHAPE_TYPE(MergePaths),
  SHAPE_TYPE(TrimPaths),
  SHAPE_TYPE(Repeater),
  SHAPE_TYPE(RoundCorners),
};
#undef SHAPE_TYPE

inline static const char *ScaleModeName(pag::Enum mode) {
  switch (mode) {
  case ::pag ::PAGScaleMode ::Stretch:
    return "Stretch";
  case ::pag ::PAGScaleMode ::LetterBox:
    return "LetterBox";
  case ::pag ::PAGScaleMode ::Zoom:
    return "Zoom";
  case ::pag ::PAGScaleMode ::None:
  default:
    return "None";
  }
};

inline static const char *TimeStretchModeName(pag::Enum mode) {

  switch (mode) {
  case ::pag ::PAGTimeStretchMode ::Scale:
    return "Scale";
  case ::pag ::PAGTimeStretchMode ::Repeat:
    return "Repeat";
  case ::pag ::PAGTimeStretchMode ::RepeatInverted:
    return "RepeatInverted";
  case ::pag ::PAGTimeStretchMode ::None:
  default:
    return "None";
  }
};
/**
 * @brief
 *
 * @param mode pag::BlendMode
 * @return const char*
 */
inline static const char *BlendModeName(pag::Enum mode) {

  static const std::array<const char *, 17> kModeNames = {
      "Normal",     "Multiply",   "Screen",    "Overlay",    "Darken",
      "Lighten",    "ColorDodge", "ColorBurn", "HardLight",  "SoftLight",
      "Difference", "Exclusion",  "Hue",       "Saturation", "Color",
      "Luminosity", "Add",
  };
  if (mode > pag::BlendMode::Add) {
    return "Unknown";
  }
  return kModeNames[mode];
} // namespace pagprobe

static std::string FormatColor(const pag::Color &color) {
  static std::array<char, 8> buf;
  snprintf(buf.data(), 8, "#%02x%02x%02x", color.red, color.green, color.blue);
  return {buf.data()};
}
} // namespace pagprobe
#endif // PAGPROBE_H