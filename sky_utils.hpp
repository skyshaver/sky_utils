#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <charconv>
#include <optional>
#include <vector>
#include <numeric>
#include <iterator>
#include <algorithm>
#include <filesystem>
#include <print>
#include <ranges>

namespace fs = std::filesystem;

namespace sky_utils {
    auto print_vector_of_strings(std::vector<std::string>& vec) -> void
    {
        for (const auto& e : vec)
            std::cout << e << '\n';
        std::cout << '\n';
    }

    auto to_int64(std::string_view s) -> std::optional<int64_t>
    {
        int64_t value{};
        if (std::from_chars(s.data(), s.data() + s.size(), value).ec == std::errc{})
            return value;
        else
            return std::nullopt;
    }

    auto split_str_to_vector(const std::string& str, char delim = ' ') -> std::vector<std::string>
    {
        std::vector<std::string> result;
        size_t idx = str.find(delim);
        size_t start = 0;
        while (idx != std::string::npos)
        {
            result.push_back(str.substr(start, idx - start));
            start = idx + 1;
            idx = str.find(delim, idx + 1);
        }
        result.push_back(str.substr(start));
        return result;
    }

    // ifstream will NOT take a string_view as a arg see https://stackoverflow.com/questions/79445302/can-stdifstream-and-stdofstream-be-used-with-a-stdstring-view-filename-arg
    // using >> skips over blank lines like while(fin >> line), getline gets all lines, even blank
    auto file_to_vector_of_lines(fs::path path) -> std::vector<std::string>
    {
        std::ifstream fin(path, std::ios::in);
        std::string line;
        std::vector<std::string> lines;
        if (!fin.is_open())
        {
            std::println("file failed to open");
            return lines;
        }

        while (std::getline(fin, line))
        {
            lines.push_back(line);
        }
        return lines;
    }

    auto file_to_string(fs::path path) -> std::string
    {
        std::string in;
        std::ifstream fin(path, std::ios::in);
        if (!fin.is_open())
        {
            std::println("file failed to open");
            return in;
        }

        in.assign((std::istreambuf_iterator<char>(fin)), (std::istreambuf_iterator<char>()));

        return in;
    }

    template<class T, size_t N>
    auto fill_array_with_sequence(std::array<T, N>& in, const std::array<T, N>& sequence) -> void
    {

        auto start = std::begin(in);
        for (; start < std::end(in); std::advance(start, sequence.size())) {
            if (std::distance(start, std::end(in)) < sequence.size()) {
                break;
            }
            std::copy(std::begin(sequence), std::end(sequence), start);
        }
        if (start < std::end(in)) {
            std::copy(std::begin(sequence), std::begin(sequence) + std::distance(start, std::end(in)), start);
        }
    }

    template<class T>
    auto create_vector_with_sequence(const std::vector<T>& sequence, size_t capacity) -> std::vector<T>
    {

        std::vector<T> vin(capacity);

        auto start = std::begin(vin);
        for (; start < std::end(vin); std::advance(start, sequence.size())) {
            if (std::distance(start, std::end(vin)) < sequence.size()) {
                break;
            }
            std::copy(std::begin(sequence), std::end(sequence), start);
        }
        if (start < std::end(vin)) {
            std::copy(std::begin(sequence), std::begin(sequence) + std::distance(start, std::end(vin)), start);
        }

        return vin;
    }

} // end namespace sky_utils
