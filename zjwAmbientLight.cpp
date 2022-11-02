#include "zjwAmbientLight.h"

#include <boost/contract.hpp>
#include <algorithm>

zjw::zjwAmbientLight::zjwAmbientLight(const glm::vec4 &ambientColor) noexcept
    : zjwLight()
    , _ambient(ambientColor)
{

}

void zjw::zjwAmbientLight::setAmbient(const glm::vec4 &ambientColor) noexcept
{
  _ambient = ambientColor;
}

const glm::vec4 &zjw::zjwAmbientLight::ambient() const noexcept
{
  return _ambient;
}

glm::vec4 zjw::zjwAmbientLight::operator()() const noexcept
{
  return _ambient;
}

float zjw::zjwAmbientLight::r() const noexcept
{
  return _ambient.r;
}

float zjw::zjwAmbientLight::g() const noexcept
{
  return _ambient.g;
}

float zjw::zjwAmbientLight::b() const noexcept
{
  return _ambient.b;
}

float zjw::zjwAmbientLight::a() const noexcept
{
  return _ambient.a;
}

void zjw::zjwAmbientLight::setR(float r) noexcept
{
  _ambient.r = r;
}

void zjw::zjwAmbientLight::setG(float g) noexcept
{
  _ambient.g = g;
}

void zjw::zjwAmbientLight::setB(float b) noexcept
{
  _ambient.b = b;
}

void zjw::zjwAmbientLight::setA(float a) noexcept
{
  _ambient.a = a;
}

std::strong_ordering zjw::zjwAmbientLight::operator<=>(zjwAmbientLight const& other) const noexcept
{
    auto tp {glm::value_ptr(_ambient)};
    auto op {glm::value_ptr(other._ambient)};

    using namespace std;
    if (equal(tp,tp + 4,op,op + 4))
        return strong_ordering::equal;
    else if (lexicographical_compare(tp,tp + 4,op,op + 4))
        return strong_ordering::less;
    else
        return strong_ordering::greater;
}

bool zjw::zjwAmbientLight::use(zjwProgram &program, const std::string &name) const noexcept
{
    using namespace boost::contract;

    if (program.isLinked())
      {
        return program.setValue(name,zjwConvert::vec4ToQVector4D(ambient()));
      }
    return false;
}
