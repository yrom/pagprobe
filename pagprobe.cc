#include "pagprobe.h"

#include <codec/utils/WebpDecoder.h>
#include <pag/file.h>

#include <cstdio>
#include <iostream>

namespace pagprobe {
using namespace pag;
json Dump(FileAttributes *fileAttributes) {
  json j = {
      {"timestamp", (fileAttributes->timestamp)},
      {"pluginVersion", (fileAttributes->pluginVersion)},
      {"aeVersion", (fileAttributes->aeVersion)},
      {"systemVersion", (fileAttributes->systemVersion)},
      {"author", (fileAttributes->author)},
      {"scene", (fileAttributes->scene)},
  };
  if (!fileAttributes->warnings.empty())
    j.push_back({"warnings", fileAttributes->warnings});
  return j;
}

inline void DumpVectorComposition(VectorComposition *v, json &j) {
  json::array_t layers = json::array();
  for (auto &l : v->layers) {
    layers.push_back(DumpLayer(l));
  }
  j["layers"] = layers;
}
inline json DumpBitmapRect(BitmapRect *bm) {
  if (bm != nullptr && bm->fileBytes != nullptr) {
    int width = 0;
    int height = 0;
    if (WebPGetInfo(bm->fileBytes->data(), bm->fileBytes->length(), &width,
                    &height) != 0) {
      return {
          {"x", bm->x},
          {"y", bm->y},
          {"width", width},
          {"height", height},
          {"sizeInBytes", bm->fileBytes->length()},
      };
    }
  }
  return kNull;
}
inline void DumpVideoComposition(VideoComposition *v, json &j) {
  json arr = json::array();
  for (auto &s : v->sequences) {
    json seq = {
        {"width", s->width},
        {"height", s->height},
        {"frameRate", s->frameRate},
        {"alphaStartX", s->alphaStartX},
        {"alphaStartY", s->alphaStartY},
    };
    json frames = json::array();
    for (auto &f : s->frames) {
      frames.push_back({
          {"frame", f->frame},
          {"isKeyframe", f->isKeyframe},
          {"sizeInBytes", f->fileBytes->length()},
      });
    }
    seq["frames"] = frames;
    if (!s->staticTimeRanges.empty()) {
      json ranges = json::array();
      for (auto &t : s->staticTimeRanges) {
        ranges.push_back({
            {"start", t.start},
            {"end", t.end},
        });
      }
      seq["staticTimeRanges"] = ranges;
    }

    arr.push_back(seq);
  }
  j["sequences"] = arr;
}

inline void DumpBitmapComposition(BitmapComposition *b, json &j) {
  json::array_t arr = json::array();
  for (auto &s : b->sequences) {
    json seq = {
        {"width", s->width},
        {"height", s->height},
        {"frameRate", s->frameRate},
    };

    json frames = json::array();

    for (auto &f : s->frames) {
      json bitmaps = json::array();
      for (auto &bm : f->bitmaps) {
        bitmaps.push_back(DumpBitmapRect(bm));
      }
      frames.push_back({{"isKeyframe", f->isKeyframe}, {"bitmaps", bitmaps}});
    }

    seq["frames"] = frames;
    arr.push_back(seq);
  }
  j["sequences"] = arr;
}

json DumpComposition(Composition *c, bool isref) {
  if (c == nullptr) return kNull;
  auto type = c->type();
  json composition_json = {
      {"type", CompositionTypeName(type)},
      {"id", c->id},

  };

  if (isref) {
    return composition_json;
  }
  composition_json.merge_patch({
      {"width", c->width},
      {"height", c->height},
      {"frameRate", c->frameRate},
      {"duration", c->duration},
      {"backgroundColor", FormatColor(c->backgroundColor)},
  });
  if (c->audioBytes != nullptr) {
    composition_json["audio"] = {
        {"sizeInBytes", c->audioBytes->length()},
        {"startTime", c->audioStartTime},
    };
    if (!c->audioMarkers.empty()) {
      json arr = json::array();
      for (auto &m : c->audioMarkers) {
        arr.push_back({
            {"startTime", m->startTime},
            {"duration", m->duration},
            {"comment", m->comment},
        });
      }
      composition_json["audio"]["markers"] = arr;
    }
  }
  if (type == CompositionType::Vector) {
    DumpVectorComposition(static_cast<VectorComposition *>(c),
                          composition_json);
  } else if (type == CompositionType::Bitmap) {
    DumpBitmapComposition(static_cast<BitmapComposition *>(c),
                          composition_json);
  } else if (type == CompositionType::Video) {
    DumpVideoComposition(static_cast<VideoComposition *>(c), composition_json);
  }
  return composition_json;
}
inline void DumpLayer(ShapeLayer *l, json &j) {
  json arr = json::array();
  if (!l->contents.empty()) {
    for (auto *c : l->contents) {
      arr.push_back(DumpShape(c));
    }
  }
  j["contents"] = arr;
}
inline void DumpLayer(PreComposeLayer *prelayer, json &j) {
  j["composition"] = DumpComposition(prelayer->composition, true);
  j["compositionStartTime"] = prelayer->compositionStartTime;
}
inline void DumpLayer(ImageLayer *layer, json &j) {
  auto *image = layer->imageBytes;
  if (image != nullptr) {
    j["imageId"] = image->id;
  }
  auto *fill = layer->imageFillRule;
  if (fill != nullptr) {
    j["fill"] = {
        {"scaleMode", ScaleModeName(fill->scaleMode)},
        /// TODO: fill->timeRemap
        {"timeRemap", {{"animatable", fill->timeRemap->animatable()}}},
    };
  }
}
inline void DumpLayer(SolidLayer *layer, json &j) {
  j["color"] = FormatColor(layer->solidColor);
  j["width"] = layer->width;
  j["height"] = layer->height;
}

inline void DumpLayer(TextLayer *layer, json &j) {
  auto text = layer->sourceText->value;
  j["sourceText"] = {
      {"text", text->text},
      {"fontFamily", text->fontFamily},
      {"fontStyle", text->fontStyle},
      {"fontSize", text->fontSize},
      {"color", FormatColor(text->fillColor)},
      {"background", FormatColor(text->backgroundColor)},
      {"backgroundAlpha", text->backgroundAlpha},
  };
}
void DumpImage(ImageBytes *image, json &j) {
  j = {
      {"id", image->id},
      {"width", image->width},
      {"height", image->height},
      {"anchorX", image->anchorX},
      {"anchorY", image->anchorY},
      {"scaleFactor", image->scaleFactor},
      {"sizeInBytes",
       image->fileBytes != nullptr ? image->fileBytes->length() : 0},
  };
}
json DumpLayer(Layer *layer) {
  auto type = layer->type();
  json j = {
      {"type", kLayerTypeNames.at(type)},
      {"id", layer->id},
      {"name", layer->name},
      {"blendMode", BlendModeName(layer->blendMode)},
      {"duration", layer->duration},
      // {"isValid", layer->verify()},
  };
  switch (type) {
    case LayerType::PreCompose:
      DumpLayer(static_cast<PreComposeLayer *>(layer), j);
      break;
    case LayerType::Image:
      DumpLayer(static_cast<ImageLayer *>(layer), j);
      break;
    case LayerType::Shape:
      DumpLayer(static_cast<ShapeLayer *>(layer), j);
      break;
    case LayerType::Text:
      DumpLayer(static_cast<TextLayer *>(layer), j);
      break;
    case LayerType::Solid:
      DumpLayer(static_cast<SolidLayer *>(layer), j);
      break;
    case LayerType::Camera:
    case LayerType::Unknown:
    case LayerType::Null:
      break;
  }

  return j;
}
inline void DumpPoint(const std::string &key, Point &p, json &j) {
  if (!p.isZero()) j[key] = {p.x, p.y};
}

inline void DumpShape(RectangleElement *e, json &j) {
  DumpPoint("size", e->size->value, j);
  DumpPoint("position", e->position->value, j);
  j["roundness"] = e->roundness->value;
}
inline void DumpShape(EllipseElement *e, json &j) {
  DumpPoint("size", e->size->value, j);
  DumpPoint("position", e->position->value, j);
}
inline void DumpShape(FillElement *e, json &j) {
  j["color"] = FormatColor(e->color->value);
  j["opacity"] = e->opacity->value;
  j["rule"] = e->fillRule;
}
inline void DumpShape(StrokeElement *e, json &j) {
  j["color"] = FormatColor(e->color->value);
  j["opacity"] = e->opacity->value;
  j["width"] = e->strokeWidth->value;
}
inline void DumpShape(ShapePathElement *e, json &j) { j["path"] = "…"; }
inline void DumpShape(ShapeGroupElement *group, json &j) {
  j["blendMode"] = BlendModeName(group->blendMode);
  auto *t = group->transform;
  if (t != nullptr) {
    j["transform"] = {
        {"opacity", t->opacity->value},
    };
    DumpPoint("anchorPoint", t->anchorPoint->value, j["transform"]);
    DumpPoint("position", t->position->value, j["transform"]);
    DumpPoint("scale", t->scale->value, j["transform"]);
  }

  json elements = json::array();
  for (auto *e : group->elements) {
    elements.push_back(DumpShape(e));
  }
  j["elements"] = elements;
}
json DumpShape(ShapeElement *shape) {
  auto type = shape->type();
  json j = {
      {"type", kShapeTypeNames.at(type)},
  };
  switch (type) {
    case ShapeType::ShapeGroup:
      DumpShape(static_cast<ShapeGroupElement *>(shape), j);
      break;
    case ShapeType::Rectangle:
      DumpShape(static_cast<RectangleElement *>(shape), j);
      break;
    case ShapeType::Ellipse:
      DumpShape(static_cast<EllipseElement *>(shape), j);
      break;
    case ShapeType::Fill:
      DumpShape(static_cast<FillElement *>(shape), j);
      break;
    case ShapeType::ShapePath:
      DumpShape(static_cast<ShapePathElement *>(shape), j);
      break;
    case ShapeType::Stroke:
      DumpShape(static_cast<StrokeElement *>(shape), j);
      break;
    case ShapeType::PolyStar:
    case ShapeType::GradientFill:
    case ShapeType::GradientStroke:
    case ShapeType::MergePaths:
    case ShapeType::TrimPaths:
    case ShapeType::Repeater:
    case ShapeType::RoundCorners:
    case ShapeType::Unknown:
      break;
  }
  return j;
}

json Dump(File *file) {
  if (file == nullptr) return kNull;

  json info = {
      {"path", file->path},
      {
          "stats",
          json::object({
              {"layers", file->numLayers()},
              {"images", file->numImages()},
              {"videos", file->numVideos()},
              {"texts", file->numTexts()},
              {"duration", file->duration()},
              {"frameRate", file->frameRate()},
          }),
      },
      {"tagLevel", file->tagLevel()},
      {"timeStretchMode", TimeStretchModeName(file->timeStretchMode)},

  };
  if (file->hasScaledTimeRange()) {
    info["scaledTimeRange"] = {file->scaledTimeRange.start,
                               file->scaledTimeRange.end};
  }
  if (!file->fileAttributes.empty()) {
    info["attributes"] = Dump(&(file->fileAttributes));
  }
  if (!file->compositions.empty()) {
    json compositions = json::array();
    for (auto *c : file->compositions) {
      compositions.push_back(DumpComposition(c));
    }
    info["compositions"] = compositions;
  }
  if (!file->images.empty()) {
    json images = json::array();
    for (auto *i : file->images) {
      json j;
      DumpImage(i, j);
      images.push_back(j);
    }
    info["images"] = images;
  }
  return info;
}

}  // namespace pagprobe