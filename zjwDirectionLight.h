/**
 * @file  zjwDirectionLight.h
 * @copyright copyright 2022 free
 * @version 0.1
 * @author ZJW
 * @date 2022年10月30日
 * @repair
 *
 * @brief 提供了类zjwDirectionLight
 */
#ifndef ZJWDIRECTIONLIGHT_H
#define ZJWDIRECTIONLIGHT_H
#include "zjwBaseLight.h"
#include "zjwLight.h"
namespace zjw
{
  /**
   * @author ZJW
   * @date 2022年10月30日
   * @repair
   *
   * @brief The zjwDirectionLight class继承在zjwLight和zjwLightBase,提供一个具有方向的光源抽象
   * @details
   *    @c zjwDirectionLight() noexcept;    默认构造函数
   *    @c zjwDirectionLight(glm::vec4,glm::vec4,glm::vec4,glm::vec3) noexcept;   构造给定方向、环境光、漫反射光、镜面反射光的光源
   *    @c void setDirection(glm::vec3) noexcept;     设置光源的方向
   *    @c glm::vec3 const& getDirection() const noexcept;      获取光源的方向
   *    @c bool use(zjwProgram const& program,string const& name);    应用光源到着色器程序
 */
class zjwDirectionLight : public zjwBaseLight,public zjwLight
{
public:
    zjwDirectionLight() noexcept;
    zjwDirectionLight(glm::vec4 const& ambient,glm::vec4 const& diffuse,
                      glm::vec4 const& specular,glm::vec3 direction) noexcept;
    zjwDirectionLight(zjwDirectionLight const&) = default;
    zjwDirectionLight(zjwDirectionLight&&) = default;
    zjwDirectionLight& operator=(zjwDirectionLight const&) = default;
    zjwDirectionLight& operator=(zjwDirectionLight&&) = default;

    /**
     * @brief setDirection
     * @param direction 光源方向向量
     */
    void setDirection(glm::vec3 const& direction) noexcept;
    /**
     * @brief getDirection
     * @return 光源方向
     */
    glm::vec3 const& getDirection() const noexcept;

    /**
     * @brief use 应用光源到着色器程序
     * @param program   预应用到的有效着色器程序
     * @param name  变量名称，变量name的类型必须是一个结构，且拥有以下顺序无关的签名：
     *    @c struct *** { *** zjwBaseLight required ***; vec3 direction; };
     * @return 指示应用是否成功。
     */
    virtual bool use(zjwProgram& program,std::string const& name) const noexcept override;

    bool operator==(zjwDirectionLight const& other) const noexcept;
private:
    glm::vec3 _direction;
};
}
#endif // ZJWDIRECTIONLIGHT_H
