#pragma once
class KyokoClient : public SleepyDiscord::DiscordClient {
public:
	using SleepyDiscord::DiscordClient::DiscordClient;
	void onReady(SleepyDiscord::Ready ready) override{
		std::cout << "ready!" << std::endl;
	}
	
	void onMessage(SleepyDiscord::Message message) override {
		if (message.startsWith(PREFIX)){
			std::queue<std::string> parameters 	= split(message.content);

			const std::string mention			= "<@" + getID().string() + ">";
			const std::string mentionNick		= "<@!" + getID().string() + ">";

			//if prefix is only param, do nothing
			parameters.pop();
			if(parameters.empty()){
				return;
			}	


			//get command
			Command::MappedCommands::iterator foundCommand =
				Command::all.find(parameters.front());
			if(foundCommand == Command::all.end()) {
				if(Command::defaultCommand != nullptr){
					Command::defaultCommand->verb(*this, message, parameters);
				}else{
					sendMessage(message.channelID, "Error: Command not found");
				}
				return;
			}

			//execute found command
			parameters.pop();
			if(parameters.size() < foundCommand->second.params.size()){
				sendMessage(message.channelID, "Error: too few parameters");
				return;
			}

			foundCommand->second.verb(*this, message, parameters);

		}
	}
};