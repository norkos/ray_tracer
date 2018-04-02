#include <Image.hpp>
#include <iostream>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <limits>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

namespace rt{
void Image::savebmp (const char *filename, int w, int h, int dpi, rt::Color* data) {
    FILE *f;
    int k = w*h;
    int s = 4*k;
    int filesize = 54 + s;
    
    double factor = 39.375;
    int m = static_cast<int>(factor);
    
    int ppm = dpi*m;
    
    unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0,0,0, 54,0,0,0};
    unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0,24,0};
    
    bmpfileheader[ 2] = (unsigned char)(filesize);
    bmpfileheader[ 3] = (unsigned char)(filesize>>8);
    bmpfileheader[ 4] = (unsigned char)(filesize>>16);
    bmpfileheader[ 5] = (unsigned char)(filesize>>24);
    
    bmpinfoheader[ 4] = (unsigned char)(w);
    bmpinfoheader[ 5] = (unsigned char)(w>>8);
    bmpinfoheader[ 6] = (unsigned char)(w>>16);
    bmpinfoheader[ 7] = (unsigned char)(w>>24);
    
    bmpinfoheader[ 8] = (unsigned char)(h);
    bmpinfoheader[ 9] = (unsigned char)(h>>8);
    bmpinfoheader[10] = (unsigned char)(h>>16);
    bmpinfoheader[11] = (unsigned char)(h>>24);
    
    bmpinfoheader[21] = (unsigned char)(s);
    bmpinfoheader[22] = (unsigned char)(s>>8);
    bmpinfoheader[23] = (unsigned char)(s>>16);
    bmpinfoheader[24] = (unsigned char)(s>>24);
    
    bmpinfoheader[25] = (unsigned char)(ppm);
    bmpinfoheader[26] = (unsigned char)(ppm>>8);
    bmpinfoheader[27] = (unsigned char)(ppm>>16);
    bmpinfoheader[28] = (unsigned char)(ppm>>24);
    
    bmpinfoheader[29] = (unsigned char)(ppm);
    bmpinfoheader[30] = (unsigned char)(ppm>>8);
    bmpinfoheader[31] = (unsigned char)(ppm>>16);
    bmpinfoheader[32] = (unsigned char)(ppm>>24);
    
    f = fopen(filename,"wb");
    
    fwrite(bmpfileheader,1,14,f);
    fwrite(bmpinfoheader,1,40,f);
    
    int* inversion = new int[k];
    for(int x = 0; x < w; x++){
        for(int y = 0; y < h; y++){
            inversion[x + (h - 1 -y) * w] = data[x + y* w].to_int();
        }
    }

    for (int i = 0; i < k; i++) {

        int& color = inversion[i];
        unsigned char result[3] = {(unsigned char)((color & 0x0000FF00) >> 8),
                                   (unsigned char)((color & 0x00FF0000) >> 16),
                                   (unsigned char)((color & 0xFF000000) >> 24)};
        
        fwrite(result,1,3,f);
    }
    delete[] inversion;
    
    fclose(f);
}
}