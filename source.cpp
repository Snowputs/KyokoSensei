#define SLEEPY_DEFAULT_REQUEST_MODE SleepyDiscord::Async
#include "sleepy_discord/sleepy_discord.h"
#include "env.h"

//Because I'm a very good programmer, these files need to be included in this exact order to compile.
//enjoy
#include "source.h"
#include "commands.h"
#include "kyokoclient.h"
#include "commands.cpp"

#include <iostream>


/*
	Most of this code is copied from/inspired by https://github.com/yourWaifu/is-your-waifu-legal
*/

//boilerplate code
bool startsWith(const std::string& target, const std::string& test) {
	return target.compare(0, test.size(), test) == 0;
}

std::queue<std::string> split(const std::string& source) {
	std::stringstream ss(source);
	std::string item;
	std::queue<std::string> target;
	while (std::getline(ss, item, ' '))
		if (!item.empty())
			target.push(item);
	return target;
}

void makeLowerCaseOnly(std::string& string) {
	std::transform(string.begin(), string.end(), string.begin(),
		[](unsigned char c) { return std::tolower(c); });
}

//Discord client code
//class KyokoClient;

int main() {
	createAllCommands();

	KyokoClient client(PRIVATE_TOKEN, SleepyDiscord::USER_CONTROLED_THREADS);
	client.setIntents(SleepyDiscord::Intent::SERVER_MESSAGES);
	client.run();
}