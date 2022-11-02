#ifndef ZJWPROGRAM_H
#define ZJWPROGRAM_H
#include <QOpenGLShaderProgram>
#include <memory>

namespace zjw
{
class zjwProgram
{
public:
    explicit zjwProgram() noexcept;
    explicit zjwProgram(std::string const& vsFile,std::string const& fsFile) noexcept;
    explicit zjwProgram(zjwProgram const& other) noexcept;
    explicit zjwProgram(zjwProgram&& other) noexcept;
    zjwProgram& operator=(zjwProgram& other) noexcept;
    zjwProgram& operator=(zjwProgram&& other) noexcept;

    bool setProgram(std::string const& vsFile,std::string const& fsFile);
    bool setProgram(std::string const& vsFile,std::string const& gsFile,std::string const& fsFile);

    template<typename T>
    bool setValue(std::string const& name,T const& value);
    int getUniform(std::string const& name) const noexcept;

    QOpenGLShaderProgram& getProgram() noexcept;
    GLuint getId() noexcept;
    void bind() const noexcept;
    bool isLinked() const noexcept;
    void destory() noexcept;

    bool operator==(zjwProgram const& other) const noexcept;
private:
    std::shared_ptr<QOpenGLShaderProgram> _program;
};

template<typename T>
bool zjwProgram::setValue(const std::string &name, const T &value)
{
    auto const location {_program->uniformLocation(name.c_str())};
    if (-1 == location)
    {
        if (-1 == location)
            return false;
    }

    _program->setUniformValue(location,value);
    return true;
}

}
#endif // ZJWPROGRAM_H
