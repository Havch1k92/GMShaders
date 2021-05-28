#include "BaseVSShader.h"

#include "fxctmp9\gmodscreenspace_vs20.inc"
#include "fxctmp9\lensflare_ps20.inc"

BEGIN_VS_SHADER(LensFlare, "Help for LensFlare.")

BEGIN_SHADER_PARAMS
	SHADER_PARAM(BLOOMTEXTURE, SHADER_PARAM_TYPE_TEXTURE, "_rt_SmallFB0", "")
	SHADER_PARAM(DIRTTEXTURE, SHADER_PARAM_TYPE_TEXTURE, "post/screen_100_1", "")
	SHADER_PARAM(FBTEXTURE, SHADER_PARAM_TYPE_TEXTURE, "_rt_FullFrameFB", "")
END_SHADER_PARAMS

SHADER_INIT
{
	LoadTexture(BLOOMTEXTURE);
	LoadTexture(FBTEXTURE);
	LoadTexture(DIRTTEXTURE);
}

SHADER_FALLBACK { return nullptr; }

SHADER_DRAW
{
	if (pShaderShadow) // Shadow state
	{
		pShaderShadow->EnableDepthWrites(false);

		pShaderShadow->EnableTexture(SHADER_SAMPLER0, true);
		pShaderShadow->EnableTexture(SHADER_SAMPLER1, true);
		pShaderShadow->EnableTexture(SHADER_SAMPLER3, true);
		pShaderShadow->VertexShaderVertexFormat(VERTEX_POSITION, 1, NULL, 0);

		DECLARE_STATIC_VERTEX_SHADER(gmodscreenspace_vs20);
		SET_STATIC_VERTEX_SHADER(gmodscreenspace_vs20);

		DECLARE_STATIC_PIXEL_SHADER(lensflare_ps20);
		SET_STATIC_PIXEL_SHADER(lensflare_ps20);
		
	}
	if (pShaderAPI) // Dynamic state
	{
		// Bind FBTEXTURE to texture slot s0
		BindTexture(SHADER_SAMPLER0, BLOOMTEXTURE);
		BindTexture(SHADER_SAMPLER1, DIRTTEXTURE);
		BindTexture(SHADER_SAMPLER3, FBTEXTURE);

		DECLARE_DYNAMIC_VERTEX_SHADER(gmodscreenspace_vs20);
		SET_DYNAMIC_VERTEX_SHADER(gmodscreenspace_vs20);

		DECLARE_DYNAMIC_PIXEL_SHADER(lensflare_ps20);
		SET_DYNAMIC_PIXEL_SHADER(lensflare_ps20);
	}

	Draw();
}
END_SHADER