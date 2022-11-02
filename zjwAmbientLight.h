/**
 * @file zjwAmbientLight.h
 * @copyright copyright 2022 free
 * @date 2022年10月30日
 * @author ZJW
 *
 * @brief 提供类zjwAmbientLight
 */

#ifndef ZJWAMBIENTLIGHT_H
#define ZJWAMBIENTLIGHT_H
#include "zjwLight.h"
#include "zjwProgram.h"
#include "zjwConvert.h"

#include <boost/contract.hpp>
#include <compare>
namespace zjw
{

  /**
 * @brief The zjwAmbientLight class 继承自类zjwLight，提供环境光的抽象
 * @date 2022年10月30日
 * @author ZJW
 * @repair
 *
 * @details
 *    @c zjwAmbientLight() noexcept;                                  默认构造函数，构造环境光(0.0,0.0,0.0,1.0)
 *    @c zjwAmbientLight(glm::vec4) noexcept;                         构造给定环境光
 *    @c float r/g/b/a() const noexcept;                                获取相关分量
 *    @c glm::vec4 operator()/ambient() const noexcept;               获取灯光值
 *    @c void setR/G/B(float) noexcept;                               设置相关分量
 *    @c bool use(zjwProgram const& program,string const&) noexcept;  将环境光引用到程序管线
 *    @c strong_ordering operator<=>(zjwAmbientLight const&) const noexcept; 比较
 */
class zjwAmbientLight : public zjwLight
{
public:
  zjwAmbientLight(glm::vec4 const& ambientColor = {0.0f,0.0f,0.0f,1.0f}) noexcept ;
  zjwAmbientLight(zjwAmbientLight const& other) noexcept = default;
  zjwAmbientLight(zjwAmbientLight&& other) noexcept = default;
  zjwAmbientLight& operator=(zjwAmbientLight const& other) noexcept = default;
  zjwAmbientLight& operator=(zjwAmbientLight&& other) noexcept = default;

  /**
   * @brief setAmbient
   * @param ambientColor
   */
  void setAmbient(glm::vec4 const& ambientColor) noexcept;
  /**
   * @brief ambient
   * @return 环境光的值
   */
  glm::vec4 const& ambient() const noexcept;
  glm::vec4 operator()() const noexcept;

  /**
   * @brief r
   * @return red分量
   */
  float r() const noexcept;
  /**
   * @brief g
   * @return green分量
   */
  float g() const noexcept;
  /**
   * @brief b
   * @return blue分量
   */
  float b() const noexcept;
  /**
   * @brief a
   * @return alpha分量
   */
  float a() const noexcept;
  /**
   * @brief setR
   * @param r
   */
  void setR(float r) noexcept;
  /**
   * @brief setG
   * @param g
   */
  void setG(float g) noexcept;
  /**
   * @brief setB
   * @param b
   */
  void setB(float b) noexcept;
  /**
   * @brief setA
   * @param a
   */
  void setA(float a) noexcept;

  std::strong_ordering operator<=>(zjwAmbientLight const& other) const noexcept;

  /**
   * @brief use 将环境光应用到程序管线
   * @param program指定有效程序。
   * @param name 指定程序管线内部变量.
   * @return 指示是否应用成功。若程序无效，或者找不到name变量，返回false;
   */
  bool use(zjwProgram& program,std::string const& name) const noexcept;
private:
    glm::vec4 _ambient;
};
}
#endif // ZJWAMBIENTLIGHT_H
