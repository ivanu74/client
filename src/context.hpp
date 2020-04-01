#pragma once

#include <iostream>
#include <string>
#include <system_error>

struct Context
{
  bool            finished = false;
  std::error_code ec;
};
