#ifndef ZJWVAO_H
#define ZJWVAO_H

#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <memory>
#include <vector>

//BOOST库
#include <boost/core/ignore_unused.hpp>
#include <boost/contract.hpp>
namespace zjw
{
struct zjwAttribute
{
    GLuint _location = 0;
    GLenum _type = GL_FLOAT;
    GLuint _offset = 0;
    GLuint _tuppleSize = 3;
    GLuint _stride = 0;
};

class zjwVao
{
public:
    zjwVao();
    zjwVao(zjwVao const&) = default;
    zjwVao(zjwVao&& other) noexcept;
    zjwVao& operator=(zjwVao const&) = default;
    zjwVao& operator=(zjwVao&& other) noexcept;

    template<typename T>
    [[nodiscard]]bool setVertexData(QOpenGLShaderProgram& program,std::vector<T> const& data,zjwAttribute const& attribute) noexcept;
    template<typename T>
    [[nodiscard]]bool setIndexData(QOpenGLShaderProgram& program,std::vector<T> const& data) noexcept;
    template<typename T>
    [[nodiscard]]bool setNormalData(QOpenGLShaderProgram& program,std::vector<T> const& data,zjwAttribute const& attribute) noexcept;
    template<typename T>
    [[nodiscard]]bool setCoordData(QOpenGLShaderProgram& program,std::vector<T> const& data,zjwAttribute const& attribute) noexcept;
    template<typename T>
    [[nodiscard]]bool setOtherData(QOpenGLShaderProgram& program,std::vector<T> const& data,zjwAttribute const& attribute) noexcept;

    [[nodiscard]]bool setData(QOpenGLShaderProgram& program,void* data,size_t dataSize,zjwAttribute const& vertexAttribute,zjwAttribute const& normalAttribute,
                              zjwAttribute const& coordAttribute,void* indexData,size_t indexDataSize,GLenum const indexDataType) noexcept;
    [[nodiscard]]bool bind() const noexcept;
    void unBind() const noexcept;
    GLuint getId() const noexcept;
    unsigned getNumberPoint() const noexcept;
    QOpenGLBuffer const& getVertexBuffer() const noexcept;
    QOpenGLBuffer const& getIndexBuffer() const noexcept;
    QOpenGLBuffer const& getNormalBuffer() const noexcept;
    QOpenGLBuffer const& getCoordBuffer() const noexcept;
protected:
    void vaoIfNotCreate() noexcept;
    void bufferIfNotCreate(QOpenGLBuffer& buffer) noexcept;
private:
    std::shared_ptr<QOpenGLVertexArrayObject> _vao;
    QOpenGLBuffer _vertexBuffer,_indexBuffer,_normalBuffer,_coordBuffer;

    GLuint _numberPoint;

    std::vector<QOpenGLBuffer> _otherBuffer;
};

template<typename T>
bool zjwVao::setCoordData(QOpenGLShaderProgram &program, const std::vector<T> &data, const zjwAttribute &attribute) noexcept
{
    using namespace boost;
    contract::check check = contract::function().precondition(
                [&](){
        BOOST_CONTRACT_ASSERT(program.isLinked());
        BOOST_CONTRACT_ASSERT(!data.empty());
    });

   vaoIfNotCreate();
   _vao->bind();

   bufferIfNotCreate(_coordBuffer);
   _coordBuffer.bind();

   _coordBuffer.allocate(data.data(),data.size() * sizeof(T));
   program.setAttributeBuffer(attribute._location,attribute._type,attribute._offset,
                              attribute._tuppleSize,attribute._stride);
   program.enableAttributeArray(attribute._location);

   unBind();
   return true;
}

template<typename T>
bool zjwVao::setNormalData(QOpenGLShaderProgram &program, const std::vector<T> &data, const zjwAttribute &attribute) noexcept
{
    using namespace boost;
    contract::check check = contract::function().precondition(
                [&](){
        BOOST_CONTRACT_ASSERT(program.isLinked());
        BOOST_CONTRACT_ASSERT(!data.empty());
    });

    vaoIfNotCreate();
    _vao->bind();

    bufferIfNotCreate(_normalBuffer);
    _normalBuffer.bind();

    _normalBuffer.allocate(data.data(),data.size() * sizeof(T));
    program.setAttributeBuffer(attribute._location,attribute._type,attribute._offset,
                               attribute._tuppleSize,attribute._stride);
    program.enableAttributeArray(attribute._location);
    unBind();

    return true;
}

template<typename T>
bool zjwVao::setIndexData(QOpenGLShaderProgram &program, const std::vector<T> &data) noexcept
{
    using namespace boost;
    contract::check check = contract::function().precondition(
                [&](){
        BOOST_CONTRACT_ASSERT(program.isLinked());
        BOOST_CONTRACT_ASSERT(!data.empty());
    });

    vaoIfNotCreate();
    _vao->bind();

    bufferIfNotCreate(_indexBuffer);
    _indexBuffer.bind();

    _indexBuffer.allocate(data.data(),data.size() * sizeof(T));

    if (std::is_same_v<T,GLuint>)
        _numberPoint = data.size();
    _vao->release();

    return true;
}

template<typename T>
bool zjwVao::setVertexData(QOpenGLShaderProgram &program, const std::vector<T> &data, const zjwAttribute &attribute) noexcept
{
    using namespace boost;
    contract::check check = contract::function().precondition(
                [&](){
        BOOST_CONTRACT_ASSERT(program.isLinked());
        BOOST_CONTRACT_ASSERT(!data.empty());
    });

    vaoIfNotCreate();
    _vao->bind();

    bufferIfNotCreate(_vertexBuffer);
    _vertexBuffer.bind();

    _vertexBuffer.allocate(data.data(),data.size() * sizeof(T));
    program.setAttributeBuffer(attribute._location,attribute._type,attribute._offset,
                               attribute._tuppleSize,attribute._stride);
    program.enableAttributeArray(attribute._location);
    if (_numberPoint == 0)
        switch (attribute._type)
        {
        case GL_FLOAT:
            _numberPoint = _vertexBuffer.size();
            break;
        default:
            break;
        }

    _vao->release();
    return true;
}
template<typename T>
bool zjw::zjwVao::setOtherData(QOpenGLShaderProgram &program, const std::vector<T> &data, const zjwAttribute &attribute) noexcept
{
    using namespace boost;
    contract::check check = contract::function().precondition(
                [&](){
        BOOST_CONTRACT_ASSERT(program.isLinked());
        BOOST_CONTRACT_ASSERT(!data.empty());
    });

    vaoIfNotCreate();
    _vao->bind();

    bufferIfNotCreate(_vertexBuffer);
    _vertexBuffer.bind();

    _vertexBuffer.allocate(data.data(),data.size() * sizeof(T));
    program.setAttributeBuffer(attribute._location,attribute._type,attribute._offset,
                               attribute._tuppleSize,attribute._stride);
    program.enableAttributeArray(attribute._location);

    _vao->release();
    return true;
}
}
#endif // ZJWVAO_H
