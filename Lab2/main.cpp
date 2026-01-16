/* ZJW simple C++ code to write out an image file (PNG)  */

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <string>
#include "Image.h"
#include "color.h"
#include "tri.h"

using namespace std;

/*write out image (PNG) data, using the triangles bounding box */
void draw(shared_ptr<Image> outImage, tri theTri) {

	//for every point in the bounding Box of the triangle
	for (int y= theTri.myBBox.minY; y <= theTri.myBBox.maxY; y++) {
		for (int x = theTri.myBBox.minX; x <= theTri.myBBox.maxX; x++) {
				float denom = float((theTri.v1[0] - theTri.v0[0])*(theTri.v2[1] - theTri.v0[1]) - 
					(theTri.v2[0] - theTri.v0[0])*(theTri.v1[1] - theTri.v0[1]));

				float beta = float((theTri.v0[0] - theTri.v2[0])*(y - theTri.v2[1]) - 
					(x - theTri.v2[0])*(theTri.v0[1] - theTri.v2[1])) / denom;
				float gamma = float((theTri.v1[0] - theTri.v0[0])*(y - theTri.v0[1]) - 
					(x - theTri.v0[0])*(theTri.v1[1] - theTri.v0[1])) / denom;
				float alpha = 1.0f - gamma - beta;

				int r = (theTri.c0.r() * alpha) + (theTri.c1.r() * beta) + (theTri.c2.r() * gamma);
				int g = (theTri.c0.g() * alpha) + (theTri.c1.g() * beta) + (theTri.c2.g() * gamma);
				int b = (theTri.c0.b() * alpha) + (theTri.c1.b() * beta) + (theTri.c2.b() * gamma);

				if (alpha >= 0 && beta >= 0 && gamma >= 0) {
						outImage->setPixel(x, outImage->getHeight() - 1 - y, r, g, b);
				}
		}
	}

	//the vertices with their colors
	outImage->setPixel(theTri.v0[0], outImage->getHeight()-1-theTri.v0[1], theTri.c0.r(), theTri.c0.g(), theTri.c0.b());
	outImage->setPixel(theTri.v1[0], outImage->getHeight()-1-theTri.v1[1], theTri.c1.r(), theTri.c1.g(), theTri.c1.b());
	outImage->setPixel(theTri.v2[0], outImage->getHeight()-1-theTri.v2[1], theTri.c2.r(), theTri.c2.g(), theTri.c2.b());
}

/*read command line arguments and write out new PNG file*/
int main(int argc, char *argv[]) {
	ofstream outFile;
	int sizeX, sizeY;
	//test tri One - note in window Coord
	tri triOne(10, 10, 5, 150, 150, 5, 200, 20, 5, color(0, 128, 128), color(128, 0, 128), color(0, 0, 200));
	triOne.computeBBox();

	//test tri two - note in window Coord
	tri triTwo(270, 390, 5, 395, 25, 5, 5, 120, 5, color(200, 128, 0), color(228, 228, 228), color(0, 128, 20));
	triTwo.computeBBox();

	if (argc < 4) {
		cerr << "Error format: a.out sizeX sizeY outfileName" << endl;
	} else {
		sizeX = stoi(argv[1]);
		sizeY = stoi(argv[2]);
		// Output filename
		string filename(argv[3]);
		// Create the image. We're using a `shared_ptr`, a C++11 feature.
		auto image = make_shared<Image>(sizeX, sizeY);

		//draw the scene and write the image to a file
		if (filename.length() > 0) {
			cout << "writing an image of size: " << sizeX << " " << sizeY << " to: " << argv[3] << endl;
			draw(image, triTwo);
			// Write image to file
			image->writeToFile(filename);
		} else {
			cout << "Error cannot open outfile" << endl;
			exit(0);
		}
	}
}