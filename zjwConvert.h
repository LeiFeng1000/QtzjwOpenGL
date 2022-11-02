/**
 * @file zjwConvert.h
 * @copyright copyright 2022 free
 * @author ZJW
 * @date 2022年10月30日
 * @repair
 *
 * @brief 提供类zjwConvert
 */
#ifndef ZJWCONVERT_H
#define ZJWCONVERT_H
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

//Qt库
#include <QVector2D>
#include <QVector3D>
#include <QVector4D>
#include <QMatrix4x4>

namespace zjw
{
  /**
   * @author ZJW
   * @date 2022年10月30日
   * @repair
   *
   * @brief The zjwConvert class 提供了glm库定义的向量、矩阵到Qt库定义的向量、矩阵之间的转换的常量函数
 */
class zjwConvert
{
public:
  /**
     * @brief vec2ToQVector2D glm::vec2 -> QVector2D
     * @param value
     * @return
     */
  [[nodiscard]]static QVector2D vec2ToQVector2D(glm::vec2 const& value) noexcept;
  /**
   * @brief vec3ToQVector3D glm::vec3 --> QVector3D
   * @param value
   * @return
   */
  [[nodiscard]]static QVector3D vec3ToQVector3D(glm::vec3 const& value) noexcept;
  /**
   * @brief vec4ToQVector4D glm::vec4 --> QVector4D
   * @param value
   * @return
   */
  [[nodiscard]]static QVector4D vec4ToQVector4D(glm::vec4 const& value) noexcept;
  /**
   * @brief mat4ToQMatrix4x4 glm::mat4 --> QMatrix4x4
   * @param value
   * @return
   */
  [[nodiscard]]static QMatrix4x4 mat4ToQMatrix4x4(glm::mat4 const& value) noexcept;
  /**
   * @brief qvec2ToGlm QVector2D --> glm::vec2
   * @param value
   * @return
   */
  [[nodiscard]]static glm::vec2 qvec2ToGlm(QVector2D const& value) noexcept;
  /**
   * @brief qvec3ToGlm QVector3D --> glm::vec3
   * @param value
   * @return
   */
  [[nodiscard]]static glm::vec3 qvec3ToGlm(QVector3D const& value) noexcept;
  /**
   * @brief qvec4ToGlm QVector4D --> glm::vec4
   * @param value
   * @return
   */
  [[nodiscard]]static glm::vec4 qvec4ToGlm(QVector4D const& value) noexcept;
  /**
   * @brief qmatrixToGlm QMatrix4x4 --> glm::mat
   * @param value
   * @return
   */
  [[nodiscard]]static glm::mat4 qmatrixToGlm(QMatrix4x4 const& value) noexcept;
private:
};
}
#endif // ZJWCONVERT_H
