//
// Created by bin zhang on 2019/1/6.
//

#include "app.h"

extern int main_loop();

std::shared_ptr<Application>& Application::instance(){
	static std::shared_ptr<Application> handle ;
	if(!handle.get()){
		handle = std::make_shared<Application>();
	}
	return handle;
}

///

Application&  Application::init(){
	cfgs_.load("settings.txt");
//	Logger::HandlerPtr handle =
	logger_.addHandler( std::make_shared<LogStdoutHandler>());
	logger_.addHandler( std::make_shared<LogFileHandler>("ctp-market"));
	logger_.setLevel(Logger::DEBUG);

	return *this;
}


Logger& Application::getLogger(){
	return logger_;
}

void Application::run(){
//	InnerController::instance()->run();
	main_loop();
	wait_for_shutdown();

}

void Application::stop(){
	cv_.notify_one();
}

void Application::addService(std::shared_ptr<Service>& service ){
	services_.push_back(service);
}

Config& Application::getConfig(){
	return cfgs_;
}

void Application::wait_for_shutdown(){
	getLogger().info(name() + " Started..");

	io_service_.run();
	std::unique_lock<std::mutex> lk(mutex_);
	cv_.wait(lk);
}

std::string Application::name(){
	return cfgs_.get_string("application.name","Application");
}

int main(int argc , char ** argvs){
	Application::instance()->init().run();
}

