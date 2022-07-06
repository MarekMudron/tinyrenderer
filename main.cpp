#include "tgaimage.h"
#include "model.h"

using namespace std;

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);



void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
	bool steep = false;
	if(abs(x0-x1) < abs(y0-y1)) { // ak je ciara strma tak vymenime x a y suradnice
		swap(x0, y0);
		swap(x1, y1);
		steep = true;
	}
	if(x0 > x1) { // ak su body zadane opacne tak ich vymenime
		swap(x0, x1);
		swap(y0, y1);
	}
	int dx = x1-x0;
	int dy = y1-y0;
	int derror = std::abs(dy)*2;
	int error = 0;
	int y = y0;
	for(int x=x0; x<=x1; x++) {
		if (steep) { 
            image.set(y, x, color); // if transposed, de−transpose 
        } else { 
            image.set(x, y, color); 
        } 
		error += derror;
		if (error > .5) {
			y += (y1 > y0 ? 1 : -1);
			error -= dx*2;
		}
	}
}

int main(int argc, char** argv) {
	Model* model;
	if(argc == 2) {
		model = new Model(argv[1]);
	}else{
		model = new Model("obj/african_head.obj");
	}
	const int width  = 800;
	const int height = 800;
	TGAImage image(width, height, TGAImage::RGB);

	for(int i = 0; i < model->nfaces(); i++) {
		vector<int> face = model->face(i);
		for(int j = 0; j < 3; j++) {
			Vec3f v0 = model->vert(face[j]);
			Vec3f v1 = model->vert(face[(j+1)%3]);
			int x0 = (v0.x + 1.)*width/2.;
			int y0 = (v0.y + 1.)*height/2.;
			int x1 = (v1.x + 1.)*width/2.;
			int y1 = (v1.y + 1.)*height/2.;
			//cout<<v0.x<<"("<<x0<<") "<<v0.y<<"("<<y0<<") "<<v1.x<<"("<<x1<<") "<<v1.y<<"("<<y1<<") "<<endl;
			line(x0, y0, x1, y1, image, white);
		}
	}
	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");
	delete model;
	return 0;
}

