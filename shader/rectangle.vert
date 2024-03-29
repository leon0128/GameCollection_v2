#version 450 // openGL version

// uniform
uniform mat4 uWorldTransform; // ワールド変換行列
uniform mat4 uViewProjection; // Sprite 用のビュー射影行列
uniform vec4 uFilledColor;    // 矩形を満たす色

// 入力
layout(location = 0) in vec3 inPosition; // 位置
// 出力
out vec4 filledColor;

void main()
{
    // 位置を同次座標変換
    vec4 position = vec4(inPosition,
                         1.0f);
    
    // 行列の演算
    gl_Position = position * 
                  uWorldTransform *
                  uViewProjection;

    filledColor = uFilledColor;
}