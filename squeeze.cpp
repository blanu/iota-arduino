#include <vector>
#include <tuple>
#include "squeeze.h"

// int

// Encode an integer in the fewest number of bytes, plus a 1-byte length to tell us how many bytes that is.
std::vector<byte> squeeze_int(int value)
{
  // Allocate the result
  std::vector<byte> r;

  // The only case where the length can be zero is for the number 0.
  if(value == 0)
  {
    r.push_back(0);
    return r;
  }

  // Remember if the integer was positive or negative. If negative, we will make the length negative later.
  // Regardless, we end up with a positive integer for the purpose of encoding.
  // Positive integers are more straightforward to encode.
  int negative = 0;
  if(value < 0)
  {
    negative = 1;
    value = -value;
  }

  // Determine how many bytes we need to encode the integer by removing zero bytes from the top end.
  // Note that this algorithm does not care about endianness and accommodates any word size.
  int max = sizeof(int);
  int saved = 0;
  int found = 0;
  for(int offset=0; offset<max; offset++)
  {
    // Get each byte of the integer separately so that we can count how many bytes we need.
    byte b = (value >> ((max - 1 - offset) * 8)) & 0xFF;

    if(found)
    {
      r.push_back(b);
    }
    else
    {
      // If it's a zero byte, we can discard it
      if(b == 0)
      {
        // Count the number of high bytes that are zero.
        saved++;
      }
      else
      {
        // When we get to the first non-zero byte, stop counting
        r.push_back(b);
        found = 1;
      }
    }
  }

  // The number of bytes to encode is all the bytes, minus the high zero bytes.
  int length = max - saved;

  // If the integer is negative, we make the length byte negative as well
  // The length byte goes at the beginning of the encoding
  if(negative)
  {
    r.insert(r.begin(), 0x80 | (byte)length);
  }
  else
  {
    r.insert(r.begin(), (byte)length);
  }

  return r;
}

std::tuple<int, std::vector<byte>> expand_int(std::vector<byte> data)
{
  // If input vector is empty, we have nothing to parse
  if(data.size() == 0)
  {
    return std::make_tuple(0, std::vector<byte>());
  }

  // The first byte of the input array is the length at the beginning of the array with the integer for us to parse, the rest of the array is extra
  int integerLength = (int)data.front();

  // The only case where the length can be zero is for the number 0.
  if(integerLength == 0)
  {
    std::vector<byte> rest(data.begin() + 1, data.end());
    return std::make_tuple(0, rest);
  }

  Serial.write((byte)0xFA);

  // We encode if the integer is positive or negative by using a positive or negative length
  int negative = 0;
  if(integerLength & 0x80) // Check the sign bit & 0b10000000
  {
    negative = 1;
    integerLength = integerLength & 0x7F; // Clear the sign bit & 0b01111111
  }

  if(data.size() < 1 + integerLength)
  {
    Serial.write({0xF7});
    return std::make_tuple(0, std::vector<byte>());
  }

  std::vector<byte> integerData(data.begin() + 1, data.begin() + 1 + integerLength);
  std::vector<byte> rest(data.begin() + 1 + integerLength, data.end());

  int integer = 0;
  for (byte b : integerData)
  {
    integer = (integer << 8) + (int)b;
  }

  if(negative)
  {
    integer = -integer;
  }

  return std::make_tuple(integer, rest);
}

int expand_int_from_bytes(std::vector<byte> bytes)
{
  int integer = 0;
  for (byte b : bytes)
  {
    integer = (integer << 8) + (int)b;
  }

  return integer;
}

