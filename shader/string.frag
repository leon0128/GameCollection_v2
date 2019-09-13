#version 450 // openGL version

// uniform
uniform sampler2D uTexture; // テクスチャサンプリング

// 入力
in vec2 fragTexCoord; // テクスチャ座標
in vec4 charColor;    // 文字の色
in vec4 bgColor;      // 背景色
// 出力
out vec4 outColor; // 出力色

void main()
{
    // 出力色を uTexture から取得
    outColor = texture(uTexture,
                       fragTexCoord);
    if(outColor.w != 0.0)
    {
        float w = outColor.w;
        outColor = charColor;
        outColor.w = w;
    }
    else
    {
        outColor = bgColor;
    }
}