//
// Created by jaume on 11/8/19.
//

#ifndef WATERARMY_MAIN_WATERARMY_LIB_SENSORREADER_H_
#define WATERARMY_MAIN_WATERARMY_LIB_SENSORREADER_H_

class SensorReader {
 public:
  virtual ~SensorReader() = default;
  virtual unsigned short percentRead() = 0;
};

#endif //WATERARMY_MAIN_WATERARMY_LIB_SENSORREADER_H_
