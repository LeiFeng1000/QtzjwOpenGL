#include "zjwBaseLight.h"

#include <boost/contract.hpp>

zjw::zjwBaseLight::zjwBaseLight() noexcept
    : _ambient()
    , _diffuse()
    , _specular()

{

}

zjw::zjwBaseLight::zjwBaseLight(const glm::vec4 &ambient, const glm::vec4 &diffuse, const glm::vec4 &specular) noexcept
    : _ambient(ambient)
    , _diffuse(diffuse)
    , _specular(specular)
{

}

void zjw::zjwBaseLight::setAmbient(const glm::vec4 &ambient) noexcept
{
    _ambient = ambient;
}

const glm::vec4 &zjw::zjwBaseLight::getAmbient() const noexcept
{
    return _ambient;
}

void zjw::zjwBaseLight::setDiffuse(const glm::vec4 &diffuse) noexcept
{
    _diffuse = diffuse;
}

const glm::vec4 &zjw::zjwBaseLight::getDiffuse() const noexcept
{
    return _diffuse;
}

void zjw::zjwBaseLight::setSpecular(const glm::vec4 &specular) noexcept
{
    _specular = specular;
}

const glm::vec4 &zjw::zjwBaseLight::getSpecular() const noexcept
{
    return _specular;
}

bool zjw::zjwBaseLight::use(zjwProgram &program, const std::string &name) const noexcept
{
    if (program.isLinked())
      {
        return program.setValue(name + ".ambient",zjwConvert::vec4ToQVector4D(_ambient)) &&
            program.setValue(name + ".diffuse",zjwConvert::vec4ToQVector4D(_diffuse)) &&
            program.setValue(name + ".specular",zjwConvert::vec4ToQVector4D(_specular));
      }
    return false;
}

bool zjw::zjwBaseLight::operator ==(const zjwBaseLight &other) const noexcept
{
    return (_ambient == other._ambient && _diffuse == other._diffuse && _specular == other._specular);
}

bool zjw::zjwOneVariableQuadratic::use(zjwProgram &program, const std::string &name) const noexcept
{
    if (program.isLinked())
      {
        return program.setValue(name + ".c",_c) &&
               program.setValue(name + ".l",_l) &&
               program.setValue(name + ".q",_q);
      }
    return false;
}

float zjw::zjwOneVariableQuadratic::operator()(float x) const noexcept
{
  return _c + x * _l + x * _q * _q;
}

void zjw::zjwOneVariableQuadratic::setConstantFactor(const float c) noexcept
{
    _c = c;
    _l = 0;
    _q = 0;
}

void zjw::zjwOneVariableQuadratic::setLinearFactor(const float l, const float c) noexcept
{
    _c = c;
    _l = l;
    _q = 0;
}

void zjw::zjwOneVariableQuadratic::setQuadraticFactor(const float q, const float l, const float c) noexcept
{
    _q = q;
    _l = l;
    _c = c;
}

std::strong_ordering zjw::zjwOneVariableQuadratic::operator<=>(zjwOneVariableQuadratic const& other) const noexcept
{
    using namespace std;

    if (_c == other._c && _l == other._l && _q == other._l)
        return strong_ordering::equal;
    if (_c < other._c && _l < other._l && _q < other._q)
        return strong_ordering::less;
    else
        return strong_ordering::greater;
}
