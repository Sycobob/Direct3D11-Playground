cbuffer cbPerObject
{
	matrix gWorldViewProj;
};

struct VertexIn
{
	float3 PosL  : POSITION;
	float4 Color : COLOR;
};

struct VertexOut
{
	float4 PosH  : SV_POSITION;
	float4 Color : COLOR;
};

VertexOut main(VertexIn vIn)
{
	VertexOut vOut;

	vOut.PosH = mul(float4(vIn.PosL, 1.0f), gWorldViewProj);
	vOut.Color = vIn.Color;

	return vOut;
}