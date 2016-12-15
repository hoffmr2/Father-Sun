

#define _CRT_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS

//#include  <fmt/format.h>
#include <spdlog/spdlog.h>
#include <chrono>
#include <thread> 
#include  <map>
#include "crow_all.h"
#include <boost/optional.hpp>

using Fibonacci_numbers = std::map<int, int64_t>;

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


boost::optional<int64_t> find_fibonacci_number(std::map<int,int64_t>& t_numbers, int n)
{
	std::pair<int, int64_t> p;
	auto it =  std::find_if(t_numbers.begin(),t_numbers.end(),[&n](auto &pair)
	{
		return (pair.first == n);
				
	});

	if(it == t_numbers.end())
	{
		return{};
	}
	else
	{
		return it->second;
	}
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


std::string get_all_numbers(const Fibonacci_numbers& map)
{
	std::string all_numbers;
	for(const auto& number: map)
	{
		all_numbers += fmt::format("{}" ,number.second);
	}
	return all_numbers;
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
		else if(req.method == "GET"_method)
		{
			auto list_all = get_all_numbers(sebonacci_numbers);
			return crow::response(200, list_all);
		}
		else
		{
			return crow::response(404);
		}
		//return "";
	});

	CROW_ROUTE(app, "fibo_numbers/<int>")(
		[&sebonacci_numbers](int n)
	{
		//if(sebonacci_numbers.find())
		auto number = find_fibonacci_number(sebonacci_numbers,n);
			if(number)
			{
				auto response = fmt::format("{}", number.get());
				return crow::response(200, response);
			}
			else
				return crow::response(404);
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
