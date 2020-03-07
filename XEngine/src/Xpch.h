#pragma once
// Pre-Compiled Headers to increase performance, must include Xpch.h in every source file(.cpp)
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "XEngine/Log.h"
// If the platform is Windows 10 include Windows.h
#ifdef X_PLATFORM_WINDOWS
	#include <Windows.h>
#endif