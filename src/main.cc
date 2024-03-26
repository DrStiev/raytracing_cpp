// https://github.com/fralken/ray-tracing-in-one-weekend
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "example.h"
#include "external/log.h"
#include "external/params.h"

const char *filenames[10] = {
    "img/random_spheres.ppm", "img/two_spheres.ppm",        "img/earth.ppm",       "img/two_perlin_spheres.ppm",
    "img/quads.ppm",          "img/simple_lights.ppm",      "img/cornell_box.ppm", "img/cornell_smoke.ppm",
    "img/final_scene.ppm",    "img/another_last_scene.ppm",
};

bool choice(int choice, RenderParameters params)
{
    switch (choice)
    {
    case 1:
        LOG(DEBUG) << "CHOSEN: RANDOM_SPHERES()";
        random_spheres(params);
        return true;
    case 2:
        LOG(DEBUG) << "CHOSEN: TWO_SPHERES()";
        two_spheres(params);
        return true;
    case 3:
        LOG(DEBUG) << "CHOSEN: EARTH()"; // FAIL
        earth(params);
        return true;
    case 4:
        LOG(DEBUG) << "CHOSEN: TWO_PERLIN_SPHERES()";
        two_perlin_spheres(params);
        return true;
    case 5:
        LOG(DEBUG) << "CHOSEN: QUADS()";
        quads(params);
        return true;
    case 6:
        LOG(DEBUG) << "CHOSEN: SIMPLE_LIGHT()";
        simple_light(params);
        return true;
    case 7:
        LOG(DEBUG) << "CHOSEN: CORNELL_BOX()"; // FAIL
        cornell_box(params);
        return true;
    case 8:
        LOG(DEBUG) << "CHOSEN: CORNELL_SMOKE()"; // FAIL
        cornell_smoke(params);
        return true;
    case 9:
        LOG(DEBUG) << "CHOSEN: FINAL_SCENE()"; // FAIL
        final_scene(params);
        return true;
    case 10:
        LOG(DEBUG) << "CHOSEN: ANOTHER_LAST_SCENE()";
        another_last_scene(params);
        return true;
    default:
        LOG(ERROR) << "INVALID CHOICE";
        return false;
    }
}

bool saveImg(int i, RenderParameters params)
{
    std::ofstream file;
    file.open(filenames[i - 1], std::fstream::in | std::fstream::out | std::fstream::trunc);
    std::cout.rdbuf(file.rdbuf());
    if (!choice(i, params))
    {
        std::cerr << "Invalid choice " << i << std::endl;
        return false;
    }
    file.close();
    return true;
}

int main(int argc, char *argv[])
{
    LOG(INFO) << "START WORKING WITH RAYTRACING";
    // set parameters before run
    RenderParameters params;
    params.setFromConfigFile("E:/personal/raytracing_Cpp/parameters.txt");
    if (argc < 2)
    {
        for (int i = 1; i <= 10; i++)
            saveImg(i, params);
    }
    else
    {
        int i = std::stoi(argv[1]);
        if (saveImg(i, params))
            return 0;
        std::cerr << "Invalid choice! Available options: ";
        for (int j = 1; j <= 10; j++)
        {
            std::cerr << j;
            if (j < 10)
                std::cerr << ", ";
        }
        std::cerr << std::endl;
    }

    return 0;
}