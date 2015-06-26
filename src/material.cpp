#include "material.h"
#include <fstream>
#include <iostream>
//#include <IL/il.h>
#include <stdlib.h>
using namespace std;

void RGBImage::writePPM(const string& filename) const {
	char* buffer = new char[w*h*3];
	for(int i = 0; i < w*h; ++i) {
		buffer[3*i  ] = (char)(data[i].r/float(bits)*255.f);
		buffer[3*i+1] = (char)(data[i].g/float(bits)*255.f);
		buffer[3*i+2] = (char)(data[i].b/float(bits)*255.f);
	}

	ofstream ofs(filename.c_str(), ios::binary);
	ofs << "P6" << endl
		<< w << " " << h << endl
		<< "255" << endl;
	ofs.write(buffer, w*h*3);
	ofs.close();

	delete [] buffer;
}

void eat_comment(ifstream& f)
{
	char linebuf[256];
	char ppp;
	while (ppp = f.peek(), ppp == '\n' || ppp == '\r') {
		f.get();
	}
	if (ppp == '#')
		f.getline(linebuf,255);
}

bool RGBImage::readPPM(const string& filename)
{
	cout << "Reading PPM file: " << filename << endl;
	ifstream ifs(filename.c_str(), ios::binary);
	if (ifs.fail()) {
		cerr << "Error opening " << filename.c_str() << endl;
		return false;
	}

	//get file type
	eat_comment(ifs);
	int mode = 0;
	string s;
	ifs >> s;
	if (s == "P3") {
		mode = 3; //ASCII mode
	} else if (s == "P6") {
		mode = 6; //binary mode
	} else {
		cout << "Unsupported file format" << endl;
		return false;
	}

	//get width
	eat_comment(ifs);
	ifs >> w;

	//get height
	eat_comment(ifs);
	ifs >> h;

	//get bits
	eat_comment(ifs);
	ifs >> bits;

	//error checking
	if (mode != 3 && mode != 6) {
		cerr << "Unsupported magic number" << endl;
		ifs.close();
		return false;
	}
	if (w<1) {
		cerr << "Unsupported width: " << w << endl;
		ifs.close();
		return false;
	}
	if (h<1) {
		cerr << "Unsupported height: " << h << endl;
		ifs.close();
		return false;
	}
	if (bits < 1 || bits > 255) {
		cerr << "Unsupported number of bits: " << bits << endl;
		ifs.close();
		return false;
	}
	//cout << "w = " << w << ", h = " << h << ", bits = " << bits << endl;
	//load image data
	data = new RGB[w*h];
	if (mode == 6) {
		ifs.get();
		ifs.read((char*)&data[0],w*h*3);
	} else if (mode == 3) {
		for (int i = 0; i < w*h; i++) {
			int v;
			ifs >> v;
			data[i].r = v;
			ifs >> v;
			data[i].g = v;
			ifs >> v;
			data[i].b = v;
		}
	}
	ifs.close();
	return true;
}

/*
void RGBImage::readDevIL(const string& filename, bool alpha)
{
    ILuint image;
    ILenum format;
    int dim;
    //RGB* data;

    ilInit();
    ilEnable(IL_ORIGIN_SET);
    ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
    //DBG_(__glmWarning("loading DevIL texture %s",filename));
    ilGenImages(1,&image);

    ilBindImage(image);
    if (!ilLoadImage((wchar_t*)filename.c_str())) {
		//DBG_(__glmWarning("glmLoadTexture(): DevIL ilLoadImage(%s): error %s\n", filename, ilGetError()));
		//cerr << "glmLoadTexture(): DevIL ilLoadImage(" << filename << "): error " << ilGetError() << "\n";
		ilDeleteImages(1, &image);
		data = nullptr;
		return;// NULL;
    }
    h = ilGetInteger(IL_IMAGE_HEIGHT);
    w = ilGetInteger(IL_IMAGE_WIDTH);
    type = alpha ? 1 : 0;
    format = alpha ? IL_RGBA : IL_RGB;
    dim = w * h * ((alpha) ? 4 : 3);
    data = (RGB*)malloc(sizeof(RGB) * dim);
    ilCopyPixels( 0, 0, 0, w, h, 1, format, IL_UNSIGNED_BYTE, data);
    ilDeleteImages(1, &image);
    if (ilGetError() == IL_NO_ERROR) {
		//DBG_(__glmWarning("loaded DevIL texture %s",filename));
    	return; //data;
    }
    //DBG_(__glmWarning("glmLoadTexture(): DevIL ilCopyPixels(): error %s\n", ilGetError()));
    free(data);
	data = nullptr;
    return;// NULL;
}*/

