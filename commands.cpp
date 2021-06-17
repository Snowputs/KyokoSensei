
void createAllCommands(){
    	Command::addCommand({
		"hello", {}, [](
			KyokoClient& client,
			SleepyDiscord::Message& message,
			std::queue<std::string>& params
		){
			client.sendMessage(message.channelID, "Hello, " + message.author.username);
		}
	});

    Command::addCommand({
		"help", {}, [](
			KyokoClient& client,
			SleepyDiscord::Message& message,
			std::queue<std::string>&
		) {
			constexpr char start[] = "Here's a list of all commands:```\n";
			constexpr char theEnd[] = "```";
			//estimate length
			std::size_t length = strlen(start) + strlen(theEnd);
			for (Command::MappedCommand& command : Command::all) {
				length += command.first.size();
				length += 2; // ' ' and '\n'
				for (std::string& parmaName : command.second.params) {
					length += 2; // '<' and '> '
					length += parmaName.size();
				}
			}
			
			std::string output;
			output.reserve(length);
			output += start;
			for (Command::MappedCommand& command : Command::all) {
				output += command.first;
				output += ' ';
				for (std::string& parmaName : command.second.params) {
					output += '<';
					output += parmaName;
					output += "> ";
				}
				output += '\n';
			}
			output += theEnd;
			client.sendMessage(message.channelID, output, SleepyDiscord::Async);
		}
	});
}