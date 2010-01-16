texture RAWZdepth;

sampler currentFrameSampler = sampler_state
{
	texture = <RAWZdepth>;
	AddressU = CLAMP;
	AddressV = CLAMP;
	MINFILTER = POINT;
	MAGFILTER = POINT;
};

struct VSOUT
{
	float4 vertPos : POSITION;
	float2 UVCoord : TEXCOORD0;
};

struct VSIN
{
	float4 vertPos : POSITION0;
	float2 UVCoord : TEXCOORD0;
};

VSOUT FrameVS(VSIN IN)
{
	VSOUT OUT = (VSOUT)0.0f;	// initialize to zero, avoid complaints.
	OUT.vertPos = IN.vertPos;
	OUT.UVCoord = IN.UVCoord;
	return OUT;
}


float4 Test(VSOUT IN) : COLOR0
{
		float4 black = float4(1.0, 0.0, 0.0, 0.0);
		float4 sample=tex2D(currentFrameSampler,IN.UVCoord);
		
		float3 rawval = floor( 255.0 * sample.arg +0.5);
		float z = dot( rawval, float3(0.996093809371817670572857294849,0.0038909914428586627756752238080039,1.5199185323666651467481343000015e-5) / 255.0);
	
		black.r=z;
	
		return(black);
}

technique t0 
{
	pass p0
	{
		VertexShader = compile vs_1_1 FrameVS();
		PixelShader = compile ps_2_0 Test();
	}
	
}