// Encode an integer in the fewest number of bytes, plus a 1-byte length to tell us how many bytes that is.
std::vector<byte> squeeze_float(float value)
{
  // Allocate the result
  std::vector<byte> r;

  // The only case where the length can be zero is for the number 0.
  if(value == 0.0)
  {
    return r;
  }

  // Remember if the integer was positive or negative. If negative, we will make the length negative later.
  // Regardless, we end up with a positive integer for the purpose of encoding.
  // Positive integers are more straightforward to encode.
  int negative = 0;
  if(value < 0.0)
  {
    negative = 1;
    value = -value;
  }

  // Determine how many bytes we need to encode the integer by removing zero bytes from the top end.
  // Note that this algorithm does not care about endianness and accommodates any word size.
  int max = sizeof(float);
  if(max == 4)
  {
        uint32_t bits;
        memcpy(&bits, &value, 4);

        int sign = (bits >> 31) & 1;                // Extract sign (1 bit)
        int exponent = ((bits >> 23) & 0xFF) - 127; // Extract exponent (8 bits), subtract bias (127)
        int mantissa = (int)(bits & 0x7FFFFF);      // Extract mantissa (23 bits). Note: We assume that the word size is EITHER 32 bits or more 64 bits. A fully generaized algorithm for any word size 1<=N<=? is outside of the scope of this implementation.

        if (exponent != -127) { // Normalized numbers add implicit leading 1
            mantissa |= (1 << 23);
        }

        std::vector<int> ints = {sign, exponent, mantissa};
        std::vector<byte> valueBytes = squeeze_ints(ints);

        int length = valueBytes.size();
        std::vector<byte> lengthBytes = squeeze_int(length);

        std::vector<byte> resultBytes = std::vector<byte>();
        resultBytes.insert(resultBytes.end(), lengthBytes.begin(), lengthBytes.end());
        resultBytes.insert(resultBytes.end(), valueBytes.begin(), valueBytes.end());
        return resultBytes;
  }
  else if(max == 8)
  {
        uint64_t bits;
        memcpy(&bits, &value, 4);

        int sign = (bits >> 63) & 1;                  // Extract sign (1 bit)
        int exponent = ((bits >> 52) & 0x7FF) - 1023; // Extract exponent (11 bits), subtract bias (1023)
        uint64_t mantissa = bits & 0xFFFFFFFFFFFFF;   // Extract mantissa (52 bits)

        if (exponent != -1023) { // Normalized numbers add implicit leading 1
            mantissa |= (1ULL << 52);
        }

        if(sizeof(int) == sizeof(uint64_t))
        {
          std::vector<int> ints = {sign, exponent, (int)mantissa};
          std::vector<byte> valueBytes = squeeze_ints(ints);

          int length = valueBytes.size();
          std::vector<byte> lengthBytes = squeeze_int(length);

          std::vector<byte> resultBytes = std::vector<byte>();
          resultBytes.insert(resultBytes.end(), lengthBytes.begin(), lengthBytes.end());
          resultBytes.insert(resultBytes.end(), valueBytes.begin(), valueBytes.end());
          return resultBytes;
        }
        else // Note: We assume that the word size is EITHER 32 bits or more 64 bits. A fully generaized algorithm for any word size 1<=N<=? is outside of the scope of this implementation.
        {
          int top = (int)(mantissa >> 32);
          int bottom = (int)((mantissa << 32) >> 32);
          std::vector<int> ints = {sign, exponent, top, bottom};
          std::vector<byte> valueBytes = squeeze_ints(ints);

          int length = valueBytes.size();
          std::vector<byte> lengthBytes = squeeze_int(length);

          std::vector<byte> resultBytes = std::vector<byte>();
          resultBytes.insert(resultBytes.end(), lengthBytes.begin(), lengthBytes.end());
          resultBytes.insert(resultBytes.end(), valueBytes.begin(), valueBytes.end());
          return resultBytes;
        }
  }
  else
  {
    return std::vector<byte>();
  }
}

std::tuple<float, std::vector<byte>> expand_float(std::vector<byte> data)
{
  // If input vector is empty, we have nothing to parse
  if(data.size() == 0)
  {
    return std::make_tuple(0, std::vector<byte>());
  }

  // The first byte of the input array is the length at the beginning of the array with the integer for us to parse, the rest of the array is extra
  int integerLength = (int)data.front();

  // We encode if the integer is positive or negative by using a positive or negative length
  int negative = 0;
  if(integerLength < 0)
  {
    negative = 1;
    integerLength = -integerLength;
  }

  std::vector<byte> integerData(data.begin(), data.begin() + integerLength);
  std::vector<byte> rest(data.begin() + integerLength, data.end());

  // The only case where the length can be zero is for the number 0.
  if(integerLength == 0)
  {
    return std::make_tuple(0, rest);
  }

  int integer = 0;
  for (byte b : integerData)
  {
    integer = (integer << 8) + (int)b;
  }

  return std::make_tuple(integer, rest);
}

