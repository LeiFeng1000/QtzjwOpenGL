/**
 * @file zjwBaseLight.h
 * @copyright copyright 2022 free
 * @author ZJW
 * @date 2022年10月30日
 * @repair
 *
 * @brief 提供类zjwBaseLight
 */

#ifndef ZJWBASELIGHT_H
#define ZJWBASELIGHT_H
#include "zjwProgram.h"
#include "zjwConvert.h"

#include <glm/glm.hpp>
#include <boost/core/ignore_unused.hpp>
#include <compare>
namespace zjw
{
  /**
   * @author ZJW
   * @date  2022年10月30日
   * @repair
   *
   * @brief The zjwDecayFactor class                      提供一个一元二次函数，为了便于在渲染管线中快捷应用，定义了use函数
   * @c zjwOneVariableQuadratic() noexcept;               构造一个0函数
   * @c void setConstantFunction(float const c) noexceptr;     重新设置为常函数
   * @c void setLinearFunction(float const c,float const l) noexcept;        重新设置为线性函数
   * @c void setQuadraticFunction(float const c,float const l,float q) noexcept;    重新设置为二次函数
   * @c float operator()(float x) const noexcept;      返回值自变量为x的应变量
   * @c bool use(zjwProgram const& program,string const& name) const noexcept;      应用函数到程序管线
 */
struct zjwOneVariableQuadratic
{
    float _c;
    float _l;
    float _q;

    /**
     * @brief use 应用函数到程序管线中
     * @param program 一个有效的着色程序
     * @param name 变量名称.假设name变量是一个结构，且具有顺序无关的以下签名：
     *      @c struct *name* { float c; float l; float q; };
     * @return 指示应用是否成功。
     */
    bool use(zjwProgram& program, std::string const& name) const noexcept;
    /**
     * @brief operator () 求自变量为x的应变量的值
     * @param x
     * @return c + l * x + x * q * q
     */
    float operator()(float x) const noexcept;
    void setConstantFactor(float const c) noexcept;
    void setLinearFactor(float const l,float const c = 0) noexcept;
    void setQuadraticFactor(float const q,float const l = 0,float const c = 0) noexcept;

    std::strong_ordering operator<=>(zjwOneVariableQuadratic const& other) const noexcept;
};

/**
 * @author ZJW
 * @date 2022年10月30日
 * @repair
 *
 * @brief The zjwBaseLight class 是一个灯光的基础类，环境光、镜面反射光、漫反射光的聚合.
 * @details
 *    @c zjwBaseLight() noexcept;     构造分量均为零的环境光、镜面反射光、漫反射光
 *    @c zjwBaseLight(glm::vec4,glm::vec4,glm::vec4) noexcept;      构造指定的环境光、镜面反射光、漫反射光
 *    @c void setAmbient(glm::vec4) noexcept;     设置环境光
 *    @c glm::vec4 const& ambient() const noexcept;     获得环境光
 *    @c void setDiffuse(glm::vec4) noexcept;     设置漫反射光
 *    @c glm::vec4 const& diffuse() const noexcept;     获得漫反射光
 *    @c void setSpecular(glm::vec4) noexcept;    设置镜面反射光
 *    @c glm::vec4 const& specular() const noexcept;    获得镜面反射光
 *    @c virtual bool use(zjwProgram const& program,string const name) const noexcept;    应用到基础光到渲染管线
 */
class zjwBaseLight
{
public:
    zjwBaseLight() noexcept;
    zjwBaseLight(glm::vec4 const& ambient,glm::vec4 const& diffuse,glm::vec4 const& specular) noexcept;

    zjwBaseLight(zjwBaseLight const&) noexcept = default;
    zjwBaseLight(zjwBaseLight&&) noexcept = default;
    zjwBaseLight& operator=(zjwBaseLight const&) noexcept = default;
    zjwBaseLight& operator=(zjwBaseLight&&) noexcept = default;

    /**
     * @brief setAmbient
     * @param ambient环境光
     */
    void setAmbient(glm::vec4 const& ambient) noexcept;
    /**
     * @brief getAmbient
     * @return 环境光
     */
    glm::vec4 const& getAmbient() const noexcept;
    /**
     * @brief setDiffuse
     * @param diffuse漫反射光
     */
    void setDiffuse(glm::vec4 const& diffuse) noexcept;
    /**
     * @brief getDiffuse
     * @return 漫反射光
     */
    glm::vec4 const& getDiffuse() const noexcept;
    /**
     * @brief setSpecular
     * @param specular镜面反射
     */
    void setSpecular(glm::vec4 const& specular) noexcept;
    /**
     * @brief getSpecular
     * @return 镜面反射
     */
    glm::vec4 const& getSpecular() const noexcept;

    /**
     * @brief use 应用光到渲染管线，子类类重载该函数，必须调用父类的use函数。
     * @param program 预应用到的着色器程序。
     * @param name 变量名称.假设变量name是一个结构，且具有无关顺序的签名：
     *    @c struct *** { vec4 ambient; vec4 diffuse; vec4 specular; };
     * @return 指示应用是否成功。
     */
    virtual bool use(zjwProgram& program,std::string const& name) const noexcept;

    bool operator==(zjwBaseLight const& other) const noexcept;
    
protected:

private:
    glm::vec4 _ambient;
    glm::vec4 _diffuse;
    glm::vec4 _specular;
};
}
#endif // ZJWBASELIGHT_H
