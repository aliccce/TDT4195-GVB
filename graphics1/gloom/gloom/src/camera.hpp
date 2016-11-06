

class Camera
{
	// Camera location
	float x = 0.0;
	float y = 0.0;
	float z = 1.0;

	float lookat_x = 0.0;
	float lookat_y = 0.0;
	float lookat_z = 0.0;

	int rotate_count = 0; // 0 is right forward. Positive values to the right, negative to the left.

	float move_step;
	float rotate_angle;

	glm::mat4x4 translate(float x, float y, float z);
	glm::mat4x4 rotate(float angle, float x, float y, float z);


public:

	Camera(float move_step, float rotate_angle) : move_step(move_step), rotate_angle(rotate_angle) { };

	glm::mat4x4 moveRight();
	glm::mat4x4 moveLeft();
	glm::mat4x4 moveForward();
	glm::mat4x4 moveBackward();
	glm::mat4x4 moveUp();
	glm::mat4x4 moveDown();

	glm::mat4x4 lookRight();
	glm::mat4x4 lookLeft();
	glm::mat4x4 lookUp();
	glm::mat4x4 lookDown();

};
