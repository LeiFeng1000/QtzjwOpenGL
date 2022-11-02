#ifndef ZJWSPOTLIGHT_H
#define ZJWSPOTLIGHT_H
#include "zjwBaseLight.h"
#include "zjwLight.h"

#include <boost/core/ignore_unused.hpp>
namespace zjw
{
class zjwSpotLight : public zjwBaseLight,public zjwLight
{
public:
    zjwSpotLight();
    zjwSpotLight(glm::vec4 const& ambient,glm::vec4 const& diffuse,glm::vec4 const& specular,
                 glm::vec3 const& position,glm::vec3 const& direction,
                 zjwDecayFactor const& dfactor,zjwDecayFactor const& afactor);

    void setPosition(glm::vec3 const& position) noexcept;
    glm::vec3 const& getPosition() const noexcept;
    void setDirection(glm::vec3 const& direction) noexcept;
    glm::vec3 const& getDirection() const noexcept;

    void setConstantDFactor(float const c) noexcept;
    void setLinearDFactor(float const l,float const c = 0) noexcept;
    void setQuadraticDFactor(float const q,float const l = 0,float const c = 0) noexcept;
    zjwDecayFactor const& getDFactor() const noexcept;

    void setConstantAFactor(float const c) noexcept;
    void setLinearAFactor(float const l,float const c = 0) noexcept;
    void setQuadraticAFactor(float const q,float const l = 0,float const c = 0) noexcept;
    zjwDecayFactor const& getAFactor() const noexcept;

    bool operator==(zjwSpotLight const& other) const noexcept;

    void use(zjwProgram& program,std::string const& name) const noexcept;
private:
    glm::vec3 _position;
    glm::vec3 _direction;

    zjwDecayFactor _dfactor;
    zjwDecayFactor _afactor;
};
}
#endif // ZJWSPOTLIGHT_H
