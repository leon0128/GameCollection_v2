#include "vertex_array.hpp"

VertexArray::VertexArray(float* vertices,
                         unsigned int numVertices,
                         unsigned int* indices,
                         unsigned int numIndices):
    mNumVertices(numVertices),
    mNumIndices(numIndices),
    mVertexBufferID(0),
    mIndexBufferID(0),
    mVertexArrayID(0)
{
    // 頂点配列オブジェクトの作成
    glGenVertexArrays(1,
                      &mVertexArrayID);
    glBindVertexArray(mVertexArrayID);

    // 頂点バッファの作成
    glGenBuffers(1,
                 &mVertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER,
                 mVertexBufferID);
    glBufferData(GL_ARRAY_BUFFER,
                 numVertices * 8 * sizeof(float),
                 vertices,
                 GL_STATIC_DRAW);
    
    // インデックスバッファの作成
    glGenBuffers(1,
                 &mIndexBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,
                 mIndexBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 numIndices * sizeof(unsigned int),
                 indices,
                 GL_STATIC_DRAW);

    // 属性の設定
    enableAttribute();
}

VertexArray::~VertexArray()
{
    // 確保したバッファの削除
    glDeleteBuffers(1,
                    &mVertexBufferID);
    glDeleteBuffers(1,
                    &mIndexBufferID);
    glDeleteVertexArrays(1,
                         &mVertexArrayID);
}

void VertexArray::setActive() const
{
    glBindVertexArray(mVertexArrayID);
}

void VertexArray::enableAttribute() const
{
    // 頂点属性 0 (位置座標: float * 3)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(float) * 8,
                          0);
    
    // 頂点属性 1 (法線ベクトル: float * 3)
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(float) * 8,
                          reinterpret_cast<void*>(sizeof(float) * 3));

    // 頂点属性 2 (テクスチャ座標: float * 2)
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2,
                          2,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(float) * 8,
                          reinterpret_cast<void*>(sizeof(float) * 6));
}