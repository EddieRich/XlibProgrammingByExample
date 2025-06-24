/* This program creates and displays a basic window.
 * The window has a default white background.
 *
 * Coded by : Ross Maloney
 * Date : August 2006
 */

#include <X11/Xlib.h>
#include <X11/Xutil.h>

/* exercise 1 */
#include <stdio.h>

int main(int argc, char **argv)
{
  Display *display;
  XSetWindowAttributes winatt;
  Window window;
  XSizeHints wmsize;
  XWMHints wmhints;
  XTextProperty windowName, iconName;
  XEvent event;
  char *window_name = "Basic 2.2";
  char *icon_name = "icon";
  int screen_num, done;
  unsigned long valuemask;

  /* 1 .open connection to the server */

  display = XOpenDisplay(NULL);

  /* exercise 1 */
  if (display == NULL)
  {
    fprintf(stderr, "Could not open display");
    return 1;
  }

  /* 2 .create a top-level window */

  screen_num = DefaultScreen(display);
  /*winatt.background_pixel = WhitePixel(display, screen_num);*/
  /* exercise 4 */
  winatt.background_pixel = 0xFFFFFF00;

  winatt.border_pixel = BlackPixel(display, screen_num);
  winatt.event_mask = ButtonPressMask;
  valuemask = CWBackPixel | CWBorderPixel | CWEventMask;
  window = XCreateWindow(display, RootWindow(display, screen_num),
                         200, 100, 800, 600, 2,
                         DefaultDepth(display, screen_num), InputOutput,
                         DefaultVisual(display, screen_num),
                         valuemask, &winatt);

  /* 3 .give the Window Manager hints */

  wmsize.flags = USPosition | USSize;
  XSetWMNormalHints(display, window, &wmsize);
  wmhints.initial_state = NormalState;
  wmhints.flags = StateHint;
  XSetWMHints(display, window, &wmhints);
  XStringListToTextProperty(&window_name, 1, &windowName);
  XSetWMName(display, window, &windowName);
  XStringListToTextProperty(&icon_name, 1, &iconName);
  XSetWMIconName(display, window, &iconName);

  /* 7 .map the windows */

  XMapWindow(display, window);

  /* 8 .enter the event loop */

  done = 0;
  while (done == 0)
  {
    XNextEvent(display, &event);
    switch (event.type)
    {
    case ButtonPress:
      /* exercise 2 */
      done = 1;
      break;
    }
  }

  /* 9 .cleanup before exiting */

  XUnmapWindow(display, window);
  XDestroyWindow(display, window);
  XCloseDisplay(display);

  /* you must return a value, author forgot this*/
  return 0;
}
