#include "Colormap.h"
#include <fstream>
#include <iostream>
#include <algorithm>

std::map<std::string, int> Colormap::indices;
std::vector<std::string> Colormap::names;
ResourceManager::Image Colormap::colormaps;

Colormap::Colormap(std::string name)
{
    if (colormaps.data.empty())
    {
        init();
    }
    index = indices[name];
}

float Colormap::textureOffset()
{
    return (float)index / colormaps.height + 1.0f / (2.0f * colormaps.height);
}

glm::vec3 Colormap::color(float value)
{
    value = std::clamp(value, 0.0f, 1.0f);
    int x = std::clamp((int)(value * colormaps.width), 0, colormaps.width - 1);
    float t = value * colormaps.width - x;
    int right_X = std::min(x + 1, colormaps.width - 1);
    glm::vec4 left = colormaps.data[x + colormaps.width * index];
    glm::vec4 right = colormaps.data[right_X + colormaps.width * index];
    glm::vec4 color = glm::mix(left, right, t) / 255.0f;
    return glm::vec3(color);
}

glm::vec3 Colormap::operator()(float value)
{
    return color(value);
}

#include "PathFinder.h"
void Colormap::init()
{
    std::filesystem::path path = resolveFile("resources/colormaps.txt");
    std::ifstream file(path);
    if (!file.is_open())
    {
        throw std::runtime_error("Could not open file " + path.string());
    }
    std::string line;
    int offset = 0;
    while (std::getline(file, line))
    {        
        // Sanitize inputs in case the file contains windows line endings, i.e. \r\n instead of \n
        line.erase(std::remove(line.begin(), line.end(), '\r' ), line.end());
        line.erase(std::remove(line.begin(), line.end(), '\n' ), line.end());

        names.push_back(line);
        indices[line] = offset;
        offset++;
    }
    path = resolveFile("resources/colormaps.png");
    colormaps = ResourceManager::loadImage(path);
}
