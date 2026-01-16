/* ZJW simple C++ code to write out an image file (PNG) representing an ellipse(s) */

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <string>
#include "Image.h"
#include "color.h"
#include "ellipse.h"
#include "rect.h"

using namespace std;


/*write out image (PNG) data, using the defined implicit equation 
  interior points write a different color then exterior points */
void draw(string out, shared_ptr<Image> outImage, vector<shared_ptr<shapes>> IEs) {

	float res;
	color inC;
	color background(12, 34, 56);
	bool inTrue = false;

	//for every point in the 2D space
	for (int y=0; y < outImage->getHeight(); y++) {
		for (int x =0; x < outImage->getWidth(); x++) {

			inTrue = false;
			//iterate through all possible equations (note 'front' determined by order in vector)

			int highestZIndex = -9999;

			for (auto eq : IEs) {
				res = eq->eval(x, y);
				if (res < 0 && eq->getZIndex() >= highestZIndex) {
					highestZIndex = eq->getZIndex();
					inC = eq->getInC();
					inTrue = true;
				}
			}
			if (inTrue) {			
				outImage->setPixel(x, outImage->getHeight()-1-y, inC.r(), inC.g(), inC.b());
			}
			else
				outImage->setPixel(x, outImage->getHeight()-1-y, background.r(), background.g(), background.b());
		}
	}
}


/*read command line arguments and write out new PNG file of given size with some ellipses*/
int main(int argc, char *argv[]) {

	ofstream outFile;
	int sizeX, sizeY;

	// create all the equations for a simple face
	vector<shared_ptr<shapes>> theEquations;
	if (argc < 4) {
		cerr << "Error format: a.out sizeX sizeY outfileName" << endl;
	} else {
		sizeX = stoi(argv[1]);
		sizeY = stoi(argv[2]);
		// Output filename
		string filename(argv[3]);
		// Create the image. We're using a `shared_ptr`, a C++11 feature.
		auto image = make_shared<Image>(sizeX, sizeY);

		//create our scene (representation of ellipses)
		// note order in vector matters
		theEquations.push_back(make_shared<rect>(vec2(25, 475), vec2(475, 25), color(34, 98, 112), 0));
		theEquations.push_back(make_shared<rect>(vec2(100, 80), vec2(150, 70), color(134, 128, 11), 1));
		theEquations.push_back(make_shared<rect>(vec2(350, 80), vec2(400, 70), color(134, 128, 11), 1));
		theEquations.push_back(make_shared<ellipse>(0.5*sizeX, 0.5*sizeY, 20, 15, color(134, 128, 11), 4));
		theEquations.push_back(make_shared<ellipse>(0.25*sizeX, 0.25*sizeY, 20, 33, color(34, 198, 112), 2));
		theEquations.push_back(make_shared<ellipse>(0.75*sizeX, 0.25*sizeY, 20, 33, color(34, 198, 112), 3));
		theEquations.push_back(make_shared<ellipse>(0.5*sizeX, 0.75*sizeY, 20, 20, color(100,100,100), 4));
		theEquations.push_back(make_shared<ellipse>(0.5*sizeX, 0.75*sizeY, 50, 10, color(134, 128, 11), 5));

		//draw the scene and write the image to a file
		if (filename.length() > 0) {
			cout << "writing an image of size: " << sizeX << " " << sizeY << " to: " << argv[3] << endl;
			draw(filename, image, theEquations);
			// Write image to file
			image->writeToFile(filename);
		} else {
			cout << "Error cannot open outfile" << endl;
			exit(0);
		}
	}

}
