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

struct Vertex {
    float2 position;
    float3 color;  
};

VS2RS VS(uint vertex_id: SV_VertexID)
{
    Vertex vertices[3];
    vertices[0] = Vertex(float2(-0.7, -0.7), float3(1.0, 0.0, 0.0));
    vertices[1] = Vertex(float2(0.0, 0.7), float3(0.0, 1.0, 0.0));
    vertices[2] = Vertex(float2(0.7, -0.7), float3(0.0, 0.0, 1.0));

    VS2RS output;
    output.position = float4(vertices[vertex_id].position, 0.0, 1.0);
    output.color = vertices[vertex_id].color;

    return output;
}

float4 PS(RS2PS input) : SV_Target {
    return float4(input.color, 1.0);
}
