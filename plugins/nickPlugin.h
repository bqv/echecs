#ifndef BECOMEPLUGIN_H
#define BECOMEPLUGIN_H

#include "../plugin.h"

using namespace std;

class nickPlugin:public plugin
{
	private:

	public:
		int handleCommand(const string& nick, const string& channel, const vector<string>& words)
		{
			string reply = "";
			if(nick != "")
			{
				reply += nick + ": ";
			}
			if(words.at(0) == "nick")
			{
				if(words.size() < 2)
				{
					reply += "You need to give a name";
					ircNet.sendMsg(channel, reply);
				}
				else
				{
					ircNet.setNick(words.at(1));
				}
				return 1;
			}
			return 0;
		}

};

#endif
