#include "material.h"
#include <fstream>
#include <iostream>
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

void RGBImage::readPPM(const string& filename)
{
	cout << "Reading PPM file: " << filename << endl;
	ifstream ifs(filename.c_str(), ios::binary);
	if (ifs.fail()) {
		cerr << "Error opening " << filename.c_str() << endl;
		return;
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
		return;
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
		return;
	}
	if (w<1) {
		cerr << "Unsupported width: " << w << endl;
		ifs.close();
		return;
	}
	if (h<1) {
		cerr << "Unsupported height: " << h << endl;
		ifs.close();
		return;
	}
	if (bits < 1 || bits > 255) {
		cerr << "Unsupported number of bits: " << bits << endl;
		ifs.close();
		return;
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
}
