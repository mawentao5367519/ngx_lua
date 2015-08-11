extern "C"
{
	#include <lua.h>
	#include <lauxlib.h>
	#include <lualib.h>
}
#include "CDes.h"
#include <string.h>
//unsigned char  key[]="12345678";

static int DesEncrypt(lua_State *L)
{
	int argc = lua_gettop(L);
	if (2 != argc)
	{
		lua_pushnil(L);
		return 1;
	}

	size_t len;
	size_t len2;
	if (!luaL_checklstring(L, 1, &len) || !luaL_checklstring(L, 2, &len2))
	{
		lua_pushnil(L);
		return 1;
	}

	if (len2 != 8)
	{
		lua_pushnil(L);
		return 1;
	}

	const char *content = luaL_checklstring(L, 1, &len);
	const char *key = luaL_checklstring(L, 2, &len2);

	unsigned char *outbuf = new unsigned char[len * 2];
	if (outbuf == NULL)
	{
		lua_pushnil(L);
		return 1;
	}
	memset(outbuf, 0, len * 2);

	CDES cs;
	if (cs.RunDes(cs.ENCRYPT,cs.ECB, (const unsigned char* )content, outbuf, len,(const unsigned char* )key, len2))
	{
		string str = cs.base64_encode((unsigned char *)outbuf, strlen((char *)outbuf));
		lua_pushstring(L, str.c_str());
	}
	else
		lua_pushnil(L);

	if (NULL != outbuf)
		delete outbuf;
	return 1;
}

static int DesDecrypt(lua_State *L)
{
	int argc = lua_gettop(L);
	if (2 != argc)
	{
		lua_pushnil(L);
		return 1;
	}

	size_t len;
	size_t len2;
	if (!luaL_checklstring(L, 1, &len) || !luaL_checklstring(L, 2, &len2))
	{
		lua_pushnil(L);
		return 1;
	}

	if (len2 != 8)
	{
		lua_pushnil(L);
		return 1;
	}


	CDES cs;
	const char *content = luaL_checklstring(L, 1, &len);
	const char *key = luaL_checklstring(L, 2, &len2);
	//œ»base64Ω‚√‹
	string strContent = cs.base64_decode(content);
	int ilen = strContent.length();
	unsigned char *outbuf = new unsigned char[ilen * 2];
	if (outbuf == NULL)
	{
		lua_pushnil(L);
		return 1;
	}
	memset(outbuf, 0, ilen * 2);
	
	if (cs.RunDes(cs.DECRYPT, cs.ECB, (const unsigned char* )strContent.c_str(), outbuf, ilen, (const unsigned char* )key, len2))
	{
		string jiemi = (string)(char *)outbuf;
		lua_pushstring(L, jiemi.c_str());
	}
	else
		lua_pushnil(L);

	if (NULL != outbuf)
		delete outbuf;
	return 1;
}

static const struct luaL_Reg Deslib[] = 
{
	{"DesEncrypt" , DesEncrypt},
	{"DesDecrypt" , DesDecrypt},
	{NULL, NULL}
};

extern "C" int luaopen_Deslib(lua_State *L)
{
	//luaL_newlib(L, KuaiShoulib);
	luaL_openlib (L, "Deslib", Deslib, 0);
	//luaL_register(L, "kuaishoulib",kuaishoulib); // lua 5.1
	return 1;
}
