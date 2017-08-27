#pragma once
#include <d3d11.h>
#include <wrl.h>
#include "ChiliException.h"
#include "Colors.h"
#include "Surface.h"
#include "Rect.h"
#include <functional>
#include <algorithm>

class Graphics
{
public:
	class Exception : public ChiliException
	{
	public:
		Exception( HRESULT hr,const std::wstring& note,const wchar_t* file,unsigned int line );
		std::wstring GetErrorName() const;
		std::wstring GetErrorDescription() const;
		virtual std::wstring GetFullMessage() const override;
		virtual std::wstring GetExceptionType() const override;
	private:
		HRESULT hr;
	};
private:
	// vertex format for the framebuffer fullscreen textured quad
	struct FSQVertex
	{
		float x,y,z;		// position
		float u,v;			// texcoords
	};
public:
	Graphics( class HWNDKey& key );
	Graphics( const Graphics& ) = delete;
	Graphics& operator=( const Graphics& ) = delete;
	void EndFrame();
	void BeginFrame();
	void PutPixel( int x,int y,int r,int g,int b )
	{
		PutPixel( x,y,{ unsigned char( r ),unsigned char( g ),unsigned char( b ) } );
	}
	void PutPixel( int x,int y,Color c );

	void DrawSprite(int x, int y, Rect subimage, Rect clip, Surface& img) {
		Rect destrect(V2i(x,y),subimage.size.c());

		int xskip = std::max(clip.left(), destrect.left()) - destrect.left();
		int yskip = std::max(clip.top(), destrect.top()) - destrect.top();
		V2i skip(xskip, yskip);

		int xstop = std::min(clip.right(), destrect.right()) - destrect.right();
		int ystop = std::min(clip.bottom(), destrect.bottom()) - destrect.bottom();
		V2i stop(xstop, ystop);

		V2i clippedSubimgpos = skip;
		V2i clippedSubimgsize = subimage.size.c().sub(skip).add(stop);
		Rect clippedSubimg(clippedSubimgpos, clippedSubimgsize);

		clippedSubimg.loop([&](V2i locimgpos) -> void {
			V2i abssrcimg = locimgpos.c().add(subimage.pos);
			V2i absdestimg = locimgpos.c().add(destrect.pos);
			PutPixel(absdestimg.x, absdestimg.y, img.getPixel(abssrcimg.x, abssrcimg.y));
		});
	}

	~Graphics();
private:
	Microsoft::WRL::ComPtr<IDXGISwapChain>				pSwapChain;
	Microsoft::WRL::ComPtr<ID3D11Device>				pDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>			pImmediateContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>		pRenderTargetView;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>				pSysBufferTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	pSysBufferTextureView;
	Microsoft::WRL::ComPtr<ID3D11PixelShader>			pPixelShader;
	Microsoft::WRL::ComPtr<ID3D11VertexShader>			pVertexShader;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				pVertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>			pInputLayout;
	Microsoft::WRL::ComPtr<ID3D11SamplerState>			pSamplerState;
	D3D11_MAPPED_SUBRESOURCE							mappedSysBufferTexture;
	Color*                                              pSysBuffer = nullptr;
public:
	static constexpr int ScreenWidth = 800;
	static constexpr int ScreenHeight = 600;
};