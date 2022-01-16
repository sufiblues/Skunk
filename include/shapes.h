#pragma once 

#include "../libs/glm/glm.hpp"
#include "../libs/glm/vec2.hpp"
#include "utils.h"
#include "sdlcontext.h"
#include <vector>
#include <array>
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

struct Line{
    std::array<glm::vec2, 2> vertices; 
};

struct Circle{
    glm::vec2 center; 
    uint radius;
};

struct Triangle{
    std::array<glm::vec2, 3> vertices;
};

struct Quadrilateral{
    std::array<glm::vec2, 4> vertices;
};

Triangle createEquilateralTriangle(glm::vec2 center, float r);
Quadrilateral createRectangle(glm::vec2 center, float width, float height);

glm::vec2 vectorRotate(glm::vec2 v, glm::vec2 origin, float theta);

/* Render Functions */ 
void renderTriangle(Triangle t, SDL_Color color);

void renderFillShape(Circle shape, SDL_Color color);

/* Marshalling */ 
void serialization();


/* All shapes inputed should be convex */
template <typename T>
void renderFillShape(T shape, SDL_Color color){
    //set up the vertex array for the render function
    SDL_Vertex vert[shape.vertices.size()];
    uint no_triangles = shape.vertices.size() - 2;
    //set up the index array for the render function as well. 
    int indices[no_triangles * 3];

    //set up first two vertices 
    vert[0].position = {shape.vertices[0][0], shape.vertices[0][1]};
    vert[1].position = {shape.vertices[1][0], shape.vertices[1][1]};
    vert[0].color = color;
    vert[1].color = color; 
    for(int i = 0; i < no_triangles; i++){
        //set up the verticies
        vert[i+2].position = {shape.vertices[i+2][0], shape.vertices[i+2][1]};
        vert[i+2].color = color;
        //set up the triangle in the indices array 
        indices[(i*3)] = 0;
        indices[(i*3) + 1] = i + 1;
        indices[(i*3) + 2] = i + 2;
    }

    SDL_RenderGeometry(sdlcontext::Renderer, NULL, vert, shape.vertices.size(), indices, no_triangles * 3);
}

template<typename Convex> 
glm::vec2 polygonCenter(Convex a){
    glm::vec2 center = glm::vec2(0,0);

    for (int i = 0; i < a.vertices.size(); i++){
        center += a.vertices[i];
    }
    center /= a.vertices.size();
    return center;
}

template<typename T>
void polygonMove(T* a, glm::vec2 shift){
    for (int i = 0; i < a->vertices.size(); i++){
        a->vertices[i] = a->vertices[i] + shift;
    }
}

template<typename Convex>
inline glm::vec2 projection(Convex a, glm::vec2 axis){
    float min_proj = glm::dot(a.vertices[0], axis);
    float max_proj = glm::dot(a.vertices[0], axis);
    for (int i = 0; i < a.vertices.size(); i++){
        float proj = glm::dot(a.vertices[i], axis);
        if(proj < min_proj) min_proj = proj;
        if(proj > max_proj) max_proj = proj;
    }
    return glm::vec2(min_proj, max_proj);
}

