#include "camera.hpp"

#include <iostream>

using namespace std;


glm::mat4x4 Camera::translate(float x, float y, float z)
{
	return (glm::mat4x4) glm::translate(glm::vec3(x, y, z));
}

glm::mat4x4 Camera::rotate(float angle, float x, float y, float z)
{
	return translate(this->x, this->y, this->z) * (glm::mat4x4) glm::rotate(angle, glm::vec3(x, y, z)) * translate(-this->x, -this->y, -this->z);
}



glm::mat4x4 Camera::moveRight() {
	/* Calculate movement in z- and x-directions */
	float x_move = move_step * cos(rotate_count * rotate_angle);
	float z_move = move_step * sin(rotate_count * rotate_angle);
	z += z_move;
	x += x_move;

	return translate(-x_move, 0.0, -z_move);
}

glm::mat4x4 Camera::moveLeft() {
	/* Calculate movement in z- and x-directions */
	float x_move = move_step * cos(rotate_count * rotate_angle);
	float z_move = move_step * sin(rotate_count * rotate_angle);
	z -= z_move;
	x -= x_move;

	return translate(x_move, 0.0, z_move);
}

glm::mat4x4 Camera::moveForward() {
	/* Calculate movement in z- and x-directions */
	float z_move = move_step * cos(rotate_count * rotate_angle);
	float x_move = move_step * sin(rotate_count * rotate_angle);
	z -= z_move;
	x += x_move;

	return translate(-x_move, 0.0, z_move);
}

glm::mat4x4 Camera::moveBackward() {
	/* Calculate movement in z- and x-directions */
	float z_move = move_step * cos(rotate_count * rotate_angle);
	float x_move = move_step * sin(rotate_count * rotate_angle);
	z += z_move;
	x -= x_move;

	return translate(x_move, 0.0, -z_move);
}

glm::mat4x4 Camera::moveUp() {
	y += move_step;
	return translate(0.0, -move_step, 0.0);
}

glm::mat4x4 Camera::moveDown() {
	y -= move_step;
	return translate(0.0, move_step, 0.0);
}



glm::mat4x4 Camera::lookUp() {
	/*	1. Rotate about y-axis so camera points toward inital value, angular with x-axis
		2. Rotate about x-axis
		3. Rotate about y-axis, back again	*/


	return rotate(rotate_count * -rotate_angle, 0.0, 1.0, 0.0)
		* rotate(-rotate_angle, 1.0, 0.0, 0.0)
		* rotate(rotate_count * rotate_angle, 0.0, 1.0, 0.0);
}

glm::mat4x4 Camera::lookDown() {
	return rotate(rotate_count * -rotate_angle, 0.0, 1.0, 0.0)
		* rotate(rotate_angle, 1.0, 0.0, 0.0)
		* rotate(rotate_count * rotate_angle, 0.0, 1.0, 0.0);
}

glm::mat4x4 Camera::lookLeft() {
	rotate_count--;
	return rotate(-rotate_angle, 0.0, 1.0, 0.0);
}

glm::mat4x4 Camera::lookRight() {
	rotate_count++;
	return rotate(rotate_angle, 0.0, 1.0, 0.0);
} 