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

    static bool compareImages(const std::string& file1, const std::string& file2);
    void compare();

private:
    std::vector<std::pair<std::string, std::string>> filePairs;
};



#endif //IMAGECOMPARATOR_H
