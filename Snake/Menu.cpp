#include "Menu.h"

#include <string>
#include <glut.h>

Menu *Menu::static_this;

void Menu::initialize_gl(){
	glEnable(GL_TEXTURE_2D);
	glClearColor(0.627, 0.878, 0.501,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, this->width, 0, this->height, -100, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Menu::draw_callback(){
	static_this->draw();
}

void Menu::reshape_callback(int width, int height){
	static_this->reshape(width, height);
}

void Menu::timer_callback(int = 0){
	static_this-> timer(0);
}

void Menu::draw()const{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0, 0, 0);

	int y_position = 20;
	for (std::vector<std::string>::const_iterator itr = std::begin(this->arr);
		itr != std::end(this->arr); itr++, y_position += 30)
		this->draw_string(*itr, 20, y_position);

	glutSwapBuffers();
}

void Menu::reshape(int width, int height){
	this->width = width;
	this->height = height;

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, this->width, 0, this->height, -100, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void  Menu::timer(int = 0){
	this->draw();
	glutTimerFunc(30, &Menu::timer_callback, 0);
}

void Menu::move_down(){
	this->cur_position = (this->cur_position + 1) % this->arr.size();
}

void Menu::move_up(){
	this->cur_position = this->cur_position == 0 ? this->arr.size() - 1 : 
		this->cur_position - 1;
}

size_t Menu::get_cur_position()const{
	return cur_position + 1;
}

void Menu::draw_string(std::string str, int x_coordinate, int y_coordinate)const{
	const char *text = str.c_str();
	glRasterPos2d(x_coordinate,y_coordinate);

	while (*text) 
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *text++);
}

void Menu::set_static_this(Menu *staticThis){
	this->static_this = staticThis;
}