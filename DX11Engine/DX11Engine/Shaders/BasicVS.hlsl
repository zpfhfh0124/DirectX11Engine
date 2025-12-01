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
    o.pos = float4(input.pos, 1.0f);
    o.col = input.col;
    return o;
}
