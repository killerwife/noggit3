#ifndef WMO_H
#define WMO_H

#include <vector>
#include <set>

#include "manager.h"
#include "vec3d.h"
#include "mpq.h"
#include "quaternion.h"
#include "video.h"

#include "ModelInstance.h" // ModelInstance

class WMO;
class WMOGroup;
class WMOInstance;
class WMOManager;
class Liquid;
class Model;


class WMOGroup {
	WMO *wmo;
	int flags;
	Vec3D v1,v2;
	int nTriangles, nVertices;
	//GLuint dl,dl_light;
	Vec3D center;
	float rad;
	int num;
	int fog;
	int nDoodads, nBatches;
	short *ddr;
	Liquid *lq;
	std::vector< std::pair<GLuint, int> > lists;
public:
	Vec3D BoundingBoxMin;
	Vec3D BoundingBoxMax;
	Vec3D VertexBoxMin;
	Vec3D VertexBoxMax;
	bool indoor, hascv;
	bool visible;

	bool outdoorLights;
	std::string name;

	WMOGroup():nBatches(0) {}
	~WMOGroup();
	void init(WMO *wmo, MPQFile &f, int num, char *names);
	void initDisplayList();
	void initLighting(int nLR, short *useLights);
	void draw(const Vec3D& ofs, const float rot);
	void drawLiquid();
	void drawDoodads(unsigned int doodadset, const Vec3D& ofs, const float rot);
	void drawDoodadsSelect(unsigned int doodadset, const Vec3D& ofs, const float rot);
	void setupFog();
};

struct WMOMaterial {
	int flags;
	int specular;
	int transparent; // Blending: 0 for opaque, 1 for transparent
	int nameStart; // Start position for the first texture filename in the MOTX data block	
	unsigned int col1; // color
	int d3; // flag
	int nameEnd; // Start position for the second texture filename in the MOTX data block
	unsigned int col2; // color
	int d4; // flag
	unsigned int col3;
	float f2;
	float diffColor[3];
	int texture1; // this is the first texture object. of course only in RAM. leave this alone. :D
	int texture2; // this is the second texture object.
	// read up to here -_-
	GLuint tex;
};

struct WMOLight {
	unsigned int flags, color;
	Vec3D pos;
	float intensity;
	float unk[5];
	float r;

	Vec4D fcolor;

	void init(MPQFile &f);
	void setup(GLint light);

	static void setupOnce(GLint light, Vec3D dir, Vec3D lcol);
};

struct WMOPV {
	Vec3D a,b,c,d;
};

struct WMOPR {
	short portal, group, dir, reserved;
};

struct WMODoodadSet {
	char name[0x14];
	int start;
	int size;
	int unused;
};

struct WMOLiquidHeader {
	int X, Y, A, B;
	Vec3D pos;
	short type;
};

struct WMOFog {
	unsigned int flags;
	Vec3D pos;
	float r1, r2, fogend, fogstart;
	unsigned int color1;
	float f2;
	float f3;
	unsigned int color2;
	// read to here (0x30 bytes)
	Vec4D color;
	void init(MPQFile &f);
	void setup();
};

class WMO: public ManagedItem {
public:
	bool draw_group_boundingboxes;

	std::string		WMOName;
	std::string filename;
	WMOGroup *groups;
	unsigned int nTextures, nGroups, nP, nLights, nModels, nDoodads, nDoodadSets, nX;
	WMOMaterial *mat;
	Vec3D extents[2];
	std::vector<std::string> textures;
	std::vector<std::string> models;
	std::vector<ModelInstance> modelis;

	std::vector<WMOLight> lights;
	std::vector<WMOPV> pvs;
	std::vector<WMOPR> prs;

	std::vector<WMOFog> fogs;

	std::vector<WMODoodadSet> doodadsets;

	Model *skybox;
	int sbid;

	WMO(const std::string& name);
	~WMO();
	void draw(int doodadset, const Vec3D& ofs, const float rot, bool boundingbox, bool groupboxes, bool highlight);
	void drawSelect(int doodadset, const Vec3D& ofs, const float rot);
	//void drawPortals();
	void drawSkybox( Vec3D pCamera, Vec3D pLower, Vec3D pUpper );


};

typedef unsigned int WMOIDTYPE;

class WMOManager: public Manager<WMOIDTYPE>
{
private:
	static int baseid;
public:
	static WMOIDTYPE add(const std::string& name);
  
  static int nextID()
  {
    return baseid++;
  }
};


#endif
