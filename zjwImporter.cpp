#include "zjwImporter.h"
#include <boost/core/ignore_unused.hpp>
#include <boost/contract.hpp>
#include <fstream>
#include <iostream>

zjw::zjwModelImporter::zjwModelImporter(const std::string &file)
{
    loadFile(file);
}

bool zjw::zjwModelImporter::loadFile(const std::string &file)
{
    using namespace boost;

    _vertexData.clear();
    _indexData.clear();
    _normalData.clear();
    _coordData.clear();

    return _load(file);
}

bool zjw::zjwModelImporter::hasVertex(unsigned index) const noexcept
{
  return _vertexData.size() > index && !_vertexData[index].empty();
}

const std::vector<glm::vec3> &zjw::zjwModelImporter::getVertex(unsigned index) const noexcept
{
    if (hasVertex(index))
      return _vertexData[index];
    else
      return _emptyVec3Data;
}

bool zjw::zjwModelImporter::hasIndex(unsigned index) const noexcept
{
  return _indexData.size() > index && !_indexData[index].empty();
}

const std::vector<unsigned> &zjw::zjwModelImporter::getIndex(unsigned index) const noexcept
{
    if (hasIndex(index))
      return _indexData[index];
    else
      return _emptyUintData;
}

bool zjw::zjwModelImporter::hasNormal(unsigned index) const noexcept
{
  return _normalData.size() > index && !_normalData[index].empty();
}

const std::vector<glm::vec3> &zjw::zjwModelImporter::getNormal(unsigned index) const noexcept
{
  if (hasNormal(index))
    return _normalData.at(index);
  else
    return _emptyVec3Data;
}

bool zjw::zjwModelImporter::hasTextureCoord(unsigned index) const noexcept
{
  return index < _coordData.size() && !_coordData[index].empty();
}

const std::vector<glm::vec2> &zjw::zjwModelImporter::getTextureCoord(unsigned index) const noexcept
{
    if (hasTextureCoord(index))
      return _coordData[index];
    else
      return _emptyVec2Data;
}

bool zjw::zjwModelImporter::_load(const std::string &file)
{
    Assimp::Importer importer;
    auto scene = importer.ReadFile(file.c_str(),
                                   aiProcess_CalcTangentSpace       |
                                   aiProcess_Triangulate            |
                                   aiProcess_JoinIdenticalVertices  |
                                   aiProcess_SortByPType);
    if (nullptr == scene)
        return false;
    _processNode(scene->mRootNode,scene);
    return true;
}

void zjw::zjwModelImporter::_processNode(const aiNode *node, const aiScene *scene)
{
    for (unsigned i{0};i < node->mNumMeshes;++i)
        _processMesh(scene->mMeshes[node->mMeshes[i]],scene);

    for (unsigned i{0};i < node->mNumChildren;++i)
        _processNode(node->mChildren[i],scene);
}

void zjw::zjwModelImporter::_processMesh(const aiMesh *mesh, const aiScene *scene)
{
    boost::ignore_unused(scene);

    _vertexData.push_back({});
    _indexData.push_back({});
    _normalData.push_back({});
    _coordData.push_back({});
    _textureData.push_back({});
    _materialData.push_back({});


    for (unsigned i{0}; i < mesh->mNumVertices; ++i)
    {
        //顶点数据
        _vertexData.back().push_back({
                                         mesh->mVertices[i].x,
                                         mesh->mVertices[i].y,
                                         mesh->mVertices[i].z
                                     });

        //法向量数据
        if (mesh->HasNormals())
        {
            _normalData.back().push_back({
                                             mesh->mNormals[i].x,
                                             mesh->mNormals[i].y,
                                             mesh->mNormals[i].z
                                         });
        }

        //纹理贴图坐标数据
        if (mesh->HasTextureCoords(0))
            _coordData.back().push_back({
                                            mesh->mTextureCoords[0][i].x,
                                            mesh->mTextureCoords[0][i].y,
                                        });
    }

    //处理面数据，添加索引数据
    for (unsigned i{0}; i < mesh->mNumFaces; ++i)
    {
        auto face {mesh->mFaces[i]};
        for (auto j{0u};j < face.mNumIndices;++j)
            _indexData.back().push_back(face.mIndices[j]);
    }

    //纹理贴图和材质
    if (mesh->mMaterialIndex >= 0)
      {
        auto materials = scene->mMaterials[mesh->mMaterialIndex];

      }
}
