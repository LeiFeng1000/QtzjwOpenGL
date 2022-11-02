#ifndef ZJWMATERIAL_H
#define ZJWMATERIAL_H
#include "zjwBaseLight.h"
namespace zjw
{
class zjwMaterial : public zjw::zjwBaseLight
{
public:
    zjwMaterial() noexcept;
    zjwMaterial(glm::vec4 const& ambient,glm::vec4 const& diffuse,
                glm::vec4 const& specular,float const& shininess) noexcept;

    void setShininess(float const shininess) noexcept;
    float getShininess() const noexcept;

    void use(zjwProgram& program,std::string const& name) const noexcept;

    bool operator==(zjwMaterial const& other) const noexcept;

    [[nodiscard]]static zjwMaterial goldMaterial() noexcept;
    [[nodiscard]]static zjwMaterial jaldMaterial() noexcept;
    [[nodiscard]]static zjwMaterial pearlMaterial() noexcept;
    [[nodiscard]]static zjwMaterial silverMaterial() noexcept;
private:
    float _shininess;
};
}
#endif // ZJWMATERIAL_H
