#include "zjwProgram.h"
#include <boost/contract.hpp>

zjw::zjwProgram::zjwProgram() noexcept
    : _program(new QOpenGLShaderProgram{})
{

}

zjw::zjwProgram::zjwProgram(const std::string &vsFile, const std::string &fsFile) noexcept
    : zjwProgram()
{
    Q_UNUSED(setProgram(vsFile,fsFile));
}

zjw::zjwProgram::zjwProgram(const zjwProgram &other) noexcept
    : _program(other._program)
{

}

zjw::zjwProgram::zjwProgram(zjwProgram &&other) noexcept
    : _program(std::move(other._program))
{

}

zjw::zjwProgram &zjw::zjwProgram::operator=(zjwProgram &other) noexcept
{
    _program = other._program;
    return *this;
}

zjw::zjwProgram& zjw::zjwProgram::operator=(zjwProgram&& other) noexcept
{
    _program = std::move(other._program);
    return *this;
}

bool zjw::zjwProgram::setProgram(const std::string &vsFile, const std::string &fsFile)
{
    if (!_program->addCacheableShaderFromSourceFile(QOpenGLShader::Vertex,vsFile.c_str()))
        return false;
    if (!_program->addCacheableShaderFromSourceFile(QOpenGLShader::Fragment,fsFile.c_str()))
        return false;

    if (_program->link())
        return true;

    return false;
}

bool zjw::zjwProgram::setProgram(const std::string &vsFile, const std::string &gsFile, const std::string &fsFile)
{
    if(!_program->addCacheableShaderFromSourceFile(QOpenGLShader::Vertex,vsFile.c_str()))
        return false;
    if(!_program->addCacheableShaderFromSourceFile(QOpenGLShader::Geometry,gsFile.c_str()))
        return false;
    if(!_program->addCacheableShaderFromSourceFile(QOpenGLShader::Fragment,fsFile.c_str()))
        return false;

    if(_program->link())
        return true;

    return false;
}

int zjw::zjwProgram::getUniform(const std::string &name) const noexcept
{
    using namespace boost;
    contract::check c = contract::function().precondition(
                [&](){
        BOOST_CONTRACT_ASSERT(isLinked());
    });

    return _program->uniformLocation(name.c_str());
}

QOpenGLShaderProgram &zjw::zjwProgram::getProgram() noexcept
{
    return *_program;
}

GLuint zjw::zjwProgram::getId() noexcept
{
    return _program->programId();
}

void zjw::zjwProgram::bind() const noexcept
{
    _program->bind();
}

bool zjw::zjwProgram::isLinked() const noexcept
{
    return _program->isLinked();
}

void zjw::zjwProgram::destory() noexcept
{
    _program.reset();
}

bool zjw::zjwProgram::operator==(const zjwProgram &other) const noexcept
{
    return _program == other._program;
}
