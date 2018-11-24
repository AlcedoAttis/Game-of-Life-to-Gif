/*
This program takes 2 arguments, the size and the timesteps of the world
and generates a big 3d vector, which it will print out and store as the global variable 
v3 world.
*/	
#include <iostream>
#include <vector>
#include <ctime>
#include <png++/png.hpp>
#include <bits/stdc++.h>

typedef std::vector<std::vector<std::vector<bool>>> v3;
typedef std::vector<std::vector<bool>> v2;
typedef std::vector<bool> v1;

v2 create_first(int, int);
v2 next_gen(v2&, char);
int log10ceil(int);
int neighbour_sum(v2&, int, int, char);
bool random_bool();
bool get_element(v2&, int, int, char);
void write_img(int, int, v3&);
void print(v3&);

int main(int, char *argv[]){
	int size = (std::atoi(argv[1]));
	int time = (std::atoi(argv[2]));
	char type = 't'; // t[orus], 0, 1
	std::srand((int) std::time(0));

	// global output variable
	v3 world;	

	world.resize(time);
	for(int t=0; t<time; t++){
		world[t].resize(size);
		for(int x=0; x<size; x++){
			world[t][x].resize(size);
		}
	}
	world[0] = create_first(size, size);
	for(int t=1; t<time; t++){
		world[t] = next_gen(world[t-1], type);
	}

	//print(world);
	write_img(size, time, world);
	return 0;
}

v2 create_first(int layer_x, int layer_y){
	v2 layer1;
	for(int x=0; x<layer_x; x++){
		layer1.push_back(v1());
		for(int y=0; y<layer_y; y++){
			layer1[x].push_back(random_bool());
		}
	}
	return layer1;
}

v2 next_gen(v2 &last, char type){
	v2 next;
	for(unsigned int x=0; x<last.size(); x++){
		next.push_back(v1());
		for(unsigned int y=0; y<last[x].size(); y++){
			int neighbours = neighbour_sum(last, x, y, type);
			bool self = last[x][y];
			bool out;
			if(self){
				out = (neighbours > 1 && neighbours <= 3);
			}
			else{
				out = (neighbours == 3);
			}
			next[x].push_back(out);
		}
	}
	return next;
}

int neighbour_sum(v2 &layer, int x, int y, char type){
	int neighbours = 0;
	for(int dx=-1; dx<=1; dx++){
		for(int dy=-1; dy<=1; dy++){
			if(get_element(layer, x+dx, y+dy, type) && (dx != 0 || dy != 0))
				++neighbours;
		}
	}
	return neighbours;
}

bool get_element(v2 &layer, int x, int y, char type){
	if(x >= 0 && x < (int) (layer.size()) && y >= 0 && y < (int) (layer[x].size()))
		return layer[x][y];
	else{
		unsigned int s = layer.size();
		if(type == 't'){
			return layer[(x+s)%s][(y+s)%s];
		}
		else return (bool) (type - '0');
	}
	return true;
}

bool random_bool() {
	return std::rand() % 2;
}

void write_img(int size, int time, v3 &world){
	std::vector<png::image< png::rgb_pixel > > image_vect;
	for(int t = 0; t < time; t++){
		png::image< png::rgb_pixel > image(size, size);
		for (size_t y = 0; y < image.get_height(); ++y){
			for (size_t x = 0; x < image.get_width(); ++x){
				int value = 255;
				if(world[t][x][y]) value = 0;
				image[y][x] = png::rgb_pixel(value, value, value);
			}
		}
		image_vect.push_back(image);
	}
	
	for(int t = 0; t < time; t++){
		std::stringstream zero_pad;
		std::string name;
	 	zero_pad << std::setw(log10ceil(time)) << std::setfill('0') << std::to_string(t);
	 	zero_pad >> name;
		image_vect[t].write("pics/test_png_"+name+".png");
	}
}

void print(v3 &in){
	for(unsigned int i=0; i<in.size(); i++){
		for(unsigned int j=0; j<in[0].size(); j++){
			for (unsigned int k = 0; k < in[0][0].size(); k++){
				std::cout << in[i][j][k];	
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;		
	}
}

int log10ceil(int x) { return (int) ((std::log(x)/std::log(10))+1); }