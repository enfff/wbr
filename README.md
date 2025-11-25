# wbr

White Background Remover - A C++ CLI tool that removes white backgrounds from black silhouette images, resulting in transparent PNG output.

## Description

This tool processes black and white images and converts white backgrounds to transparent pixels using the multiply method. The multiply method calculates the alpha (transparency) channel based on the grayscale value of each pixel:

- **White pixels (255)** → Alpha = 0 (fully transparent)
- **Black pixels (0)** → Alpha = 255 (fully opaque)
- **Gray pixels** → Proportional transparency

## Building

### Prerequisites

- CMake 3.10 or higher
- C++17 compatible compiler (GCC, Clang, MSVC)

### Build Instructions

```bash
mkdir build
cd build
cmake ..
make
```

### Installation (optional)

```bash
sudo make install
```

## Usage

```bash
./wbr <input_image_path>
```

### Arguments

- `input_image_path`: Path to the input image file (supports JPEG, PNG, BMP, GIF, etc.)

### Output

The tool creates a new PNG file with the suffix `_nobg` in the same directory as the input file.

**Example:**
```bash
./wbr image.jpg
# Creates: image_nobg.png
```

## Example

```bash
# Process a silhouette image
./wbr silhouette.png
# Output: silhouette_nobg.png with transparent background
```

## Supported Formats

### Input
- JPEG
- PNG
- BMP
- GIF
- TGA
- PSD
- HDR
- PIC
- PNM

### Output
- PNG (with alpha channel for transparency)

## How It Works

The multiply method works by:

1. Loading the input image and reading pixel values
2. Converting RGB values to grayscale using the luminance formula: `0.299*R + 0.587*G + 0.114*B`
3. Calculating alpha as: `alpha = 255 - grayscale_value`
4. Setting output pixels to black with the calculated alpha value
5. Saving as PNG with full alpha channel support

This effectively makes white areas transparent while preserving black content with full opacity.
