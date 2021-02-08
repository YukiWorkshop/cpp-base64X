/*
    This file is part of cpp-base64.
    Copyright (C) 2020-2021 ReimuNotMoe <reimu@sudomaker.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the MIT License.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include "cpp-base64X.hpp"

using namespace YukiWorkshop;

Base64X::encode_state Base64X::encode(const void *__input, size_t __len) {
	return encode_state{(const char *)__input, __len};
}

Base64X::encode_state Base64X::encode(const char *__input) {
	return encode_state{__input, strlen(__input)};
}

Base64X::decode_state Base64X::decode(const void *__input, size_t __len) {
	return decode_state((const char *)__input, __len);
}

Base64X::decode_state Base64X::decode(const char *__input) {
	return decode_state(__input, strlen(__input));
}
