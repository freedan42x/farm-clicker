#include "game.hpp"
#include <rapidjson/writer.h>

using namespace rapidjson;

void sec(int result)
{
  if (result < 0) (void) sec<void>(nullptr);
}

void isec(int result)
{
  if (result < 0) (void) isec<void>(nullptr);
}

std::string format_money(double x, unsigned short prec)
{
  std::string result;

  static const double eps = 0.001;
  const double rx = round(x);
  if (abs(rx - x) <= eps) {
    size_t len = snprintf(nullptr, 0, "%lu", (uint64_t) rx);
    result.resize(len);
    snprintf(&result[0], len + 1, "%lu", (uint64_t) rx);
  } else {
    size_t len = snprintf(nullptr, 0, "%.*f", prec, x);
    result.resize(len);
    snprintf(&result[0], len + 1, "%.*f", prec, x);
  }
  
  return result;
}

double apply_percent(double x, unsigned short ps)
{
  return x + x * (ps / 100.0);
}

bool read_json(std::string path, Document *d)
{
  FILE *f = fopen(path.c_str(), "r");
  if (f == NULL) {
    printf("NOTE: Could not open save file `%s`: %s\n", path.c_str(), strerror(errno));
    printf("NOTE: Creating new save file `%s`\n", path.c_str());
    return false;
  }

  fseek(f, 0, SEEK_END);
  size_t fsize = ftell(f);
  fseek(f, 0, SEEK_SET);

  char *buf = (char *) malloc(fsize + 1);
  if (fread((void *) buf, fsize, 1, f) != 1) {
    fprintf(stderr, "Could not read save file `%s`: %s\n", path.c_str(), strerror(errno));
    fclose(f);
    return false;
  }
  buf[fsize] = 0;

  fclose(f);

  if (d->Parse(buf).HasParseError()) {
    fprintf(stderr, "Corrupted save file `%s`\n", path.c_str());
    return false;
  }

  return true;
}

void write_json(std::string path, Game &game)
{
  StringBuffer sbuf;
  Writer<StringBuffer> w(sbuf);

  w.StartObject();
  {
    w.Key("config");
    w.StartObject();
    game.config->write(w);
    w.EndObject();

    w.Key("game");
    w.StartObject();
    game.write(w);
    w.EndObject();
  }
  w.EndObject();

  FILE *f = fopen(path.c_str(), "w");
  if (f == NULL) {
    fprintf(stderr, "Oopsie-doopsie! Could not open save file `%s`: %s\n", path.c_str(), strerror(errno));
    return;
  }

  if (fwrite(sbuf.GetString(), sbuf.GetLength(), 1, f) != 1) {
    fprintf(stderr, "Oopsie-doopsie! Could not write to save file `%s`: %s\n", path.c_str(), strerror(errno));
    fclose(f);
    return;
  }

  fclose(f);
}
