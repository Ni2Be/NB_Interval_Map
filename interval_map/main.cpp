#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#define IMPLEMENTATION_DEBUG
#include "interval_map.hpp"
#include <iostream>
#include <string>

#include <random>
#include <chrono>


TEST_CASE("assing to interval_map", "[interval_map]") {

	SECTION("usage tests") {
		
		//Interval map example useage as a compressed picture format
		/*
		0. .....ooooo.....
		1. ..ooooooooooo..
		2. ..ooo.....ooo..
		3. ..ooo.....ooo..
		4. ..ooo.....ooo..
		5. ..ooooooooooo..
		6. .....ooooo.....
		*/
		//Interval map saves cooridantes where which color (represented as "." and "o")
		//should display on a screen pixel line


		typedef std::string Color;
		//checking
		std::cout << "Expected output:\n";
		std::vector<std::vector<Color>> pixelLinesCheck = { 
			{".",".",".",".",".","o","o","o","o","o",".",".",".",".","."},
			{".",".","o","o","o","o","o","o","o","o","o","o","o",".","."},
			{".",".","o","o","o",".",".",".",".",".","o","o","o",".","."},
			{".",".","o","o","o",".",".",".",".",".","o","o","o",".","."},
			{".",".","o","o","o",".",".",".",".",".","o","o","o",".","."}, 
			{".",".","o","o","o","o","o","o","o","o","o","o","o",".","."},
			{".",".",".",".",".","o","o","o","o","o",".",".",".",".","."} };
		for (const auto& pixelLine : pixelLinesCheck) {
			for (int i = 0; i < 15; i++)
				std::cout << pixelLine[i];
			std::cout << "\n";
		}

		//result
		std::cout << "\nOutput:\n";
		typedef unsigned char key;
		std::vector<interval_map<key, Color>> pixelLines(7, { "." });

		pixelLines[0].assign(5, 10, "o");
		pixelLines[1].assign(2, 13, "o");
		for (int i = 2; i < 5; i++)
		{
			pixelLines[i].assign(2, 5, "o");
			pixelLines[i].assign(10, 13, "o");
		}
		pixelLines[5].assign(2, 13, "o");
		pixelLines[6].assign(5, 10, "o");

		for (const auto& pixelLine : pixelLines) {
			for (int i = 0; i < 15; i++)
				std::cout << pixelLine[i];
			std::cout << "\n";
		}


		//Auto Check
		for (int i = 0; i < 7; i++)
		{
			for (int n = 0; n < 15; n++)
			{
				CHECK(pixelLines[i][n] == pixelLinesCheck[i][n]);
			}
		}
	}
	SECTION("logic tests") {
		typedef uint16_t key;
		interval_map<key, std::string> map("A");


		CHECK(map[std::numeric_limits<key>::lowest()] == "A");
		CHECK(map[std::numeric_limits<key>::max()] == "A");
		CHECK(map[555] == "A");



		map.assign(12, 600, "B");
		CHECK(map[std::numeric_limits<key>::lowest()] == "A");
		CHECK(map[std::numeric_limits<key>::max()] == "A");
		CHECK(map[555] == "B");
		CHECK(map[12] == "B");
		CHECK(map[600] == "A");


		map.assign(6, 500, "A");
		CHECK(map[std::numeric_limits<key>::lowest()] == "A");
		CHECK(map[std::numeric_limits<key>::max()] == "A");
		CHECK(map[5] == "A");
		CHECK(map[444] == "A");
		CHECK(map[555] == "B");
		CHECK(map[600] == "A");


		map.assign(600, 900, "C");
		CHECK(map[std::numeric_limits<key>::lowest()] == "A");
		CHECK(map[std::numeric_limits<key>::max()] == "A");
		CHECK(map[555] == "B");
		CHECK(map[12] == "A");
		CHECK(map[600] == "C");
		CHECK(map[644] == "C");
		CHECK(map[900] == "A");


		map.assign(500, 800, "D");

		CHECK(map[std::numeric_limits<key>::lowest()] == "A");
		CHECK(map[std::numeric_limits<key>::max()] == "A");
		CHECK(map[555] == "D");
		CHECK(map[12] == "A");
		CHECK(map[500] == "D");
		CHECK(map[533] == "D");
		CHECK(map[800] == "C");
		CHECK(map[888] == "C");
		CHECK(map[900] == "A");



		map.assign(500, 700, "E");
		CHECK(map[std::numeric_limits<key>::lowest()] == "A");
		CHECK(map[std::numeric_limits<key>::max()] == "A");
		CHECK(map[555] == "E");
		CHECK(map[12] == "A");
		CHECK(map[500] == "E");
		CHECK(map[533] == "E");
		CHECK(map[700] == "D");
		CHECK(map[733] == "D");
		CHECK(map[800] == "C");
		CHECK(map[888] == "C");
		CHECK(map[900] == "A");



		map.assign(400, 501, "F");
		CHECK(map[std::numeric_limits<key>::lowest()] == "A");
		CHECK(map[std::numeric_limits<key>::max()] == "A");
		CHECK(map[555] == "E");
		CHECK(map[12] == "A");
		CHECK(map[500] == "F");
		CHECK(map[533] == "E");
		CHECK(map[700] == "D");
		CHECK(map[733] == "D");
		CHECK(map[800] == "C");
		CHECK(map[888] == "C");
		CHECK(map[900] == "A");
		CHECK(map[500] == "F");
		CHECK(map[501] == "E");


		map.assign(600, 650, "F");
		CHECK(map[std::numeric_limits<key>::lowest()] == "A");
		CHECK(map[std::numeric_limits<key>::max()] == "A");
		CHECK(map[500] == "F");
		CHECK(map[533] == "E");
		CHECK(map[620] == "F");
		CHECK(map[670] == "E");
		CHECK(map[700] == "D");
		CHECK(map[733] == "D");
		CHECK(map[800] == "C");
		CHECK(map[888] == "C");
		CHECK(map[900] == "A");



		map.assign(510, 532, "F");
		CHECK(map[std::numeric_limits<key>::lowest()] == "A");
		CHECK(map[std::numeric_limits<key>::max()] == "A");
		CHECK(map[500] == "F");
		CHECK(map[515] == "F");
		CHECK(map[533] == "E");
		CHECK(map[620] == "F");
		CHECK(map[670] == "E");
		CHECK(map[700] == "D");



		map.assign(std::numeric_limits<key>::lowest(), std::numeric_limits<key>::max(), "E");

		CHECK(map[std::numeric_limits<key>::lowest()] == "E");
		CHECK(map[std::numeric_limits<key>::max()] == "A");
		CHECK(map[555] == "E");
		CHECK(map[12] == "E");
		CHECK(map[500] == "E");
		CHECK(map[533] == "E");
		CHECK(map[700] == "E");
		CHECK(map[733] == "E");
		CHECK(map[800] == "E");
		CHECK(map[888] == "E");
		CHECK(map[900] == "E");


		//ASSING MAX TESTS
		map.assign_max("F");
		CHECK(map[std::numeric_limits<key>::lowest()] == "E");
		CHECK(map[std::numeric_limits<key>::max()] == "F");
		CHECK(map[std::numeric_limits<key>::max() - 1] == "E");
		CHECK(map[555] == "E");
		CHECK(map[12] == "E");
		CHECK(map[500] == "E");
		CHECK(map[533] == "E");

		CHECK(map.m_map.size() == 2);


		map.assign_max("E");
		CHECK(map[std::numeric_limits<key>::lowest()] == "E");
		CHECK(map[std::numeric_limits<key>::max()] == "E");
		CHECK(map[std::numeric_limits<key>::max() - 1] == "E");
		CHECK(map[555] == "E");
		CHECK(map[12] == "E");
		CHECK(map[500] == "E");
		CHECK(map[533] == "E");

		CHECK(map.m_map.size() == 1);

		//RESET TEST
		map.reset("A");

		CHECK(map[std::numeric_limits<key>::lowest()] == "A");
		CHECK(map[std::numeric_limits<key>::max()] == "A");
		CHECK(map[12] == "A");
		CHECK(map[500] == "A");
		CHECK(map[533] == "A");

		CHECK(map.m_map.size() == 1);
	}
	SECTION("template tests") {
		typedef uint16_t key;
		struct noCpy
		{
			noCpy(std::string s)
				:
				s(s) {};
			std::string s = 0;
			bool operator==(const noCpy& rhs) const { return this->s == rhs.s; };
			bool operator==(const std::string& rhs) const { return this->s == rhs; };

		private:
			noCpy& operator=(noCpy& rhs);

		};
		interval_map<key, noCpy> map({ "A" });


		CHECK(map[std::numeric_limits<key>::lowest()] == "A");
		CHECK(map[std::numeric_limits<key>::max()] == "A");
		CHECK(map[555] == "A");



		map.assign(12, 600, { "B" });
		CHECK(map[std::numeric_limits<key>::lowest()] == "A");
		CHECK(map[std::numeric_limits<key>::max()] == "A");
		CHECK(map[555] == "B");
		CHECK(map[12] == "B");
		CHECK(map[600] == "A");

		CHECK(map.check_ranges());
	}

	SECTION("randomised") {

		double val = 0;
		double overallTime = 0;
		double treeSize = 0;
		std::cout << "\nTEST: randomised:\n";
		for (int c = 0; c < 1000; c++)
		{
			typedef int key;
			interval_map<key, std::string> map("A");

			key lastFirst = 0;
			key lastSec = 0;
			key lastValNum = 0;
			interval_map<key, std::string> lastMap("A");

			std::vector<key> randNums(30000);
			for (auto& num : randNums)
				num = rand();

			if (c % 10 == 0)
				std::cout << "\r" << c / 10.0 << "%  ";
			auto before = std::chrono::system_clock::now();
			for (auto i = 0; i < 30000; i += 3)
			{
				key first = randNums[i];
				key sec = randNums[i + 1];
				key valNum = randNums[i + 2];
				map.assign(first, sec, { (char)(valNum % 24 + 67) });

				//if (!map.check_ranges())
				//{
				//	std::cout << "Last:\nINSERT: " << lastFirst << ", " << lastSec << ", " << ": " << (char)(lastValNum % 24 + 67) << "\n";
				//	lastMap.print_ranges();
				//	std::cout << "\n\nNew:\nINSERT: " << first << ", " << sec << ", " << ": " << (char)(valNum % 24 + 67) << "\n";
				//	map.print_ranges();
				//	return;

				//lastFirst = first;
				//lastSec = sec;
				//lastValNum = valNum;
				//lastMap = map;
			}
			val += (std::chrono::system_clock::now().time_since_epoch().count() - before.time_since_epoch().count()) / 10000000.0;
			overallTime += val;
			treeSize += map.m_map.size();
			CHECK(map.check_ranges());
		}
		std::cout << "\r" << 100 << "%             \n";
		std::cout << "avg time: " << val << " ms\n";
		std::cout << "avg tree size: " << treeSize / 1000.0 << "\n";
		std::cout << "overall time: " << overallTime / 1000.0 << " sec\n";

	}


	SECTION("randomised small ranges") {

		double val = 0;
		double overallTime = 0;
		double treeSize = 0;
		std::cout << "\nTEST: randomised small ranges:\n";

		for (int c = 0; c < 1000; c++)
		{
			typedef int key;
			interval_map<key, std::string> map("A");

			key lastFirst = 0;
			key lastSec = 0;
			key lastValNum = 0;
			interval_map<key, std::string> lastMap("A");

			std::vector<key> randNums(30000);
			
			for (auto& num : randNums)
					num = rand();
			for (int i = 0; i < randNums.size(); i++)
			{
				if(i % 3 == 1)				
					randNums[i] = randNums[i - 1] + 10;
				else
					randNums[i] = rand();
			}

			if(c % 10 == 0)
				std::cout << "\r" << c / 10.0 << "%  ";

			auto before = std::chrono::system_clock::now();
			for (auto i = 0; i < 30000; i += 3)
			{
				key first = randNums[i];
				key sec = randNums[i + 1];
				key valNum = randNums[i + 2];
				map.assign(first, sec, { (char)(valNum % 24 + 67) });
			}
			val += (std::chrono::system_clock::now().time_since_epoch().count() - before.time_since_epoch().count()) / 10000000.0;

			overallTime += val;
			treeSize += map.m_map.size();
			CHECK(map.check_ranges());
		}
		std::cout << "\r" << 100 << "%             \n";
		std::cout << "avg time: " << val << " ms\n";
		std::cout << "avg tree size: " << treeSize / 1000.0 << "\n";
		std::cout << "overall time: " << overallTime / 1000.0 << " sec\n";

	}



	SECTION("randomised small ranges, heavy operator==") {

		std::cout << "\nTEST: randomised small ranges, heavy operator==:\n";
		struct heavyEq
		{
			std::string gen_random(const int len) {
				std::string s;
				static const char alphanum[] =
					"0123456789"
					"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
					"abcdefghijklmnopqrstuvwxyz";

				for (int i = 0; i < len; ++i) {
					s.push_back(alphanum[rand() % (sizeof(alphanum) - 1)]);
				}
				return s;
			}
			heavyEq(std::string s)
				:
				s(s) 
			{
				s1 = gen_random(20);
				s2 = gen_random(20);
				s3 = gen_random(20);
			};
			std::string s = 0;
			std::string s1 = "";
			std::string s2 = "";
			std::string s3 = "";
			bool operator==(const heavyEq& rhs) const 
			{ 
				return this->s == rhs.s
					|| this->s1 == rhs.s1
					|| this->s2 == rhs.s2
					|| this->s3 == rhs.s3; 
			};

		};
		double val = 0;
		double overallTime = 0;
		double treeSize = 0;

		for (int c = 0; c < 1000; c++)
		{
			typedef int key;
			interval_map<key, heavyEq> map({ "A" });


			std::vector<key> randNums(30000);

			for (auto& num : randNums)
				num = rand();
			for (int i = 0; i < randNums.size(); i++)
			{
				if (i % 3 == 1)
					randNums[i] = randNums[i - 1] + 10;
				else
					randNums[i] = rand();
			}

			if (c % 10 == 0)
				std::cout << "\r" << c / 10.0 << "%  ";
			auto before = std::chrono::system_clock::now();
			for (auto i = 0; i < 30000; i += 3)
			{
				key first = randNums[i];
				key sec = randNums[i + 1];
				key valNum = randNums[i + 2];
				map.assign(first, sec, { { (char)(valNum % 24 + 67) } });
			}
			val += (std::chrono::system_clock::now().time_since_epoch().count() - before.time_since_epoch().count()) / 10000000.0;
			overallTime += val;
			treeSize += map.m_map.size();
			CHECK(map.check_ranges());
		}
		std::cout << "\r" << 100 << "%             \n";
		std::cout << "avg time: " << val << " ms\n";
		std::cout << "avg tree size: " << treeSize / 1000.0 << "\n";
		std::cout << "overall time: " << overallTime / 1000.0 << " sec\n";

	}
}


