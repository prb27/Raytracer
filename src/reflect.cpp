#include <Eigen/Core>

Eigen::Vector3d reflect(const Eigen::Vector3d & in, const Eigen::Vector3d & n)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  Eigen::Vector3d normal_in = in.normalized();
  Eigen::Vector3d normal_n = n.normalized();
  return normal_in - 2 * (normal_in.dot(normal_n)) * normal_n;
  ////////////////////////////////////////////////////////////////////////////
}
