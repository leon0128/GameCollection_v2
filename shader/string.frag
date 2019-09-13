#version 450 // openGL version

// uniform
uniform sampler2D uTexture; // テクスチャサンプリング
uniform float uAlpha;       // 透明度

// 入力
in vec2 fragTexCoord; // テクスチャ座標
// 出力
out vec4 outColor; // 出力色

void main()
{
    // 出力色を uTexture から取得
    outColor = texture(uTexture,
                       fragTexCoord);
}