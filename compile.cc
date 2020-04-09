#include <stdio.h>

#include <boost/algorithm/string.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "rfonttable.h"
#include "ropcodes.h"

int main(int argc, char** argv) {
  std::ifstream file(argv[1]);
  std::string readbuf;
  std::string databuf;
  std::vector<size_t> lbls;

  while (std::getline(file, readbuf)) {
    if (readbuf[0] == '*') {
      lbls.push_back(databuf.length());
    } else if (readbuf.length() != 0) {
      std::vector<std::string> tokens;
      boost::algorithm::split(tokens, readbuf, boost::algorithm::is_space());
      if (tokens[0] == "UnknownOpcode") {
        databuf += static_cast<uint8_t>(std::stoi(tokens[1], nullptr, 16));
        continue;
      }
      if (tokens[0] == "Text") {
        for (auto it = ++(tokens[1].begin()); it != tokens[1].end();) {
          std::string ch;
          ch += *(it++);
          if (ch == "\"") {
            break;
          }

          // proper handling of Unicode codepoints
          if ((ch[0] & 0xc0) == 0xc0) {
            ch += *(it++);
          }
          if ((ch[0] & 0xe0) == 0xe0) {
            ch += *(it++);
          }

          databuf += static_cast<uint8_t>(rfonttable.at(ch) >> 8);
          databuf += static_cast<uint8_t>(rfonttable.at(ch));
        }
        continue;
      }
      auto op = ropcodes.at(tokens[0]);
      databuf += std::get<0>(op);
      for (auto it = ++(tokens.begin()); it != tokens.end(); it++) {
        databuf += static_cast<uint8_t>(std::stoi(*it, nullptr, 16));
      }
    }
  }

  std::string lblbuf;
  lblbuf += static_cast<uint8_t>(lbls.size());
  lblbuf += static_cast<uint8_t>(static_cast<uint16_t>(lbls.size()) >> 8);

  for (auto lbl : lbls) {
    lbl += lbls.size() * 2;
    lbl += (std::string(argv[1]).find(".DATA") != std::string::npos) ? 4 : 2;
    lblbuf += static_cast<uint8_t>(lbl);
    lblbuf += static_cast<uint8_t>(static_cast<uint16_t>(lbl >> 8));
  }

  if (std::string(argv[1]).find(".DATA") != std::string::npos) {
    size_t pos = databuf.length() + lbls.size() * 2 + 4;
    lblbuf += static_cast<uint8_t>(pos);
    lblbuf += static_cast<uint8_t>(static_cast<uint16_t>(pos >> 8));
  }

  std::cout << lblbuf;
  std::cout << databuf;
  return 0;
}

