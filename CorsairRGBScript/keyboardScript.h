#pragma once

#include <memory>
#include <string>
#include <vector>

class luaScript;
struct lua_State;
class corsairRGBKeyboard;



#define LUA_EXPORT_GETNAME(name) name ## _FORWARDER
#define LUA_EXPORT_DECLARE(name) \
	static int name ## _FORWARDER (lua_State *L) { \
	auto script = keyboardScript::getInstanceFromLuaState(L); \
	return script-> name (L); } \
	int name (lua_State *L);

class keyboardScript
{
public:
	keyboardScript(void);
	~keyboardScript(void);

	void doFile(const wchar_t* fileName);
	void doMainLoop();

private:
	bool inErrorState;
	std::shared_ptr<luaScript> scriptInstance;
	std::shared_ptr<corsairRGBKeyboard> keyboardInstance;


	void fireEvent(const char* eventHandler) { std::vector<int> args; fireEvent(eventHandler, args); }
	void fireEvent(const char* eventHandler, int arg1) { std::vector<int> args; args.push_back(arg1); fireEvent(eventHandler, args); }
	void fireEvent(const char* eventHandler, int arg1, int arg2) { std::vector<int> args; args.push_back(arg1); args.push_back(arg2); fireEvent(eventHandler, args); }
	void fireEvent(const char* eventHandler, std::vector<int> arguments);

	/* exported functions */
	LUA_EXPORT_DECLARE(lua_Wait);
	LUA_EXPORT_DECLARE(lua_InitializeKeyboard);
	LUA_EXPORT_DECLARE(lua_SetKeyColor);
	LUA_EXPORT_DECLARE(lua_UpdateKeyboard);


	/* utility functions */
	static void displayLUAError(char* error, lua_State* L);
	static keyboardScript* getInstanceFromLuaState(lua_State *L);

	static bool verifyParameters(lua_State *L, const char* functionName, int argCount);
	static int getIntegerParameter(lua_State *L, int stackIndex);
	static std::string getStringParameter(lua_State *L, int stackIndex);


	/* enumerations */
	enum keyboardIdentifier : int
	{
		KEYBOARD_FIRST = 0,
		KEYBOARD_K70 = KEYBOARD_FIRST,
		KEYBOARD_LAST = KEYBOARD_K70
	};

	enum keyboardIndicator : int
	{
		INDICATOR_FIRST = 0,
		INDICATOR_CAPSLOCK = INDICATOR_FIRST,
		INDICATOR_NUMLOCK,
		INDICATOR_SCROLLOCK,
		INDICATOR_LAST = INDICATOR_SCROLLOCK
	};

	enum keyboardIndicatorState : int
	{
		INDICATOR_STATE_FIRST = 0,
		INDICATOR_STATE_OFF = INDICATOR_STATE_FIRST,
		INDICATOR_STATE_ON,
		INDICATOR_STATE_LAST = INDICATOR_STATE_OFF
	};
};

