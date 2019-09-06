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

void Shader::unload() const
{
    glDeleteProgram(mShaderProgramID);
    glDeleteShader(mVertexShaderID);
    glDeleteShader(mFragmentShaderID);
}

bool Shader::compile(const std::string& filename,
                     GLenum type,
                     GLuint& outShader)
{
    // ファイルを開く
    std::ifstream shaderFile(filename);
    if(!shaderFile.is_open())
    {
        SDL_Log("Cannot open shader file: %s",
                filename.c_str());
        return false;
    }

    // ファイルテキストを const char* として読み込む
    std::stringstream sstream;
    sstream << shaderFile.rdbuf();
    const char* contents = sstream.str().c_str();

    // シェーダー作成
    outShader = glCreateShader(type);

    // コンパイル
    glShaderSource(outShader,
                   1,
                   &(contents),
                   nullptr);
    glCompileShader(outShader);
    if(!isCompiled(outShader))
    {
        SDL_Log("Failed to compile shader: %s",
                filename.c_str());
        return false;
    }

    return true;
}

bool Shader::isCompiled(GLuint shader) const
{
    GLint status; // コンパイルステータス

    // 問い合わせ
    glGetShaderiv(shader,
                  GL_COMPILE_STATUS,
                  &status);
    if(status != GL_TRUE)
    {
        char buffer[512] = "";
        memset(buffer,
               0,
               512);
        glGetShaderInfoLog(shader,
                           511,
                           nullptr,
                           buffer);
        SDL_Log("Failed to compile GLSL: \n%s",
                buffer);
        return false;
    }

    return true;
}

void Shader::isValidProgram() const
{
    GLint status; // コンパイルステータス

    // リンク状況の問い合わせ
    glGetProgramiv(mShaderProgramID,
                   GL_LINK_STATUS,
                   &status);

    if(status != GL_TRUE)
    {
        char buffer[512] = "";
        memset(buffer,
               0,
               512);
        glGetProgramInfoLog(mShaderProgramID,
                            511,
                            nullptr,
                            buffer);
        SDL_Log("Failed to link GLSL: \n%s",
                buffer);
        return false;
    }

    return true;
}