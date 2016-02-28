//
//  renderer.cpp
//  Rasteriser
//
//  Created by Toby Devlin on 28/02/2016.
//  Copyright © 2016 Toby Devlin. All rights reserved.
//

#include "renderer.hpp"



struct Point2D {
    float x, y;
};


class Element2D {
    
    float minx, maxx;
    float miny, maxy;
    int NV;
    
public:
    virtual void factory(float * vertx, float * verty)=0;
};

class Tri2D : Element2D{
    
public:
    Tri2D(float * vertx, float * verty);
    int render(void);
};

class Quad2D : Element2D{
    
public:
    Quad2D(float * vertx, float * verty);
    int render(void);
};

float orient2d(const Point2D& a, const Point2D& b, const Point2D& c)
{
    return (b.x-a.x)*(c.y-a.y) - (b.y-a.y)*(c.x-a.x);
}


float mymin(float a, float b, float c) {
    if (a<=c & a<=b)
        return a;
    else if (b<=c)
        return b;
    else
        return c;
}

float mymin(float a, float b) {
    if (a<b)
        return a;
    else
        return b;
}

float mymax(float a, float b) {
    if (a>b)
        return a;
    else
        return b;
}

float mymax(float a, float b, float c) {
    if (a>b & a>c)
        return a;
    else if (b>c)
        return b;
    else
        return c;
}


void drawTri(const Point2D& v0, const Point2D& v1, const Point2D& v2)
{
    // Compute triangle bounding box
    float minX = mymin(v0.x, v1.x, v2.x);
    float minY = mymin(v0.y, v1.y, v2.y);
    float maxX = mymax(v0.x, v1.x, v2.x);
    float maxY = mymax(v0.y, v1.y, v2.y);
    
    // Rasterize
    Point2D p;
    for (p.y = minY; p.y <= maxY; p.y++) {
        for (p.x = minX; p.x <= maxX; p.x++) {
            // Determine barycentric coordinates
            int w0 = orient2d(v1, v2, p);
            int w1 = orient2d(v2, v0, p);
            int w2 = orient2d(v0, v1, p);
            
            // If p is on or inside all edges, render pixel.
            if (w0 >= 0 && w1 >= 0 && w2 >= 0)
                renderPixel(p, w0, w1, w2);
        }
    }
}