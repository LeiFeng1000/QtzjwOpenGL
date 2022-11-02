#ifndef ZJWLIGHT_H
#define ZJWLIGHT_H

#include <glm/glm.hpp>
namespace zjw
{
enum struct zjwLightType : unsigned
{
    Ambient = 0,
    Direction,
    Point,
    Spot
};
class zjwLight
{
public:
    zjwLight() noexcept;
    zjwLight(zjwLightType const& type) noexcept;

    zjwLight(zjwLight const&) noexcept = default;
    zjwLight(zjwLight&&) noexcept = default;
    zjwLight& operator=(zjwLight const&) noexcept = default;
    zjwLight& operator=(zjwLight&&) noexcept = default;

    void setType(zjwLightType const& type) noexcept;
    zjwLightType getType() const noexcept;
private:
    zjwLightType _type;
};
}
#endif // ZJWLIGHT_H
