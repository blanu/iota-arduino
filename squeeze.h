#ifndef __SQUEEZE_H_
#define __SQUEEZE_H_

#include <Arduino.h>
#include <tuple>
#include <vector>

class Storage;

std::vector<byte> squeeze_int(int value);
std::tuple<int, std::vector<byte>> expand_int(std::vector<byte> value);
int expand_int_from_bytes(std::vector<byte> bytes);

std::vector<byte> squeeze_float(float value);
std::tuple<float, std::vector<byte>> expand_float(std::vector<byte> value);

std::vector<byte> squeeze_ints(std::vector<int> value);
std::tuple<std::vector<int>, std::vector<byte>> expand_ints(std::vector<byte> value);

std::vector<byte> squeeze_floats(std::vector<float> value);
std::tuple<std::vector<float>, std::vector<byte>> expand_floats(std::vector<byte> value);

#endif