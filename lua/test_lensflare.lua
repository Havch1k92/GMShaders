local render = render
local _rt_FullFrameFB = render.GetScreenEffectTexture()
local _rt_SmallFB0 = render.GetSmallTex0()

local matLensflare = Material("effects/shaders/lensflare")
local matDownsample = Material("pp/downsample")

require("shaderhotloader")

hook.Add("RenderScreenspaceEffects", "RenderLensFlare", function()
	render.UpdateScreenEffectTexture()
	
	local oldRT = render.GetRenderTarget()
	matDownsample:SetFloat("$darken", 0.4)
	
	render.SetRenderTarget(_rt_SmallFB0)
	
	render.SetMaterial(matDownsample)
	render.DrawScreenQuad()
	
	render.SetRenderTarget(oldRT)
	
	matLensflare:SetTexture("$fbtexture", _rt_FullFrameFB)
	matLensflare:SetTexture("$bloomtexture", _rt_SmallFB0)
	
	render.SetMaterial(matLensflare)
	render.DrawScreenQuad()
end)
