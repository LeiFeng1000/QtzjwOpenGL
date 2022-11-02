#include "zjwMaterial.h"
#include <boost/contract.hpp>

zjw::zjwMaterial::zjwMaterial() noexcept
    : zjw::zjwBaseLight()
{

}

zjw::zjwMaterial::zjwMaterial(const glm::vec4 &ambient, const glm::vec4 &diffuse, const glm::vec4 &specular, const float &shininess) noexcept
    : zjw::zjwBaseLight(ambient,diffuse,specular)
    , _shininess(shininess)
{

}

void zjw::zjwMaterial::setShininess(const float shininess) noexcept
{
    _shininess = shininess;
}

float zjw::zjwMaterial::getShininess() const noexcept
{
    return _shininess;
}

void zjw::zjwMaterial::use(zjwProgram &program, const std::string &name) const noexcept
{
    using namespace boost;

    boost::contract::check c = contract::function().precondition(
                [&](){
        BOOST_CONTRACT_ASSERT(program.setValue(name + ".shininess",_shininess));
    });

    zjwBaseLight::use(program,name);
}

bool zjw::zjwMaterial::operator==(const zjwMaterial &other) const noexcept
{
    return _shininess == other._shininess && static_cast<zjwBaseLight>(*this) == static_cast<zjwBaseLight>(other);
}

zjw::zjwMaterial zjw::zjwMaterial::goldMaterial() noexcept
{
    return zjwMaterial({0.24725f,0.1995f,0.0745f,1.0f},
                       {0.75146f,0.60648f,0.22648f,1.0f},
                       {0.62828f,0.5558f,0.36607f,1.0f},
                       51.2f);
}

zjw::zjwMaterial zjw::zjwMaterial::jaldMaterial() noexcept
{
    return zjwMaterial({0.135f,0.2225f,0.1575f,0.95f},
                       {0.54f,0.89f,0.63f,0.95f},
                       {0.3162f,0.3162f,0.3162f,0.95f},
                       12.8f);
}

zjw::zjwMaterial zjw::zjwMaterial::pearlMaterial() noexcept
{
    return zjwMaterial({0.25f,0.20725f,0.20725f,0.922f},
                       {1.0f,0.829f,0.829f,0.922f},
                       {0.2966f,0.2966f,0.2966f,0.922f},
                       11.264f);
}

zjw::zjwMaterial zjw::zjwMaterial::silverMaterial() noexcept
{
    return zjwMaterial({0.19225f,0.19225f,0.19225f,1.0f},
                       {0.50754f,0.50754f,0.50754f,1.0f},
                       {0.50827f,0.50827f,0.50827f,1.0f},
                       51.2f);
}
