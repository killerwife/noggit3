// This file is part of Noggit3, licensed under GNU General Public License (version 3).

#include <noggit/Misc.h>

#include <iomanip>
#include <map>
#include <sstream>
#include <string>
#include <vector>

namespace misc
{
  void find_and_replace(std::string& source, const std::string& find, const std::string& replace)
  {
    size_t found = source.rfind(find);
    while (found != std::string::npos) //fixed unknown letters replace. Now it works correctly and replace all found symbold instead of only one at previous versions
    {
      source.replace(found, find.length(), replace);
      found = source.rfind(find);
    }
  }

  float frand()
  {
    return rand() / static_cast<float>(RAND_MAX);
  }

  float randfloat(float lower, float upper)
  {
    return lower + (upper - lower) * frand();
  }

  int randint(int lower, int upper)
  {
    return lower + static_cast<int>((upper + 1 - lower) * frand());
  }

  float dist(float x1, float z1, float x2, float z2)
  {
    float xdiff = x2 - x1, zdiff = z2 - z1;
    return std::sqrt(xdiff*xdiff + zdiff*zdiff);
  }

  float dist(math::vector_3d const& p1, math::vector_3d const& p2)
  {
    return dist(p1.x, p1.z, p2.x, p2.z);
  }

  // return the shortest distance between the point (x, z)
  // and square at (squareX, squareZ) with a size of unitSize
  float getShortestDist(float x, float z, float squareX, float squareZ, float unitSize)
  {
    float px, pz;

    if (x >= squareX && x < squareX + unitSize)
    {
      px = x;
    }
    else
    {
      px = (squareX < x) ? squareX + unitSize : squareX;
    }

    if (z >= squareZ && z < squareZ + unitSize)
    {
      pz = z;
    }
    else
    {
      pz = (squareZ < z) ? squareZ + unitSize : squareZ;
    }

    return (px == x && pz == z) ? 0.0f : dist(x, z, px, pz);
  }

  float getShortestDist(math::vector_3d const& pos, math::vector_3d const& square_pos, float unitSize)
  {
    return getShortestDist(pos.x, pos.z, square_pos.x, square_pos.z, unitSize);
  }

  bool rectOverlap(math::vector_3d const* r1, math::vector_3d const* r2)
  {
    return r1[0].x <= r2[1].x
      && r2[0].x <= r1[1].x
      && r1[0].z <= r2[1].z
      && r2[0].z <= r1[1].z;
  }

  float angledHeight(math::vector_3d const& origin, math::vector_3d const& pos, math::radians const& angle, math::radians const& orientation)
  {
    return ( origin.y
           + (  (pos.x - origin.x) * math::cos(orientation)
              + (pos.z - origin.z) * math::sin(orientation)
             ) * math::tan(angle));
  }

  void extract_v3d_min_max(math::vector_3d const& point, math::vector_3d& min, math::vector_3d& max)
  {
    min.x = std::min(min.x, point.x);
    max.x = std::max(max.x, point.x);
    min.y = std::min(min.y, point.y);
    max.y = std::max(max.y, point.y);
    min.z = std::min(min.z, point.z);
    max.z = std::max(max.z, point.z);
  }
}

void SetChunkHeader(sExtendableArray& pArray, int pPosition, int pMagix, int pSize)
{
  sChunkHeader* Header = pArray.GetPointer<sChunkHeader>(pPosition);
  Header->mMagic = pMagix;
  Header->mSize = pSize;
}

bool pointInside(math::vector_3d point, math::vector_3d extents[2])
{
  minmax(&extents[0], &extents[1]);

  return point.x >= extents[0].x && point.z >= extents[0].z &&
    point.x <= extents[1].x && point.z <= extents[1].z;
}

void minmax(math::vector_3d* a, math::vector_3d* b)
{
  if (a->x > b->x)
  {
    float t = b->x;
    b->x = a->x;
    a->x = t;
  }
  if (a->y > b->y)
  {
    float t = b->y;
    b->y = a->y;
    a->y = t;
  }
  if (a->z > b->z)
  {
    float t = b->z;
    b->z = a->z;
    a->z = t;
  }
}

bool checkInside(math::vector_3d extentA[2], math::vector_3d extentB[2])
{
  minmax(&extentA[0], &extentA[1]);
  minmax(&extentB[0], &extentB[1]);

  return pointInside(extentA[0], extentB) ||
    pointInside(extentA[1], extentB) ||
    pointInside(extentB[0], extentA) ||
    pointInside(extentB[1], extentA);
}

bool checkOriginInside(math::vector_3d extentA[2], math::vector_3d modelPos)
{
  return pointInside(modelPos, extentA);
}
