#pragma once
#ifndef __MODEL_H__
#define __MODEL_H__

#include <vector>
#include "Vector2D.h"
#include "tgaimage.h"

class Model {
public:
	Model(const char* filename);
	~Model();
	TGAColor diffuse(Vector2D uv);
	std::vector<int> face(int idx);
	TGAImage diffusemap_;
	void load_texture(std::string filename, const char* suffix, TGAImage& img);
};

#endif //__MODEL_H__