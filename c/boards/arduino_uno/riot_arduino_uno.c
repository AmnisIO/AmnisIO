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

int riot_arduino_uno_run(riot_arduino_uno_main main) {
  if(main == NULL) {
    return -1;
  }
  riot_arduino_uno_sources *sources = riot_arduino_uno_sources_create();
  if(sources == NULL) {
    return -2;
  }
  riot_arduino_uno_sinks *sinks = main(sources);
  if(sinks == NULL) {
    return -3;
  }
  while(true) {
    // TODO: Read all inputs and map to sources
    // TODO: If all sinks/outputs have completed, break
  }
  return 0;
}
