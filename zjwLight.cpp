#include "zjwLight.h"


zjw::zjwLight::zjwLight() noexcept
    : _type(zjwLightType::Ambient)
{

}

zjw::zjwLight::zjwLight(const zjwLightType &type) noexcept
    : _type(type)
{

}

void zjw::zjwLight::setType(const zjwLightType &type) noexcept
{
    _type = type;
}

zjw::zjwLightType zjw::zjwLight::getType() const noexcept
{
    return _type;
}
