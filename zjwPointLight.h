#ifndef ZJWPOINTLIGHT_H
#define ZJWPOINTLIGHT_H
#include "zjwBaseLight.h"
#include "zjwLight.h"

#include <boost/core/ignore_unused.hpp>
namespace zjw
{
class zjwPointLight : public zjwBaseLight,public zjwLight
{
public:
    zjwPointLight() noexcept;
    zjwPointLight(glm::vec4 const& ambient,glm::vec4 const& diffuse,
                  glm::vec4 const& specular,glm::vec3 const& position,
                  zjwDecayFactor const& factor = {0.0f,1.0f,0.0f}) noexcept;
    zjwPointLight(zjwPointLight const&) = default;
    zjwPointLight(zjwPointLight&&) = default;
    zjwPointLight& operator=(zjwPointLight const&) = default;
    zjwPointLight& operator=(zjwPointLight&&) = default;

    void setPosition(glm::vec3 const& position) noexcept;
    glm::vec3 const& getPosition() const noexcept;

    void setConstantFactor(float const c) noexcept;
    void setLinearFactor(float const l,float const c = 0) noexcept;
    void setQuadraticFactor(float const q,float const l = 0,float const c = 0) noexcept;
    zjwDecayFactor const& getFactory() const noexcept;

    bool operator==(zjwPointLight const& other) const noexcept;

    void use(zjwProgram& program,std::string const& name) const noexcept override;
    void use(zjwProgram& program,std::string const& lightName,std::string const& factorName) const noexcept;
private:
    glm::vec3 _position;
    zjwDecayFactor _factor;
};
}
#endif // ZJWPOINTLIGHT_H
