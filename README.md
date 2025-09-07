# ComparePNGandBMP
A simple c++ library that will compare .png and .bmp images.

## What you can expect
Every output .bmp image in the provided directory, see [setup guide](#How-to-use), will get matched against the provided .png with the same name. There are two types of output to expect.

### Similarity rate can be calculated
```
"file1.bmp" and "file1.png" are 100% similar
 ┗━━━┳━━━┛       ┗━━━┳━━━┛      ┗━┳━┛
     ┗ The filename of the bmp file
                     ┗ The filename of the png file
                                  ┗ The similarity percentage of files, based on the amount of pixels that have the same color
```
The color of this line will depend on the quality of the result. 
- Gray/unhighlighted is for matches > 96% (A good threshold based on visible difference).
- Orange/yellow if for matches > 90%. (needs fixing)
- Red for matches <= 90%. (pretty bad)

### Similarity rate cannot be calculated
```
Images have different dimensions: ./3d_fractals169.bmp (1024x908) vs ./3d_fractals169.png (1024x907)`
                                 ┗━━━━━━━━━━┳━━━━━━━━━┛┗━━━━┳━━━━┛  ┗━━━━━━━━━━┳━━━━━━━━━┛┗━━━━┳━━━━┛
                                            ┗ The filename of the bmp file     ┃               ┃
                                                            ┗ The dimensions of the bmp file (width x height)
                                                  The filename of the png file ┛               ┃
                                               The dimensions of the bmp file (width x height) ┛
```
The color of this line will indicate the severity of the difference:
- Orange/yellow, only one pixel off in one direction (do a manual review to decide how simialr images are)
- Red, more than one pixel off in one/multiple direction(s)

## How to use
Copy/import all the following files to your project:
- `ImageComparator.h`
- `ImageComparator.cpp`
- `stb_image.h`  

Make sure to list in your CMakeLists.txt source files:
```cmake
stb_image.h
ImageComparator.cpp
```

To use the comparator
```cpp
#include "ImageComparator.h"

int main() {
    // ... other main code

    // Add this to your main and specify the directory with images.
    ImageComparator image_comparator("./");
    image_comparator.compare();
}
```

## Credits
Makes use of the amazing [stb_image](https://github.com/nothings/stb/blob/master/stb_image.h)
