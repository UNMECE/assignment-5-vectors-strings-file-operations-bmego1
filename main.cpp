#include "pixel.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>




void read_pixel(std::vector <Pixel> &pixel_list, const std::string &filename) {
	std::if(!file) {
		std::cerr<<"Can not open file: " << filename << std::endl;
		return;
	}

	std::string line;
		while(std::getline(file, line)) {
			std::stringstream ss(line);
			std::string token;
			Pixel p;

					//r,g,b,x,y
			std::getline(ss, token, ','); p.r=std::stoi(token);
			std::getline(ss, token, ','); p.g=std::stoi(token);
			std::getline(ss, token, ','); p.b=std::stoi(token);
			std::getline(ss, token, ','); p.x=std::stoi(token);
			std::getline(ss, token, ','); p.y=std::stoi(token);

			pixel_list.pushback(p);

		}
	file.close();
}


void average_colors(std::vector<Pixel> &pixel_list) {
	
	for(const auto &p : pixel_list) {
		sum_r += p.r;
		sum_g += p.g;
		sum_b += p.b;
	}
	
	double sum_r=0, sum_g=0, sum_b=0;
	int count=pixel_list.size();
		
	std::cout<<"The Average of R: "<<sum_r/count<<"\n";
	std::cout<<"The Average of G: "<<sum_g/count<<"\n";
	std::cout<<"The Average of B: "<<sum_b/count<<"\n";
}




void flip_vertically(std::vector<Pixel> &pixel_list) {
	int max_y=256;

	for(auto &p : pixel_list) {
		p.y=max_y - 1 - p.y;
	}
}



void save_pixels(const std::vector<Pixel> &pixel_list, const std::string &filename) {
	
	for(const auto &p : pixel_list) {
		file <<p.r<<"," <<p.g<<"," << p.b<<"," <<p.x<<"," <<p.y<<","<<"\n";
	}
	
	std::ofstream file(filename);
	
	if(!file) {
		std::cerr<<"Can not open file: "<<filename<<std::endl;
		return;
	}
	
	file.close();
	std::cout<<"The file is saved! "<<filename<< std::endl;
	
}


int main(int limp, char *comm[]) {
	if(limp<2) {
		std::cerr<<"The usage: "<<comm[0]<<"<filename>\n";
		return 1;
	}

	std::vector<Pixel> pixel_list;
	read_pixel(pixel_list, comm[1]);

	std::cout<<"List has been loaded "<< pixel_list.size() << "pixels.\n";




	average_colors(pixel_list);

	flip_vertically(pixel_list);

	save_pixels(pixel_list, "flipped.dat");

	return 0;
}


