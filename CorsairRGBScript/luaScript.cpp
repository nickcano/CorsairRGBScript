#include "luaScript.h"

#include <string>
#include <windows.h>

std::map<lua_State*, luaScript*> luaScript::luaData;

///////////////////////////////////////////////////////////////////////////////
// construction and destruction
///////////////////////////////////////////////////////////////////////////////

luaScript* luaScript::getInstance(lua_State* L)
{
	auto ret = luaScript::luaData.find(L);
	if (ret == luaScript::luaData.end())
		luaL_error(L, "Failed to get current script pointer!");
	return ret->second;
}

luaScript::luaScript(_DisplayError errorFunction, void* extraData)
{
	this->errorFunction = errorFunction;
	tablesOpen = 0;
	L = luaL_newstate();
	luaL_openlibs(L);

	this->extraData = extraData;
	luaScript::luaData.insert(std::make_pair<lua_State*, luaScript*>(L, this));
}

luaScript::~luaScript(void)
{
	auto ret = luaScript::luaData.find(L);
	if (ret != luaScript::luaData.end())
		luaScript::luaData.erase(ret);
	lua_close(L);
}

///////////////////////////////////////////////////////////////////////////////
// load lua code
///////////////////////////////////////////////////////////////////////////////
bool widePathToShortAsciiPath(const wchar_t* wPath, char* cPath)
{
	wchar_t transformString[MAX_PATH];
	ZeroMemory(transformString, MAX_PATH * sizeof(wchar_t));
	ZeroMemory(cPath, MAX_PATH);

	do
	{
		if (GetShortPathNameW(wPath, NULL, 0) == 0) break;
		if (GetShortPathNameW(wPath, transformString, MAX_PATH) == 0) break;
		for (int i = 0; i < MAX_PATH; i++)
			cPath[i] = ((char*)&transformString[0])[i*2];
		return true;
	} while (0);

	return false;
}

bool luaScript::doFile(const wchar_t* filename)
{
	char cFileName[MAX_PATH*2];
	if (!widePathToShortAsciiPath(filename, cFileName))
		return false;

	if (luaL_loadfile(L, cFileName))
	{
		reportErrors();
		return false;
	}
	else
	{
		if (lua_pcall(L,0,0,0))
		{
			reportErrors();
			return false;
		}
	}
}

bool luaScript::doString(const char* script)
{
	if (luaL_loadstring(L, script))
	{
		reportErrors();
		return false;
	}
	else
	{
		if (lua_pcall(L,0,0,0))
		{
			reportErrors();
			return false;
		}
	}

	return true;
}

bool luaScript::doBinary(const char* buffer, int size, const wchar_t* name)
{
	char cName[MAX_PATH*2];
	widePathToShortAsciiPath(name, cName);
	if (luaL_loadbuffer(L, buffer, size, cName))
	{
		reportErrors();
		return false;
	}
	else
	{
		if (lua_pcall(L,0,0,0))
		{
			reportErrors();
			return false;
		}
	}

	return true;
}

void luaScript::reportErrors()
{
	if (this->errorFunction)
	{
		char errorText[1024];
		sprintf(errorText, "%s", lua_tostring(L, -1));
		lua_pop(L, 1);
		this->errorFunction(errorText, L);
	}
}

lua_State* luaScript::getState()
{
	return this->L;
}

///////////////////////////////////////////////////////////////////////////////
// get globals
///////////////////////////////////////////////////////////////////////////////

bool luaScript::getGlobalInteger(const char* key, int &value)
{
	lua_getglobal(L, key);
	if (!lua_isnumber(L, -1))
	{
		lua_pop(L,1);
		return false;
	}

	value = (int)lua_tonumber(L,-1);
	lua_pop(L,1);
	return true;
}

bool luaScript::getGlobalString(const char* key, char* &value)
{
	lua_getglobal(L, key);
	if (!lua_isstring(L, -1))
	{
		lua_pop(L,1);
		return false;
	}

	value = (char*)lua_tostring(L,-1);
	lua_pop(L,1);
	return true;
}

