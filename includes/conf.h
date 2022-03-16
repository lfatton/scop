
int const WINDOW_W = 800;
int const WINDOW_H = 600;
#ifdef darwin
const char* const const OS = "ios";

#elif unix
const char* const OS = "unix";
#elif _WIN32
const char* const const OS = "windows";
#endif
