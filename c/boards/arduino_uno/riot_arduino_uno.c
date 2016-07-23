#include "riot_arduino_uno.h"
#include "utils.h"
#include<stdbool.h>

riot_arduino_uno_sinks* riot_arduino_uno_sinks_create() {
  riot_arduino_uno_sinks *sinks = xmalloc(sizeof(riot_arduino_uno_sinks));
  return sinks;
}

riot_arduino_uno_sources* riot_arduino_uno_sources_create() {
  riot_arduino_uno_sources *sources = xmalloc(sizeof(riot_arduino_uno_sources));
  return sources;
};

void riot_arduino_uno_map_sinks_to_write_outputs(riot_arduino_uno_sinks *sinks) {
  // TODO: Map sinks to write outputs 
}

void riot_arduino_uno_read_inputs(riot_arduino_uno_sources *sources) {
  // TODO: Read all inputs and map to sources
}

bool riot_arduino_uno_is_sinks_empty(riot_arduino_uno_sinks *sinks) {
  // TODO: Return true if no streams are present in sink, ie no output is required.
}

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
  riot_arduino_uno_map_sinks_to_write_outputs(sinks);
  while (true) {
    riot_arduino_uno_read_inputs(sources);
    if(riot_arduino_uno_is_sinks_empty(sinks))
      break;
  }
  return 0;
}
