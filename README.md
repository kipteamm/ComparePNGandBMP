# ComparePNGandBMP
A simple c++ library that will compare .png and .bmp images.

## How to use
Copy/import all the following files to your project:
- `ImageComparator.h`
- `ImageComparator.cpp`
- `stb_image.h`  

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
