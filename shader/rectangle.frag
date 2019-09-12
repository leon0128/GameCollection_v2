#version 450 // openGL version

// uniform
uniform vec4 uFilledColor; // 満たす色

// 出力
out vec4 outColor; // 出力色

void main()
{
    // 色を出力
    outColor = vec4(1, 0.5, 0.5, 1);
}