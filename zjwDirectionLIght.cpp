#include "zjwDirectionLight.h"

#include <boost/contract.hpp>

zjw::zjwDirectionLight::zjwDirectionLight() noexcept
    : zjwBaseLight()
    , zjwLight(zjwLightType::Direction)
    , _direction()
{

}

void zjw::zjwDirectionLight::setDirection(const glm::vec3 &direction) noexcept
{
    _direction = direction;
}

const glm::vec3 &zjw::zjwDirectionLight::getDirection() const noexcept
{
    return _direction;
}

bool zjw::zjwDirectionLight::use(zjwProgram &program, const std::string &name) const noexcept
{
    if (program.isLinked())
      {
        return program.setValue(name + ".direction",zjwConvert::vec3ToQVector3D(_direction)) &&
            zjwBaseLight::use(program,name);
      }

    return false;
}

bool zjw::zjwDirectionLight::operator==(const zjwDirectionLight &other) const noexcept
{
    return (_direction == other._direction && static_cast<zjw::zjwBaseLight>(*this)==static_cast<zjwBaseLight>(other));
}

zjw::zjwDirectionLight::zjwDirectionLight(const glm::vec4 &ambient, const glm::vec4 &diffuse, const glm::vec4 &specular, glm::vec3 direction) noexcept
    : zjwBaseLight(ambient,diffuse,specular)
    , zjwLight(zjwLightType::Direction)
    , _direction(direction)
{

}
