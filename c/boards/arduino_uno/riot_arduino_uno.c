#include "riot_arduino_uno.h"
#include "utils.h"

riot_arduino_uno_sinks* riot_arduino_uno_sinks_create() {
  riot_arduino_uno_sinks *sinks = xmalloc(sizeof(riot_arduino_uno_sinks));
  return sinks;
}

riot_arduino_uno_sources* riot_arduino_uno_sources_create() {
  riot_arduino_uno_sources *sources = xmalloc(sizeof(riot_arduino_uno_sources));
  return sources;
};
