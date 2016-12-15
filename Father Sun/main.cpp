

//#include  <fmt/format.h>
#include <spdlog/spdlog.h>

/*
 * Fmt - biblioteka do formatownia napsiów
 */


int64_t FibonacciRek(int n)
{
	if (n == 0 || n == 1)
		return n;
	else
		return FibonacciRek(n - 1) + FibonacciRek((n - 2));
}


int64_t FibonaciIter(int n)
{
	int64_t f0 = 0;
	int64_t f1 = 1, f2=0;

	for (int i=0;i<n;++i)
	{
		f2 = f0 + f1;
		f0 = f1;
		f1 = f2;
	}
	return f2;
}



int main()
{

	fmt::print("Hellow World\n");
	fmt::print("Mam tyle {} murzynów\n", 500);

	auto logger = spdlog::stdout_logger_mt("Father Sun",true);

	logger->set_level(spdlog::level::debug);
	logger->info("Dzisiaj techday");
	logger->debug("mówimy o c++");
	logger->error("Coœ sie popsu³o");
	logger->info("Fibonnaci Number: {}", FibonaciIter((3)));


	return 0;
}