//////////////////////////////////////////////////////////////////////////////
//
//  --- Object.cpp ---
//  Created by Brian Summa
//
//////////////////////////////////////////////////////////////////////////////


#include "common.h"
/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
int ID = 1;


bool rayTriangleIntersect(const vec4 &P, const vec4 &E,
                          const vec3 &v0, const vec3 &v1, const vec3 &v2, const vec3 v0Normal, const vec3 v1Normal, const vec3 v2Normal,
                          float &t);

vec3 Vec3(vec4 v) {
    return vec3(v.x, v.y, v.z);
}

vec4 Vec4(vec3 v) {
    return vec4(v.x, v.y, v.z, 0.0);
}

Object::IntersectionValues Sphere::intersect(vec4 p0, vec4 V) {
    IntersectionValues result;

    double t = raySphereIntersection(p0, V);
    if (t != std::numeric_limits<double>::infinity()) {
        result.t = t;
        result.P = p0 + t * V;
        result.N = normalize(result.P - this->center);
        result.ID_ = ID;
        result.name == "sphere";
        ID++;
    }
    return result;
}

/* -------------------------------------------------------------------------- */
/* ------ Ray = p0 + t*V  sphere at origin center and radius radius    : Find t ------- */

double Sphere::raySphereIntersection(vec4 p0, vec4 V) {
    double t = std::numeric_limits<double>::infinity();

    vec3 V3 = normalize(Vec3(V)); //V direction du rayon
    vec3 distcentre = Vec3(p0 - center);
    if (strcmp(this->path,"")==0) {
        double a = dot(V3, V3);
        double b = 2 * dot(distcentre, V3);
        double c = dot(distcentre, distcentre) - (radius * radius);
        double delta = (b * b) - 4 * a * c;
        //std::cout << " delta = " << delta << std::endl;
        if (delta > EPSILON) {
            // t = (-b - sqrt(delta)) / (2.0 * length(V) * a);
            double t1 = (-b - sqrt(delta)) / (2.0 * a);
            double t2 = (-b + sqrt(delta)) / (2.0 * a);
            if (t1 > 0 && t2 > EPSILON)
                t = fmin(t1, t2);
            if (t1 <= EPSILON)
                t = t2;
            if (t2 <= EPSILON)
                t = t1;
            if (t1 <= EPSILON && t2 <= EPSILON)
                t = std::numeric_limits<double>::infinity();
        }
    } else {
        for (uint32_t i = 0;i < mesh.getNumTri();i++) {
//            std::cerr<<  i << "\n";
            const vec3 &v0 = Vec3(mesh.vertices[i * 3]);
            const vec3 &v0Normal = Vec3(mesh.normals[i * 3]);

            const vec3 &v1 = Vec3(mesh.vertices[i * 3 + 1]);
            const vec3 &v1Normal = Vec3(mesh.normals[i * 3 + 1]);

            const vec3 &v2 = Vec3(mesh.vertices[i * 3 + 2]);
            const vec3 &v2Normal = Vec3(mesh.normals[i * 3 + 2]);

            float tfar = std::numeric_limits<double>::infinity();
            if ( rayTriangleIntersect(p0, V, v0, v1, v2,v0Normal, v1Normal, v2Normal, tfar ) && tfar < t) {
                t = tfar;
            }
        }
    }
    return t;
}

/*https://fr.wikipedia.org/wiki/Algorithme_d%27intersection_de_Möller–Trumbore*/
bool rayTriangleIntersect(const vec4 &P, const vec4 &E,
                          const vec3 &v0, const vec3 &v1, const vec3 &v2, const vec3 normaleV0, const vec3 normaleV1, const vec3 normaleV2,
float &t) {
    vec3 orig = Vec3(P);
    vec3 dir = Vec3(E);
    vec3 vertex0 = v0;
    vec3 vertex1 = v1;
    vec3 vertex2 = v2;
    vec3 edge1, edge2, h, s, q;
    float a, f, u, v;
    edge1 = vertex1 - vertex0;
    edge2 = vertex2 - vertex0;
    h = cross(dir, edge2);
    a = dot(edge1, h);

    if (a > -EPSILON && a < EPSILON)
        return false;    // Le rayon est parallèle au triangle.

    f = 1.0f / a;
    s = Vec3(orig) - vertex0;
    u = f * (dot(s, h));
    if (u < EPSILON || u > 1.0)
        return false;

    q = cross(s, edge1);
    v = f * dot(dir, q);
    if (v < EPSILON || u + v > 1.0)
        return false;

    // On calcule t pour savoir ou le point d'intersection se situe sur la ligne.
    t = f * dot(edge2, q);
    if (t > EPSILON) // Intersection avec le rayon
    {

        return true;
    } else // On a bien une intersection de droite, mais pas de rayon.
        return false;
}




/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
Object::IntersectionValues Square::intersect(vec4 p0, vec4 V) {
    IntersectionValues result;
    double t = raySquareIntersection(p0, V);

    if (t != std::numeric_limits<double>::infinity()) {
        result.t = t;
        result.P = p0 + t * V;
        result.N = Vec4(normal);
        result.ID_ = ID;
        ID++;
    }
    return result;

}

/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
double Square::raySquareIntersection(vec4 p0, vec4 V) {
    double t = std::numeric_limits<double>::infinity();

    vec3 p0_vec3 = vec3(p0.x, p0.y, p0.z);
    vec3 V_vec3 = vec3(V.x, V.y, V.z);
    vec3 point_vec3 = vec3(point.x, point.y, point.z);

    double denom = dot(V_vec3, normal);
    if (denom != 0) {
        t = (dot(point_vec3, normal) - dot(p0_vec3, normal)) / denom;

    }
    vec4 p = p0_vec3 + t * V_vec3;
    float vec1_2 = dot(normalize(p - mesh.vertices[5]), normalize(mesh.vertices[1] - mesh.vertices[5]));
    float vec2_3 = dot(normalize(p - mesh.vertices[1]), normalize(mesh.vertices[2] - mesh.vertices[1]));
    float vec3_4 = dot(normalize(p - mesh.vertices[2]), normalize(mesh.vertices[0] - mesh.vertices[2]));
    float vec4_1 = dot(normalize(p - mesh.vertices[0]), normalize(mesh.vertices[5] - mesh.vertices[0]));
    if (vec1_2 > EPSILON and vec2_3 > EPSILON and vec3_4 > EPSILON and vec4_1 > EPSILON && t > EPSILON) return t;
    return std::numeric_limits<double>::infinity();

}

