#pragma once

#include <GL/glew.h>

class VertexArray
{
public:
    // 第一引数は頂点配列のポインタ
    // 第二引数は頂点配列の要素数
    // 第三引数はインデックス配列のポインタ
    // 第四匹数はインデックス配列の要素数
    VertexArray(float* vertices,
                unsigned int numVertices,
                unsigned int* indices,
                unsigned int numIndices);
    ~VertexArray();

    // 有効化
    void setActive();

private:
    // コンストラクタで呼び出す
    void enableAttribute();

    // メンバ変数
    unsigned int mNumVertices; // 頂点配列の要素数
    unsigned int mNumIndices;  // インデックス配列の要素数
    GLuint mVertexBufferID;    // 頂点配列の openGL ID
    GLuint mIndexBufferID;     // インデックス配列の openGL ID
    GLuint mVertexArrayID;     // 頂点配列オブジェクトの openGL ID
};