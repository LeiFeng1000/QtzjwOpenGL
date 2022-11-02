#include "zjwVao.h"

zjw::zjwVao::zjwVao()
    : _vao(new QOpenGLVertexArrayObject())
    , _vertexBuffer()
    , _indexBuffer(QOpenGLBuffer::IndexBuffer)
    , _normalBuffer()
    , _coordBuffer()
    , _numberPoint()
    , _otherBuffer()
{

}

zjw::zjwVao::zjwVao(zjwVao &&other) noexcept
    : _vao(std::move(other._vao))
    , _vertexBuffer(other._vertexBuffer)
    , _indexBuffer(other._indexBuffer)
    , _normalBuffer(other._normalBuffer)
    , _coordBuffer(other._coordBuffer)
    , _numberPoint(other._numberPoint)
    , _otherBuffer(std::move(other._otherBuffer))
{
    other._vertexBuffer = QOpenGLBuffer();
    other._indexBuffer = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    other._normalBuffer = QOpenGLBuffer();
    other._vertexBuffer = QOpenGLBuffer();
    other._numberPoint = 0;
}

zjw::zjwVao &zjw::zjwVao::operator=(zjwVao &&other) noexcept
{
    _vao = std::move(other._vao);
    _vertexBuffer = other._vertexBuffer;
    _indexBuffer = other._indexBuffer;
    _normalBuffer = other._normalBuffer;
    _coordBuffer = other._coordBuffer;
    _numberPoint = other._numberPoint;
    _otherBuffer = std::move(other._otherBuffer);

    other._vertexBuffer = QOpenGLBuffer();
    other._indexBuffer = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    other._normalBuffer = QOpenGLBuffer();
    other._coordBuffer = QOpenGLBuffer();
    other._numberPoint = 0;

    return *this;
}

bool zjw::zjwVao::setData(QOpenGLShaderProgram &program, void *data, size_t dataSize, const zjwAttribute &vertexAttribute, const zjwAttribute &normalAttribute, const zjwAttribute &coordAttribute, void *indexData, size_t indexDataSize, const GLenum indexDataType) noexcept
{
    vaoIfNotCreate();
    boost::ignore_unused(bind());

    bufferIfNotCreate(_vertexBuffer);
    _vertexBuffer.bind();

    _vertexBuffer.allocate(data,dataSize);
    program.setAttributeBuffer(vertexAttribute._location,vertexAttribute._type,vertexAttribute._offset,
                               vertexAttribute._tuppleSize,vertexAttribute._stride);
    program.setAttributeBuffer(normalAttribute._location,normalAttribute._type,normalAttribute._offset,
                               normalAttribute._tuppleSize,normalAttribute._stride);
    program.setAttributeBuffer(coordAttribute._location,coordAttribute._type,coordAttribute._offset,
                               coordAttribute._tuppleSize,coordAttribute._stride);

    bufferIfNotCreate(_indexBuffer);
    _indexBuffer.bind();
    _indexBuffer.allocate(indexData,indexDataSize);
    switch (indexDataType)
    {
    case GL_FLOAT:
        _numberPoint = indexDataSize / sizeof(GLfloat);
        break;
    case GL_UNSIGNED_INT:
        _numberPoint = indexDataSize / sizeof(GLuint);
        break;
    default:
        break;
    }

    unBind();

    return true;
}

bool zjw::zjwVao::bind() const noexcept
{
    if (!_vao->isCreated())
        return false;

    _vao->bind();
    return true;
}

void zjw::zjwVao::unBind() const noexcept
{
    _vao->release();
}

GLuint zjw::zjwVao::getId() const noexcept
{
    return _vao->objectId();
}

unsigned zjw::zjwVao::getNumberPoint() const noexcept
{
    return _numberPoint;
}

const QOpenGLBuffer &zjw::zjwVao::getVertexBuffer() const noexcept
{
    return _vertexBuffer;
}

const QOpenGLBuffer &zjw::zjwVao::getIndexBuffer() const noexcept
{
    return _indexBuffer;
}

const QOpenGLBuffer &zjw::zjwVao::getNormalBuffer() const noexcept
{
    return _normalBuffer;
}

const QOpenGLBuffer &zjw::zjwVao::getCoordBuffer() const noexcept
{
    return _coordBuffer;
}

void zjw::zjwVao::vaoIfNotCreate() noexcept
{
    _vao->isCreated();

    _vao->create();
}

void zjw::zjwVao::bufferIfNotCreate(QOpenGLBuffer &buffer) noexcept
{
    buffer.isCreated();

    buffer.create();
}

