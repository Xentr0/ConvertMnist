#include <stdio.h>
#include <iostream>
#include <vector>
#include <cassert>
#include <fstream>

using namespace std;

int main()
{
	unsigned char byte;
	vector<unsigned> labels;
	FILE *labelfile = fopen("Data/t10k-labels-idx1-ubyte.gz", "rb");
	fseek(labelfile, 8, SEEK_SET);
	while (fread(&byte, 1, 1, labelfile) != 0)
	{
		labels.push_back(byte);
	}
	cout << labels.size() << " labels read." << endl;

	fclose(labelfile);

	vector<float> pixeldata;
	FILE *fp = fopen("Data/t10k-images-idx3-ubyte.gz", "rb");
	fseek(fp, 16, SEEK_SET);
	while (fread(&byte, 1, 1, fp) != 0)
	{	 
		pixeldata.push_back(byte);
	}
	
	cout << pixeldata.size() << " pixels read." << endl;
	cout << 10000 * 28 * 28 << " pixels expected." << endl;

	fclose(fp);

	int imagesize = 28 * 28;

	assert(pixeldata.size() / imagesize == labels.size());

	ofstream outfile("Data/trainMNIST.txt");
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
