# pagprobe

Dump the infomation in json of pag file by [libpag](https://github.com/Tencent/libpag) .

## Building

```sh
git clone https://github.com/yrom/pagprobe.git

cd pagprobe

cmake -DPAG_BUILD_TESTS=OFF -DPAG_BUILD_SHARED=OFF \
    -DUSE_CCACHE=ON "-DCCACHE_OPTIONS=CCACHE_CPP2=true;CCACHE_SLOPPINESS=clang_index_store" \
    -DCMAKE_BUILD_TYPE=Release \
    -Bbuild -G Ninja .

cmake --build ./build --config Release --target pagprobe
```

## Usage

```
./build/pagprobe ./thirdparty/libpag/assets/fans.pag
```

output in json format:

```json
{
  "path": "./thirdparty/libpag/assets/fans.pag",
  "stats": {
    "layers": 8,
    "images": 0,
    "videos": 0,
    "texts": 0,
    "duration": 25,
    "frameRate": 24.0
  },
  "tagLevel": 25,
  "timeStretchMode": "Repeat",
  "compositions": [
    {
      "type": "Vector",
      "id": 2076,
      "width": 750,
      "height": 1334,
      "frameRate": 24.0,
      "duration": 25,
      "backgroundColor": "#000000",
      "layers": [
        {
          "type": "Shape",
          "id": 2101,
          "name": "",
          "blendMode": "Normal",
          "duration": 25,
          "contents": [
            {
              "type": "ShapeGroup",
              "blendMode": "Normal",
              "transform": {
                "opacity": 255,
                "position": [
                  20.249984741210938,
                  9.25
                ],
                "scale": [
                  1.0,
                  1.0
                ]
              },
              "elements": [
                {
                  "type": "ShapePath",
                  "path": "…"
                },
                {
                  "type": "Fill",
                  "color": "#ffffff",
                  "opacity": 255,
                  "rule": 0
                }
              ]
            }
          ]
        },
        {
          "type": "Shape",
          "id": 2100,
          "name": "",
          "blendMode": "Normal",
          "duration": 25,
          "contents": [
            {
              "type": "ShapeGroup",
              "blendMode": "Normal",
              "transform": {
                "opacity": 255,
                "position": [
                  15.25,
                  15.25
                ],
                "scale": [
                  1.0,
                  1.0
                ]
              },
              "elements": [
                {
                  "type": "ShapePath",
                  "path": "…"
                },
                {
                  "type": "Fill",
                  "color": "#8150ff",
                  "opacity": 255,
                  "rule": 0
                }
              ]
            }
          ]
        },
        {
          "type": "Shape",
          "id": 2099,
          "name": "",
          "blendMode": "Normal",
          "duration": 25,
          "contents": [
            {
              "type": "ShapeGroup",
              "blendMode": "Normal",
              "transform": {
                "opacity": 255,
                "position": [
                  10.749969482421875,
                  12.27850341796875
                ],
                "scale": [
                  1.0,
                  1.0
                ]
              },
              "elements": [
                {
                  "type": "ShapePath",
                  "path": "…"
                },
                {
                  "type": "Fill",
                  "color": "#8150ff",
                  "opacity": 255,
                  "rule": 0
                }
              ]
            }
          ]
        },
        {
          "type": "Shape",
          "id": 2498,
          "name": "",
          "blendMode": "Normal",
          "duration": 25,
          "contents": [
            {
              "type": "ShapeGroup",
              "blendMode": "Normal",
              "transform": {
                "opacity": 255,
                "position": [
                  106.0,
                  116.10931396484375
                ],
                "scale": [
                  1.0,
                  1.0
                ]
              },
              "elements": [
                {
                  "type": "ShapePath",
                  "path": "…"
                },
                {
                  "type": "TrimPaths"
                },
                {
                  "type": "Stroke",
                  "color": "#ffffff",
                  "opacity": 255,
                  "width": 26.0
                }
              ]
            }
          ]
        },
        {
          "type": "Shape",
          "id": 2102,
          "name": "",
          "blendMode": "Normal",
          "duration": 25,
          "contents": [
            {
              "type": "ShapeGroup",
              "blendMode": "Normal",
              "transform": {
                "opacity": 255,
                "position": [
                  106.0,
                  116.10931396484375
                ],
                "scale": [
                  1.0,
                  1.0
                ]
              },
              "elements": [
                {
                  "type": "ShapePath",
                  "path": "…"
                },
                {
                  "type": "Stroke",
                  "color": "#8150ff",
                  "opacity": 255,
                  "width": 20.0
                }
              ]
            }
          ]
        },
        {
          "type": "Shape",
          "id": 2098,
          "name": "",
          "blendMode": "Normal",
          "duration": 25,
          "contents": [
            {
              "type": "ShapeGroup",
              "blendMode": "Normal",
              "transform": {
                "opacity": 255,
                "position": [
                  28.25,
                  40.75
                ],
                "scale": [
                  1.0,
                  1.0
                ]
              },
              "elements": [
                {
                  "type": "ShapePath",
                  "path": "…"
                },
                {
                  "type": "Fill",
                  "color": "#ffffff",
                  "opacity": 255,
                  "rule": 0
                }
              ]
            }
          ]
        },
        {
          "type": "Shape",
          "id": 2097,
          "name": "",
          "blendMode": "Normal",
          "duration": 25,
          "contents": [
            {
              "type": "ShapeGroup",
              "blendMode": "Normal",
              "transform": {
                "opacity": 255,
                "position": [
                  124.25,
                  162.5
                ],
                "scale": [
                  1.0,
                  1.0
                ]
              },
              "elements": [
                {
                  "type": "ShapePath",
                  "path": "…"
                },
                {
                  "type": "Stroke",
                  "color": "#5c34c4",
                  "opacity": 255,
                  "width": 18.0
                }
              ]
            },
            {
              "type": "ShapeGroup",
              "blendMode": "Normal",
              "transform": {
                "opacity": 255,
                "position": [
                  87.25,
                  162.5
                ],
                "scale": [
                  1.0,
                  1.0
                ]
              },
              "elements": [
                {
                  "type": "ShapePath",
                  "path": "…"
                },
                {
                  "type": "Stroke",
                  "color": "#5c34c4",
                  "opacity": 255,
                  "width": 18.0
                }
              ]
            }
          ]
        },
        {
          "type": "Shape",
          "id": 2200,
          "name": "",
          "blendMode": "Normal",
          "duration": 25,
          "contents": [
            {
              "type": "ShapeGroup",
              "blendMode": "Normal",
              "transform": {
                "opacity": 255,
                "position": [
                  53.25,
                  6.25
                ],
                "scale": [
                  1.0,
                  1.0
                ]
              },
              "elements": [
                {
                  "type": "ShapePath",
                  "path": "…"
                },
                {
                  "type": "Fill",
                  "color": "#000000",
                  "opacity": 255,
                  "rule": 0
                }
              ]
            }
          ]
        }
      ]
    },
    {
      "type": "Vector",
      "id": 2354,
      "width": 244,
      "height": 244,
      "frameRate": 24.0,
      "duration": 25,
      "backgroundColor": "#000000",
      "layers": [
        {
          "type": "PreCompose",
          "id": 2365,
          "name": "",
          "blendMode": "Normal",
          "duration": 25,
          "composition": {
            "type": "Vector",
            "id": 2076
          },
          "compositionStartTime": 0
        }
      ]
    }
  ]
}
```
