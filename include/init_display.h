t_text_display *create_text_display(t_display *display, char *str);
t_text_display *create_graphic_display(t_display *display, char *path);
t_text_display *create_color_display(t_display *display, SDL_Color color);
void init_menu(t_display *display);
void init_terrain(t_display *display);
void init_characters(t_display *display);
void init_bombs(t_display *display);
void init_misc(t_display *display);
void init_default_theme(t_display *display);
t_display *init_window();
