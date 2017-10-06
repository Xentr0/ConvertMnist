// ConvertMnist.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <cassert>
#include <fstream>

using namespace std;

int main()
{
	unsigned char byte;
	vector<unsigned> labels;
	FILE *labelfile = fopen("C:/Users/Ruben/Desktop/NeuralNet/t10k-labels.idx1-ubyte", "rb");
	fseek(labelfile, 8, SEEK_SET);
	while (fread(&byte, 1, 1, labelfile) != 0)
	{
		labels.push_back(byte);
	}
	cout << labels.size() << " labels read." << endl;

	fclose(labelfile);

	vector<float> pixeldata;
	FILE *fp = fopen("C:/Users/Ruben/Desktop/NeuralNet/t10k-images.idx3-ubyte", "rb");
	fseek(fp, 16, SEEK_SET);
	while (fread(&byte, 1, 1, fp) != 0)
	{	 
		pixeldata.push_back(byte);
		//cout << "Reading bytes, step: " << pixeldata.size() << endl;
	}

	fclose(fp);

	int imagesize = 28 * 28;

	assert(pixeldata.size() / imagesize == labels.size());

	ofstream outfile("C:/Users/Ruben/Desktop/NeuralNet/testMNIST.txt");
	//outfile << "topology: " << imagesize << " 100 10" << endl;
	
	
	for (unsigned int i = 0; i < labels.size(); i++)
	{
		outfile << "in: ";
		for (unsigned int j = 0; j < imagesize; j++)
		{
			unsigned int index = i*imagesize + j;
			outfile << pixeldata[index] / 255.0 << " ";			
		}
		outfile << endl;
		outfile << "out: ";
		for (unsigned int u = 0; u < labels[i]; u++)
		{
			outfile << "0 ";
		}
		outfile << "1 ";
		for (unsigned int u = 0; u < 9 - labels[i]; u++)
		{
			outfile << "0 ";
		}
		outfile << endl;
		//cout << "Progress: " << i + 1 << " / " << labels.size() << endl;
	}

	cout << "File written." << endl;

	return 0;
}
