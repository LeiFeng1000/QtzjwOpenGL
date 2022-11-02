#include "zjwConvert.h"

QVector2D zjw::zjwConvert::vec2ToQVector2D(const glm::vec2 &value) noexcept
{
    return QVector2D(value.x,value.y);
}

QVector3D zjw::zjwConvert::vec3ToQVector3D(const glm::vec3 &value) noexcept
{
    return QVector3D(value.x,value.y,value.z);
}

QVector4D zjw::zjwConvert::vec4ToQVector4D(const glm::vec4 &value) noexcept
{
    return QVector4D(value.x,value.y,value.z,value.w);
}

QMatrix4x4 zjw::zjwConvert::mat4ToQMatrix4x4(const glm::mat4 &value) noexcept
{
    return QMatrix4x4(glm::value_ptr(glm::transpose(value)));
}

glm::vec2 zjw::zjwConvert::qvec2ToGlm(const QVector2D &value) noexcept
{
    return glm::vec2(value.x(),value.y());
}

glm::vec3 zjw::zjwConvert::qvec3ToGlm(const QVector3D &value) noexcept
{
    return glm::vec3(value.x(),value.y(),value.z());
}

glm::vec4 zjw::zjwConvert::qvec4ToGlm(const QVector4D &value) noexcept
{
    return glm::vec4(value.x(),value.y(),value.z(),value.w());
}

glm::mat4 zjw::zjwConvert::qmatrixToGlm(const QMatrix4x4 &value) noexcept
{
    return glm::make_mat4(value.constData());
}

