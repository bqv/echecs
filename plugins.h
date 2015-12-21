#ifndef PLUGINS_H
#define PLUGINS_H
#include "plugin.h"

#include "plugins/chessPlugin.h"
#include "plugins/choosePlugin.h"
#include "plugins/nickPlugin.h"
#include "plugins/ircExtraPlugin.h"
#include "plugins/aliasPlugin.h"

class plugins
{
	private:
		vector<plugin*> pluginList;
	public:
		plugins()
		{
			pluginList.push_back(new chessPlugin);
			pluginList.push_back(new choosePlugin);
			pluginList.push_back(new nickPlugin);
			pluginList.push_back(new ircExtraPlugin);
			//alias plugin should go last to stop other commands being realiased.
			pluginList.push_back(new aliasPlugin);
		}
		//handle commads for all plugins, returns 0 on not matched, 1 on matched
		int handleCommand(string nick, string channel, vector<string> words);
		//handle messages for all plugins, returns 0 on not matched, 1 on matched
		int handleMessage(string nick, string channel, vector<string> words);
		//allows each plugin to run something each tick.  Returns the number of plugins that did something.
		int doTick();
		//allows each plugin to check the command line arguments and use them as they see fit.
		int startupOptions(vector<string> args);
};

#endif
