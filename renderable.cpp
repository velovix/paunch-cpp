#include "lodepng.h"
#include "paunch.h"
#include "draw.h"

namespace paunch {

Renderable::Renderable() {}

Renderable::Renderable(int mode, std::vector<double> verticies) {

	std::vector<float> verts32;
	for(auto &val: verticies) {
		verts32.push_back((float)val);
	}

	this->mode = mode;
	this->verticies = verts32;

	glGenBuffers(1, &this->vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, verts32.size()*sizeof(float), verts32.data(), GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	Error error = _checkForErrors();
	if(error.Report().length() > 0) {
		throw error;
	}
}

Renderable::Renderable(double x, double y, double width, double height, std::string filename, int clip) {

	std::vector<double> vertCoords = {x, y, x+width, y, x, y+height, x+width, y+height, x+width, y, x, y+height};
	*this = Renderable(Triangles, vertCoords);

	std::vector<double> texCoords = {0,0,1,0,0,1,1,1,1,0,0,1};
	this->Texture(texCoords, filename, clip);

	Error error = _checkForErrors();
	if(error.Report().length() > 0) {
		throw error;
	}
}

void Renderable::Texture(std::vector<double> coords, std::string filename, int clip) {

	FILE * file;
	file = fopen(filename.data(), "r");
	if(file == NULL) {
		fclose(file);
		throw Error("Could not read image file");
	}
	fclose(file);

	std::vector<float> coords32;
	for(auto &val: coords) {
		coords32.push_back((float)val);
	}

	glGenBuffers(1, &this->texcoordBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->texcoordBuffer);
	glBufferData(GL_ARRAY_BUFFER, coords.size()*4, &coords32[0], GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	std::vector<unsigned char> data;
	unsigned int width, height;

	unsigned int error = lodepng::decode(data, width, height, filename);
	if(error) {
		throw Error(lodepng_error_text(error));
	}

	std::vector<unsigned char> flippedData;
	for(unsigned int y=0; y<height; y++) {
		for(unsigned int x=0; x<width; x++) {
			for(unsigned int color=0; color<4; color++) {
				flippedData.push_back(data.at((((width*(height-y-1))+x)*4)+color));
			}
		}
	}

	int clipWidth = width;
	int clipHeight = height / clip;

	this->textures.resize(clip);
	glGenTextures(clip, &this->textures[0]);
	for(int i=0; i<clip; i++) {
		glBindTexture(GL_TEXTURE_2D, this->textures.at(i));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, clipWidth, clipHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, &flippedData.at((clip-i-1)*(clipWidth*clipHeight*4)));
	}

	glBindTexture(GL_TEXTURE_2D, 0);

	Error glError = _checkForErrors();
	if(glError.Report().length() > 0) {
		throw glError;
	}
}

void Renderable::Draw(int frame) {

	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	if(this->texcoordBuffer != 0) {
		glActiveTexture(GL_TEXTURE0);

		glBindBuffer(GL_ARRAY_BUFFER, this->texcoordBuffer);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindTexture(GL_TEXTURE_2D, this->textures.at(frame));
		glEnableVertexAttribArray(1);
	}

	glEnableVertexAttribArray(0);
	glDrawArrays(this->mode, 0, this->verticies.size());
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glBindTexture(GL_TEXTURE_2D, 0);

	Error error = _checkForErrors();
	if(error.Report().length() > 0) {
		throw error;
	}
}

void Renderable::Move(double x, double y) {

	for(unsigned int i=0; i<this->verticies.size(); i+=2) {
		this->verticies[i] += (float)x;
		this->verticies[i+1] += (float)y;
	}

	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
	glBufferSubData(GL_ARRAY_BUFFER, 0, this->verticies.size()*4, &this->verticies[0]);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Renderable::SetPosition(double x, double y) {

	double xDisp = x - (double)this->verticies[0];
	double yDisp = y - (double)this->verticies[1];

	this->Move(xDisp, yDisp);
}

Double2 Renderable::GetPosition() {

	return Double2((double)this->verticies[0], (double)this->verticies[1]);
}

}
