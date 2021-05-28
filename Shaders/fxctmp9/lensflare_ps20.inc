#include "shaderlib/cshader.h"

class lensflare_ps20_Static_Index
{
public:
	lensflare_ps20_Static_Index() { }
	int GetIndex() { return 0;}
};
#define shaderStaticTest_lensflare_ps20 0
class lensflare_ps20_Dynamic_Index
{
public:
	lensflare_ps20_Dynamic_Index() { }
	int GetIndex() { return 0; }
};
#define shaderDynamicTest_lensflare_ps20 0
