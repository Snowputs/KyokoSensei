#pragma once
class KyokoClient;

namespace Command {
	using Verb = std::function<
		void(
			KyokoClient&,
			SleepyDiscord::Message&,
			std::queue<std::string>&
			)
	>;
	struct Command {
		std::string name;
		std::vector<std::string> params;
		Verb verb;
	};
	using MappedCommands = std::unordered_map<std::string, Command>;
	using MappedCommand = MappedCommands::value_type;
	static MappedCommands all;
	static void addCommand(Command command) {
		all.emplace(command.name, command);
	}
	static Command* defaultCommand = nullptr;
};

void createAllCommands();