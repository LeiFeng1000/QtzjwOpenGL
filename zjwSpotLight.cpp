#include "zjwSpotLight.h"
#include <boost/contract.hpp>

zjw::zjwSpotLight::zjwSpotLight()
    : zjwBaseLight()
    , zjwLight(zjwLightType::Spot)
    , _position{1.0f,0.0f,0.0f}
    , _direction{1.0f,1.0f,1.0f}
{

}

zjw::zjwSpotLight::zjwSpotLight(const glm::vec4 &ambient, const glm::vec4 &diffuse, const glm::vec4 &specular, const glm::vec3 &position, const glm::vec3 &direction, const zjwDecayFactor &dfactor, const zjwDecayFactor &afactor)
    : zjwBaseLight(ambient,diffuse,specular)
    , zjwLight(zjwLightType::Spot)
    , _position(position)
    , _direction(direction)
    , _dfactor(dfactor)
    , _afactor(afactor)
{

}

void zjw::zjwSpotLight::setPosition(const glm::vec3 &position) noexcept
{
    _position = position;
}

const glm::vec3 &zjw::zjwSpotLight::getPosition() const noexcept
{
    return _position;
}

void zjw::zjwSpotLight::setDirection(const glm::vec3 &direction) noexcept
{
    using namespace boost;
    auto oldValue = _direction;
    contract::check check = contract::function().precondition(
                [&](){
        BOOST_CONTRACT_ASSERT(direction != glm::vec3(0.0f,0.0f,0.0f));  //不能设置为0向量
    }).except(
                [&](){
        _direction = oldValue;
    });

    _direction = direction;
}

const glm::vec3 &zjw::zjwSpotLight::getDirection() const noexcept
{
    return _direction;
}

void zjw::zjwSpotLight::setConstantDFactor(const float c) noexcept
{
    using namespace boost;
    auto old = _dfactor;
    contract::check check = contract::function().precondition(
                [&](){
        BOOST_CONTRACT_ASSERT(c > 0);
    }).except(
                [&](){
        _dfactor = old;
    });

    _dfactor.setConstantFactor(c);
}

void zjw::zjwSpotLight::setLinearDFactor(const float l, const float c) noexcept
{
    using namespace boost;
    auto old = _dfactor;
    contract::check check = contract::function().precondition(
                [&](){
        BOOST_CONTRACT_ASSERT(l > 0 && c >= 0);
    }).except(
                [&](){
        _dfactor = old;
    });

    _dfactor.setLinearFactor(l,c);
}

void zjw::zjwSpotLight::setQuadraticDFactor(const float q, const float l, const float c) noexcept
{
    using namespace boost;
    auto old = _dfactor;
    contract::check check = contract::function().precondition(
                [&](){
        BOOST_CONTRACT_ASSERT(q > 0 && l >= 0 && c >= 0);
    }).except(
                [&](){
        _dfactor = old;
    });

    _dfactor.setQuadraticFactor(q,l,c);
}

const zjw::zjwDecayFactor &zjw::zjwSpotLight::getDFactor() const noexcept
{
    return _dfactor;
}

void zjw::zjwSpotLight::setConstantAFactor(const float c) noexcept
{
    using namespace boost;
    auto old = _dfactor;
    contract::check check = contract::function().precondition(
                [&](){
        BOOST_CONTRACT_ASSERT(c > 0);
    }).except(
                [&](){
        _afactor = old;
    });

    _afactor.setConstantFactor(c);
}

void zjw::zjwSpotLight::setLinearAFactor(const float l, const float c) noexcept
{
    using namespace boost;
    auto old = _afactor;
    contract::check check = contract::function().precondition(
                [&](){
        BOOST_CONTRACT_ASSERT(l > 0 && c >= 0);
    }).except(
                [&](){
        _afactor = old;
    });

    _afactor.setLinearFactor(l,c);
}

void zjw::zjwSpotLight::setQuadraticAFactor(const float q, const float l, const float c) noexcept
{
    using namespace boost;
    auto old = _afactor;
    contract::check check = contract::function().precondition(
                [&](){
        BOOST_CONTRACT_ASSERT(q > 0 && l >= 0 && c >= 0);
    }).except(
                [&](){
        _afactor = old;
    });

    _afactor.setQuadraticFactor(q,l,c);
}

const zjw::zjwDecayFactor &zjw::zjwSpotLight::getAFactor() const noexcept
{
    return _afactor;
}

bool zjw::zjwSpotLight::operator==(const zjwSpotLight &other) const noexcept
{
    return _position == other._position &&
            _direction == other._direction &&
            (_dfactor <=> other._dfactor) == 0 &&
            (_afactor <=> other._afactor) == 0 &&
            static_cast<zjwBaseLight>(*this) == static_cast<zjwBaseLight>(other);
}

void zjw::zjwSpotLight::use(zjwProgram &program, const std::string &name) const noexcept
{
    using namespace boost;
    contract::check c = contract::function().precondition(
                [&](){
        BOOST_CONTRACT_ASSERT(program.getUniform(name + ".position") != -1);
        BOOST_CONTRACT_ASSERT(program.getUniform(name + ".direction") != -1);
    });

    _afactor.use(program,name);
    _dfactor.use(program,name);

    zjwBaseLight::use(program,name);
}