// ints

// Encode an array of integers in the fewest number of bytes, plus an encoded integer length to tell us how many bytes that is.
std::vector<byte> squeeze_ints(std::vector<int> values)
{
  // Allocate the result
  std::vector<byte> r=std::vector<byte>();

  // The only case where the length can be zero is for the number 0.
  if(values.size() == 0)
  {
    return r;
  }

  int size = values.size();
  std::vector<byte> sizeBytes = squeeze_int(size);

  r.insert(r.begin(), sizeBytes.begin(), sizeBytes.end());

  for(int value : values)
  {
    std::vector<byte> valueBytes = squeeze_int(value);
    r.insert(r.end(), valueBytes.begin(), valueBytes.end());
  }

  return r;
}

std::tuple<std::vector<int>, std::vector<byte>> expand_ints(std::vector<byte> data)
{
  // If input vector is empty, we have nothing to parse
  if(data.size() == 0)
  {
    return std::make_tuple(std::vector<int>(), data);
  }

  std::vector<int> integers = std::vector<int>();

  // The first byte of the input array is the length at the beginning of the array with the integer for us to parse, the rest of the array is extra
  std::tuple<int, std::vector<byte>> sizeResult = expand_int(data);
  int size = std::get<0>(sizeResult);
  std::vector<byte> rest = std::get<1>(sizeResult);

  // The only case where the length can be zero is for empty array [].
  if(size == 0)
  {
    return std::make_tuple(std::vector<int>(), rest);
  }

  for(int count=0; count<size; count++)
  {
    std::tuple<int, std::vector<byte>> intResult = expand_int(rest);
    int integer = std::get<0>(intResult);
    rest = std::get<1>(intResult);

    integers.push_back(integer);
  }

  return std::make_tuple(integers, rest);
}

// floats

// Encode an array of floats in the fewest number of bytes, plus an encoded integer length to tell us how many bytes that is.
std::vector<byte> squeeze_floats(std::vector<float> values)
{
  // Allocate the result
  std::vector<byte> r=std::vector<byte>();

  // The only case where the length can be zero is for the number 0.
  if(values.size() == 0)
  {
    return r;
  }

  int size = values.size();
  std::vector<byte> sizeBytes = squeeze_int(size);

  r.insert(r.begin(), sizeBytes.begin(), sizeBytes.end());

  for(float value : values)
  {
    std::vector<byte> valueBytes = squeeze_float(value);
    r.insert(r.end(), valueBytes.begin(), valueBytes.end());
  }

  return r;
}

std::tuple<std::vector<float>, std::vector<byte>> expand_floats(std::vector<byte> data)
{
  // If input vector is empty, we have nothing to parse
  if(data.size() == 0)
  {
    return std::make_tuple(std::vector<float>(), data);
  }

  std::vector<float> floats = std::vector<float>();

  // The first byte of the input array is the length at the beginning of the array with the integer for us to parse, the rest of the array is extra
  std::tuple<int, std::vector<byte>> sizeResult = expand_int(data);
  int size = std::get<0>(sizeResult);
  std::vector<byte> rest = std::get<1>(sizeResult);

  // The only case where the length can be zero is for empty array [].
  if(size == 0)
  {
    return std::make_tuple(std::vector<float>(), rest);
  }

  for(int count=0; count<size; count++)
  {
    std::tuple<float, std::vector<byte>> floatResult = expand_float(rest);
    float floating = std::get<0>(floatResult);
    rest = std::get<1>(floatResult);

    floats.push_back(floating);
  }

  return std::make_tuple(floats, rest);
}
