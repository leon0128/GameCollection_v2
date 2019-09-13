#version 450 // openGL version

// uniform
uniform mat4 uWorldTransform; // ワールド変換行列
uniform mat4 uViewProjection; // ビュー射影行列
uniform vec4 uCharColor;    // 文字の色

// 入力
layout(location = 0) in vec3 inPosition; // 頂点位置
layout(location = 2) in vec2 inTexCoord; // テクスチャ座標
// 出力
out vec2 fragTexCoord; // テクスチャ座標

void main()
{
    // 四次元ベクトルに変換
    vec4 position = vec4(inPosition,
                         1.0f);
    
    // 行列演算
    gl_Position = position *
                  uWorldTransform *
                  uViewProjection;
    
    // テクスチャ座標の設定
    fragTexCoord = inTexCoord;
}