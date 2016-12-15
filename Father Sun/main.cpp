

#define _CRT_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS

//#include  <fmt/format.h>
#include <spdlog/spdlog.h>
#include <chrono>
#include <thread> 
#include  <map>
#include "crow_all.h"


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
	using namespace std::chrono_literals;
	int64_t f0 = 0;
	int64_t f1 = 1, f2=0;

	for (int i=0;i<n;++i)
	{
		f2 = f0 + f1;
		f0 = f1;
		f1 = f2;
	}
	std::this_thread::sleep_for(2s);
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
	logger->info("Fibonnaci Number: {}", FibonaciIter((9)));

	crow::SimpleApp app;

	std::map<int, int64_t> sebonacci_numbers;

	//GET
	CROW_ROUTE(app, "/fibo_numbers").methods("POST"_method)(
		[&logger,&sebonacci_numbers](const crow::request& req )
	{
		if(req.method == "POST"_method)
		{
			logger->debug("Cia³o Wiadomosci {}", req.body);
			int n = std::stoi(req.body);
			//req.body
			sebonacci_numbers[n] = FibonaciIter(n);
			return crow::response(200);
		}
		else
		{
			return crow::response(200);
		}
		//return "";
	});

	CROW_ROUTE(app, "fibo_numbers/<int>")(
		[](int n)
	{
		return "";
	});


	/*
	CROW_ROUTE(app,"/hellow")(
		[]() 
	{
		return FibonaciIter(5);
	}
	);//wyrazenie lambda

	CROW_ROUTE(app, "/hellow/<int>")(
		[](int n)
	{
		return fmt::format("{}", FibonaciIter(n));
	}
	);
*/
	app.port(8080).multithreaded().run();
	return 0;
}