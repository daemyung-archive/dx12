struct IA2VS
{
    float2 position : POSITION;
    float3 color : COLOR;
};

struct VS2RS
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
};

struct RS2PS
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
};

VS2RS VS(IA2VS input)
{
    VS2RS output;
    output.position = float4(input.position, 0.0, 1.0);
    output.color = input.color;

    return output;
}

float4 PS(RS2PS input) : SV_Target {
    return float4(input.color, 1.0);
}
