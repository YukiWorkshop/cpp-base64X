/*
    This file is part of cpp-base64.
    Copyright (C) 2020-2021 ReimuNotMoe <reimu@sudomaker.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the MIT License.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#pragma once

#include <cmath>
#include <iostream>
#include <vector>
#include <string>

#include <cmath>
#include <cstdlib>
#include <cstring>

#include "3rdParty/base64/include/libbase64.h"

namespace YukiWorkshop::Base64X {

	class encode_state {
	private:
		const char *buf_;
		size_t len_;

		size_t required_size() {
			return len_ * 4 / 3 + 4;
		}
	public:
		encode_state(const char *buf, size_t len) : buf_(buf), len_(len) {

		}

		template <typename T>
		T as() {
			T ret;
			size_t encoded_size;
			ret.resize(required_size());
			base64_encode(buf_, len_, (char *)ret.data(), &encoded_size, 0);
			ret.resize(encoded_size);
			return ret;
		}
	};

	template <typename T, typename A>
	encode_state encode(const std::vector<T, A>& __input) {
		return encode_state{(const char *)__input.data(), __input.size() * sizeof(T)};
	}

	template <typename T>
	encode_state encode(const T& __input) {
		return encode_state{(const char *)__input.data(), __input.size()};
	}

	encode_state encode(const void *__input, size_t __len);
	encode_state encode(const char *__input);

	class decode_state {
	private:
		const char *buf_;
		size_t len_;

	public:
		decode_state(const char *buf, size_t len) : buf_(buf), len_(len) {

		}

		template <typename T, typename A = std::allocator<T>>
		std::vector<T, A> as_vector() {
			puts("a");
			std::vector<T, A> ret;
			size_t decoded_size;
			ret.resize(std::ceil((float)len_ / sizeof(T)));
			base64_decode(buf_, len_, (char *)ret.data(), &decoded_size, 0);
			ret.resize(std::ceil((float)decoded_size / sizeof(T)));
			return ret;
		}

		template <typename T>
		T as() {
			T ret;
			size_t decoded_size;
			ret.resize(len_);
			base64_decode(buf_, len_, (char *)ret.data(), &decoded_size, 0);
			ret.resize(decoded_size);
			return ret;
		}
	};

	template <typename T>
	decode_state decode(const T& __input) {
		return decode_state{(const char *)__input.data(), __input.size()};
	}

	decode_state decode(const void *__input, size_t __len);
	decode_state decode(const char *__input);

	template <typename T>
	class Encoder {
	protected:
		base64_state b64_state;
		T *output_target = nullptr;

		friend void __encode_to_target(Encoder& __enc, T& __tgt, const char *__input, size_t __len) {
			size_t encoded_size;
			size_t required_size = __len * 4 / 3 + 4;
			size_t tgt_orig_size = __tgt.size();

			__tgt.resize(tgt_orig_size + required_size);
			base64_stream_encode(&__enc.b64_state, __input, __len, __tgt.data() + tgt_orig_size, &encoded_size);
			__tgt.resize(tgt_orig_size + encoded_size);
		}

		friend void __finalize(Encoder& __enc, T& __tgt) {
			size_t encoded_size;
			size_t required_size = 16;
			size_t tgt_orig_size = __tgt.size();

			__tgt.resize(tgt_orig_size + required_size);
			base64_stream_encode_final(&__enc.b64_state, __tgt.data() + tgt_orig_size, &encoded_size);
			__tgt.resize(tgt_orig_size + encoded_size);

			__enc.reset();
		}
	public:
		Encoder() {
			reset();
		}

		void reset() {
			base64_stream_encode_init(&b64_state, 0);
		}

		T finalize() {
			T ret;
			__finalize(*this, ret);
			return ret;
		}

		template <typename T2, typename A>
		T encode(const std::vector<T2, A>& __input) {
			T ret;
			__encode_to_target(*this, ret, (const char *)__input.data(), __input.size() * sizeof(T2));
			return ret;
		}

		template <typename T2>
		T encode(const T2& __input) {
			T ret;
			__encode_to_target(*this, ret, (const char *)__input.data(), __input.size());
			return ret;
		}

		T encode(const char *__input) {
			T ret;
			__encode_to_target(*this, ret, __input, strlen(__input));
			return ret;
		}

		friend void operator>>(Encoder& e, T& s) {
			e.output_target = &s;
		}

		friend void operator>>(Encoder& e, void *s) {
			e.output_target = (T *)s;
		}

		template <typename T2>
		friend Encoder& operator<<(Encoder& e, T2& s) {
			__encode_to_target(e, *e.output_target, s.data(), s.size());
			return e;
		}

		friend Encoder& operator<<(Encoder& e, const char *s) {
			if (s)
				__encode_to_target(e, *e.output_target, s, strlen(s));
			else
				__finalize(e, *e.output_target);

			return e;
		}

	};


	template<typename T>
	class Decoder {
	protected:
		base64_state b64_state;
		T *output_target = nullptr;

		friend void __decode_to_target(Decoder& __dec, T& __tgt, const char *__input, size_t __len) {
			size_t decoded_size;
			size_t required_size = __len * 3 / 4 + 4;
			size_t tgt_orig_size = __tgt.size();

			__tgt.resize(tgt_orig_size + required_size);
			base64_stream_decode(&__dec.b64_state, __input, __len, __tgt.data() + tgt_orig_size, &decoded_size);
			__tgt.resize(tgt_orig_size + decoded_size);
		}
	public:
		Decoder() {
			reset();
		}

		void reset() {
			base64_stream_decode_init(&b64_state, 0);
		}

		template <typename T2>
		T decode(const T2& __input) {
			T ret;
			__decode_to_target(*this, ret, __input.data(), __input.size());
			return ret;
		}

		T decode(const char *__input) {
			T ret;
			__decode_to_target(*this, ret, __input, strlen(__input));
			return ret;
		}

		friend void operator>>(Decoder& d, T& s) {
			d.output_target = &s;
		}

		friend void operator>>(Decoder& d, void *s) {
			d.output_target = (T *)s;
		}

		template <typename T2>
		friend Decoder& operator<<(Decoder& d, T2& s) {
			__decode_to_target(d, *d.output_target, s.data(), s.size());
			return d;
		}

		friend Decoder& operator<<(Decoder& d, const char *s) {
			__decode_to_target(d, *d.output_target, s, strlen(s));
			return d;
		}
	};
}
