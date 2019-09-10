#version 450 // openGL version

// uniform
uniform uFilledColor; // 満たす色

// 出力
out vec4 outColor; // 出力色

void main()
{
    // 色を出力
    outColor = uFilledColor;
}