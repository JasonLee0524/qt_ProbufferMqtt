
#ifndef BASE64_ENCODE
#define BASE64_ENCODE

#include <string>

std::string base64_encode(unsigned char const* , unsigned int len);
std::string base64_decode(std::string const& s);
#endif
