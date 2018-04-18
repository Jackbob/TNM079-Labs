
#include "UniformCubicSplineSubdivisionCurve.h"

UniformCubicSplineSubdivisionCurve::UniformCubicSplineSubdivisionCurve(
    const std::vector<Vector3<float>> &joints, Vector3<float> lineColor,
    float lineWidth)
    : mCoefficients(joints), mControlPolygon(joints) {
  this->mLineColor = lineColor;
  this->mLineWidth = lineWidth;
}

void UniformCubicSplineSubdivisionCurve::Subdivide() {
  // Allocate space for new coefficients
  std::vector<Vector3<float>> newc;

  assert(mCoefficients.size() > 4 && "Need at least 5 points to subdivide");

  int n {(int)mCoefficients.size()};
  int newn{n*2-1};
  newc.resize(newn);

  // Implement the subdivision scheme for a natural cubic spline here
  for(int i=1; i<newn-1; i++){
    if(i%2 == 0) {
      int idx1{i/2-1}, idx2{i/2}, idx3{i/2+1};
      newc[i] = (mCoefficients[idx1] + 6 * mCoefficients[idx2] + mCoefficients[idx3]) / 8;
    }
    else {
      int idx1{i/2}, idx2{i/2+1};
      newc[i] = (mCoefficients[idx1] + mCoefficients[idx2]) / 2;
    }
  }
  newc[0] = mCoefficients[0];
  newc[newn-1] = mCoefficients[n-1];

  // If 'mCoefficients' had size N, how large should 'newc' be? Perform a check
  // here!
  assert(true && "Incorrect number of new coefficients!");

  mCoefficients = newc;
}

void UniformCubicSplineSubdivisionCurve::Render() {
  // Apply transform
  glPushMatrix(); // Push modelview matrix onto stack

  // Convert transform-matrix to format matching GL matrix format
  // Load transform into modelview matrix
  glMultMatrixf(mTransform.ToGLMatrix().GetArrayPtr());

  mControlPolygon.Render();

  // save line point and color states
  glPushAttrib(GL_POINT_BIT | GL_LINE_BIT | GL_CURRENT_BIT);

  // draw segments
  glLineWidth(mLineWidth);
  glColor3fv(mLineColor.GetArrayPtr());
  glBegin(GL_LINE_STRIP);
  // just draw the spline as a series of connected linear segments
  for (auto &mCoefficient : mCoefficients) {
    glVertex3fv(mCoefficient.GetArrayPtr());
  }
  glEnd();

  // restore attribs
  glPopAttrib();

  glPopMatrix();

  GLObject::Render();
}
