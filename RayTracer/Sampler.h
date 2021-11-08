#pragma once
#include "Renderer.h"
#include "Image.h"


class Sampler
{
public:
	virtual glm::vec3 value(const glm::vec2& uv, const glm::vec3& p) const = 0;
};

class ColorSampler : public Sampler {
public:
    ColorSampler() = default;
    ColorSampler(const glm::vec3& color) : color{ color } {}
    virtual glm::vec3 value(const glm::vec2& uv, const glm::vec3& p) const override
    {
        return color;
    }
public:
    glm::vec3 color;
};

class CheckerSampler : public Sampler {
public:
    CheckerSampler() = default;
    CheckerSampler(std::shared_ptr<Sampler> even, std::shared_ptr<Sampler> odd, float scale = 1)
        : even{ even }, odd{ odd }, scale{ 1 } {}
    CheckerSampler(const glm::vec3& color1, const glm::vec3& color2, float scale = 1)
        : even{ std::make_shared<ColorSampler>(color1) }, odd{ std::make_shared<ColorSampler>(color2) },
        scale{ scale } {}
    virtual glm::vec3 value(const glm::vec2& uv, const glm::vec3& p) const override;
public:
    float scale = 1;
    std::shared_ptr<Sampler> odd;
    std::shared_ptr<Sampler> even;
};

class TextureSampler : public Sampler {
public:
    TextureSampler() = default;
    TextureSampler(std::shared_ptr<Image> image, float scale = 1) : image{ image }, scale{ scale } {}
    virtual glm::vec3 value(const glm::vec2 & uv, const glm::vec3 & p) const override;
public:
    float scale = 1;
    std::shared_ptr<Image> image;
};

//inline glm::vec3 ColorToVec3(const color_t& color)
//{
//    glm::vec3 out_color;
//    out_color.r = color.r / (float)255;
//    out_color.g = color.g / (float)255;
//    out_color.b = color.b / (float)255;
//        
//    return out_color;
//}