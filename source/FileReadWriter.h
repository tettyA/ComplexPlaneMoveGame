#pragma once
#include "course.h"

#include "stdafx.h"

#include <vector>
#include <string>

#include "header.h"

void CourseLoader(course& c, FilePath fp);


void CourseWriter(course& c, std::u32string filepath);