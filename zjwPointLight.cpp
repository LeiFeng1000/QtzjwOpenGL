#include "zjwPointLight.h"


zjw::zjwPointLight::zjwPointLight() noexcept
    : zjwBaseLight()
    , zjwLight(zjwLightType::Point)
    , _position(1.0f,0.0f,0.0f)
    , _factor{0.0f,1.0f,0.0f}
{

}

void zjw::zjwPointLight::setPosition(const glm::vec3 &position) noexcept
{
    _position = position;
}

const glm::vec3 &zjw::zjwPointLight::getPosition() const noexcept
{
    return _position;
}

void zjw::zjwPointLight::setConstantFactor(const float c) noexcept
{
    _factor.setConstantFactor(c);
}

void zjw::zjwPointLight::setLinearFactor(const float l, const float c) noexcept
{
    _factor.setLinearFactor(l,c);
}

void zjw::zjwPointLight::setQuadraticFactor(const float q, const float l, const float c) noexcept
{
    _factor.setQuadraticFactor(q,l,c);
}

const zjw::zjwDecayFactor &zjw::zjwPointLight::getFactory() const noexcept
{
    return _factor;
}

bool zjw::zjwPointLight::operator==(const zjwPointLight &other) const noexcept
{
    return static_cast<zjwBaseLight>(*this)==static_cast<zjwBaseLight>(other) &&
            _position == other._position &&
            (_factor <=> other._factor)==0;
}

void zjw::zjwPointLight::use(zjwProgram &program, const std::string &name) const noexcept
{
    program.setValue((name + ".position").c_str(),zjwConvert::vec3ToQVector3D(_position));
    _factor.use(program,name);

    zjwBaseLight::use(program,name);
}

void zjw::zjwPointLight::use(zjwProgram &program, const std::string &lightName, const std::string &factorName) const noexcept
{
    program.setValue(lightName + ".position",zjwConvert::vec3ToQVector3D(_position));
    _factor.use(program,factorName);

    zjwBaseLight::use(program,lightName);
}

zjw::zjwPointLight::zjwPointLight(const glm::vec4 &ambient, const glm::vec4 &diffuse, const glm::vec4 &specular, const glm::vec3 &position, const zjwDecayFactor &factor) noexcept
    : zjwBaseLight(ambient,diffuse,specular)
    , zjwLight(zjwLightType::Point)
    , _position(position)
    , _factor(factor)
{

}
