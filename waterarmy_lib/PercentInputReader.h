//
// Created by jaume on 11/14/19.
//

#ifndef WATERARMY_MAIN_WATERARMY_LIB_PERCENTINPUTREADER_H_
#define WATERARMY_MAIN_WATERARMY_LIB_PERCENTINPUTREADER_H_

class PercentInputReader {
 public:
  virtual ~PercentInputReader() = default;
  virtual long readPercentInput() = 0;
};

#endif //WATERARMY_MAIN_WATERARMY_LIB_PERCENTINPUTREADER_H_
