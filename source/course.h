#pragma once
#include "stdafx.h"

#include <vector>

#include "header.h"


#include "cmd.h"

#include "point.h"
#include "textedpoint.h"
#include "playerpoint.h"
#include "pointobject.h"


struct course {
	std::vector<cmd> cmds;
	std::vector<pointobject>pobjs;


	textedpoint startpoint;
	textedpoint goalpoint;

	int checkdpointnum = 0;
	int allcheckpointnum = 0;
};