void makeMipMaps(vector<RGBImage*>& texMap) 
{ 
    RGBImage* parentMap = texMap.back();
    if (parentMap->w < 2) return; 
    if (parentMap->h < 2) return; 

    RGBImage* MipMap = new RGBImage;
    MipMap->w = parentMap->w / 2; 
    MipMap->h = parentMap->h / 2; 
    MipMap->bits = parentMap->bits;
    MipMap->data = new RGB[MipMap->w*MipMap->h];

    int u,v;

    /* find the new texture values */ 
    for (u = 0; u < MipMap->w; u++) {
		for (v = 0; v < MipMap->h; v++) {
			if (0>(parentMap->w*v*2 + u*2) || (parentMap->w*v*2 + u*2)>(parentMap->w*parentMap->h)) 
				cout << "Mipmap num " << texMap.size() << ", u*2=" << u*2 << " v*2=" << v*2 << " exceeding w=" << parentMap->w << " h=" << parentMap->h << endl;
			if (0>(parentMap->w*v*2 + u*2 + 1) || (parentMap->w*v*2 + u*2 + 1)>(parentMap->w*parentMap->h))
				cout << "Mipmap num " << texMap.size() << ", u*2=" << u*2 << " v*2+1=" << v*2 + 1  << " exceeding w=" << parentMap->w << " h=" << parentMap->h << endl;
			if (0>(parentMap->w*(v*2+1) + u*2) || (parentMap->w*(v*2+1) + u*2)>(parentMap->w*parentMap->h)) 
				cout << "Mipmap num " << texMap.size() << ", u*2+1=" << u*2+1 << " v*2=" << v*2  << " exceeding w=" << parentMap->w << " h=" << parentMap->h << endl;
			if (0>(parentMap->w*(v*2+1) + u*2 + 1) || (parentMap->w*(v*2+1) + u*2 + 1)>(parentMap->w*parentMap->h)) 
				cout << "Mipmap num " << texMap.size() << ", u*2+1=" << u*2+1 << " v*2+1=" << v*2 + 1  << " exceeding w=" << parentMap->w << " h=" << parentMap->h << endl;
			MipMap->data[MipMap->w*v+u].r = (parentMap->data[parentMap->w*v*2 + u*2].r
										    + parentMap->data[parentMap->w*v*2 + u*2 + 1].r
											+  parentMap->data[parentMap->w*(v*2+1) + u*2].r
											+  parentMap->data[parentMap->w*(v*2+1) + u*2 + 1].r)
											/  4;
			MipMap->data[MipMap->w*v+u].g = (parentMap->data[parentMap->w*v*2 + u*2].g
										    + parentMap->data[parentMap->w*v*2 + u*2 + 1].g
											+  parentMap->data[parentMap->w*(v*2+1) + u*2].g
											+  parentMap->data[parentMap->w*(v*2+1) + u*2 + 1].g)
											/  4;
			MipMap->data[MipMap->w*v+u].b = (parentMap->data[parentMap->w*v*2 + u*2].b
										    + parentMap->data[parentMap->w*v*2 + u*2 + 1].b
											+  parentMap->data[parentMap->w*(v*2+1) + u*2].b
											+  parentMap->data[parentMap->w*(v*2+1) + u*2 + 1].b)
											/  4;
		}
    }

    /* make a link to the mip map */ 
    texMap.push_back(MipMap);

    /* recurse until we are done */ 
    makeMipMaps( texMap ); 
}

/*
void deleteMipMaps(vector<RGBImage*>& texMap) {
	for (size_t i=texMap.size()-1; i<=1; i++) {
		delete texMap[i];
	}
	texMap.resize(1);
}*/