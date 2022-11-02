#ifndef ZJWTEXTURE_H
#define ZJWTEXTURE_H
#include <QOpenGLTexture>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_4_3_Core>
#include <memory>
namespace zjw
{
class zjwTexture
{
public:
    zjwTexture();
    zjwTexture(QOpenGLTexture::Target target);
    zjwTexture(std::string const& t2dFile);
    zjwTexture(zjwTexture const&) = default;
    zjwTexture(zjwTexture&& other);
    zjwTexture& operator=(zjwTexture const&) = default;
    zjwTexture& operator=(zjwTexture&& other);

    ~zjwTexture();

    [[nodiscard]]bool bind(GLenum binding = GL_TEXTURE0,QOpenGLFunctions* function = nullptr) const noexcept;
    void unBind();
    [[nodiscard]]bool create() noexcept;
    bool isCreated() const noexcept;
    GLuint id() const noexcept;
    
    [[nodiscard]]static zjwTexture createDepthImageTexture(QOpenGLFunctions& function,int w,int h) noexcept;
private:
    std::shared_ptr<QOpenGLTexture> _texture;
};
}
#endif // ZJWTEXTURE_H
