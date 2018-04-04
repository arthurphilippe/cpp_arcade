#include <unistd.h>
#include <SDL2/SDL.h>
#include "SdlDisplay.hpp"

int main(void)
{
  arc::SdlDisplay z;

  for (int i = 0; i < 10000000; i++)
    for (int i = 0; i < 10000000; i++)
      z.putstr("coucou", 50, 50);
  return (0);
}
