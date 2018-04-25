/*************************************************************************************************
 *
 * Modeling and animation (TNM079) 2007
 * Code base for lab assignments. Copyright:
 *   Gunnar Johansson (gunnar.johansson@itn.liu.se)
 *   Ken Museth (ken.museth@itn.liu.se)
 *   Michael Bang Nielsen (bang@daimi.au.dk)
 *   Ola Nilsson (ola.nilsson@itn.liu.se)
 *   Andreas Sˆderstrˆm (andreas.soderstrom@itn.liu.se)
 *
 *************************************************************************************************/
#include "Quadric.h"

Quadric::Quadric(const Matrix4x4<float> &q) { this->mQuadric = q; }

Quadric::~Quadric() {}

/*!
 * Evaluation of world coordinates are done through either transformation
 * of the world-coordinates by mWorld2Obj, or transformation of the quadric
 * coefficient matrix by GetTransform() ONCE (see Section 2.2 in lab text).
 */
float Quadric::GetValue(float x, float y, float z) const {

    Implicit::TransformW2O(x,y,z);
    Vector4<float> point(x,y,z,1);

    return point * (mQuadric*point);

  }

/*!
 * Use the quadric matrix to evaluate the gradient.
 */
Vector3<float> Quadric::GetGradient(float x, float y, float z) const {


  //Implicit::TransformW2O(x,y,z);
  Vector4<float> p(x,y,z,1);

  Vector4<float> m1(mQuadric.operator()(0,0), mQuadric.operator()(0,1), mQuadric.operator()(0,2), mQuadric.operator()(0,3));
  Vector4<float> m2(mQuadric.operator()(1,0), mQuadric.operator()(1,1), mQuadric.operator()(1,2), mQuadric.operator()(1,3));
  Vector4<float> m3(mQuadric.operator()(2,0), mQuadric.operator()(2,1), mQuadric.operator()(2,2), mQuadric.operator()(2,3));

  Vector3<float> n {2*(p*m1), 2*(p*m2), 2*(p*m3)};

  //n.Normalize();

  return n;

}
