//======================================================
// File Name	: Utilities.h
// Summary		: ���[�e�B���e�B
// Date			: 2019.07.24
// Author		: Takumi Yanase
//======================================================
// �C���N���[�h�K�[�h
#ifndef INCLUDE_UTILITIES
#define INCLUDE_UTILITIES
//======================================================
#include <algorithm>
//======================================================
template<class T>
inline constexpr const T& Clamp(const T& v, const T& low, const T& high)
{
	return std::min(std::max(v, low), high);
}

#endif // INCLUDE_UTILITIES
