#ifndef ZJWOPENGLSTATUS_H
#define ZJWOPENGLSTATUS_H
#include <QOpenGLFunctions>
#include <optional>
#include <vector>

#include <glm/glm.hpp>

namespace zjw
{
class zjwOpenGLStatus
{
public:
    zjwOpenGLStatus() noexcept;

    void setDepthTestStatus(bool enable,GLenum func) noexcept;
    void setCullFaceStatus(bool enable,GLenum frontFace) noexcept;
    void setColorClear(glm::vec4 const& color) noexcept;
    void setDepthClear(float const z) noexcept;

    void use(QOpenGLFunctions& function) const noexcept;
private:
    bool _enableDepthTest;  //是否启用深度测试
    GLenum _depthFunc;

    bool _enableCullFace;   //是否启用背面消除
    GLenum _frontFace;

    bool _isClearColor; //是否进行颜色缓存清理
    glm::vec4 _colorClear;

    bool _isClearDepth; //是否进行深度清理
    float _depthClear;
};
}
#endif // ZJWOPENGLSTATUS_H
