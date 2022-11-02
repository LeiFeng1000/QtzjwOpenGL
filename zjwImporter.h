/**
 * @file zjwImport.h
 * @copyright copyright 2022 free
 * @state writing
 * @author ZJW
 * @date 2022年10月30日
 * @repair
 *
 * @brief 提供类zjwModelImporter
 */
#ifndef zjwModelImporter_H
#define zjwModelImporter_H
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>

#include "zjwMaterial.h"
namespace zjw
{
  /**
   * @author ZJW
   * @date 2022年10月30日
   * @repair
   *
   * @brief The zjwModelImporter class提供3D模型导入器。类是线程不安全的
   * @details
   *    @c zjwModelImporter   默认构造函数
   *    @c zjwModelImporter(std::string const& file);   构造，并导入文件file初始化数据
   *    @c bool loadFile(string);   加载文件file的数据
   *    @c bool hasVertex(unsigned) const noexcept;     查询是否拥有给定索引的模型的顶点数据
   *    @c verctor<glm::vec3> getVertex(unsigend) const noexcept;     获得给定索引的模型的顶点数据
   *    @c bool hasIndex(unsigned) const noexcept;      查询是否拥有给定索引的模型的索引数据
   *    @c verctor<unsigned> getIndex(unsigned) const noexcept;      获得给定索引的模型的索引数据
   *    @c bool hasTexture(unsigned) const noexcept;    查询是否拥有给定模型的
   *    @c verctor<glm::vec2> getTextureCoord(unsigned) const noexcept;     获得给定索引的模型的纹理坐标数据
   *    @c verctor<string> getTexture(unsigned) const noexcept;       获取给定索引的魔心的所有纹理贴图
 */
class zjwModelImporter
{
public:
  zjwModelImporter() noexcept;
  /**
     * @brief zjwModelImporter
     * @param file  模型文件
     */
  zjwModelImporter(std::string const& file);
  zjwModelImporter(zjwModelImporter const&) = default;
  zjwModelImporter(zjwModelImporter&&) = default;
  zjwModelImporter& operator=(zjwModelImporter const&) = default;
  zjwModelImporter& operator=(zjwModelImporter&&) = default;

  /**
   * @brief loadFile
   * @param file 模型文件名
   * @return 指示是否加载成功
   */
  bool loadFile(std::string const& file);

  /**
   * @brief hasVertex 查询包含索引为index的模型的顶点数据
   * @param index 指定索引
   * @return 包含有给定索引的模型的顶点数据时返回true，否则返回false
   */
  bool hasVertex(unsigned index = 0) const noexcept;
  /**
   * @brief getVertex 获取索引为index的模型的顶点数据
   * @param index 索引
   * @return 若成功时，包含了请求的顶点数据；失败时，为空
   */
  std::vector<glm::vec3> const& getVertex(unsigned index = 0) const noexcept;

  /**
   * @brief hasIndex 查询是否拥有给定索引的模型的索引数据
   * @param index 指定模型索引
   * @return true拥有查询的索引，否则false
   */
  bool hasIndex(unsigned index = 0) const noexcept;
  /**
   * @brief getIndex 获取索引为index的模型的索引数据
   * @param index 指定模型索引
   * @return 返回模型索引数据。若index无效，返回空
   */
  std::vector<unsigned> const& getIndex(unsigned index = 0) const noexcept;

  /**
   * @brief hasNormal 查询是否拥有指定索引的模型的法向量数据
   * @param index 指定模型索引
   * @return true,拥有给定索引的模型的法向量数据；false,无数据
   */
  bool hasNormal(unsigned index = 0) const noexcept;
  /**
   * @brief getNormal 获取指定索引的模型的法向量数据
   * @param index 指定索引
   * @return 给定索引的法向量数据，若无此数据返回空数组
   */
  std::vector<glm::vec3> const& getNormal(unsigned index = 0) const noexcept;

  /**
   * @brief hasTextureCoord 查询是否拥有索引为index的模型的纹理坐标数据
   * @param index 指定索引
   * @return 是否拥有索引
   */
  bool hasTextureCoord(unsigned index = 0) const noexcept;
  /**
   * @brief getCoord 获取索引为index的模型的纹理坐标数据
   * @param index 指定模型索引
   * @return 模型索引数据，如无模型数据返回空的数组
   */
  std::vector<glm::vec2> const& getTextureCoord(unsigned index = 0) const noexcept;

protected:
    bool _load(std::string const& file);
    void _processNode(aiNode const* node,aiScene const* scene);
    void _processMesh(aiMesh const* mesh,aiScene const* scene);
private:
    std::vector<std::vector<glm::vec3>> _vertexData;
    std::vector<std::vector<unsigned>> _indexData;
    std::vector<std::vector<glm::vec3>> _normalData;
    std::vector<std::vector<glm::vec2>> _coordData;

    std::vector<std::vector<std::string>> _textureData;
    std::vector<zjwMaterial> _materialData;

    std::vector<glm::vec3> _emptyVec3Data;
    std::vector<glm::vec2> _emptyVec2Data;
    std::vector<unsigned> _emptyUintData;
};
}
#endif // zjwModelImporter_H
