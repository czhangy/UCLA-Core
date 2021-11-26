struct flagState {
  int input;
  int output;
  char** path;
};

int
handleOptions (int argc, char **argv, struct flagState* container);
