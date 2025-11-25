#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <iostream>
#include <string>
#include <cstdint>
#include <filesystem>

#include "stb_image.h"
#include "stb_image_write.h"

/**
 * Remove white background from a black and white image using the multiply method.
 * 
 * The multiply method works by:
 * 1. Converting the grayscale value to an alpha channel
 * 2. For white pixels (255), alpha becomes 0 (fully transparent)
 * 3. For black pixels (0), alpha becomes 255 (fully opaque)
 * 4. The alpha is calculated as: alpha = 255 - grayscale_value
 * 
 * This effectively removes white backgrounds while preserving black content.
 */
bool removeWhiteBackground(const std::string& inputPath, const std::string& outputPath) {
    int width, height, channels;
    
    // Load the image, preserving original channels
    unsigned char* imageData = stbi_load(inputPath.c_str(), &width, &height, &channels, 0);
    
    if (!imageData) {
        std::cerr << "Error: Failed to load image: " << inputPath << std::endl;
        std::cerr << "Reason: " << stbi_failure_reason() << std::endl;
        return false;
    }
    
    std::cout << "Loaded image: " << width << "x" << height << " with " << channels << " channels" << std::endl;
    
    // Create output buffer with RGBA (4 channels)
    int outputChannels = 4;
    unsigned char* outputData = new unsigned char[width * height * outputChannels];
    
    // Process each pixel using the multiply method
    // For black and white images, we use the pixel intensity to determine transparency
    // White (255) becomes transparent, Black (0) becomes opaque
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int srcIndex = (y * width + x) * channels;
            int dstIndex = (y * width + x) * outputChannels;
            
            // Get the grayscale value (for B&W images, all channels should be similar)
            // If RGB, use luminance formula; if grayscale, use directly
            uint8_t grayValue;
            if (channels >= 3) {
                // Use luminance formula for RGB: 0.299*R + 0.587*G + 0.114*B
                grayValue = static_cast<uint8_t>(
                    0.299f * imageData[srcIndex] + 
                    0.587f * imageData[srcIndex + 1] + 
                    0.114f * imageData[srcIndex + 2]
                );
            } else {
                // Grayscale image
                grayValue = imageData[srcIndex];
            }
            
            // Multiply method: alpha = 255 - grayValue
            // White (255) -> alpha = 0 (transparent)
            // Black (0) -> alpha = 255 (opaque)
            uint8_t alpha = 255 - grayValue;
            
            // Set output pixel to black with calculated alpha
            // For black and white silhouette images, the output is a black shape
            // with varying transparency based on the original grayscale values
            outputData[dstIndex] = 0;       // R - black
            outputData[dstIndex + 1] = 0;   // G - black
            outputData[dstIndex + 2] = 0;   // B - black
            outputData[dstIndex + 3] = alpha; // A - calculated transparency
        }
    }
    
    // Write output as PNG (supports transparency)
    int result = stbi_write_png(outputPath.c_str(), width, height, outputChannels, outputData, width * outputChannels);
    
    // Cleanup
    stbi_image_free(imageData);
    delete[] outputData;
    
    if (result == 0) {
        std::cerr << "Error: Failed to write output image: " << outputPath << std::endl;
        return false;
    }
    
    std::cout << "Successfully created: " << outputPath << std::endl;
    return true;
}

std::string generateOutputPath(const std::string& inputPath) {
    std::filesystem::path p(inputPath);
    std::string stem = p.stem().string();
    std::string parentPath = p.parent_path().string();
    
    std::string outputPath;
    if (parentPath.empty()) {
        outputPath = stem + "_nobg.png";
    } else {
        outputPath = parentPath + "/" + stem + "_nobg.png";
    }
    
    return outputPath;
}

void printUsage(const char* programName) {
    std::cout << "White Background Remover (wbr)" << std::endl;
    std::cout << "Removes white background from black silhouette images." << std::endl;
    std::cout << std::endl;
    std::cout << "Usage: " << programName << " <input_image_path>" << std::endl;
    std::cout << std::endl;
    std::cout << "Arguments:" << std::endl;
    std::cout << "  input_image_path  Path to the input image (JPEG, PNG, BMP, etc.)" << std::endl;
    std::cout << std::endl;
    std::cout << "Output:" << std::endl;
    std::cout << "  Creates a new PNG file with '_nobg' suffix in the same directory" << std::endl;
    std::cout << "  Example: input.jpg -> input_nobg.png" << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printUsage(argv[0]);
        return 1;
    }
    
    std::string inputPath = argv[1];
    
    // Check if input file exists
    if (!std::filesystem::exists(inputPath)) {
        std::cerr << "Error: Input file does not exist: " << inputPath << std::endl;
        return 1;
    }
    
    // Generate output path
    std::string outputPath = generateOutputPath(inputPath);
    
    std::cout << "Processing: " << inputPath << std::endl;
    std::cout << "Output will be saved to: " << outputPath << std::endl;
    
    if (!removeWhiteBackground(inputPath, outputPath)) {
        return 1;
    }
    
    return 0;
}