bool luaScript::getGlobalBool(const char* key, bool &value)
{
	lua_getglobal(L, key);
	if (!lua_isboolean(L, -1))
	{
		lua_pop(L,1);
		return false;
	}

	value = (bool)lua_toboolean(L,-1);
	lua_pop(L,1);
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// get from tables
///////////////////////////////////////////////////////////////////////////////
bool luaScript::beginGetGlobalTable(const char* table)
{
	if (tablesOpen > 0 )
	{
		lua_pushstring(L, table);
		lua_gettable(L, -2);
	}
	else
	{
		lua_getglobal(L, table);
	}

	if (!lua_istable(L, -1))
	{
		lua_pop(L,1);
		return false;
	}

	tablesOpen++;
	return true;
}

bool luaScript::getGlobalFieldInteger(const char* key, int &value)
{
	lua_pushstring(L, key);
	lua_gettable(L, -2);
	if (!lua_isnumber(L, -1))
	{
		lua_pop(L, 1);
		return false;
	}

	value = (int)lua_tonumber(L, -1);
	lua_pop(L, 1);  // remove number and key
	return true;
}

bool luaScript::getGlobalFieldString(const char* key, char* &value)
{
	lua_pushstring(L, key);
	lua_gettable(L, -2);
	if (!lua_isstring(L, -1))
	{
		lua_pop(L, 1);
		return false;
	}

	value = (char*)lua_tostring(L, -1);
	lua_pop(L, 1);  // remove number and key
	return true;
}

void luaScript::endGetGlobalTable()
{
	tablesOpen--;
	lua_pop(L, 1);
}



///////////////////////////////////////////////////////////////////////////////
// push args
///////////////////////////////////////////////////////////////////////////////

int luaScript::pushTable()
{
	lua_newtable(L);
	return lua_gettop(L);
}

void luaScript::addTableInt(int table, const char* key, int value)
{
	lua_pushstring(L,key);
	lua_pushnumber(L,value);
	lua_settable(L, table);
}

void luaScript::addTableString(int table, const char* key, const char* value)
{
	lua_pushstring(L,key);
	lua_pushstring(L,value);
	lua_settable(L, table);
}

void luaScript::pushFunction(const char* name, lua_CFunction function)
{
	//lua_pushcclosure(L, function, 0);
	//lua_setglobal(L, name);
	lua_register(L, name, function);
}

void luaScript::pushNumber(const char* name, int value)
{
	lua_pushnumber(L, value);
	lua_setglobal(L, name);
}


///////////////////////////////////////////////////////////////////////////////
// execute functions
///////////////////////////////////////////////////////////////////////////////

void luaScript::beginExecuteFunction(const char* name)
{
	lua_getglobal(L, name);
}

void luaScript::pushFunctionArg(const char* value)
{
	lua_pushstring(L, value);
}

void luaScript::pushFunctionArg(int value)
{
	lua_pushnumber(L, value);
}

bool luaScript::endExecuteFunction(int args, int rets)
{
	if (lua_pcall(L, args, rets, 0))
	{
		reportErrors();
		return false;
	}

	return true;
}

///////////////////////////////////////////////////////////////////////////////
// get returns
///////////////////////////////////////////////////////////////////////////////

bool luaScript::getReturnInteger(int &value)
{
	if (!lua_isnumber(L, -1))
	{
		lua_pop(L,1);
		return false;
	}

	value = (int)lua_tonumber(L,-1);
	lua_pop(L,1);
	return true;
}

bool luaScript::getReturnString(char* &value)
{
	if (!lua_isstring(L, -1))
	{
		lua_pop(L,1);
		return false;
	}

	value = (char*)lua_tostring(L,-1);
	lua_pop(L,1);
	return true;
}

bool luaScript::getReturnBool(bool &value)
{
	if (!lua_isboolean(L, -1))
	{
		lua_pop(L,1);
		return false;
	}

	value = (bool)lua_toboolean(L,-1);
	lua_pop(L,1);
	return true;
}