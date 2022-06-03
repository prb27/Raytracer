#include "raycolor.h"
#include "first_hit.h"
#include "blinn_phong_shading.h"
#include "reflect.h"

bool raycolor(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector< std::shared_ptr<Light> > & lights,
  const int num_recursive_calls,
  Eigen::Vector3d & rgb)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  int hit_id;
  double t;
  Eigen::Vector3d normal;
  normal.normalize();
  
  if(first_hit(ray, min_t, objects, hit_id, t, normal)){
    if(num_recursive_calls == 0){
      rgb = blinn_phong_shading(ray, hit_id, t, normal, objects, lights);
    } 
    if(num_recursive_calls > 30){
      return true;
    } else {
      //reflections
      rgb = blinn_phong_shading(ray, hit_id, t, normal, objects, lights);
      Eigen::Vector3d rgb_reflect;
      Ray reflection;
      reflection.origin = ray.origin  + t * ray.direction;
      reflection.direction = (ray.direction - 2*(ray.direction.dot(normal))*normal);
      raycolor(reflection, 0.00001, objects, lights, num_recursive_calls + 1, rgb_reflect);
      rgb += (objects[hit_id]->material->km.array() * rgb_reflect.array()).matrix();
    }
  } else {
    return false;
  }

  
  return true;
  ////////////////////////////////////////////////////////////////////////////
}
