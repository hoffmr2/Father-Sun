

//#include  <fmt/format.h>
#include <spdlog/spdlog.h>

/*
 * Fmt - biblioteka do formatownia napsi�w
 */
int main()
{

	fmt::print("Hellow World\n");
	fmt::print("Mam tyle {} murzyn�w\n", 500);

	auto logger = spdlog::stdout_logger_mt("Father Sun",true);

	logger->set_level(spdlog::level::debug);
	logger->info("Dzisiaj techday");
	logger->debug("m�wimy o c++");
	logger->error("Co� sie popsu�o");


	return 0;
}