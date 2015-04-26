#pragma once

#include "lua\include\lua.hpp"
#pragma comment(lib, "lua\\lib\\lua5.1.lib")
#include <map>

typedef void(*_DisplayError)(char*, lua_State*);
bool widePathToShortAsciiPath(const wchar_t* wPath, char* cPath);

class luaScript
{
	public:
		static luaScript* getInstance(lua_State* L);

		luaScript(_DisplayError errorFunction, void* extraData = NULL);
		~luaScript(void);

		template<typename T>
		T getExtraData() { return static_cast<T>(this->extraData); }

		bool doFile(const wchar_t* filename);
		bool doString(const char* script);
		bool doBinary(const char* buffer, int size, const wchar_t* name);

		lua_State* getState();
		bool getGlobalInteger(const char* key, int &value);
		bool getGlobalString(const char* key, char* &value);
		bool getGlobalBool(const char* key, bool &value);

		bool beginGetGlobalTable(const char* table);
		bool getGlobalFieldInteger(const char* key, int &value);
		bool getGlobalFieldString(const char* key, char* &value);
		void endGetGlobalTable();
		
		int pushTable();
		void addTableInt(int table, const char* key, int value);
		void addTableString(int table, const char* key, const char* value);
		
		void pushFunction(const char* name, lua_CFunction function);
		void pushNumber(const char* name, int value);

		void beginExecuteFunction(const char* name);
		void pushFunctionArg(const char* value);
		void pushFunctionArg(int value);
		bool endExecuteFunction(int args, int rets);

		bool getReturnInteger(int &value);
		bool getReturnString(char* &value);
		bool getReturnBool(bool &value);

	private:
		static std::map<lua_State*, luaScript*> luaData;

		void* extraData;
		_DisplayError errorFunction;
		int tablesOpen;
		lua_State *L;
		void reportErrors();
};