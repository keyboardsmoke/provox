#pragma once

#include <vector>
#include "Leb128.h"

// Implementing floating point using ULEB128, to a maximum of 64-bits
// Exceeding 64-bits results in lost precision as additional data is shifted off
class LebReal
{
public:

private:
	//
};