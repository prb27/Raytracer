#include "blinn_phong_shading.h"
// Hint:
#include "first_hit.h"
#include <iostream>
#include <math.h>

Eigen::Vector3d blinn_phong_shading(
  const Ray & ray,
  const int & hit_id, 
  const double & t,
  const Eigen::Vector3d & n,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector<std::shared_ptr<Light> > & lights)
{
  ////////////////////////////////////////////////////////////////////////////
  Eigen::Vector3d ambient = Eigen::Vector3d(0.1, 0.1, 0.1);
  Eigen::Vector3d rgb = (ambient.array() * (objects[hit_id]->material->ka).array()).matrix();
  
  for(int i = 0; i < lights.size(); i++){
    
    Eigen::Vector3d surface_point = ray.origin + (ray.direction * t);
    Eigen::Vector3d light_direction;
    double light_max_t;
    lights[i]->direction(surface_point, light_direction, light_max_t);
    
    int shade_check_hit;
    double shade_check_t;
    Eigen::Vector3d shade_check_n;
    
    Ray light_ray;
    light_ray.origin = surface_point;
    light_ray.direction = light_direction;
    bool occluded = first_hit(light_ray, 0.01, objects, shade_check_hit, shade_check_t, shade_check_n);
    
    if(!occluded){
    //diffuse lighting
      Eigen::Vector3d diffuse = (lights[i]->I.array() * (objects[hit_id]->material->kd).array()).matrix() * fmax(n.dot(light_direction), 0);
    
    //specular lighting color
      Eigen::Vector3d half_angle = light_direction.normalized() + (ray.origin + t * ray.direction.normalized()).normalized();
      half_angle = half_angle / half_angle.norm();

      Eigen::Vector3d specular = (lights[i]->I.array() * (objects[hit_id]->material->ks).array()).matrix() * pow(fmax(n.dot(half_angle), 0), objects[hit_id]->material->phong_exponent);

      rgb += diffuse + specular;
    }
    
  }
  return rgb;
  ////////////////////////////////////////////////////////////////////////////
}
