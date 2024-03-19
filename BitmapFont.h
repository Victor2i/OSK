#pragma once

struct FNT1_HEADER{
	unsigned char Magic[2];
	unsigned char CharSize;
	unsigned char Pages;
};

struct FNT1_FONT{
	FNT1_HEADER* FNT1Header;
	void* GlyphBuffer;
};