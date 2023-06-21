#include <sys/stat.h>

#include <iostream>

#include "pagprobe.h"
using namespace pagprobe;
using namespace pag;
static bool FileExsits(const char *path) {
  struct stat s;
  auto r = stat(path, &s);
  return r == 0 && ((S_IFREG & s.st_mode) != 0);
}

int main(int argc, const char **argv) {
  json results = json::array();
  for (size_t i = 1; i < argc; i++) {
    const auto *file_path = argv[i];
    if (!FileExsits(file_path)) {
      continue;
    }
    auto file = File::Load(file_path);
    results.push_back(Dump(file.get()));
  }
  if (results.size() == 1) {
    std::cout << results.front().dump(2) << std::endl;
  } else {
    std::cout << results.dump(2) << std::endl;
  }
  return 0;
}