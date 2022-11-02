#include "zjwTexture.h"
#include <iostream>
#include <QOpenGLContext>
#include <boost/contract.hpp>

zjw::zjwTexture::zjwTexture()
    : _texture(new QOpenGLTexture(QOpenGLTexture::Target2D))
{
}

zjw::zjwTexture::zjwTexture(QOpenGLTexture::Target target)
    : _texture(new QOpenGLTexture(target))
{
}

zjw::zjwTexture::zjwTexture(const std::string &t2dFile)
    : _texture(new QOpenGLTexture(QImage(t2dFile.c_str()).mirrored()))
{
}

zjw::zjwTexture::zjwTexture(zjwTexture &&other)
    : _texture(std::move(other._texture))
{
}

zjw::zjwTexture &zjw::zjwTexture::operator=(zjwTexture && other)
{
    _texture = std::move(other._texture);
    return *this;
}

zjw::zjwTexture::~zjwTexture()
{

}

bool zjw::zjwTexture::bind(GLenum binding,QOpenGLFunctions* function) const noexcept
{
    using namespace boost;
    contract::check check = contract::function().precondition(
                [&](){
        BOOST_CONTRACT_ASSERT(_texture->isCreated());
        BOOST_CONTRACT_ASSERT(function);
    });

    function->glActiveTexture(GL_TEXTURE0);
    _texture->bind(binding);

    return true;
}

void zjw::zjwTexture::unBind()
{
    _texture->release();
}

bool zjw::zjwTexture::create() noexcept
{
    return _texture->create();
}

bool zjw::zjwTexture::isCreated() const noexcept
{
    return _texture->isCreated();
}

GLuint zjw::zjwTexture::id() const noexcept
{
    return _texture->textureId();
}

zjw::zjwTexture zjw::zjwTexture::createDepthImageTexture(QOpenGLFunctions &function, int w, int h) noexcept
{
    zjwTexture texture;

    using namespace boost;
    contract::check check = contract::function().precondition(
                [&](){
        BOOST_CONTRACT_ASSERT(w > 0 && h > 0);
    }).postcondition(
                [&](){
        BOOST_CONTRACT_ASSERT(texture.create());
    });
    
    Q_UNUSED(texture.bind());
    function.glTexImage2D(GL_TEXTURE_2D,0,GL_DEPTH_COMPONENT32,w,h,0,
                          GL_DEPTH_COMPONENT,GL_FLOAT,NULL);
    function.glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    function.glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    function.glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    function.glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
//    function.glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_COMPARE_MODE,GL_COMPARE_REF_TO_TEXTURE);
//    function.glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_COMPARE_FUNC,GL_LEQUAL);
    texture._texture->release();
    
    return texture;
}

