#ifndef PARAMS_H
#define PARAMS_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "../color.h"
#include "../rtweekend.h"

class RenderParameters
{
  public:
    RenderParameters()
        : lookfrom(13, 2, 3), lookat(0, 0, 0), vup(0, 1, 0), vfov(20), aspect_ratio(16.0 / 9.0), image_width(1920),
          samples_per_pixel(100), max_depth(50), defocus_angle(0.6), focus_dist(10.0), c(0.70, 0.80, 1.00)
    {
    }

    // Parameters
    point3 lookfrom;
    point3 lookat;
    vec3 vup;
    double vfov;
    double aspect_ratio;
    int image_width;
    int samples_per_pixel;
    int max_depth;
    double defocus_angle;
    double focus_dist;
    color c;

    void setFromConfigFile(const std::string &filename);
};

// TODO: not the best solution but works
std::vector<std::string> splitComma(std::string input)
{
    std::istringstream ss(input);
    std::vector<std::string> tokens;
    std::string token;

    while (std::getline(ss, token, ','))
    {
        tokens.push_back(token);
    }

    return tokens;
}

std::vector<std::vector<std::string>> parse_config_file(const std::string &filename)
{
    std::vector<std::vector<std::string>> params;
    std::ifstream file(filename);
    std::vector<std::string> lines;

    if (!file.is_open())
    {
        std::cerr << "Error: Failed to open file " << filename << std::endl;
        return params;
    }

    std::string line;

    while (std::getline(file, line))
    {
        std::istringstream is_line(line);
        std::string key;
        if (std::getline(is_line, key, '='))
        {
            std::string value;
            if (std::getline(is_line, value))
            {
                params.push_back(splitComma(value));
            }
        }
    }
    return params;
}

void RenderParameters::setFromConfigFile(const std::string &filename)
{
    std::vector<std::vector<std::string>> values = parse_config_file(filename);

    if (values.size() != 11)
    {
        std::cerr << "Error: Configuration file does not contain all required parameters\n";
        return;
    }

    // Set parameters based on parsed values
    lookfrom = point3(std::stod(values[0][0]), std::stod(values[0][1]), std::stod(values[0][2]));
    lookat = point3(std::stod(values[1][0]), std::stod(values[1][1]), std::stod(values[1][2]));
    vup = vec3(std::stod(values[2][0]), std::stod(values[2][1]), std::stod(values[2][2]));
    vfov = std::stod(values[3][0]);
    aspect_ratio = std::stod(values[4][0]);
    image_width = std::stod(values[5][0]);
    samples_per_pixel = std::stoi(values[6][0]);
    max_depth = std::stoi(values[7][0]);
    defocus_angle = std::stod(values[8][0]);
    focus_dist = std::stod(values[9][0]);
    c = color(std::stod(values[10][0]), std::stod(values[10][1]), std::stod(values[10][2]));

    std::cout << "Parameters set from config file: " << filename << std::endl;
}

#endif
