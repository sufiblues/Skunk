#include "shapes.h"

Triangle createEquilateralTriangle(glm::vec2 center, float r){

  Triangle t;

  t.vertices[0] = center + glm::vec2(0,-r);
  t.vertices[1] = center + glm::vec2(r*cos(M_PI/6), r * sin(M_PI/6));
  t.vertices[2] = center + glm::vec2(-(r*cos(M_PI/6)), r * sin(M_PI/6));

  return t;
}

Quadrilateral createRectangle(glm::vec2 center, float width, float height){
  Quadrilateral q;
  q.vertices[0] = center + glm::vec2(-width/2, -height/2);
  q.vertices[1] = center + glm::vec2(width/2, -height/2);
  q.vertices[2] = center + glm::vec2(width/2, height/2);
  q.vertices[3] = center + glm::vec2(-width/2, height/2);
  return q;

}

/* Vector is rotated counterclockwise by theta. The origin is what you are rotating around */
glm::vec2 vectorRotate(glm::vec2 v, glm::vec2 origin, float theta){
  //find the delta angle
  float s = sin(theta);
  float c = cos(theta);

  //zero out the origin
  v = v - origin;
  //rotate around (0,0)
  float xnew = v[0] * c - v[1] * s;
  float ynew = v[0] * s + v[1] * c;

  //add origin transform 
  v[0] = xnew + origin[0];
  v[1] = ynew + origin[1];

  return v;
}

void renderFillShape(Circle circle, SDL_Color color){
    //the resolution of the circle, i.e. how accurate do you want it to look
    //could convert it to an argument but whatever
    uint no_sides = 30;
    //add additional vertex for the center of the circle 
    uint no_vertices = no_sides + 1;

    SDL_Vertex vert[no_vertices];
    //set the center of the vertex 
    vert[0].position = {circle.center[0], circle.center[1]};
    vert[0].color = color;

    //divide the circumference of the circle into angles 
    float delta_angle = 2 * M_PI / no_sides; 
    
    //each side will have its own triangle which needs three vertices. 
    uint no_indices = (no_sides) * 3;
    int indices[no_indices];
    //set the vertices
    for(int i = 0; i < no_sides; i ++){
        //rotate point around 
        glm::vec2 point = vectorRotate(circle.center + glm::vec2(0,circle.radius), circle.center, i * delta_angle);
        vert[i+1].position = {point[0], point[1]};
        vert[i+1].color = color;
        //setting the triangle for each side i.e [0,1,2], [0,2,3] [0,3,4] etc
        indices[(i*3)] = 0;
        indices[(i*3) + 1] = i + 1;
        indices[(i*3) + 2] = i + 2;
    }
    // last vertex should be the first one in order to complete the circle
    indices[no_indices - 1] = 1;

    SDL_RenderGeometry(sdlcontext::Renderer, NULL, vert, no_vertices, indices, no_indices);




}
