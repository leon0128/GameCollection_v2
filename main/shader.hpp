#pragma once

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <string>
#include <fstream>
#include <sstream>

class Shader
{
public:
    Shader();
    ~Shader(){}

    // 第一引数は頂点シェーダーのファイル名
    // 第二引数はフラグメントシェーダーのファイル名
    bool load(const std::string& vertexShaderName,
              const std::string& indexShaderName);
    void unload();

    // シェーダーの有効化
    void setActive();

    // シェーダープログラムの uniform に値の設定
    void setMatrix4Uniform(const char* uniformName,
                           const Matrix4& matrix);
    void setVector3Uniform(const char* uniformName,
                           const Vector3& vector);
    void setFloatUniform(const char* uniformName,
                         float value);
    void setColorUniform(const char* uniformName,
                         const SDL_Color& color);

private:
    // load() で実行
    bool compile(const std::string& filename, // ファイルからシェーダーをコンパイル
                 GLenum type,
                 GLuint& outShader);
    bool isCompiled(GLuint shader);           // コンパイルができたかの確認
    bool isValidProgram();                    // リンクが有効か

    // メンバ変数
    GLuint mVertexShaderID;   // 頂点シェーダーID
    GLuint mFragmentShaderID; // フラグメントシェーダ―ID
    GLuint mShaderProgramID;  // シェーダープログラムID
};