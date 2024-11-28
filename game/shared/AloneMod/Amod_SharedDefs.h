#ifndef __AMOD_SHARED_DEFS_H
#define __AMOD_SHARED_DEFS_H

extern const char* g_szMapNames[67];

bool IsCityMap(const char* szMapName);

#ifdef CLIENT_DLL
extern const char* szMapName;
#endif

#endif