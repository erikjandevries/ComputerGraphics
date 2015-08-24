// Transform.cpp: implementation of the Transform class.


#include <iostream>
#include "glm/ext.hpp"
#include "Transform.h"

//Please implement the following functions:

// Helper rotation function.
mat3 Transform::rotate(const float degrees, const vec3& axis) {
  // YOUR CODE FOR HW1 HERE
  float theta = -degrees * pi / 180;
  vec3 a = glm::normalize(axis);

  // We immediately define the transposed matrix,
  // because of column major ordering
  mat3 R1T = cos(theta) * mat3(1,0,0, 0,1,0, 0,0,1);
  mat3 R2T = (1-cos(theta)) * mat3( a.x*a.x, a.x*a.y, a.x*a.z,
                                   a.y*a.x, a.y*a.y, a.y*a.z,
                                   a.z*a.x, a.z*a.y, a.z*a.z);
  mat3 R3T = sin(theta) * mat3(   0,  a.z, -a.y,
                              -a.z,    0,  a.x,
                               a.y, -a.x,    0);

  mat3 RT = R1T + R2T + R3T;

  // You will change this return call
  //return mat3();
  return RT;
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
  // YOUR CODE FOR HW1 HERE

  eye = eye * Transform::rotate(degrees, up);

  //std::cout << "degrees: " << degrees << std::endl;
  //std::cout << "    eye: " << eye.x << ", " << eye.y << ", " << eye.z << std::endl;
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
  // YOUR CODE FOR HW1 HERE
  vec3 n = glm::cross(eye, up);
  eye = eye * Transform::rotate(degrees, n);
  up = up * Transform::rotate(degrees, n);

  //std::cout << "degrees: " << degrees << std::endl;
  //std::cout << "    eye: " << eye.x << ", " << eye.y << ", " << eye.z << std::endl;
  //std::cout << "     up: " << up.x << ", " << up.y << ", " << up.z << std::endl;
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
  // YOUR CODE FOR HW1 HERE
  vec3 w = glm::normalize(eye);
  vec3 u = glm::normalize(glm::cross(up,w));
  vec3 v = glm::cross(w,u);

  mat4 M = mat4( u.x, u.y, u.z, -glm::dot(u,eye),
                 v.x, v.y, v.z, -glm::dot(v,eye),
                 w.x, w.y, w.z, -glm::dot(w,eye),
                   0,   0,   0, 1.0f
               );

  // You will change this return call
  //return mat4();
  return glm::transpose(M);
}

Transform::Transform()
{

}

Transform::~Transform()
{

}
