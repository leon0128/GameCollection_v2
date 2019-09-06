#include "shader.hpp"

Shader::Shader():
    mVertexShaderID(0),
    mFragmentShaderID(0),
    mShaderProgramID(0)
{
}

bool Shader::load(const std::string& vertexShaderName,
                  const std::string& fragmentShaderName)
{
    // 頂点シェーダーとプログラムシェーダーのコンパイル
    if(!compile(vertexShaderName,
                GL_VERTEX_SHADER,
                mVertexShaderID) ||
       !compile(fragmentShaderName,
                GL_FRAGMENT_SHADER,
                mFragmentShaderID))
    {
        return false;
    }

    // 頂点シェーダーとフラグメントシェーダーをリンク
    mShaderProgramID = glCreateProgram();
    glAttachShader(mShaderProgramID,
                   mVertexShaderID);
    glAttachShader(mShaderProgramID,
                   mFragmentShaderID);
    glLinkProgram(mShaderProgramID);

    // リンクの確認
    if(!isValidProgram())
        return false;

    return true;
}