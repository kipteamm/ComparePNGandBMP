//
// Created by kipteam on 3/19/25.
//

#ifndef IMAGECOMPARATOR_H
#define IMAGECOMPARATOR_H

#include <string>
#include <vector>


class ImageComparator {
public:
    explicit ImageComparator(const std::string& directory);

    bool compareImages(const std::string& file1, const std::string& file2);
    void compare();

private:
    std::vector<std::pair<std::string, std::string>> filePairs;

    unsigned int goodMatches = 0;
    double similarityRate = 100.0;
};



#endif //IMAGECOMPARATOR_H
