struct VS_OUT
{
    float4 pos : SV_POSITION;
    float3 col : COLOR;
};

float4 PSMain(VS_OUT input) : SV_Target
{
    return float4(input.col, 1.0f);
}
