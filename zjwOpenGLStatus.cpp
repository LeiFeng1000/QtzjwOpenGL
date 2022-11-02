#include "zjwOpenGLStatus.h"

zjw::zjwOpenGLStatus::zjwOpenGLStatus() noexcept
    : _enableDepthTest(true)
    , _depthFunc(GL_LEQUAL)
    , _enableCullFace(true)
    , _frontFace(GL_CCW)
    , _isClearColor(true)
    , _colorClear(1.0f,1.0f,1.0f,1.0f)
    , _isClearDepth(true)
    , _depthClear(1.0f)
{

}

void zjw::zjwOpenGLStatus::setDepthTestStatus(bool enable, GLenum func) noexcept
{
    _enableDepthTest = enable;
    _depthFunc = func;
}

void zjw::zjwOpenGLStatus::setCullFaceStatus(bool enable, GLenum frontFace) noexcept
{
    _enableCullFace = enable;
    _frontFace = frontFace;
}

void zjw::zjwOpenGLStatus::setColorClear(const glm::vec4 &color) noexcept
{
    _colorClear = color;
}

void zjw::zjwOpenGLStatus::setDepthClear(const float z) noexcept
{
    _depthClear = z;
}

void zjw::zjwOpenGLStatus::use(QOpenGLFunctions &function) const noexcept
{
    if (_isClearColor)
    {
        function.glClearColor(_colorClear.x,_colorClear.y,_colorClear.z,_colorClear.w);
        function.glClear(GL_COLOR_BUFFER_BIT);
    }
    if (_isClearDepth)
    {
        function.glClearDepthf(_depthClear);
        function.glClear(GL_DEPTH_BUFFER_BIT);
    }

    if (_enableDepthTest)
        function.glEnable(GL_DEPTH_TEST);
    else
        function.glDisable(GL_DEPTH_TEST);
    function.glDepthFunc(_depthFunc);

    if (_enableCullFace)
        function.glEnable(GL_CULL_FACE);
    else
        function.glDisable(GL_CULL_FACE);
    function.glFrontFace(_frontFace);
}

