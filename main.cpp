#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize2.h"
using namespace std;
int main(){
	int x, y;
	string title;
	cout << "Give the file name: ";
	cin >> title;
	cout << endl;
	unsigned char* maze = stbi_load(title.c_str(), &x, &y, NULL, 1);
	int width;
	cout << "Give desired width: ";
	cin >> width;
	cout << endl;
	int height = (int)((float)y / x * width);
	vector<unsigned char> newImage(width * height);
	stbir_pixel_layout dp = static_cast<stbir_pixel_layout>(1);
	stbir_resize_uint8_linear(
		maze, x, y, 0,
		newImage.data(), width, height, 0, dp 
	);
	vector<vector<string>> arr1(height, vector<string>(width));
	int div;
	do {
		div = 0;
		cout << "set threshold (0-10): ";
		cin >> div;
		cout << endl;
		if (div > 10 || div < 0) {
			cout << "ERROR: Type in a value from 0 to 10." << endl;
		}
	} while (div > 10 || div < 0);

	div += 30;
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			stbi_uc pixel = newImage[width * i + j];
			switch ((pixel/div)+1) {
			case 1:
				arr1[i][j] = "  ";
				break;
			case 2:
				arr1[i][j] = "--";
				break;
			case 3:
				arr1[i][j] = "==";
				break;
			case 4:
				arr1[i][j] = "++";
				break;
			case 5:
				arr1[i][j] = "**";
				break;
			case 6:
				arr1[i][j] = "%%";
				break;
			case 7:
				arr1[i][j] = "##";
				break;
			case 8:
				arr1[i][j] = "@@";
				break;
			}
		}
	}
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			cout << arr1[i][j];
		}
		cout <<endl;
	}
	ofstream file("result.txt", ofstream::out | ofstream::trunc);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			file << arr1[i][j];
		}
		file << "\n";
	}
	file.close();
	system("pause");
	return 0;
}