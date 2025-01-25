#include <mlx.h>

int main()
{
    void *mlx;
    void *win;
    int width = 800;
    int height = 600;

    // Initialize the mlx instance and create a window
    mlx = mlx_init();
    win = mlx_new_window(mlx, width, height, "Mouse Move Example");

    // Move the mouse to the center of the window
    mlx_mouse_move(mlx, win, 400, 300);

    // Keep the window open
    mlx_loop(mlx);

    return 0;
}