template<typename Convex, typename Convex_>
glm::vec2 MTV(Convex a, Convex_ b){
    float smallest_overlap = std::numeric_limits<float>::infinity();
    glm::vec2 smallest_axis = glm::vec2(0,0);
    //check for overlapping boundires on axes of Polygon A
    for (int i = 0; i < a.vertices.size(); ++i){
      //create edge by subtracting the next vertex by the current one , clockwise doesnt matter
      glm::vec2 current = a.vertices[i];
      glm::vec2 next = a.vertices[(i+1) % a.vertices.size()];

      glm::vec2 edge = next - current;

      //get the normal vector to the edge !! Clockwise edges REMEMBER!!
      glm::vec2 axis = glm::vec2(edge[1], -edge[0]);

      //axis = glm::normalize(axis);
    
      glm::vec2 a_bounds = projection(a,axis);
      glm::vec2 b_bounds = projection(b,axis);

      //find overlap
      float overlap = fmax(0, fmin(a_bounds[1], b_bounds[1]) - fmax(a_bounds[0], b_bounds[0]));

      //found a seperating axis
      if(overlap == 0.0f){ 
        return glm::vec2(0,0);
      }
      //else there is an overlap
      else{
        if (overlap < smallest_overlap) {
          std::cout << "a " << a_bounds[0] << " " << a_bounds[1] << std::endl; 
          std::cout << "b " << b_bounds[0] << " " << b_bounds[1] << std::endl; 

          smallest_overlap = overlap;
          smallest_axis = axis;
        }
      }
    }

    //check axis on b
    for (int i = 0; i < b.vertices.size(); ++i){

      glm::vec2 current = b.vertices[i];
      glm::vec2 next = b.vertices[(i+1) % b.vertices.size()];

      glm::vec2 edge = next - current;

      glm::vec2 axis = glm::vec2(edge[1], -edge[0]);

      glm::vec2 a_proj_bounds = projection(a,axis);
      glm::vec2 b_proj_bounds = projection(b,axis);

      float overlap = fmax(0, fmin(a_proj_bounds[1], b_proj_bounds[1]) - fmax(a_proj_bounds[0], b_proj_bounds[0]));

      //found a seperating axis
      if(overlap == 0.0f){ 
        return glm::vec2(0,0);
      }
      //else there is an overlap
      else{
        if (overlap < smallest_overlap) {
          smallest_overlap = overlap;
          smallest_axis = axis;
        }
      }
    }

    glm::vec2 center_a = polygonCenter(a);
    glm::vec2 center_b = polygonCenter(b);
    glm::vec2 direction = center_a - center_b;

    std::cout << "overlap " <<  smallest_overlap << std::endl;

    if (glm::dot(direction, smallest_axis) < 0.0f) {
      smallest_axis = -smallest_axis;
    }

    smallest_axis = glm::normalize(smallest_axis);

    return smallest_axis * smallest_overlap;
}

inline float projectionOverlap(glm::vec2 a, glm::vec2 b) {
    return fmax(0, fmin(a[1], b[1]) - fmax(a[0], b[0]));
}

template<typename Polygon, typename Polygon_>
  glm::vec2 MTV2(Polygon a, Polygon_ b){
    float overlap = std::numeric_limits<float>::infinity();
    glm::vec2 smallest_axis = glm::vec2(0,0);

    //std::vector<glm::vec2> a_axes = getAxes(a);
    //std::vector<glm::vec2> b_axes = getAxes(b);

    for(int i = 0; i < a.vertices.size(); i++){
      glm::vec2 current = a.vertices[i];
      glm::vec2 next = a.vertices[(i+1) % a.vertices.size()];

      glm::vec2 edge = next - current;

      //get the normal vector to the edge !! Clockwise edges REMEMBER!!
      glm::vec2 axis = (glm::vec2(edge[1], -edge[0]));

      glm::vec2 a_bounds = projection(a,axis);
      glm::vec2 b_bounds = projection(b,axis);

      float o = projectionOverlap(a_bounds,b_bounds);

      if (o == 0.0f){
        return glm::vec2(0,0); 
      }
      else{
        if(o < overlap){
          std::cout << "a_overlap " << o << "\n";

          overlap = o;
          smallest_axis = axis;
        }
      }
    }

    for (int i = 0; i < b.vertices.size(); i++){
      glm::vec2 current = b.vertices[i];
      glm::vec2 next = b.vertices[(i+1) % b.vertices.size()];

      glm::vec2 edge = next - current;

      //get the normal vector to the edge !! Clockwise edges REMEMBER!!
      glm::vec2 axis = glm::normalize(glm::vec2(edge[1], -edge[0]));

      glm::vec2 a_bounds = projection(a,axis);
      glm::vec2 b_bounds = projection(b,axis);

        //overlap = dotproduct/magnitude
      float o = projectionOverlap(a_bounds,b_bounds);

      if (o == 0.0f){
        return glm::vec2(0,0); 
      }
      else{
        if(o < overlap){
          std::cout << "b_overlap " << o << "\n";
          overlap = o;
          smallest_axis = axis;
        }
      }
    }

    glm::vec2 center_a = polygonCenter(a);
    glm::vec2 center_b = polygonCenter(b);

    glm::vec2 direction = center_a - center_b;
    if(glm::dot(direction, smallest_axis) < 0.0f){
        smallest_axis = - smallest_axis;
    }

    smallest_axis = glm::normalize(smallest_axis);
    return smallest_axis * overlap;

}

