/*
    This file is part of cpp-base64.
    Copyright (C) 2020-2021 ReimuNotMoe <reimu@sudomaker.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the MIT License.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <vector>
#include <iostream>

#include "cpp-base64X.hpp"

using namespace YukiWorkshop;

int main() {
	// Example 1
	// Encode
	std::string brand = "YukiWorkshop";
	std::string out1;
	Base64X::Encoder<std::string> e1;
	e1 >> out1;
	e1 << brand << " " << "Rocks!" << nullptr;
	std::cout << out1 << "\n";

	// Decode
	std::string dout1;
	Base64X::Decoder<std::string> d1;
	d1 >> dout1;
	d1 << out1;
	std::cout << dout1 << "\n";


	// Example 2
	// Encode
	std::string buf = "Austin!";
	std::vector<uint8_t> v(buf.begin(), buf.end());
	std::string words[4] = { "Hey ", "guys, ", "this is "};
	std::string out2;
	Base64X::Encoder<std::string> e2;
	for (auto &word : words) {
		out2 += e2.encode(word);
	}
	out2 += e2.encode(v);
	out2 += e2.finalize();
	std::cout << out2 << "\n";

	// Decode
	Base64X::Decoder<std::string> d2;
	for (auto &it : out2) {
		std::string c;
		c.push_back(it);
		std::cout << d2.decode(c);
	}
	std::cout << "\n";

	// Example 3
	// Encode
	std::string buf0 = "roses are red";
	std::vector<uint8_t> buf1(buf0.begin(), buf0.end());
	auto out3 = Base64X::encode(buf1).as<std::string>();
	std::cout << out3 << "\n";

	auto out4 = Base64X::encode("violets are blue").as<std::vector<uint8_t>>();
	fwrite(out4.data(), 1, out4.size(), stdout);
	fputc('\n', stdout);

	// Decode
	auto dout3 = Base64X::decode(out3).as<std::string>();
	std::cout << dout3 << "\n";
	auto dout4 = Base64X::decode(out4).as<std::vector<uint8_t>>();
	fwrite(dout4.data(), 1, dout4.size(), stdout);
	fputc('\n', stdout);


	// Example 4
	// Encode
	std::vector<double> buf2 = {3.14159265357, 42.42, 233.233, 666.666};
	auto out5 = Base64X::encode(buf2).as<std::vector<uint8_t>>();
	fwrite(out5.data(), 1, out5.size(), stdout);
	fputc('\n', stdout);

	// Decode
	auto dout5 = Base64X::decode(out5).as_vector<double>();
	for (auto &it : dout5) {
		std::cout << it << " ";
	}
	std::cout << "\n";


}