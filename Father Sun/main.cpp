

//#include  <fmt/format.h>
#include <spdlog/spdlog.h>

/*
 * Fmt - biblioteka do formatownia napsiów
 */
int main()
{

	fmt::print("Hellow World\n");
	fmt::print("Mam tyle {} murzynów\n", 500);

	auto logger = spdlog::stdout_logger_mt("Father Sun",true);

	logger->set_level(spdlog::level::debug);
	logger->info("Dzisiaj techday");
	logger->debug("mówimy o c++");
	logger->error("Coœ sie popsu³o");


	return 0;
}