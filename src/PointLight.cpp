#include "PointLight.h"

void PointLight::direction(
  const Eigen::Vector3d & q, Eigen::Vector3d & d, double & max_t) const
{
  ////////////////////////////////////////////////////////////////////////////
  //p is the point of the light
  Eigen::Vector3d diff = p - q; 
  d = diff.normalized();
  max_t = diff.norm();
  ////////////////////////////////////////////////////////////////////////////
}
