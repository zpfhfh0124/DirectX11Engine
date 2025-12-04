cbuffer MatrixBuffer : register(b0)
{
    //float4x4 gWorld;
    //float4x4 gView;
    //float4x4 gProj;
    float4x4 gWVP;
}

struct VS_IN
{
    float3 pos : POSITION;
    float3 col : COLOR;
};

struct VS_OUT
{
    float4 pos : SV_POSITION;
    float3 col : COLOR;
};

VS_OUT VSMain(VS_IN input)
{
    VS_OUT o;
    
    //float4 worldPos = mul(float4(input.pos, 1.0f), gWorld);
    //float4 viewPos  = mul(worldPos, gView);
    //float4 projPos  = mul(viewPos,  gProj);
    float4 p = float4(input.pos, 1.0f);
    o.pos = mul(p, gWVP);
    o.col = input.col;
    return o;
}
