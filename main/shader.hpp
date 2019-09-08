#pragma once

#include "mathematics.hpp"
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <string>
#include <fstream>
#include <sstream>

class Shader
{
public:
    // uniform の型
    enum EType
    {
        FLOAT,
        COLOR,
        VECTOR3,
        MATRIX4
    };

    Shader();
    ~Shader(){}

    // 第一引数は頂点シェーダーのファイル名
    // 第二引数はフラグメントシェーダーのファイル名
    bool load(const std::string& vertexShaderName,
              const std::string& indexShaderName);
    void unload() const;

    // シェーダーの有効化
    void setActive() const;

    // uniform に値の設定
    void setUniform(const char* name,
                    EType type,
                    void* value) const;

private:
    // load() で実行
    bool compile(const std::string& filename, // ファイルからシェーダーをコンパイル
                 GLenum type,
                 GLuint& outShader);
    bool isCompiled(GLuint shader) const;     // コンパイルができたかの確認
    bool isValidProgram() const;              // リンクが有効か

    // メンバ変数
    GLuint mVertexShaderID;   // 頂点シェーダーID
    GLuint mFragmentShaderID; // フラグメントシェーダ―ID
    GLuint mShaderProgramID;  // シェーダープログラムID
};