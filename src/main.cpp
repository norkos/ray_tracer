#include <iostream>
#include <ctime> 

#include <Image.hpp>
#include <Parser.hpp>
#include <Scene.hpp>
#include <OctTree.hpp>

using namespace rt;

Color make_color(std::vector<Color>& temp_color){
    double r = 0;
    double g = 0;
    double b = 0;

    for(auto& color: temp_color){
        r += color.red;
        g += color.green;
        b += color.blue;
    }

    double aa_square = 1.0 / temp_color.size();
    return Color({r* aa_square, g * aa_square, b * aa_square, 0});
}


int main()
{
    Parser parser;

    clock_t t = clock();
    if(! parser.parse("/home/kosmal/workspace/models/Models/model.obj", "/home/kosmal/workspace/models/Models/model.mtl")){
        printf ("File doesn't exist.\n");
        return -1;
    }
    t = clock() - t;
    printf ("It took me %ld clicks (%f seconds) to load the scene file with %zu triangles.\n",
        t,((float)t)/CLOCKS_PER_SEC, parser.get_triangles().size());

    t = clock();
    OctTree tree(parser.get_triangles());
    t = clock() - t;
    printf ("It took me %ld clicks (%f seconds) to create OctTree.\n",
        t,((float)t)/CLOCKS_PER_SEC);
    
    t = clock();
    const int width = 1920;//1280;//1920;//1920;//480;
    const int height = 1080;//720;//1080;//1080;//270;
    const double accuracy = 0.00000001;
   
    Color* pixels = new Color[width * height];
    Scene scene(accuracy, tree);

    const Vector camera_pos( 300.0, 57.0, 120.0);
    Vector st(-9.60/8, 5.40/8, 0.0);
    Vector en( 9.60/8,-5.40/8, 0.0);
    Vector d = en - st;
    double dx = d.getX() / width;
    double dy = d.getY() / height;

    int aa_depth = 1, aa_square = aa_depth * aa_depth;
    double y = st.getY();

    for(int j = 0; j < height; j++, y+=dy)
    {
        clock_t row = clock();
        double x = st.getX();
        for(int i = 0; i < width; i++, x+=dx)
        {
            std::vector<Color> temp_color(aa_square);

            for (int aax = 0; aax < aa_depth; aax++) {
                for(int aay = 0; aay < aa_depth; aay++){
                    
                    int aa_index = aay * aa_depth + aax;
                    Vector direction(x, y, -1);
                    Ray ray(camera_pos, direction.normalize());
                    temp_color[aa_index] =  scene.get_color(ray,i,j);

                    //if(temp_color[aa_index].red > 0.99){
                    //    printf ("No trangle found for x = %d y = %d\n", i, j);
                    //}
                }
            }

            pixels[i + j * width] = make_color(temp_color);

        }
        row = clock() - row;
        //printf ("%ld \t %f\n", row, ((float)row)/CLOCKS_PER_SEC);
        printf (".");
        fflush(stdout); 
    }

    t = clock() - t;
    printf ("\nIt took me %ld clicks (%f seconds) to render.\n",t,((float)t)/CLOCKS_PER_SEC);

    t = clock();
    Image().savebmp("scene.bmp",width,height,72,pixels);
    t = clock() - t;
    printf ("It took me %ld clicks (%f seconds) to save picture.\n",t,((float)t)/CLOCKS_PER_SEC);
    
    delete[] pixels;

    return 0;
}
