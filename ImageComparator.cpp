//
// Created by kipteam on 3/19/25.
//

#define STB_IMAGE_IMPLEMENTATION
#include "ImageComparator.h"
#include "stb_image.h"

#include <unordered_map>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;


ImageComparator::ImageComparator(const std::string &directory) {
    std::unordered_map<std::string, std::string> pairs;
    std::vector<std::string> filenames;
    std::vector<std::string> pngs;

    for (const auto& entry : fs::directory_iterator(directory)) {
        if (!entry.is_regular_file()) continue;

        const std::string extension = entry.path().extension().string();
        if (extension != ".bmp" && extension != ".png") continue;

        const std::string filename = entry.path().stem().string();
        const std::string fullPath = entry.path().string();

        auto it = pairs.find(filename);
        if (it == pairs.end()) {
            pairs[filename] = fullPath;
            continue;
        }

        this->filePairs.push_back({it->second, fullPath});
    }
}

bool ImageComparator::compareImages(const std::string& file1, const std::string& file2) {
    int width1, height1, channels1;
    int width2, height2, channels2;

    unsigned char* img1 = stbi_load(file1.c_str(), &width1, &height1, &channels1, 0);
    if (!img1) {
        std::cerr << "Failed to load image: " << file1 << std::endl;
        return false;
    }

    unsigned char* img2 = stbi_load(file2.c_str(), &width2, &height2, &channels2, 0);
    if (!img2) {
        std::cerr << "Failed to load image: " << file2 << std::endl;
        stbi_image_free(img1);
        return false;
    }

    if (width1 != width2 || height1 != height2) {
        std::cerr << "Images have different dimensions: " << file1 << " (" << width1 << "x" << height1 << ") vs "
                  << file2 << " (" << width2 << "x" << height2 << ")" << std::endl;
        stbi_image_free(img1);
        stbi_image_free(img2);
        return false;
    }

    const int channels = std::min(channels1, channels2);
    const long long totalPixels = width1 * height1 * channels;
    double matchingPixels = 0.0;

    for (int y = 0; y < height1; y++) {
        for (int x = 0; x < width1; x++) {
            for (int c = 0; c < channels; c++) {
                const int idx = (y * width1 + x) * channels1 + c;

                if (const int idx2 = (y * width2 + x) * channels2 + c; img1[idx] == img2[idx2]) {
                    matchingPixels++;
                }
            }
        }
    }

    const double similarity = (matchingPixels / totalPixels) * 100.0;
    std::cout << "Comparing " << fs::path(file1).filename() << " and " << fs::path(file2).filename() << ": " << similarity << "% similar" << std::endl;

    if (similarity > 96) {
        this->goodMatches += 1;
        this->similarityRate = std::min(this->similarityRate, similarity);
    }

    stbi_image_free(img1);
    stbi_image_free(img2);

    return true;
}

void ImageComparator::compare() {
    for (const auto&[fst, snd] : this->filePairs) {
        compareImages(fst, snd);
    }

    std::cout << this->goodMatches << "/" << this->filePairs.size() << " images have a similarity rate of over " << this->similarityRate << "%";
}
