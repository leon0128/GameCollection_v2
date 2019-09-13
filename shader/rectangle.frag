#version 450 // openGL version

// 入力
in vec4 filledColor;
// 出力
out vec4 outColor; // 出力色

void main()
{
    // 色を出力
    outColor = filledColor;
}