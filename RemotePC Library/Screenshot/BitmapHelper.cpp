#include "BitmapHelper.h"

CBitmapHelper::CBitmapHelper()
{
	SetValues(0, 0, 0, 4);
}

void CBitmapHelper::SetValues(int Width, int Height, int BitsPerPixels, int Align)
{
	w = Width;
	h = Height;
	bpp = BitsPerPixels;
	Alignment = Align;
}

//////////////////////////////////////////////////////////////////////////
// Calculate how many padding bytes are required
//////////////////////////////////////////////////////////////////////////
int CBitmapHelper::CalcPaddingSize(int RowSize)
{
	if(Alignment == 0)
		return 0;

	int Padding = Alignment - (RowSize % Alignment);
	if(Padding == Alignment)
		Padding = 0;

	return Padding;
}

//////////////////////////////////////////////////////////////////////////
// Calculate how many bytes are required for a row of pixels (unaligned)
//////////////////////////////////////////////////////////////////////////
int CBitmapHelper::CalcRowSize()
{
	int nbits = w * bpp;
	
	int size = nbits / 8;
	if(nbits % 8 > 0)
		size++;

	return size;
}

//////////////////////////////////////////////////////////////////////////
// Calculate how many bytes are required for a row of pixels (aligned)
//////////////////////////////////////////////////////////////////////////
int CBitmapHelper::CalcPitchSize()
{
	int RowSize = CalcRowSize();
	return RowSize + CalcPaddingSize(RowSize);
}

//////////////////////////////////////////////////////////////////////////
// Calculate how many bytes are required to hold the entire image
//////////////////////////////////////////////////////////////////////////
int CBitmapHelper::CalcBufferSize()
{
	if(Alignment > 0){
		return CalcPitchSize() * h;
	} else {
		int nbits = w * h * bpp;

		int size = nbits / 8;
		if(nbits % 8 > 0)
			size++;

		return size;
	}
}

//----------------------------------------------------------------------//
//----------------------------------------------------------------------//
//----------------------------------------------------------------------//

int CBitmapHelper::CalcPaddingSize(int Width, int Height, int BitsPerPixels, int Align)
{
	SetValues(Width, Height, BitsPerPixels, Align);
	return CalcPaddingSize(CalcRowSize());
}

int CBitmapHelper::CalcRowSize(int Width, int Height, int BitsPerPixels, int Align)
{
	SetValues(Width, Height, BitsPerPixels, Align);
	return CalcRowSize();
}

int CBitmapHelper::CalcPitchSize(int Width, int Height, int BitsPerPixels, int Align)
{
	SetValues(Width, Height, BitsPerPixels, Align);
	return CalcPitchSize();
}

int CBitmapHelper::CalcBufferSize(int Width, int Height, int BitsPerPixels, int Align)
{
	SetValues(Width, Height, BitsPerPixels, Align);
	return CalcBufferSize();
}

