#ifndef IRCEXTRAPLUGIN_H
#define IRCEXTRAPLUGIN_H

#include "../plugin.h"

using namespace std;

class ircExtraPlugin:public plugin
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
			if(words.at(0) == "join" && words.size() > 1)
			{
				ircNet.joinChannel(words.at(1));
				return 1;
			}
			if(words.at(0) == "part" && words.size() > 1)
			{
				ircNet.partChannel(words.at(1));
				return 1;
			}
			return 0;
		}

		int handleMessage(const string& nick, const string& channel, const vector<string>& words)
		{
			if(words.at(0) == ircNet.getNick() + ":" && words.size() >= 2)
			{
				if(words.at(1) == "you" || words.at(1) == "You")
				{
					string reply = nick + ": No, you";
					for(size_t i=2; i<words.size(); ++i)
					{
						reply += " " + words.at(i);
					}
					ircNet.sendMsg(channel, reply);
				}
				if(words.at(1) == "you're" || words.at(1) == "You're")
				{
					string reply = nick + ": No, you're";
					for(size_t i=2; i<words.size(); ++i)
					{
						reply += " " + words.at(i);
					}
					ircNet.sendMsg(channel, reply);
				}
			}
			return 0;
		}

		int startupOptions(const vector<string>& args)
		{
			for(size_t i=0; i<args.size(); ++i)
			{
				if((args.at(i) == "--channel" || args.at(i) == "--chan" || args.at(i) == "--join") && args.size() > i+1)
				{
					ircNet.joinChannel(args.at(i+1));
					++i;
				}
				else if(args.at(i) == "--nick" && args.size() > i+1)
				{
					ircNet.setNick(args.at(i+1));
					++i;
				}
			}
			return 0;
		}
};

#endif
