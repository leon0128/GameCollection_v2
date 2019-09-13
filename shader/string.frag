#version 450 // openGL version

// uniform
uniform sampler2D uTexture; // テクスチャサンプリング

// 入力
in vec2 fragTexCoord; // テクスチャ座標
in vec4 color;        // 色
// 出力
out vec4 outColor; // 出力色

void main()
{
    // 出力色を uTexture から取得
    outColor = texture(uTexture,
                       fragTexCoord);
    if(outColor.w != 0.0)
    {
        outColor = vec4(0.5, 0.5, 0.5, 1.0);
    }
}